#include "utilities.hpp"
#include <cmath>
#include <random>
#include <stdexcept>
#include <utility>

std::random_device rd;
std::mt19937 gen(rd());

int getRandomIndex(int max, std::mt19937& gen) {
    std::uniform_int_distribution<int> dist(0, max);
    return dist(gen);
}

double euclidianDistance(const Point* a, const Point* b, const int k_dimensions) {
    double dist = 0.0;
    for (int i = 0; i < k_dimensions; ++i) {
        double diff = a->coords[i] - b->coords[i];
        dist += diff * diff;
    }

    return std::sqrt(dist);
}

double dotProduct(const Point* a, const Point* b, const int k_dimensions) {
    double dot = 0.0;
    for (int i = 0; i < k_dimensions; ++i) {
        dot += a->coords[i] * b->coords[i];
    }

    return dot;
}

Point calculateCentroid(const ProjVec& pDist, int start, int end, const int k_dimensions) {
    Point centroid;
    int numPoints = end - start;

    // Sum all coordinates
    for (int i = start; i < end; ++i) {
        for (int j = 0; j < k_dimensions; ++j) {
            centroid.coords[j] += pDist[i].second.coords[j];
        }
    }

    // Divide by the number of points
    for (int i = 0; i < k_dimensions; ++i) {
        centroid.coords[i] /= numPoints;
    }

    return centroid;
};

double calculateRadius(const ProjVec &points, const Point &centroid, int start, int end) {
    double maxDistance = 0.0;

    for (int i = start; i < end; ++i) {
        double distance = points[i].second.dist(centroid);

        if (distance > maxDistance) {
            maxDistance = distance;
        }
    }

    return maxDistance;
};


// TODO: add start and end and modify the function to use them
// refactor all of this to use start and end
void partitionPoints(ProjVec& points, const int k_dimensions, int start, int end) {
    int numPoints = end - start;

    // Check if there are enough points
    if (numPoints < 2) {
        throw std::invalid_argument("At least two points are required.");
    }
    
    // Select a random point
    int randomIndex = getRandomIndex(numPoints - 1, gen);

    Point *randomPoint = &(points[start + randomIndex].second);

    Point *farthestPoint = &(points[start].second);
    double maxDistance = 0.0;

    // Find the farthest point from the random point
    for (int i = start; i < end; ++i) {
        double distance = euclidianDistance(randomPoint, &(points[i].second), k_dimensions);
        if (distance > maxDistance) {
            maxDistance = distance;
            farthestPoint = &(points[i].second);
        }
    }

    // Find the farthest point from the farthest point
    Point* farthestPoint2 = &(points[end - 1].second);
    maxDistance = 0.0;

    for (int i = start; i < end; ++i) {
        double distance = euclidianDistance(farthestPoint, &(points[i].second), k_dimensions);
        if (distance > maxDistance) {
            maxDistance = distance;
            farthestPoint2 = &(points[i].second);
        }
    }

    // Calculate the midpoint of the line connecting the two farthest points
    Point midPoint;
    for (int i = 0; i < k_dimensions; ++i) {
        midPoint.coords[i] = (farthestPoint->coords[i] + farthestPoint2->coords[i]) / 2;
    }

    // Calculate the normal vector defining the hyperplane b/w the midpoint and one of the farthest points
    // Either of the farthest points can be used
    Point hyperplaneNormal;
    for (int i = 0; i < k_dimensions; ++i) {
        hyperplaneNormal.coords[i] = farthestPoint->coords[i] - midPoint.coords[i];
    }

    // Project all points onto the hyperplane normal vector
    for (int i = start; i < end; ++i) {
        double scalarProjection = dotProduct(&hyperplaneNormal, &(points[i].second), k_dimensions);
        points[i].first = scalarProjection;
    }
}