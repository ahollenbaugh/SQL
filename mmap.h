#ifndef MMAP_H
#define MMAP_H

#include "../../!includes/BPlusTree/bplustree.h"
#include "../../!includes/mpair/mpair.h"

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it){
            //
        }
        Iterator operator ++(int unused){
            //
        }
        Iterator operator ++(){
            //
        }
        MPair<K, V> operator *(){
            //
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            //
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            //
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();

//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    const Vector<V>& operator[](const K& key) const;
    Vector<V>& operator[](const K& key);

//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

//  Operations:
    bool contains(const K& key) const ;
    Vector<V> &get(const K& key);

    Iterator find(const K& key);
    int count(const K& key);
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:



    bool is_valid();

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

    // overloaded == should go here:
    friend bool operator ==(const MMap<K, V>& LHS, const MMap<K, V>& RHS);

private:
    BPlusTree<MPair<K, V> > mmap;
};

template <typename K, typename V>
MMap<K, V>::MMap(){
    // left blank
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::begin(){
    return mmap.begin();
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::end(){
    return mmap.end();
}

template <typename K, typename V>
int MMap<K, V>::size() const{
    return mmap.size();
}

template <typename K, typename V>
bool MMap<K, V>::empty() const{
    return mmap.empty();
}

template <typename K, typename V>
const Vector<V>& MMap<K, V>::operator[](const K& key) const{
    // assert that the key is in the map
    const bool debug = false;
    if(debug){
        cout << "MMap operator[] (const) fired" << endl;
    }
    assert(contains(key));
    return get(key);
}

template <typename K, typename V>
Vector<V>& MMap<K, V>::operator[](const K& key){
    // add new entry if key is not in the map
    const bool debug = false;
    if(debug){
        cout << "MMap operator[] (non-const) fired" << endl;
    }
    if(!contains(key))
        mmap.insert(MPair<K, V>(key));
//        insert(key, V());

    return get(key);
}

template <typename K, typename V>
void MMap<K, V>::insert(const K& k, const V& v){
    MPair<K, V> entry(k, v); // build the MPair given a key and a value
    mmap.insert(entry);
}

template <typename K, typename V>
void MMap<K, V>::erase(const K& key){
    //
}

template <typename K, typename V>
void MMap<K, V>::clear(){
    mmap.clear_tree();
}

template <typename K, typename V>
bool MMap<K, V>::contains(const K& key) const {
    MPair<K, V> entry(key);
    return mmap.contains(entry);
}

template <typename K, typename V>
Vector<V> &MMap<K, V>::get(const K& key){
    MPair<K, V> entry(key); // create new MPair with key and empty vector just in case
    return mmap.get(entry).value_list; // return a reference to the vector belonging to this key
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::find(const K& key){
    //
}

template <typename K, typename V>
int MMap<K, V>::count(const K& key){
    //
}

template <typename K, typename V>
bool MMap<K, V>::is_valid(){
    //
}

template <typename K, typename V>
bool operator ==(const MMap<K, V>& LHS, const MMap<K, V>& RHS){
    if(LHS.mmap == RHS.mmap)
        return true;
    return false;
}

#endif // MMAP_H
