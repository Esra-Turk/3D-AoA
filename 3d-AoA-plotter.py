# install python3
# install pip install matplotlib

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation

# Static points
static_points = np.array([
    [-10, 0, 0],
    [10, 0, 0],
    [0, 10, 0],
    [0, -10, 0]
])

# Mobile point data (example path of the mobile node)
mobile_points = np.array([
    [-50, 60, 70],
    [-40, 50, 60],
    [-30, 40, 50],
    [-20, 30, 40],
    [-10, 20, 30],
    [0, 20, 30],
    [10, 20, 30],
    [20, 30, 40],
    [30, 40, 50],
    [40, 50, 60],
    [50, 60, 70],
    [50, 50, 70],
    [50, 40, 70],
    [50, 30, 70],
    [50, 20, 70]
])

def update_graph(num):
    graph._offsets3d = (mobile_points[:num+1, 0], mobile_points[:num+1, 1], mobile_points[:num+1, 2])
    return graph,

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(static_points[:, 0], static_points[:, 1], static_points[:, 2], color='r', label='Static Nodes')
graph = ax.scatter([], [], [], color='b', label='Mobile Node')

# Setting the axes properties
ax.set_xlim3d([-50.0, 50.0])
ax.set_ylim3d([-50.0, 50.0])
ax.set_zlim3d([-50.0, 50.0])
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.legend()

# Creating the Animation object
ani = FuncAnimation(fig, update_graph, frames=len(mobile_points), interval=500, blit=False)

plt.show()
