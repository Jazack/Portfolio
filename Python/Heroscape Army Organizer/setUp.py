# Name: Benjamin Jones
# Program: setUP.py
# Purpose: used for deciding which element to load

import sys
import os.path
from os import path

class setUP:
    __slots__ = ['file', 'default', 'dSize', 'failSafe', 'standardMessage']
    def __init__(self):
        self.file = "setup.heroscape"
        self.failSafe = "units.db"
        self.default = "DEFAULT:"
        self.standardMessage = ["setup.heroscape file","Created for the Heroscape Army Chooser","Best not to edit this document\n"]
        self.dSize = 8
        self.create()

    def create(self):
        if not path.exists(self.file):
            f = open(self.file, "w+")
            f.writelines([
                self.standardMessage[0],
                '\n',
                self.standardMessage[1],
                '\n',self.standardMessage[2],
                '\n',
                'DEFAULT:units.db',
                '\n'
                ])
            f.close()
            
    def setDefault(self, wr):
        location = 0
        f = open(self.file, "r")
        lines = f.readlines()
        for i in lines:
            if i[0:self.dSize] == self.default:
                break
            location += 1
        f.close()
        lines[location] = self.default + wr
        f = open(self.file, "w+")
        f.writelines(lines)
        f.close()

    def getDefault(self):
        f = open(self.file, "r")
        temp = f.readlines()
        
        for i in temp:
            if i[0:self.dSize] == self.default:
                ret = i[self.dSize:]
                return ret.strip('\n')
        return self.failSafe
            
