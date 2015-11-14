import numpy
import matplotlib.pyplot as plt
import matplotlib
import sys

x,y = [],[]
u,v = [],[]
fileName = sys.argv[1]
file = open(fileName,'r')
for line in file:
    row = line.split()
    x.append(float(row[0]))
    y.append(float(row[1]))
    u.append(float(row[3]))
    v.append(float(row[4]))

plt.quiver(x,y,u,v)
plt.axes().set_aspect('equal', 'datalim')
matplotlib.pyplot.savefig('vectors.png')
