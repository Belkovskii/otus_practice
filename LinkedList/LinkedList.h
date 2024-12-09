#include <iostream>

template <typename T>
class LinkedList;

template <typename T>
class Node
{
    template <typename T>
    friend class LinkedList;

public:
    Node(const T &v)
    {
        value = *(new T(v));
        next_ptr = nullptr;
    }
    Node(const Node &other)
    {
        value = other.value;
        next_ptr = nullptr;
    }
    T &getValue()
    {
        return value;
    }
    Node *const getNextPtr()
    {
        return next_ptr;
    }

private:
    T value;
    Node *next_ptr;
};

template <typename T>
class LinkedList
{
    template <typename T>
    friend std::ostream &operator<<(std::ostream &const, LinkedList<T> &const);

public:
    LinkedList()
    {
        first_ptr = last_ptr = current_iter_ptr = nullptr;
        sizeOfList = 0;
    };
    ~LinkedList()
    {
        deleteAll();
    }
    LinkedList(const LinkedList &other)
    {
        if (this != &other)
        {
            for (int i = 0; i < other.sizeOfList; i++)
            {
                this->push_back(other[i]);
            }
        }
    }
    LinkedList &operator=(const LinkedList &other)
    {
        if (this != &other)
        {
            if (sizeOfList != 0)
            {
                deleteAll();
            }
            for (int i = 0; i < other.sizeOfList; i++)
            {
                this->push_back(other[i]);
            }
        }
        return *this;
    }
    
    LinkedList(LinkedList&& other) 
    {
        sizeOfList = other.sizeOfList;
        first_ptr = other.first_ptr;
        current_iter_ptr = first_ptr;
        other.current_iter_ptr = other.first_ptr;
        for (int i=0; i<sizeOfList; i++)
        {
            current_iter_ptr->next_ptr = other.current_iter_ptr;
            current_iter_ptr = current_iter_ptr->next_ptr;
            other.current_iter_ptr = other.current_iter_ptr->next_ptr;
        }
        other.first_ptr = nullptr;
        other.sizeOfList 0;
    }

    LinkedList& operator= (LinkedList&& other)
    {
        deleteAll();
        sizeOfList = other.sizeOfList;
        first_ptr = other.first_ptr;
        current_iter_ptr = first_ptr;
        other.current_iter_ptr = other.first_ptr;
        for (int i=0; i<sizeOfList; i++)
        {
            current_iter_ptr->next_ptr = other.current_iter_ptr;
            current_iter_ptr = current_iter_ptr->next_ptr;
            other.current_iter_ptr = other.current_iter_ptr->next_ptr;
        }
        other.first_ptr = nullptr;
        other.sizeOfList 0;
    }

    void push_back(const T &value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (0 == newNode)
        {
            std::cout << "Could not allocate memory" << std::endl;
            return;
        }
        if (sizeOfList == 0)
        {
            first_ptr = newNode;
            last_ptr = first_ptr;
        }
        else
        {
            last_ptr->next_ptr = newNode;
            last_ptr = last_ptr->next_ptr;
        }
        sizeOfList++;
    }
    void insert(const T &value, int index)
    {
        if (index < 0 || index > sizeOfList)
        {
            std::cout << "Wrong index. Must be in range [0 ; " << size() - 1 << "]" << std::endl;
            return;
        }
        Node<T> *newNode = new Node<T>(value);
        if (0 == newNode)
        {
            std::cout << "Could not allocate memory" << std::endl;
            return;
        }
        current_iter_ptr = first_ptr;
        if (index == 0)
        {
            newNode->next_ptr = first_ptr;
            first_ptr = newNode;
        }
        else if (index == size())
        {
            last_ptr->next_ptr = newNode;
            last_ptr = last_ptr->next_ptr;
        }
        else {
            for (int i = 0; i < index-1; i++)
            {
                current_iter_ptr = current_iter_ptr->next_ptr;
            }
            if (current_iter_ptr != last_ptr)
            {
                newNode->next_ptr = current_iter_ptr->next_ptr;
            }
            current_iter_ptr->next_ptr = newNode;
        }
        sizeOfList++;
    }
    int size()
    {
        return sizeOfList;
    }
    T &const operator[](int index)
    {
        if (index < 0 || index > sizeOfList)
        {
            std::cout << "Wrong index. Must be in range [0 ; " << size() - 1 << "]" << std::endl;
            exit(1);
        }
        current_iter_ptr = first_ptr;
        for (int i = 0; i < index; i++)
        {
            current_iter_ptr = current_iter_ptr->next_ptr;
        }
        return current_iter_ptr->getValue();
    }

    T &const operator[](int index) const
    {
        if (index < 0 || index > sizeOfList)
        {
            std::cout << "Wrong index. Must be in range [0 ; " << size() - 1 << "]" << std::endl;
            exit(1);
        }
        current_iter_ptr = first_ptr;
        for (int i = 0; i < index; i++)
        {
            current_iter_ptr = current_iter_ptr->next_ptr;
        }
        return current_iter_ptr->getValue();
    }

    void erase(int index)
    {
        if (index < 0 || index > sizeOfList)
        {
            std::cout << "Wrong index. Must be in range [0 ; " << size() - 1 << "]" << std::endl;
            exit(1);
        }
        current_iter_ptr = first_ptr;
        for (int i=0; i<index-1; i++)
        {
            current_iter_ptr = current_iter_ptr->next_ptr;
        }
        Node<T>* nodeToDelete = current_iter_ptr->next_ptr;
        if (nodeToDelete != last_ptr)
        {
            current_iter_ptr->next_ptr = nodeToDelete->next_ptr;
        }
        else 
        {
            current_iter_ptr->next_ptr = nullptr;
        }
        delete nodeToDelete;
        sizeOfList--;
    }

private:
    Node<T> *first_ptr;
    Node<T> *last_ptr;
    mutable Node<T> *current_iter_ptr;
    int sizeOfList;
    void deleteAll()
    {
        current_iter_ptr = first_ptr;
        while (current_iter_ptr != nullptr)
        {
            Node<T> *temp = current_iter_ptr;
            current_iter_ptr = current_iter_ptr->next_ptr;
            delete temp;
        }
        sizeOfList = 0;
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &const stream, LinkedList<T> &const ll)
{
    if (ll.sizeOfList == 0)
    {
        stream << "List is empty";
        return stream;
    }
    for (int i = 0; i < ll.sizeOfList; i++)
    {
        stream << ll[i];
        if (i < ll.sizeOfList - 1)
        {
            stream << ", ";
        }
        else
        {
            stream << "\n";
        }
    }
    return stream;
}