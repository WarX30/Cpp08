#pragma once

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

class Span
{
	private:
		std::vector<int> _numbers;
		unsigned int _maxSize;

	public:
		Span();
		Span(unsigned int n);
		Span(const Span &other);
		Span &operator=(const Span &other);
		~Span();

		void addNumber(int n);

		template <typename It>
		void addNumber(It begin, It end)
		{
			typename std::iterator_traits<It>::difference_type count;
			count = std::distance(begin, end);
			if (count < 0)
				throw std::runtime_error("Invalid range");	
			if (static_cast<unsigned long>(count) >
					this->_maxSize - this->_numbers.size())
				throw std::runtime_error("Span capacity exceeded");
			while (begin != end)
			{
				addNumber(*begin);
				++begin;
			}
		}
		int shortestSpan() const;
		int longestSpan() const;
};
