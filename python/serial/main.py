# -*- coding: utf-8 -*-
import PySimpleGUI as sg


import threading
import math
import serial
import time
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
#def run():
#    #print(threading.currentThread().getName() + '\n')
#    #seri.serialread(ser)
#    ser.flushInput() # 清空缓冲区
#    #while (True):
#    line = ser.readline()
#    #count = ser.inWaiting() # 获取串口缓冲区数据
#    if line !=0 :
#        retstr = ser.read(ser.inWaiting()).hex()
#        print(retstr)
#        retstr = retstr.replace('0d0a41540a','')
#        strlist = retstr.split("00000008")
#        for value in strlist:	# 循环输出列表值
#            print (value)
#            if not value.find('5551'):
#                speed = value[4:16];
#                speedx =speed[2:4] + speed[0:2];
#                speedy =speed[6:8] + speed[4:6];
#                speedz =speed[10:12] + speed[8:10];
#
#                speedx = hex_2_short(speedx)
#                speedy = hex_2_short(speedy)
#                speedz = hex_2_short(speedz)
#                speedx = (speedx/32768)*16
#                speedy = (speedy/32768)*16
#                speedz = (speedz/32768)*16
#                print (speedx)
#                print (speedy)  
#                print (speedz) 
#                speed =  math.sqrt(speedx*speedx + speedy*speedy +speedz*speedz)
#                print(type(speed))
#                print(time.time()," --- speed --> ", speed) # 打印一下子
#                
#        time.sleep(0.1)
        #ser.flushInput() # 清空缓冲区
flag  = 1
def run():
    print(threading.currentThread().getName() + '\n')
    global flag
    global ser
    #seri.serialread(ser)
    flag = 1
    while True:
        ser.flushInput() # 清空缓冲区
        #while (True):
        line = ser.readline()
        #count = ser.inWaiting() # 获取串口缓冲区数据
        if line !=0 :
            retstr = ser.read(ser.inWaiting()).hex()
            print(retstr)
            retstr = retstr.replace('0d0a41540a','')
            strlist = retstr.split("00000008")
            for value in strlist:	# 循环输出列表值
                print (value)
                if not value.find('5551'):
                    speed = value[4:16];
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
                    print(time.time()," --- speed --> ", speed) # 打印一下子
        
            #time.sleep(1)
        if flag != 1 :
            break
        
def serialclose():
    ser.close()#关闭端口
    print("close success")

    
# Create some widgets
text = sg.Text("输入设备COM号：")
text_entry = sg.InputText()
ok_btn = sg.Button('open')
close_btn = sg.Button('close')
start_btn = sg.Button('start')
stop_btn = sg.Button('stop')
exit_btn = sg.Button('Exit')
layout = [[text, text_entry, ok_btn, close_btn],
          [start_btn],[stop_btn],
          [exit_btn]]
 
# Create the Window
window = sg.Window('Hello Speed', layout)
 
# Create the event loop
while True:
    event, values = window.read()
    if event in (None, 'Exit'):
        # User closed the Window or hit the Cancel button
        break


    if event in (None, 'open'):
        ser = serialopen("COM5")
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
        my_thread.join()
        
    print(f'Event: {event}')
    print(str(values))

window.close()