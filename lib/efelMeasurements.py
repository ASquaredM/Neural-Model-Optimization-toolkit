import math
import warnings
from collections import OrderedDict
from enum import Enum

import efel
import matplotlib.pyplot as plt
import numpy as np

from lib.Model import Model
from lib.NrnModel import NrnModel


class Level(Enum):
    HIGH = 0.5
    MID = 5.0
    LOW = 10.0
    VLOW = 50.0

EFEL_NAME_MAP = {
                 "AP Amplitude": "AP_amplitude",
                 "AP Height": "AP_height",
                 "AP Width": "AP_width",
                 "AHP Absolute Depth": "AHP_depth_abs",
                 "AHP time from peak": "AHP_time_from_peak",
                 "Spike Count": "Spikecount",
                 "Time to First Spike": "time_to_first_spike",
                 }
EFEL2NAME_MAP = {v: k for k, v in EFEL_NAME_MAP.items()}


def _zero_valued_dict(keys):
    return dict.fromkeys(keys, 0)


class EfelMeasurements():
    def __init__(self, model:Model , config: dict):

        self.cell = model
        self.voltage = None
        self.t = None
        self.delay = None
        self.duration = None
        self.current_amplitude = None
        self.Tstop = None
        self.trace = {}
        self._setup(config)

    def _setup(self, config):
        self.voltage, self.t = self.cell.stimulateCell(
            float(config["Amplitude"]), float(
                config["Duration"]), float(config["Delay"]),
            float(
                config["T stop"]), config["Stimulus Section"], config["Recording Section"],
            clampAt=float(config["Stimulus Position"]), recordAt=float(config["Recording Position"]), init=float(config["Vinit"]))
        self.delay = float(config["Delay"])
        self.duration = float(config["Duration"])
        self.Tstop = float(config["T stop"])
        self.current_amplitude = float(config["Amplitude"])
        self._initialize()

    def _initialize(self):
        # start =  sorted(self._closeMatches(self.t,delay,0.025),key=lambda x: x[0])[0][0]
        # end =  sorted(self._closeMatches(self.t,delay+duration,0.025),key=lambda x: x[0])[0][0]
        # print(t[2]-t[1])
        efel.setDoubleSetting('stimulus_current', self.current_amplitude)
        efel.setIntSetting("strict_stiminterval", True)
        self.trace['T'] = self.t
        self.trace['V'] = self.voltage
        # max because delay may be less than 5ms
        self.trace['stim_start'] = [max(self.delay-5, 0)]
        self.trace['stim_end'] = [self.Tstop]

        return self.voltage, self.t

    def get_measurements(self, outputDict: dict,featureNames: list):
        traces = [self.trace]
        efel_feature_names = self._convert_to_efel_names(featureNames)
        warnings.filterwarnings("ignore", category=RuntimeWarning)
        check_peaks = efel.getFeatureValues(traces, ["Spikecount_stimint"])
        if check_peaks[0]["Spikecount_stimint"][0] == 0:
            return _zero_valued_dict(featureNames)

        amplitudes = efel.getFeatureValues(traces, ["AP_amplitude"])
        if (amplitudes[0]["AP_amplitude"] is None):
            # print("efel failed",len(traces_results[0]["AP_amplitude"]) , len(traces_results[0]["AP_height"]))
            print(f"n spikes are {check_peaks[0]['Spikecount_stimint'][0]}")
            return _zero_valued_dict(featureNames)


        traces_results = efel.getFeatureValues(traces, efel_feature_names)
        warnings.filterwarnings("default", category=RuntimeWarning)
        for trace_results in traces_results:
            # trace_result is a dictionary, with as keys the requested eFeatures
            for feature_name, feature_values in trace_results.items():
                if len(feature_values) > 0:
                    outputDict[EFEL2NAME_MAP[feature_name]
                                      ] = np.mean(feature_values)
                else:
                    print(f"{feature_name} failed")
                    print(f"{feature_name} equals {feature_values}")
                    outputDict[EFEL2NAME_MAP[feature_name]] = 0
        if "Time to First Spike" in list(outputDict.keys()):
            if outputDict["Time to First Spike"] !=0:
                outputDict["Time to First Spike"] +=self.delay

        self.measurements = outputDict

        # for name in featureNames:
        #     if name  == "Input Resistance":
        #         self.measurements[name] = self.inputResistance(-0.5,
        #                                                           plotting=False, printing=False)
        #     elif name == "Rheobase":
        #         self.measurements[name] = self.Rheobase(
        #             Level.VLOW, 1, plotting=False, printing=False)
        #     elif name == "Time Constant":
        #         self.measurements[name] = self.timeConstant(
        #             -0.5, plotting=False, printing=False)
        return self.measurements

    def _closeMatches(self, lst: list, findVal, tolerance):
        """ find a list of closest matches to a specific value with a spicified tolerance
            Args:
                :param lst: target list to search into
                :param findVal: target value
                :param tolerance: accepted error in matches
            :return: list of (value,index) pairs
        """
        # matches = [(val,index) for index,val in enumerate(lst) if abs(val - findVal) < tolerance]
        matches = [(val, index) for index, val in enumerate(lst)
                   if math.isclose(val, findVal, abs_tol=tolerance)]

        return matches

    def _convert_to_efel_names(self, regular_feature_names: list):
        efel_feature_names = []
        for fName in regular_feature_names:
            if fName not in list(EFEL_NAME_MAP.keys()):
                raise ValueError(
                    f" Feature: '{fName}' is not availabe in Efel or not spelled well")
            efel_feature_names.append(EFEL_NAME_MAP[fName])
        return efel_feature_names


if __name__ == '__main__':

    fig, ax = plt.subplots()
    for i in range(1):
        delay = 150  # 150
        duration = 1
        current = 21
        efel.setDoubleSetting('stimulus_current', current)
        # efel.setDoubleSetting('interp_step', 0.025)
        # efel.setIntSetting("strict_stiminterval", True)

        testEFEL = EfelMeasurements()
        testEFEL.stimulateCell(current, duration, delay,
                               testEFEL.iseg, 0.5, 500)
        testEFEL.get_measurements(["Spikecount", "time_to_first_spike", "AP_amplitude",
                                   "AP_height", 'AP_width', 'AHP_depth_abs', "AHP_time_from_peak"])

        testEFEL.model.graphVolt(
            testEFEL.voltage, testEFEL.t, "trace", ax, color=np.random.rand(3,))
        # ax.set_color("red")
    plt.show()
