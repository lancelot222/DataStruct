//
//  Header.h
//  BinaryHeap
//
//  Created by Lancelot Xu on 14/11/5.
//  Copyright (c) 2014年 Lancelot Xu. All rights reserved.
//

/*
 *  小顶堆
 */

#include <vector>
using namespace std;

#ifndef BinaryHeap_Header_h
#define BinaryHeap_Header_h

template <typename Comparable>
class BinaryHeap
{
public:
    explicit BinaryHeap(int capacity = 100);
    explicit BinaryHeap(const vector<Comparable> & items);
    
    bool isEmpty() const;
    const Comparable & findMin() const;
    
    void insert(const Comparable &x);
    void deleteMin();
    void deleteMin(Comparable & minItem);
    void makeEmpty();
    
private:
    int currentSize;
    vector<Comparable> array;
    
    void buildHeap();
    void precoloteDown(int hole);
};

/* --------------------------- 一下是实现部分 ------------------------------- */

template <typename Comparable>
void BinaryHeap<Comparable>::insert(const Comparable &x)
{
    if (currentSize == array.size()-1)
        array.resize( array.size()*2 );
    
    //上滤
    int hole =  ++currentSize;
    for (; hole > 1 && x < array[hole/2]; hole /= 2)
        array[hole] = array[hole/2];
    array[hole] = x;
}

template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin()
{
    if (isEmpty())
        throw UnderflowException(); //这个并没有定义
    
    array[1] = array[currentSize--];
    precoloteDown(1);
}

template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin(Comparable & minItem)
{
    if (isEmpty())
        throw UnderflowException(); //这个并没有定义
    
    minItem = array[1];
    array[1] = array[currentSize--];
    precoloteDown(1);
}

template <typename Comparable>
void BinaryHeap<Comparable>::makeEmpty()
{
    currentSize = 0;
    array.clear();
}

template <typename Comparable>
void BinaryHeap<Comparable>::precoloteDown(int hole)
{
    int child;
    Comparable tmp = array[hole];
    
    for (; hole*2 <= currentSize; hole = child) {
        child = hole*2;
        if (child != currentSize && array[child+1] < array[child])
            child++;
        if (array[child] < tmp)
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = tmp;
}

template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(const vector<Comparable> & items)
{
    for (int i = 0; i < items.size(); i++)
        array[i+1] = items[i];
    buildHeap();
}

template <typename Comparable>
void BinaryHeap<Comparable>::buildHeap()
{
    for (int i = currentSize/2; i > 0; i--)
        precoloteDown(i);
}

#endif
