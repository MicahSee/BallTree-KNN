#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "Point.hpp"
#include <vector>
#include <random>
#include <iostream>

using ProjVec = std::vector<std::pair<double, Point>>;

// Utility function to calculate the centroid
Point calculateCentroid(const ProjVec& points, int start, int end, const int k_dimensions);

// Utility function to calculate the radius
double calculateRadius(const ProjVec& points, const Point& centroid, int start, int end);

double euclidianDistance(const Point* a, const Point* b, const int k_dimensions);

double dotProduct(const Point* a, const Point* b, const int k_dimensions);

int getRandomIndex(int max, std::mt19937& gen);

// Utility function to select a random point, find its farthest neighbor, find the farthest neighbor
// of that point, project the rest of the points onto the line connecting the two farthest points,
// and split the points into two group based on the midpoint of the line
// returns the points and their scalar projection as well as half the distance between the two farthest points
void partitionPoints(ProjVec& points, const int k_dimensions, int start, int end);

#endif // UTILITIES_HPP