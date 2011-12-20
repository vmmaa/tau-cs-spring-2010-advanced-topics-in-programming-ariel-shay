/******************************************************************************
 * Exercise 03 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Main Test File.
 *****************************************************************************/

#pragma once
#include "stdafx.h"
#include "parser.h"
#include "analyzer.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int main(void)
{
	// check identifiers
	Parser parser1("test_identifiers.txt");
	cout << parser1 << "\n";
	getchar();

	Analyzer analyzer1(parser1);
	cout << analyzer1 << "\n";
	getchar();

	// check brackets
	Parser parser2("test_brackets.txt");
	cout << parser2 << "\n";
	getchar();

	Analyzer analyzer2(parser2);
	cout << analyzer2 << "\n";
	getchar();

	// check if-else
	Parser parser3("test_if-else.txt");
	cout << parser3 << "\n";
	getchar();

	Analyzer analyzer3(parser3);
	cout << analyzer3 << "\n";
	getchar();

	// check keywords
	Parser parser4("test_keywords.txt");
	cout << parser4 << "\n";
	getchar();

	Analyzer analyzer4(parser4);
	cout << analyzer4 << "\n";
	getchar();

	return 0;
}

