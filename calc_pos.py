import math
import numpy as np

def calculate(coord, distances):
    origin_dist = distances;
    mA = np.array([[0,0,0],[0,0,0],[0,0,0]], dtype=np.float64)
    mb = np.array([0,0,0], dtype=np.float64)

    # 0123
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
    coord[0],coord[3] = coord[3], coord[0]
    distances = [origin_dist[3],origin_dist[1],origin_dist[2],origin_dist[0]]
    invertedA = np.linalg.inv(mA);
    ret = invertedA @ mb

    # 3120
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
    coord[0],coord[2] = coord[2], coord[0]
    distances = [origin_dist[2],origin_dist[1],origin_dist[3],origin_dist[0]]
    invertedA = np.linalg.inv(mA);
    ret += invertedA @ mb

    # 2130
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
    coord[0],coord[3] = coord[3], coord[0]
    distances = [origin_dist[0],origin_dist[1],origin_dist[3],origin_dist[2]]
    invertedA = np.linalg.inv(mA);
    ret += invertedA @ mb
    
    # 0132
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
    coord[0],coord[1] = coord[1], coord[0]
    coord[3],coord[1] = coord[1], coord[3]
    distances = [origin_dist[1],origin_dist[2],origin_dist[3],origin_dist[0]]
    invertedA = np.linalg.inv(mA);
    ret += invertedA @ mb

    # 1230
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
    coord[0],coord[3] = coord[3], coord[0]
    distances = [origin_dist[0],origin_dist[2],origin_dist[3],origin_dist[1]]
    invertedA = np.linalg.inv(mA);
    ret += invertedA @ mb

    # 0231
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
    coord[2],coord[3] = coord[3], coord[2]
    coord[0],coord[1] = coord[1], coord[0]
    distances = [origin_dist[2],origin_dist[0],origin_dist[1],origin_dist[3]]
    invertedA = np.linalg.inv(mA);
    ret += invertedA @ mb

    # 2013
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
    coord[0],coord[3] = coord[3], coord[0]
    distances = [origin_dist[3],origin_dist[0],origin_dist[1],origin_dist[2]]
    invertedA = np.linalg.inv(mA);
    ret += invertedA @ mb

    # 3012
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
    coord[0],coord[3] = coord[3], coord[0]
    coord[0],coord[2] = coord[2], coord[0]
    distances = [origin_dist[1],origin_dist[0],origin_dist[2],origin_dist[3]]
    invertedA = np.linalg.inv(mA);
    ret += invertedA @ mb

    # 1023
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
    coord[0],coord[3] = coord[3], coord[0]
    distances = [origin_dist[3],origin_dist[0],origin_dist[2],origin_dist[1]]
    invertedA = np.linalg.inv(mA);
    ret += invertedA @ mb

    # 3021
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
    coord[0],coord[3] = coord[3], coord[0]
    coord[2],coord[3] = coord[3], coord[2]
    distances = [origin_dist[1],origin_dist[0],origin_dist[3],origin_dist[2]]
    invertedA = np.linalg.inv(mA);
    ret += invertedA @ mb

    # 1032
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
    coord[0],coord[3] = coord[3], coord[0]
    distances = [origin_dist[2],origin_dist[0],origin_dist[3],origin_dist[1]]
    invertedA = np.linalg.inv(mA);
    ret += invertedA @ mb

    # 2031
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
    ret += invertedA @ mb

    
    return ret/12;

if __name__ == '__main__':
    coord = [[0,0,2],[3,3,1.7],[0,3,1.5],[5,0,1.1]]
    real_dist = [1.73205, 2.34307,  2.29129, 4.12431]

    real_pos = calculate(coord, real_dist)
    print(real_pos)
