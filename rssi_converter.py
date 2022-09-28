import matplotlib.pyplot as plt
import numpy as np
import math

f = open('./TAG_RSSI_1m.txt')

tag_rssi = f.readlines()
np_tag_rssi = np.array(tag_rssi)

print(np_tag_rssi)

val_tag_rssi = np.array([])
for i in np_tag_rssi:
    print(i[:-2])
    val_tag_rssi = np.append(val_tag_rssi, float(i[:-2]))

print(val_tag_rssi)

print(np.average(val_tag_rssi))