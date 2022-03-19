# coding:utf-8
import csv
data = [
    ("测试1",'软件测试工程师'),
    ("测试2",'软件测试工程师'),
    ("测试3",'软件测试工程师'),
    ("测试4",'软件测试工程师'),
    ("测试5",'软件测试工程师'),
]
f = open('222.csv','w')
writer = csv.writer(f)
for i in data:
    writer.writerow(i)
f.close()
