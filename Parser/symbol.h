#ifndef PARSER_SYMBOL_H
#define PARSER_SYMBOL_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "enums.h"

class Symbol {
protected:
    int symbol;
public:
    Symbol(int s) : symbol(s){}
    int getSymbol();
    virtual void printSymbol() const = 0;
};

class Word : public Symbol{
public:
    void printSymbol() const override;
    using Symbol::Symbol;
};

class Variable : public Symbol {
public:
    void printSymbol() const override;
    using Symbol::Symbol;
};

#endif