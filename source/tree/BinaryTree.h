#ifndef Algorithms_BinaryTree_H_
#define Algorithms_BinaryTree_H_

#include "Tree.h"

template<typename T>
using BinaryTree = Tree<T,2>;

template<typename T>
using BinaryTreePtr = std::shared_ptr<BinaryTree<T>>;

template<typename T>
BinaryTreePtr<T> insert(BinaryTreePtr<T> tree, BinaryTreePtr<T> child){
    if(child->mData <= tree->mData){
        auto leftChild = get_child<0>(tree);
        if(leftChild){
            return insert(leftChild, child);
        }
        
        set_child<0>(tree, child);
        return tree;
    }
    else{
        auto rightChild = get_child<1>(tree);
        if(rightChild){
            return insert(rightChild, child);
        }
        
        set_child<1>(tree, child);
        return tree;
    }
    
    return nullptr;
}

template<typename T>
BinaryTreePtr<T> search(BinaryTreePtr<T> tree, const T& value){
    if(tree->mData == value){
        return tree;
    }
    
    auto leftChild = get_child<0>(tree);
    auto rightChild = get_child<1>(tree);
    
    if(tree->mData > value){
        return leftChild ? search(leftChild, value) : nullptr;
    }
    else{
        return rightChild ? search(rightChild, value) : nullptr;
    }
    return nullptr;
}

template<typename T>
void remove(BinaryTreePtr<T> tree, const T& value){
    auto node = search(tree, value);
    
    if(!node){
        return;
    }
    
    auto leftChild = get_child<0>(node);
    auto rightChild = get_child<1>(node);
    
    if(leftChild == nullptr && rightChild == nullptr){
        auto parent = node->mParent.lock();
        auto nodeIndex = index(parent, node);
        parent->mChildren[nodeIndex] = nullptr;
        node->mParent.reset();
    }
    else if(leftChild != nullptr && rightChild != nullptr){
        // find the left-most leaf of the right child
        auto toSwap = get_child<1>(node);
        while(get_child<0>(toSwap)){
            toSwap = get_child<0>(toSwap);
        }
        
        // move the data
        node->mData =  toSwap->mData;
        // remove the leaf node
        auto parent = toSwap->mParent.lock();
        parent->mChildren[index(parent, toSwap)] = nullptr;
        toSwap->mParent.reset();
    }
    else if(leftChild != nullptr){
        node->mData = leftChild->mData;
        node->mChildren[index(node, leftChild)] = nullptr;
        leftChild->mParent.reset();
    }
    else if(rightChild != nullptr){
        node->mData = rightChild->mData;
        node->mChildren[index(node, rightChild)] = nullptr;
        rightChild->mParent.reset();
    }
}

#endif
