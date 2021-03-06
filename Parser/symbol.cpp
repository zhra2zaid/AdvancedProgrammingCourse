#include "strings.h"
#include "symbol.h"

using namespace std;

int Symbol::getSymbol(){return symbol;}

void Word::printSymbol() const {
    if(symbol != EPSILON) {
        cout << terminalStrings[symbol] << " ";
    }
}

void Variable::printSymbol() const {
    cout << tokenStrings[symbol] << " ";
}