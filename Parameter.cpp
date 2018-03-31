#include "Graph.h"
#include "Simple_window.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>


struct Parameter
{
	vector<string>name;
	vector<double>size;
};

istream& operator>>(istream& is, Parameter& p)
{
	double d;
	string s;
	while (is)
	{
		is >> s >> d;
		p.name.push_back(s);
		p.size.push_back(d);
	}
	p.name.pop_back();
	p.size.pop_back();

	if (!is)return is;
}

void read_vals(string filename, Parameter& p)
{
	ifstream ist{ filename };
	if (!ist)error("can't open input file", filename);
	ist >> p;
}
