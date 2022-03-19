# coding:utf-8
import csv
data = [
    ("abc","abs"),
]
f = open('222.csv', 'wb')
writer = csv.writer(f)
for i in data:
    writer.writerow(i)
f.close()
