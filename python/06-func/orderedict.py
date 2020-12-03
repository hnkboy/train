from collections import OrderedDict
b={}

#b['a']={"a":"b"}
#b['b']={"a":"b"}
#b['c']={"a":"b"}
b['a']='A'
b['b']='B'
b['c']='C'
for k,v in b.items():
    print("key:{0}".format(k))
    print("value:{0}".format(v))

d = OrderedDict([(1,{"a":"b"}),(3,{"c":"d"}),(2,{"c":"d"})])


for i in d:
    print("key:{0}".format(i))
    print("value:{0}".format(d[i]))


print(d.get(1))
print(d.get(3))

f = OrderedDict()

g = OrderedDict()
h = OrderedDict()
f['a'] = 'A'
f['b'] = 'B'
f['c'] = 'C'

g['a'] = 'A'
g['b'] = 'B'
g['c'] = 'C'

print (f==g)
h['a'] = 'A'
h['c'] = 'C'
h['b'] = 'B'
print (f==h)

a1={}
a2={}
a1['a'] = 'A'
a1['b'] = 'B'
a1['c'] = 'C'


a2['a'] = 'A'
a2['c'] = 'C'
a2['b'] = 'B'
print (a1==a2)
