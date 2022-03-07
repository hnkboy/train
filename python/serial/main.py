# -*- coding: utf-8 -*-
import PySimpleGUI as sg


import threading
import math
import serial
import serial.tools.list_ports
import time
import re

import xlwt
import datetime


global ser

def hex_2_short(hexstr):
    width = 16
    intnum=int(hexstr, 16)
    if intnum > 2 ** (width-1)- 1:
        intnum = 2 ** width - intnum
        intnum=0-intnum
    return intnum

def serialopen(portx):
    bps=230400
    timex=5
    #串口执行到这已经打开 再用open命令会报错
    ser = serial.Serial(portx, int(bps), timeout=1, parity=serial.PARITY_NONE,stopbits=1)
    ser.flushInput() # 清空缓冲区
    if (ser.isOpen()):
        print("open success")
        # 向端口些数据 字符串必须译码
        #ser.write("hello".encode())

    else:
        print("open failed")
        ser.close()#关闭端口
    return ser

flag  = 1
num = 0
def run():
    print(threading.currentThread().getName() + '\n')
    global flag
    global ser
    global worksheet
    global style
    global num
    #seri.serialread(ser)
    flag = 1
    while True:
        ser.flushInput() # 清空缓冲区
        #while (True):
        #line = ser.readline()
        retstr = ser.read(16).hex()
        print(retstr)
        print(type(retstr))
        speed = retstr[20:32];
        speedx =speed[2:4] + speed[0:2];
        speedy =speed[6:8] + speed[4:6];
        speedz =speed[10:12] + speed[8:10];

        speedx = hex_2_short(speedx)
        speedy = hex_2_short(speedy)
        speedz = hex_2_short(speedz)
        speedx = (speedx/32768)*16
        speedy = (speedy/32768)*16
        speedz = (speedz/32768)*16
        print (speedx)
        print (speedy)  
        print (speedz) 
        speed =  math.sqrt(speedx*speedx + speedy*speedy +speedz*speedz)
        print(type(speed))
        print( time.strftime("%Y-%m-%d %X",time.localtime())," --- speed --> ", speed) # 打印一下
        worksheet.write(num, 0, datetime.datetime.now(), style)
        worksheet.write(num, 1, speed)
        
        num  = num +  1
        if flag != 1 :
            break
        
def serialclose():
    ser.close()#关闭端口
    print("close success")

#com=('COM1','COM2','COM3','COM4','COM5','COM6','COM7','COM8','COM9','COM10')
com = list(serial.tools.list_ports.comports())
# Create some widgets
text = sg.Text("输入设备COM号：")
text_entry = sg.InputCombo(com,size=(25, 1),key='-LIST-')
#text_entry = sg.InputText()
ok_btn = sg.Button('open')
close_btn = sg.Button('close')
start_btn = sg.Button('start')
stop_btn = sg.Button('stop')

exit_btn = sg.Button('Exit')
#file_entry = sg.FileSaveAs(
#        key='fig_save',
#        #file_types=(('Excel', '.xls')),  # TODO: better names
#        #file_types=(("Mp3 Files", "*.mp3")), 
#        )

layout = [[text, text_entry, ok_btn, close_btn],
          [start_btn,stop_btn],
          [exit_btn]]
 
# Create the Window
window = sg.Window('Hello Speed', layout)
 
workbook = xlwt.Workbook()
worksheet = workbook.add_sheet('My Sheet')
style = xlwt.XFStyle()
style.num_format_str = 'M/D/YY h:mm:ss' # Other options: D-MMM-YY, D-MMM, MMM-YY, h:mm, h:mm:ss, h:mm, h:mm:ss, M/D/YY h:mm, mm:ss, [h]:mm:ss, mm:ss.0

 
# Create the event loop
while True:
    #value = window.ReadNonBlocking()
    event, values = window.read()
    if event in (None, 'Exit'):
        # User closed the Window or hit the Cancel button
        break


    if event in (None, 'open'):
        portlist = values['-LIST-']
        comport = "".join(portlist) #转换为字符串
        comport = re.findall(r"[(](.*?)[)]",comport)
        ser = serialopen(comport[0])
    if event in (None, 'close'):
        serialclose()
    if event in (None, 'start'):
        #seri.serialread(ser)
        #注意这,开始咯,指明具体的方法和方法需要的参数
        #my_thread = threading.Thread(target=run, args=(ser,))
        my_thread = threading.Thread(target=run)
        #run()
        #一定不要忘记
        my_thread.start()
        print("start ... ")
    if event in (None, 'stop'):
        flag = False
        print("stop ... ")
        filename = time.strftime("%Y%m%d%H%M%S",time.localtime())
        filename = filename + ".xls"
        workbook.save(filename)
        my_thread.join()
        
    print(f'Event: {event}')
    print(str(values))

window.close()