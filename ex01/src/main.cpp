#include "../include/Span.hpp"
#include "../include/color.hpp"

#include <climits>
#include <cstdlib>
#include <ctime>
#include <string>

void printSection(const std::string &title)
{
	std::cout << "\n" << BOLD_ON YELLOW
			  << "\n========== " << title << " =========="
			  << BOLD_OFF << std::endl;
}

void printResult(const std::string &test, bool success)
{
	if (success)
		std::cout << BOLD_ON GREEN << "[PASS] "
				  << test << BOLD_OFF << std::endl;
	else
		std::cout << BOLD_ON RED << "[FAIL] "
				  << test << BOLD_OFF << std::endl;
}

void testSpans(Span &span, int expectedShort, int expectedLong,
			   const std::string &test)
{
	try
	{
		int shortest = span.shortestSpan();
		int longest = span.longestSpan();

		std::cout << test << std::endl;
		std::cout << "Shortest span: " << shortest << std::endl;
		std::cout << "Longest span : " << longest << std::endl;

		printResult("Shortest span", shortest == expectedShort);
		printResult("Longest span", longest == expectedLong);
	}
	catch (const std::exception &e)
	{
		printResult(test + " : unexpected exception", false);
		std::cout << BOLD_ON BLUE << e.what()
				  << BOLD_OFF << std::endl;
	}
}

void testNotEnoughNumbers()
{
	printSection("TEST 1 - NOT ENOUGH NUMBERS");

	Span empty(5);

	try
	{
		empty.shortestSpan();
		printResult("Empty Span - shortestSpan", false);
	}
	catch (const std::runtime_error &e)
	{
		printResult("Empty Span - shortestSpan throws", true);
		std::cout << BOLD_ON BLUE << e.what() << BOLD_OFF << std::endl;
	}

	try
	{
		empty.longestSpan();
		printResult("Empty Span - longestSpan", false);
	}
	catch (const std::runtime_error &e)
	{
		printResult("Empty Span - longestSpan throws", true);
		std::cout << BOLD_ON BLUE << e.what() << BOLD_OFF << std::endl;
	}

	Span one(5);
	one.addNumber(42);

	try
	{
		one.shortestSpan();
		printResult("One number - shortestSpan", false);
	}
	catch (const std::runtime_error &e)
	{
		printResult("One number - shortestSpan throws", true);
		std::cout << BOLD_ON BLUE << e.what() << BOLD_OFF << std::endl;
	}

	try
	{
		one.longestSpan();
		printResult("One number - longestSpan", false);
	}
	catch (const std::runtime_error &e)
	{
		printResult("One number - longestSpan throws", true);
		std::cout << BOLD_ON BLUE << e.what() << BOLD_OFF << std::endl;
	}
}

void testNormalSpans()
{
	printSection("TEST 2 - NORMAL VALUES");

	Span span(5);

	span.addNumber(6);
	span.addNumber(3);
	span.addNumber(17);
	span.addNumber(9);
	span.addNumber(11);

	testSpans(span, 2, 14, "Values: 6, 3, 17, 9, 11");

	try
	{
		span.addNumber(100);
		printResult("Capacity exceeded", false);
	}
	catch (const std::runtime_error &e)
	{
		printResult("Capacity exceeded throws", true);
		std::cout << e.what() << std::endl;
	}
}

void testNegativeValues()
{
	printSection("TEST 3 - NEGATIVE VALUES");

	Span span(4);

	span.addNumber(-10);
	span.addNumber(-5);
	span.addNumber(-20);
	span.addNumber(-15);

	testSpans(span, 5, 15, "Values: -10, -5, -20, -15");
}

void testIdenticalValues()
{
	printSection("TEST 4 - IDENTICAL VALUES");

	Span span(3);

	span.addNumber(7);
	span.addNumber(7);
	span.addNumber(7);

	testSpans(span, 0, 0, "Values: 7, 7, 7");
}

void testCopyAndAssignment()
{
	printSection("TEST 5 - COPY CONSTRUCTOR");

	Span original(4);
	original.addNumber(10);
	original.addNumber(20);
	original.addNumber(30);

	Span copied(original);
	testSpans(copied, 10, 20, "Copy of original");

	printSection("TEST 6 - ASSIGNMENT OPERATOR");

	Span assigned(2);
	assigned = original;
	testSpans(assigned, 10, 20, "Assigned Span");
}

void testRangeAddition()
{
	printSection("TEST 7 - ADD A RANGE");

	std::vector<int> values;
	std::srand(std::time(0));

	for (int i = 1; i <= 10000; ++i)
		values.push_back(std::rand());

	Span span(10000);
	span.addNumber(values.begin(), values.end());

	testSpans(span, 1, 9999, "10,000 consecutive integers");
}

void testRangeExceedsCapacity()
{
	printSection("TEST 8 - RANGE EXCEEDS CAPACITY");

	std::vector<int> values;
	values.push_back(10);
	values.push_back(20);
	values.push_back(30);
	values.push_back(40);

	Span span(3);
	span.addNumber(values[0]);
	span.addNumber(values[1]);

	try
	{
		span.addNumber(values.begin(), values.end());
		printResult("Range exceeds capacity", false);
	}
	catch (const std::runtime_error &e)
	{
		printResult("Range exceeds capacity throws", true);
		std::cout << e.what() << std::endl;
	}

	/*
	 * Diagnostic: with the current template implementation,
	 * the first three numbers may already have been inserted
	 * before the fourth insertion throws.
	 */
	testSpans(span, 10, 10,
			  "Check state after failed range addition");
}

void testIntegerLimits()
{
	printSection("TEST 9 - INT_MIN AND INT_MAX");

	Span span(2);
	span.addNumber(INT_MIN);
	span.addNumber(INT_MAX);

	try
	{
		int result = span.shortestSpan();
		(void)result;
		printResult("shortestSpan overflow", false);
	}
	catch (const std::overflow_error &e)
	{
		printResult("shortestSpan detects overflow", true);
		std::cout << BOLD_ON BLUE << e.what() << BOLD_OFF << std::endl;
	}

	try
	{
		int result = span.longestSpan();
		(void)result;
		printResult("longestSpan overflow", false);
	}
	catch (const std::overflow_error &e)
	{
		printResult("longestSpan detects overflow", true);
		std::cout << BOLD_ON BLUE << e.what() << BOLD_OFF << std::endl;
	}
}

int main()
{
	printSection("CPP08 - EX01 SPAN");

	testNotEnoughNumbers();
	testNormalSpans();
	testNegativeValues();
	testIdenticalValues();
	testCopyAndAssignment();
	testRangeAddition();
	testRangeExceedsCapacity();
	testIntegerLimits();

	printSection("END OF TESTS");

	return (0);
}
