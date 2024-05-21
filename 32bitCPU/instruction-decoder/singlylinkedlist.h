#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <functional>

template <class T>
class SinglyLinkedList;

template <class S>
std::ostream& operator << (std::ostream&, const SinglyLinkedList<S>&);

template <class S>
std::istream& operator << (std::istream&, SinglyLinkedList<S>&);

template <class T>
class SinglyLinkedList{
private:
    class Node{
    private:
        Node* next;
        T data;

    public:
        Node();
        Node(const T&);

        T getData() const;
        Node* getNext() const;

        void setData(const T&);
        void setNext(Node*);
    };

    Node* anchor;

    bool isValidPos(Node*) const;
    void copyAll(const SinglyLinkedList<T>&);
    void insertData(const T&, Node*);

public:
    typedef Node* position;

    class Exception : public std::exception {
    public:
        explicit Exception(const char* message) : msg(message) {}
        explicit Exception(const std::string& message) : msg(message) {}
        virtual ~Exception() throw() {}

        virtual const char* what() const throw() {
            return msg.c_str();
        }

    private:
        std::string msg;
    };

    SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList<T>&);
    ~SinglyLinkedList();

    bool isEmpty() const;
    void insertData(const T&);
    void insertOrdered(const T&, std::function<int(const T&, const T&)>);

    void deleteData(Node*);

    Node* getFirstPos() const;
    Node* getLastPos() const;
    Node* getNextPos(Node*) const;
    Node* getPrevPos(Node*) const;

    Node* findData(const T&, std::function<int(const T&, const T&)>);
    T retrieve(Node*);

    std::string toString() const;

    void deleteAll();

    void writeToDisk(const std::string&);
    void readToDisk(const std::string&);

    SinglyLinkedList<T>& operator = (const SinglyLinkedList<T>&);

    template <class S>
    friend std::ostream& operator << (std::ostream&, const SinglyLinkedList<S>&);

    template <class S>
    friend std::istream& operator >> (std::istream& is, SinglyLinkedList<S>&);

};


using namespace std;

//*********************** Node Class Implementation *************************
template <class T>
SinglyLinkedList<T>::Node::Node() : next(nullptr){}

template <class T>
SinglyLinkedList<T>::Node::Node(const T& d) : next(nullptr), data(d){}

template <class T>
T SinglyLinkedList<T>::Node::getData() const{
    return data;
}

template <class T>
typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::Node::getNext() const{
    return next;
}

template <class T>
void SinglyLinkedList<T>::Node::setData(const T& d){
    data = d;
}

template <class T>
void SinglyLinkedList<T>::Node::setNext(Node* p){
    next = p;
}


//*********************** SinglyLinkedList Class Implementation *************************

template <class T>
bool SinglyLinkedList<T>::isValidPos(Node* n) const{
    Node* aux(anchor);

    while(aux != nullptr){
        if(aux == n){
            return true;
        }

        aux = aux->getNext();
    }

    return false;
}

template <class T>
void SinglyLinkedList<T>::copyAll(const SinglyLinkedList<T>& l){
    Node *aux(l.anchor);
    Node *last(nullptr);
    Node *newNode;

    while(aux != nullptr){
        newNode = new Node(aux->getData());

        if(newNode == nullptr){
            throw("Memory not Available | copyAll()");
        }

        if(last == nullptr){
            anchor = newNode;
        }else{
            last->setNext(newNode);
        }

        last = newNode;
        aux = aux->getNext();
    }
}


template <class T>
SinglyLinkedList<T>::SinglyLinkedList() : anchor(nullptr){}

template <class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& l) : anchor(nullptr){
    copyAll(l);
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList<T>(){
    deleteAll();
}

template <class T>
bool SinglyLinkedList<T>::isEmpty() const{
    return anchor == nullptr;
}

template <class T>
void SinglyLinkedList<T>::insertData(const T& d){
    insertData(d, getLastPos());
}

template <class T>
void SinglyLinkedList<T>::insertData(const T& d, Node* n){
    if(n != nullptr && !isValidPos(n)){
        throw("Invalid Position | insertData()");
    }

    Node* aux(new Node(d));

    if(aux == nullptr){
        throw("Memory not Available | insertData()");
    }

    if(n == nullptr){
        aux->setNext(anchor);
        anchor = aux;
    }else{
        aux->setNext(n->getNext());
        n->setNext(aux);
    }
}

template <class T>
void SinglyLinkedList<T>::insertOrdered(const T& d, function<int(const T&, const T&)> comp){
    Node* aux(anchor);
    Node* pos(nullptr);

    while(aux != nullptr and comp(d, aux->getData()) > 0){
        pos = aux;
        aux = aux->getNext();
    }

    insertData(d, pos);
}

template <class T>
void SinglyLinkedList<T>::deleteData(Node* n){
    if(!isValidPos(n)) {
        throw Exception("Invalid Position | deleteData()");
    }

    if(n == anchor){
        anchor = anchor->getNext();
    }else{
        getPrevPos(n)->setNext(n->getNext());
    }

    delete n;
}

template <class T>
typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::getFirstPos() const{
    return anchor;
}

template <class T>
typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::getLastPos() const{
    if(isEmpty()) {
        return anchor;
    }

    Node *aux(anchor);

    while(aux->getNext() != nullptr){
        aux = aux->getNext();
    }

    return aux;
}

template <class T>
typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::getPrevPos(Node* n) const{
    if(n == anchor){
        return nullptr;
    }

    Node *aux(anchor);

    while(aux != nullptr and aux->getNext() != n){
        aux = aux->getNext();
    }

    return aux;
}

template <class T>
typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::getNextPos(Node* n) const{
    if(!isValidPos(n)) {
        return nullptr;
    }

    return n->getNext();
}

template <class T>
typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::findData(const T& d, function<int(const T&, const T&)> comp){
    Node *aux(anchor);

    while(aux != nullptr and comp(d, aux->getData()) != 0){
        aux = aux->getNext();
    }

    return aux;
}

template <class T>
T SinglyLinkedList<T>::retrieve(Node* n){
    if(!isValidPos(n)) {
        throw Exception("Invalid Position | retrieve()");
    }

    return n->getData();
}

template <class T>
string SinglyLinkedList<T>::toString() const{
    Node *aux(anchor);
    string result;

    while(aux != nullptr){
        result += aux->getData().toString() + "\n";

        aux = aux->getNext();
    }

    return result;
}

template <class T>
void SinglyLinkedList<T>::deleteAll(){
    Node *aux;

    while(anchor != nullptr){
        aux = anchor;

        anchor = anchor->getNext();

        delete aux;
    }
}

template <class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator = (const SinglyLinkedList<T>& l){
    deleteAll();
    copyAll(l);
    return *this;
}

template <class S>
std::ostream& operator << (std::ostream& os, const SinglyLinkedList<S>& l){
    typename SinglyLinkedList<S>::Node *aux(l.anchor);

    while(aux != nullptr){
        os << aux->getData();
        aux = aux->getNext();

    }

    return os;
}

template <class S>
std::istream& operator >> (std::istream& is, SinglyLinkedList<S>& l){
    l.deleteAll();

    S data;
    typename SinglyLinkedList<S>::Node* last(nullptr);
    typename SinglyLinkedList<S>::Node* aux;

    while(is >> data){
        aux = new typename SinglyLinkedList<S>::Node(data);

        if(aux == nullptr){
            throw("Memory not Available | insertData()");
        }

        if(last == nullptr){
            l.anchor = aux;
        }else{
            last->setNext(aux);
        }
        last = aux;

    }

    is.clear();
    return is;
}

#endif // SINGLYLINKEDLIST_H
