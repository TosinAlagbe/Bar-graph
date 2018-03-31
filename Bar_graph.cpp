#include "Graph.h"
#include "Simple_window.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

class Group : public Shape
{
public:
	Group(const Group&) = delete;
	Group &operator=(const Group&) = delete;
	virtual void bond();

protected:

	Group() {};
	int w_length = 1200;
	int w_height = 1000;

	Simple_window w{ Point{ 100,10 }, w_length, w_height, " " };

	Vector_ref<Graph_lib::Rectangle>rect;
	Vector_ref<Circle>circ;
	Vector_ref<Octagon>oct;
	Vector_ref<Axis>ax;
	Vector_ref<Text>txt;

};

class Bar_graph : public Group
{
public:
	Bar_graph(vector<string>&p, vector<double>v);
	double maxim(vector<double>);
	double minim(vector<double>);

private:
	void shorten(vector<string>&);
	void set_axis();
	vector<double>values;
	vector<string>params;
	int x_axis = w_length - 120;
	int y_axis = w_height - 70;
	Point x_point{ 100,w_height - 50 };
	Point y_point{ 100,w_height - 50 };
	double bar_size = x_axis / (values.size() * 3);
	void auto_scale(vector<double>&, int&);

};


void Bar_graph::auto_scale(vector<double>&v, int& s)
{
	if (maxim(v) <= 20)
	{
		for (int i = 0; i< v.size(); ++i)
		{
			v[i] = v[i] * 6;
		}
		s = s * 6;
	}
	if (maxim(v)>20 && maxim(v) <= 50)
	{
		for (int i = 0; i< v.size(); ++i)
		{
			v[i] = v[i] * 5;
		}
		s = s * 5;
	}
	if (maxim(v)>50 && maxim(v) <= 100)
	{
		for (int i = 0; i< v.size(); ++i)
		{
			v[i] = v[i] * 4;
		}
		s = s * 4;
	}
	if (maxim(v) > 100 && maxim(v) <= 300)
	{
		for (int i = 0; i< v.size(); ++i)
		{
			v[i] = v[i] * 3;
		}
		s = s * 3;
	}
	if (maxim(v) > 300 && maxim(v) <= 500)
	{
		for (int i = 0; i< v.size(); ++i)
		{
			v[i] = v[i] * 2;
		}
		s = s * 2;
	}
	if (maxim(v) > 500)
	{
		s = s * 1;
	}
}

void Bar_graph::shorten(vector<string>&s)
{
	for (int i = 0; i < s.size(); ++i)
	{
		if (int(s[i].size()) > 7)
		{
			remove_vowel(s[i]);
		}
	}
}

void Bar_graph::set_axis()
{
	ax.push_back(new Axis{ Axis::x, x_point, x_axis });
	ax.push_back(new Axis{ Axis::y, y_point, y_axis });
	for (int i = 0; i < ax.size(); ++i)
	{
		ax[i].set_color(Color::black);
	}
}

Bar_graph::Bar_graph(vector<string>&p, vector<double>v)
	:values{ v }, params{ p }
{
	int txt_start = x_point.x;
	int scale_fac = 1;

	int step_size = maxim(v) / 10;
	int val_start = minim(v) - step_size;
	int val_limit = maxim(v) + step_size;

	auto_scale(v, scale_fac);

	shorten(p);

	if (v.size() != p.size())
	{
		error("string must map to double");
	}
	set_axis();
	for (int i = 0; i < p.size(); ++i)
	{
		txt.push_back(new Text{ Point(txt_start + bar_size,x_point.y + 20), p[i] });
		txt[txt.size() - 1].set_color(Color::black);
		txt_start = txt_start + 2 * bar_size;
	}
	for (val_start; val_start < val_limit; val_start += step_size)
	{
		txt.push_back(new Text{ Point(x_point.x - 45,int(x_point.y - (val_start * scale_fac))), to_string(val_start) });
		txt[txt.size() - 1].set_color(Color::black);
	}

	int x_start = x_point.x;

	for (int i = 0; i < v.size(); ++i)
	{
		rect.push_back(new Graph_lib::Rectangle
			{ Point{ int(x_start + bar_size), int(x_point.y - v[i]) },
			int(bar_size), int(v[i]) });
		rect[rect.size() - 1].set_color(Color::black);
		x_start = x_start + 2 * bar_size;
	}

}

double Bar_graph::maxim(vector<double>v)
{
	sort(v.begin(), v.end());
	return v[v.size() - 1];
}
double Bar_graph::minim(vector<double>v)
{
	sort(v.begin(), v.end());
	return v[0];
}
