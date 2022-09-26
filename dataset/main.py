import os
import numpy as np
import matplotlib.pyplot as plt

# Change current working directory into file path
path = os.path.dirname(os.path.abspath(__file__))
os.chdir(path)

# Open data
f = open('./rssi_2m_2.txt', 'r')
input = f.readlines()
rssi = np.empty(shape=0)
for line in input:
    rssi = np.append(rssi, int(line[:-1]))
    if rssi.size == 1000 :
        break

print(np.mean(rssi))
print(rssi.size)

plt.axhline(y=np.mean(rssi), color='r', linewidth=1.0)
line = plt.plot(rssi)
plt.setp(line, linewidth=0.5)
plt.show()