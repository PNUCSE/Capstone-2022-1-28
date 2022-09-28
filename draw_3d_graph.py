import matplotlib.pyplot as plt
import numpy as np
import math
import calc_pos as CP

tag_pos = [2,1,0]
coord = [[0,0,2],[3,3,1.7],[0,3,1.5],[5,0,1.1]]
real_dist = [1.73205, 2.34307,  2.29129, 4.12431]
real_dist[0] = math.sqrt((coord[0][0]-tag_pos[0])**2 + (coord[0][1]-tag_pos[1])**2 + (coord[0][2]-tag_pos[2])**2)
real_dist[1] = math.sqrt((coord[1][0]-tag_pos[0])**2 + (coord[1][1]-tag_pos[1])**2 + (coord[1][2]-tag_pos[2])**2)
real_dist[2] = math.sqrt((coord[2][0]-tag_pos[0])**2 + (coord[2][1]-tag_pos[1])**2 + (coord[2][2]-tag_pos[2])**2)
real_dist[3] = math.sqrt((coord[3][0]-tag_pos[0])**2 + (coord[3][1]-tag_pos[1])**2 + (coord[3][2]-tag_pos[2])**2)

print(real_dist)

f = open('./TAG_DIST_4m.txt')
tag_dist = f.readlines()
np_tag_dist = np.array(tag_dist)
dist_4m = np.array([])
for i in np_tag_dist:
    dist_4m = np.append(dist_4m, float(i))


f = open('./TAG_DIST_3m.txt')
tag_dist = f.readlines()
np_tag_dist = np.array(tag_dist)
dist_3m = np.array([])
for i in np_tag_dist:
    dist_3m = np.append(dist_3m, float(i))


f = open('./TAG_DIST_2m_2.txt')
tag_dist = f.readlines()
np_tag_dist = np.array(tag_dist)
dist_2m = np.array([])
for i in np_tag_dist:
    dist_2m = np.append(dist_2m, float(i))


fig = plt.figure()
ax = fig.add_subplot(projection='3d')
for i in range(900,1100):
    dist = [dist_3m[i]/3*real_dist[0], dist_2m[i+50]/2*real_dist[1], dist_2m[i+100]/2*real_dist[2], dist_4m[i]/4*real_dist[3]]
    pos = CP.calculate(coord, dist)
    ax.scatter(pos[0], pos[1], pos[2], color='b')

ax.scatter(tag_pos[0], tag_pos[1], tag_pos[2], color='r')
ax.scatter(coord[0][0], coord[0][1], coord[0][2], color='y')
ax.scatter(coord[1][0], coord[1][1], coord[1][2], color='y')
ax.scatter(coord[2][0], coord[2][1], coord[2][2], color='y')
ax.scatter(coord[3][0], coord[3][1], coord[3][2], color='y')

ax.view_init(30,60)
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.show()
