#include "token.h"

Token::Token()
{
    // left blank
}
Token::Token(string str, int type){
    _token = str;
    _type = type;
}
ostream& operator <<(ostream& outs, const Token& t){
    outs << t._token << endl;
    return outs;
}
int Token::type(){
    return _type;
}
string Token::type_string(){
    switch (_type) {
    case -1:
        return "UNKNOWN";
    case 0:
        return "DOUBLE";
    case 1:
        return "ALPHA";
    case 2:
        return "SPACE";
    case 3:
        return "PUNCT";
    }
}
string Token::token_str(){
    return _token;
}
