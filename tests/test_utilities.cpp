#include "utilities.hpp"
#include <gtest/gtest.h>

int k_dimensions = 3;

TEST(CalculateCentroidTest, BasicTest) {
    std::vector<Point> points = {
        Point({1.0, 2.0, 3.0}),
        Point({4.0, 5.0, 6.0}),
        Point({7.0, 8.0, 9.0})
    };

    Point centroid = calculateCentroid(points, k_dimensions);
    Point expectedCentroid({4.0, 5.0, 6.0});

    EXPECT_EQ(centroid, expectedCentroid);
}

TEST(EuclidianDistanceTest, BasicTest) {
    Point a({1.0, 2.0, 3.0});
    Point b({4.0, 5.0, 6.0});

    double dist = euclidianDistance(&a, &b, k_dimensions);
    double expectedDist = 5.196152;

    EXPECT_NEAR(dist, expectedDist, 0.0001);
}

TEST(DotProductTest, BasicTest) {
    Point a({1.0, 2.0, 3.0});
    Point b({4.0, 5.0, 6.0});

    double dot = dotProduct(&a, &b, k_dimensions);
    double expectedDot = 32.0;

    EXPECT_EQ(dot, expectedDot);
}

TEST(GetRandomIndexTest, BasicTest) {
    std::mt19937 gen(42);
    int max = 10;

    int randomIndex = getRandomIndex(max, gen);
    EXPECT_GE(randomIndex, 0);
    EXPECT_LE(randomIndex, max);
}

TEST(PartitionPointsTest, BasicTest) {
    int k_dimensions = 3;

    std::vector<Point> points = {
        Point({1.0, 0.0, 0.0}),
        Point({-1.0, 0.0, 0.0}),
        Point({0.0, 1.0, 0.0}),
        Point({0.0, -1.0, 0.0})
    };

    std::vector<double> result = partitionPoints(points, k_dimensions);
    
    // Print out the scalar projection
    for (int i = 0; i < points.size(); ++i) {
        std::cout << result[i] << " ";
    }

    EXPECT_EQ(result.size(), points.size());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}