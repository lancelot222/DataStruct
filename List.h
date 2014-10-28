//
//  Header.h
//  List
//
//  Created by Lancelot Xu on 14/10/28.
//  Copyright (c) 2014年 Lancelot Xu. All rights reserved.
//

#ifndef List_Header_h
#define List_Header_h

template <typename Object>
class List
{
private:
    struct Node;
    
public:
    class const_iterator;
    class iterator;
    
public:
    List();
    List(const List &rhs);
    ~List();
    
    const List & operator= (const List &rhs);
    
    iterator begin(){
        return iterator(head->next);
    }
    const_iterator begin() const{
        return const_iterator(head->next);
    }
    iterator end(){
        return iterator(tail);
    }
    const_iterator end() const{
        return const_iterator(tail);
    }
    
    int size() const{
        return theSize;
    }
    bool empty() const{
        return size() == 0;
    }
    void clear(){
        while(!empty())
            pop_front();
    }
    
    Object & front(){
        return *begin();
    }
    const Object & front() const{
        return *begin();
    }
    Object & back(){
        return *--end();
    }
    const Object & back() const{
        return *--end();
    }
    
    void push_front(const Object & x){
        insert(begin(), x);
    }
    void push_back(const Object & x){
        insert(end(), x);
    }
    void pop_front(){
        erase(begin());
    }
    void pop_back(){
        erase(--end());
    }
    
    iterator insert(iterator iter, const Object &x);
    iterator erase(iterator iter);
    iterator erase(iterator start, iterator end);
    
private:
    int theSize;
    Node *head;
    Node *tail;
    
    void init();
};

template <typename Object>
struct List<Object>::Node{
    Object data;
    Node *prev;
    Node *next;
    
    Node( const Object & d = Object(), Node *p = nullptr, Node *n = nullptr )
    : data(d), prev(p), next(n) {}
};

template <typename Object>
class List<Object>::const_iterator{
public:
    const_iterator() : current (nullptr) {}
    
    const Object & operator* () const{
        return retrieve();
    }
    
    const_iterator & operator++ ()
    {
        current = current->next;
        return *this;
    }
    
    const_iterator operator++ (int)
    {
        const_iterator old = *this;
        ++(*this);
        return old;
    }
    
    bool operator== (const const_iterator & rhs) const
    {
        return current == rhs.current;
    }
    bool operator!= (const const_iterator & rhs) const
    {
        return !(*this == rhs);
    }
    
protected:
    Node * current;
    
    Object & retrieve() const{
        return current->data;
    }
    
    const_iterator(Node *p) : current(p){}
    
    friend class List<Object>;
};

template<typename Object>
class List<Object>::iterator : const_iterator
{
public:
    iterator(){}
    
    Object & operator* (){
        return const_iterator::retrieve();
    }
    const Object & operator* () const {
        return const_iterator::operator*();
    }
    
    iterator & operator++ (){
        const_iterator::current = const_iterator::current->next;
        return *this;
    }
    
    iterator operator++ (int){
        iterator old = *this;
        ++(*this);
        return old;
    }
    
protected:
    iterator(Node *p): const_iterator(p){}
    
    friend class List<Object>;
};


template<typename Object>
List<Object>::List(){
    init();
}

template<typename Object>
List<Object>::~List()
{
    clear();
    delete head;
    delete tail;
}

template<typename Object>
List<Object>::List(const List & rhs)
{
    init();
    *this = rhs;
}

template<typename Object>
const List<Object> & List<Object>::operator=(const List & rhs)
{
    if (*this == &rhs)
        return *this;
    clear();
    for (const_iterator iter = rhs.begin(); iter != rhs.end(); iter++)
        push_back(*iter);
    return *this;
}

template<typename Object>
void List<Object>::init()
{
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

template<typename Object>
typename List<Object>::iterator List<Object>::insert(iterator iter, const Object &x)
{
    Node *p = iter.current;
    theSize++;
    return iterator(p->prev = p->prev->next = new Node(x, p->prev, p));
}

template<typename Object>
typename List<Object>::iterator List<Object>::erase(iterator iter)
{
    Node *p = iter.current;
    iterator retVal( p->next );
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;
    
    return retVal;
}

template<typename Object>
typename List<Object>::iterator List<Object>::erase(iterator from, iterator to)
{
    for (iterator iter = from; iter != to; iter++) {
        iter = erase(iter);
    }
    return to;
}

#endif
