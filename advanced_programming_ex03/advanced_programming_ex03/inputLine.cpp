/******************************************************************************
 * Exercise 03 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * InputLine - Source File.
 *****************************************************************************/

#pragma once
#include "stdafx.h"
#include "inputLine.h"
#include <utility>

/* STATIC MEMBERS ************************************************************/
bool InputLine::isTokenMapInit = false;
const string InputLine::sm_DEFAULT_DELIMITERS = " \t=+-*&()[]{};<>";
wordMap InputLine::sm_TOKENS_TYPE;
wordMap InputLine::sm_TOKENS_KEYWORDS;
wordMap InputLine::sm_TOKENS_OPERATORS_LEN2;
wordMap InputLine::sm_TOKENS_OPERATORS_LEN1;
wordMap InputLine::sm_TOKENS_DELIMITERS;
vector<wordMap> InputLine::sm_MAPS;

/* CTORs and DTORs ***********************************************************/
/* CTOR - Create from rawLine. */
InputLine::InputLine(const string rawLine):
	m_rawLine(rawLine)
{
	if (!isTokenMapInit)
	{
		isTokenMapInit = true;
		initMaps();
	}
	tokenize();
}

/* DTOR - Default. */
InputLine::~InputLine(void)
{
	m_tokenLine.~vector();
}

/* STATIC METHODS ************************************************************/
void InputLine::initMaps()
{
	sm_TOKENS_TYPE.insert(make_pair("char",TYPE_CHAR));
	sm_TOKENS_TYPE.insert(make_pair("short",TYPE_SHORT));
	sm_TOKENS_TYPE.insert(make_pair("int",TYPE_INT));
	sm_TOKENS_TYPE.insert(make_pair("long",TYPE_LONG));
	sm_TOKENS_TYPE.insert(make_pair("float",TYPE_FLOAT));
	sm_TOKENS_TYPE.insert(make_pair("double",TYPE_DOUBLE));
	sm_TOKENS_TYPE.insert(make_pair("void",TYPE_VOID));

	sm_TOKENS_KEYWORDS.insert(make_pair("if",KEY_IF));
	sm_TOKENS_KEYWORDS.insert(make_pair("else",KEY_ELSE));
	sm_TOKENS_KEYWORDS.insert(make_pair("for",KEY_FOR));
	sm_TOKENS_KEYWORDS.insert(make_pair("while",KEY_WHILE));
	sm_TOKENS_KEYWORDS.insert(make_pair("class",KEY_CLASS));
	sm_TOKENS_KEYWORDS.insert(make_pair("private",KEY_PRIVATE));
	sm_TOKENS_KEYWORDS.insert(make_pair("public",KEY_PUBLIC));
	sm_TOKENS_KEYWORDS.insert(make_pair("const",KEY_CONST));
	sm_TOKENS_KEYWORDS.insert(make_pair("virtual",KEY_VIRTUAL));

	sm_TOKENS_OPERATORS_LEN2.insert(make_pair("++",OP_2ADD));
	sm_TOKENS_OPERATORS_LEN2.insert(make_pair("--",OP_2SUB));
	sm_TOKENS_OPERATORS_LEN2.insert(make_pair("==",OP_2EQUAL));
	sm_TOKENS_OPERATORS_LEN2.insert(make_pair("->",OP_ARROW));
	sm_TOKENS_OPERATORS_LEN2.insert(make_pair("<<",OP_SHIFT_L));
	sm_TOKENS_OPERATORS_LEN2.insert(make_pair(">>",OP_SHIFT_R));
	
	sm_TOKENS_OPERATORS_LEN1.insert(make_pair("=",OP_ASSIGN));
	sm_TOKENS_OPERATORS_LEN1.insert(make_pair("+",OP_ADD));
	sm_TOKENS_OPERATORS_LEN1.insert(make_pair("-",OP_SUB));
	sm_TOKENS_OPERATORS_LEN1.insert(make_pair("*",OP_ASTERISK));
	sm_TOKENS_OPERATORS_LEN1.insert(make_pair("&",OP_AMPER));
	sm_TOKENS_OPERATORS_LEN1.insert(make_pair(">",DEL_GT));
	sm_TOKENS_OPERATORS_LEN1.insert(make_pair("<",DEL_LT));

	sm_TOKENS_DELIMITERS.insert(make_pair("(",DEL_PAR_L));
	sm_TOKENS_DELIMITERS.insert(make_pair(")",DEL_PAR_R));
	sm_TOKENS_DELIMITERS.insert(make_pair("[",DEL_SPAR_L));
	sm_TOKENS_DELIMITERS.insert(make_pair("]",DEL_SPAR_R));
	sm_TOKENS_DELIMITERS.insert(make_pair("{",DEL_TPAR_L));
	sm_TOKENS_DELIMITERS.insert(make_pair("}",DEL_TPAR_R));
	sm_TOKENS_DELIMITERS.insert(make_pair(";",DEL_SEMICOL));
	
	sm_MAPS.push_back(sm_TOKENS_TYPE);
	sm_MAPS.push_back(sm_TOKENS_KEYWORDS);
	sm_MAPS.push_back(sm_TOKENS_OPERATORS_LEN2);
	sm_MAPS.push_back(sm_TOKENS_OPERATORS_LEN1);
	sm_MAPS.push_back(sm_TOKENS_DELIMITERS);
}

