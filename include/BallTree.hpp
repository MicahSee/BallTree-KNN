#ifndef BALLTREE_HPP
#define BALLTREE_HPP

#include "Point.hpp"
#include <vector>
#include <memory>
#include <queue>
#include <algorithm>
#include <functional>
#include "utilities.hpp"

using DistPointPair = std::pair<double, Point>;

struct BallNode {
    Point point;
    double radius;

    std::unique_ptr<BallNode> left;
    std::unique_ptr<BallNode> right;

    std::vector<Point> children;

    BallNode(const Point& pt, double r) : point(pt), radius(r), left(nullptr), right(nullptr) {}
};

class BallTree {
    public:
        BallTree(const std::vector<Point>& points, int k_dims, int points_per_leaf);
        ~BallTree() = default;

        // KNN search
        std::vector<Point> knnSearch(const Point& target, int k) const;

        // Function to return the root node
        BallNode* getRoot() const {
            return root.get();
        }

    private:
        // BallNode structure using smart pointers
        std::unique_ptr<BallNode> root;
        int k_dimensions;
        int points_per_leaf;

        // Recursive function to build the ball-tree
        std::unique_ptr<BallNode> buildTree(ProjVec points, int start, int end); 

        // Helper function for KNN search
        void knnSearchHelper(const BallNode* node, const Point& target, int k,
                            std::priority_queue<DistPointPair, std::vector<DistPointPair>, std::greater<>>& minHeap) const;
};

#endif // BALLTREE_HPP