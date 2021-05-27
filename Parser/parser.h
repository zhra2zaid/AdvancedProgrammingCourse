#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include <fstream>
#include "symbol.h"

using namespace std;

class Parser {
	ifstream& inputFile;

	vector<vector<shared_ptr<Symbol>>> rules {
		{ make_shared<Variable>(E_), make_shared<Variable>(T) },
		{ make_shared<Variable>(E_), make_shared<Variable>(T), make_shared<Word>(PLUS) },
		{ make_shared<Word>(EPSILON) },
		{ make_shared<Variable>(T_), make_shared<Variable>(F) },
		{ make_shared<Variable>(T_), make_shared<Variable>(F), make_shared<Word>(ASTERISK) },
		{ make_shared<Word>(EPSILON)},
		{ make_shared<Word>(RPAREN), make_shared<Variable>(E), make_shared<Word>(LPAREN) },
		{ make_shared<Word>(ID) }
	};

	vector<vector<int>> table {
		{ 0, -1, -1, 0, -1, -1 },
		{ -1, 1, -1, -1, 2, 2 },
		{ 3, -1, -1, 3, -1, -1 },
		{ -1, 5, 4, -1, 5, 5 },
		{ 7, -1, -1, 6, -1, -1 }
	};

	vector<shared_ptr<Symbol>> stack;
	vector<shared_ptr<Symbol>> accepted;
	
public:
	explicit Parser(ifstream& file) : inputFile(file) {}
	void parse();
	terminal nextToken ();
	void printLM();
};

#endif