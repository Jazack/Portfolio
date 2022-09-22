# Name: Benjamin Jones
# Program: Display.py
# Purpose: create a GUI for the database

# import elements
from tkinter import *
from tkinter import simpledialog
from tkinter import scrolledtext
from tkinter import ttk
from tkinter import messagebox
from tkinter import simpledialog
from functools import partial
import sys
import threading
# import additional scripts
import CardDatabaseMaker
import Gather
import popup
import pointEval
import new

# class Display
#
# purpose: to display the elements
class Display:
    # pre-define the slots
    __slots__ = ['oldText', 'pu', 'db', 'gt', 'pe', "dicL", "connected",
                 "powers", "specials", "tabs", "eff", 'nTabs', 'nSpecials',
                 'generals', 'general', 'start', 'opt', 'loc','database', 'extra', 'threads']

    """
    __init__:  sets up the parameters

    parameters:
    self ----- this can be ignored
    db ------- the database to be used, if no databse is given, use the default units.db
    unit ----- the unit to load
    """
    def __init__(self, db="units.db", unit = False):
        self.database = db
        self.db = CardDatabaseMaker.ReadFiles(db)
        self.gt = Gather.GatherItems(db)
        self.pu = popup.PopUp()
        self.pe = pointEval.worthEval(db)
        self.general = self.db.getAllGenerals()
        self.generals = []
        for item in self.general:
            self.generals.append([item, self.db.getGeneralRank(item)])
        self.general = []
        for item in self.generals:
            self.general.append(item[0])
        sorting = lambda x : (x[1])
        self.generals = sorted(self.generals, key = sorting)
        self.threads = {}
##        print(self.generals)
##        self.generals = ["JANDAR", "ULLAR", "VYDAR", "EINAR", "UTGAR", "VALKRILL", "AQUILLA", "MARVEL"]
        if unit:
            self.extra = True
            self.start = unit[0]
            self.loc = unit[1]
            self.opt = 3
        else:
            self.extra = False
            self.start = False
            self.opt = 21
            self.loc = False
        

    
    """
    cardview: displays the cards and runs the GUI

    parameters:
    self ----- this can be ignored
    window --- the window that is to be used
    starter -- the starter unit
    """
    def cardview(self, window, starter = False):
        
