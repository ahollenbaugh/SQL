#ifndef MAP_H
#define MAP_H

#include "bplustree.h"
#include "pair.h"

template <typename K, typename V>
class Map
{
public:
    // ---------------------------------------------------------------------------------
//    typedef BPlusTree<Pair<K, V> > map_base;
    typedef BPlusTree<Pair<K, V> > bpt_pair;
    class Iterator{
    public:
        friend class Map;
        Iterator(typename bpt_pair::Iterator it): _it(it){
            // left blank
        }
        Iterator operator ++(int unused){
            // left blank
        }
        Iterator operator ++(){
            ++_it;
            return *this;
        }
        Pair<K, V> operator *(){
            return *_it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return (lhs._it == rhs._it);
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return (lhs._it != rhs._it);
        }
    private:
        typename bpt_pair::Iterator _it;

    };
    // ---------------------------------------------------------------------------------

    Map();
//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    V& operator[](const K& key);

//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    V get(const K& key);

//  Operations:
    Iterator find(const K& key);
    bool contains(const Pair<K, V>& target) const;

    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    Iterator lower_bound(const K& key); // return first that goes NOT BEFORE key entry
                                        // or next if does not exist >= entry

    Iterator upper_bound(const K& key); // return first that goes AFTER key
                                        // exist or not, the next entry > entry

    bool is_valid(){return map.is_valid();}

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }
private:
    int key_count;
    bpt_pair map;
};

template <typename K, typename V>
Map<K, V>::Map(){
    const bool debug = false;
    if(debug){
        cout << "Map ctor fired" << endl;
    }
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::begin(){
    Map<K, V>::Iterator it(map.begin());
    return it;
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::end(){
    Map<K, V>::Iterator it(map.end());
    return it;
}

template <typename K, typename V>
int Map<K, V>::size() const{
    return map.size();
    // return key_count
}

template <typename K, typename V>
bool Map<K, V>::empty() const{
    return map.empty();
    // return key_count == 0
}

template <typename K, typename V>
V& Map<K, V>::operator[](const K& key){
    // calls get function from btree
    // if item doesn't exist, throw exception/assert
    return map.get(key).value;
}

template <typename K, typename V>
void Map<K, V>::insert(const K& k, const V& v){
    // build pair with key and value and insert into map
    Pair<K, V> insert_me(k, v);
    map.insert(insert_me);
}

template <typename K, typename V>
void Map<K, V>::erase(const K& key){
    //
}

template <typename K, typename V>
void Map<K, V>::clear(){
    map.clear_tree();
}

template <typename K, typename V>
V Map<K, V>::get(const K& key){
    Pair<K, V> p(key);
    return map.get(p).value;
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::find(const K& key){
    //
}

template <typename K, typename V>
bool Map<K, V>::contains(const Pair<K, V>& target) const{
    return map.contains(target);
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::lower_bound(const K& key){
    //
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::upper_bound(const K& key){
    //
}

#endif // MAP_H
