#include "utilities.hpp"
#include <gtest/gtest.h>

TEST(CalculateCentroidTest, BasicTest) {
    const int k_dimensions = 3;

    std::vector<Point> points = {
        Point({1.0, 2.0, 3.0}),
        Point({4.0, 5.0, 6.0}),
        Point({7.0, 8.0, 9.0})
    };

    Point centroid = calculateCentroid(points, k_dimensions);
    Point expectedCentroid({4.0, 5.0, 6.0});

    EXPECT_EQ(centroid, expectedCentroid);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}