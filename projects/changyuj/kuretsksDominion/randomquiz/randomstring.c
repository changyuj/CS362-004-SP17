/* Susan Kuretski
 * CS362-400, Spring 2017
 * Quiz 2
 *
 * Introduction:
 * 		The purpose of this quiz was to create a random tester
 * 		for testme.c which would result in printing an error message.
 *
 * Pre-conditions:
 * 		- inputChar() and inputString() functions were left empty to finish.
 * 		- testme() function contained a while-loop which called inputChar()
 * 		  and inputString().
 * 		- The while-loop triggered different states (range 1-9) when a certain
 * 		  char was encountered.
 * 		- The while-loop resulted in an error message and exited the program
 * 		  when the exact string 'reset' resulted.
 *
 * Test Development:
 *   ** inputChar()
 *  	- Since these chars: '[', '(', '{', ' ', 'a', 'x', '}' ,')' ,']'
 *  	  trigger the state, I decided to use ASCII values 32 - 126. This
 *  	  range covers all the characters which would trigger a state change.
 *  	  The inputChar() function was written to produce a random ASCII char
 *  	  32 - 126, and then returns produced random char.
 *
 *   ** inputString()
 *   	- Since the exact string 'reset' triggered the error, I first decided
 *   	to:
 *   	   1. Produce a random string of 5 characters only (the length of the
 *   	      word reset).
 *   	   2. Use random ASCII characters 'a' - 'z'. No upper case letters,
 *   	      non-alphabet characters. This limits the already large pool of
 *   	      possibilities.
 *   	   3. inputString() created a random string of letters 'a' - 'z' with
 *   	      the possibility of repeating.
 *
 *  Results:
 *  	- I was not able to trigger an error within a "reasonable" amount of
 *   	  iterations since the possible combinations of lower case five letters
 *   	  is 26^5.  I reached up to 20 million iterations without triggering an error.
 *
 *   	- I decided to further limit my random pool. Since the random character
 *   	  function progressed to state 9 quickly, I realized my issue was with
 *   	  the random string. Therefore, I decided to limit my string to only the
 *   	  letters 'r', 's', 'e', and 't'. The letters are capable of repeating.
 *   	  Randomness was still in place, but I decreased the possible combinations
 *   	  significantly from 26^5 to 4^5.
 *
 *   	- By changing the randomness to the letters r, s, e, and t, I was able to
 *   	  reach an error condition at iteration between 800-1200 on average.
 *
 *  Conclusion:
 *  	- Randomness can be as great or small as you wish. The degree of randomness
 *  	  should depend upon:
 *  	     1. what is being tested
 *  	     2. why it is being tested
 *  	     3. what a typical use case may look like
 *  	     4. how critical/severe an error would impact the system
 *  	        a. Fault tolerant?
 *  	        b. Life threatening?
 *  	        c. System threatening? (i.e. shutdown, loss of resources)
 *  	     5. Identified edge cases
 *  	- Since this test case was not seemingly critical, I decided limiting the test
 *  	  pool with certain characters was appropriate.
 *
 *
 *
 *
 *
 *
 *
 *
 */
