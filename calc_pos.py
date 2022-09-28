import math
import numpy as np

def calculate(coord, distances):
    mA = np.array([[0,0,0],[0,0,0],[0,0,0]], dtype=np.float64)
    mb = np.array([0,0,0], dtype=np.float64)
    for i in range(3):
        x0 = coord[i][0]
        x1 = coord[i + 1][0]
        y0 = coord[i][1]
        y1 = coord[i + 1][1]
        z0 = coord[i][2]
        z1 = coord[i + 1][2]
        mA[i][0] = 2 * (x1 - x0)
        mA[i][1] = 2 * (y1 - y0)
        mA[i][2] = 2 * (z1 - z0)
        mb[i] = distances[i] * distances[i] - distances[i + 1] * distances[i + 1]
        mb[i] += (x1 * x1 + y1 * y1 + z1 * z1) - (x0 * x0 + + y0 * y0 + z0 * z0)
    invertedA = np.linalg.inv(mA);
    return invertedA @ mb;

if __name__ == '__main__':
    coord = [[0,0,2],[3,3,1.7],[0,3,1.5],[5,0,1.1]]
    real_dist = [1.73205, 2.34307,  2.29129, 4.12431]

    real_pos = calculate(coord, real_dist)
    print(real_pos)
