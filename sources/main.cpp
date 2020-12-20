/**
    \file
    \mainpage Homework 5 of the course "C ++ Developer. Professional" LLC "Otus Online Education"
	\brief Homework 5 of the course "C ++ Developer. Professional" LLC "Otus Online Education"
	\author Bulanov Sergey
	\version 0.0.1
	\date December 2020
	\warning There was done for educational purposes.

*This project is an implementation of the endless sparse matrix.
*/

#include "../headers/extended_matrix.h"
#include <iostream>


int main(int, char**){

    using impl::operator<<;

    using Matrix2D = SparseMatrix<int, 0>;

	const size_t SIZE2D = 10;

	Matrix2D matrix2d;

	for (size_t i = 0; i < SIZE2D; ++i) {
		matrix2d[i][i] = static_cast<int>(i);
        matrix2d[i][SIZE2D - i - 1] = static_cast<int>(SIZE2D - i - 1);
	}

	for (size_t i = 1; i < SIZE2D - 1; ++i) {
		for (size_t j = 1; j < SIZE2D - 1; ++j) {
			std::cout << matrix2d[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << matrix2d.size() << std::endl;

	for (const auto & it : matrix2d)
		std::cout << it << std::endl;

	std::cout << matrix2d[100][100] << std::endl;
	((matrix2d[100][100] = 314) = 0) = 217;
	std::cout << matrix2d[100][100] << std::endl;

    std::cout << "-----------------------------------Optional task-----------------------------------:\n " << std::endl;

	const size_t SIZE4D = 4;

    using Matrix4D = SparseMatrix<int, 0, 4>;

	Matrix4D matrix4d;

	for (size_t i = 0; i < SIZE4D; ++i) {
		matrix4d[i][i][i][i] = 9 - i * 2;
	}

    std::cout << "4x4x4x4 matrix traversal: " << std::endl << std::endl;

	for (size_t i = 0; i < SIZE4D ; ++i) {
		for (size_t j = 0; j < SIZE4D; ++j) {
            for (size_t k = 0; k < SIZE4D; ++k) {
                for (size_t m = 0; m < SIZE4D; ++m) {
                    std::cout << matrix4d[i][j][k][m] << " ";
                }
                std::cout << " ";
            }
            std::cout << std::endl;
		}
		std::cout << std::endl;
	}
    std::cout << "Size of matrix4d: " << matrix4d.size() << std::endl << std::endl;

    std::cout << "Matrix traversal with range for base: " << std::endl;
    for (const auto& it : matrix4d)
		std::cout << it << std::endl;

    (((matrix4d[1][2][3][4] = 11) = 110) = 1110);
    std::cout << std::endl << "Assignment concatenation: matrix4d[1][2][3][4] = 11 = 110 = 1110:" << std::endl << std::endl;
    std::cout << "New value in matrix4d: " << std::endl;

    for (const auto & it : matrix4d)
		std::cout << it << std::endl;

	return 0;
}

