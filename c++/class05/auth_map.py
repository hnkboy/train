#!/usr/bin/python2

import sys
import csv

path = "data.csv"
def usage():
    message = "Command set auth map by .\n"
    message += "%s [ add | del | set | show]" % (sys.argv[0])
    sys.exit(message)
def show_map(start,end):
    cnt = 0
    f = csv.reader(open(path,'r'))
    for i in f:
        if cnt != 0:
            if i[0] >= start and i[0] <= end:
                message = ''
                isfirst = True 
                jcnt = 0
                for j in i:
                    if jcnt > 1:
                        message = message + "," + j
                    elif jcnt == 0:
                       isfirst = False 
                    elif jcnt == 1:
                        message =  j;
                    jcnt = jcnt + 1
                print (message);
        cnt = cnt + 1
#def add(username, usertype, tragetname, targettype, priority):
def add_map(arg):
    f = csv.reader(open(path,'r'))
    cnt = 0
    for i in f:
        if cnt != 0:
            #username and priority
            if i[1] == arg[0] and i[2] == arg[1] and i[7] == arg[4]:
                print ("ERROR")
                return
        cnt = cnt + 1

    len(open(path).readlines())
    line = []
    line.append(len(open(path).readlines()))
    line.append(arg[0])
    line.append(arg[1])
    line.append("1")
    line.append(arg[2])
    line.append(arg[3])
    line.append("2")
    line.append(arg[4])
    csv_write = csv.writer(open(path, 'a'))
    csv_write.writerow(line)
    print ("OK")
def set_map(arg):
    f = csv.reader(open(path,'r'))
    datalist = []
    cnt = 0
    for i in f:
        if cnt != 0:
            if i[1] == arg[0] and i[2] == arg[1] and i[7] == arg[4]:
                i[4] = arg[2]
                i[5] = arg[3]
        cnt = cnt + 1
        datalist.append(i)
    csv_write = csv.writer(open(path, 'w'))
    csv_write.writerows(datalist)
    print ("OK")
def del_map(arg):
    f = csv.reader(open(path,'r'))
    isdel = False
    datalist = []
    cnt = 0
    for i in f:
        if cnt != 0:
            if i[1] == arg[0] and i[2] == arg[1] and i[4] == arg[2]  and i[5] == arg[3] and i[7] == arg[4]:
                isdel = True
            else:
                datalist.append(i)
            i[0] = cnt;
        else:
            datalist.append(i)
        cnt = cnt + 1
    csv_write = csv.writer(open(path, 'w'))
    csv_write.writerows(datalist)
    if isdel == True:
        print ("OK")
    else:
        print ("ERROR")
if len(sys.argv) < 2:
    command = 'help'
else:
    command = sys.argv[1]


commands = ('add', 'del', 'set', 'show')
if command in ('add'):
    if not len(sys.argv) == 7:
        print ("Option 1 \"%s\" is not correct." % (command))
        sys.exit()
elif command in ('set'):
    if not len(sys.argv) == 7:
        print ("Option 1 \"%s\" is not correct." % (command))
        sys.exit()
elif command in ('del'):
    if not len(sys.argv) == 7:
        print ("Option 1 \"%s\" is not correct." % (command))
        sys.exit()
elif command in ('show'):
    if not len(sys.argv) == 4:
        print ("Option 1 \"%s\" is not correct." % (command))
        sys.exit()
elif command in commands:
    if not len(sys.argv) == 2:
        print ("Option 2 \"%s\" is not correct." % (command))
        sys.exit()
elif command not in commands:
    print ("Option 3 \"%s\" is not correct." % (command))
    print (len(sys.argv))
    usage()
elif command == "help":
    usage()

csvfile = csv.writer(open(path,'a'))
if len(open(path).readlines()) == 0:
    csvfile = csv.writer(open(path,'w'))
    datalist = ["num", "user", "type", "uid", "targetuser", "targettype", "tragetuid", "priority"]
    csvfile.writerow(datalist)

if command == "add":
    l =  sys.argv[2:7]
    add_map(l)
elif command == "del":
    l =  sys.argv[2:7]
    del_map(l)
elif command == "set":
    l =  sys.argv[2:7]
    set_map(l)
elif command == "show":
    show_map(sys.argv[2], sys.argv[2] + sys.argv[3])
