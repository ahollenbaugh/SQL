#ifndef BTREE_ARRAY_FUNCTIONS_H
#define BTREE_ARRAY_FUNCTIONS_H
#include <iostream>
#include <iomanip>  // setw
#include <cassert>  // assert function
using namespace std;

// PROTOTYPES -------------------------------------------------------------------------------------------------------------------

template <class T>
T maximal(const T& a, const T& b);

template <class T>
void swap_values(T& a, T& b);

template <class T>
int index_of_maximal(T data[ ], int n);

template <class T>
void ordered_insert(T data[ ], int& n, T entry);

template <class T>
int first_ge(const T data[ ], int n, const T& entry);

template <class T>
void attach_item(T data[ ], int& n, const T& entry);

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);

template <class T>
void detach_item(T data[ ], int& n, T& entry);

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);

template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size);

template <class T>
void print_array(const T data[], int n, int pos = -1);

template <class T>
bool is_gt(const T data[], int n, const T& item);

template <class T>
bool is_le(const T data[], int n, const T& item);

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list);

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme);

// --------------------- ordered_insert helper functions ----------------

template <typename T>
void shift_left(T data[], int pos, int& size);

template <typename T>
void shift_right(T data[], int pos, int& size);

template <typename T>
int get_pos(const T data[], int size, T entry);

// DEFINITIONS --------------------------------------------------------------------------------------------------------------------




template <class T>
T maximal(const T& a, const T& b){
    // return the larger of the two items
    assert(a != b);
    if(a > b)
        return a;
    return b;
}

