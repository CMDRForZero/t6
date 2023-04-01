#include "parser.hpp"

Parser::Parser()
    : buf(-1), value(0), symbol(0), prevalue(0)
{
}

int Parser::scan() {
    while(1) {
        char t;
        if (buf != -1) {
            t = buf;
            buf = -1;
        }
        else if (symbol == -1) {
            return EOF;
        }
        else {
            t = getchar();
        }
        if (t == ' ' || t == '\t' || t == '\n' || t == '\r') {
            return EOF;
        }
        else if (t == '-') {
            return SUB;
        }
        else if (t == '+') {
            return COMP;
        }
        else if (t == '*') {
            return MULT;
        }
        else if (t == '/') {
            return DIV;
        }
        else if (t == '(') {
            return LBRACE;
        }
        else if (t == ')') {
            return RBRACE;
        }
        else if (t >= '0' && t <= '9') {
            value = t - '0';
            t = getchar();
            while(t >= '0' && t <= '9') {
                value = value*10 + t - '0';
                t = getchar();
            }
            buf = t;
            return I;
        }
        else if (t == EOF) {
            return EOF;
        }
        else {
            error("Unknown input");
        }
   }
}

void Parser::error(std::string msg) {
    std::cout<<msg<<std::endl;
    exit(1);
}

// E::= TE'
void Parser::e() {
    symbol = scan();
    t();
    // prevalue = value;
    e_();    
}

// E'::= RTE' |e
int Parser::e_() {
    //symbol = scan();
    int opr;
    if (symbol == EOF) {
        return EOF;
    }
    else if ((opr = r()) != -1) {
        t();
        e_();
    }
}

// R::= + |-
int Parser::r() {
    if (symbol == SUB) {
        prevalue = value;
        symbol = scan();
        return SUB;
    }
    else if (symbol == COMP) {
        prevalue = value;
        symbol = scan();
        return COMP;
    }
    else {
        return -1;
    }
}

// T::= FT'
void Parser::t() {
    f();
    t_();
}

// T'::= SFT' |e
int Parser::t_() {
    symbol = scan();
    int opr;
    if (symbol == EOF) {
        return EOF;
    }
    else if ((opr = s()) != -1){
        f();
        t_();
    }
}

// S::= * |/
int Parser::s() {
    if (symbol == MULT) {
        //prevalue = value;
        symbol = scan();
        return MULT;
    }
    else if (symbol == DIV) {
        //prevalue = value;
        symbol = scan();
        return DIV;
    }
    else {
        //error("404"); // заменить название ошибки
        return -1;
    }
}

// F::= i |(E)
int Parser::f() {
    if (symbol == LBRACE) {
        e();
        if (symbol != RBRACE) {
            error("Brace disballance");
        }
        symbol = scan();
        return symbol;
    }
    else if (symbol == I) {
        prevalue = value;
        symbol = scan();
        return value;
    }
    else {
        error("Invalid input ..");
        return -1;
    }
}

void Parser::printresult() {
    e();
    if (symbol != EOF) {
        error("Still some input exists");
    }
    std::cout<<"success, result: "<<symbol<<std::endl;
}

