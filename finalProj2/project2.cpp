// << Swami Shreeji >>
/* Nishant Patel; Oct 27, 2016; cs280 Proj2 Lexer */

// Oct 3 2017 - Adding instructions on how to compile/run in README.txt

#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include "p2lex.h"

using namespace std;

// Track line number
int linenum = 0;

// Prep Verbose mode
bool verbose = false;
vector<string> verboseOut;

int main(int argc, char* argv[])
{	
	string userInput;
	istream *reader;
	ifstream infile;

	// Keeps a count of diff tokens
    map <TokenType,int> counters;

    // Keeps count of uniq lexemes
    map<TokenType, map<string,int> > x;

    // Temp token
    Token t;

    map <TokenType, string> TokRep = {
    	  { ID, "id" }
    	, { STR, "str" }
    	, { INT, "int" }
    	, { PLUS, "plus" }
    	, { STAR, "star" }
    	, { LEFTSQ, "leftsq" }
    	, { RIGHTSQ, "rightsq" }
    	, { PRINT, "print" }
    	, { SET, "set" }
    	, { SC, "sc" }
    	, { LPAREN, "lparen" }
    	, { RPAREN, "rparen" }
    	, { DONE, "done" }
    	, { ERR, "err" } 
    };

    /* argc */
	// NO input file
	if (argc == 1) 
	{
		cout << "Reading from stdin" << endl;
		getline (cin, userInput);
	} 


	 // Input file ONLY
	 else if (argc == 2 && strcmp(argv[1], "-v") != 0) 
	 	{
	 		infile.open(argv[1]);
	 		if (infile.is_open() ) reader = &infile;
	 	}


	 // Optional -v, and input file	
	 else if (argc == 3) 
	 	{
	 		if (strcmp(argv[1], "-v") == 0)
	 		{
	 			verbose = true;
	 			infile.open(argv[2]);
	 			if (infile.is_open() ) reader = &infile;
	 			
	 			cout << "Verbose mode" << endl;
	 		}


	 		// IF argv[1] != "-v" --- THEN ERROR
	 		 else 
	 		 {
	 			cout << "USAGE: " << argv[0] << " ('-v')? followed by [filename]" << endl;
	 			return 1;
	 		 }


	      // IF argc > 3, ERROR
	 	} else 
	 	  {
	 	 	  cout << "Max 2 args. USAGE: " << argv[0] << " ('-v')? followed by [filename]" << endl;
	 	 	  return 1;
	 	  } // end check for -v, and correct count of args


	 // check: working on stdin or file?
	 if (userInput.size() != 0) 
	 {
	 	  cout << "Need to getToken() on user input" << endl;
	 } else 
	  {
	  	   while (true) 
	  	   {
	  	   	    t = getToken(reader);
	  	   	    counters[t.getTok()]++;

	  	   	    x[t.getTok()][t.getLexeme()]++;

	  	   	    if (t.getTok() == DONE) 
	  	   	    {
	  	   	    	break;
	  	   	    }
	  	   } // end getToken() loop
	  }

/* Still need to handle userInput --> getToken() */

	  // If verbose FLAG TRUE : cout << verboseOut
	  if (verbose) 
	  {
	  	   for (int i = 0; i < verboseOut.size(); i++) 
	  	   {
	  	   	    cout << verboseOut[i] << endl;
	  	   }
	  }
	  
	  // Iterate through maps, grab string rep and count of the number of times
	  for (map<TokenType, int>::iterator it = counters.begin(); it != counters.end(); it++) 
	  {
        cout << TokRep[it->first] << ": " << it->second << endl;
      }

      cout << "Number of uniq lexemes for ID: " << x[ID].size() << endl;
      cout << "Number of uniq lexemes for STR: " << x[STR].size() << endl;
      cout << "Number of uniq lexemes for INT: " << x[INT].size() << endl;
      
    // For it to NOT SEG FAULT on AFS. NJIT requirement, else it works with return 0 normally
    exit (1);  
	return 0;
}
