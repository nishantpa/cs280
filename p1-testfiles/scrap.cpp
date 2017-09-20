/*   int outputLen = 12;

   for (int i = 0; i < words.size(); i++)
   {
       // dashSupp is really just a char absorber that absorbs from diff strings
       string dashSupp, tempUpdater;
       int ifLess, updater;

       // String size > outputLength
       if (words[i].size() > outputLen)
       {

           // If you're IN MIDDLE OF A WORD, you gotta break with a dash and feed rest onto next line. What if you're at the start of a word???
           if ( !isblank(words[i][outputLen]) && !isblank(words[i][outputLen + 1]) )
           {
               // absorb chars from limit to end of string
               dashSupp = words[i].substr(outputLen, words[i].size() );

               // Replace chars that go over limit with "dash"
               words[i].replace(outputLen - 1, words[i].size(), "-");

               // That string is now ready. Place in queue to go to standard out
               outReady.push(words[i]);


               // Prepare to throw extra chars from prev string into next element. Needs a space @ end though
               dashSupp.push_back(' ');


               // If next element is NOT .ll directive, then can safely move extra chars to next element. Continue with text processing
               if (words[i + 1].find(".ll") != 0)
               {
                   words[i + 1].insert(0, dashSupp);

               } else // the next element in the vector IS a .ll directive!
                   //if(words[i + 1].find(".ll") == 0)
                   {
                       cout << "Entered" << endl;
                       // Grab the new chars limit
                       tempUpdater = words[i + 1].substr(4, words[i + 1].size() );
                       updater = stoi(tempUpdater);

                       // As long as 10 <= N < 120 , update output chars limit
                       if (updater >= 10 && updater < 120)
                       {
                           outputLen = updater;
                           cout << outputLen << endl;
                       }

                   }

//            // end IF MIDDLE of word
//            } else if( isblank(words[i][outputLen]) )
//             {
//                 // add whitespace as padding
////                if (words[i].find_first_of(' ', 0) )
////                 {
////                     words[i].insert(words[i].find_first_of(' '), ' ');
////                 }
            }

       } else if (words[i].size() < outputLen)
        {

        }// end if >


       if (words[i].size() < outputLen)
       {
           // How many chars shorter is the string than the limit?
           ifLess = outputLen - words[i].size();

           // grab chars from beginning of next string to needed amt of chars -1. Why -1? need space for dash
           dashSupp = words[i+1].substr(0, ifLess - 1);


       }
   }
//
 /*************************************************************************/
//    // Final part - write output ready lines to standard out
//
//    int i = 0;
//    while (!outReady.empty() )
//    {
//
//        cout << outReady.front() << endl;
//        outReady.pop();
//        i++;
//    }




Ozymandias

Percy Bysshe Shelley, 1792 - 1822

.ll 5
.ll 173
I met a traveller from an antique land
Who said: "Two vast and trunkless legs of stone
Stand in the desert . . . Near them, on the sand,
.ll 10
Half sunk, a shattered visage lies, whose frown,
And wrinkled lip, and sneer of cold command,
Tell that its sculptor well those passions read
Which yet survive, stamped on these lifeless things,
.ll 40
The hand that mocked them, and the heart that fed:
And on the pedestal these words appear:
'My name is Ozymandias, king of kings:
.ll 118
Look on my works, ye Mighty, and despair!'
Nothing beside remains. Round the decay
Of that colossal wreck, boundless and bare
The lone and level sands stretch far away."
