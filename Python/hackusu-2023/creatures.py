'''
class for pc

it will need:
strength
dexterity
wisdom
x
y
life
level
exp
type
inventory
'''
import random
import items
class randomMonster:
    def __init__(self,depth, ID, x, y):
        types = ['spider',
                 'orc',
                 'skeleton',
                 ]
        use = random.randint(0, len(types) - 1)
        use = types[use]
        self.store = monster(depth, ID, x, y, use)
    def getStore(self):
        return self.store
class creatures:
    def __init__(self, ty):
        self.baseStats ={
            # character classes
            'fighter':[random.randint(10,20), random.randint(12,19), random.randint(8,15), random.randint(3, 10), 2],
            'wizard':[random.randint(5,10), random.randint(3,10), random.randint(8,15), random.randint(12, 19), 1],
            'ranger':[random.randint(7,15), random.randint(8,15), random.randint(12,19), random.randint(3, 10), 3],
            # monster section
            'spider':[3,2,3,2,3],
            'orc':[6,4,2,2,1],
            'skeleton':[2,2,3,1,2],
            }
        loc = 0
        self.hp = self.baseStats[ty][loc]
        loc += 1
        self.str = self.baseStats[ty][loc]
        loc += 1
        self.dex = self.baseStats[ty][loc]
        loc += 1
        self.wis = self.baseStats[ty][loc]
        loc += 1
        self.move = self.baseStats[ty][loc]
        loc += 1
        self.ty = ty
    def getHP(self):
        return self.hp
    def wound(self, damage):
        self.hp -= damage
    def getPosition(self):
        return [self.x, self.y]
    def getStats(self):
        return [self.str, self.dex, self.wis]
    def getType(self):
        return self.ty
    def modStr(self, mod):
        self.str += mod
    def modDex(self, mod):
        self.dex += mod
    def modWis(self, mod):
        self.wis += mod
    def attack(self):
        return self.str/2
    def setY(self, y):
        self.y = y
    def setX(self, x):
        self.x = x
    def getMove(self):
        return self.move
class monster(creatures):
    def __init__(self,depth, ID, x, y, ty = 'spider'):
        super().__init__(ty)
        self.strength = ['orc']
        self.dexterity = ['spider', 'skeleton']
        self.wisdom = []
        self.hp = random.randint(10,20)
        self.str = (self.str ** (depth))
        self.dex = (self.dex ** (depth))
        self.wis = (self.wis ** (depth))
        self.x = x
        self.y = y
        self.id = ID
    def getID(self):
        return self.id
    def attack(self):
        if self.getType() in self.strength:
            return round(self.str/2.5)
        elif self.getType() in self.dexterity:
            return (self.dex/2.5)
        elif self.getType() in self.wisdom:
            return (self.wis/2.5)
    def getExp(self):
        if self.getType() in self.strength:
            return round(self.str/2)+1
        elif self.getType() in self.dexterity:
            return round(self.dex/2)+1
        elif self.getType() in self.wisdom:
            return round(self.wis/2)+1
class pc(creatures):
    def __init__(self, ty = 'fighter'):
        super().__init__(ty)
        starters = {
            'fighter':items.aSword,
            'ranger':items.aBow,
            'wizard':items.aStaff,
            }
        self.secretHealth = self.hp
        self.secretStarter = starters[ty]
        self.level = 1
        self.exp = 0
        self.x = 1
        self.y = 1
        self.needed = 10
        self.inventory = [starters[ty](0, 1, 0, 0)]
    def getInventory(self):
        return self.inventory[1:]
    def addInventory(self, item):
        self.inventory.append(item)
    def findItem(self, item):
        for i in range(len(self.inventory)):
            if item.getID() == self.inventory[i].getID():
                return i
        return -1
    def removeInventory(self, item):
        i = self.findItem(item)
        if i > 0:
            del self.inventory[i]
    def getItem(self, index):
        if index < len(self.inventory):
            return self.inventory[index]
        else:
            raise('ATTEMPTING TO USE ITEM THAT DOES NOT EXIST')
    def setEquipped(self, item):
        i = self.findItem(item)
        if i > 0:
            self.inventory[i] = self.inventory[0]
        self.inventory[0] = item
    def setUnequipped(self):
        self.inventory.append(self.inventory[0])
        self.inventory[0] = None
    def getEquipped(self):
    	return self.inventory[0]
    def attack(self):
        use = self.getEquipped()
        return round(use.useItem(self)*(1+self.exp/30) if use else self.str/2*(1+self.exp/30))
    def attackStr(self, modifier):
        return self.str*modifier/2
    def attackDex(self, modifier):
        return self.dex*modifier/2
    def attackWis(self, modifier):
        return self.wis*modifier/2
    def addExperience(self, exp):
    	self.exp += exp
    	ret = False
    	if self.exp >= self.needed:
    		self.needed *= 3
    		ret = True
    	return ret
    def resetEquipped(self):
         self.inventory = [self.secretStarter(0, 1, 0, 0)]
    def resetHealth(self):
         self.hp = random.randint(10,20)
    def wound(self, damage):
        self.hp -= (damage - self.exp/50)
    		
    
        
