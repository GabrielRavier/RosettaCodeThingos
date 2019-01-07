#ifndef READLINESWORD_HPP_INCLUDED
#define READLINESWORD_HPP_INCLUDED

#include <istream>
#include <string>
#include <vector>
#include <iterator>

template <class outIterator> void readWords(std::istream& is, outIterator it)
{
	std::string word;
	while (is >> word)
		*it = word;
}

template <class outIterator> void readLines(std::istream& is, outIterator it)
{
	std::string line;
	while (std::getline(is, line))
		*it = line;
}

#endif