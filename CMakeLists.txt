cmake_minimum_required(VERSION 3.10)
project(KNNBallTree)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Add your source files
# add_executable(KNNBallTree main.cpp utilities.cpp)

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link Google Test
# target_link_libraries(KNNBallTree ${GTEST_LIBRARIES} pthread)

# Add centroid test executable
# add_executable(test_centroid_calc tests/test_centroid_calc.cpp src/utilities.cpp)
# target_link_libraries(test_centroid_calc ${GTEST_LIBRARIES} pthread)

# Add utilities test executable
# add_executable(test_utilities tests/test_utilities.cpp src/utilities.cpp)
# target_link_libraries(test_utilities ${GTEST_LIBRARIES} pthread)

# Add ball tree test executable
add_executable(test_ball_tree tests/test_ball_tree.cpp src/utilities.cpp src/BallTree.cpp)
target_link_libraries(test_ball_tree ${GTEST_LIBRARIES} pthread)

# Set build type to release
set(CMAKE_BUILD_TYPE Release)

# Disable optimizations and debugging symbols
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -g0")

# Enable testing
enable_testing()

# Add tests
# add_test(NAME CalculateCentroidTest COMMAND test_centroid_calc)
# add_test(NAME UtilitiesTest COMMAND test_utilities)
add_test(NAME BallTreeTest COMMAND test_ball_tree)