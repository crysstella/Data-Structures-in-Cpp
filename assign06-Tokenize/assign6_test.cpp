/*
 * assign6_test.cpp
 * Tests for assignment 6
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

ostream& operator<< (ostream& out, const vector<string>& vs) {
    if(vs.empty())
        return out;

    for(size_t i = 0; i < vs.size()-1; ++i)
        out << "`" << vs.at(i) << "`, ";
    out << "`" << vs.back() << "`";

    return out;
}

bool tokenize(string s, vector<string>& tokens);

bool check_tokenization(string s, vector<string> tokens) {
    vector<string> output;
    bool b = tokenize(s,output);

    if(!b) {
        cout << "CHECK: string \"" << s << "\" should tokenize without errors.\n";
        return false;
    }

    if(tokens != output) {
        cout << "CHECK: tokenization of string \"" << s << "\" is incorrect:\n";
        cout << "       Expected: " << tokens << endl;
        cout << "       Found: " << output << endl;
        return false;
    }

    return true;
}

bool check_error(string s) {
    vector<string> output;

    if(tokenize(s,output)) {
        cout << "CHECK: tokenization of string \"" << s << "\" should fail with errors"
                ", but succeeds.\n";
        return false; 
    }

    return true;
}

bool check_success() {
    return check_tokenization("abc",          {"abc"}) &&
           check_tokenization("123",          {"123"}) &&
           check_tokenization("123.456",      {"123.456"}) &&
           check_tokenization("abc123",       {"abc123"}) &&
           check_tokenization("123abc",       {"123", "abc"}) &&
           check_tokenization("()+-*/",       {"(", ")", "+", "-", "*", "/"}) &&
           check_tokenization("  abc  123  ", {"abc", "123"}) &&
           check_tokenization("123.456abc",   {"123.456", "abc"}) &&
           check_tokenization("123<abc",      {"123", "<", "abc"}) &&
           check_tokenization("123<=abc",     {"123", "<=", "abc"}) &&
           check_tokenization("123>abc",      {"123", ">", "abc"}) &&
           check_tokenization("123>=abc",     {"123", ">=", "abc"}) && 
           check_tokenization("<<>><>",       {"<", "<", ">", ">", "<", ">"}) &&
           check_tokenization("abc\n\t123",   {"abc", "123"});
}

bool check_errors() {
    return check_error("123.") &&
           check_error(".123") &&
           check_error("123=456") && 
           check_error("abc.def") &&
           check_error("123..456") &&
           check_error("123.456.789") &&
           check_error("123<==456") &&
           check_error("123>==456") &&
           check_error("   .   ") &&
           check_error("abc=def");
}

int main(int argc, char**) {
    if(argc > 1) {
        while(true) {
            string input;
            cout << "> ";
            getline(cin, input);
            vector<string> tokens;
            bool b = tokenize(input, tokens);

            if(b) {
                cout << "Tokens (" << tokens.size() << "): " << tokens << endl;
            }
            else
                cout << "Error during tokenization" << endl;
        }
    }
    else if(check_success() && check_errors()) 
        cout << "*** All Tests Passed Successfully! ****\n";
}