##        if type(starter) != bool and len(starter) > 1:
##            starter = starter[0]
        title = "Heroscape Database"
        firstRun = True

        ## used to add generals
        def addGeneral():
            try:
                newGeneral = simpledialog.askstring(title="New General", prompt="Name of the new general:")
                if newGeneral == "":
                    raise Exception("NO NAME GIVEN")
                elif newGeneral == False:
                    return
                rank = self.generals[-1][1] + 1
                color = "white"
                newGeneral = newGeneral.upper()
                self.db.addGeneral(newGeneral, color, rank)
                self.generals.append([newGeneral, rank])
                self.general.append(newGeneral)
                updateGenerals()
                messagebox.showinfo("SUCCESS", "Successfully added your general")
            except:
                print("Unexpected error: ", sys.exc_info()[0])
                print("Message: ", sys.exc_info()[1])
            return
        ## used to delete a general
        def delGeneral(gen):
            mes = "WARNING! THIS CANNOT BE UNDONE!\nALL FIGURES UNDER THE GENERAL WILL BE DELETED!\nCONTINUE?"
            if messagebox.askokcancel('Delete General', mes):
                i = 0
                for general in self.generals:
                    if gen in general:
                        break
                    i += 1
                self.generals.pop(i)
                self.general.remove(gen)
                i = 0
                while True:
                    if i in self.threads:
                        i += 1
                    else:
                        break
                self.threads[i] = threading.Thread(target = delGeneralHelper, args = (gen, i))
                self.threads[i].start()
            else:
                print("cancelled")
            return
        def delGeneralHelper(gen, i):
            toDel = self.db.gatherGeneral(gen)
            for unit in toDel:
                print('deleting ', end='')
                print(unit)
                self.db.delete(unit)
            self.db.delGeneral(gen)
            updateGenerals()
            deleteMenu(gen)
            messagebox.showinfo("SUCCESS", "Successfully deleted the general")
            return

        ## used to help with keeping track of the generals
        def updateGenerals():
            filemenu.delete(0, 'last')
            fileDelGenerals.delete(0, 'last')
            filemenu.add_cascade(label="All", menu = allUnits, background=CustColorChange(("","allUnits")))
            create (allUnits, "allUnits")
            for general in self.generals:
                myVarsFiles[general[0]] = Menu(menu, tearoff = 0)
                create(myVarsFiles[general[0]], general[0])
                use = general[0][0] + general[0][1:].lower()
                filemenu.add_cascade(label = use, menu = myVarsFiles[general[0]], background=CustColorChange(("",general[0])))
                fileDelGenerals.add_command(label = use, command = partial(delGeneral, general[0]))
        ## used to set to zero all items
        def emptyAll():
            # make a screen to warn about this
            mes = "WARNING! THIS CANNOT BE UNDONE!\nCONTINUE?\n(NOTE: YOU MUST EXIT THE DATABASE BEFORE\nEFFECTS TAKE PLACE"
            return emptyAllHelper() if self.pu.popup(mes) else print("cancelled")
            
        def emptyAllHelper():
            # get list of all names, empty each item
            manage = self.db.getAll()
            for unit in manage:
                temp = self.db.display(unit)
                temp[-1] = 0
                add(temp)
            
        ## used to drop items
        def drop():
            send = name.get("1.0",END).upper().strip("\n")
            if self.db.display(send):
                mes = 'Are you sure you want to delete '
                mes += send + '?'
                if not messagebox.askokcancel('ABOUT TO DELETE', mes):
                    return
            else:
                messagebox.showinfo('NO DATA', 'There is no unit to delete')
                return
            self.db.delete(send)
            deleteMenu()
            messagebox.showinfo("SUCCESS", "Unit deleted successfully")
        ## used to change the color of non database items
        def CustColorChange(group):
            send = group[1].lower()#general.get("1.0",END).lower().strip("\n")
            if len(send) == 0:
                return
            nsend = send.upper()# + send[1:]
            color = self.db.getGeneralColor(nsend)
            if color == []:
                color = "white"
            return color
        ## used to change the color of database items
        def colorChange():
            send = general.get("1.0",END).lower().strip("\n")
            nsend = send.upper()# + send[1:]
            color = self.db.getGeneralColor(nsend)
            if color == []:
                color = "white"
            window.configure(background=color)
            for wid in widgets:
                wid.configure(bg=color)
        # used to delete menus 
        def deleteMenu(nsend = False):
            if not nsend:
                send = general.get("1.0",END).lower().strip("\n")
                nsend = send.upper()# + send[1:]
            #because python apparently does not have
            #switch statements
            allUnits.delete(0, 'last')
            create(allUnits, "allUnits")
            for key in myVarsFiles.keys():
                if nsend == key:
                    myVarsFiles[key].delete(0, 'last')
                    create(myVarsFiles[key], key)
                    break
