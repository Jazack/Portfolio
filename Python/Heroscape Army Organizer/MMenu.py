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
    __slots__ = ['db', 'opt']
    def __init__(self):
        self.db = ""
        self.opt = False
    def mme(self):
#--------------------------------------------START OF TKINTER FUNCTIONS--------------------------------------------
        self.opt = False
        # functions for tkinter window
        def destroy():
            self.db = False
            self.opt = False
            window.destroy()
        def loadHelp(event = None):
            self.db = DBfirst.get()
            self.opt = pFirst.get()
            if self.opt == "CARD VIEWER":
                self.opt = 1
            elif self.opt == "COPY DATABASE":
                self.opt = 2
            window.destroy()
        
#--------------------------------------------START OF TKINTER WINDOW--------------------------------------------
        window = Tk()
        window.geometry("235x100")
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
        DBfirst.set("units.db")

        progs = ["CARD VIEWER","COPY DATABASE"]
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
