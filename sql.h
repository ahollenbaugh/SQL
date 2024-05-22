#ifndef SQL_H
#define SQL_H

#include <iostream>
#include <iomanip>
//#include <queue>
#include "table.h"
#include "stokenizer.h"
#include "vector.h"
#include "parser.h"
#include "record.h"

using namespace std;

class SQL
{
public:
    SQL();
    void run();                      // interactive (commands from user)
    void run_batch(string filename); // commands from batch file
private:
//    Map<string, Table> tables;
//    Map<string, string> parse_tree;
//    Parser parser;
    string table_names = "table_names.txt";

};

#endif // SQL_H
