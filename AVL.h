//
//  Header.h
//  AVL
//
//  Created by Lancelot Xu on 14/10/31.
//  Copyright (c) 2014年 Lancelot Xu. All rights reserved.
//

#ifndef AVL_Header_h
#define AVL_Header_h

/*
 AVL树的节点
 */
struct AvlNode
{
    Comparable element;
    AvlNode *left;
    AvlNode *right;
    int height;
    
    AvlNode(const Comparable & theElement, AvlNode *lt,
                    AvlNode * rt, int h = 0)
    : element(theElement), left(lt), right(rt), height(h){}
};

/*
 返回子树t的高度，NULL返回-1
 */
int height(AvlNode *t) const
{
    return t = nullptr ? -1 : t->height;
}

/*
 把x插入到子树t中
 */
void insert(const Comparable & x, AvlNode * &t)
{
    if (t == nullptr)
        t = new AvlNode(x, nullptr, nullptr);
    else if (x < t->element)
    {
        insert(x, t->left);
        if (height(t->left) - height(t->right) == 2)
            if (x < t->left->element)
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
    }
    else if (t->element < x){
        insert(x, t->right);
        if (height(t->right) - height(t->left) == 2)
            if(t->right->element < x)
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        
    }
    else
        ; //已经存在了
    t->height = max(height(t->left), height(t->right)) + 1;
}

/*
 一种单旋转的情况
 */
void rotateWithLeftChild(AvlNode * &k2)
{
    AvlNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max( height(k2->left), height(k2->right) ) + 1;
    k1->height = max( height(k1->left), k2->height ) + 1;
}

/*
 一种双旋转的情况
 */
void doubleWithLeftChild(AvlNode * &k3)
{
    rotateWithLeftChild(k3->left);
    rotateWithLeftChild(k3);
}

#endif
