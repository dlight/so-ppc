#!/usr/bin/env python2.6

import pygtk
pygtk.require('2.0')
import gtk, gobject, cairo

import sys
sys.path.insert(0, '')

import os, signal

#import mem

class Screen(gtk.DrawingArea):
    def __init__(self, blocks):
        gtk.DrawingArea.__init__(self)
        self.blocks = blocks

    __gsignals__ = { "expose-event": "override" }

    def do_expose_event(self, event):
        cr = self.window.cairo_create()
        cr.rectangle(event.area.x, event.area.y,
                event.area.width, event.area.height)
        cr.clip()

        self.draw(cr, *self.window.get_size())

    def desenhar(self, cr, w, h):
        todraw = list(self.blocks)

        total = 0

        for i in self.blocks:
            total += i.size

        cr.move_to(0, 0)

        px = 0

        for i in todraw:
            wq = (i.size / float(total)) * w
            if not i.free():
                cr.rectangle(px, 0, wq, h)
                cr.fill()
            px += wq

    def draw(self, cr, width, height):
        cr.set_source_rgb(1, 1, 1)
        cr.rectangle(0, 0, width, height)
        cr.fill()

        cr.set_source_rgb(0.0, 0.0, 0.0)

        #cr.rectangle(10, 20, 30, 40)
        #cr.rectangle( 29.0909090909 , 0, 7.27272727273 , height)
        #cr.fill()

        self.desenhar(cr, width, height)
    def size_request(self):
        (640, 480)

class Drawer():
    def __init__(self, blocks):
        self.blocks = blocks
        self.main(blocks)

    def main(self, blocks):
        tela = Screen(blocks)

        def qm(i):
            if i.free(): return "L"
            else: return "A"

        q = [("%s %d" % (qm(i), i.size)) for i in blocks]

        self.janela = gtk.Window()
        self.janela.connect("destroy", gtk.main_quit)

        vbox = gtk.VBox(False, 5)
        vbox.set_border_width(0)

        align = gtk.Alignment(0, 0, 0, 0)

        align.add(gtk.Label(str=('Blocos: %s' % q)))

        vbox.pack_start(align, False, False, 0)
        vbox.pack_start(tela, True, True, 0)


        tela.set_size_request(640, 200)

        self.janela.add(vbox)
        self.janela.show_all()
        self.janela.present()

    def run(self):
        print 'a'
        gtk.main()

if __name__ == "__main__":
    main()
