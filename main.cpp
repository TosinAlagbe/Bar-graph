int main()
{
	Parameter x;
	string fname;
	cin >> fname;
	read_vals(fname, x);
	Bar_graph bar(x.name, x.size);
	bar.bond();
}
