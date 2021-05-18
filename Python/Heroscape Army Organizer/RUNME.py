# Name: Benjamin Jones
# Program: Controller.py
# Purpose: used for deciding which element to load

import sys
import shutil
from tkinter import *
from tkinter import simpledialog
from tkinter import scrolledtext
from tkinter import ttk
from functools import partial

# my programs
import Display
import MMenu

# Class: Control
#
# Purpose: to control where to send the user and keep everything
#           running smoothly
class Control:
    __slots__ = ['men', "dis", "sw", "ret", "disA"]

    # initialize global variables
    def __init__(self):
        self.men = MMenu.Menu()
        self.sw = ["", True]

    # Function: new
    #
    # Purpose: to get the name for a new database
    # PARAMETERS:
    # change -- the message in the text field
    def new(self, change = ""):
        # initialize variables
        self.ret = ""
        firstPass = True
        # initialize function for button choose
        def choose(event = None):
            self.ret = tGet.get("1.0",END).strip("\n")
            if self.ret != "":
                win.destroy()
        # window
        win = Tk()
        win.title("New Army Creator")
        # elements
        lGet = Label(win, text="PLEASE ENTER TITLE OF NEW DATABASE")
        tGet = Text(
            win,
            width = 30,
            height = 1,
            )
        tGet.bind("<Return>", choose)
        bGet = Button(
            win,
            text = "CHOOSE",
            command = choose,
            )
        if firstPass:
            tGet.insert('1.0', change)
            firstPass = False
        lGet.grid(row=0, column = 0)
        tGet.grid(row=1,column=0)
        bGet.grid(row=2,column=0)
        # loop
        mainloop()
        # return ret
        return self.ret

    # Function: copy
    #
    # Purpose: copy a database
    # PARAMETERS:
    # file -- the file to be copied
    def copy(self, file):
        # run in a try statement
        try:
            # get a name for the new database
            newFile = self.new("PLEASE ENTER NEW FILE NAME")
            # if no name was given, throw an error
            if newFile == "":
                raise Exception("NO NAME GIVEN")
            # see if the file ends in ".db"
            if len(newFile) > 3:
                temp = newFile[len(newFile)-3:]
            else:
                temp = "new"
            # if it doesn't, add a ".db" to the end
            if temp != ".db":
                newFile = newFile + ".db"
            # copy the file
            shutil.copyfile(file, newFile)
        # if an exception is thrown, print the error type and the message
        except:
            print("Unexpected error: ", sys.exc_info()[0])
            print("Message: ", sys.exc_info()[1])
            
    # Function: setUp
    #
    # Purpose: to manage where the user is sent
    def setUp(self):
        # repeat until the user chooses to exit
        while self.sw[1] != False:
            DISPLAY = 1
            COPY = 2
            tracker = 1 # to see if a new database needs to be created, and stop the copy function from happening if so
            self.sw = self.men.mme() #this will return a tuple of which item to open, and the database to use
            # go through an almost switch statement
            if self.sw[0] == "NEW":
                self.sw[0] = self.new()
                tracker = 0
            if self.sw[0] == "": # make sure a proper database name was given
                pass
            elif self.sw[1] == DISPLAY: # if display was choosen, set up and run display
                self.dis = Display.Display(self.sw[0])
                self.dis.cardview()
            elif self.sw[1] == COPY and tracker != 0: # if copy was choosen, run copy
                self.copy(self.sw[0])
    
            

#I may allow for console control over this, but not right now
me = Control()

me.setUp()
