/******************************************************************************
 * Exercise 03 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Analyzer - Header File.
 *****************************************************************************/

#include "inputLine.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <sstream>
#include <iostream>
using namespace std;

class Analyzer
{
	public:
		// CTORs, DTORs
		Analyzer(const Parser & parser);
		virtual ~Analyzer(void);

		// methods:
		void virtual analyze(void);

		// getters:
		inline const map<string,TokenWord> getSymbolTable() const;
		inline const vector<string> getErrorList() const;

		// operators:
		friend ostream& operator<< (ostream& os, const Analyzer& pi_analyzer);

	protected:
		// map from identifier name to type
		map<string,TokenWord> m_symbolTable;
		vector<string> m_errors;
		const Parser &m_parser;

	private:
		// methods:
		bool isNumber(string str) const;
};
