from collections import OrderedDict

from lib.MultiObectiveDeap import Nsga2Optimizer
from lib.Simulator import Simulator

AVAILABE_OPTIMIZERS = {"NSGA2": Nsga2Optimizer}


class Fitter:
    def __init__(self, model_type: str, model_file: str, model_name: str, **kwargs):
        self.model_meta_data = None
        self.simulator = None
        self.optimizer = None
        self.requested_measurments = None
        self.stimulation_protocol = None
        self.parameters_info = None
        self.experimental_data = OrderedDict()  # measurement_name: weight, mean, std
        self.target_parameters = OrderedDict()  # param_name : range

        self._initialize_simulator(model_type, model_file, model_name)

    def _save_model_metaData(self, model_type, model_file, model_name):
        keys = ["model_type", "model_file", "model_name"]
        vals = [model_type, model_file, model_name]
        self.model_meta_data = dict(zip(keys, vals))

    def _initialize_simulator(self, model_type, model_file, model_name):
        """Initializes the simulator with the given model configuration."""
        self.simulator = Simulator(model_type, model_file, model_name)

    def fetch_model_parameters(self) -> list:
        """Returns an OrderedDictionary with keys= compartments  name , values= dictionary of each channel and their corresponding parameters as strings
            usually parameters are channel conductances.
        """
        if self.simulator is None:
            raise ValueError("Simulator is not initialized")
        return self.simulator.fetch_model_parameters()

    def fetch_model_channels(self) -> OrderedDict:
        """Returns an OrderedDictionary with keys= compartments  name , values= list of inserted channels"""
        if self.simulator is None:
            raise ValueError("Simulator is not initialized")
        return self.simulator.fetch_model_channels()

    def fit(self, config: dict, measurer_type: str = "efel", optimizer_type: str = "NSGA2", **kwargs):  # TODO: ask about parallism
        self.optimizer = AVAILABE_OPTIMIZERS[optimizer_type]()

        self.stimulation_protocol = config.get("stimulation_protocol", None)
        """Format:  {"Protocol Name": "IClamp دروب داون", "Stimulus Type":"Step دروب داون" , "Amplitude":"21" ,"Delay":"150", "Duration":"3", 
        "Stimulus Section":"Iseg دروب داون","Stimulus Position":"0.5" ,"Param":"V دروب", "Recording Section":"Soma دروب د","Recording Position":"0.5", "Vinit":"-65", "T stop":"500"}
        """
        if self.stimulation_protocol is None:
            raise ValueError("stimulation protocol is not provided")

        self.experimental_data = config.get("experimental_data", None)
        """Format: OrderedDict--> {   "AP_height":{"weight":-1,"mean":12,"std":12}, "spikeCount":{"weight":-1,"mean":2,"std":1}     }"""
        if self.experimental_data is None:
            raise ValueError("Experimental data is not provided")

        self.optimizer.setup(config)
        pop,logbook = self.optimizer.optimize()
        self.best_params , self.best_errors = self.optimizer.get_results(pop)
        self.optimizer.plot_convergence()
        return self.best_params , self.best_errors

    def save_to_file(self,protocol:dict, results: list,file_name="results.json"):
        self.optimizer.save_results(protocol,results,file_name)



if __name__ == '__main__':
    fitter = Fitter("Nmodel", "5CompMy_temp.hoc", "fivecompMy")
    channels = fitter.fetch_model_channels()  # gui first page
    # gui second page, need to be parsed in the upper layer
    params = fitter.fetch_model_parameters()
    config = {
        "Optimizer": {"Random Seed": 1, "Population Size": 2, "Number of Generations": 2,
                      "Offspring Size": 2, "Mutation Probability": 0.3},
        # ---------------------------------------------------------------------------- #
        "stimulation_protocol": {"Protocol Name": "IClamp", "Stimulus Type": "Step", "Amplitude": 21, "Delay": 150, "Duration": 1,
                                 "Stimulus Section": "iseg", "Stimulus Position": 0.5, "Param": "V", "Recording Section": "soma", "Recording Position": 0.5, "Vinit": -65, "T stop": 500},
        # ---------------------------------------------------------------------------- #
        "model_meta_data": {"model_type": "Nmodel", "model_file": "5CompMy_temp.hoc", "model_name": "fivecompMy"},
        # ----------------------------------parameters_info must be list of dicts---------------------------------- #
        "parameters_info": [ {"location": "soma", "name":"gnabar_NafSmb1","value":0.0,"low":0.0,"high":1.0},
        {"location": "soma", "name":"gkdrbar_KdrSmb1","value":0.0,"low":0.0,"high":1.0},
        {"location": "soma", "name":"gcanbar_CaSmb1","value":0.0,"low":0.0,"high":1.0} 
                            ],
        # ---------------------------------experimental_data must be OrderedDict-------------------------------------- #
        "experimental_data":OrderedDict ({"Rheobase":{"weight":1.0,"mean": 7.88,"std":None},
                              "AP Width":{"weight":1.0,"mean":0.8,"std":None}  
                            })

    }
    fitter.fit(config)
    # print(len(params))
    # conductances = []
    # i=0
    # for  section in params:
    #     # print(section[0])
    #     # print(section[1])
    #     for mech in section[1]: 
    #         if mech[0] != "morphology":
    #             for param in mech[1]:
    #                 conductances.append([i,section[0].split(".")[-1] , param])
    #                 i+=1
        
    # print(conductances)

    def get_list_of_parameters(params):
        conductances = []
        i=0
        for  section in params:
            # print(section[0])
            # print(section[1])
            for mech in section[1]: 
                if mech[0] != "morphology":
                    for param in mech[1]:
                        conductances.append([i,section[0].split(".")[-1] , param])
                        i+=1
        return conductances
    

    print(get_list_of_parameters(params))
