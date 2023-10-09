#include <iostream>
#include "LinkedList\LinkedList.h"
#include "DynamicArray\DynamicArray.h"
#include <gtest/gtest.h>

int main() 
{
    
    
    LinkedList<int> ll;
    for (int i=0; i<10; i++)
    {
        ll.push_back(i);
    }
    std::cout << ll << std::endl;
    TEST(TestCheckLinkedList, checkSize) {
        ASSERT_TRUE(ll.size() == 10);
    }
    //ожидаемый результат: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9

    std::cout << ll.size() << "\n\n";
    //ожидаемый результат: 10

    ll.erase(2);
    ll.erase(4-1);
    ll.erase(6-2);
    std::cout << ll << std::endl;
    //ожидаемый результат: 0, 1, 3, 5, 7, 8, 9

    ll.insert(10, 0);
    std::cout << ll << std::endl;
    //ожидаемый результат: 10, 0, 1, 3, 5, 7, 8, 9


    ll.insert(20, 4);
    std::cout << ll << std::endl;
    //ожидаемый результат: 10, 0, 1, 3, 20, 5, 7, 8, 9

    ll.insert(30, ll.size());
    std::cout << ll << std::endl;
    //ожидаемый результат: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30

    std::cout << "--------------" << std::endl;
    
    DynamicArray<int> da;
    for (int i=0; i<10; i++)
    {
        da.push_back(i);
    }
    std::cout << da << std::endl;
    //ожидаемый результат: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9

    std::cout << da.size() << "\n\n";
    //ожидаемый результат: 10

    da.erase(2);
    da.erase(4-1);
    da.erase(6-2);
    std::cout << da << std::endl;
    //ожидаемый результат: 0, 1, 3, 5, 7, 8, 9

    da.insert(10, 0);
    std::cout << da << std::endl;
    //ожидаемый результат: 10, 0, 1, 3, 5, 7, 8, 9


    da.insert(20, 4);
    std::cout << da << std::endl;
    //ожидаемый результат: 10, 0, 1, 3, 20, 5, 7, 8, 9

    da.insert(30, da.size());
    std::cout << da << std::endl;
    //ожидаемый результат: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30

}