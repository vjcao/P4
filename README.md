# Traveling Salesman Project

## Introduction
This project is separated into three parts and is used for solving the Traveling Salesperson Problem or TSP.

## Part A
Part A implements the minimum spanning tree algorithm, 

## Part B
Part B estimates the length the TSP through the use of heuristics. The specific heuristic used is the arbitrary insertion heuristic refefernced here, https://www2.isye.gatech.edu/~mgoetsch/cali/VEHICLE/TSP/TSP013__.HTM.

## Part C
Part C calculates the actual TSP length through the use of a backtracking algorithm and uses the estimation from Part B as the starting point. Any generated branch for the TSP path with a length that is greater than the estimation or previous smallest TSP will be pruned and a new branch will be selected until the smallest TSP path branch is selected. 
