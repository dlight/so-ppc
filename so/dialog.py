#!/usr/bin/env python2.6
import gtk

def callback(self, widget, data=None):
    print "%s was toggled %s" % (data, ("OFF", "ON")[widget.get_active()])

def criar_config():
    window = gtk.Window()
    vbox = gtk.VBox(False, 5)
    vbox.set_border_width(5)
    window.add(vbox)
    window.connect("destroy", lambda x: x.destroy())

    button2 = gtk.RadioButton(None, "radio button1")
    #button2.connect("toggled", callback, "radio button 1")
    #box2.pack_start(button, True, True, 0)
    vbox.add(button2)

    button3 = gtk.RadioButton(button, "radio button1")
    #button.connect("toggled", callback, "radio button 1")
    #box2.pack_start(button, True, True, 0)
    vbox.add(button3)

    def test(self, widget, data=None):
        print button2.get_active()
        print button3.get_active()

    button4 = gtk.Button("close")
    button.connect_object("clicked", test, window,
                              None)

    vbox.add(button4)

    window.show_all()

criar_config()
gtk.main()
