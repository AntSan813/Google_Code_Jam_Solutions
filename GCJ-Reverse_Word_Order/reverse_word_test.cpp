/*******************************************
*	Author: Antonio Santos
*	Input: This code takes a number of cases (x) and lets the user input x lines of text. 
*	Output: the output is all of those cases in reverse order.
*	Last date of update: 12/23/16
*	Notes: this code was enhanced to handle big data. bug in this code is noted as a counter
*******************************************/
#include <iostream>
#include <fstream>

using namespace std;


//start of main
int main(){

	//following are neccessary to read in test data from a file
	ifstream input_file;
	input_file.open("example_test_data.txt");	

	//following are the arrays used	
	char* reversed_array = new char[1000]; //reversed array
	char array[1000]; 			//input array
	char* word_holder = new char[256];	//word holder array
	char* master_array = new char[100000];  //array that holds all text in the end

	//following are counters used for the arrays
	int RA_bug = 0; 			//reversed array bug
	int A_bug = 0;				//input array bug
	int WH_bug = 0;				//word holder bug
	int MA_bug = 0;				//master array bug
	int read_counter = 0;

	//following are other neccessary counters
	int iterations, case_num = 1;		//neccessary counters
	int fix = 0;				


	//first user input - tells us how many cases we will have
	cout << "How many inputs will you be giving? " << endl;
	input_file >> iterations;
	cout << iterations << endl;


	//following loop asks user for input x amount of times.
	//everytime this loop is ran, the master array grabs the reverse order of the case.
	//Not only that, but all other arrays will be cleared after each iteration of the loop.
	//
	for(int i = 0; i < iterations; i++){
		
		read_counter = 0; 

		//second user input - tells us the array of characters we want to reverse in this case.
		cout << endl << "Enter some characters: " << endl;
		array[read_counter] = input_file.get(); //seed in first char in the file
		//make sure that the first seed is not a new line
		if(array[read_counter] == '\n')
			array[read_counter] = input_file.get();
	
		//while we dont hit a new line, keep feeding in data into the array. 
		//when we hit a new line, we know that we have reached the end of out first input.
		while(array[read_counter] != '\n'){
			cout << array[read_counter];
			read_counter++;
			array[read_counter] = input_file.get();
		}
	
		//to split the master array into sections (cases), i decided to use the '*' character to
		//notify us that we have reached the end of a case. 
		//please note that this is error prone- what if the users input in this case contains a '*'?
		//With that being said, there is alternatives to this method that will be more efficient
		master_array[MA_bug] = '*';
		MA_bug++;

		//following is an algorithm used to reverse the users input
		while(array[A_bug] != '\0'){


			//if there is a space in the input, in other words, if there is more than one word in the input
                	if(array[A_bug] == ' '){

                        	while(WH_bug + 1 != 0){


					//assuming that the input will not start with a space,
					//we can logically assume that this while loop will only initiate if and only 
					//if an array of characters has been instanciated into word holder 
                                	reversed_array[RA_bug] = word_holder[WH_bug]; 

	                                word_holder[WH_bug] = '\0'; //everytime a char from word holder array goes into reverse
								    //array, we want to delete that spot - or move the appended
								    //"end of sequence" character to the spot we just removed.

        	                        WH_bug--;
					RA_bug++;
                	        }               

				//after the while loop kicks out, that means that there was a word added into the reverse
				//array variable. this if statement only initiates if the user puts a space, which can lead
				//us to assume that the user inputed more than one word (or they just accidentally pressed space).
				//No matter the case, we still have to add that space to the reverse array since the user did put one.
                        	reversed_array[RA_bug] = ' ';


	                        WH_bug = 0; //reset the word holder counter
				RA_bug++; 
        	        }                                       


			//else there is no space in the input (yet). 
                	else{
                        	word_holder[WH_bug] = array[A_bug]; //add the char from the main array to the word holder array
			     	WH_bug++;    
        	        }

			array[A_bug] = '\0';	
                	A_bug++;  //move up the main array

       		}

		
		//Now, once we get out of the while loop, we know that if there were more than one word in the inpput, then
		//at least one of the words is in the reversed array. With this method, the last word did not make it in, so
		//now we must check if there is a word, and if there is then we must put it in the reversed array and essentially
		// delete the word holder array
	        if(word_holder[0] != '\0'){


			//using the same method above move the items from one array to the other.
        	        while(WH_bug + 1 != 0){
                	        reversed_array[RA_bug] = word_holder[WH_bug];
                        	word_holder[WH_bug] = '\0';
	                        WH_bug--;
				RA_bug++;
        	        }
                	WH_bug = 0;
	        }

		
		RA_bug = RA_bug - 1; //to make sure the computer reads whithin the limits of the reverse array, we decrement it.
	
		//Now for the magic - we move what is in the reverse array into the master array, and then delete the reverse array.
		while(fix != RA_bug ){
			master_array[MA_bug] = reversed_array[RA_bug - fix];
			reversed_array[RA_bug - fix] = '\0';
			MA_bug++;
			fix++;
		}

		//now we must set the integer variables used as counters to zero so that we can start fresh for our next case of inputs
		RA_bug = 0;
		A_bug = 0;
		fix = 0;
	
		//because we are putting everything into one massive array, we cannot set the counter for that array to zero
		MA_bug++;


	} //end of while




//test to make sure everything is reversing correctly 
/*	
	cout << MA_bug << endl;
	for(int i = 0; i < MA_bug; i++){
		cout << master_array[i];
		
	}
*/


	cout << endl; //for readability


	//output time - the following outputs the master array
	for(int x = 0; x < MA_bug; x++){

		//remember the character we intentionally put into the master array to tell us when weve reached the end of a case?
		//that comes into play here. everytime we reach that character, its going to tell the computer we have reached the start
		// of a new case.
		//if we reached that special character, cout this statement
		if(master_array[x] == '*'){
			cout << endl << "Case #" << case_num << ": ";
			case_num++;
		}


		//else keep outputting the characters in the master array 
		else{
	             //since we also let the new line char inside the array, we must account for it and ignore it when it comes up
        	        if(master_array[x] == '\n')
                	        x++;
			else
				cout << master_array[x];
		}
	}


	//delete the allocated memory so we dont have dangling pointers and what not
	delete[] word_holder;
	delete[] reversed_array;
	delete[] master_array;

	cout << endl; //more readability

	return 0;
}
