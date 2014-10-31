//
//  Header.h
//  BinarySearchTree
//
//  Created by Lancelot Xu on 14/10/29.
//  Copyright (c) 2014年 Lancelot Xu. All rights reserved.
//

#ifndef BinarySearchTree_Header_h
#define BinarySearchTree_Header_h

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &rhs);
    ~ BinarySearchTree();
    
    const Comparable & findMin() const;
    const Comparable & findMax() const;
    bool contains(const Comparable &x) const;
    bool isEmpty() const;
    void printTree() const;
    
    void makeEmpty();
    void insert(const Comparable &x);
    void remove(const Comparable &x);
    
    const BinarySearchTree & operator=(const BinarySearchTree & rhs);
    
private:
    struct BinaryNode{
        Comparable element;
        BinaryNode * left;
        BinaryNode & right;
        
        BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
        : element( theElement ), left( lt ), right( rt ){}
    };
    
    BinaryNode * root;
    
    void insert(const Comparable &x, BinaryNode * &t) const;
    void remove(const Comparable &x, BinaryNode * &t) const;
    BinaryNode * findMin(BinaryNode *t) const;
    BinaryNode * findMax(BinaryNode *t) const;
    bool contains(const Comparable &x, BinaryNode *t) const;
    void makeEmpty(BinaryNode * &t);
    void printTree(BinaryNode *t) const;
    BinaryNode * clone(BinaryNode *t) const;
};


/*
 public的成员函数使用调用private递归函数的技术
 
 如果x在树中返回true
 */
template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &x) const
{
    return contains(x, root);
}

/*
 把x插入的树中，忽略掉重复的对象
 */
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x)
{
    insert(x, root);
}

/*
 把x从树中删除
 */
template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x)
{
    remove(x, root);
}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree()
{
    root = nullptr;
}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree &rhs)
{
    (*this) = rhs;
}

template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
    makeEmpty();
}

/*
 深度拷贝
 */
template <typename Comparable>
const BinarySearchTree<Comparable> &
    BinarySearchTree<Comparable>::operator= (const BinarySearchTree &rhs)
{
    if (this != &rhs) {
        makeEmpty();
        root = clone(rhs.root);
    }
}

template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin() const
{
    return findMin(root);
}

template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax() const
{
    return findMax(root);
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const
{
    return root == nullptr;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree() const
{
    printTree(root);
}



/*
 ----------------------------  以下是private方法 ------------------------------------
 */

/*
 内部方法：测试一个对象(x)是否在这棵子树(t)里面
 */
template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x, BinaryNode *t) const
{
    if (t == nullptr)
        return false;
    else if (x < t->element)
        return contains(x, t->left);
    else if (t->element < x)
        return contains(x, t->right);
    else
        return true;
}

/*
 内部方法：找一棵子树里面的最小元素
 递归方法
 */
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *
    BinarySearchTree<Comparable>::findMin(BinaryNode *t) const
{
    if (t == nullptr)
        return nullptr;
    if (t->left == nullptr)
        return t;
    return findmin(t->left);
}

/*
 内部方法：找一棵子树里面的最小大元素
 非递归方法
 */
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *
    BinarySearchTree<Comparable>::findMax(BinaryNode *t) const
{
    if (t != nullptr) {
        while (t->right != nullptr)
            t = t->right;
    }
    return t;
}

/*
 内部方法：把一个对象(x)插入一棵树中(t)
 */
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x, BinaryNode * &t) const
{
    if (t == nullptr)
        t = new BinaryNode(x, nullptr, nullptr);
    else if(x < t->element)
        insert(x, t->left);
    else if(t->element < x)
        insert(x, t->right);
    else
        ; //已经存在了，这里先什么都不做
}

/*
 内部方法：从子树(t)中删除一个对象(x)
 */

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x, BinaryNode * &t) const
{
    if (t == nullptr)
        return;     //没找到
    if (x < t->element)
        remove(x, t->left);
    else if (t->element < x)
        remove(x, t->right);
    else if (t->left != nullptr && t->right != nullptr) //有两个儿子
    {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else
    {
        BinaryNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
        
}

/*
 内部方法：把子树(t)删除
 */

template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode * &t)
{
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

/*
 内部方法：用来克隆子树(t)
 */
template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *
    BinarySearchTree<Comparable>::clone(BinaryNode *t) const
{
    if (t == nullptr)
        return nullptr;
    
    return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

/*
 内部方法：打印子树(t)
 */
template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode *t) const
{
    //放在后面了
}

#endif
