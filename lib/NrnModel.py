import pprint
from collections import OrderedDict

import matplotlib.pyplot as plt
from neuron import h
from neuron.units import ms, mV

from lib.Model import Model

PRINTING = False



class NrnModel(Model):
    GLOBAL_PARAMS = [""]  #i.e accessed by h.param
    def __init__(self, model_file: str, model_name: str):
        Model.__init__(self,model_file)
        if model_name is None:
            raise ValueError(
                "You Must give the model name in the Nmodel template")
        self.compartments_dict = None
        self.compartments_list = None
        self.channels = None
        self.model_parameters = None
        self.model_name = None
        self._setup(model_file, model_name)

    def _setup(self, model_file: str, model_name: str = None):
        """loading the model hoc file, updates self.compartments_dict ,self.compartments_list """
        # loading the cell

        if model_name is None:
            raise ValueError("Model name must be passed")
        h.load_file(model_file)    # with no h current
        self.model_name = model_name
        try:
            self.cell = getattr(h, model_name)()
        except:
            raise ValueError(
                "The given model name doesn't match the one given in model template file")

        # topology = self.cell.wholetree()
        self.compartments_dict = self.get_all_compartments()
        self.compartments_list = list(self.compartments_dict.values())
        # print(list(self.compartment_dict.keys()))
        # print(self.compartments_list[0].wholetree())

    

    def GetParameters(self, printing=PRINTING):
        """ Returns model parameters dictionary with the following format:
        {
            {key=section_name :value= {key= 'morphology': value= {paramVame: paramValue ,.:.,.:.,.:.} ,
                                      key = 'density_mechs': value = {key=channel_name , value = {paramVame: paramValue ,.:.,.:.,.:.}}}
        }
        """
        topology = h.allsec()
        pp = pprint.PrettyPrinter()
        modelParams = []
        for section in topology:
            modelParams.append(section.psection())
            # print(type(section.psection()))

        params = OrderedDict()
        # params = {}
        for sec in modelParams:
            # for every section in the cell create a key with section name, with value equal to a dictionary
            params[str(sec.get("name"))] = {}

            params[str(sec.get("name"))]['morphology'] = sec.get("morphology")
            unwanted_morphology_info = ["pts3d", "parent", "trueparent"]
            for info in unwanted_morphology_info:
                params[str(sec.get("name"))]['morphology'].pop(info, None)

            params[str(sec.get("name"))]['density_mechs'] = {}
            params[str(sec.get("name"))]['density_mechs'] = sec.get(
                "density_mechs")
        if printing:
            pprint.PrettyPrinter().pprint(params)

        self.model_parameters = params
        return self.model_parameters

    def get_model_parameters(self, printing=PRINTING):
        """
        Collects every member of every section object and filters out those that are not parameters of
        the model. The function will collect:
            * every parameter of the the mechanisms
            * every mechanism
            * some default parameters that are always included in a model,
              and pointprocesses that are not some sort of Clamp
        :return: the filtered content of the model in a string matrix
        """

        parameters = []
        temp = []
        parname = []
        mechs_pars = []
        DEFAULTS = []
        seg_num = 0

        for sec in h.allsec():
            temp.append(str(h.secname(sec=sec)))

            DEFAULTS = ["morphology", ["L", "cm", "Ra", "diam"]]
            mechs_pars.append(DEFAULTS)
            for seg in sec:

                for mech in seg:

                    # i+=1
                    h('strdef mtname, msname')
                    h('mtname=" "')
                    h('objref mechs')
                    h.mtname = mech.name()
                    h('mechs=new MechanismStandard(mtname)')
                    h('k = mechs.count()')
                    parnum = int(h.k)
                    h('j=0')
                    for j in range(parnum):
                        h.j = j
                        h('k = mechs.name(msname, j)')
                        parname.append(h.msname)
                    mechs_pars.append([mech.name(), parname])
                    # mechs_pars.append(parname)
                    parname = []
                seg_num += 1

                temp.append(mechs_pars)
            mechs_pars = []
            # temp.append(channels)
            seg_num = 0
            parameters.append(temp)

            temp = []

        if printing:
            pprint.PrettyPrinter().pprint(parameters)
        self.model_parameters = parameters
        return parameters

    def get_compartments_channels(self, printing=PRINTING):
        """Returns the available channels for each compartement and updates self.channels"""
        channels = OrderedDict()
        for sec in h.allsec():
            channels[str(sec.name())] = []
        for sec in h.allsec():
            for seg in sec:
                for mech in seg:
                    channels[str(sec.name())] += [str(mech.name())]
        if printing:
            pp = pprint.PrettyPrinter()
            pp.pprint(channels)
        self.channels = channels
        return channels

    def get_all_compartments(self) -> OrderedDict:
        sections = OrderedDict()
        for section in h.allsec():
            sections[str(h.secname(sec=section))] = section
        return sections

    def get_compartement(self, compartement: str):
        if len(compartement.split('.')) == 1:
            # in case of input was soma instead of fivecompMy[0].soma
            compartement = self._get_model_name() + "." + compartement
        return self.compartments_dict.get(compartement)

    def set_parameter(self,section_name: str, parameter_name: str , value: float):
        """
        set_parameter [summary]

        Parameters
        ----------
        section_name : str
            [description]
        parameter_type : str
            [description]
        parameter_name : str
            [description]
        value : float
            [description]
        """
        section = self.get_compartement(section_name)
        if section_name == "GLOBAL" :
            #example h.th_NafSmb1
            setattr(h,parameter_name,value)
            
        else:
            setattr(section,parameter_name,value)
            


    def _get_model_name(self) -> str:
        return list(self.compartments_dict.keys())[0].split(".")[0]

    def setIClamp(self, delay, duration, amp, segment, position):
        """Add a current clamp at {position} of {segment}"""
       
        stim = h.IClamp(segment(position))
        stim.delay = delay           # ms
        stim.dur = duration        # ms
        stim.amp = amp             # nA
        return stim

    def recordVolt(self, segmentToRecord, position):

        # set up a recording vector and record voltage at {position} of {segment}
        segment_v = h.Vector().record(segmentToRecord(position)._ref_v)

        segment_t = h.Vector().record(h._ref_t)  # record time.
        return segment_v, segment_t

    def runControler(self, TStop, init=-65):
        h.load_file('stdrun.hoc')
        h.finitialize(init * mV)
        h.continuerun(TStop * ms)
        # print(list(self.soma_v))
    
    def stimulateCell(self, clampAmp, duration, delay, Tstop,stimSeg,recordSec="soma", clampAt=0.5,recordAt =0.5 , init=-65):
        """ Stimulate the cell with the supplied properties
            Args:
            :param clampAmp: the current value at which the cell is stimulated (in nA)
            :param duration: the time for which the stimulation is continued
            :param delay: the time at which the stimulation is started
            :param stimSeg: the segment at which the cell is stimulated
            :param clampAt: the location in the segment at which clamp is inserted
            :param Tstop: the duration for which the recording is done
            :param init: the resting membrane voltage of the cell

        :return volt: the recorded voltage vector
        :return t: the recorded time vector

         """
        
        stim = self.setIClamp(delay, duration, clampAmp,
                              segment=self.get_compartement(stimSeg), position=clampAt)
        volt, t = self.recordVolt(self.get_compartement(recordSec), recordAt)
        self.runControler(TStop=Tstop, init=-65)
        return volt, t

    def __repr__(self):
        return f"Model  {self.model_name} with Kinetecs \n {list(self.get_all_compartments().keys())} \n  \n And  with parameters: \n {self.get_model_parameters()}  "
    def set_test(self):
        section = self.get_compartement("soma")
        print(section)
        setattr(section,"g_pas",0.005)
        print(section.g_pas)

if __name__ == '__main__':
    from hoc2swc import hoc2swc

    # hoc2swc("5CompMy_temp.hoc", "out.swc")
    model = NrnModel("5CompMy_temp.hoc", "fivecompMy")
    print(model.get_compartement("soma"))
    # model.get_model_parameters()
    # model.get_compartments_channels(printing=False)
    # print(model.get_model_parameters(printing=False)[
    #       "fivecompMy[0].soma"]["morphology"]['diam'][0])
    pp = pprint.PrettyPrinter()
    # pp.pprint(model)
    # print(model.get_compartement("soma"))
    # pp = pprint.PrettyPrinter()
    # for seg in model.compartments_list[0]:
    #     print(type(seg.NafSmb1_amA))
    # print(model.compartments_list[0][0].pas.g)
    # pp.pprint(h.shape())
    # print(model.cell.soma.g_pas)
