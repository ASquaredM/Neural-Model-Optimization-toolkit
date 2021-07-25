import math
# from xlwt import Workbook
import time
from collections import OrderedDict

import efel
import numpy as np
from neuron import h

from lib.efelMeasurements import EfelMeasurements
from lib.FeatureExtractor import FeatureExtractor
from lib.NrnModel import NrnModel
from lib.Model import Level, Plotter

PLOTTING = False
PRINTING = False
SUPPORTED_MODEL_TYPES = {'Nmodel':NrnModel}


class Simulator():
    def __init__(self, model_type: str, model_file: str, model_name: str):
        if model_type in list(SUPPORTED_MODEL_TYPES.keys()):
            self.model = SUPPORTED_MODEL_TYPES[model_type](model_file, model_name)
        else:
            raise NotImplementedError(
                f"only {list(SUPPORTED_MODEL_TYPES.keys())} are supported")
        self.stimulus_protocol = None
        self.requested_measurments = None

    def fetch_model_parameters(self) -> OrderedDict:
        return self.model.get_model_parameters()

    def fetch_model_channels(self) -> OrderedDict:
        return self.model.get_compartments_channels()

    # list of ordered Dictionary [[location: soma, name: g_pas, value:0.001],  [location, name, value]  ]
    def set_model_parameters(self, parameters: list):
        if (not isinstance(parameters, list)) or (len(parameters) == 0):
            raise ValueError("Parameters to be set must be a list of size > 0")

        if not isinstance(parameters[0], dict):
            raise TypeError(
                "Each parameter must be of type Dict e.g [location: soma, name: g_pas, value:0.001]")
        for parameter in parameters:
            self.model.set_parameter(parameter["location"],parameter["name"],parameter["value"])

    def get_measurements(self, protocol: dict, requested_measurments: list, measurer: str = "efel") -> OrderedDict:
        # TODO: ReFactor the names of theses classes, add rheobase,rin,tau to efel

        self.stimulus_protocol = protocol
        self.requested_measurments = requested_measurments
        
        measurments = OrderedDict.fromkeys(requested_measurments, 0.0)
        Non_AP = ["Input Resistance", "Time Constant", "Rheobase"]
        non_ap_requested_measurments = []
        # print(self.model)
        for feature in requested_measurments:
            if feature in Non_AP:
                
                non_ap_requested_measurments.append(feature)
                requested_measurments.remove(feature)
       
        if len(non_ap_requested_measurments) > 0:
            feature_extractor = FeatureExtractor(self.model, protocol)
            # update the measurements dictionary with non ap measurements
            feature_extractor.get_measurements(
                measurments, non_ap_requested_measurments)
        if len(requested_measurments) > 0:  # get the remaining non_ap features
            if measurer.lower() == "efel":
                feature_extractor = EfelMeasurements(self.model, protocol)
                feature_extractor.get_measurements(
                    measurments, requested_measurments)
            elif measurer.lower() == "spikeanalyzer":
                feature_extractor = FeatureExtractor(self.model, protocol)
                feature_extractor.get_measurements(
                    measurments, requested_measurments)
            else:
                raise ValueError("Thr Requested Measurer is not supported")
        return measurments

if __name__ == '__main__':
    pass
