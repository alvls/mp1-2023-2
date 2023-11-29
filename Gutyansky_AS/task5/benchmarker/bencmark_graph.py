import json

data = {}

with open('benchmark_result.json', encoding='utf-8') as d:
  data = json.load(d)

import matplotlib.pyplot as plt

x = []
dlines = {}
for i, n in enumerate(data):
    sorts = data[n]
    for sn in sorts:
        if sn not in dlines:
            dlines[sn] = list()
        
        dlines[sn].append(sorts[sn])
    x.append(i + 1)

fig, ax = plt.subplots(nrows=2, ncols=4, sharex = True)

ax[0][1].plot(x, dlines['Пузырьковая'])
ax[0][1].set_title('Пузырьковая')

ax[0][2].plot(x, dlines['Выбором'])
ax[0][2].set_title('Выбором')

ax[0][3].plot(x, dlines['Вставкой'])
ax[0][3].set_title('Вставкой')

ax[1][0].plot(x, dlines['Хоара'])
ax[1][0].set_title('Хоара')

ax[1][1].plot(x, dlines['Шелла'])
ax[1][1].set_title('Шелла')

ax[1][2].plot(x, dlines['Слиянием'])
ax[1][2].set_title('Слиянием')

ax[1][3].plot(x, dlines['Подсчётом'])
ax[1][3].set_title('Подсчётом')

for s in dlines:
    ax[0][0].plot(x, dlines[s], label = s)

ax[0][0].set_title('Общее')
ax[0][0].legend()

plt.show()