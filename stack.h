#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
using namespace std;

template <class T>
struct Node {
    T x;
    Node<T>* next;

    explicit Node(T x) : x(x), next(nullptr) {
    }
};


template <class T>
class LinkedList
{
public:
    Node<T>* first;
    Node<T>* last;
    int Size;
    // Node<T>* capacity;
    LinkedList() {
        first = nullptr;
        last = nullptr;
        Size = 0;
        //capacity = 0;
    }

    bool isEmpty() const {
        return !first;
        //return last == nullptr;
    }

    int size() const {
        return Size;
    }

    void push_back(T x) {
        Node<T>* node = new Node<T>(x);

        if (isEmpty()) {
            first = node;
            last = node;
            Size = 1;
            return;
        }

        last->next = node;
        last = node;
        Size++;
    }

    T pop_front() {
        if (isEmpty()) throw "LinkedList::pop_front() - Error: List is empty!";
        Node<T>* node = first;
        first = first->next;
        if (!first) last = nullptr;

        T x = node->x;
        delete node;
        Size--;
        return x;
    }


    void removeByIdx(int idx) {
        if (idx < 0)  throw "LinkedList::removeByIdx() - Error: idx<0!";
        int n = size();
        if (idx >= n)  throw "LinkedList::removeByIdx() - Error: idx>=size()!";
        LinkedList<T> temp;
        for (int i = 0; i < n; i++) {
            T x = pop_front();
            if (i != idx) temp.push_back(x);
        }
        first = temp.first;
        last = temp.last;
        Size = temp.Size;
        temp.first = nullptr;
        temp.last = nullptr;
        temp.Size = 0;
    }



    void show()const {
        Node<T>* node = first;
        while (node) {
            cout << node->x << " ";
            node = node->next;
        }
        cout << endl;
    }


    void show_reverse() const {
        for (int i = size() - 1; i >= 0; i--) {
            cout << operator[](i) << " ";
        }
        cout << endl;
    }

    Node<T>* getFirst() const {
        return first;
    }

    T pop_back() {
       // if (isEmpty()) throw runtime_error("Cannot pop from an empty list.");
        if (isEmpty()) throw "Cannot pop from an empty list.";

        if (first == last) {
            T value = first->x;
            delete first; 
            first = last = nullptr; 
            Size = 0;
            return value;
        }

        Node<T>* current = first;
        while (current->next != last) {
            current = current->next;
        }

        T value = last->x; 
        delete last;
        last = current; 
        last->next = nullptr; 
        Size--; 
        return value;
    }

    T pop() {
        if (isEmpty()) {
            //throw runtime_error("Pop operation attempted on an empty list.");
            throw "Pop operation attempted on an empty list.";
        }

        Node<T>* temp = first;
        T value = first->x;
        first = first->next;

        if (first == nullptr) {
            last = nullptr;
        }

        delete temp;
        return value;
    }

    T& peek_front() const {
        if (isEmpty()) throw "LinkedList::peek_front() - Error: List is empty!";
        return first->x;
    }

    T& peek_back() const {
        if (isEmpty()) throw "LinkedList::peek_back() - Error: List is empty!";
        return last->x;
    }

    T& top() const {
        if (isEmpty()) throw "LinkedList::top() - Error: List is empty!";
        return last->x;
    }

    void clear() {
        Node<T>* current = first;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        first = nullptr;
        last = nullptr;
        Size = 0;
    }


    T& operator[](int idx) {
        if (idx < 0)     throw "LinkedList::operator[](int idx) - Error: idx<0!";
        if (idx >= Size) throw "LinkedList::operator[](int idx) - Error: idx >= Size!";
        int cnt = 0;
        Node<T>* node = first;
        while (cnt < idx) {
            node = node->next;
            cnt++;
        }
        return node->x;
    }

    const T& operator[](int idx) const {
        if (idx < 0)     throw "LinkedList::operator[](int idx) - Error: idx<0!";
        if (idx >= Size) throw "LinkedList::operator[](int idx) - Error: idx >= Size!";
        int cnt = 0;
        Node<T>* node = first;
        while (cnt < idx) {
            node = node->next;
            cnt++;
        }
        return node->x;
    }

    bool isFull() const {
        return top == Size - 1;
    }

    const int indexOf(T x) const {
        int n = size();
        for (int i = 0; i < n; i++) {
            T xx = this->operator[](i);
            if (xx == x) return i;
        }
        return -1;
    }

    virtual ~LinkedList() {
        clear();
    }
};

#endif // LINKEDLIST_H
