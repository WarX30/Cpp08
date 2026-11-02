
#include "../include/MutantStack.hpp"
#include "../include/color.hpp"

#include <iostream>
#include <ostream>
#include <string>
#include <stack>

void printSection(const std::string &title)
{
    std::cout << BOLD_ON CYAN << "\n\n========== "
              << title
              << " ==========\n" << BOLD_OFF << std::endl;
}

void printResult(const std::string &test, bool success)
{
	if (success)
		std::cout << BOLD_ON GREEN << "[PASS] " << BOLD_OFF;
	else
		std::cout << BOLD_ON RED << "[FAIL] " << BOLD_OFF;
	std::cout << BLUE << test << RESET << std::endl;
}

void testLIFO()
{
    printSection("TEST 1 - LIFO BEHAVIOR");

    MutantStack<int> mstack;

    mstack.push(10);
    mstack.push(20);
    mstack.push(30);

    printResult("Size is 3", mstack.size() == 3);
    printResult("Top is 30", mstack.top() == 30);

    mstack.pop();

    printResult("Top after pop is 20", mstack.top() == 20);
    printResult("Size after pop is 2", mstack.size() == 2);
}

void testNormalIterator()
{
    printSection("TEST 2 - NORMAL ITERATOR");

    MutantStack<int> mstack;

    mstack.push(10);
    mstack.push(20);
    mstack.push(30);
    mstack.push(40);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    std::cout << YELLOW << "Forward traversal: ";

    while (it != ite)
    {
        std::cout << *it;
        ++it;
        if (it != ite)
            std::cout << " -> ";
    }
    std::cout << RESET << std::endl;

    printResult("Begin points to 10", *mstack.begin() == 10);
    printResult("Last element is 40", *(--mstack.end()) == 40);
}

void testConstIterator()
{
    printSection("TEST 3 - CONST ITERATOR");

    MutantStack<int> original;

    original.push(100);
    original.push(200);
    original.push(300);

    const MutantStack<int> &mstack = original;
    MutantStack<int>::const_iterator it = mstack.begin();
    MutantStack<int>::const_iterator ite = mstack.end();

    std::cout << YELLOW << "Const traversal: ";

    while (it != ite)
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << RESET << std::endl;

    printResult("Const begin points to 100",
                *mstack.begin() == 100);
}

void testReverseIterator()
{
    printSection("TEST 4 - REVERSE ITERATOR");

    MutantStack<int> mstack;

    mstack.push(10);
    mstack.push(20);
    mstack.push(30);
    mstack.push(40);

    MutantStack<int>::reverse_iterator it = mstack.rbegin();
    MutantStack<int>::reverse_iterator ite = mstack.rend();

    std::cout << YELLOW << "Reverse traversal: ";

    while (it != ite)
    {
        std::cout << *it;
        ++it;
        if (it != ite)
            std::cout << " -> ";
    }
    std::cout << RESET << std::endl;

    printResult("Rbegin points to 40", *mstack.rbegin() == 40);
}

void testConstReverseIterator()
{
    printSection("TEST 5 - CONST REVERSE ITERATOR");

    MutantStack<int> original;

    original.push(10);
    original.push(20);
    original.push(30);

    const MutantStack<int> &mstack = original;

    MutantStack<int>::const_reverse_iterator it = mstack.rbegin();
    MutantStack<int>::const_reverse_iterator ite = mstack.rend();

    std::cout << YELLOW << "Const reverse traversal: ";

    while (it != ite)
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << RESET << std::endl;

    printResult("Const rbegin points to 30",
                *mstack.rbegin() == 30);
}

void testCopyConstructor()
{
    printSection("TEST 6 - COPY CONSTRUCTOR");

    MutantStack<int> original;

    original.push(10);
    original.push(20);
    original.push(30);

    MutantStack<int> copy(original);

    printResult("Copy has same size",
                copy.size() == original.size());
    printResult("Copy has same top",
                copy.top() == original.top());

    copy.pop();

    printResult("Copy can be modified independently",
                copy.size() == 2 && original.size() == 3);
}

void testAssignmentOperator()
{
    printSection("TEST 7 - ASSIGNMENT OPERATOR");

    MutantStack<int> original;
    MutantStack<int> assigned;

    original.push(10);
    original.push(20);
    original.push(30);

    assigned.push(999);
    assigned = original;

    printResult("Assigned stack has same size",
                assigned.size() == original.size());
    printResult("Assigned stack has same top",
                assigned.top() == original.top());

    assigned.pop();

    printResult("Assignment creates independent contents",
                assigned.size() == 2 && original.size() == 3);
}

void testStringType()
{
    printSection("TEST 8 - STRING TYPE");

    MutantStack<std::string> mstack;

    mstack.push("Hello");
    mstack.push("42");
    mstack.push("C++98");

    printResult("String top is C++98",
                mstack.top() == "C++98");

    MutantStack<std::string>::iterator it = mstack.begin();

    std::cout << YELLOW << "String traversal: ";

    while (it != mstack.end())
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << RESET << std::endl;
}

void testStdStackCompatibility()
{
    printSection("TEST 9 - STD::STACK COMPATIBILITY");

    MutantStack<int> mutant;
    std::stack<int> standard;

    int values[] = {5, 17, 3, 5, 737, 0};
    int i = 0;

    while (i < 6)
    {
        mutant.push(values[i]);
        standard.push(values[i]);
        ++i;
    }

    bool same = true;

    while (!standard.empty() && !mutant.empty())
    {
        if (standard.top() != mutant.top())
            same = false;

        standard.pop();
        mutant.pop();
    }

    printResult("Same LIFO sequence as std::stack",
                same && standard.empty() && mutant.empty());
}

void testSubjectExample()
{
    printSection("TEST 10 - SUBJECT EXAMPLE");

    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    printResult("Top is 17", mstack.top() == 17);

    mstack.pop();

    printResult("Top after pop is 5", mstack.top() == 5);

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    std::cout << YELLOW << "\nSubject traversal: ";

    while (it != ite)
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << RESET << std::endl;

    printResult("Size is 5", mstack.size() == 5);
    printResult("Top is 0", mstack.top() == 0);
}

int main()
{
    std::cout << BOLD_ON << YELLOW
              << "========== CPP08 - EX02 MUTANTSTACK =========="
              << BOLD_OFF << std::endl;

    testLIFO();
    testNormalIterator();
    testConstIterator();
    testReverseIterator();
    testConstReverseIterator();
    testCopyConstructor();
    testAssignmentOperator();
    testStringType();
    testStdStackCompatibility();
    testSubjectExample();

    printSection("END OF TESTS");

    return 0;
}
