/*
	@Nishant Patel; Feb 11 2017; cs341 Proj1
	  Finished all parts. Passes all tests. 
	  Descriptive comments added. 
	  Submission ready

	@Nishant Patel; Feb 10 2017; cs341 Proj1
	  Revisiting on 10 Feb 2017. What's left:
	  Implement DFA rules entirely
	  Test each case
		
		NOTE: state + 1 b/c DFA diagram in notebook starts
		at q1. Otherwise, I'm all for simplicity and removing
		the need for "state + 1"

		NOTE: anything NOT in the language goes to TRAP
 ____________________________________________________________
	@Nishant Patel; Feb 1 2017; cs341 Proj1
	Implement a DFA for the language specified
	  File created. Handled user input
*/

#include <iostream>
#include <string>
using namespace std;

int DFATest(string test) 
{
	enum transState {q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15} state = q1;

	// PASS or FAIL string
	bool result;
	
	// getchar from string and test against DFA
	for (char& c : test) 
	{
		switch (state) 
		{
			case q1:
				cout << "BEGIN TEST. State: q1" << endl;
				if (c == 'w') 
				{
					state = q2;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				} else {
					state = q13;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				}
				
			case q2:
				if (c == 'w') 
				{
					state = q3;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				} else {
					state = q13;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				}

			case q3:
				if (c == 'w') 
				{
					state = q4;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				} else {
					state = q15;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				}

			case q4:
				if (c == '.') 
				{
					state = q5;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				} else {
					state = q15;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				}

			case q5:
				if (c == 'c') 
				{
					state = q6;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				} else {
					state = q13;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				}

			case q6:
				if (c == 'o') 
				{
					state = q7;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				} else if (c == 'a') 
				 {
					state = q9;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = true;
					break;
				 } else {
				 	state = q13;
				 	cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				 }

			case q7:
				if (c == 'm') 
				{
					state = q8;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = true;
					break;
				} else if (c == '.') 
				 {
					state = q10;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				 } else {
				 	state = q13;
				 	cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				 }

			case q8:
				if (c == '.') 
				{
					state = q5;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = true;
					break;
				} else {
					state = q13;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = true;
					break;
				}

			case q9:
			{
				state = q13;
				cout << c << ", STATE: q" << state + 1 << endl;
				result = true;
				break;
			}
				
			case q10:
				if (c == 'c') 
				{
					state = q11;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				}

			case q11:
				if (c == 'a') 
				{
					state = q12;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = true;
					break;
				}

			// No transition out of q12
			case q12:
			{
				cout << c << ", STATE: q" << state + 1 << endl;
				result = true;
				break;
			}

			case q13:
				if (c == '.') 
				{
					state = q14;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				} else {
					state = q13;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				}

			case q14:
				if (c == 'c') 
				{
					state = q6;
					cout << c << ", STATE: q" << state + 1 << endl;
					result = false;
					break;
				}


			// Serves as trap and hold state
			case q15:
				cout << c << ", STATE: q" << state + 1 << endl;
				// cout << "Entered TRAP " << c << endl;
				result = false;
				continue;

			default:
			{
				cout << c << ", STATE: q" << state + 1 << endl;
				// cout << "Entered TRAP " << c << endl;
				result = false;
				continue;
			}
				
		} // end switch

	} // end getchar

	// Delivers final answer --> String accepted or rejected?
	if (result)
	{
		cout << test << " is accepted." << endl;
	} else {
		cout << test << " is rejected." << endl;
	}
	return 0;	
}

int main (int argc, char *argv[]) 
{
	// Holds "y" "n" and string to be tested
	string input; 

	// loop until 'n' detected
	for (;;) 
	{
		cout << "Do you want to enter a string?" << endl;
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

			DFATest(input);
		}

	}
	cout << "Program completed successfully." << endl;
	return 0;
}