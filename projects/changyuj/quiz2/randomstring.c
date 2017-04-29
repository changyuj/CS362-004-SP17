/*
To start implement the random tester, I took a look at the skeletal code that was available
in the assignment. I saw the inputChar and the inputString function both will have to return
a value and be assigned to the char c and char s. 

looking at how the testme function runs through the if statements, I saw that there are only 9
possible char it will be generating. Therefore, I can create a array of char that holds just
these 9 values and then have it randomly choose one of the char in the array to return in the inputChar().
Since the testme will run with a while loop and steps through the c char while assigning the state in 
an specific order then this should work for inputChar.

Second, I noticed the char s would require inputString to return the whole array of char to be assigned to 
s, so simply setting the char array in inputString to the string 'reset' with '\0' wouldn't satisfy the 
random test. So I would imagie that a array providing a list of possible chars and have them randomly 
be assigned into a char string and return that string. This way, only if the string have the 
correct sequence of 'reset' will allow the error message to be printed since the state is already 
set to 9 as the inputChar have already went through all the steps for that to happen.

*/