##            if nsend == "Jandar":
##                jandar.delete(0, 'last')
##                create(jandar, "jandar")
##            elif nsend == "Ullar":
##                ullar.delete(0, 'last')
##                create(ullar, "Ullar")
##            elif nsend =="Einar":
##                einar.delete(0, 'last')
##                create(einar, "Einar")
##            elif nsend =="Vydar":
##                vydar.delete(0, 'last')
##                create(vydar, "vydar")
##            elif nsend =="Utgar":
##                utgar.delete(0, 'last')
##                create(utgar, "Utgar")
##            elif nsend =="Marvel":
##                marvel.delete(0, 'last')
##                create(marvel, "Marvel")
##            elif nsend =="Aquilla":
##                aquilla.delete(0, 'last')
##                create(aquilla, "Aquilla")
##            elif nsend =="Valkrill":
##                valkrill.delete(0, 'last')
##                create(valkrill, "Valkrill")
        # used to make it so all the fields can be edited
        def editor():
            name.config(state=NORMAL)
            general.config(state=NORMAL)
            race.config(state=NORMAL)
            ty.config(state=NORMAL)
            cla.config(state=NORMAL)
            personality.config(state=NORMAL)
            size.config(state=NORMAL)
            life.config(state=NORMAL)
            move.config(state=NORMAL)
            ran.config(state=NORMAL)
            attack.config(state=NORMAL)
            defense.config(state=NORMAL)
            points.config(state=NORMAL)
            if abilities['state'] != "normal":
                change(abilities, self.oldText)
            abilities.config(state=NORMAL)
            quantity.config(state=NORMAL)
        # what to do when someone hits enter
        def enterHelp(event = None):
            read()
            search.delete("1.0",END)
            return("break")
        # focus on the next window with tab
        def focus_next_window(event):
            event.widget.tk_focusNext().focus()
            return("break")
        # create function
        def create(file, name):
            send = []
            if name == "allUnits":
                for general in self.generals:
                    send.append(general[0])
            else:
                send.append(name.upper())
                
            items = self.db.gatherGeneral(send)
            items = sorted(items)
            for i in items:
                file.add_command(label=i, command=partial(menuHelp, i))
        # changes what's in a field
        def change(text, item):
            text.config(state=NORMAL)
            text.delete("1.0", END)
            if item != None and item != "":
                text.insert("1.0", item)
                text.config(state=DISABLED)
        # destroy's the window
        def destroy():
            window.quit()
        # empties everything
        def empty():
            items=[]
            for i in range(15):
                items.append(None)
            change(name, items[0])
            change(general,items[1])
            change(race,items[2])
            change(ty,items[3])
            change(cla,items[4])
            change(personality,items[5])
            change(size,items[6])
            change(life,items[7])
            change(move,items[8])
            change(ran,items[9])
            change(attack,items[10])
            change(defense,items[11])
            change(points,items[12])
            change(abilities,items[13])
            change(quantity,items[14])
        # helps the menu communicate with changeHelp
        def menuHelp(name):
            items = self.db.display(name)
            changeHelp(items)
        # changes the displayed items
        def changeHelp(items):
            try:
                for tab in self.tabs:
                    tab.destroy()
            except:
                pass
            try:
                for tab in self.nTabs:
                    tab.destroy()
            except:
                pass
            change(name, items[0])
            change(general,items[1])
            change(race,items[2])
            change(ty,items[3])
            change(cla,items[4])
            change(personality,items[5])
            change(size,items[6])
            change(life,items[7])
            change(move,items[8])
            change(ran,items[9])
            change(attack,items[10])
            change(defense,items[11])
            change(points,items[12])
            change(abilities,abilGet(items[13]))
            change(quantity,items[14])
            quantity.config(state=NORMAL)
            colorChange()
            self.eff = self.gt.gather(items[0])
            if self.eff != None:
                synergy()
        # reads in the search bar item and displays it if it exists
        def read(send = False):
            reset = True
            if send == False:
                reset = False
                send = search.get("1.0", END).upper().strip("\n")
            items=[]
            items = self.db.display(send)
            if len(items) == 0 or send == "NEW":
                for i in range (15):
                    items.append(None)
            if reset:
                send = False
            changeHelp(items)
        # gets the abilities so as to show which characters the abilities effect
        def abilGet(item):
            self.dicL = []
            self.powers = []
            self.oldText = item
            newText = ""
            search = ""
            ty = ""
            do = ""
            spch = False
            inName = False
            hidden = False
            for char in item:
                if not spch:
                    if char == "<":
                        inName = True
                        spch = True
                    else:
                        if not hidden:
                            newText += char
                        if inName:
                            search += char
                else:
                    if not inName and char == ">":
                        spch = False
                        if do == "":
                            do = None
                        if ty == "POWER":
                            self.powers.append(search)
                        if ty == "HIDDEN" or ty == "HID":
                            hidden = not hidden
                        else:
                            self.dicL.append((ty,search,do))
                        ty = ""
                        search = ""
                        do = ""
                    elif char == ">":
                        if ty == "HIDDEN" or ty == "HID":
                            hidden = not hidden
                            inName = False
                            ty = ""
                        spch = False
                    elif char == "/":
                        inName = False
                    elif inName and char != ">":
                        ty += char
                    elif not inName:
                        do += char
            self.connected = self.db.custSearchHelp(self.dicL)
            if self.connected != None:
                specialSetup()
            return newText
        # for setting up the synergy section on the left
        def synergy():

            allies.delete(0, 'last')
            nuetral.delete(0, 'last')
            enemies.delete(0, 'last')
            
            eff = sorted(self.eff)

            for ef in eff:
                if ef != None:
                    for i in ef:
                        if i[1][1] == "A":
                            allies.add_command(label=i[1][0], state=DISABLED)
                            allies.add_command(label=i[0], command=partial(menuHelp, i[0]), background = CustColorChange(self.db.display(i[0])))
                        elif i[1][1] == None:
                            nuetral.add_command(label=i[1][0], state=DISABLED)
                            nuetral.add_command(label=i[0], command=partial(menuHelp, i[0]), background = CustColorChange(self.db.display(i[0])))
                        elif i[1][1] == "E":
                            enemies.add_command(label=i[1][0], state=DISABLED)
                            enemies.add_command(label=i[0], command=partial(menuHelp, i[0]), background = CustColorChange(self.db.display(i[0])))
        # adds new characters
        def add(send=[]):
            if send == [] or len(send) < 15:
                send = []
                change = True
                if name.get("1.0",END).isspace() or general.get("1.0",END).isspace(): return
                send.append(name.get("1.0",END).upper().strip("\n"))
                send.append(general.get("1.0",END).upper().strip("\n"))
                if send[-1] not in self.general:
                    mes = "ERROR: AN INVALID ENTRY WAS GIVEN FOR GENERAL"
                    messagebox.showerror('INCORRECT DATA', mes)
                    send = []
                    return
                send.append(race.get("1.0",END).upper().strip("\n"))
                send.append(ty.get("1.0",END).upper().strip("\n"))
                send.append(cla.get("1.0",END).upper().strip("\n"))
                send.append(personality.get("1.0",END).upper().strip("\n"))
                send.append(size.get("1.0",END).upper().strip("\n"))
                send.append(life.get("1.0",END).upper().strip("\n"))
                if not send[-1].isdigit():
                    mes = "ERROR: AN INVALID ENTRY WAS GIVEN FOR LIFE"
                    messagebox.showerror('INCORRECT DATA', mes)
                    send = []
                    return
                send.append(move.get("1.0",END).upper().strip("\n"))
                if not send[-1].isdigit():
                    mes = "ERROR: AN INVALID ENTRY WAS GIVEN FOR MOVE"
                    messagebox.showerror('INCORRECT DATA', mes)
                    send = []
                    return
                send.append(ran.get("1.0",END).upper().strip("\n"))
                if not send[-1].isdigit():
                    mes = "ERROR: AN INVALID ENTRY WAS GIVEN FOR RANGE"
                    messagebox.showerror('INCORRECT DATA', mes)
                    send = []
                    return
                send.append(attack.get("1.0",END).upper().strip("\n"))
                if not send[-1].isdigit():
                    mes = "ERROR: AN INVALID ENTRY WAS GIVEN FOR ATTACK"
                    messagebox.showerror('INCORRECT DATA', mes)
                    send = []
                    return
                send.append(defense.get("1.0",END).upper().strip("\n"))
                if not send[-1].isdigit():
                    mes = "ERROR: AN INVALID ENTRY WAS GIVEN FOR DEFENSE"
                    messagebox.showerror('INCORRECT DATA', mes)
                    send = []
                    return
                send.append(points.get("1.0",END).upper().strip("\n"))
                if not send[-1].isdigit():
                    mes = "ERROR: AN INVALID ENTRY WAS GIVEN FOR POINT VALUE"
                    messagebox.showerror('INCORRECT DATA', mes)
                    send = []
                    return
                if abilities['state'] == "normal":
                    send.append(abilities.get("1.0",END).upper().strip("\n"))
                else: send.append(self.oldText)
                send.append(quantity.get("1.0",END).upper().strip("\n"))
                if not send[-1].isdigit():
                    mes = "ERROR: AN INVALID ENTRY WAS GIVEN FOR QUANTITY"
                    messagebox.showerror('INCORRECT DATA', mes)
                    send = []
                    return
                
            else: change = False
            if self.db.display(send[0]):
                if not messagebox.askokcancel('UNIT ALREADY EXISTS','This unit already exists, save anyways?'):
                    return
            self.db.add(send[0],
                        send[1],
                        send[2],
                        send[3],
                        send[4],
                        send[5],
                        send[6],
                        send[7],
                        send[8],
                        send[9],
                        send[10],
                        send[11],
                        send[12],
                        send[13],
                        send[14])
            # see if the item is in table records
            temp = self.db.displayRecord(send[0])
            if temp == []:
                worth = self.pe.formula(send[0])
                self.db.addRecord(send[0], 0, 0, 'N\A', worth)
            for i in range(0,15): send.pop()
            if change: deleteMenu()
            messagebox.showinfo("SUCCESS", "UNIT SUCCESSFULLY SAVED")

        ## for setting up the specials tab on the right
        def specialSetup():
            isEmpty = True
            for item in self.connected:
                if item != None:
                    isEmpty = False
            if isEmpty:
                return
            self.tabs = []
            self.specials = []

            self.tabs.append(Frame(window))
            self.tabs[0].grid(row=0,column=co,rowspan=17,sticky='news')
            self.tabs[0].grid_rowconfigure(0,weight=1)
            self.tabs[0].grid_columnconfigure(0,weight=1)
            self.tabs[0].grid_propagate(False)

            self.tabs.append(Canvas(self.tabs[0]))
            self.tabs[1].grid(row=0,column=0,sticky="news")

            self.tabs.append(Scrollbar(self.tabs[0],orient="vertical", command=self.tabs[1].yview))
            self.tabs[1].config(yscrollcommand = self.tabs[-1].set)
            self.tabs[2].grid(row=0,column=1,sticky=N+S)
            
            self.tabs.append(Frame(self.tabs[1]))
            self.tabs[1].create_window((0,0), window=self.tabs[3],anchor='nw')
            for i in range (len(self.powers)):
                if self.connected[i] != None:
                    tempL = Label(self.tabs[3], text=self.powers[i])
                    if self.connected[i] != None and self.connected[i] != () and self.connected[i][0][0] != name.get("1.0",END).upper().strip("\n") or len(self.connected[i]) > 1:
                        self.specials.append(len(self.tabs)-4)
                        self.tabs.append(tempL)
                    for group in self.connected[i]:
                        tempB = Button(self.tabs[3],
                                       text = group[0],
                                       width = 30,
                                       height = 1,
                                       bg = CustColorChange(group),
                                       command = partial(menuHelp, group[0])
                                       )
                        if group[0] != name.get("1.0",END).upper().strip("\n"):
                            self.tabs.append(tempB)
            #in case the user forgets to add in the power tags, this
            #will allow the user to still be able to fix their mistakes
            if len(self.tabs) < 5:
                return
            col = 0
            ro = 0
            total = 0
            for i in range(len(self.tabs)):
                if i > 3:                    
                    self.tabs[i].grid(row=ro, column=col, sticky="news")
                    
                    ro += 1
                    total += 1
                    if total in self.specials:
                        ro = 0
                        col += 1
            col += 1
            self.tabs[3].update_idletasks()
            cols = sum([self.tabs[4].winfo_width() for j in range(col)])
            ros = sum([self.tabs[4].winfo_height() for i in range(0,13)])
            self.tabs[0].config(width=cols+self.tabs[2].winfo_width(),
                                height=ros)
            self.tabs[1].config(scrollregion=self.tabs[1].bbox("all"))
             

        #window
