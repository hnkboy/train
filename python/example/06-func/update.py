import json
x = {"apple", "banana", "cherry"}
y = {"google", "microsoft", "apple"}
z = {"z", "microsoft", "apple"}
types = {}
x.update(y)
x.update(z)
#重复的覆盖




print(x)



file_name = "C:\\Users\\Jerry\Documents\\acl.api.json"
with open(file_name) as f:
    j = json.load(f)
    print(j['enums'],"\\\\")

    types.update({d[0]: {'type': 'enum', 'data': d} for d in j['enums']})

print(types)