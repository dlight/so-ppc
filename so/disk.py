#!/usr/bin/env python2.6

import sys

import disk_gui

def partition(l, pred):
    yes, no = [], []
    for e in l:
        if pred(e):
            yes.append(e)
        else:
            no.append(e)
    return yes, no

class Disk_scheduler:
    def __init__(self, offset, size):
        self.offset = offset
        self.pos = offset
        self.size = size
        self.time = 0
        self.draw = [offset]

    def move(self, dest):
        self.time += abs(self.pos - dest)

        self.draw += [dest]

        print "Movendo de %d a %d (tempo %d)" % \
            (self.pos, dest, self.time)

        self.pos = dest

# First come, first served

class FCFS(Disk_scheduler):
    def schedule(self, read_list):
        for i in read_list:
            self.move(i)

# Shortest seek time first

class SSTF(Disk_scheduler):
    def schedule(self, read_list):
        while read_list:
            read_list.sort(key=lambda x: abs(x - self.pos))
            i = read_list.pop(0)
            self.move(i)

# C-SCAN

class CSCAN(Disk_scheduler):
    def schedule(self, read_list):
        read_list.sort()
        less, more = partition(read_list, lambda x: x < self.pos)
        for i in more:
            self.move(i)
        for i in less:
            self.move(i)

# SCAN

class SCAN(Disk_scheduler):
    def schedule(self, read_list):
        read_list.sort()
        less, more = partition(read_list, lambda x: x < self.pos)
        less.reverse()

        print 'Menor:', less
        print 'Maior:', more

        for i in more:
            self.move(i)
        for i in less:
            self.move(i)


def main():
    sys.argv.pop(0)

    choice = sys.argv.pop(0)

    if choice == 'fcfs':
        print 'Algoritmo: FCFS'

        algorithm = FCFS
    elif choice == 'sstf':
        print 'Algoritmo: SSTF'

        algorithm = SSTF
    elif choice == 'cscan':
        print 'Algoritmo: CSCAN'

        algorithm = CSCAN
    elif choice == 'scan':
        print 'Algoritmo: SCAN'

        algorithm = SCAN

    print

    offset = int(sys.argv.pop(0))
    size = int(sys.argv.pop(0))
    dest = [int(i) for i in sys.argv]

    scheduler = algorithm(offset, size)
    scheduler.schedule(dest)

    drawer = disk_gui.Drawer(scheduler.time, size, scheduler.draw)
    drawer.run()


if __name__ == '__main__':
  main()
