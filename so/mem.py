#!/usr/bin/env python2.6

import sys

class Block:
    def __init__(self, t, size):
        self.type = t
        self.size = size
    def free(self):
        return self.type == True

class Memory_scheduler:
    def __init__(self, free_blocks):
        self.blocks = \
            [Block(True, i) for i in free_blocks]

    def alloc(self, n, size):
        def insert2(lst, pos, a, b):
            # a = [1, 2, 3, 4]
            # insert2(a, 2, 5, 6)
            # a -> [1, 2, 5, 6, 4]

            lst.pop(pos)
            lst.insert(pos, b)
            lst.insert(pos, a)

        oldsize = self.blocks[n].size

        alloc_block = Block(False, size)
        free_block = Block(True, oldsize - size)

        insert2(self.blocks, n, alloc_block, free_block)

        print "Alocando %d em bloco de tamanho %d (pos %d)" % \
            (size, oldsize, n)

    def schedule(self, alloc_list):
        for i in alloc_list:
            n = self.find(i)
            self.alloc(n, i)

class First_fit(Memory_scheduler):
    def find(self, size):
        i = 0
        while i < len(self.blocks):
            b = self.blocks[i]
            if b.free() and size <= b.size:
                return i
            i += 1
        raise Exception("Sem memoria")

class Best_fit(Memory_scheduler):
    def find(self, size):
        i = 0
        best = None
        best_guess = 10000000
        while i < len(self.blocks):
            b = self.blocks[i]
            if b.free() and size <= b.size and b.size - size < best_guess:
                best = i
                best_guess = b.size - size
            i += 1            

        if best != None:
            return best
        else:
            raise Exception("Sem memoria")

class Worst_fit(Memory_scheduler):
    def find(self, size):
        i = 0
        best = None
        best_guess = -1
        while i < len(self.blocks):
            b = self.blocks[i]
            if b.free() and size <= b.size and b.size - size > best_guess:
                best = i
                best_guess = b.size - size
            i += 1            

        if best != None:
            return best
        else:
            raise Exception("Sem memoria")

free = []
alloc = []

sys.argv.pop(0)

choice = sys.argv.pop(0)

if choice == 'first':
    algorithm = First_fit
elif choice == 'best':
    algorithm = Best_fit
elif choice == 'worst':
    algorithm = Worst_fit

em = free

for i in sys.argv:
    if i == "--":
        em = alloc
    else:
        em.append(int(i))

import mem_gui

def main():
    print 'Blocos livres:', free
    print 'A alocar:', alloc

    print

    scheduler = algorithm(free)
    #print sys.argv

    #alloc = [int(i) for i in sys.argv]
    scheduler.schedule(alloc)

    print

    for i in scheduler.blocks:
        if i.free():
            print 'Bloco livre: %d' % i.size
        else:
            print 'Bloco alocado: %d' % i.size

    drawer = mem_gui.Drawer(scheduler.blocks)
    drawer.run()
    

if __name__ == '__main__':
  main()
