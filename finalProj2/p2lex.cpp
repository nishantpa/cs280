/* Nishant Patel; Oct 27 2016; cs280 */
/* This file implements	getToken() function && overrides <<operator */

#include "p2lex.h"
#include <iostream>
#include <ios>
#include <map>
#include <istream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

string word, ch;
extern vector<string> verboseOut;
extern bool verbose;

Token getToken(istream *instream) 
{
	// Build lexeme
	string word;
	char ch;


	// EOF? : DONE
	if ( instream->peek() == std::ifstream::traits_type::eof() ) 
	{
		 Token temp(DONE, "eof");
		 return temp;
	} 


/* Now, work on all the cases you can have of ch->get() */	
	

// Start building lexeme. Falls into IFs	
ch = instream->get();


	// Newline? : linenum++ 
	if (ch == '\n')	
	{
		linenum++;
		// ch = instream->get() ??	
	}


	// IF blanks, move get() onward
	while (isspace(ch) ) 
	{
		ch = instream->get();
	}

	// "+"? : return Token
	if (ch == '+') 
	{
		Token temp(PLUS, "+");
		string s(1, ch);
		verboseOut.push_back("plus");
		return temp;
	}


	// "*"? : return Token
	if (ch == '*') 
	{
		Token temp(STAR, "*");
		string s(1, ch);
		verboseOut.push_back("star");
		return temp;
	}


	// "["? : return Token
	if (ch == '[') 
	{
		Token temp(LEFTSQ, "[");
		string s(1, ch);
		verboseOut.push_back("leftsq");
		return temp;
	}
	

	// "]"? : return Token
	if (ch == ']') 
	{
		Token temp(RIGHTSQ, "]");
		string s(1, ch);
		verboseOut.push_back("rightsq");
		return temp;
	}

	
	// "("? : return Token
	if (ch == '(') 
	{
		Token temp(LPAREN, "(");
		string s(1, ch);
		verboseOut.push_back("lparen");
		return temp;
	}


	// ")"? : return Token
	if (ch == ')') 
	{
		Token temp(RPAREN, "(");
		string s(1, ch);
		verboseOut.push_back("rparen");
		return temp;
	}


	// ";"? : return Token
	if (ch == ';') 
	{
		Token temp(SC, ";");
		string s(1, ch);
		verboseOut.push_back("sc");
		return temp;
	}


	// "INT"? : return Token
	if (isdigit(ch)) 
	{
		string s(1, ch);
		Token temp (INT, s);
		s.insert(0, "int(");
		s.push_back(')');
		verboseOut.push_back(s);
		return temp;
	}


	// Entering "string"
	if (ch == '"') 
	{
		 word += ch;
		 ch = instream->get();

		 while (ch != '"') 
		 {
		 	word += ch;
			ch = instream->get();

			if (ch == '\n') 
			{
				Token temp(ERR, word);

				// IF ERR while in verbose mode
				if (verbose) 
				{
					for (int i = 0; i < verboseOut.size(); i++) 
				  	{
				  	    cout << verboseOut[i] << endl;
				  	}
				}

				cout << "err("<< word << ")" << endl;
				exit(1);
			}
		 }
		
		word.insert(0, "str(");
		word.push_back('"');
		word.push_back(')');

		Token temp(STR, word);
		verboseOut.push_back(word);

		return temp;	 
	}


	// Maybe entering comment
	if (ch == '/') 
	{
		if ( instream->peek() == '/')
		{
			while (ch != '\n') 
				ch = instream->get();
		}

		// Check if you need this. Skeptical here
		ch = instream->get();
	}

	/* Checked indiv char tokens. Now need to check IDs, KEYWORDs (print, set) */

	// ID? : Build lexeme
	if (isalpha(ch)) 
	{
		word += ch;
		ch = instream->get();

			// get to end of word
			while (isalpha(ch))
			{
				word+= ch;
				ch = instream->get();
			}
		
		
		if (word.compare("print") == 0) 
		{
			    Token temp (PRINT, word);
			    verboseOut.push_back(word);
			    
			    return temp;
		} else if (word.compare("set") == 0) 
		  {
			  	  Token temp (SET, word);
			  	  verboseOut.push_back(word);

			  	  return temp;
		  } 

		word.insert(0, "id(");
		word.push_back(')');	
		
		verboseOut.push_back(word);
		Token temp(ID, word);

		return temp;
	}

	/* NOT returning anything. IF returning empty token, shows as ERR in output */

}



