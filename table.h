#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include <iomanip>
#include "map.h"
#include "mmap.h"
#include "record.h"
#include "vector.h"
#include "parser.h"

using namespace std;

class Table
{
public:

    // CONSTRUCTORS:

    Table();
    Table(const string& name, const Vector<string> fields);     // Creates new table
    Table(const string& name);                                  // Opens existing table

    // COMMANDS:

    void insert_into(Record entry);
    Table select(vector<string> command);                                             // Select certain fields
    Table select_all();                                         // Select all fields

    // Perhaps make the below functions private?

    void set_fields(Vector<string> field_names);                // Sets field names
    void get_fields();                                          // Returns vector of field names
    void reindex(Record r, long recNo);                                     // Updates indices when records are added/deleted
    void print_table();
    friend ostream & operator << (ostream &out, const Table &t);
    bool _where = false;                         // false if no conditions

private:
    string table_name;                           // Name of the table
    Vector<MMap<string, int> > _indices;         // Maps field names to records and record numbers
    // _indices is organized like this:
    // first -> Bill:11,37,40 | Richard:[73],59,63 | ...
    // last  -> Harris:[73],87,92 | Johnson:18,38 | ...
    // dept  -> CS:22,38,54 | Humanities:51,[73],80 | ...
    Vector<string> _fields;                      // Example: fname, lname, dept...
    Map<string, int> _field_order;               // Example: fname: 0, lname: 1, dept: 2...
    bool _empty;                                 // True if no records have been added
    int _serial_no;                              // Global serial number
    int _last_recno;                             // ?
    string bin_fname;                            // filename for binary file
    string fields_fname;                         // filename for text file
    Parser p;                                    // this takes care of processing commands and generating parse trees
};

#endif // TABLE_H
