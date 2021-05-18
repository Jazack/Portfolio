# Name: Benjamin Jones
# Program: Gather.py
# Purpose: Gather files from the database

# imports
import sys
import CardDatabaseMaker

## class Gather Items
#
#Purpose: Gather items from a database
class GatherItems:
    # function __init__
    # self - the item itself, do not need to worry about it
    # db - the database being accessed
    def __init__(self, db):
        # set up the database item
        self.db = CardDatabaseMaker.ReadFiles(db)

    ## gather's the units that effect unit,
    ## separeted into if it's friendly, nuetral, or hostile
    def gather(self, name):
        ret = [] #ret[0] = friendly, [1] = nuetral, [2] = hostile
        for i in range(3):
            ret.append([])
        ## gather all units
        units = sorted(self.db.getAllBut(name))
        ## for each unit see if the abilities effect name
        for i in units:
            effected = self.abilGet(i)
            for eff in effected:
                if name in eff:
                    ## if they do, add them to ret
                    if eff[0][1] == "A":
                        ret[0].append((i, eff[0]))
                    elif eff[0][1] == None:
                        ret[1].append((i, eff[0]))
                    elif eff[0][1] == "E":
                        ret[2].append((i, eff[0]))
            # end of for loop eff
        # end of for loop i
        return ret

    ## gets the abilities of the character of name
    ## name - the name of the character being accesed
    def abilGet(self, name):
        # set up variables
        items = self.db.display(name)
        item = items[13]
        ret = []
        dicL = []
        powers = []
        search = ""
        ty = "" 
        do = ""
        hidden = False
        spch = False
        inName = False
        # go through each char in the item, and sort it into usable information
        for char in item:
            if not spch:
                if char == "<":
                    inName = True
                    spch = True
                else:
                    if inName:
                        search += char
            else:
                if not inName and char == ">":
                    spch = False
                    if do == "":
                        do = None
                    if ty == "POWER":
                        powers.append((search,do))#combines the power with type
                        ret.append([])
                        ret[-1].append(powers[-1])
                    if ty == "HIDDEN" or ty == "HID":
                        if hidden == True:
                            hidden = False
                        else:
                           hidden = True
                    else:
                        dicL.append((ty,search,do))
                    ty = ""
                    search = ""
                    do = ""
                elif char == ">":
                    if ty == "HIDDEN" or ty == "HID":
                            if hidden:
                                hidden = False
                            else:
                                hidden = True
                            inName = False
                            ty = ""
                    spch = False
                elif char == "/":
                    inName = False
                elif inName and char != ">":
                    ty += char
                elif not inName:
                    do += char
        # end of for loop

        # set up items to find that which is connected to the named character
        connected = self.db.custSearchHelp(dicL)
        num = 0
        # only seach if there is something in connected, do a for loop
        # for every item connected
        if connected != None:
            for i in connected:
                try: # try method in case something goes wrong
                    if len(i) > 1:
                        for e in i:
                            if e[0] != None:
                                ret[num].append(e[0])
                    else:
                        if i != None:
                            ret[num].append(i)
                # if something goes wrong, see if i is null, if it's not, append
                # i to the end of ret
                except: 
                    if i != None:
                        ret[num].append(i)
                num += 1 # increment i
            # end of for loop
        else:
            #ret should only have the power within it, as such
            # if there is one with a power and none else,
            pass
        return ret
