#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Tree

#include <boost/test/unit_test.hpp>
#include <iostream>

#include "../Tree.h"
#include "../BinaryTree.h"

BOOST_AUTO_TEST_CASE(test_tree_creation){
    auto root = std::make_shared<Tree<int, 2>>();

    BOOST_CHECK( root->mChildren.size() == 2 );
    for(auto c : root->mChildren){
        BOOST_CHECK( c == nullptr );
    }
}

BOOST_AUTO_TEST_CASE(test_get_child){
    auto root = std::make_shared<Tree<int,2>>();
    root->mChildren[0] = std::make_shared<Tree<int,2>>();
    root->mChildren[1] = std::make_shared<Tree<int,2>>();
    
    BOOST_CHECK( (get_child<0>(root)) == root->mChildren[0] );
    BOOST_CHECK( (get_child<1>(root)) == root->mChildren[1] );
}

BOOST_AUTO_TEST_CASE(test_set_child){
    auto root = std::make_shared<Tree<int,2>>();
    
    BOOST_CHECK( (set_child<0>(root, std::make_shared<Tree<int,2>>())) == nullptr );
    BOOST_CHECK( (set_child<0>(root, std::make_shared<Tree<int,2>>())) != nullptr );
    BOOST_CHECK( (set_child<1>(root, std::make_shared<Tree<int,2>>())) == nullptr );
    
    BOOST_CHECK( (get_child<0>(root)) == root->mChildren[0] );
    BOOST_CHECK( (get_child<1>(root)) == root->mChildren[1] );
    
    BOOST_CHECK( (get_child<0>(root))->mParent.lock() == root );
    BOOST_CHECK( (get_child<1>(root))->mParent.lock() == root );
}

BOOST_AUTO_TEST_CASE(test_binary_tree_insert){
    auto root = std::make_shared<BinaryTree<int>>(1);
    auto left = std::make_shared<BinaryTree<int>>(0);
    auto right = std::make_shared<BinaryTree<int>>(2);
    auto right_right = std::make_shared<BinaryTree<int>>(3);
    
    insert(root, left);
    insert(root, right);
    insert(root, right_right);
    
    BOOST_CHECK( get_child<0>(root) == left );
    BOOST_CHECK( get_child<1>(root) == right );
    
    BOOST_CHECK( get_child<0>(left) == nullptr );
    BOOST_CHECK( get_child<1>(left) == nullptr );
    
    BOOST_CHECK( get_child<0>(right) == nullptr );
    BOOST_CHECK( get_child<1>(right) == right_right );
}

BOOST_AUTO_TEST_CASE(test_binary_tree_search){
    auto root = std::make_shared<BinaryTree<int>>(1);
    auto left = std::make_shared<BinaryTree<int>>(0);
    auto right = std::make_shared<BinaryTree<int>>(2);
    auto right_right = std::make_shared<BinaryTree<int>>(3);
    
    insert(root, left);
    insert(root, right);
    insert(root, right_right);
    
    auto good_tree = search(root, 3);
    auto bad_tree = search(root, 4);
    
    BOOST_CHECK( good_tree == right_right );
    BOOST_CHECK( bad_tree == nullptr );
}

BOOST_AUTO_TEST_CASE(test_binary_tree_remove_leaf){
    /*
            1
          0
     */
    auto root = std::make_shared<BinaryTree<int>>(1);
    auto left = std::make_shared<BinaryTree<int>>(0);
    auto right = std::make_shared<BinaryTree<int>>(2);
    auto right_right = std::make_shared<BinaryTree<int>>(3);
    
    insert(root, left);
    insert(root, right);
    insert(root, right_right);
    
    remove(root, 0);
    BOOST_CHECK( get_child<0>(root) == nullptr );
}

BOOST_AUTO_TEST_CASE(test_binary_tree_remove_one_child_left){
    /*
            2
           1
          0
     */
    
    auto root = std::make_shared<BinaryTree<int>>(2);
    auto one = std::make_shared<BinaryTree<int>>(1);
    auto two = std::make_shared<BinaryTree<int>>(0);
    
    insert(root, one);
    insert(root, two);
    
    remove(root, 1);
    BOOST_CHECK( get_child<0>(root) == one );
    BOOST_CHECK( one->mParent.lock() == root );
    BOOST_CHECK( one->mData == 0 );
    
    BOOST_CHECK( get_child<0>(one) == nullptr );
    BOOST_CHECK( get_child<1>(one) == nullptr );
    BOOST_CHECK( two->mParent.expired() );
}

BOOST_AUTO_TEST_CASE(test_binary_tree_remove_one_child_right){
    /*
        4
       2
        3
     */
    auto root = std::make_shared<BinaryTree<int>>(4);
    auto two = std::make_shared<BinaryTree<int>>(2);
    auto three = std::make_shared<BinaryTree<int>>(3);
    
    insert(root, two);
    insert(root, three);
    
    remove(root, 2);
    BOOST_CHECK( get_child<0>(root) == two );
    BOOST_CHECK( two->mParent.lock() == root );
    BOOST_CHECK( two->mData == 3 );
    
    BOOST_CHECK( get_child<0>(two) == nullptr );
    BOOST_CHECK( get_child<1>(two) == nullptr );
    BOOST_CHECK( three->mParent.expired() );
}

BOOST_AUTO_TEST_CASE(test_binary_tree_remove_two_children){
    /*
             1
           0    5
              3  6
             2 4
     */
    std::vector<BinaryTreePtr<int>> nodes{
        std::make_shared<BinaryTree<int>>(1),   // 0
        std::make_shared<BinaryTree<int>>(0),   // 1
        std::make_shared<BinaryTree<int>>(5),   // 2
        std::make_shared<BinaryTree<int>>(3),   // 3
        std::make_shared<BinaryTree<int>>(6),   // 4
        std::make_shared<BinaryTree<int>>(2),   // 5
        std::make_shared<BinaryTree<int>>(4),   // 6
    };
    for(auto i=1;i<nodes.size();++i)
        insert(nodes[0], nodes[i]);
    
    remove(nodes[0],1);
    BOOST_CHECK( nodes[0]->mData == 2 );
    BOOST_CHECK( nodes[5]->mParent.expired() );
    BOOST_CHECK( get_child<0>(nodes[3]) == nullptr );
}
