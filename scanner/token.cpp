#include "token.h"
#include "tokenstrings.h"

using namespace std;

// implements token
tokenType Token::getType(){return type;}
string Token::getText(){return text;}
void Token::printToken(){
	if (type < 258) {
		char printype = type;
		cout << printype;
	}
	else {
		cout << tokenStrings[type - 258];
	}
	cout << "\t" << text << endl;
}

//implements varToken
void varToken::add_line(int l){lines->insert(l);}

shared_ptr<set<int>> varToken::getLines(){return lines;}