##        window = Tk()
        window.geometry('')
        #menu
        window.bind_class("Text", "<Tab>",focus_next_window)
        menu = Menu(window)
        window.config(menu=menu)
        filemenu = Menu(menu, tearoff=0)
        file = Menu(menu, tearoff=0)
        fileDelGenerals = Menu(menu, tearoff = 0)
                               
        myVarsFiles = vars()

        allUnits = Menu(menu, tearoff=0)
        create (allUnits, "allUnits")
        for general in self.generals:
            myVarsFiles[general[0]] = Menu(menu, tearoff = 0)
            create(myVarsFiles[general[0]], general[0])
##        utgar = Menu(menu, tearoff=0)
##        create(utgar, "utgar")
##        jandar = Menu(menu, tearoff=0)
##        create(jandar, "jandar")
##        ullar = Menu(menu, tearoff=0)
##        create(ullar, "ullar")
##        vydar = Menu(menu, tearoff=0)
##        create(vydar, "vydar")
##        einar = Menu(menu, tearoff=0)
##        create(einar, "einar")
##        aquilla = Menu(menu, tearoff=0)
##        create(aquilla, "aquilla")
##        valkrill = Menu(menu, tearoff=0)
##        create(valkrill, "valkrill")
##        marvel = Menu(menu, tearoff=0)
##        create(marvel, "marvel")

        menu.add_cascade(label="File",menu=file)
        file.add_command(label="New", command=empty)
        file.add_command(label="Save", command = add)
        file.add_command(label="Add general", command = addGeneral)
        file.add_command(label="Empty all", command = emptyAll)
        file.add_cascade(label="Delete general:", menu = fileDelGenerals)
        menu.add_cascade(label="Factions", menu=filemenu)

