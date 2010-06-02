#!/usr/bin/env python2.6

import pygtk
pygtk.require('2.0')
import gtk, gobject, cairo

import sys
sys.path.insert(0, '')

import os, signal

class Screen(gtk.DrawingArea):
    def __init__(self, size, points):
        gtk.DrawingArea.__init__(self)
        self.size = float(size)
        self.points = points

    __gsignals__ = { "expose-event": "override" }

    def do_expose_event(self, event):
        cr = self.window.cairo_create()
        cr.rectangle(event.area.x, event.area.y,
                event.area.width, event.area.height)
        cr.clip()

        self.draw(cr, *self.window.get_size())

    def desenhar(self, cr, w, h):
        todraw = list(self.points)

        init = todraw.pop(0)
        cr.move_to(float(init / self.size) * w, 0)

        total = float(len(todraw))
        i = 1
        while i <= total:
            e = todraw.pop(0)
            hq = (i/total) * h
            wq = (e / self.size) * w
            cr.line_to(wq, hq)
            cr.stroke()
            cr.move_to(wq, hq)
            i += 1

    def draw(self, cr, width, height):
        cr.set_source_rgb(1, 1, 1)
        cr.rectangle(0, 0, width, height)
        cr.fill()

        cr.set_source_rgb(0.0, 0.0, 0.0)

        self.desenhar(cr, width, height)
    def size_request(self):
        (640, 480)

class Drawer():
    def __init__(self, time, size, points):
        self.time = time
        print
        print 'Desenhando:', points
        print 'Tempo total:', time
        self.points = points
        self.main(time, size, points)

    def main(self, time, size, points):
        tela = Screen(size, points)

        self.janela = gtk.Window()
        self.janela.connect("destroy", gtk.main_quit)

        vbox = gtk.VBox(False, 5)
        vbox.set_border_width(0)

        align = gtk.Alignment(0, 0, 0, 0)

        q = ('Tempo total: %d (Posicoes: %s)' % (time, points))

        align.add(gtk.Label(str=q))

        vbox.pack_start(align, False, False, 0)
        vbox.pack_start(tela, True, True, 0)


        tela.set_size_request(640, 480)

        self.janela.add(vbox)
        self.janela.show_all()
        self.janela.present()

    def run(self):
        gtk.main()

if __name__ == "__main__":
    main()
