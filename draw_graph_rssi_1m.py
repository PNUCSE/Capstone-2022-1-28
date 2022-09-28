import matplotlib.pyplot as plt
import numpy as np
import math

f = open('./TAG_RSSI_1m.txt')

tag_rssi = f.readlines()
np_tag_rssi = np.array(tag_rssi)

print(np_tag_rssi)

val_tag_rssi = np.array([])
for i in np_tag_rssi:
    if -60 < float(i[:-2]) < -40:
        val_tag_rssi = np.append(val_tag_rssi, float(i[:-2]))

n = 500
x = range(0,n)
y = val_tag_rssi[0:500]

plt.scatter(x,y)
plt.axhline(np.average(y), c='r')
plt.show()

