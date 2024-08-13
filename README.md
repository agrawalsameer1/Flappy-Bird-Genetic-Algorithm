# Flappy Bird Genetic Algorithm
A C++ implementation of the Genetic Algorithm to create an AI that can play Flappy Bird

**Description of the Approach:**
Every player within a generation has 4 parameters that operate on 4 inputs: its vertical distance from the roof, its vertical distance from the floor, its vertical distance from the nearest top pipe, and its vertical distance from the nearest bottom pipe. These inputs are normalized, and then fed into the player's "brain", which determines whether, in a given frame, the player should flap or not.

A generation contains 50 such players, and new generations are seeded based on the 5 best performing players from the previous generation. Small mutations are added to each member of a new generation to slowly approach an optimal solution. The allowed size of the mutations decrease as the players get better, so that an overly large mutation does not detract from the player's performance.

Edited video of sample training run: [https://youtu.be/lvPr7DS7sAc](https://youtu.be/lvPr7DS7sAc)
