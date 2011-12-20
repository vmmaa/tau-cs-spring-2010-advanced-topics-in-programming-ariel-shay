/******************************************************************************
 * Exercise 03 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Parser - Header File.
 *****************************************************************************/

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "inputLine.h"
using namespace std;

/* The Parser class acts as a wraper to the whole parsing process. 
 * A Parser objects manages the parsing process, by reading a file, and calling
 * to method of InputLine and Analyzer objects (which it contains) in a 
 * chronological way. */
class Parser
{
	public:
		// CTORs, DTORs
		Parser(const char* filepath);
		virtual ~Parser(void);

		// Methods:
		void virtual parse(const char* filepath);

		// Getters:
		inline int getLineTokenCount(int line) const;
		inline int getTokenCount()             const;
		inline int getLineCount()              const;
		inline bool isParsed()				   const;
		inline const vector<InputLine>& getLineVector() const;
		
		// Operators:
		friend ostream& operator<< (ostream& os, const Parser& pi_parser);

	protected:
		// Members:
		vector<InputLine> m_lineVector;
		int               m_tokenCount;
		bool			  m_isParsed;
};
