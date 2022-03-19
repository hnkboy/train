#!/usr/bin/python2

import sys
import csv
import json
import collections

path = "data.csv"
def usage():
    message = "Command modify auth map by .\n"
    message += "%s [ add | del | modify | query]" % (sys.argv[0])
    sys.exit(message)
def query_map(start, end):
    info = collections.OrderedDict()
    policy = []
    cnt = 0
    total = 0
    #message = ''
    total = len(open(path).readlines()) - 1
    info["total"] = total
    info["policy"] = policy
    message = "total:" + str(total) 
    f = csv.reader(open(path,'r'))
    for i in f:
        if cnt != 0:   
            if int(i[0]) >= start and int(i[0]) <= end:
                #isfirst = True
                #jcnt = 0
                userinfo = collections.OrderedDict()
                #for j in i:
                #    if jcnt > 1:
                #        message = message + "," + j
                #    elif jcnt == 0:
                #        isfirst = False
                #    elif jcnt == 1:
                #        message =  message + '\n' + j
                #    jcnt = jcnt + 1
                userinfo["id"] = int(i[0])
                userinfo["srcuser"] = i[2]
                userinfo["dstuser"] = i[3]
                userinfo["type"] = i[1]
                userinfo["priority"] = int(i[4])
                policy.append(userinfo)
        cnt = cnt + 1
    print(json.dumps(info,sort_keys=False,indent=2))
    #print (message);
#def add(username, usertype, tragetname, targettype, priority):
def add_map(arg):
    f = csv.reader(open(path,'r'))
    cnt = 0
    for i in f:
        if cnt != 0:
            #username and priority
            if i[1] == arg[0] and i[2] == arg[1] and i[3] == arg[2]:
                print ("ERROR: User map info is exist.")
                return
        cnt = cnt + 1

    line = []
    line.append(len(open(path).readlines()))
    line.append(arg[0])
    line.append(arg[1])
    line.append(arg[2])
    line.append(arg[3])
    csv_write = csv.writer(open(path, 'a'))
    csv_write.writerow(line)
    print ("OK")
def modify_map(arg):
    f = csv.reader(open(path,'r'))
    datalist = []
    cnt = 0
    findhit  = False
    for i in f:
        if cnt != 0:
            if i[1] == arg[0] and i[2] == arg[1] and i[3] == arg[2]:
                findhit  = True
                i[2] = arg[3]
                i[3] = arg[4]
                #print(i[3])
                #print(i[4])
                i[4] = arg[5]
        cnt = cnt + 1
        datalist.append(i)
    if findhit == True :
        csv_write = csv.writer(open(path, 'w'))
        csv_write.writerows(datalist) 
        print ("OK")
    else:
        print ("ERROR: No user map info data.")
def del_map(arg):
    f = csv.reader(open(path,'r'))
    isdel = False
    datalist = []
    cnt = 0
    for i in f:
        if cnt != 0:
            if i[1] == arg[0] and i[2] == arg[1] and i[3] == arg[2]:
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
        print ("ERROR: No user map info data.")
if len(sys.argv) < 2:
    command = 'help'
else:
    command = sys.argv[1]

querydefault = False
commands = ('add', 'del', 'modify', 'query')
#print(len(sys.argv))
if command in ('add'):
    if not len(sys.argv) == 6:
        print ("Option 1 \"%s\" is not correct." % (command))
        sys.exit()
elif command in ('modify'):
    if not len(sys.argv) == 8:
        print ("Option 1 \"%s\" is not correct." % (command))
        sys.exit()
elif command in ('del'):
    if not len(sys.argv) == 5:
        print ("Option 1 \"%s\" is not correct." % (command))
        sys.exit()
elif command in ('query'):
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
    datalist = ["num", "type", "srcuser", "dstuser", "priority"]
    csvfile.writerow(datalist)



if command == "add":
    l =  sys.argv[2:6]
    add_map(l)
elif command == "del":
    l =  sys.argv[2:5]
    del_map(l)
elif command == "modify":
    l =  sys.argv[2:8]
    modify_map(l)
elif command == "query":
    query_map(int(sys.argv[2]), int(sys.argv[2]) + int(sys.argv[3]))

