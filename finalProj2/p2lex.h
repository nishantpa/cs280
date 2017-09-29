// lexical analyzer header
// cs280
// problem 2
// fall 2016

#include <string>
#include <iostream>

// The Tokens I must account for
enum TokenType {
	ID,			// identifier
	STR,		// string
	INT,		// integer constant
	PLUS,		// the + operator
	STAR,		// the * operator
	LEFTSQ,		// the [
	RIGHTSQ,	// the ]
	PRINT,		// print keyword
	SET,		// set keyword
	SC,			// ; semicolon
	LPAREN,		// The (
	RPAREN,		// the )
	DONE,		// finished!
	ERR,		// an unrecoverable error
};

// Token class defined here. Tokens have following properties
class Token {
private:
	TokenType	tok;
	std::string	lexeme;

public:
	Token() : tok(ERR), lexeme("") {}
	Token(TokenType t, std::string s) : tok(t), lexeme(s) {}

	TokenType	getTok() const		{ return tok; }
	std::string	getLexeme() const	{ return lexeme; }

	// ==operator overloaded
	friend bool operator==(const Token& left, const Token& right) {
		return left.tok == right.tok;
	}

	// <<operator overloaded
	friend std::ostream& operator<<(std::ostream& out, const Token& t);
}; // end class Token definition 

extern	int	linenum;

// getToken() has ONLY 1 argument - it gets passed a pointer to file to read
extern	Token	getToken(std::istream* instream);
