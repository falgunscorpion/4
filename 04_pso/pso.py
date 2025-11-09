import matplotlib.pyplot as plt
import numpy as np

# Particle positions at each iteration (x, y pairs)
iterations = [
    # Iteration 1
    [
        (0.432976, 2.18719),
        (-1.3947, -0.180304),
        (0.497592, 5),
        (-0.639, 1.692),
        (-0.15849, 1.87934),
        (-0.779056, 2.35489),
        (-0.590384, 1.57778),
        (2.92399, -1.12189)
    ],
    # Iteration 2
    [
        (0.224034, 2.00538),
        (-0.288036, 2.43435),
        (0.872552, 5),
        (-0.633652, 1.67944),
        (1.58469, 2.40048),
        (-1.30498, 4.979),
        (-0.476672, 1.31061),
        (1.83381, -0.405594)
    ],
    # Iteration 3
    [
        (2.88744, 3.11066),
        (0.0314424, 0.772685),
        (2.32737, 2.49494),
        (-0.385624, 1.74933),
        (2.89207, 2.79134),
        (1.76907, 3.42218),
        (2.64293, 2.71453),
        (0.540851, 5)
    ]
]

# Global best positions (from fitness values)
gBest_positions = [
    (-0.639, 1.692),       # Iteration 1 best (Particle 4)
    (-0.476672, 1.31061),  # Iteration 2 best (Particle 7)
    (2.89207, 2.79134)     # Iteration 3 best (Particle 5)
]

# Convert to numpy for easy plotting
iterations = [np.array(it) for it in iterations]

# Plot trajectories
plt.figure(figsize=(8, 6))

colors = plt.cm.tab10(np.linspace(0, 1, len(iterations[0])))

for p in range(len(iterations[0])):  # each particle
    traj = np.array([it[p] for it in iterations])
    plt.plot(traj[:,0], traj[:,1], '-o', color=colors[p], label=f'Particle {p+1}')

# Plot Global Bests with red star markers
gBest_positions = np.array(gBest_positions)
plt.plot(gBest_positions[:,0], gBest_positions[:,1], 'r*', markersize=15, label="Global Best")

plt.title("Particle Swarm Optimization - Particle Movement with Global Best")
plt.xlabel("X Position")
plt.ylabel("Y Position")
plt.legend()
plt.grid(True)
plt.show()
