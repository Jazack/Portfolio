"""
Author: Benjamin Jones
Date: 4/27/2021
Program: MMenu
Purpose: create the main menu
"""

from tkinter import *
from tkinter import simpledialog
from tkinter import scrolledtext
from tkinter import ttk
from functools import partial
import os
##from Image import ImageTk,Image

class Menu:
    __slots__ = ['db', 'opt',]
    def __init__(self):
        self.db = ""
        self.opt = False
    def mme(self, default, window):
        # constants:
        CARD_V = "CARD VIEWER"
        COPY_D = "COPY DATABASE"
        CARD_S = "CARD STAT VIEWER"
        SET_D = "SET DEFAULT"
        MERGER = "MERGE DATABASES"
        RESETWL = "RESET WIN LOSS RECORD"
        UBR = "UNIT BATTLE REPORT"
        AG = "ARMY GENERATOR"
        UP = "UPDATE VALUES"
        AD = "ARMY DISPLAY"
        N_CARD_V = 1
        N_COPY_D = 2
        N_CARD_S = 3
        N_SET_D = 4
        N_MERGER = 5
        N_RESETWL = 6
        N_UBR = 7
        N_AG = 8
        N_UP = 9
        N_AD = 10
#--------------------------------------------START OF TKINTER FUNCTIONS--------------------------------------------
        self.opt = False
        # functions for tkinter window
        def destroy():
            self.db = False
            self.opt = False
            window.quit()
##            window.destroy()
        def loadHelp(event = None):
            self.db = DBfirst.get()
            self.opt = pFirst.get()
            if self.opt == CARD_V:
                self.opt = N_CARD_V
            elif self.opt == COPY_D:
                self.opt = N_COPY_D
            elif self.opt == CARD_S:
                self.opt = N_CARD_S
            elif self.opt == SET_D:
                self.opt = N_SET_D
            elif self.opt == MERGER:
                self.opt = N_MERGER
            elif self.opt == RESETWL:
                self.opt = N_RESETWL
            elif self.opt == UBR:
                self.opt = N_UBR
            elif self.opt == AG:
                self.opt = N_AG
            elif self.opt == UP:
                self.opt = N_UP
            elif self.opt == AD:
                self.opt = N_AD
            window.quit()
##            window.destroy()
        
#--------------------------------------------START OF TKINTER WINDOW--------------------------------------------
##        window = Tk()
        window.geometry("270x100")
        window.title("HAB")
        # menu
##        window.bind_class("Text", "<Tab>",focus_next_window)

        # images
##        canvas = Canvas(window, width = 680, height = 130)
##        img = ImageTk.PhotoImage(Image.open(file="images\HImage.jpeg"))
##
        # options from local databases
        fileExt = ".db"
        filePath = os.getcwd()
        files = [_ for _ in os.listdir(filePath) if _.endswith(fileExt)]
        files.append("NEW")
        DBfirst = StringVar(window)
        DBfirst.set(default)

        progs = [CARD_V, CARD_S , AG, AD, UBR, UP, COPY_D, MERGER, SET_D, RESETWL]
        pFirst = StringVar(window)
        pFirst.set(progs[0])
        
        # Labels
        lDOptions = Label(window, text="DATABASE:")
        lWOptions = Label (window, text="SUB PROGRAM:")
        lTitle = Label(window, text = "HEROSCAPE SELECTOR")

        widgets = [lDOptions, lWOptions] # this currently doesn't have much use right now, but it likely will
        
        # Menus
        tDOptions = OptionMenu(
            window,
            DBfirst,
            *files,
        )
        tWOptions = OptionMenu(
            window,
            pFirst,
            *progs,
        )
        tDOptions.config(width=15)
        tWOptions.config(width=15)
        # buttons
        load = Button(
            window,
            text = "Load",
            width = 15,
            height = 1,
            command = loadHelp
            )
        ex = Button(
            window,
            text = "Exit",
            width = 15,
            height = 1,
            command = destroy
            )
        co = 1
##        canvas.grid(row=0,column=co,columnspan = 2,sticky = N+W+E+S)
##        canvas.create_image(680,130, anchor = N+W+E+S, image = img)
        lTitle.grid(row = 0, column = co, columnspan = 3, sticky = W+E)
        lDOptions.grid(row=1, column=co, sticky =N+W+E+S)
        tDOptions.grid(row=2, column=co, sticky =N+W+E+S)
        load.grid(row=3, column = co, sticky = N+W+E+S)
        co = co + 1
        lWOptions.grid(row = 1, column = co, sticky = N+W+E+S)
        tWOptions.grid(row = 2, column = co, sticky = N+W+E+S)
        ex.grid(row=3, column = co, sticky = N+W+E+S)
#--------------------------------------------END OF TKINTER WINDOW--------------------------------------------
        mainloop()
        return [self.db, self.opt]
