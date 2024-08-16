#include <gtest/gtest.h>
#include "DynamicArray.h"

TEST(DynamicArrayTest, InsertTest) {
    DynamicArray<int> array;
    array.insert(10);
    array.insert(20);

    ASSERT_EQ(array.getSize(), 2);
    EXPECT_EQ(array[0], 10);
    EXPECT_EQ(array[1], 20);
}

TEST(DynamicArrayTest, RemoveTest) {
    DynamicArray<int> array;
    array.insert(10);
    array.insert(20);
    array.insert(30);

    array.remove(1);

    ASSERT_EQ(array.getSize(), 2);
    EXPECT_EQ(array[0], 10);
    EXPECT_EQ(array[1], 30);
}

TEST(DynamicArrayTest, ClearTest) {
    DynamicArray<int> array;
    array.insert(10);
    array.insert(20);

    array.clear();

    ASSERT_EQ(array.getSize(), 0);
}

TEST(DynamicArrayTest, OutOfRangeTest) {
    DynamicArray<int> array;
    array.insert(10);

    EXPECT_THROW(array[1], std::out_of_range);
    EXPECT_THROW(array.remove(1), std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
