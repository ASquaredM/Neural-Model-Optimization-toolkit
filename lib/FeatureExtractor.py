import math
from collections import OrderedDict
from enum import Enum

import numpy as np

from lib.Model import Plotter

PLOTTING = False
PRINTING = False


class Level(Enum):
    HIGH = 0.5
    MID = 5.0
    LOW = 10.0
    VLOW = 50.0


NAME_MAP = {"Input Resistance": "inputResistance",
            "Average Input Resistance": "avgInRes",
            "Time Constant": "timeConstant",
            "Rheobase": "Rheobase",
            "AP Amplitude": "APHeight",
            "AP Width": "APWidth",
            "AHP Depth": "AHPDepth",
            "AHP Duration": "AHPDuration",
            "AHP Half Duration": "AHPHalfDuration",
            "AHP Half Decay": "AHPHalfDecay",
            "AHP Rising Time": "AHPRisingTime",
}


class FeatureExtractor:
    def __init__(self, model,config):
        self.cell = model
        self.voltage = None
        self.t = None
        self.delay = None
        self.duration = None
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
        

    def inputResistance(self, amp, plotting: bool = PLOTTING, printing: bool = PRINTING):
        """ Measures the input resistance
            Args:
                :param amp: current amplitude used to stimulate the cell
                :param plotting: Boolean used to toggle plotting on and off
                :param printing: Boolean used to toggle printing on and off
            :return inputResistance: input Resistance


        """
        delay = 150
        duration = 100
        volt, t = self.cell.stimulateCell(
            amp, duration, delay, 500, "soma", "soma", clampAt=0.5, recordAt=0.5, init=-65)

        # TODO: slice the time interval of the stimulas and get the plateau volts
        # ::DONE::
        slicedVolt, slicedT = self.sliceSpikeGraph(
            volt, t, delay - 10, delay + duration + 10)

        restMembPot = max(slicedVolt)  # Should be around -65 mv
        minDepolarPot = min(slicedVolt)

        # should it always be positive  ??
        inputResistance = abs((restMembPot - minDepolarPot)/amp)
        # print(self.soma.psection())

        if printing:
            print("----- Input Resistance Measurement -----")
            print(f'clamp Current: {amp} nA')
            print(f'restMembPot: {restMembPot} mV')
            print(f'minDepolarPot: {minDepolarPot} mV')
            print(f'inputResistance: {inputResistance} (mV/nA)')
            print("----- ---------------------------- -----")
            # self.xlSheet.write(1,0,"Input Resistance")
            # self.xlSheetWriteRows("Input Resistance")
            # self.xlSheetWriteCols(inputResistance)

        if plotting:
            # TODO: overlay plots , plot full graph and the sliced with diff color ,  and mark points on the graph
            # ::DONE::
            plt = Plotter.graphOverlap(
                volt, t, 'k', 'Full Spike', 0.8, slicedVolt, slicedT, 'g', 'Sliced spike', 1.0, 'input Resistance')
            plt.show()
        return inputResistance

    def avgInRes(self, sampleAmps, plotting: bool = PLOTTING, printing: bool = PRINTING):
        """ Measures the average input resistance over many samples
            Args:
                :param sampleAmps: List of current amplitudes used to stimulate the cell
                :param plotting: Boolean used to toggle plotting on and off
                :param printing: Boolean used to toggle printing on and off
            :return avgInRes: average input Resistance


        """
        inputRes = [self.inputResistance(
            amp, plotting=plotting, printing=printing) for amp in sampleAmps]
        avgInRes = sum(inputRes)/len(inputRes)

        if printing:
            print("----- Averaged Input Resistance  -----\n")
            # print(f'inputRes List: \n{inputRes}\n')
            print(f'avgInRes: {avgInRes} (mV/nA)')
            print("----- ---------------------------- -----\n")

        return avgInRes

    def timeConstant(self, amp, plotting: bool = PLOTTING, printing: bool = PRINTING):
        """ Measures the time constant
            Args:
                :param amp: List of current amplitudes used to stimulate the cell
                :param plotting: Boolean used to toggle plotting on and off
                :param printing: Boolean used to toggle printing on and off

            :return tC: time constant
        """
        delay = 150
        duration = 100
        volt, t = self.cell.stimulateCell(
            amp, duration, delay, 500, "soma", "soma", clampAt=0.5, recordAt=0.5, init=-65)
        tStart = delay + duration
        # TODO: make a function that detects stable intervales and use it in time constant function
        tEnd = delay + duration + 30

        slicedVolt, slicedTime = self.sliceSpikeGraph(volt, t, tStart, tEnd)
        # slicedVolt, slicedTime,plt = self.patternHighligher(volt,t,tStart,duration,plotting = True)

        vStart = slicedVolt[0]
        vEnd = slicedVolt[-1]
        tC = -(tEnd - tStart) / math.log(1 - (vEnd/vStart))

        if printing:
            print(f'Time Constant: {tC}')
            # print(f'vStart: {vStart}')
            # print(f'vEnd: {vEnd}')
            # print(f'tStart: {tStart}')
            # print(f'tEnd: {tEnd}')
        if plotting:
            plt = Plotter.graphOverlap(volt, t, 'k', 'Full Spike', 0.8,
                                       slicedVolt, slicedTime, 'g', 'Sliced spike', 1.0, 'Time Constant')
            # Plotter.graphMarker(plt,tStart,vStart,'start Point')
            plt.show()
        return tC

    def APHeight(self, voltVec, timeVec, delay, duration, plotting: bool = PLOTTING, printing: bool = PRINTING):
        """ measures the AP Height of the spike
            Args:
                :param voltVec: recoreded vector of the spike voltage
                :param timeVec: recoreded vector of the spike time
                :param delay: the time at which the cell is stimulated
                :param duration: the time for which the stimulation is continued
                :param plotting: Boolean used to toggle plotting on and off
                :param printing: Boolean used to toggle printing on and off

            :return apHeight: the Height of the spike in milliVolts

            :return apRest: the resting potential in milliVolts

            :return apPeak: the peak potential in milliVolts

        """
        if(not(self.isSpike(voltVec, timeVec, delay, duration, Level.HIGH, plotting))):
            if printing:
                print("No spike detected")
            return 0, 0, 0
        volt, time = self.sliceSpikeGraph(voltVec, timeVec, delay, delay + 10)
        # get peak point
        vPeak = max(volt)
        indexPeak = volt.index(vPeak)
        TPeak = time[indexPeak]
        # get restng point
        vRest = volt[0]
        indexVRest = volt.index(vRest)
        tRest = time[indexVRest]
        apHeight = abs(vPeak - vRest)

        if printing:
            print(f'apHeight: {apHeight} mV')

        if plotting:
            plt = Plotter.graphOverlap(voltVec, timeVec, 'k', 'Full AP', 0.8,
                                       volt, time, 'g', 'AP Spike', 1.0, 'AP Height')

            Plotter.graphMarker(plt, TPeak, vPeak, 'AP Peak', 'x')
            Plotter.graphMarker(plt, tRest, vRest, 'AP Resting', 'x')

        return apHeight, vRest, vPeak

    def APWidth(self, voltVec, timeVec, delay, duration, plotting: bool = PLOTTING, printing: bool = PRINTING):
        # FIXME: matches aren't on the same level , but close enough ... (works for me)
        """ measures the AP width of the spike

                :param voltVec: recoreded vector of the spike voltage
                :param timeVec: recoreded vector of the spike time
                :param delay: the time at which the cell is stimulated
                :param duration: the time for which the stimulation is continued
                :param plotting: Boolean used to toggle plotting on and off
                :param printing: Boolean used to toggle printing on and off

            :return : the width of the spike in milliSecs

        """
        # TODO: find the end of the spike with the interval function that will be done later
        # volt, time = self.sliceSpikeGraph(voltVec, timeVec, delay, delay + 10)
        if(not(self.isSpike(voltVec, timeVec, delay, duration, Level.HIGH, PLOTTING))):
            if printing:
                print("No spike detected")
            return 0

        volt, time, plt = self.patternHighligher(
            voltVec, timeVec, delay, duration, False)
        apHeight, vRest, vPeak = self.APHeight(
            voltVec, timeVec, delay, duration, False, False)
        # calculate the mid point
        apHalfV = (apHeight / 2) + vRest

        # find actual matches
        matches = self.closeMatches(volt, apHalfV, 5)
        # check if no matches found
        if matches == []:
            if printing:
                print("no matches were found!")
            return 0  # could have retried with a different precesion
        matches = list(zip(*matches))
        # print(f'matches {matches}')
        vMatches = matches[0]
        indexMatches = matches[-1]

        m1 = vMatches[0]
        m2 = vMatches[-1]
        t1 = time[indexMatches[0]]
        t2 = time[indexMatches[-1]]

        apWidth = (t2 - t1)
        if plotting:
            plt = Plotter.graphOverlap(voltVec, timeVec, 'k', 'Full AP', 0.8,
                                       volt, time, 'g', 'AP Spike', 1.0, 'AP Width')

            Plotter.graphMarker(plt, t1, m1, 'AP half1', 'x')
            Plotter.graphMarker(plt, t2, m2, 'AP half2', 'x')

            plt.show()
        if printing:
            # print(f'vRest {vRest} mV')
            # print(f'apHalfV {apHalfV} mV')
            print(f'apWidth: {apWidth} ms')
        return apWidth

    def AHPDepth(self, voltVec, timeVec, delay, duration, plotting: bool = PLOTTING, printing: bool = PRINTING):
        """ Calculate the depth of the AHP phase in mV

        Args:
            :param voltVec: recoreded vector of the spike voltage
            :param timeVec: recoreded vector of the spike time
            :param delay: the time at which the stimulation is started
            :param duration: the time for which the stimulation is continued
            :param plotting: Boolean used to toggle plotting on and off
            :param printing: Boolean used to toggle printing on and off


        :return AHPDepth:depth of the AHP phase in mV

        """
        if(not(self.isSpike(voltVec, timeVec, delay, duration, Level.HIGH, PLOTTING))):
            if printing:
                print("No spike detected")
            return 0

        volt, t, plt = self.patternHighligher(
            voltVec, timeVec, delay, duration, plotting=plotting, reverse=True)
        AHPStartV = volt[0]
        AHPPeakV = min(volt)
        AHPStartT = t[0]
        AHPPeakT = t[volt.index(AHPPeakV)]
        AHPDepthV = abs(AHPPeakV - AHPStartV)

        if plotting:
            Plotter.graphMarker(
                plt, AHPPeakT, AHPPeakV, 'AHP PEAK', markerShape='x')
            Plotter.graphMarker(
                plt, AHPStartT, AHPStartV, 'AHP Start', markerShape='x')

            plt.title('AHP Depth')
            plt.show()
        if printing:
            print(f'AHPDepthV :{AHPDepthV} mV')
        return AHPDepthV

    def AHPDuration(self, voltVec, timeVec, delay, duration, plotting: bool = PLOTTING, printing: bool = PRINTING):
        """ Calculate the duration of the AHP phase in mSec

        Args:
            :param voltVec: recoreded vector of the spike voltage
            :param timeVec: recoreded vector of the spike time
            :param delay: the time at which the stimulation is started
            :param duration: the time for which the stimulation is continued
            :param plotting: Boolean used to toggle plotting on and off
            :param printing: Boolean used to toggle printing on and off

        :return AHPDuration:duration of the AHP phase in mSec
        """
        if(not(self.isSpike(voltVec, timeVec, delay, duration, Level.HIGH, plotting))):
            if printing:
                print("No spike detected")
            return 0

        volt, t, plt = self.patternHighligher(
            voltVec, timeVec, delay, duration, plotting=plotting, reverse=True)
        AHPStartV = volt[0]
        AHPStartT = t[0]

        AHPEndV = volt[-1]
        AHPEndT = t[-1]
        AHPDuration = AHPEndT - AHPStartT

        if plotting:
            Plotter.graphMarker(
                plt, AHPStartT, AHPStartV, 'AHP Start', markerShape='x')
            Plotter.graphMarker(plt, AHPEndT, AHPEndV,
                                'AHP End', markerShape='x')

            plt.title('AHP Duration')
            plt.show()
        if printing:
            print(f'AHPDuration: {AHPDuration} mSecs')
        return AHPDuration

    def AHPHalfDuration(self, voltVec, timeVec, delay, duration, plotting: bool = PLOTTING, printing: bool = PRINTING):
        """ Calculate the half-duration of the AHP phase in mSec

        Args:
            :param voltVec: recoreded vector of the spike voltage
            :param timeVec: recoreded vector of the spike time
            :param delay: the time at which the stimulation is started
            :param duration: the time for which the stimulation is continued
            :param plotting: Boolean used to toggle plotting on and off
            :param printing: Boolean used to toggle printing on and off

        :return AHPHalfDuration:half duration of the AHP phase in mSec
        """
        if(not(self.isSpike(voltVec, timeVec, delay, duration, Level.HIGH, PLOTTING))):
            if printing:
                print("No spike detected")
            return 0

        volt, t, plt = self.patternHighligher(
            voltVec, timeVec, delay, duration, plotting=plotting, reverse=True)
        AHPStartV = volt[0]
        AHPPeakV = min(volt)
        # print(f'AHPPeakV :{AHPPeakV}')
        # print(f'AHPStartV :{AHPStartV}')

        AHPHalfV = ((AHPPeakV - AHPStartV) / 2) + AHPStartV
        # find close matches to the exact value of {AHPHalfV}

        matches = self.closeMatches(volt, AHPHalfV, 0.5)
        if matches == []:
            if printing:
                print("no matches were found!")
            return 0  # could have retried with a different precesion

        # print(f'\nmatches :{matches}\n')
        matches = list(zip(*matches))
        # print(f'\nmatches zip: {matches}\n')

        #   TODO: remove print later
        if printing:
            print(f'AHPHalfV :{AHPHalfV}')
            # print(f'matches {matches}')
        matchesV, matchesT = matches
        # left point
        v1 = matchesV[0]
        t1 = t[matchesT[0]]

        # right point
        v2 = matchesV[-1]
        t2 = t[matchesT[-1]]

        AHPHalfDuration = t2 - t1
        if plotting:
            Plotter.graphMarker(
                plt, t1, v1, 'AHP half-left', markerShape='x')
            Plotter.graphMarker(
                plt, t2, v2, 'AHP half.right', markerShape='x')
            plt.show()
        if printing:
            print(f'AHPHalfDuration: {AHPHalfDuration} mSecs')
        return AHPHalfDuration

    def AHPHalfDecay(self, voltVec, timeVec, delay, duration, plotting: bool = PLOTTING, printing: bool = PRINTING):
        """ Calculate the half-decay of the AHP phase in mSec

        Args:
            :param voltVec: recoreded vector of the spike voltage
            :param timeVec: recoreded vector of the spike time
            :param delay: the time at which the stimulation is started
            :param duration: the time for which the stimulation is continued
            :param plotting: Boolean used to toggle plotting on and off
            :param printing: Boolean used to toggle printing on and off

        :return AHPHalfDecay:half decay of the AHP phase in mSec
        """

        if(not(self.isSpike(voltVec, timeVec, delay, duration, Level.HIGH, PLOTTING))):
            if printing:
                print("No spike detected")
            return 0

        volt, t, plt = self.patternHighligher(
            voltVec, timeVec, delay, duration, plotting=plotting, reverse=True)
        AHPStartV = volt[0]
        AHPPeakV = min(volt)
        AHPPeakT = t[volt.index(AHPPeakV)]

        AHPHalfV = ((AHPPeakV - AHPStartV) / 2) + AHPStartV
        # print(f'AHPHalfV :{AHPHalfV}')

        # find close matches to the exact value of {AHPHalfV}
        matches = self.closeMatches(volt, AHPHalfV, 0.5)
        if matches == []:
            if printing:
                print("no matches were found!")
            return 0  # could have retried with a different precesion

        matches = list(zip(*matches))
        # print(f'matches {matches}')
        matchesV, matchesT = matches

        # right point
        AHPHalfVLeft = matchesV[-1]
        AHPHalfTLeft = t[matchesT[-1]]

        AHPHalfDecay = AHPHalfTLeft - AHPPeakT
        if plotting:

            Plotter.graphMarker(
                plt, AHPHalfTLeft, AHPHalfVLeft, 'AHP half-left', markerShape='x')
            Plotter.graphMarker(
                plt, AHPPeakT, AHPPeakV, 'AHP Peak', markerShape='x')

            plt.title('AHP Half-Decay')
            plt.show()
        if printing:
            print(f'AHPHalfDecay: {AHPHalfDecay} mSecs')
        return AHPHalfDecay

    def AHPRisingTime(self, voltVec, timeVec, delay, duration, plotting: bool = PLOTTING, printing: bool = PRINTING):
        """ Calculate the Rising Time of the AHP phase in mSec

            Args:
                :param voltVec: recoreded vector of the spike voltage
                :param timeVec: recoreded vector of the spike time
                :param delay: the time at which the stimulation is started
                :param duration: the time for which the stimulation is continued
                :param plotting: Boolean used to toggle plotting on and off
                :param printing: Boolean used to toggle printing on and off

            :return AHPRisingTime: Rising Time of the AHP phase in mSec
        """
        # check if there's a spike
        if(not(self.isSpike(voltVec, timeVec, delay, duration, Level.HIGH, plotting))):
            if printing:
                print("No spike detected")
            return 0

        volt, t, plt = self.patternHighligher(
            voltVec, timeVec, delay, duration, plotting=plotting, reverse=True)
        AHPStartV = volt[0]
        AHPStartT = t[0]

        AHPPeakV = min(volt)
        AHPPeakT = t[volt.index(AHPPeakV)]

        AHPRisingTime = AHPPeakT - AHPStartT
        if plotting:
            Plotter.graphMarker(
                plt, AHPPeakT, AHPPeakV, 'AHP PEAK', markerShape='x')
            Plotter.graphMarker(
                plt, AHPStartT, AHPStartV, 'AHP Start', markerShape='x')
            plt.title('AHP-Rising Time')
            plt.show()
        if printing:
            print(f'AHPRisingTime :{AHPRisingTime} mSecs')
        return AHPRisingTime

    def Rheobase(self, accuracy, refineTimes: int, plotting: bool = PLOTTING, printing: bool = PRINTING, duration=50, delay=150):
        """ Calculate Rheobase current of the cell in nA
            Args:
                :param accuracy: accuracy level {Level.HIGH, Level.MID, Level.LOW,Level.VLOW}
                :param refineTimes: number of repeation, the higher, the more accurate the Rheobase
                :param plotting: Boolean used to toggle printing on and off
                :param printing: Boolean used to toggle printing on and off
                :param duration: the time for which the stimulation is continued (should be +50 ms)
                :param delay: the time at which the stimulation is started

            :return rheobase: Calculate Rheobase current of the cell in nA
        """
        rheobase_steps = False
        start = 1
        end = 20
        step = 1
        while refineTimes:

            for current in np.arange(start, end, step):

                volt, t = self.cell.stimulateCell(
                    current, duration, delay, 500, "soma", "soma", clampAt=0.5, recordAt=0.5, init=-65)
                if self.isSpike(volt, t, delay, duration, accuracy, plotting=plotting):
                    start = current - step
                    end = current
                    if printing and rheobase_steps:
                        print(f'in Range [{start},{end}] ')
                        print(f'at current: {current}')
                    step = step / 10
                    break

            refineTimes -= 1

        rheobase = end
        if printing:
            print(f'rheobase {rheobase} nA')
        return rheobase

