#!/usr/bin/env python

# Copyright (c) 2013 Darran Hunt (darran [at] hunt dot net dot nz)
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
# INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
# THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

import sys
from pygame import *
import os
from ocempgui.widgets import *
from ocempgui.widgets.Constants import *

base.GlobalStyle.load("joy.style")

init()
j = joystick.Joystick(0)
j.init()
print 'Initialised Joystick : %s' % j.get_name()
print 'Num axes:',j.get_numaxes();
print 'Num buttons:',j.get_numbuttons();

# Grab current joystick status
event.pump()

class Application():
    def event(self, evt):
        if evt.type == JOYAXISMOTION:
            self.axis[evt.axis].text = 'axis(%d): %f' % (evt.axis, evt.value)
        elif evt.type == JOYBUTTONUP:
            self.button[evt.button].text = 'button(%d): 0' % (evt.button)
        elif evt.type == JOYBUTTONDOWN:
            self.button[evt.button].text = 'button(%d): 1' % (evt.button)

    def createWidgets(self):
        buttonCount = j.get_numbuttons()
        self.table = Table(1, 2 + buttonCount / 8)
        self.table.spacing = 5
        self.table.set_row_align(0, ALIGN_TOP)
        #self.table.set_row_align(1, ALIGN_TOP)

        self.axisFrame = VFrame(Label('Axis'))
        self.axisFrame.align = ALIGN_RIGHT
        self.axisFrame.spacing = 5
        self.axisFrame.boarder = BORDER_SUNKEN
        self.axisFrame.minsize = (150,200)
        for i in range(0, j.get_numaxes()):
            self.axis[i] = Label('axis(%d): %f' % (i, j.get_axis(i)))
            self.axisFrame.add_child(self.axis[i])
        self.table.add_child(0, 0, self.axisFrame)

        for i in range(0, j.get_numbuttons()):
            if (i % 8) == 0:
                frame = VFrame(Label("Buttons %d - %d" % (i, i+7)))
                frame.align = ALIGN_RIGHT
                frame.spacing = 5
                frame.minsize = (110,200)
                self.buttonFrame[i/8] = frame
                self.table.add_child(0, (i / 8) + 1, frame)

            self.button[i] = Label('button(%d): %d' % (i, j.get_button(i)))
            frame.add_child(self.button[i])

        return self.table

    def __init__(self):
        self.axis = {}
        self.button = {}
        self.buttonFrame = {}

def main():
    app = Application()
    re = Renderer()
    re.create_screen(800, 300)
    re.title = 'Joystick monitor'
    re.color = (234, 228, 223)
    re.add_widget(app.createWidgets())

    while True:
        evt = event.wait()
        if evt.type == QUIT:
            j.quit()
            sys.exit ()
        else:
            app.event(evt)

    try:
        j.quit()
    except:
        pass

if __name__ == "__main__":
    main()
