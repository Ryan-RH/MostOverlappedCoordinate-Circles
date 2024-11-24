This code was created to find the most overlapped point of a finite number of circles with fixed radii.
The task was initially taken on using a brute-force method of scanning every coordinate point within the area with a specified step size and seeing how many circles overlap that point.
However, this method proved to be inaccurate and incredibly computationally inefficient.

This code managed to decrease the time taken to find the most overlapped point by 99.95% with 100% accuracy for the given data.

It can be adapted for circles with random radii very easily.

WARNING:
This code only finds the circles that have the most overlaps NOT the overlapped coordinate.
Best method is to take the most overlapping circles, create a bounding box and use a smart convergence algorithm to find a coordinate that lies within the region.
Simultaneous equation solver would take too long to compute, rigid scanning would also take too long and possibly inaccurate, random sampling would take just as long.
