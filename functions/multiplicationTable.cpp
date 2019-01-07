 #include <iostream>
 #include <iomanip>
 #include <cmath>
 #include <algorithm>
 #include <cstddef>
 
 using std::max;
 using std::cout;
 using std::setw;
 using std::ostream;
 
size_t tableColumnWidth(int min, int max)
{
	 unsigned absMax = max(max * max, min * min);
	 
	 size_t colWidth = log10(absMax);
	 
	 if (min < 0 && max > 0)
		 ++colWidth;
	 
	 return colWidth;
}
 
struct Writer
{
	decltype(setw(1)) fmt;
	Writer(size_t w) : fmt(setw(w))
	{
		
	}
	
	template <class T> Writer& operator()(const ostream& os, const T& info)
	{
		os << fmt << info;
		return *this;
	}
};

void printTableHeader(const ostream& os, int min, int max)
{
	Writer write(tableColumnWidth(min, max));
	
	write(" ");
	for (int col = min; col <= max; ++col)
		write(os, col);
	
	os << "\n\n";
}

void printTableRow(const ostream& os, int num, int min, int max)
{
	Writer write(tableColumnWidth(min, max));
	
	write(num);
	
	for (int i = min; i < num; ++i)
		write(os, ' ');
	
	for (int i = num; i <= max; ++i)
		write(os, num * i);
	
	os << "\n\n";
}

void printTable(const ostream& os, int min, int max)
{
	printTableHeader(os, min, max);
	
	for (int row = min; row <= max; ++row)
		printTableRow(os, row, min, max);
}