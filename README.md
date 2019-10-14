# Travelling Salesman Project

## Introduction
The travelling salesman problem is one of the most computationally demanding problems to solve. There is no known polynomial time complexity solution to this problem making it an np hard problem. This project is separated into three parts and is used for estimating and solving the TSP.

## Part A
Part A implements the minimum spanning tree algorithm, Prim's algorithm with a twist.

## Part B
Part B estimates the length the TSP through the use of heuristics. The specific heuristic used is the arbitrary insertion heuristic refefernced here, https://www2.isye.gatech.edu/~mgoetsch/cali/VEHICLE/TSP/TSP013__.HTM.

## Part C
Part C calculates the actual TSP length through the use of a backtracking algorithm and uses the estimation from Part B as the starting point. Any generated branch for the TSP path with a length that is greater than the estimation or previous smallest TSP will be pruned and a new branch will be selected until the smallest TSP path branch is selected. 
