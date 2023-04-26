'''
This program generates a magic square
Magic squares are filled with numbers such that the following conditions are met:
	1) each opposite coordinates equal to the same value
	2) all columns and rows equate to the same value
	3) no digit is repeated
This program generates small magic squares. It can easily handle squares smaller than 9x9,
at 9x9 through 15x15 it has a harder time generating it, but can usually handle situations
where it is given a starting value double the recommended value
above 15x15 it rarely works, even with larger starting values.
'''
import random
import math
import time
'''
Class: MagicSquare
Purporse: Creates a magic square
'''
class MagicSquare:
	'''
	def __init__

	params:
	self
	int size ---------- the size of the square, defaults to 3, which is a 3 by 3 grid
	int start --------- the starting value, defaults to -1
	'''
	def __init__(self, size = 3, start = -1):
		self.error = 15
		self.errored = False
		self.size = size
		self.sizeUse = size - 1
		if start > 0:
			self.start = start
		else:
			self.start = random.randrange(int(size**2/2+1), int(size**2))
		self.allDigits = []
		self.magicSquare = []
		for i in range(size):
			temp = []
			for j in range(size):
				temp.append(None)
			self.magicSquare.append(temp)
		self.mid = int((self.size - 1) / 2)
		self.magicSquare[self.mid][self.mid] = self.start
		self.allDigits.append(self.start)
		self.endVals = self.start * self.size
	'''
	def setOpposite
	
	params:
	self
	int x ------------- the x coordinate
	int y ------------- the y coordinate
	int val ----------- the value used
	'''
	def setOpposite(self, x, y, val):
		'''
		opposites are such that
		x + opx = sizeUse
		y + opy = sizeUse
		or
		opx = sizeUse - x
		opy = sizeUse - y
		
		and the value should be such that
		val + opVal = start * 2
		or
		opVal = start * 2 - val
		'''
		opx = self.sizeUse - x
		opy = self.sizeUse - y
		opVal = self.start * 2 - val
		self.allDigits.append(opVal)
		self.magicSquare[opx][opy] = opVal
		
	'''
	def removeVals
	
	params:
	self
	int x ------------- the x coordinate
	int y ------------- the y coordinate
	'''
	def removeVals(self, x, y):
		if x == int((self.size - 1) / 2) and y == int((self.size - 1) / 2):
			return
		if self.magicSquare[x][y]:
			self.allDigits.remove(self.magicSquare[x][y])
		self.magicSquare[x][y] = None
		opx = self.sizeUse - x
		opy = self.sizeUse - y
		if self.magicSquare[opx][opy]:
			self.allDigits.remove(self.magicSquare[opx][opy])
		self.magicSquare[opx][opy] = None
	'''
	def setHalf
	
	params:
	self
	'''
	def setHalf(self):
		'''
		this will set a little under half of the magic square, which will naturally set the other half
		two while loops will be used
		cycling through the array
		'''
		xCoord = 0
		myList = list(set(range(1, self.start * 2)) - set(self.allDigits))
		larger = 50
		smaller = 50
		while(xCoord < int(self.sizeUse / 2)):
			weight = []
			length = len(myList)
			quant = int(length/2)
			for i in range(quant):
				weight.append(larger)
			while len(weight) < length:
				weight.append(smaller)
			yCoord = 0
			yLen = self.size
			reset = 1
			self.errored = False
			while(yCoord < yLen):
				if yCoord + 1 == yLen:
					'''
					get the proper item for here:
					val = endVals - current y vals
					if that is already in the magic square up the yCoord by one
					remove the vals in that location and the opposite,
					generate a new value for it
					'''
					count = 0
					error = 0
					for item in self.magicSquare[xCoord]:
						if item != None:
							count += item
					rand = self.endVals - count
					if rand in self.allDigits or rand <= 0 or rand >= self.start * 2:
						for i in range(0, reset):
							yCoord -= 1
							if self.magicSquare[xCoord][yCoord] > self.start:
								larger += 5
								smaller -= 5
							else:
								larger -= 5
								smaller += 5
							self.removeVals(xCoord, yCoord)
							
						reset += 1
						if reset >= self.size:
							reset = 1
							error += 1
						if error >= self.error:
							self.errored = True
							break
						rand = random.choices(myList, weights=tuple(weight), k = 1)[0]
				else:
					rand = random.choices(myList, weights=tuple(weight), k = 1)[0]
				if self.errored:
					break
				self.allDigits.append(rand)
				self.magicSquare[xCoord][yCoord] = rand
				self.setOpposite(xCoord, yCoord, rand)
				myList = list(set(range(1, self.start * 2)) - set(self.allDigits))
				# if a larger value than the starting value was chosen, become more likely to pick a smaller value
				if rand > self.start:
					larger -= 5
					smaller += 5
				else:
					larger += 5
					smaller -= 5
				weight = []
				length = len(myList)
				quant = int(length/2)
				for i in range(quant):
					weight.append(smaller)
				while len(weight) < length:
					weight.append(larger)
				yCoord += 1
			xCoord += 1
	'''
	def empty
	
	params:
	self
	'''
	def empty(self):
		self.magicSquare = []
		for i in range(size):
			temp = []
			for j in range(size):
				temp.append(None)
			self.magicSquare.append(temp)
		self.magicSquare[self.mid][self.mid] = self.start
		self.allDigits = [self.start]
		self.setHalf()
	'''
	def setRest
	
	params:
	self
	'''
	def setRest(self):
		'''
		sets the middle part of the magic square
		
		calculate the values for each row
		if the item is not in the magicsquare already, add it
		else remove spots that are next to it
		'''
		y = 0
		destroy = False
		while y < self.mid:
			if self.magicSquare[self.mid][y] == None:
				count = 0
				for x in range(0, self.size):
					if self.magicSquare[x][y] != None:
						count += self.magicSquare[x][y]
				val = self.endVals - count
				if val in self.allDigits or val <= 0 or val >= self.start * 2:
					'''
					this is where I remove the items to either side
					'''
					self.removeVals(self.mid - 1, y)
					self.removeVals(self.mid + 1, y)
					destroy = True
				else:
					self.magicSquare[self.mid][y] = val
					self.allDigits.append(val)
					self.setOpposite(self.mid, y, val)
				
			y += 1
		if destroy:
			self.removeVals(self.mid - 1, 0)
			self.removeVals(self.mid + 1, 0)
			self.removeVals(self.mid, 0)
	'''
	def fillEmpty
	
	params:
	self
	'''
	def fillEmpty(self):
		xOps = [self.mid - 1, self.mid + 1]
		for x in xOps:
			y = 0
			reset = 1
			errorCount = 0
			error = False
			while(y < self.size):
				if self.magicSquare[x][y] == None:
					if y < self.size - 1:
						# this is an empty item
						rand = random.choice(list(set(range(1, self.start * 2)) - set(self.allDigits)))
					else:
						count = 0
						for item in self.magicSquare[x]:
							if item != None:
								count += item
						rand = self.endVals - count
						if rand in self.allDigits or rand <= 0 or rand >= self.start * 2:
							for i in range(0, reset):
								y -= 1
								self.removeVals(x, y)
								self.removeVals(self.mid, y)
							reset += 1
							if reset >= self.size:
								reset = 1
								errorCount += 1
							if errorCount >= self.error:
								error = True
								break
								# raise Exception(f'ERROR: COULD NOT PROCESS COLUMN {x}, point B')
							rand = random.choice(list(set(range(1, self.start * 2)) - set(self.allDigits)))
					self.magicSquare[x][y] = rand
					self.allDigits.append(rand)
					self.setOpposite(x, y, rand)
				y += 1
			if error:
				self.empty()
	'''
	def none
	
	params:
	self
	'''
	def none(self):
		ret = False
		for y in range(0, self.size):
			if self.magicSquare[self.mid][y] == None:
				ret = True
				break
		return ret
	'''
	def operator
	
	params:
	self
	'''
	def operator(self):
		self.setHalf()
		now = time.time()
		while(self.none()):
			end = time.time()
			if (end - now) > 60:
				raise Exception('ERROR: TIMED OUT')
			if not self.errored:
				self.fillEmpty()
			else:
				self.empty()
			if not self.errored:
				self.setRest()
	'''
	def printer
	
	params:
	self
	'''
	def printer(self):
		size = len(str(self.start * 2))
		for i in self.magicSquare:
			for j in i:
				length = len(str(j))
				if length != size:
					for k in range(length, size):
						print('0', end = '')
				print(j, end=', ')
			print('')
	
'''
	Section to get all of the items ready for the program1
'''
a = 0
while (a == 0):
    size = input('Please input an odd number greater than 1: ')
    try:
        if int(size):
            size = int(size)
            if size > 1 and size % 2 == 1:
                a = size
    except:
        print('Please only do numbers')
a = 0
useSize = int((size ** 2) / 2 + 1)
while (a == 0):
    start = input(f'Please input a number greater or equal to {useSize}, or -1 to have a random starting value: ')
    try:
        if int(start):
            start = int(start)
            if start == -1:
                a = -1
            elif start >= useSize:
                a = start
            else:
                print(f'It needs to be greater than or equal to {useSize}')
    except:
        print('Please only do numbers')
try:
	magicSquare =  MagicSquare(size, start)
	magicSquare.operator()
	magicSquare.printer()
except Exception as err:
	print(f'unexpected {err=}, {type(err)=}')
