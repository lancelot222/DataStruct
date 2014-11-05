//
//  Header.h
//  HashTableBySeoarateChain
//
//  Created by Lancelot Xu on 14/11/5.
//  Copyright (c) 2014年 Lancelot Xu. All rights reserved.
//

/* ----------------------------------------------------------------- */
/*
 * 以下是一个可以储存在一般散列表中的Employee类
 */

/*
class Employee
{
public:
    const string & getName() const{
        return name;
    }
    
    bool operator == (const Employee & rhs) const{
        return getName() == rhs.getName();
    }
    
    bool operator != (const Employee & rhs) const{
        return !(*this == rhs);
    }
    
    //应该还有构造函数之类的东西
    
private:
    string name;
    double salary;
    int seniority;
    
    //...
};

int hash(const Employee & item)
{
    return hash(item.getName());
}
*/

/*-----------------  分离链接法来实现 HashTable ------------------------*/

#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

#ifndef HashTableBySeoarateChain_Header_h
#define HashTableBySeoarateChain_Header_h

template <typename HashedObject>
class HashTable
{
public:
    explicit HashTable(int size = 101);
    
    bool contains(const HashedObject & x) const;
    
    void makeEmpty();
    bool insert(const HashedObject & x);
    bool remove(const HashedObject & x);
    
private:
    vector< list<HashedObject> > theLists;
    int currentSize;
    
    void rehash();
    int myhash(const HashedObject &x) const;
};

int hash(const string &key);
int hash(int key);

template <typename HashedObject>
int HashTable<HashedObject>::myhash(const HashedObject & x) const
{
    int hashVal = hash(x);   // 这里要求哈希对象自己有实现哈希函数
    
    hashVal %= theLists.size();
    if (hashVal < 0)
        hashVal += theLists.size();
    
    return hashVal;
}

/* ----------------------------------------------------------------- */
/*
 * 以下是散列表的实现部分
 */

template <typename HashedObject>
void HashTable<HashedObject>::makeEmpty()
{
    for(int i = 0; i < theLists.size(); i++)
        theLists[i].clear();
}

template <typename HashedObject>
bool HashTable<HashedObject>::contains(const HashedObject & x) const
{
    const list<HashedObject> & whichList = theLists[ myhash(x) ];
    return find( whichList.begin(), whichList.end(), x ) != whichList.end();
}

template <typename HashedObject>
bool HashTable<HashedObject>::remove(const HashedObject & x)
{
    list<HashedObject> & whichList = theLists[ myhash(x) ];
    //下一行会报错。。。求解。。。
    list<HashedObject>::iterator iter = find(whichList.begin(), whichList.end(), x);
    
    if (iter == whichList.end())
        return false;
    
    whichList.erase(iter);
    --currentSize;
    return true;
}

template <typename HashedObject>
bool HashTable<HashedObject>::insert(const HashedObject & x)
{
    list<HashedObject> & whichList = theLists[ myhash(x) ];
    if ( find(whichList.begin(), whichList.end(), x) != whichList.end() )
        return false;
    whichList.push_back(x);
    
    //太大就再散列
    if (++currentSize > theLists.size())
        rehash();
    
    return true;
}

template <typename HashedObject>
void HashTable<HashedObject>::rehash()
{
    vector< list<HashedObject> > oldList = theLists;
    
    //创建一个两倍大得空表, nextPrime 待实现
    theLists.resize( nextPrime(2*theLists.size()) );
    for (int j = 0; j < theLists.size(); j++)
        theLists[j].clear();
    
    //拷贝
    currentSize = 0;
    for (int i = 0; i < oldList.size(); i++) {
        list<HashedObject>::iterator iter = oldList[i].begin();
        while(iter != oldList[i].end())
            insert(*iter++);
    }
}


#endif
