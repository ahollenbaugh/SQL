#include "stokenizer.h"

// In the stokenizer.cpp, you must reintroduce the _table static member variable once again:
int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

const char* DIGITS = "0123456789";
const char* ALPHA = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* SPACE = " \t\r\n";
const char* PUNCT = "!\"#$%&\'()*+,-./:;<=>\?@]\\[^_{|}~`";

const int DOUBLE_START_STATE = 0;
const int ALPHA_START_STATE = 5;
const int SPACE_START_STATE = 8;
const int PUNCT_START_STATE = 11;

const int UNKNOWN_TOKEN_TYPE = -1;
const int DOUBLE_TOKEN_TYPE = 0;
const int ALPHA_TOKEN_TYPE = 1;
const int SPACE_TOKEN_TYPE = 2;
const int PUNCT_TOKEN_TYPE = 3;

STokenizer::STokenizer()
{
    make_table(_table);
    _pos = 0;
}
STokenizer::STokenizer(char str[]){
    make_table(_table);
    _pos = 0;
    set_string(str);
}
bool STokenizer::done(){
    // Probably won't use this.
    // When more() is false, it's implied that done() is true.
}
bool STokenizer::more(){
    // If you're not doing a pre-read loop,
    // then more() is true when you're pointing
    // to the null character.
    // If you ARE doing a pre-read loop,
    // this function should return true
    // when you're pointing to the space
    // AFTER the null character.
    if(_buffer[_pos] != '\0')
        return true;
    return false;
}
STokenizer& operator >> (STokenizer& s, Token& t){
    // s >> t
    // grabs one token at a time
    const bool debug = false;
    if(debug)cout<<"STokenizer::operator >> fired"<<endl;
    string str;
    // see if it's a DOUBLE token:
    if(s.get_token(DOUBLE_START_STATE, str)){
        t = Token(str, DOUBLE_TOKEN_TYPE); // set string and type of token
    }
    // if not, see if it's an ALPHA token:
    else if(s.get_token(ALPHA_START_STATE, str)){
        t = Token(str, ALPHA_TOKEN_TYPE);
    }
    // if not, see if it's a SPACE token:
    else if(s.get_token(SPACE_START_STATE, str)){
        t = Token(str, SPACE_TOKEN_TYPE);
    }
    // if not, see if it's a PUNCT token:
    else if(s.get_token(PUNCT_START_STATE, str)){
        t = Token(str, PUNCT_TOKEN_TYPE);
    }
    // if not, UNKNOWN:
    else{
        t = Token(str, UNKNOWN_TOKEN_TYPE);
    }
    return s;
}
void STokenizer::set_string(char str[]){
    strcpy(_buffer, str);
}
void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    init_table(_table);

    // ----------------------------------- DOUBLE machine ------------------------------------------:

    // At state 0:
        // digit -> state 1
        // decimal point -> state 2
    mark_cells(0, _table, DIGITS, 1);
    mark_cell(0, _table, '.', 2);
    // At state 1:
        // digit -> state 1
        // decimal point -> state 2
    mark_cells(1, _table, DIGITS, 1);
    mark_cell(1, _table, '.', 2);
    // At state 2:
        // digit -> state 3
    mark_cells(2, _table, DIGITS, 3);
    // At state 3:
        // digit -> state 3
    mark_cells(3, _table, DIGITS, 3);
    // Success states: 1, 3
    // Fail states: 0, 2
    mark_success(_table, 1);
    mark_success(_table, 3);
    mark_fail(_table, 0);
    mark_fail(_table, 2);

    // ----------------------------------- ALPHA machine ------------------------------------------:

    // At state 5:
        // alpha -> state 6
    mark_cells(5, _table, ALPHA, 6);
    // At state 6:
        // alpha -> state 6
    mark_cells(6, _table, ALPHA, 6);
    // Success states: 6
    mark_success(_table, 6);
    // Fail states: 5
    mark_fail(_table, 5);

    // ----------------------------------- SPACE machine ------------------------------------------:
    // At state 8:
        // space -> state 9
    mark_cells(8, _table, SPACE, 9);
    // At state 9:
        // space -> state 9
    mark_cells(9, _table, SPACE, 9);
    // Success states: 9
    mark_success(_table, 9);
    // Fail states: 8
    mark_fail(_table, 8);
    // ----------------------------------- PUNCT machine ------------------------------------------:
    // At state 11:
        // punct -> state 12
    mark_cells(11, _table, PUNCT, 12);
    // At state 12:
        // punct -> state 12
    mark_cells(12, _table, PUNCT, 12);
    // Success states: 12
    mark_success(_table, 12);
    // Fail states: 11
    mark_fail(_table, 11);
}
bool STokenizer::get_token(int start_state, string& token){
    // point to next char after token we extracted
    // in the input
    // if return false, pos should be unchanged

    const bool debug = false;
    if(debug)cout<<"STokenizer::get_token fired"<<endl;
    int state = start_state;
    int pos_last_success = -1;
    char current_char;

    while(_buffer[_pos] != '\0' && state != -1){
        if(debug){
            cout<<"STokenizer::get_token: strlen(_buffer): "<<strlen(_buffer)<<endl;
        }
        current_char = _buffer[_pos];

        // need code to handle negative character values

        state = _table[state][current_char];
        if(debug)cout<<"state = "<<state<<endl;

        if(state != -1){
            token.push_back(current_char);
            if(debug)cout<<"strlen(_buffer) before pos++: "<<strlen(_buffer)<<endl;
            _pos++; // <- !!!!!!!! THIS IS CHANGING THE LENGTH OF BUFFER
            if(debug)cout<<"_pos: "<<_pos<<endl;
            if(debug)cout<<"strlen(_buffer) after pos++: "<<strlen(_buffer)<<endl;
        }
        if(is_success(_table, state)){
            pos_last_success = _pos;
        }
        if(debug)show_string(_buffer, _pos);
    }

    if(debug)cout<<"token.length: "<<token.length()<<endl;

    if(token.length() == 0){
        return false;
    }
    return true;
}
