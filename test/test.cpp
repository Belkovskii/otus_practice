#include <gtest/gtest.h>
#include "../DynamicArray/DynamicArray.h"
#include "../LinkedList/LinkedList.h"

TEST(LinkedListTest, TestSize) {
    //Arrange
    LinkedList<int> ints;
    int expected_size= 11;
    for(int i=0; i<expected_size; ++i) {
        ints.push_back(i);
    }

    //Act
    int actual_size = ints.size();

    //Assert
    ASSERT_EQ(actual_size, expected_size);
}