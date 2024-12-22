#include <gtest/gtest.h>
#include "../DynamicArray/DynamicArray.h"
#include "../LinkedList/LinkedList.h"


struct LinkedListFixture : public testing::Test {

    size_t original_list_size = 9;

    LinkedList<std::string> l_list;

    void SetUp() override {
        l_list.push_back("A");
        l_list.push_back("B");
        l_list.push_back("C");
        l_list.push_back("D");
        l_list.push_back("E");
        l_list.push_back("F");
        l_list.push_back("G");
        l_list.push_back("H");
        l_list.push_back("I");
    }

    void TearDown() override {
        std::cout << "List deleted" << '\n';
    }
};

struct DynamicArrayFixture : public testing::Test {

    DynamicArray<int> d_array;

    void SetUp() override {        
        d_array.push_back(9);
        d_array.push_back(8);
        d_array.push_back(7);
        d_array.push_back(6);
        d_array.push_back(5);
        d_array.push_back(4);
        d_array.push_back(3);
        d_array.push_back(2);
        d_array.push_back(1);
        d_array.push_back(0);
    }

    void TearDown() override {
        std::cout << "Array deleted" << '\n';
    }

};

TEST(LinkedListTest, CreateLinkedList) {
    //Arrange

    //Act
    LinkedList<int>* ll_ptr = new LinkedList<int>();

    //Assert
    ASSERT_NE(ll_ptr, nullptr);
    delete ll_ptr;    
}

TEST_F(LinkedListFixture, PushBack) {
    //Arrange

    //Act
    l_list.push_back("Z");
    size_t actual_size = l_list.size();
    int last_element_index = static_cast<int>(actual_size - 1);

    //Assert
    ASSERT_EQ(l_list[actual_size-1], "Z");
}

TEST_F(LinkedListFixture, InsertFirst) {
    //Arrange

    //Act
    l_list.insert("Z", 0);

    //Assert
    ASSERT_EQ(l_list[0], "Z");
    ASSERT_EQ(l_list[1], "A");
    ASSERT_EQ(l_list.size(), static_cast<int>(original_list_size+1));
}

TEST_F(LinkedListFixture, InsertMiddle) {
    //Arrange
    int middle_index = static_cast<int>(l_list.size()/2);
    std::string middle_element_before_insert = l_list[middle_index];

    //Act
    l_list.insert("Z", middle_index);

    //Assert
    ASSERT_EQ(l_list[middle_index], "Z");
    ASSERT_EQ(l_list[middle_index+1], middle_element_before_insert);
}

TEST_F(LinkedListFixture, DeleteFromHead) {
    //Arrange

    //Act
    l_list.erase(0);

    //Assert
    ASSERT_EQ(l_list[0], "B");
    ASSERT_EQ(l_list.size(), 8);
    ASSERT_EQ(l_list[l_list.size()-1], "I");
}

TEST_F(LinkedListFixture, DeleteFromMiddle) {
    //Arrange

    //Act
    int size_before_erase = l_list.size();
    l_list.erase(4);
    

    //Assert
    ASSERT_EQ(l_list[3], "D");
    ASSERT_EQ(l_list[4], "F");
    ASSERT_EQ(l_list.size(), --size_before_erase);
}

TEST_F(LinkedListFixture, GetElement) {
    //Arrange

    //Act
    std::string first_element = l_list[0];
    std::string last_element = l_list[l_list.size()-1];

    //Assert
    ASSERT_EQ(first_element, "A");
    ASSERT_EQ(last_element, "I");
}

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

TEST(DynamicArrayTest, CreateDynamicArray) {
    //Arrange

    //Act
    DynamicArray<int> d_a_1;

    d_a_1.push_back(1);
    d_a_1.push_back(2);
    d_a_1.push_back(3);

    DynamicArray<int> d_a_2 = DynamicArray<int>(d_a_1);

    //Assert
    ASSERT_EQ(d_a_2[0], 1);
    ASSERT_EQ(d_a_2[1], 2);    
    ASSERT_EQ(d_a_2[2], 3);    
     
}

TEST_F(DynamicArrayFixture, PushBack) {

    //ARRANGE

    //Act
    d_array.push_back(-1);

    //Assert
    ASSERT_EQ(d_array[10], -1);
}

TEST_F(DynamicArrayFixture, InsertFirst) {
    //Arrange

    //Act
    d_array.insert(5, 0);

    //Assert
    ASSERT_EQ(d_array[0], 5);
    ASSERT_EQ(d_array.size(), 11);
}

TEST_F(DynamicArrayFixture, InsertMiddle) {
    //Arrange

    //Act
    d_array.insert(10, 5);

    //Assert
    ASSERT_EQ(d_array[5], 10);
    ASSERT_EQ(d_array.size(), 11);
}

TEST_F(DynamicArrayFixture, DeleteFromHead) {
    //Arrange

    //Act
    d_array.erase(0);

    //Assert
    ASSERT_EQ(d_array[0], 8);
    ASSERT_EQ(d_array.size(), 9);
}

TEST_F(DynamicArrayFixture, DeleteFromMiddle) {
    //Arrange

    //Act
    d_array.erase(5);

    //Assert
    ASSERT_EQ(d_array[5], 3);
    ASSERT_EQ(d_array.size(), 9);
}
