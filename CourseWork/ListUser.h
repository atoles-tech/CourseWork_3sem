#ifndef LISTUSER_H
#define LISTUSER_H

template<typename T>
class ListUser {
public:
    ListUser();
    ~ListUser();
    void push_back(T data);
    void removeAt(int index);
    void clear();
    int getSize() { return Size; }
    T& operator[](const int index);
    ListUser<T>& operator=(ListUser<T>& other);
private:
    template<typename T>
    class Node {
    public:
        Node* pNext;
        T data;

        Node(T data = T(), Node* pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
        }
    };
    int Size;
    Node<T>* head;
};

#endif