template <class T>
void swap_values(T& a, T& b){
    // swap the two items
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
int index_of_maximal(T data[ ], int n){
    // return index of the largest item in data
    // ...return n?
    // What is n?
    // Since this function will be used for
    // B-trees, and the array of entries in
    // a node is sorted from smallest to largest,
    // is a for loop even necessary? Can't I
    // just return data[last element]?
    // If that's the case, that means
    // n must be the size of the array.
    return data[n - 1];
}

template <class T>
void ordered_insert(T data[ ], int& n, T entry){
    // insert entry into the sorted array data with length n
    const bool debug = false;
    if(debug){
        cout << "ordered_insert fired" << endl;
    }
    int pos; // where entry is supposed to go
    pos = get_pos(data, n, entry);
    // shift everything to the right at pos
    // to make room for the new entry:
    shift_right(data, pos, n);
    data[pos] = entry; // if pos == n, no shift needed
    n++;
    if(debug){
        cout << entry << " has been inserted" << endl
             << "size: " << n << endl;
        print_array(data, n);
    }
}

template <class T>
int first_ge(const T data[ ], int n, const T& entry){
    // return the first element in data that is not less than entry
    const bool debug = false;
    if(debug){
        cout << "first_ge fired" << endl;
    }
    for(int i = 0; i < n; i++){
        if(data[i] >= entry)
            return i;
    }
    return n; // if nothing is >= entry, return first unused index
}

template <class T>
void attach_item(T data[ ], int& n, const T& entry){
    // append entry to the right of data
    const bool debug = false;
    if(debug){
        cout << "attach_item fired" << endl;
        print_array(data, n, n-1);
        cout << "size: " << n << endl;
    }
    data[n] = entry;
    n++;
    if(debug){
        cout << entry << " has been attached" << endl;
        print_array(data, n, n-1);
        cout << "size: " << n << endl;
    }
}

template <class T>
void insert_item(T data[ ], int i, int& n, T entry){
    // insert entry at index i in data
    // if i (position) equals n (size), you can just
    // call attach_item and it will append it rather
    // than going through all this shifting business.
    const bool debug = false;
    if(debug){
        cout << "insert_item fired" << endl;
        print_array(data, n, i);
        cout << "size: " << n << endl;
    }
    if(i == n){
        attach_item(data, n, entry);
    }
    else{
        shift_right(data, i, n);
        data[i] = entry;
    }
    if(debug){
        cout << entry << " has been inserted" << endl;
        print_array(data, n, i);
        cout << "size: " << n << endl;
    }
}

template <class T>
void detach_item(T data[ ], int& n, T& entry){
    // remove the last element in data and place it in entry
    const bool debug = false;
    if(debug){
        cout << "detach_item fired" << endl;
    }
    if(n <= 0)
        return;
        // n cannot be negative; also, this ensures
        // n-- doesn't cause n to be negative.
    entry = data[n-1];
    n--;
    if(debug){
        cout << entry << " has been detached" << endl;
        print_array(data, n);
        cout << "size: " << n << endl;
    }
}

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry){
    // delete item at index i and place it in entry
    const bool debug = false;
    if(debug){
        cout << "delete_item fired" << endl;
    }

    // If data[] is empty, you can't do anything,
    // so just exit the function.
    if(n == 0)
        return;
    // Otherwise...
    entry = data[i];
    shift_left(data, i, n);
    if(debug){
        cout << entry << " has been deleted" << endl
             << "size: " << n << endl;
        print_array(data, n);
    }
}

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2){
    // append data2 to the right of data1
    const bool debug = false;
    if(debug){
        cout << "merge fired" << endl;
        print_array(data1, n1);
        cout << "size1: " << n1 << endl;
        print_array(data2, n2);
        cout << "size2: " << n2 << endl;
    }
    int j = 0; // for iterating thru data2
    // starting at the first empty space in data1,
    // copy the n2 elements over from data2.
    for(int i = n1; i < n1 + n2; i++){
        data1[i] = data2[j];
        j++;
    }
    n1 += n2;
    if(debug){
        cout << "arrays have been merged" << endl;
        print_array(data1, n1);
        cout << "size1: " << n1 << endl;
    }
}

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2){
    // move n/2 elements from the right of data1 and move to data2
    // Do I append to data2?
    // Do I insert in ascending order?
    // Do I overwrite pre-existing elements in data2?
    // 11/11/2019: For now, I will just append. This
    // is assuming data2 is a brand new empty array.
    // That means I need to assume n2 = 0 at the start.

    const bool debug = false;
    if(debug){
        cout << "split fired" << endl;
        print_array(data1, n1);
        cout << "size1: " << n1 << endl;
        print_array(data2, n2);
        cout << "size2: " << n2 << endl;
    }

    // Copy the right half of data1 over to data2.
    // Don't forget to set n1 to half its original size.
    int num_copy = n1 / 2;
    for(int i = n1 - num_copy; i < n1; i++){
        // starting at n1 - num_copy (right half of data1),
        // copy to data2 num_copy times.
        attach_item(data2, n2, data1[i]);
    }
    // decrease n1:
    n1 -= num_copy;

    if(debug){
        cout << "data1 has been split" << endl;
        print_array(data1, n1);
        cout << "size1: " << n1 << endl;
        print_array(data2, n2);
        cout << "size2: " << n2 << endl;
    }
}

template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size){
    // copy src[] into dest[]
    // copy src size elements to dest
    // Am I just setting dest_size equal to src_size?
    const bool debug = false;
    if(debug){
        cout << "copy_array fired" << endl;
        cout << "----- BEFORE COPY -----" << endl;
        cout << "dest" << endl;
        print_array(dest, dest_size);
        cout << "dest_size: " << dest_size << endl;
        cout << "src" << endl;
        print_array(src, src_size);
        cout << "src_size: " << src_size << endl;
    }
    for(int i = 0; i < src_size; i++)
        dest[i] = src[i];
    dest_size = src_size;
    if(debug){
        cout << "----- AFTER COPY -----" << endl;
        cout << "dest" << endl;
        print_array(dest, dest_size);
        cout << "dest_size: " << dest_size << endl;
        cout << "src" << endl;
        print_array(src, src_size);
        cout << "src_size: " << src_size << endl;
    }
}

