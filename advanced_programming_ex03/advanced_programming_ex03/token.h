/******************************************************************************
 * Exercise 03 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Token - Header File.
 *****************************************************************************/

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "enums.h"
using namespace std;

class Token
{
	public:
		// CTORs, DTORs
		Token(MasterTokenWord masterWord, TokenWord word, const string value);
		//Token(TokenWord word, const string value);
		~Token(void);

		// Getters:
		MasterTokenWord getMasterTokenWord() const;
		TokenWord getTokenWord() const;
		inline bool hasValue() const;
		string getValue() const;

		// static functions:
		static MasterTokenWord getMasterFromTokenWord(TokenWord tw);

	protected:

		// Members:
		MasterTokenWord m_master;
		TokenWord m_word;
		string m_value;
};