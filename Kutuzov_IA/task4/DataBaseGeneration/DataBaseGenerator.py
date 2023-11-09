import random as rand
import time as time

Inpf = open("RawItemsList.txt", 'r')
Outf = open("ItemDataBase.txt", 'w')

def IdToCode(Id):
    s = str(Id)
    while len(s) < 4:
        s = "0" + s

    return s

def GenerateCost(seed):
    rand.seed = seed + time.time()
    return int((rand.random() ** 2) * 10000) + 1

def GenerateDiscount(seed):
    rand.seed = seed + time.time()
    return int((rand.random() * 10)) * 5

#Program
n = int(Inpf.readline())

Outf.write(str(n) + "\n")

for i in range(n):
    s = Inpf.readline().replace(" ", "_")
    s = s.replace('\n', '')
    Outf.write(IdToCode(i + 1) + " " + s + " " + str(GenerateCost(i)) + " " + str(GenerateDiscount(i)) + '\n')