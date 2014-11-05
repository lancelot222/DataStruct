//
//  Header.h
//  ProbHashTable
//
//  Created by Lancelot Xu on 14/11/5.
//  Copyright (c) 2014年 Lancelot Xu. All rights reserved.
//

#include <vector>
using namespace std;

#ifndef ProbHashTable_Header_h
#define ProbHashTable_Header_h

template <typename HashedObject>
class HashTable
{
public:
    explicit HashTable(int size = 101);
    
    bool contains(const HashedObject & x) const;
    
    void makeEmpty();
    bool insert(const HashedObject &x);
    bool remove(const HashedObject &x);
    
    enum EntryType{
        ACTIVE, EMPTY, DELETED
    };
    
private:
    struct HashEntry{
        HashedObject element;
        EntryType info;
        
        HashEntry(const HashedObject & e = HashedObject(), EntryType i = EMPTY)
        : element(e), info(i){}
    };
    
    vector<HashEntry> array;
    int currentSize;
    
    bool isActive(int currentPos) const;
    int findPos(const HashedObject & x) const;
    void rehash();
    int myhash(const HashedObject &x) const;
};

int nextPrime(int);

/* ------------------------------------------------------------------- */

template <typename HashedObject>
HashTable<HashedObject>::HashTable(int size) : array( nextPrime(size) ){
    makeEmpty();
}

template <typename HashedObject>
void HashTable<HashedObject>::makeEmpty()
{
    currentSize = 0;
    for (int i = 0; i < array.size(); i++) {
        array[i].info = EMPTY;
    }
}

template <typename HashedObject>
bool HashTable<HashedObject>::contains(const HashedObject & x) const
{
    return isActive( findPos(x) );
}

template <typename HashedObject>
int HashTable<HashedObject>::findPos(const HashedObject & x) const
{
    int offset = 1;
    int currentPos = myhash(x);
    
    while (array[ currentPos ].info != EMPTY &&
           array[ currentPos ].element != x) {
        currentPos += offset;
        offset += 2;
        if (currentPos >= array.size())
            currentPos -= array.size();
    }
    return currentPos;
}

template <typename HashedObject>
bool HashTable<HashedObject>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}

template <typename HashedObject>
bool HashTable<HashedObject>::insert(const HashedObject & x)
{
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return false;
    
    array[currentPos] = HashEntry(x, ACTIVE);
    
    if (++currentPos > array.size()/2)
        rehash();
    return true;
}

template <typename HashedObject>
bool HashTable<HashedObject>::remove(const HashedObject &x)
{
    int currentPos = findPos(x);
    if (!isActive(currentPos))
        return false;
    
    array[currentPos].info = DELETED;
    return true;
}

template <typename HashedObject>
void HashTable<HashedObject>::rehash()
{
    vector<HashEntry> oldArray = array;
    
    //创建两倍大小的空表
    array.resize( nextPrime(2*oldArray.size()) );
    for (int i = 0; i < array.size(); i++)
        array[i].info = EMPTY;
    
    //拷贝
    for (int i = 0; i < oldArray.size(); i++)
        if (oldArray[i].info == ACTIVE)
            insert(oldArray[i].element);
}


#endif
