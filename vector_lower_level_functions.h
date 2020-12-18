#ifndef VECTOR_LOWER_LEVEL_FUNCTIONS_H
#define VECTOR_LOWER_LEVEL_FUNCTIONS_H

#include <iostream>
#include <cassert>
using namespace std;

// PROTOTYPES

template<typename T>
T* add_entry(T* list, const T& new_entry, int& size, int& capacity);

template<typename T>
T* allocate(int capacity);

template<typename T>
T* remove_entry(T* list, int& size, int& capacity);

//template<typename T>
//T* remove_entry(T* list, const T& delete_me, int& size, int& capacity);

template<typename T>
void copy_list(T *dest, T* src, int many_to_copy);

template<typename T>
T* search_list(T* list, const T& find_me, int size);

template<typename T>
void print_list(T* list, int size);

template<typename T>
void test_string();

// DEFINITIONS ------------------------------------------------------------------------------------------

template<typename T>
T* add_entry(T* list, const T& new_entry, int& size, int& capacity){
    // double the space when you run out of room
    // is new_entry just being appended to the array?
    // Assuming it is...
    // add first then allocate?
    // should I check if size == capacity first?
    //
    const bool debug = false;
    if(debug){
        cout<<"Before add_entry"<<endl;
        cout<<"size: "<<size<<endl;
        cout<<"capacity: "<<capacity<<endl;
    }
    T *new_list;
    list[size] = new_entry;
    size++;
    if(size == capacity){
        capacity *= 2;
        new_list = allocate<T>(capacity);
        copy_list(new_list, list, size);
        if(debug){
            cout<<"After add_entry"<<endl;
            cout<<"size: "<<size<<endl;
            cout<<"capacity: "<<capacity<<endl;
        }
        return new_list;
    }
    if(debug){
        cout<<"After add_entry"<<endl;
        cout<<"size: "<<size<<endl;
        cout<<"capacity: "<<capacity<<endl;
    }
    return list;
}

template<typename T>
T* allocate(int capacity){
    const bool debug = false;
    if (debug) cout<<"allocate: capacity: "<<capacity<<endl;
    return new T[capacity];
}

template<typename T>
T* remove_entry(T* list, int& size, int& capacity){
    // isn't this just supposed to work like vector::pop() YES!!
    // in that we're popping the last element from the array?
    // is that what is being stored in the delete_me variable?
    if(size == 0)
        // there's nothing to remove here
        return list;
    T* new_list;
    size--;
    if(size == (capacity / 4)){
        capacity /= 2;
        new_list = allocate<T>(capacity);
        copy_list(new_list, list, size);
        return new_list;
    }
    return list;
//    T* new_list;
//    for(int i = 0; i < size; i++){
//        if(list[i] == delete_me){
//            // start shifting left at i
//            // and do this until i == capacity - 1
//            // (if i is the last element, then we
//            // can't refer to i+1).
//            for(int k = i; k < capacity - 1; k++){
//                list[k] = list[k+1];
//            }
//            // you "removed" an item from list, so decrement size:
//            size--;
//            // reallocate half the space when size is 1/4 of the capacity
//            if(size == (capacity / 4)){
//                capacity /= 2;
//                new_list = allocate<T>(capacity);
//                copy_list(new_list, list, size);
//                return new_list;
//            }
//            return list;
//        }
//    }
}

//template<typename T>
//T* remove_entry(T* list, const T& delete_me, int& size, int& capacity){
//    // isn't this just supposed to work like vector::pop() YES!!
//    // in that we're popping the last element from the array?
//    // is that what is being stored in the delete_me variable?
//    T* new_list;
//    for(int i = 0; i < size; i++){
//        if(list[i] == delete_me){
//            // start shifting left at i
//            // and do this until i == capacity - 1
//            // (if i is the last element, then we
//            // can't refer to i+1).
//            for(int k = i; k < capacity - 1; k++){
//                list[k] = list[k+1];
//            }
//            // you "removed" an item from list, so decrement size:
//            size--;
//            // reallocate half the space when size is 1/4 of the capacity
//            if(size <= (capacity / 4)){
//                capacity /= 2;
//                new_list = allocate<T>(capacity);
//                copy_list(new_list, list, size);
//                return new_list;
//            }
//            return list;
//        }
//    }
//}



template<typename T>
void copy_list(T *dest, T* src, int many_to_copy){
    const bool debug = false;
    for(int i = 0; i < many_to_copy; i++){
        // can't use add_entry because we don't have _capacity
        // or _size
//        dest = add_entry(dest, src[i], _size, _capacity);
        dest[i] = src[i];
    }
    if(debug){
        std::cout << "copy_list: src: ";
        print_list(src, many_to_copy);
        std::cout << std::endl;
    }
}

template<typename T>
T* search_list(T* list, const T& find_me, int size){
    const bool debug = false;
    T *find_me_ptr = NULL;
    T found_item;
    for(int n = 0; n < size; n++){
        if(list[n] == find_me){
            found_item = list[n];
            find_me_ptr = &found_item;
        }
    }
    return find_me_ptr;
}

template<typename T>
void print_list(T* list, int size){
    cout << "{";
    for(int i = 0; i < size; i++)
        cout << list[i] << " ";
    cout << "}";
    cout << endl;
}

template<typename T>
void test_string(){
//    int capacity = 3;
//    int size = 0;
//    T* list = allocate(capacity);
//    list = add_entry(list, "Erika", size, capacity);
//    print_list(list, size);

//    list = add_entry(list, "Red", size, capacity);
//    print_list(list, size);

//    list = add_entry(list, "Bo", size, capacity);
//    print_list(list, size);

//    list = add_entry(list, "Pierson", size, capacity);
//    print_list(list, size);

//    list = add_entry(list, "Maher", size, capacity);
//    print_list(list, size);

//    list = add_entry(list, "Mac", size, capacity);
//    print_list(list, size);

//    list = add_entry(list, "Paula", size, capacity);
//    print_list(list, size);


//    cout<<"Deleting Erika"<<endl;

//    list = remove_entry(list, "Erika", size, capacity);
//    print_list(list, size);


//    cout<<"Deleting Bo"<<endl;

//    list = remove_entry(list, "Bo", size, capacity);
//    print_list(list, size);

//    cout<<"Deleting Maher"<<endl;

//    list = remove_entry(list, "Maher", size, capacity);
//    print_list(list, size);

//    cout<<"Deleting Pierson"<<endl;

//    list = remove_entry(list, "Pierson", size, capacity);
//    print_list(list, size);

//    cout<<"Deleting Red"<<endl;

//    list = remove_entry(list, "Red", size, capacity);
//    print_list(list, size);
}

#endif // VECTOR_LOWER_LEVEL_FUNCTIONS_H
