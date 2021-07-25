import json
import pickle
from collections import OrderedDict
from copy import deepcopy
from datetime import datetime

import deap
import deap.benchmarks
import deap.gp
import matplotlib.pyplot as plt
import numpy as np
from deap import algorithms, base, creator, tools

from lib.algorithms import eaMuPlusLambda
from lib.Simulator import Simulator

plt.style.use('dark_background')

np.random.seed(1)
N = 0


class Nsga2Optimizer:
    NGEN = 50
    POP_SIZE = 100
    OFFSPRING_SIZE = 100
    MUTATION_PROP = 0.3
    SEED = 1

    def __init__(self):
        self.N_generations = Nsga2Optimizer.NGEN
        self.population_size = Nsga2Optimizer.POP_SIZE
        self.offspring_size = Nsga2Optimizer.OFFSPRING_SIZE
        self.mutation_probability = Nsga2Optimizer.MUTATION_PROP
        # self.crossover_probability = 1 - Nsga2Optimizer
        self.random_seed = Nsga2Optimizer.SEED
        self.pop = None
        self.logbook = None

        self.model_meta_data = None
        self.parameters_info = None
        self.stimulation_protocol = None
        self.experimental_data = None

        self.best_solution = None
        self.best_score = None

    def setup(self, config: dict):
        self._set_Nsga_config(config["Optimizer"])
        # {"Name"}
        self._set_config("model_meta_data",
                         config.get("model_meta_data", None))
        # OrderedDict{"name": {"location":"","low":"","high":""} }
        # List [{"location": "", "name":" ","value":0.0,"low":"",high:""} ]
        self._set_config("parameters_info",
                         config.get("parameters_info", None))

        # {"Protocol Name": "IClamp", "Stimulus Type":"Step" , "Amplitude":"21",...}
        self._set_config("stimulation_protocol",
                         config.get("stimulation_protocol", None))
        # OrderedDict{"name": {"weight":"","mean":"","std":""} }
        self._set_config("experimental_data",
                         config.get("experimental_data", None))
        self.simulator = Simulator(
            self.model_meta_data["model_type"], self.model_meta_data["model_file"], self.model_meta_data["model_name"])

    def _set_Nsga_config(self, config):
        self.N_generations = config.get(
            'Number of Generations', Nsga2Optimizer.NGEN)
        self.population_size = config.get(
            'Population Size', Nsga2Optimizer.POP_SIZE)
        self.offspring_size = config.get(
            'Offspring Size', Nsga2Optimizer.OFFSPRING_SIZE)
        self.mutation_probability = config.get(
            'Mutation Probability', Nsga2Optimizer.MUTATION_PROP)
        self.crossover_probability = 1 - self.mutation_probability
        self.random_seed = config.get(
            'Random Seed', Nsga2Optimizer.SEED)

    def _set_config(self, config_name: str, config):

        CONFIGs_Structure_types = {"Optimizer": dict, "stimulation_protocol": dict,
                                   "model_meta_data": dict, "parameters_info": list, "experimental_data": OrderedDict}
        # print(config)
        if (config is None):
            raise ValueError(
                f"{config_name} information must be provided in a {CONFIGs_Structure_types[config_name]} to the configration of the optimizer, so it can be used in every evaluation")
        else:
            setattr(self, config_name, config)
            # if isinstance(config,list):
            #     getattr(self, config_name) =[val for val in config ]

            # else:
            #     getattr(self, config_name) = deepcopy(config)

    def set_random_seed(self, seed: int):
        self.random_seed = seed

    def evaluate(self, params):
        """Cost using euclidean distance, parameter set are fed to the Cellmodel then cell measurments are done to be compared with model exprimental measurements.
        """
        # self.simulator = Simulator(
        #     self.model_meta_data["model_type"], self.model_meta_data["model_file"], self.model_meta_data["model_name"])
        if len(params) != len(self.parameters_info):
            raise ValueError(
                "indivedual size is not equal to request parameters size")
        for i in range(len(self.parameters_info)):
            self.parameters_info[i]["value"] = params[i]
            # print(self.parameters_info[i]["value"])

        self.simulator.set_model_parameters(self.parameters_info)
        simulator_measurements = self.simulator.get_measurements(
            self.stimulation_protocol, list(self.experimental_data.keys()))
        errors = []
        for measurement in list(self.experimental_data.keys()):
            if self.experimental_data[measurement]["std"] is not None:
                errors.append(abs(self.experimental_data[measurement]["mean"] -
                                  simulator_measurements[measurement])/self.experimental_data[measurement]["std"])
            else:
                errors.append(abs(self.experimental_data[measurement]["mean"] -
                                  simulator_measurements[measurement])/self.experimental_data[measurement]["mean"])

        return errors

    def optimize(self,callbacks = None ,save_last=False ,plot=False):

        # The parent and offspring population size are set the same
        MU = self.offspring_size
        LAMBDA = self.offspring_size
        # ALPHA = POP_SIZE

        # Crossover probability
        CXPB = 1 - self.mutation_probability
        # Mutation probability, should sum to one together with CXPB
        MUTPB = self.mutation_probability

        # Eta parameter of cx and mut operators
        ETA = 10.0
        IND_SIZE = len(self.parameters_info)

        LOWER = [float(param["low"]) for param in self.parameters_info]
        UPPER = [float(param["high"]) for param in self.parameters_info]
        OBJ_SIZE = len(self.experimental_data)
        # weights = [-1.0] * OBJ_SIZE
        weights = [-1.0*objective["weight"]
                   for objective in self.experimental_data.values()]
        creator.create("Fitness", base.Fitness, weights=weights)
        creator.create("Individual", Individual, fitness=creator.Fitness)

        self.toolbox = base.Toolbox()
        self.toolbox.register("uniformparams", uniform, LOWER, UPPER, IND_SIZE)
        self.toolbox.register(
            "Individual",
            tools.initIterate,
            creator.Individual,
            self.toolbox.uniformparams)
        self.toolbox.register(
            "population",
            deap.tools.initRepeat,
            list,
            self.toolbox.Individual)
        self.toolbox.register("evaluate", self.evaluate)

        self.toolbox.register(
            "mate",
            deap.tools.cxSimulatedBinaryBounded,
            eta=ETA,
            low=LOWER,
            up=UPPER)
        self.toolbox.register("mutate", deap.tools.mutPolynomialBounded, eta=ETA,
                              low=LOWER, up=UPPER, indpb=0.1)

        self.toolbox.register("variate", deap.algorithms.varAnd)

        if not plot:
            self.toolbox.register(
                "select",
                tools.selNSGA2)
        else:
            self.toolbox.register(
                "select", selector=tools.selNSGA2)

        pop = self.toolbox.population(n=MU)

        # first_stats = tools.Statistics(key=lambda ind: ind.fitness.values[0])
        # second_stats = tools.Statistics(key=lambda ind: ind.fitness.values[1])
        # third_stats = tools.Statistics(key=lambda ind: ind.fitness.values[2])
        # fourth_stats = tools.Statistics(key=lambda ind: ind.fitness.values[3])
        # fifth_stats = tools.Statistics(key=lambda ind: ind.fitness.values[4])
        # sixth_stats = tools.Statistics(key=lambda ind: ind.fitness.values[5])
        # seventh_stats = tools.Statistics(key=lambda ind: ind.fitness.values[6])
        # stats = tools.MultiStatistics(Spikecount=first_stats, time_to_first_spike=second_stats, AP_amplitude=third_stats, AP_height=fourth_stats,
        #                               APWidth=fifth_stats, AHP_depth_abs=sixth_stats, AHP_time_from_peak=seventh_stats)

        stats_list = [tools.Statistics(
            key=lambda ind: ind.fitness.values[i]) for i in range(OBJ_SIZE)]
        total_error = tools.Statistics(key=lambda ind: sum(
            [ind.fitness.values[i] for i in range(OBJ_SIZE)]))
        stats_dict = dict(zip(list(self.experimental_data.keys()), stats_list))
        stats_dict["Total_error"] = total_error
        stats = tools.MultiStatistics(**stats_dict)

        # print(stats_dict)

        stats.register("min_error", np.min, axis=0)
        # stats.register("avg", np.mean)
        # stats.register("std", np.std)
        # stats.register("max", np.max)
        pop, logbook = eaMuPlusLambda(
            pop,
            self.toolbox,
            MU,
            LAMBDA,
            CXPB,
            MUTPB,
            self.N_generations,
            stats,
            halloffame=None, verbose=False, callbacks=callbacks)
        if save_last:
            with open("last_generation_pop.obj", "wb") as gen_file:
                pickle.dump(pop, gen_file)
            with open("last_generation_logStats.obj", "wb") as logbook_file:
                pickle.dump(logbook, logbook_file)

        self.pop, self.logbook = pop, logbook

        pop.sort(key=lambda ind: sum(self.evaluate(ind)))
        # pop = sorted(pop,key=lambda ind: ind.total_indivedual_error)
        print("@@@@@@@@@@@@@@@@@@@@@")
        i = 0
        for ind in pop:
            print(ind)
            error = self.evaluate(ind)
            print(f"individual {i}   error is {error} ")
            print(f"and Total error =  {sum(error)}")
            i += 1
            print("########################")
        self.min_errors_across_gens = logbook.chapters["Total_error"].select("min_error")
        # self.plot_convergence()
        # self.get_results(pop)
        
        return pop, logbook

    def get_results(self, population):
        best_solution = population[0]
        self.best_solution = [[param["location"], param["name"], str(
            best_solution[i])] for i, param in enumerate(self.parameters_info)]

        best_solution_errors = self.evaluate(best_solution)
        self.best_solution_errors = [  [objective, str(round(best_solution_errors[i],5))] for i,objective in enumerate(self.experimental_data.keys()) ]

        self.total_error = [ "Total Error", str(round(sum(best_solution_errors),5))  ]
        self.best_solution_errors.append(self.total_error)
        print(self.best_solution_errors)
        return self.best_solution , self.best_solution_errors


    def save_results(self,protocol:dict, results: list,file_name="results.json"):
        a_file = open("results.json", "w")
        json.dump(protocol, a_file)
        a_file.write("\n\n")
        json.dump(results, a_file)
        a_file.close()

    def plot_convergence(self):
        plt.plot(self.min_errors_across_gens,color="red",label ="population minimum")
        plt.xlabel('# Generations')
        plt.ylabel('Total Error')
        plt.legend()
        plt.savefig("convergance.png")


