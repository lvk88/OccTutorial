import matplotlib.pyplot as plt
import matplotlib
import sys

x,y = [],[]
fileName = sys.argv[1]
file = open(fileName,'r')
for line in file:
    row = line.split()
    x.append(row[0])
    y.append(row[1])

plt.plot(x,y,'ro')
plt.axes().set_aspect('equal', 'datalim')
matplotlib.pyplot.savefig('points.png')
