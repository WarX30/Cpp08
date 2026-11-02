#include "../include/Span.hpp"
#include "../include/color.hpp"

#include <algorithm>
#include <climits>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <vector>

Span::Span() : _numbers(), _maxSize()
{
	std::cout << BOLD_ON
			  << "A defalut constructor called"
			  << BOLD_OFF << std::endl;
}

Span::Span(unsigned int n) : _numbers(), _maxSize(n)
{
	std::cout << BOLD_ON YELLOW
			  << "A constructor called"
			  << BOLD_OFF << std::endl;
}

Span::Span(const Span &other) :
	_numbers(other._numbers), _maxSize(other._maxSize)
{
	std::cout << BOLD_ON YELLOW
			  << "A copy constructor called"
			  << BOLD_OFF << std::endl;
}

Span	&Span::operator=(const Span &other)
{
	if (this != &other)
	{
		this->_numbers = other._numbers;
		this->_maxSize = other._maxSize;
	}
	std::cout << BOLD_ON YELLOW
			  << "Assignement Operator called"
			  << BOLD_OFF << std::endl;
	return (*this);
}

Span::~Span()
{
	std::cout << BOLD_ON RED
			  << "A destructor called"
			  << BOLD_OFF << std::endl;
}

void Span::addNumber(int n)
{
	if (this->_numbers.size() >= this->_maxSize)
		throw std::runtime_error("Span is full");
	this->_numbers.push_back(n);
}

int	Span::shortestSpan() const
{
	if (this->_numbers.size() < 2)
		throw std::runtime_error("Not enough numbers");

	std::vector<int> sorted = this->_numbers;
	std::sort(sorted.begin(), sorted.end());

	long long minSpan = LLONG_MAX;
	for (std::size_t i = 0; i < sorted.size() - 1; i++)
	{
		long long diff = static_cast<long long>(sorted[i + 1])
			- static_cast<long long>(sorted[i]);
		if (minSpan > diff)
			minSpan = diff;
	}
	if (minSpan > INT_MAX)
		throw std::overflow_error("Integer overflow");
	return (static_cast<int>(minSpan));
}

int	Span::longestSpan() const
{
	if (this->_numbers.size() < 2)
		throw std::runtime_error("Not enough numbers");

	int  min = *std::min_element(this->_numbers.begin(), this->_numbers.end());
	int	 max = *std::max_element(this->_numbers.begin(), this->_numbers.end());
	long long value = static_cast<long long>(max) - static_cast<long long>(min);
	if (value > std::numeric_limits<int>::max())
		throw std::overflow_error("Integer overflow");
	return (static_cast<int>(value));
}
