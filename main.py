# This Python file uses the following encoding: utf-8
import os
from pathlib import Path
import sys

from PySide2.QtGui import QGuiApplication
from PySide2.QtQml import QQmlApplicationEngine
from PySide2.QtCore import QObject, Slot, Signal
import json
from collections import OrderedDict

from lib.Fitter import Fitter


class MainWindow(QObject):
    def __init__(self):
        QObject.__init__(self)

        self.fitter = None
        self.sections = []
        self.paramList = {'element1': "Soma", 'element2': "pas"}

        self.paramCheck = {
            "indexParam": 1,
            "sectionParam": "Soma",
            "nameParam": "CaSmb1"
        }

        self.resParam = {
            "element1": "Soma",
            "element2": "pas",
            "element3": "0.63541"
        }

        self.resFit = {
            "element1": "Soma",
            "element2": "0.63541"
        }

        self.updated = 0
        self.updatedSections = 0

        self.OptimizerSettings = {
            "Random Seed": 1,
            "Population Size": 2,
            "Number of Generations": 10,
            "Offspring Size": 2,
            "Mutation Probability": 0.3
        }

        self.sigSettings = {
            "Protocol Name": "IClamp",
            "Stimulus Type": "Step",
            "Amplitude": 21,
            "Delay": 150,
            "Duration": 1,
            "Stimulus Section": "iseg",
            "Stimulus Position": 0.5,
            "Param": "V",
            "Recording Section": "soma",
            "Recording Position": 0.5,
            "Vinit": -65,
            "T stop": 500
        }

        self.parameters_info = []

        self.experimental_data = {}

        self.config = {
            "Optimizer": {
                "Random Seed": 1,
                "Population Size": 100,
                "Number of Generations": 50,
                "Offspring Size": 100,
                "Mutation Probability": 0.3
            },
            # ---------------------------------------------------------------------------- #
            "stimulation_protocol": {
                "Protocol Name": "IClamp",
                "Stimulus Type": "Step",
                "Amplitude": 21,
                "Delay": 150,
                "Duration": 1,
                "Stimulus Section": "iseg",
                "Stimulus Position": 0.5,
                "Param": "V",
                "Recording Section": "soma",
                "Recording Position": 0.5,
                "Vinit": -65,
                "T stop": 500
            },
            # ---------------------------------------------------------------------------- #
            "model_meta_data": {
                "model_type": "Nmodel",
                "model_file": "5CompMy_temp.hoc",
                "model_name": "fivecompMy"
            },
            # ----------------------------------parameters_info must be list of dicts---------------------------------- #
            "parameters_info": [{
                "location": "soma",
                "name": "gnabar_NafSmb1",
                "value": 0.0,
                "low": 0.0,
                "high": 1.0
            }, {
                "location": "soma",
                "name": "gkdrbar_KdrSmb1",
                "value": 0.0,
                "low": 0.0,
                "high": 1.0
            }, {
                "location": "soma",
                "name": "gcanbar_CaSmb1",
                "value": 0.0,
                "low": 0.0,
                "high": 1.0
            }],
            # ---------------------------------experimental_data must be OrderedDict-------------------------------------- #
            "experimental_data":
            OrderedDict({
                "AP Height": {
                    "weight": 1.0,
                    "mean": 80.5,
                    "std": None
                },
                "AP Width": {
                    "weight": 1.0,
                    "mean": 0.8,
                    "std": None
                }
            })
        }
        self.ModelPath = "C:/Users/pc/Download/"
        self.ModelName = "fiveCompModel"

    # Signal
    appHomeBuffer = Signal(str)
    appTuningBuffer = Signal(str)
    appResultBufferParam = Signal(str)
    appResultBufferFitness = Signal(str)
    getText = Signal(str)
    getParam = Signal(str)
    enableTune = Signal()
    pushRes = Signal()
    pushWait = Signal()

    # Function
    @Slot(str)
    def updateModelPath(self, str):
        self.ModelPath = str
        self.ModelPath = self.ModelPath[8:].split("/")[-1]
        print(self.ModelPath, "---", type(self.ModelPath))

    # Function
    @Slot(str)
    def updateModelName(self, str):
        self.ModelName = str
        print(self.ModelName, "---", type(self.ModelName))

    # Function
    @Slot()
    def fetchModel(self):
        self.fitter = Fitter("Nmodel", self.ModelPath, self.ModelName)
        self.channels = self.fitter.fetch_model_channels()  # gui first page
        for i in list(self.channels.keys()):
            self.sections.append(i.split(".")[-1])
        print(self.sections)    
        for key, val in self.channels.items():
            for i in val:
                self.paramList = {
                    'element1': key.split(".")[-1],
                    'element2': i
                }
                self.appHomeBuffer.emit(json.dumps(self.paramList))
        self.enableTune.emit()

    @Slot()
    def fetchParam(self):
        if (self.updated == 0):
            self.params = self.fitter.fetch_model_parameters()
            i = 1
            for section in self.params:
                for mech in section[1]:
                    if mech[0] != "morphology":
                        for param in mech[1]:
                            self.paramCheck = {
                                "indexParam": i,
                                "sectionParam":
                                section[0].split(".")[-1],
                                "nameParam": param
                            }
                            self.appTuningBuffer.emit(
                                json.dumps(self.paramCheck))
                            i += 1

            self.updated = 1

    @Slot()
    def fetchSections(self):
        return
        if (self.updatedSections == 0):
            self.appTuningBuffer.emit(json.dumps(self.paramCheck))
            self.updatedSections = 1

    # Function
    @Slot()
    def tuneModel(self):
        print("Tuning!!")
        self.pushWait.emit()
        self.config["stimulation_protocol"] = self.sigSettings
        self.config["parameters_info"] = self.parameters_info
        self.config["experimental_data"] = OrderedDict(
            self.experimental_data)
        self.ResParam, self.ResFit = self.fitter.fit(self.config)
        self.sendResults(self.ResParam, self.ResFit)
        self.pushRes.emit()

    # Function
    @Slot(str)
    def sendParamList(self, str):
        self.appHomeBuffer.emit(json.dumps(self.paramList))

    # Function
    @Slot()
    def sendResults(self, bestParams, errors):
        for i in bestParams:
            self.resParam = {
                "element1": i[0],
                "element2": i[1],
                "element3": i[2]
            }
            self.appResultBufferParam.emit(json.dumps(self.resParam))
        
        for i in errors:
            self.resFit = {
                "element1": i[0],
                "element2": i[1]
            }
            self.appResultBufferFitness.emit(json.dumps(self.resFit))

    @Slot()
    def getSigSettings(self):
        self.getText.emit("all")
        print(self.sigSettings)

    @Slot(str, str)
    def recieveOptimizerSetting(self, key, value):
        self.OptimizerSettings[key] = (value if (type(value) == type(self.OptimizerSettings[key])) else float(value))

    @Slot(str, str)
    def recieveSigSettings(self, key, value):
        self.sigSettings[key] = (value if (type(value) == type(self.sigSettings[key])) else float(value))

    @Slot(str, str, str, str)
    def recieveParam(self, key, value, lowerbound, upperbound):
        for i, param in enumerate(self.parameters_info):
            if (param["location"] == key):
                if (param["name"] == value):
                    return
        self.parameters_info.append({
            "location": key,
            "name": value,
            "value": 0.0,
            "low": float(lowerbound),
            "high": float(upperbound)
        })
        print(self.parameters_info)

    @Slot(str, str)
    def removeParam(self, key, value):
        for i, param in enumerate(self.parameters_info):
            if (param["location"] == key):
                if (param["name"] == value):
                    del self.parameters_info[i]
                    return

    @Slot(str, str, str, str)
    def recieveFeature(self, featureName, weight, mean, stddev):
        self.experimental_data[featureName] = {
            "weight": float(weight),
            "mean": float(mean),
            "std": (stddev if stddev != "None" else None)
        }
        print(self.experimental_data)

    @Slot(str)
    def removeFeature(self, featureName):
        del self.experimental_data[featureName]

    @Slot()
    def saveRes(self):
        self.fitter.save_to_file(self.sigSettings, self.ResParam)

if __name__ == "__main__":
    app = QGuiApplication(sys.argv)

    # Get Context
    main = MainWindow()

    engine = QQmlApplicationEngine()
    engine.rootContext().setContextProperty("backend", main)

    # Load QML file
    engine.load(
        os.fspath(Path(__file__).resolve().parent / "qml/main.qml"))

    if not engine.rootObjects():
        sys.exit(-1)
    sys.exit(app.exec_())
