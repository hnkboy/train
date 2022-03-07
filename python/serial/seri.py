import serial
import time
import binascii
import struct
import math

import pyqtgraph as pg
import array
import numpy as np
from queue import Queue
import threading






def hex_2_short(hexstr):
    width = 16
    intnum=int(hexstr, 16)
    if intnum > 2 ** (width-1)- 1:
        intnum = 2 ** width - intnum
        intnum=0-intnum
    return intnum
    
q = Queue(maxsize=0)

def serialopen():
    global ser;
    portx="COM5"
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
        
def serialread(ser):
    global q;
    ser.flushInput() # 清空缓冲区
    while (True):
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
                        speed = value[4:16]
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
                        q.put(speed)
                time.sleep(0.1)
                ser.flushInput() # 清空缓冲区

            else:
                print("open failed")
                ser.close()#关闭端口
                
i = 0
data = array.array('f') #可动态改变数组的大小,double型数组
#def plotData():
#    global i;
#    global q;
#    global data;
#    if i < historyLength:
#        data[i] = q.get()
#        i = i+1
#    else:
#        data[:-1] = data[1:]
#        data[i-1] = q.get()
#    curve.setData(data)
idx = 0
def plotData():
    global idx#内部作用域想改变外部域变量
    data.append(idx)
    idx += 1
    print(idx)
    curve.setData(data)

 
if __name__ == "__main__":


    portx="COM5"
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
        
    while (True):
        print("read")
        line = ser.readline()
        #count = ser.inWaiting() # 获取串口缓冲区数据
        if line !=0 :
            retstr = ser.read(ser.inWaiting()).hex()
            print(retstr)
        else:
            print("open failed")
            ser.close()#关闭端口   
        
    #th1 = threading.Thread(target=serialread)


    #th1.start()


    
