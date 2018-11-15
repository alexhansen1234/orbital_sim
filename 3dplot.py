import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
fig = plt.figure()
ax = fig.add_subplot(111,projection='3d')

file = open("parse.txt", "r")
s = file.read()
s = s.replace("(", "")
s = s.replace(")", "")
s = s.replace(" ", "")
s = s.split("\n")
s = list(map(lambda x: x.split(","), s))
s.pop()
s = list(map(lambda x: (float(x[1]), float(x[2]), float(x[3])), s))
xs = [];
ys = [];
zs = [];

for x in s:
    xs.append(x[0])
    ys.append(x[1])
    zs.append(x[2])

ax.scatter(xs, ys, zs)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.show()
