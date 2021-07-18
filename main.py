# This Python file uses the following encoding: utf-8
import os
from pathlib import Path
import sys

from PySide2.QtGui import QGuiApplication
from PySide2.QtQml import QQmlApplicationEngine
from PySide2.QtCore import QObject, Slot, Signal
import json


class MainWindow(QObject):
    def __init__(self):
        QObject.__init__(self)

        compList = ["soma", "iseg", "den1", "den2", "den3"]
        self.paramList = {'element1':"chungs"}

    # Signal
    appBuffer = Signal(str)

    # Function
    @Slot(str)
    def sendParamList(self, str):
        self.appBuffer.emit(json.dumps(self.paramList))


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
