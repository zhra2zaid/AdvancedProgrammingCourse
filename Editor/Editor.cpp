#include <string>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <vector>
#include "Editor.h"
using namespace std;
static bool waitForDot = false;
static bool zero = false;
Editor::Editor() : document() {}

void Editor::loop()
{
	string a;
	while (1)
	{
		getline(cin, a);
		if (a == "q")
			break;
		handle(a);
	}
}

void Editor::init(string &name)
{
	ifstream in;
	in.open(name);
	vector<string> vec;
	string line;
	int count = 0;
	while (getline(in, line))
	{
		vec.insert(count + vec.begin(), line);
		count++;
	}
	in.close();
	copy(vec.begin(), vec.end(), back_inserter(document.lines));
	loop();
}
//handle a text line from the user
void Editor::handle(string line)
{

	//in case of 'a', 'i' or 'c', call "text" function, until '.' received.
	if (waitForDot)
	{
		document.text(line);
		if (!line.compare("."))
		{
			waitForDot = false;
			if (zero)
			{
				zero = false;
				document.currentLine--;
			}
		}
		return;
	}

	if (!line.compare("p"))
	{
		document.p();
		return;
	}
	if (!line.compare("%p"))
	{
		document.prec_p();
		return;
	}
	if (!line.compare("a"))
	{
		if (document.lines.empty() && document.currentLine == 0)
		{
			--document.currentLine;
		}
		waitForDot = true;
		document.a();
		return;
	}
	if (!line.compare("i"))
	{
		if (document.currentLine == 0)
		{
			zero = true;
		}
		document.i();
		waitForDot = true;

		return;
	}
	if (!line.compare("c"))
	{
		waitForDot = true;
		document.c();
		return;
	}
	if (!line.compare("d"))
	{
		document.d();
		return;
	}
	if (line.at(0) == 'w' && line.at(1) == ' ')
	{
		line = line.substr(2, line.length() - 1);
		document.w(line);
	}
	if (!line.compare("n"))
	{
		document.n();
		return;
	}

	//check if the text is a number
	int num = 0;
	bool isAnumber;
	string s = line;
	try
	{
		num = stoi(s);
		isAnumber = true;
	}
	catch (std::invalid_argument const &e)
	{
		isAnumber = false;
	}
	catch (std::out_of_range const &e)
	{
		isAnumber = false;
	}
	if (isAnumber)
	{
		if (s.at(0) == '+' || s.at(0) == '-')
		{
			document.num2(num);
		}
		else
		{
			document.num(num);
		}
		return;
	}

	//empty text
	if (line.size() == 0)
	{
		document.text(line);
		return;
	}

	if (line == "j")
	{
		document.j();
	}
	// '/text'
	if (line.at(0) == '/')
	{
		document.slesh_text(split(line, '/')[1]);
		return;
	}
	// 's/old/new/'
	if (line.at(0) == 's')
	{
		vector<string> arr = split(line, '/');
		if (arr.size() >= 3)
		{
			document.s_slech_old_new(arr[1], arr[2]);
			return;
		}
	}
	if (line == "$")
	{
		document.dollar();
	}
	if (line.at(0) == 'e' && line.find(".txt"))
	{
		document.e(line);
	}
}
//split text by char and return a vector of words
vector<string> Editor::split(string str, char splitBy)
{
	vector<string> words;
	string word = "";
	for (auto x : str)
	{
		if (x == splitBy)
		{
			words.push_back(word);
			word = "";
		}
		else
		{
			word = word + x;
		}
	}
	words.push_back(word);
	return words;
}