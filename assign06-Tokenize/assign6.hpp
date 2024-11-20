#pragma once
/*
 * assign6.hpp
 * Header file template for assignment 6.
 *
 * You can modify the classes here. You will also need to add a .cpp containing
 * the implementations of the two required functions.
 * 
 * You can add other methods/members to the classes if you need to, but you
 * have to keep the existing ones.
 */

#include <string>
#include <vector>

struct exp { 
    // You will have to implement the print method on all the subclasses.
    virtual void print() = 0; 
};

// Precedence 100
struct exp_num : public exp {
    int value;

    exp_num(int v) : value(v) { }

    void print();
};


// Precedence 100
struct exp_var : public exp {
    std::string name;

    exp_var(std::string n) : name(n) { }

    void print();
};


// Precdence 100
struct exp_paren : public exp {
    exp* inner;

    exp_paren(exp* i) : inner(i) { }

    void print();
};

// Precedence 100 
struct exp_minus : public exp {
    exp* inner;

    exp_minus(exp* i) : inner(i) { }

    void print();
};

// Precedence 100
struct exp_func : public exp {
    std::string name;
    exp* arg;

    exp_func(std::string n, exp* a) : name(n), arg(a) { }

    void print();
};

// Precedence:
// +  50
// -  50
// *  75
// /  75
struct exp_op : public exp {
    char op;
    exp* left;
    exp* right;

    exp_op(char o, exp* l, exp* r) : op(o), left(l), right(r) { }

    void print();
};

// *** You need to implement the following two functions ***

std::vector<std::string> tokenize(std::string s);

exp* parse(std::vector<std::string>::iterator start, 
           std::vector<std::string>::iterator finish,
           int& prec);


