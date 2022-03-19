#coding=UTF-8
import json

info={}
info["code"]=1
info["id"]=1900
info["name"]='张三'
info["sex"]='男'
 
list=[info,info,info]
 
 
data={}
data["code"]=1
data["id"]=1900
data["name"]='张三'
data["sex"]='男'
data["info"]=info
data["data"]=list
 
jsonStr = json.dumps(data)
 
print "jsonStr:",jsonStr
