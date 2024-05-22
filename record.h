#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <fstream>
#include <cstring>
#include "vector.h"

using namespace std;

bool file_exists(const char filename[]);

void open_fileRW(fstream& f, const char filename[]);
void open_fileW(fstream& f, const char filename[]);

typedef Vector<string> vectorstr;

class Record{
public:
    Record(){
        for (int i = 0; i<ROW_MAX; i++)
            record[i][0] = NULL;
        recno = -1;
    }
    Record(vectorstr v){
        // Given a vector of values
        // (ex: {"Harris", "Richard", "CS", "626..."})
        for (int i = 0; i<ROW_MAX; i++)
            record[i][0] = NULL;
        // Copy each value to the 2D array:
        for (int i=0; i<v.size(); i++)
            strcpy(record[i], v[i].c_str());
    }
    vectorstr get_fields(); // assuming field names are stored in .bin file
    long write(fstream& outs);
    long read(fstream& ins, long recno);

    friend ostream& operator<<(ostream& outs,
                               const Record& r);
//private:
    static const int ROW_MAX = 10;
    static const int COL_MAX = 500;
    int recno;
    char record[ROW_MAX][COL_MAX];
};


#endif // RECORD_H
