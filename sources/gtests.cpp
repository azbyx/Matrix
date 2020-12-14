#define NDEBUG


#include "../headers/matrix.h"
#include "gtest/gtest.h"
//#include "gmock/gmock.h"



TEST(matrix_test, interface_test) {

    ASSERT_EQ(1, 1);
}

int main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}


