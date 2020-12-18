#ifndef PAIR_H
#define PAIR_H
#include <iostream>
using namespace std;
template <typename K, typename V>
struct Pair
{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V()){
        key = k;
        value = v;
    }
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me){
        outs << print_me.key << " | " << print_me.value;
        return outs;
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        // comparing keys only, right?
        return (lhs.key == rhs.key);
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return (lhs.key < rhs.key);
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return (lhs.key > rhs.key);
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return (lhs.key <= rhs.key);
    }
    friend bool operator >= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return (lhs.key >= rhs.key);
    }
    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        // what is being added exactly?
        // assert for this class so that no one calls it
        // for mpair, if you have two mpairs with the same key,
        // just append the values from one mpair to the
        // values of the other mpair.
        // For example:
        // key: test | values: 1 2 3 4
        // key: test | values: 5 6 7 8
        // After using + operator:
        // key: test | values: 1 2 3 4 5 6 7 8
    }
};

#endif // PAIR_H
