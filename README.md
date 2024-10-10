# KNN Ball Tree

This project implements a K-Nearest Neighbors (KNN) search using a Ball Tree data structure. The project includes unit tests using Google Test.

## Features

- Build a Ball Tree from a set of points.
- Perform KNN search on the Ball Tree.
- Unit tests using Google Test.

## Requirements

- C++17
- CMake 3.10 or higher
- Google Test

## Installation

1. **Clone the repository:**

    ```sh
    git clone https://github.com/yourusername/knn-ball-tree.git
    cd knn-ball-tree
    ```

2. **Create a build directory and navigate into it:**

    ```sh
    mkdir build
    cd build
    ```

3. **Run CMake to configure the project:**

    ```sh
    cmake ..
    ```

4. **Build the project:**

    ```sh
    make
    ```

## Usage

### Running the Tests

After building the project, you can run the tests using the following command:

```sh
./test_ball_tree