def gen(generation=None):
    print(generation)
    


class Individual(list):
    def __init__(self, *args):
        list.__init__(self, *args)
        self.measurements = None
        self.measurements_error = None
        self.total_indivedual_error = None


def uniform(lower_list, upper_list, dimensions):
    """Fill array from uniform distribution  """

    if hasattr(lower_list, '__iter__'):
        return [np.random.uniform(lower, upper) for lower, upper in
                zip(lower_list, upper_list)]
    else:
        return [np.random.uniform(lower_list, upper_list)
                for _ in range(dimensions)]


if __name__ == '__main__':

    print("start Time =",  datetime.now().strftime("%H:%M:%S"))
    optimizer = Nsga2Optimizer()
    config = {
        "Optimizer": {"Random Seed": 1, "Population Size": 4, "Number of Generations": 3,
                      "Offspring Size": 4, "Mutation Probability": 0.3},
        # ---------------------------------------------------------------------------- #
        "stimulation_protocol": {"Protocol Name": "IClamp", "Stimulus Type": "Step", "Amplitude": 21, "Delay": 150, "Duration": 1,
                                 "Stimulus Section": "iseg", "Stimulus Position": 0.5, "Param": "V", "Recording Section": "soma", "Recording Position": 0.5, "Vinit": -65, "T stop": 500},
        # ---------------------------------------------------------------------------- #
        "model_meta_data": {"model_type": "Nmodel", "model_file": "5CompMy_temp.hoc", "model_name": "fivecompMy"},
        # ----------------------------------parameters_info must be list of dicts---------------------------------- #
        "parameters_info": [{"location": "soma", "name": "gnabar_NafSmb1", "value": 0.0, "low": 0.0, "high": 1.0},
                            {"location": "soma", "name": "gkdrbar_KdrSmb1",
                                "value": 0.0, "low": 0.0, "high": 1.0},
                            {"location": "soma", "name": "gcanbar_CaSmb1",
                                "value": 0.0, "low": 0.0, "high": 1.0}
                            ],
        # ---------------------------------experimental_data must be OrderedDict-------------------------------------- #
        "experimental_data": OrderedDict({"AP Height": {"weight": 1.0, "mean": 80.5, "std": None},
                                          "AP Width": {"weight": 1.0, "mean": 0.8, "std": None}
                                          })

    }
    import threading
    optimizer.setup(config)
    # t1 = threading.Thread(target=optimizer.optimize, args=())
    pop, logbook = optimizer.optimize(plot=False)
    parameters, _  =optimizer.get_results(pop)
    optimizer.save_results(optimizer.stimulation_protocol,parameters )
    # t1.start()
    # for i in range(50):
    #     print("x"*i)
    # t1.join()

    # print(pop)
    # print(logbook)
    # i = 0
    # pop.sort(key=lambda ind: ind.total_indivedual_error)
    # for ind in pop:
    #     print(ind)
    #     print(f"individual {i} Total error =  {ind.total_indivedual_error}")
    #     i += 1
    #     # print(ind.total_indivedual_error)
    # errors = map(lambda ind: ind.total_indivedual_error, pop)
    # best_sol_idx = np.argmin(errors)
    # print("best solution is   ", pop[best_sol_idx], )
    # print("with errors :   ", list(
    #     map(lambda ind: ind.measurements_error, pop))[best_sol_idx], )
    # print(f"with total error {list(errors)[best_sol_idx]}")
    # print("end Time =",  datetime.now().strftime("%H:%M:%S"))
