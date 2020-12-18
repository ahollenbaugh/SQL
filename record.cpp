#include "record.h"

long Record::write(fstream &outs){
    //write to the end of the file.
    outs.seekg(0, outs.end);
    long pos = outs.tellp();

    //outs.write(&record[0], sizeof(record));
    outs.write(&record[0][0], sizeof(record));

    return pos/sizeof(record);
}
long Record::read(fstream &ins, long recno){
    long pos= recno * sizeof(record);
    // record number * number of bytes in a record
    ins.seekg(pos, ios_base::beg);
    // pos: offset value; ios_base::beg: beginning of stream
    // seekg sets position of next char to be extracted

    ins.read(&record[0][0], sizeof(record));
    // reads sizeof(record) characters into record
    return ins.gcount();
    // gcount returns number of characters in stream
}
template <class T>
ostream& operator<<(ostream& outs, const vector<T>& v){
    for (int i= 0; i<v.size(); i++)
        outs<<v[i]<<" ";
    return outs;
}
ostream& operator<<(ostream& outs,
                    const Record& r){
    for (int i=0; i<r.ROW_MAX; i++)
            outs<<r.record[i]<<endl;
    return outs;
}

//-------------------------------------------------
bool file_exists(const char filename[]){
    const bool debug = false;
    fstream ff;
    ff.open (filename,
        std::fstream::in | std::fstream::binary );
    if (ff.fail()){
        if (debug) cout<<"file_exists(): File does NOT exist: "<<filename<<endl;
        return false;
    }
    if (debug) cout<<"file_exists(): File DOES exist: "<<filename<<endl;
    ff.close();
    return true;
}

void open_fileRW(fstream& f, const char filename[]) throw(char*){
    const bool debug = false;
    //openning a nonexistent file for in|out|app causes a fail()
    //  so, if the file does not exist, create it by openning it for
    //  output:
    if (!file_exists(filename)){
        f.open(filename, std::fstream::out|std::fstream::binary);
        if (f.fail()){
            cout<<"file open (RW) failed: with out|"<<filename<<"]"<<endl;
            throw("file RW failed  ");
        }
        else{
            if (debug) cout<<"open_fileRW: file created successfully: "<<filename<<endl;
        }
    }
    else{
        f.open (filename, std::fstream::in | std::fstream::out| std::fstream::binary );
        if (f.fail()){
            cout<<"file open (RW) failed. ["<<filename<<"]"<<endl;
            throw("file failed to open.");
        }
    }

}
void open_fileW(fstream& f, const char filename[]){
    f.open (filename, std::fstream::out| std::fstream::binary );
    if (f.fail()){
        cout<<"file open failed: "<<filename<<endl;
        throw("file failed to open.");
    }
    else
        cout << "File write successful." << endl;
}
