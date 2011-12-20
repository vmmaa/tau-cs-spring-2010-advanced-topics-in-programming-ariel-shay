/******************************************************************************
 * Exercise 03 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * inputLine - Header File.
 *****************************************************************************/

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "token.h"
using namespace std;

typedef map<string, TokenWord> wordMap;

class InputLine
{
	public:
		// CTORs, DTORs
		InputLine(const string rawLine);
		virtual ~InputLine(void);

		// Getters:
		inline string  getRawLine()       const;
		vector<Token>  getTokenizedLine() const;
		int            getTokensCount()   const;

	protected:
		// Functions:
		void virtual tokenize();
		void static initMaps();
		Token static generateToken(string rawString);

		// Members:
		string         m_rawLine;
		vector<Token>  m_tokenLine;


		// Static Members:
		static bool  isTokenMapInit;
		static const string sm_DEFAULT_DELIMITERS;
		static wordMap sm_TOKENS_TYPE;
		static wordMap sm_TOKENS_KEYWORDS;
		static wordMap sm_TOKENS_OPERATORS_LEN2;
		static wordMap sm_TOKENS_OPERATORS_LEN1;
		static wordMap sm_TOKENS_DELIMITERS;
		static vector<wordMap> sm_MAPS;
};