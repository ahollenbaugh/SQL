#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>

using namespace std;

template <typename T>
struct tree_node{
    T _item;
    tree_node<T>* _left;
    tree_node<T>* _right;
    int _height;

    int balance_factor(){
        // Calculates and returns balance factor.

        //balance factor = height of the right subtree
        //                        - the height of the left subtree
        //a NULL child has a height of -1
        //a leaf has a height of 0

        if(_right && _left)
            return _right->_height - _left->_height;
        if(!_right && _left)
            return -1 - _left->_height;
        if(_right && !_left)
            return _right->_height - (-1);
        if(!_right && !_left)
            return -1 - (-1);
    }

    int height(){
        // Calculates and returns height.

        // Height of a node is 1 + height of the "taller" child
        //A leaf node has a height of zero: 1 + max(-1,-1)

        if(!_left && !_right) // if left and right are null (leaf)
            return 0; // 1 + -1 = 0
        if(!_left && _right) // only left is null
            return 1 + max(-1, _right->_height);
        if(_left && !_right) // only right is null
            return 1 + max(_left->_height, -1);
        return 1 + max(_left->_height, _right->_height); // neither left or right is null
    }
    int update_height(){
        //set the _height member variable (call height();)
        _height = height();
    }

    tree_node(T item=T(), tree_node* left=NULL, tree_node* right=NULL): _item(item), _left(left), _right(right){
        //don't forget to set the _height.
        _height = update_height();

    }
    friend ostream& operator <<(ostream& outs, const tree_node<T>& t_node){
        outs<<"|"<<t_node._item<<"|";
        return outs;
    }
};

#endif // TREE_NODE_H
