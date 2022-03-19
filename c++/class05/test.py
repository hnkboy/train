import pandas as pd

df = pd.read_csv('test.csv')
newRows = []
last_val_is_zero = False
tempRow = None
for row in df.iterrows():
    print row
    vals = row[1]
    #print vals['num'] 
    if vals['num'] == 0:
        if not last_val_is_zero:
            vals['user'] = "hahaha"
            tempRow = vals
            last_val_is_zero = True
        else:
            tempRow['user'] = "tmepRow"
    else:
        if tempRow is not None:
            newRows.append(tempRow)
        newRows.append(vals)
        tempRow = None
        last_val_is_zero = False
#print (tempRow)
if tempRow is not None:
    newRows.append(tempRow)
#print (newRows)
    
newData = [[val for val in row] for row in newRows]
newDf = pd.DataFrame(newData, columns=[x for x in newRows[0].keys()])