Token InputLine::generateToken(string rawString)
{
	wordMap::iterator it;
	int i;
	int size = (int) sm_MAPS.size();
	for (i = 0; i < size; i++)
	{
		it = sm_MAPS[i].find(rawString);
		if (it != sm_MAPS[i].end())
		{
			TokenWord tok = it->second;
			Token token(Token::getMasterFromTokenWord(tok),tok,rawString);
			return token; // changed from ""
		}
	}
	Token token(USER_DEFINED,CUSTOM,rawString);
	return token;
}

/* METHODS *******************************************************************/
/* void tokenize();
 * Tokenizes the rawLine member of the InputLine object. */
void InputLine::tokenize()
{
	int lastInd = 0;
	int tempInd = 0;
	// Find first token (in case delimiters in begining).
		int firstInd = m_rawLine.find_first_of(sm_DEFAULT_DELIMITERS);
		if (!firstInd && m_rawLine.npos != firstInd+1 && 
					sm_TOKENS_OPERATORS_LEN2.find(m_rawLine.substr(firstInd,2)) != sm_TOKENS_OPERATORS_LEN2.end())
		{
			firstInd = 0;
			lastInd = 2;
		}
	// Find where the first token ends.
		else if (firstInd) {
			firstInd = m_rawLine.find_first_not_of(sm_DEFAULT_DELIMITERS);
    		lastInd = m_rawLine.find_first_of(sm_DEFAULT_DELIMITERS, firstInd);
		}
		else
		{
			firstInd = 0;
			lastInd = 1;
		}

	while (m_rawLine.npos != lastInd || m_rawLine.npos != firstInd)
	{
		// Generate new token according to indices and analyzed type.
		string tempString = m_rawLine.substr(firstInd, lastInd-firstInd);
		if (tempString != " " && tempString != "	")
		{
			Token tempToken = generateToken(tempString);
    		// Add token.
			m_tokenLine.push_back(tempToken);
		}
    	// Update position of next token and check for double operators.
		tempInd = m_rawLine.find_first_of(sm_DEFAULT_DELIMITERS, lastInd);
		if (tempInd > lastInd) {
			firstInd = lastInd;
			lastInd = m_rawLine.find_first_of(sm_DEFAULT_DELIMITERS, firstInd);
		} else {
			firstInd = tempInd;
			if (firstInd > -1)
			{
				if (m_rawLine.npos != firstInd+1 && 
					sm_TOKENS_OPERATORS_LEN2.find(m_rawLine.substr(firstInd,2)) != sm_TOKENS_OPERATORS_LEN2.end())
				{
					lastInd = firstInd + 2;
				} else 
				{
					lastInd = firstInd + 1;
				}
			}
		// Find where the first token ends.
			else {
				firstInd = m_rawLine.find_first_not_of(sm_DEFAULT_DELIMITERS, lastInd);
    			lastInd = m_rawLine.find_first_of(sm_DEFAULT_DELIMITERS, firstInd);
			}
		}
    	/*firstInd = m_rawLine.find_first_not_of(sm_DEFAULT_DELIMITERS, lastInd);
    	// Update position of end of next token.
    	lastInd = m_rawLine.find_first_of(sm_DEFAULT_DELIMITERS, firstInd);*/
	}
}

/* GETTERS *******************************************************************/
/* inline string getRawLine() const.
 * @RETURN: the raw string line originally given to the InputLine object. */
inline string InputLine::getRawLine() const
{
	return m_rawLine;
}

/* inline vector<string> getTokenizedLine() const.
 * @RETURN: returns the tokenized line of the InputLine object. */
vector<Token> InputLine::getTokenizedLine() const
{
	return m_tokenLine;
}

/* int getTokensCount() const.
 * @RETURN: returns the number of tokens of an InputLine object. */
int InputLine::getTokensCount() const
{
	return (int) m_tokenLine.size();
}

