/******************************************************************************
 * Exercise 03 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Analyzer - Source File.
 *****************************************************************************/

#pragma once
#include "stdafx.h"
#include "analyzer.h"
#include "exception1.h"

/*************
* CTOR, DTOR
**************/

/* CTOR - constructor from parser object */
Analyzer::Analyzer(const Parser & parser):
	m_parser(parser)
{
	analyze();
}

/* DTOR - default DTOR */
Analyzer::~Analyzer(){
	m_errors.~vector();
	// not cleaning since the members are static anyway.
}

/*************
*	Methods
**************/

/* analyze */
/* analyzes the parser object, which contains the tokenized data */
void Analyzer::analyze(void){
	// define counters for testing legal syntax
	int ifElseCount = 0;	// counter for 'if' and 'else'
	int parCount = 0;		// counter for '(' and ')'
	int sparCount = 0;		// counter for '[' and ']'
	int tparCount = 0;		// counter for '{' and '}'
	
	// iterate over all input lines and check for errors
	try {
		if (!m_parser.isParsed()) {
			throw exParse;
		}
		
		// print lines contents
		vector<InputLine> v = m_parser.getLineVector();
		for (int i=0; i < (int) v.size(); i++){
			vector<Token> line = v[i].getTokenizedLine();
			stringstream ss; ss << (i+1);
			string lineNum = ss.str();
			
			Token* prevPrevTok = NULL;
			Token* prevTok = NULL;
			Token* currTok;
			
			for (int j=0; j < (int) line.size(); j++){
				stringstream ss2; ss2 << (j+1);
				string tokNum = ss2.str();
				currTok = &line[j];

				// check if started comment, if so continue to next line (break)
				if (currTok->getValue() == "//") break;

				TokenWord tw = currTok->getTokenWord();
				char c;
				
				switch (tw){
					// check #1: parenthesis check
					case DEL_PAR_L:
						parCount++;
						break;
					case DEL_PAR_R:
						parCount--;
						if (parCount < 0){
							string errMsg = "line "+lineNum+", token "+tokNum+": illegal round parenthesis, too many ')'";
							m_errors.push_back(errMsg);
						}
						break;
					case DEL_SPAR_L:
						sparCount++;
						break;
					case DEL_SPAR_R:
						sparCount--;
						if (sparCount < 0){
							string errMsg = "line "+lineNum+", token "+tokNum+": illegal brackets, too many ']'";
							m_errors.push_back(errMsg);
						}
						break;
					case DEL_TPAR_L:
						tparCount++;
						break;
					case DEL_TPAR_R:
						tparCount--;
						if (tparCount < 0){
							string errMsg = "line "+lineNum+", token "+tokNum+": illegal curly brackets, too many '}'";
							m_errors.push_back(errMsg);
						}
						break;

					// check #2: if-else check
					case KEY_IF:
						ifElseCount++;
						break;
					case KEY_ELSE:
						ifElseCount--;
						if (ifElseCount < 0){
							string errMsg = "line "+lineNum+", token "+tokNum+": too many 'else' statements";
							m_errors.push_back(errMsg);
						}
						break;

					// check #3: variables checks
					case CUSTOM:
						// check if it's a number (double or int etc.), if so skip it
						if (isNumber(currTok->getValue())) break;

						// check that doesn't start with a non-alphabet character
						c = currTok->getValue().at(0);
						if (c < 65 || (c > 90 && c < 97) || c > 122){
							string errMsg = "line "+lineNum+", token "+tokNum+": cannot start identifier with a non-alphabetical character: "+c;
							m_errors.push_back(errMsg);
							break; // do not continue checks on variable
						}
						// check declaration rules
						if (prevTok != NULL && prevTok->getMasterTokenWord() == TYPE){
							if (prevPrevTok != NULL && prevPrevTok->getMasterTokenWord() == TYPE){
								// double definition
								string errMsg = "line "+lineNum+", token "+tokNum+": double type definition for token "+currTok->getValue();
								m_errors.push_back(errMsg);
							} else {
								// check if already defined
								if (m_symbolTable.find(currTok->getValue()) != m_symbolTable.end()){
									string errMsg = "line " +lineNum+", token "+tokNum+": variable "+currTok->getValue()+" already defined, cannot redefine as "+prevTok->getValue();
									m_errors.push_back(errMsg);
								} else {
									// put variable in symbol table
									m_symbolTable.insert(make_pair(currTok->getValue(),prevTok->getTokenWord()));
								}
							}
						} else {
							// this is not a definition. check if defined, else error
							if (m_symbolTable.find(currTok->getValue()) == m_symbolTable.end()){
								string errMsg = "line "+lineNum+", token "+tokNum+": variable "+currTok->getValue()+" is used before declared";
								m_errors.push_back(errMsg);
							}
						}
						break;

					// no errors found - do nothing
					default:
						break;
				}

				// update prevTok, prevPrevTok:
				prevPrevTok = prevTok;
				prevTok = currTok;
			}
			
			// tests when finishing row
			// check that line ends with a ';' ???
		}

		// tests when finishing all lines:
		// check number of all parenthesis:
		if (parCount != 0){
			string errMsg = "end of file: illegal number of round parenthesis";
			m_errors.push_back(errMsg);
		}
		if (sparCount != 0){
			string errMsg = "end of file: illegal number of brackets";
			m_errors.push_back(errMsg);
		}
		if (tparCount != 0){
			string errMsg = "end of file: illegal number of curly brackets";
			m_errors.push_back(errMsg);
		}
		// check number of if-else:
		if (ifElseCount < 0){
			string errMsg = "end of file: too many 'else' in the file";
			m_errors.push_back(errMsg);
		}
	} 
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
}

/* getSymbolTable */
/* getter for the parsed file symbol table */
inline const map<string,TokenWord> Analyzer::getSymbolTable() const{
	return m_symbolTable;
}

/* getErrorList */
/* getter for the errors vector */
inline const vector<string> Analyzer::getErrorList() const{
	return m_errors;
}

/***************
*	operators
***************/
/* overloading operator << for printing analysis results */
ostream& operator<< (ostream& os, const Analyzer& pi_analyzer){
	os << "List of errors:\n";
	for (int i=0; i< (int) pi_analyzer.m_errors.size(); i++){
		os << pi_analyzer.m_errors[i] << "\n";
	}

	return os;
}

/*********************
*	private methods
*********************/

/* isNumber */
/* returns true iff the given string is a number (int, double etc.) and false otherwise */
bool Analyzer::isNumber(string str) const{
	bool seenDot = false;
	string digits = "1234567890";

	// first check that doesn't start with a '.'
	if (str.at(0) == '.') return false;

	// check the string
	for(int i=0; i<(int)str.size(); i++){
		const char c = str.at(i);
		if (c == '.'){
			if (seenDot) return false; // to many dots
			else seenDot = true;
			continue; // don't also check if it's a number
		}
		if (digits.find(c) == string::npos) return false; // also not a number
	}

	// past test
	return true;
}