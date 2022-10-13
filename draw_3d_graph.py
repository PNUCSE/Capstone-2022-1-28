import matplotlib.pyplot as plt
import numpy as np
import math
import calc_pos as CP

tag_pos = [2,2,2]
coord = [[0,0,2],[3,3,1.7],[0,3,1.5],[5,0,1.1]]
real_dist = [1.73205, 2.34307,  2.29129, 4.12431]
A=-49.81824806521396
real_dist[0] = math.sqrt((coord[0][0]-tag_pos[0])**2 + (coord[0][1]-tag_pos[1])**2 + (coord[0][2]-tag_pos[2])**2)
real_dist[1] = math.sqrt((coord[1][0]-tag_pos[0])**2 + (coord[1][1]-tag_pos[1])**2 + (coord[1][2]-tag_pos[2])**2)
real_dist[2] = math.sqrt((coord[2][0]-tag_pos[0])**2 + (coord[2][1]-tag_pos[1])**2 + (coord[2][2]-tag_pos[2])**2)
real_dist[3] = math.sqrt((coord[3][0]-tag_pos[0])**2 + (coord[3][1]-tag_pos[1])**2 + (coord[3][2]-tag_pos[2])**2)

print(real_dist)

f = open('./4.txt')
tag_dist = f.readlines()
np_tag_dist = np.array(tag_dist)
dist_4m = np.array([])
for i in np_tag_dist:
    dist_4m = np.append(dist_4m, 10**((A-float(i))/20))


f = open('./3.txt')
tag_dist = f.readlines()
np_tag_dist = np.array(tag_dist)
dist_3m = np.array([])
for i in np_tag_dist:
    dist_3m = np.append(dist_3m, 10**((A-float(i))/20))


f = open('./2.txt')
tag_dist = f.readlines()
np_tag_dist = np.array(tag_dist)
dist_2m = np.array([])
for i in np_tag_dist:
    dist_2m = np.append(dist_2m, 10**((A-float(i))/20))

    
f = open('./1.txt')
tag_dist = f.readlines()
np_tag_dist = np.array(tag_dist)
dist_1m = np.array([])
for i in np_tag_dist:
    dist_1m = np.append(dist_1m, 10**((A-float(i))/20))


fig = plt.figure()
ax = fig.add_subplot(projection='3d')
z_sum = 0
weighted_pos = [0,0,0]
for i in range(1100,1200):
    dist = [dist_3m[i+5000]/3*real_dist[0], dist_2m[i+5050]/2*real_dist[1], dist_2m[i+5100]/2*real_dist[2], dist_4m[i+5000]/4*real_dist[3]]
    tmp = CP.calculate(coord, dist)
    weighted_pos[0] *= 0.5
    weighted_pos[1] *= 0.5
    weighted_pos[2] *= 0.5
    weighted_pos[0] += tmp[0]
    weighted_pos[1] += tmp[1]
    weighted_pos[2] += tmp[2]
    z_sum += tmp[2]

for i in range(1200,1700):
    dist = [dist_3m[i+5000]/3*real_dist[0], dist_2m[i+5050]/2*real_dist[1], dist_2m[i+5100]/2*real_dist[2], dist_4m[i+5000]/4*real_dist[3]]
    tmp = CP.calculate(coord, dist)
    weighted_pos[0] *= 0.5
    weighted_pos[1] *= 0.5
    weighted_pos[2] *= 0.5
    weighted_pos[0] += tmp[0]
    weighted_pos[1] += tmp[1]
    weighted_pos[2] += tmp[2]
    z_sum += tmp[2] 
    # ax.scatter(weighted_pos[0]/2, weighted_pos[1]/2, weighted_pos[2]/2 * 0.2 + z_sum/(100+i-1199) * 0.8 + 4, color='b', s=2)
    ax.scatter(weighted_pos[0]/2, weighted_pos[1]/2, (weighted_pos[2]/2*0.1 + z_sum/(100+i-1199)*0.9) + 4, color='b', s=2)

# for i in range(1200,1300):
#     dist = [dist_2m[i+5100]/2*real_dist[0], dist_2m[i+1050]/2*real_dist[1], dist_2m[i+5100]/2*real_dist[2], dist_4m[i+5000]/4*real_dist[3]]
#     tmp = CP.calculate(coord, dist)
#     ax.scatter(tmp[0], tmp[1], tmp[2], color='b')

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
