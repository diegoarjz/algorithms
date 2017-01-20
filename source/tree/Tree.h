#ifndef Algorithms_Tree_H_
#define Algorithms_Tree_H_

#include <array>

/**
 * Defines a templated tree structure with NChild children and holding
 * data of type T.
 */
template<typename T, int NChild>
class Tree{
public:
    std::array<std::shared_ptr<Tree>,NChild> mChildren;
    std::weak_ptr<Tree> mParent;
    T mData;
    
    Tree(const T& data= T())
    :mData(data){
        
    }
};

template<typename T, int NChild>
using TreePtr = std::shared_ptr<Tree<T,NChild>>;

/**
 * Returns the child of a tree.
 */
template<int child, typename T, int NChild>
TreePtr<T,NChild> get_child(TreePtr<T,NChild> tree){
    return tree->mChildren[child];
}

/**
 * Sets the child of a tree and returns the previous child.
 */
template<int child, typename T, int NChild>
TreePtr<T,NChild> set_child(TreePtr<T,NChild> tree, TreePtr<T,NChild> childTree){
    auto prev = tree->mChildren[child];
    tree->mChildren[child] = childTree;
    childTree->mParent = tree;
    return prev;
}

/**
 * Removes the child of a tree.
 */
template<int child, typename T, int NChild>
void remove_child(TreePtr<T,NChild> tree){
    tree->mChildren[NChild]->mParent.reset();
    tree->mChildren[NChild] = nullptr;
}

/**
 * Gets the index of a given child.
 */
template<typename T, int NChild>
int index(TreePtr<T,NChild> tree, TreePtr<T,NChild> childTree){
    for(size_t i=0; i<tree->mChildren.size(); ++i){
        if(tree->mChildren[i] == childTree){
            return i;
        }
    }
    return -1;
}

#endif
