/******************************************************************************
 * Exercise 03 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Token - Source File.
 *****************************************************************************/

#include "stdafx.h"
#include "token.h"
using namespace std;

/***************
*	CTOR, DTOR
****************/

/* CTOR - create from enums and value */
Token::Token(MasterTokenWord masterWord, TokenWord word, const string value = ""):
m_master(masterWord),
m_word(word),
m_value(value){
}

/* CTOR - create from enum and value */
/*Token::Token(TokenWord word, const string value = ""):
m_word(word),
m_value(value){
}*/

/* DTOR - default DTOR */
Token::~Token(){}

/************
*	Getters
*************/

/* getMasterTokenWord */
/* returns the MasterTokenWord of the Token */
MasterTokenWord Token::getMasterTokenWord() const{
	return m_master;
}

/* getTokenWord */
/* returns the TokenWord of the Token */
TokenWord Token::getTokenWord() const{
	return m_word;
}

/* hasValue */
/* returns true iff the token has value, i.e. user defined */
inline bool Token::hasValue() const{
	return !(m_value.empty());
}

/* getValue */
string Token::getValue() const{
	return m_value;
}

/*********************
*	static functions
*********************/

/* getMasterFromTokenWord */
/* returns the MastertokenWord related to the TokenWord */
MasterTokenWord Token::getMasterFromTokenWord(TokenWord tw){ 
	if (tw == TYPE_CHAR || tw == TYPE_SHORT || tw == TYPE_INT || tw == TYPE_LONG ||
		tw == TYPE_FLOAT || tw == TYPE_DOUBLE || tw == TYPE_VOID){
			return TYPE;
	} else if (tw == KEY_IF || tw == KEY_ELSE || tw == KEY_FOR || tw == KEY_WHILE ||
		tw == KEY_CLASS || tw == KEY_PRIVATE || tw == KEY_PUBLIC || tw == KEY_CONST || tw == KEY_VIRTUAL){
			return KEYWORD;
	} else if (tw == OP_2ADD || tw == OP_2SUB || tw == OP_2EQUAL || tw == OP_ARROW ||
		tw == OP_SHIFT_L || tw == OP_SHIFT_R){
			return OPERATORS_LEN2;
	} else if (tw == OP_ASSIGN || tw == OP_ADD || tw == OP_SUB || tw == OP_ASTERISK ||
		tw == OP_AMPER || tw == DEL_GT || tw == DEL_LT){
			return OPERATORS_LEN1;
	} else if (tw == DEL_PAR_L || tw == DEL_PAR_R || tw == DEL_SPAR_L || tw == DEL_SPAR_R ||
		tw == DEL_TPAR_L || tw == DEL_TPAR_R || tw == DEL_SEMICOL){
			return DELIMITER;
	} else {
		return USER_DEFINED;
	}
}