##        filemenu.add_cascade(label="All", menu = allUnits, background=CustColorChange(("","allUnits")))
        updateGenerals()
##        filemenu.add_cascade(label="Jandar", menu = jandar, background=CustColorChange(("","jandar")))
##        filemenu.add_cascade(label="Ullar", menu = ullar, background=CustColorChange(("","ullar")))
##        filemenu.add_cascade(label="Vydar", menu = vydar, background=CustColorChange(("","vydar")))
##        filemenu.add_cascade(label="Einar", menu = einar, background=CustColorChange(("","einar")))
##        filemenu.add_cascade(label="Utgar", menu = utgar, background=CustColorChange(("", "Utgar")))
##        filemenu.add_cascade(label="Aquilla", menu = aquilla, background=CustColorChange(("","aquilla")))
##        filemenu.add_cascade(label="Valkrill", menu = valkrill, background=CustColorChange(("","valkrill")))
##        filemenu.add_cascade(label="Marvel", menu = marvel, background=CustColorChange(("","marvel")))

        syn = Menu(menu,tearoff=0)
        menu.add_cascade(label="Synergies", menu=syn)
        allies= Menu(menu, tearoff=0)
        enemies = Menu(menu, tearoff=0)
        nuetral = Menu(menu, tearoff=0)

        syn.add_cascade(label="Allies", menu=allies)
        syn.add_cascade(label="Nuetral", menu=nuetral)
        syn.add_cascade(label="Enemies", menu=enemies)
            
        window.grid_columnconfigure(5,weight=1)
        window.grid_rowconfigure(0,weight=1)
        window.title(title)
