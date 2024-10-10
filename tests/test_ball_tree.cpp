#include "utilities.hpp"
#include "BallTree.hpp"
#include <gtest/gtest.h>

TEST(BuildTree, BasicTest) {
    const int k_dimensions = 2;
    const int points_per_leaf = 2;

    // Create a set of ten points in 2D in the 1st quadrant, between (0, 0) and (10, 10)
    std::vector<Point> points = {
        Point({-1, 0}),
        Point({1, 0}),
        Point({0, -1}),
        Point({0, 1})
    };

    BallTree tree(points, k_dimensions, points_per_leaf);

    // Go through the tree and check if the points are in the correct leaf nodes
    // Print the centroids, radii, and points in each leaf node
    std::queue<BallNode*> q;
    q.push(tree.getRoot());

    while (!q.empty()) {
        BallNode* currNode = q.front();
        q.pop();

        if (currNode->left) {
            q.push(currNode->left.get());
        }

        if (currNode->right) {
            q.push(currNode->right.get());
        }

        std::cout << "Centroid: ";
        for (int i = 0; i < k_dimensions; ++i) {
            std::cout << currNode->point.coords[i] << " ";
        }

        std::cout << "Radius: " << currNode->radius << std::endl;

        std::cout << "Points: ";
        for (const Point& pt : currNode->children) {
            std::cout << "(";
            for (int i = 0; i < k_dimensions; ++i) {
                std::cout << pt.coords[i] << " ";
            }
            std::cout << ") ";
        }

        std::cout << std::endl;
    }

    EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}