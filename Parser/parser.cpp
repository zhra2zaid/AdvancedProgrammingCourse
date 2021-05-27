#include <string>
#include "strings.h"
#include "parser.h"

void Parser::parse(){
    
    stack.push_back(make_shared<Word>(END));
    stack.push_back(make_shared<Variable>(E));

    shared_ptr<Symbol> x = stack[stack.size()-1]; //x = top of the stack
    terminal a = nextToken(); //a = current token
    printLM();

    while(stack.size() > 1){
        if(dynamic_cast<Word*>(x.get()) != nullptr && x->getSymbol() == a){
            stack.pop_back();
            a = nextToken();
            accepted.push_back(x); //push the parsed token (the new one) to the accepted list
        }
        else if(x->getSymbol() == EPSILON){
            stack.pop_back();
            x = stack[stack.size()-1];
            continue;
        }
        else if(dynamic_cast<Word*>(x.get()) != nullptr || table[x->getSymbol()][a] == -1){
            cout << "syntax error" << endl;
            return;
        }
        else{
            stack.pop_back();
            int rule = table[x->getSymbol()][a];
            for (auto symbol = rules[rule].begin(); symbol != rules[rule].end(); ++symbol) {
                stack.push_back(*symbol);
            }
        }

        printLM();
        x = stack[stack.size()-1];
    }
}

terminal Parser::nextToken (){
    string token;
    if(inputFile >> token) {
        return str_to_terminal.at(token);
    }
    else{
        return END;
    }
}

void Parser::printLM(){
    for (auto symbol = accepted.begin(); symbol != accepted.end(); ++symbol) {
        (*symbol)->printSymbol();
    }

    cout << "| ";

    for (auto symbol = stack.rbegin(); symbol != stack.rend()-1; ++symbol) {
        (*symbol)->printSymbol();
    }

    cout << endl;
}
