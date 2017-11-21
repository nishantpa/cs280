/* < das na das >

	@nishant patel; Mar 18 2017; cs341 proj2
	  "y" "n" Evaluate expression loop. TODO:
	  Implement PDA Rules entirely
	____________________________________________________________
	@Nishant Patel; Mar 18 2017; cs341 Proj2
	Implement a PDA for the expression specified
	  File created. Handled user input

	Σ = {a,b,c,...,z,A,B,C,...,Z,0,1,2,...,9,+,-,∗,/,(,),$, _ }

	
	S 	→ $T$
	T	→ T+T|T-T|T*T|T/T|(T)|CX|I → XX|C|N|_|ε
	X	→ XX|C|N|_|ε
	C	→ a|b|c|···|z|A|B|C|···|Z|
	N	→ 0|1|2|···|9
	I	→ NI|N

	Split up language into 3 parts:

	Σ1 = [a-zA-Z_]
	Σ2 = [0-9]
	Σ3 = [+ - * /]

	4 prints required:
		After each transition of the PDA, your program must print out the symbol that was read, the 
		symbol that was popped from the stack, the symbol that was pushed onto the stack, and the name 
		of the current state of the PDA.

	
	TO COMPILE: g++ -std=c++0x p2_17s_np358.cpp
	TO RUN: ./a.out

*/

#include <iostream>
#include <string>
#include <stack>
#include <cctype>
using namespace std;

	// To test expression
	int PDATest(string test) 
	{

		// All states of PDA. q5 trap state. 
		// q6 added later after needing adjustments
		enum transState {q0, q1, q2, q3, q4, q5, q6} state = q0;

		// PASS or FAIL flag
		bool result;

		// Stack holding pushed chars. Integral part of PDA
		stack <char> pda_stack;

		cout << "BEGIN. Starting at state q0" << endl;

		// getchar from string and test against PDA
		// States follow rules of PDA. See PDA drawing. State transitions and PDA must comply
		for (char& c : test) 
		{
			cout << "Symbol read: " << c << " ";
			switch (state) 
			{
				case q0:
					if (c == '$') 
					{
						state = q1;
						pda_stack.push(c);
						cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: " << c << endl;
						break;
					} else {
						state = q5;
						cout << "Current State: q" << state << endl;
						break;
					}

				case q1:
					if (c == '(') 
					{
						state = q1;
						pda_stack.push(c);
						cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: "  << c << endl;
						break;
					} 

					else if(isalpha(c) || c == '_') 
					 {
						state = q2;
						cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
						break;

					 } 

					else if (isdigit(c)) 
					 {
						state = q6;
						cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
						break;
					 }

				    else 
				     { // transition to trap

						state = q5;
						cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
						break;
					 }

				case q2:
					if (isalnum(c)) 
					{
						state = q2;
						cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
						break;
					} 

					else if (c == '_') 
					 {
						state = q2;
						cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
						break;
					 } 

					else if (c == '+' || c == '-' || c == '*' || c == '/')
					 {
						state = q1;
						cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
						break;
					 } 

					
					 else if (c == ')') 
					{
						cout << "Current state: q" << state << " Symbol popped: " << pda_stack.top() << ". Symbol pushed: <empty>" << endl;
						if (pda_stack.top() == '(' )
						{
							pda_stack.pop();
							break;
						} else {
							// cout << "\nUnbalanced parenthesis. TRANSITION TO TRAP STATE\n" << endl;
							state = q5;
							break;	
						}
						
					}

					else if (c == '$' && pda_stack.top() == '$')  
					 {
						state = q4;
						result = true;
						cout << "Current state: q" << state << " Symbol popped: " << pda_stack.top() << ". Symbol pushed: <empty>" << endl;
						pda_stack.pop();
						break;
					 }

					else {
						state = q5;
						cout << "Current State: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
						break;
					}

				case q3:
					if (c == '$') 
					{
						state = q4;
						result = true;
						cout << "Current state: q" << state << " Symbol popped: " << pda_stack.top() << ". Symbol pushed: <empty>" << endl;
						pda_stack.pop();
						break;
					}

					else if (c == '+' || c == '-' || c == '*' || c == '/') 
					 {
						state = q1;
						cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
						break;
					 }

					else if (c == '(') 
					 {
					 	state = q3;
					 	cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
					 	break;
					 }

				case q4:
					result = true;
					cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
					break;

				case q5:
					result = false;
					// cout << "Entered TRAP " << c << endl;
					cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
					continue;

				case q6:
					if(isdigit(c)) 
					{
						state = q6;
						cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
						break;
					}				

					else if (c == ')') 
					{
						cout << "Current state: q" << state << " Symbol popped: " << pda_stack.top() << ". Symbol pushed: <empty>" << endl;
						if (pda_stack.top() == '(' )
						{
							pda_stack.pop();
							break;
						} else {
							// cout << "\nUnbalanced parenthesis. TRANSITION TO TRAP STATE\n" << endl;
							state = q5;
							break;	
						}
						
					}

					else if (c == '+' || c == '-' || c == '*' || c == '/') 
					{
						state = q1;
						cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
						break;
					}

					// Reached the end of string. Make sure stack complies
					else if (c == '$' && pda_stack.top() == '$') 
					{
						state = q4;
						cout << "Current state: q" << state << " Symbol popped: " << pda_stack.top() << ". Symbol pushed: <empty>" << endl;
						pda_stack.pop();
						break;
					} else {
						state = q5;
						// cout << "Entered TRAP STATE" << endl;
						cout << "Current state: q" << state << " Symbol popped: <empty>. Symbol pushed: <empty>" << endl;
						break;
					}

					
			} // end switch/case 

		}  // end getchar

		// Delivers final answer --> Expression accepted or rejected?
		if (result)
		{
			cout << test << " is accepted." << endl;
		} else {
			cout << test << " is rejected." << endl;
		}

	
	return 0;

	} // end PDATest

	int main(int argc, char *argv[])
	{

	// Holds "y" "n" and expression to be tested
		string input; 

		// loop until 'n' detected
		for (;;) 
		{
			cout << "Do you want to enter an expression?" << endl;
			getline(cin, input);

			if ( input == "n" ) 
			{
				cout << __FILE__ << " will terminate now." << endl;
			    break;
			}
			
			if ( input == "y" ) 
			{
				cout << "Please enter a string" << endl;
				getline(cin, input);
				cout << "you typed: " << input << endl;

				// Begin expression evaluation
				PDATest(input);
			}

		}
		
		cout << "Program completed successfully." << endl;
		return 0;
	}