from argparse import ONE_OR_MORE
from contextlib import AbstractAsyncContextManager
import matplotlib.pyplot as plt
import numpy as np
import math

f = open('./2m_FILTERED_RSSI_4.txt')
# f = open('./TAG_RSSI_3.txt')
# f = open('./1m_json_5.txt')

#{"name":"TAG","rssi":"-52","val":"86710"}


tag_rssi = f.readlines()
np_tag_rssi = np.array(tag_rssi)

print(np_tag_rssi)

val_tag_rssi = np.array([])
for i in np_tag_rssi:
    if float(i[:-2]):
        val_tag_rssi = np.append(val_tag_rssi, float(i[:-1]))

# for i in np_tag_rssi:
#     if float(i[22:25]):
#         val_tag_rssi = np.append(val_tag_rssi, float(i[22:25]))

n = 1000
x = range(0,1000)
y = val_tag_rssi[-2000:-1000]

plt.scatter(x,y,s=1)
plt.axis([0,1000,-67.5,-47.5])
plt.axhline(np.average(y), c='r')
plt.show()

print(np.average(val_tag_rssi[:]))


a = -49.81824806521396
b = -55.72942739344008
c = -59.35312428634194
d = -61.76477831410016
print(10**((a-b)/20))
print(10**((a-c)/20))
print(10**((a-d)/20))