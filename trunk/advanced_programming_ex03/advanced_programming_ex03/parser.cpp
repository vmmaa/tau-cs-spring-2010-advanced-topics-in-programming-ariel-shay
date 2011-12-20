/******************************************************************************
 * Exercise 03 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Parser - Source File.
 *****************************************************************************/

#pragma once
#include "stdafx.h"
#include "parser.h"
#include "exception2.h"

/* CTORs and DTORs ***********************************************************/
/* CTOR - Parse immediatley upon creation. */
Parser::Parser(const char* filepath):
	m_tokenCount(0),
	m_isParsed(false)
{
	// TODO: Initialize members.
	parse(filepath);
}

/* DTOR - Default. */
Parser::~Parser(void)
{
	m_lineVector.~vector();
}

/* METHODS *******************************************************************/
/* void parse(const string filepath).
 * Starts the parsing process of the given file.
 * $filepath - The path of the file to be parsed. */
void Parser::parse(const char* filepath)
{
	// Variables.
	string     line;

	// Open file.
	ifstream file (filepath);
	try {
		if (!file.is_open())
		{
			throw exFile;
		}
		while (!file.eof())
		{
			// Extract raw line and make it into InputLine.
			getline(file, line);
			InputLine inputLine(line);
			m_lineVector.push_back(inputLine);
			m_tokenCount += inputLine.getTokensCount();
		}
			
		file.close();

		// mark as parsed
		m_isParsed = true;
	} catch (exception& e)
	{
		cout << e.what() << endl;
	}
}

/* GETTERS *******************************************************************/
/* inline int getLineCount() const.
 * @RETURN: line count of last processed input file. */
inline int Parser::getLineCount() const
{
	return (int) m_lineVector.size();
}

/* inline int getLineTokenCount(int line) const.
 * $line  : the line to count the tokens in.
 * @pre   : 0 <= line < getLineCount(). 
 * @RETURN: token count of last processed input file in given line. */
inline int Parser::getLineTokenCount(int line) const
{
	return m_lineVector[line].getTokensCount();
}

/* inline int getTokenCount() const.
 * @RETURN: total token count of last processed input file. */
inline int Parser::getTokenCount() const
{
	return m_tokenCount;
}

/* inline bool isParsed() const.
 * @RETURN: true iff the given file is parsed on construction, false if an error occured on contruction */
inline bool Parser::isParsed() const
{
	return m_isParsed;
}

/* inline const vector<InputLine> const
/* @RETURN: the input-lines vector where each line is tokenized. */
inline const vector<InputLine>& Parser::getLineVector() const{
	return m_lineVector;
}

/* OPERATORS ***************************************************************/
/* overloading operator << for printing parsing contents */
ostream& operator<< (ostream& os, const Parser& pi_parser){
	if (pi_parser.isParsed()){
		// print initial information
		os << "Number of lines in parsed file:  " << pi_parser.getLineCount() << "\n";
		os << "Number of tokens in parsed file: " << pi_parser.getTokenCount() << "\n";

		// print lines contents
		vector<InputLine> v = pi_parser.getLineVector();
		for (int i=0; i < (int) v.size(); i++){
			// print line
			os << "line " << (i+1) << ":\t";
			vector<Token> line = v[i].getTokenizedLine();
			for (int j=0; j< (int) line.size(); j++){
				os << "'" << line[j].getValue() << "' ";
			}
			os << "\n";
		}
	} else {
		os << "File not parsed\n";
	}

	return os;
}