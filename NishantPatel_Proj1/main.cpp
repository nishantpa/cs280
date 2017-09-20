//  Created by Nishant Patel on 9/23/16.
//  Copyright © 2016 Nishant Patel. All rights reserved.
//
//  To compile: g++ -std=c++0x main.cpp -o <filename>
//  Run the program with 1 arg passed: <filename> p1-test1.in. Prints to STDOUT
//  This program is a dynamic text formatter. When it detects a properly formed .ll directive, 
//   it will format text according to the character limit specified there

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <queue>

using namespace std;

int main(int argc, char *argv[]) {

    vector <string> words(0);
 
    if(argc != 2)
    {
        return 1;
    }

    ifstream file (argv[1]);
    
    // Opens file, filters extra blank lines, lines starting with . , and
    // ill formed .ll directives
    if (file)
    {   
       string line;
        
          // Make each line of text a element of vector
          // Test to filter blank lines, "." and ".ll N"
          while (!file.eof())
          {
              getline(file, line);
              if (line.size() > 0)
              {
                      if (line.front() == '.')
                      {
                          if (line[1] != 'l') {
                              continue;
                          }
                          
                          if (line.size() > 7)
                          {
                              continue;
                          } else {
                              words.push_back(line);
                          }
                          
                      } else {
                          words.push_back(line);
                      }
              }

              else if (words.back().size() > 0)
                  {
                      words.push_back(line);
                  } else {
                        continue;
                    }
              
          } // end insert into vector
        
        words.pop_back();
    }
    
    
    // Filters extra whitespace
    // Loops through all elements in vector and filters extra whitespace.
    for (int i = 0; i < words.size(); i++)
    {
        string filtSpace;
        
        // Filters whitespaces for each line.
        for (char& ch : words[i])
        {
            if (isblank(ch))
            {
                
                if ( isblank(filtSpace.back()) || filtSpace.size() == 0 )
                {
                    continue;
                } else {
                    filtSpace.push_back(ch);
                  }
                
            } else {
                filtSpace.push_back(ch);
              }
        }
        
        // Replace element with filtered version
        words[i] = filtSpace;
        
    }

   
    // Text Format ; Keep track of string length and outputLen
    // Defaults as specified in Doc
    int charlimit = 60, padSpace = 0;
    int checkN, charShort, extraChar;
    string limitUp, carryChar;
    vector <string> outReady(0);
 
    // Run through words[] and throw processed lines into outReady
    for (int i = 0; i < words.size(); i++)
    {
        int j = 1;
        
        // Update line's char limit if directive found
        if (words[i].find(".ll") == 0)
        {
            limitUp = words[i].substr(4, words[i].size() );
            checkN = stoi(limitUp);
            
            if (checkN >= 10 && checkN < 120)
            {
                charlimit = checkN;
                
                if (outReady.size() == 0)
                {
                    continue;
                }
                else
                outReady.push_back("\n");
            }
            continue;
        } // done checking and processing directive
        
        // If it's a blank line, add that to outReady
        if (words[i].size() == 0)
        {
            outReady.push_back("\n");
            continue;
        }
       
        // if element size is < charLimit AND that element is the last line of paragraph, then no processing needed. Add to outReady
        if (words[i].size() < charlimit && words[i + j].size() == 0)
        {
            outReady.push_back(words[i]);
            outReady.push_back("\n");
            continue;
        }
        
        // if elem is < charLimit AND there is NOT a blank line following it
        if (words[i].size() < charlimit && words[i + j].size() > 0)
        {
            words[i].push_back(' ');
            charShort = charlimit - words[i].size();
            
            // If next line is directive, look at line after it
            if (words[i + j].find(".ll") == 0)
            {
                ++j;
            }
            
            // IF the [charShort -1] char is NOT BLANK && the char before [charShort -1] IS BLANK, then we are at the beginning of a word
            if (!isblank(words[i + j][charShort - 1]) && isblank(words[i + j][charShort - 2]) )
            {
                carryChar = words[i + j].substr(0, charShort - 2);
                words[i].append(carryChar);
                
                // Pad line with whitespace until it reaches charLimit.
                    while (words[i].size() != charlimit)
                    {
                        padSpace = words[i].find_first_of(" ");
                        words[i].insert(padSpace, " ");
                        padSpace = words[i].find_last_of(" ");
                        words[i].insert(padSpace, " ");
                    }
                
                outReady.push_back(words[i]);
                outReady.push_back("\n");
                words[i + j].erase(0, carryChar.size() +1);
                
            }  // end IF @ beginning of word
            
            else
                 
            // IF in middle of word
            if (!isblank(words[i + j][charShort - 1]) && !isblank(words[i + j][charShort - 2]) )
            {
                carryChar = words[i + j].substr(0, charShort - 1);
                
                if (carryChar.size() == 0)
                {
                    words[i].pop_back();
                    while (words[i].size() != charlimit)
                    {
                        padSpace = words[i].find_first_of(" ");
                        words[i].insert(padSpace, " ");
                    }
                    
                    outReady.push_back(words[i]);
                    outReady.push_back("\n");
                    
                    continue;
                }

                carryChar.push_back('-');
                words[i].append(carryChar);
                
                outReady.push_back(words[i]);
                outReady.push_back("\n");
                
                words[i + j].erase(0, carryChar.size() - 1);
            } // end if in MIDDLE of word
            
            else
                
            // handle if BLANK @charLimit
            if (isblank(words[i + j][charShort - 1]) )
            {
                carryChar = words[i + j].substr(0, charShort - 1);
                words[i].append(carryChar);
                
                words[i + j].erase(0, charShort);
                
                outReady.push_back(words[i]);
                outReady.push_back("\n");
                continue;
            }
        } // end words[i] < charLimit AND the next line is NOT a blank line
        
        else
            
        // if elem > charLimit
        if (words[i].size() > charlimit)
        {
            extraChar = words[i].size() - charlimit;
            
            // test if MIDDLE of word @ limit
            if (!isblank(words[i][charlimit - 1]) && !isblank(words[i][charlimit - 2]) )
            {
                carryChar = words[i].substr(charlimit - 1, words[i].size());
                
                // to prevent adding words onto line with directive
                if (words[i + j].find(".ll") == 0)
                {
                    ++j;
                }
                
                words[i + j].insert(0, carryChar + " ");
                words[i].erase(charlimit - 1, words[i].size() );
                words[i].push_back('-');
                
                outReady.push_back(words[i]);
                outReady.push_back("\n");
                
                continue;
            } // end if MIDDLE of word @ limit
         
            else
            
            // test if beginning of word @ limit
            if (!isblank(words[i][charlimit - 1]) && isblank(words[i][charlimit - 2]) )
            {
                carryChar = words[i].substr(charlimit -1, words[i].size() );
                
                if (words[i + j].find(".ll") == 0)
                {
                    ++j;
                }
                
                words[i + j].insert(0, carryChar + " ");
                words[i].erase(charlimit - 2, words[i].size() );
                
                // Need to pad with whitespace before throwing into outReady
                while (words[i].size() != charlimit)
                {
                    padSpace = words[i].find_first_of(" ");
                    words[i].insert(padSpace, " ");
                }
                
                outReady.push_back(words[i]);
                outReady.push_back("\n");
                
                continue;
            } // end if ELEM > charLimit && @ beginning of word
            
            else
            
            // test if @ charLimit you hit whitespace
            if (isblank( (words[i][charlimit - 1]) ))
            {
                carryChar = words[i].substr(charlimit, words[i].size());
                
                if (words[i + j].find(".ll") == 0)
                {
                    ++j;
                }
                
                words[i + j].insert(0, carryChar + " ");
                
                words[i].erase(charlimit - 1, words[i].size());
                
                while (words[i].size() != charlimit)
                {
                    padSpace = words[i].find_first_of(" ");
                    words[i].insert(padSpace, " ");
                }
                
                outReady.push_back(words[i]);
                outReady.push_back("\n");
                
            } // end if ELEM > charLimit && @charLimit a blank
            
        } // end if ELEM > charLimit

    } // end loop through words[] vector @ index i
    
  //  outReady.pop_back();
     for(string i : outReady){
         cout << i;
     }
    
    return 0;
}