########################################################################
##################         HELPER FUNCTIONS          ###################
########################################################################

    def sliceSpikeGraph(self, voltVec, tVec, startAtTime, endAtTime):
        """ Slices the spike between two desired times

                :param voltVec: recoreded vector of the spike voltage
                :param tVec: recoreded vector of the spike time
                :param startAtTime: time in (ms) at which start the slice
                :param endAtTime: time in (ms) at which end the slice


            :return slicedVolt: (list) of the sliced spike's voltVec
            :return slicedTime: (list) of the sliced spike's tVec

         """

        voltVec = list(voltVec)
        tVec = list(tVec)

        slicedTime = [t for t in tVec if startAtTime <= t <= endAtTime]

        startIndex = tVec.index(slicedTime[0])
        endIndex = tVec.index(slicedTime[-1])

        slicedVolt = voltVec[startIndex:endIndex + 1]

        return slicedVolt, slicedTime

    def closeMatches(self, lst: list, findVal, tolerance):
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

    def patternHighligher(self, voltVec, timeVec, delay, duration, plotting: bool = PLOTTING, restingVolt=-65, reverse=False):
        """ Detects the up-down shape of the spike and extracts it
            Args:
                :param voltVec: recoreded vector of the spike voltage
                :param timeVec: recoreded vector of the spike time
                :param delay: the time at which the stimulation is started
                :param duration: the time for which the stimulation is continued
                :param plotting: Boolean used to toggle plotting on and off



            :return spikeVolt: list of the spike voltage values
            :return spikeTime: list of the spike time values
            :return plt: matplotlib class member (graph handler,used to overlay on top old graphs)

         """
        volt, t = self.sliceSpikeGraph(
            voltVec, timeVec, delay, delay + duration + 70)

        stillUp = True
        stillDown = True
        # if not(reverse):
        spikeVolt = [volt[0]]
        for v in volt:
            title = "Spike Pattern"
            label = "Spike"

            if (v >= spikeVolt[-1]) and stillUp:
                spikeVolt += [v]
            elif (v < spikeVolt[-1]) and (v >= restingVolt) and stillDown:
                stillUp = False
                spikeVolt += [v]
            else:
                stillDown = False
        if reverse:
            stillDown = True
            stillUp = False
            spikeVolt = [spikeVolt[-1]]
            title = "AHP Pattern"
            label = "AHP"
            for v in volt:
                if (v < spikeVolt[-1]) and (v <= restingVolt) and stillDown:
                    spikeVolt += [v]
                    stillUp = True
                elif (v > spikeVolt[-1]) and (v <= restingVolt) and stillUp:
                    stillDown = False
                    spikeVolt += [v]
                else:
                    stillUp = False

        startIndex = volt.index(spikeVolt[0])
        endIndex = volt.index(spikeVolt[-1])
        spikeTime = t[startIndex:endIndex + 1]

        # resize both list to match dimenstions
        spikeVolt, spikeTime = self.matchSize(spikeVolt, spikeTime)
        plt = None
        if plotting:
            plt = Plotter.graphOverlap(voltVec, timeVec, 'k', "Full AP", 0.2,
                                       spikeVolt, spikeTime, 'r', label, 1.0, title)
            # plt.show()

        return spikeVolt, spikeTime, plt

    def matchSize(self, lst1, lst2):
        # resize both list to match dimenstions
        len1 = len(lst1)
        len2 = len(lst2)
        if len1 != len2:
            minLen = min(len1, len2)
            lst1 = lst1[:minLen]
            lst2 = lst2[:minLen]
        return lst1, lst2

    def isSpike(self, voltVec, timeVec, delay, duration, accuracy: Level, plotting: bool = PLOTTING) -> bool:
        """ detect if there is a spike

        Args:
            :param voltVec: recoreded vector of the spike voltage
            :param timeVec: recoreded vector of the spike time
            :param delay: the time at which the stimulation is started
            :param duration: the time for which the stimulation is continued
            :param accuracy: accuracy level {Level.HIGH, Level.MID, Level.LOW,Level.VLOW}
            :param plotting: Boolean used to toggle plotting on and off

        :return bool: true if spike and false otherwise
         """

        volt, t, plt = self.patternHighligher(
            voltVec, timeVec, delay, duration,  plotting=plotting)
        if plotting:
            plt.close()
        return (abs(max(volt) - min(volt)) >= accuracy.value)

    def get_measurements(self, outputDict: dict,requested_measurments: list):
        delay = self.delay
        duration = self.duration
        volt = self.voltage
        t = self.t

        for feature in requested_measurments:
            if feature not in list(NAME_MAP.keys()):
                raise ValueError(
                    f" Feature: '{feature}' is not implemented or not spelled well")
            if NAME_MAP[feature] == "inputResistance":
                outputDict[feature] = self.inputResistance(-0.5,
                                                                  plotting=False, printing=False)
            elif NAME_MAP[feature] == "Rheobase":
                outputDict[feature] = self.Rheobase(
                    Level.VLOW, 1, plotting=False, printing=False)
            elif NAME_MAP[feature] == "timeConstant":
                outputDict[feature] = self.timeConstant(
                    -0.5, plotting=False, printing=False)
            else:
                outputDict[feature] = getattr(self, NAME_MAP[feature])(
                    volt, t, delay, duration, plotting=False, printing=False)
        self.measurements = outputDict
        return outputDict
