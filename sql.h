#ifndef SQL_H
#define SQL_H

#include <iostream>
#include <iomanip>
//#include <queue>

#include "../../!includes/Table/table.h"
//#include "../../!includes/Map/map.h"
#include "../../!includes/STokenizer/stokenizer.h"
#include "../../!includes/vector/vector.h"
#include "../../!includes/Parser/parser.h"
#include "../../!includes/Record/record.h"

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
