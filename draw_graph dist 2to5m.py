import matplotlib.pyplot as plt
import numpy as np
import math

f = open('./TAG_DIST_4m.txt')

tag_dist = f.readlines()
np_tag_dist = np.array(tag_dist)

print(np_tag_dist)

val_tag_rssi = np.array([])
for i in np_tag_dist:
    if(float(i) < 10): val_tag_rssi = np.append(val_tag_rssi, float(i))

n = 1000
x = range(0,n)
y = val_tag_rssi[0:1000]

print(np.average(y))

# plt.scatter(x,y)
# plt.axhline(np.average(y), c='r')
# plt.show()