##        buttons = Frame(window)
        lname = Label(window, text = "NAME:")
        lgeneral = Label(window, text = "GENERAL:")
        lrace = Label(window, text = "RACE:")
        lty = Label(window, text = "TYPE:")
        lcla = Label(window, text = "CLASS:")
        lpersonality = Label(window, text = "PERSONALITY:")
        lsize = Label(window, text = "SIZE:")
        llife = Label(window, text = "LIFE:")
        lmove = Label(window, text = "MOVE:")
        lran = Label(window, text = "RANGE:")
        lattack = Label(window, text = "ATTACK:")
        ldefense = Label(window, text = "DEFENSE:")
        lpoints = Label(window, text = "POINTS:")
        labilities = Label(window, text = "ABILITIES:")
        lquantity = Label(window, text = "QUANTITY:")
        lsearch=Label(window,text="SEARCH:")
        widgets = [lname,lgeneral,lrace,lty,lcla,lpersonality,lsize,llife,lmove,lran,
                   lattack,ldefense,lpoints,labilities,lquantity,lsearch]
        name = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        general = Text(
            window,
            height = 1,
            width=28,
            wrap = "none"
            )
        race = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        ty = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        cla = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        personality = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        size = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        life = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        move = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        ran = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        attack = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        defense = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        abilities = scrolledtext.ScrolledText(
            window,
            wrap="word",
            height = 15,
            width=28,
            )
        points = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        quantity = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        search = Text(
            window,
            height = 1,
            width=15,
            wrap = "none"
            )
        search.bind("<Return>", enterHelp)
        save = Button(
            window,
            text = "Save",
            width = 5,
            height = 1,
            command = partial(add, [])
            )
        load = Button(
            window,
            text = "Load",
            width = 5,
            height = 1,
            command = enterHelp
            )
        delete = Button(
            window,
            text = "Delete",
            width = 5,
            height=1,
            command = drop
            )
        edit = Button(
            window,
            text="Edit",
            width=5,
            height=1,
            command=editor)
        ex = Button(
            window,
            text = "Exit",
            width = 5,
            height = 1,
            command = destroy
            )

        co = 1

        lname.grid(row=0, column=co, columnspan=2,sticky = N+W+E+S)
        name.grid(row=1, column=co, columnspan=2,sticky = N+W+E+S)
        lgeneral.grid(row=3,column=co, columnspan=2,sticky=N+W+E+S)
        general.grid(row=4,column=co,columnspan=2,sticky=N+W+E+S)
        lrace.grid(row=5,column=co,sticky=N+W+E+S)
        race.grid(row=6,column=co,sticky=W)

        lty.grid(row=7,column=co,sticky=N+W+E+S)
        ty.grid(row=8,column=co,sticky=W)

        lcla.grid(row=9,column=co,sticky=N+W+E+S)
        cla.grid(row=10,column=co,sticky=W)

        lpersonality.grid(row=11,column=co,sticky=N+W+E+S)
        personality.grid(row=12,column=co,sticky=W)

        lsize.grid(row=13,column=co,sticky=N+W+E+S)
        size.grid(row=14,column=co,sticky=W)
        lsearch.grid(row=15,column=co,sticky=N+W+E+S)
        search.grid(row=16,column=co,sticky=W)
        co +=1

        save.grid(row=15,column=co,sticky=N+W+E+S)

        load.grid(row=16,column=co,sticky=N+W+E+S)

        llife.grid(row=5,column=co,sticky=N+W+E+S)
        life.grid(row=6,column=co,sticky=W)

        lmove.grid(row=7,column=co,sticky=N+W+E+S)
        move.grid(row=8,column=co,sticky=W)

        lran.grid(row=9,column=co,sticky=N+W+E+S)
        ran.grid(row=10,column=co,sticky=W)

        lattack.grid(row=11,column=co,sticky=N+W+E+S)
        attack.grid(row=12,column=co,sticky=W)

        ldefense.grid(row=13,column=co,sticky=N+W+E+S)
        defense.grid(row=14,column=co,sticky=W)
        co += 1

        labilities.grid(row=0, column=co, columnspan=2)
        abilities.grid(row=1,column=co,columnspan=2,rowspan=12)

        delete.grid(row=16,column=co,sticky=N+W+E+S)

        lpoints.grid(row=13,column=co,sticky=N+W+E+S)
        points.grid(row=14,column=co,sticky=N+W+E+S)
        co += 1

        lquantity.grid(row=13,column=co,sticky=N+W+E+S)
        quantity.grid(row=14,column=co,sticky=N+W+E+S)
        edit.grid(row=15,column=co,sticky=N+W+E+S)

        ex.grid(row=16,column=co,sticky=N+W+E+S)
        co +=1
        if firstRun:
            firstRun = False
            if starter != False:
                read(starter[0])
                
        window.mainloop()
        if self.extra:
            return [self.database, self.opt, starter]
        keys = self.threads.keys()
        for key in keys:
            self.threads[key].join()
        return [self.database, self.opt]
