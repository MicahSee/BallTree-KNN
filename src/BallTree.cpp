#include "BallTree.hpp"
#include <iostream>


BallTree::BallTree(const std::vector<Point>& points, int k_dims, int points_per_leaf) : k_dimensions(k_dims), points_per_leaf(points_per_leaf) {
    ProjVec pointDist;
    
    // Construct a vector of points and projection distance
    for (int i = 0; i < points.size(); ++i) {
        pointDist.push_back(std::make_pair(0.0, points[i]));
    }
    
    // Build the ball tree using the internal method
    root = buildTree(pointDist, 0, pointDist.size());
};

// Recursive function to build the ball tree
// TODO: modify the function to use a reference of the point vector
std::unique_ptr<BallNode> BallTree::buildTree(ProjVec pDist, int start, int end) {
    std::cout << "<---------------------->" << std::endl;
    std::cout << "Building tree from " << start << " to " << end << std::endl;
    std::cout << "Num Points: " << pDist.size() << std::endl;

    // Print out all the points in the range
    std::cout << "Points in Range: ";

    for (int i = start; i < end; ++i) {
        std::cout << "{";
        for (int j = 0; j < k_dimensions; ++j) {
            std::cout << pDist[i].second.coords[j] << " ";
        }

        std::cout << "} ";
    }
    std::cout << std::endl;

    // Find the centroid and radius, will return to this later
    Point centroid = calculateCentroid(pDist, start, end, k_dimensions);
    double radius = calculateRadius(pDist, centroid, start, end);

    // // Print the centroid and radius
    // std::cout << "Centroid: ";
    // for (int i = 0; i < k_dimensions; ++i) {
    //     std::cout << centroid.coords[i] << " ";
    // }

    // std::cout << "Radius: " << radius << std::endl;

    // Base case: if the number of points is less than the threshold
    if (end - start <= points_per_leaf) {
        std::unique_ptr<BallNode> currNode = std::make_unique<BallNode>(centroid, radius);

        // Add the points to the leaf node
        for (int i = start; i < end; ++i) {
            currNode->children.push_back(pDist[i].second);
        }

        return currNode;
    }

    /* 
    --------------------------------------------------------------------------------------------
    | Partition the points into two groups based on the projection of the points onto the line |
    --------------------------------------------------------------------------------------------
    */

    // TODO: the size of the vector changes here, find a more efficient way to move points between function calls and only need to sort a subset
    // The best solution is most likely to pass a vector of std::vector<std::pair<double, Point>> between the recursive calls and sort that
    partitionPoints(pDist, k_dimensions, start, end);

    // Partition objects into two groups: less than zero and greater or equal to zero
    // TODO: check if the case where dist = 0 is handled correctly
    auto partitionPoint = std::partition(pDist.begin() + start, pDist.begin() + end, [](const std::pair<double, Point>& p) { 
                                            return p.first < 0;
                                        });
    

    // Begin debugging
    std::cout << "Points in New Order: ";

    for (int i = 0; i < pDist.size(); ++i) {
        std::cout << "{";
        for (int j = 0; j < k_dimensions; ++j) {
            std::cout << pDist[i].second.coords[j] << " ";
        }

        std::cout << "} ";
    }
    // End debugging

    std::cout << std::endl;

    std::unique_ptr<BallNode> currNode = std::make_unique<BallNode>(centroid, radius);

    // Build the left and right subtrees
    int mid_idx = partitionPoint - pDist.begin();

    currNode->left = buildTree(pDist, start, start + mid_idx);
    currNode->right = buildTree(pDist, start + mid_idx, end);

    return currNode;
}