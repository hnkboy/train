# -*- coding: utf-8 -*-
import PySimpleGUI as sg
 
# Create some widgets
text = sg.Text("输入设备COM号：")
text_entry = sg.InputText()
ok_btn = sg.Button('OK')
cancel_btn = sg.Button('Cancel')
layout = [[text, text_entry],
          [ok_btn, cancel_btn]]
 
# Create the Window
window = sg.Window('Hello', layout)
 
# Create the event loop
while True:
    event, values = window.read()
    if event in (None, 'Cancel'):
        # User closed the Window or hit the Cancel button
        break
    print(f'Event: {event}')
    print(str(values))
 
window.close()