template <class T>
void print_array(const T data[], int n, int pos){
    // print array data
    const bool debug = false;
    if(debug){
        cout << "print_array fired" << endl;
        cout << "n: " << n << endl;
    }
    cout << endl;

    if(n == 0)
        cout << "[EMPTY LIST]" << endl;
    else{
        for(int i = n-1; i >= 0; i--){
            cout << data[i] << endl;
        }
//        for(int i = 0; i < n; i++){
//            cout << setw(6) << left << data[i];
//        }
        cout << endl;

        // print indices underneath elements:
//        for(int i = 0; i < n; i++)
//            cout << setw(6) << left << i;
//        cout << endl;

        // print ^ underneath pos:
        for(int i = 0; i < n; i++){
            if(i == pos)
                cout << setw(6) << left << "^";
            else
                cout << setw(6) << "";
        }
    }

    cout << endl;
}

template <class T>
bool is_gt(const T data[], int n, const T& item){
    // item > all data[i]

    // If data is empty, isn't item
    // technically greater than all the items?
    // Or should I just return since there
    // are no items to compare it to?

    const bool debug = false;
    if(debug){
        cout << "is_gt fired" << endl;
        print_array(data, n);
    }
    assert(n >= 0);
    for(int i = 0; i < n; i++){
        if(item <= data[i]){
            if(debug) cout << item << " is not > list" << endl;
            return false;
        }
    }
    if(debug) cout << item << " is > list" << endl;
    return true;
}

template <class T>
bool is_le(const T data[], int n, const T& item){
    // item <= all data[i]
    const bool debug = false;
    if(debug){
        cout << "is_le fired" << endl;
    }
    assert(n >= 0);
    for(int i = 0; i < n; i++){
        if(item > data[i]){
            if(debug) cout << item << " is not <= list" << endl;
            return false;
        }
    }
    if(debug) cout << item << " is <= list" << endl;
    return true;
}

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list){
    // print vector list
}

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme){
    // list.push_back addme
}

// --------------------- ordered_insert helper functions ----------------

template <typename T>
void shift_left(T data[], int pos, int& size){
    const bool debug = false;
    if(debug){
        cout << "shift_left fired" << endl;
        cout << "before shift: ";
        print_array(data, size, pos);
        cout << "size: " << size << endl;
    }

    assert(pos >= 0); // position can't be negative

    // Regarding this loop: i cannot be equal
    // to size - 1 (the last element in the array)
    // because there's nothing to the right of it,
    // so we can't shift left there!
    for(int i = pos; i < size - 1; i++){
        data[i] = data[i + 1];
    }
    if(pos <= size - 1)
        size--; // only decrement size if a shift takes place

    if(debug){
        cout << "after shift: ";
        print_array(data, size);
        cout << "size: " << size << endl;
    }
}

template <typename T>
void shift_right(T data[], int pos, int& size){
    // shift elements right at pos
    const bool debug = false;

    if(debug){
        cout << "shift_right fired" << endl
             << "before shift: ";
        print_array(data, size, pos);
        cout << "size: " << size << endl;
    }

    assert(pos >= 0); // position can't be negative

    // The below condition ensures that we are not
    // inserting a value at a position that is
    // greater than the first empty space.
    // Also, if pos == size, the loop never
    // gets entered, therefore no shift occurs.
    // If no shift occurs, then we shouldn't
    // increment size. Just return from the function.
    if(pos >= size){
        if(debug)
            cout << "No need to shift. Exiting..." << endl;
        return;
    }
    for(int i = size; i > pos; i--)
        data[i] = data[i - 1];
    // this function needs to increase size
    // even though nothing has been inserted
    // because we're still copying values, so
    // we end up with an extra value!!
    size++;

    if(debug){
        cout << "after shift";
        print_array(data, size, pos);
        cout << "size: " << size << endl;
    }
}

template <typename T>
int get_pos(const T data[], int size, T entry){
    // returns index where entry belongs (assuming data is sorted)
    for(int i = 0; i < size; i++){
        if(data[i] >= entry)
            return i;
    }
    // if it doesn't fit between any values already
    // in the array, then it should be appended.
    return size;
}

#endif // BTREE_ARRAY_FUNCTIONS_H
