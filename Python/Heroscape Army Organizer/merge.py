# Name: Benjamin Jones
# Program: Database Merger
# purpose: Merge two databases together

# imports
import sqlite3
import itertools
import os

import CardDatabaseMaker
import Gather
import popup

class merge:
    __slots__ = ["mergeTo","mergeWith","pu"]
    
    def __init__(self, mergeTo, mergeWith = "units.db"):
        self.mergeTo = CardDatabaseMaker.ReadFiles(mergeTo)
        self.mergeWith = CardDatabaseMaker.ReadFiles(mergeWith)
        self.pu = popup.PopUp()

    def combine(self):
        # collect every item in mergeWith
        items = self.mergeWith.getAll()
        # if it is already in mergeTo, add the quantity together
        for item in items:
            withHelp = self.mergeWith.display(item)
            if self.mergeTo.inside(item):
                toHelp = self.mergeTo.display(item)
                self.mergeTo.add(withHelp[0],
                        toHelp[1],
                        toHelp[2],
                        toHelp[3],
                        toHelp[4],
                        toHelp[5],
                        toHelp[6],
                        toHelp[7],
                        toHelp[8],
                        toHelp[9],
                        toHelp[10],
                        toHelp[11],
                        toHelp[12],
                        toHelp[13],
                        toHelp[14] + withHelp[14])
            else:
                self.mergeTo.add(
                        withHelp[0],
                        withHelp[1],
                        withHelp[2],
                        withHelp[3],
                        withHelp[4],
                        withHelp[5],
                        withHelp[6],
                        withHelp[7],
                        withHelp[8],
                        withHelp[9],
                        withHelp[10],
                        withHelp[11],
                        withHelp[12],
                        withHelp[13],
                        withHelp[14])
        return
                    
                
        # otherwise create a new element with every item of it
        
        
