//G1`
// E::= TE'
// E'::= R T E' |e
// R:: = +| -
// T:: = FT'
// T'::= S F T' |e
// S:: = *|/
// F:: = i |(E)

#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stack>
#include "ASTree.hpp"

#define I 254
#define SUB 255
#define COMP 256
#define MULT 257
#define DIV 258
#define LBRACE 259
#define RBRACE 260


class Parser {
public:
    Parser();
    int scan();
    void error(std::string msg);
    void e();
    int e_();
    int r();
    void t();
    int t_();
    int s();
    int f();
    void printresult();

private:
    int symbol;
    int value;
    int buf;
    bool flag;
    int prevalue;
};

#endif /* parser_hpp */
