#include "../headers/extended_matrix.h"
#include "gtest/gtest.h"
#include <vector>


TEST(matrix_general, assignment_concatenation) {

    SparseMatrix<int, -1, 3> matrix;

    ((matrix[101][99][100] = 10) = 110) = 1110;

    ASSERT_EQ(matrix[101][99][100],1110);
    ASSERT_EQ(matrix.size(), 1);

}

TEST(matrix_general, traversing_elements_with_non_default_values) {
    const size_t RANK = 4;
    SparseMatrix<int, -1, 4> matrix;
    std::vector<int> valueAccumulator;
    int sumValues{0};

    matrix[1][5][6][6] = 999;
    matrix[2][4][10][8] = 99;
    matrix[1][5][8][10] = 9;
    matrix[2][4][2][7] = -8;
    matrix[1][12][4][9] = -98;
    matrix[2][4][6][8] = -998;

    for(const auto& it : matrix){
        int value = std::get<RANK>(it);
        valueAccumulator.push_back(value);
        sumValues += value;
    }

    ASSERT_EQ(valueAccumulator.size(), 6);
    ASSERT_EQ(sumValues, 3);
}

TEST(matrix_2D, checking_default_value) {

    SparseMatrix<int, 0> matrix;
    const size_t FIRST_RANK = 3;
    const size_t SECOND_RANK = 10;

    for (size_t i = 0; i < FIRST_RANK; i++) {
        for (size_t j = 0; j < SECOND_RANK; j++) {
            ASSERT_EQ(matrix[i][j], 0);
        }
    }

    ASSERT_EQ(matrix.size(), 0);
}

TEST(matrix_2D, insert_remove) {

    SparseMatrix<int, -999> matrix;
    size_t SIZE = 4;

    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
        matrix[i][j] = i * SIZE + j;
        }
    }

    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            ASSERT_EQ(matrix[i][j], i * SIZE + j);
        }
    }

    ASSERT_EQ(SIZE * SIZE, matrix.size());

    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            matrix[i][j] = -999;
        }
    }

    ASSERT_EQ(matrix.size(), 0);
}

TEST(matrix_5D, checking_default_value) {

    SparseMatrix<int, 0, 5> matrix;

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 4; j++) {
            for (size_t k = 0; k < 3; k++) {
                for (size_t m = 0; m < 2; m++) {
                    for (size_t n = 0; n < 3; n++) {
                        ASSERT_EQ(matrix[i][j][k][m][n], 0);
                    }
                }
            }
        }
    }

    ASSERT_EQ(0, matrix.size());
}

TEST(matrix_5D, insert_remove) {

    SparseMatrix<int, -99, 5> matrix;

    matrix[2][5][6][10][1] = 999;
    matrix[2][4][11][8][1] = 99;
    matrix[1][5][9][10][3] = 9;

    ASSERT_EQ(matrix.size(), 3);

    matrix[2][5][6][10][1] = -99;
    matrix[2][4][11][8][1] = -99;
    matrix[1][5][9][10][3] = -99;

    ASSERT_EQ(matrix.size(), 0);
}

int main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
