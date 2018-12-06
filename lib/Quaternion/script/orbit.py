import Quaternion as q
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

if __name__ == '__main__':
    fig = plt.figure()
    ax = fig.add_subplot(111,projection='3d')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    plt.ion()
    plt.show()

    n = 20
    v = []
    u = q.quatd(0, 1, 0, 0)
    r = q.quatd.rotation(360/20, 0, 1, 0)

    for i in range(0, n):
        v.append(u)
        u = r * u * ~r;

    r = q.quatd.rotation(1, 0, 1, 0)

    while(True):
        for i in range(0, len(v)):
            v[i] = r * v[i] * ~r;

        xs = []
        ys = []
        zs = []

        for i in v:
            xs.append(i.x)
            ys.append(i.y)
            zs.append(i.z)

        #print(v)
        ax.clear()
        ax.scatter(xs, ys, zs)
        plt.draw()
        plt.pause(0.00001)
