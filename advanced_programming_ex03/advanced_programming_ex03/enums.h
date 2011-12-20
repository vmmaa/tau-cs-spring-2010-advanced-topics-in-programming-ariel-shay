/******************************************************************************
 * Exercise 03 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * TokenWord and MasterTokenWord enumerators - Header File.
 *****************************************************************************/

enum TokenWord{
	// Types
	TYPE_CHAR,
	TYPE_SHORT,
	TYPE_INT,
	TYPE_LONG,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_VOID,
	
	// Keywords
	KEY_IF,
	KEY_ELSE,
	KEY_FOR,
	KEY_WHILE,
	KEY_CLASS,
	KEY_PRIVATE,
	KEY_PUBLIC,
	KEY_CONST,
	KEY_VIRTUAL,

	// Operators of length 2
	OP_2ADD,
	OP_2SUB,
	OP_2EQUAL,
	OP_ARROW,
	OP_SHIFT_L,
	OP_SHIFT_R,

	// Operators of length 1
	OP_ASSIGN,
	OP_ADD,
	OP_SUB,
	OP_ASTERISK,
	OP_AMPER,
	DEL_GT,
	DEL_LT,	

	// Delimiters
	DEL_PAR_L,
	DEL_PAR_R,
	DEL_SPAR_L,
	DEL_SPAR_R,
	DEL_TPAR_L,
	DEL_TPAR_R,
	DEL_SEMICOL,

	// User-defined
	CUSTOM
};

// not in use for now
enum MasterTokenWord{
	TYPE,
	KEYWORD,
	OPERATORS_LEN2,
	OPERATORS_LEN1,
	DELIMITER,
	USER_DEFINED
};
