import pandas as pd

df = pd.read_excel("data.xlsx", dtype=str)
res = str(len(df))+'\n'
for row in df.values:
    res += f'{row[0]};{row[1]};{int(row[2])};{int(row[3])}\n'

with open('database.dat', mode='w', encoding='cp1251') as file:
    file.write(res)