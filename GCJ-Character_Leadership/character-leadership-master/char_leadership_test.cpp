/***************************************************************************************************************************************************
	Author: Antonio Santos
	Description: This program takes the input of cases, and for each case the user inputs an array of names. the output 
	is the leader of those names. the leader is determined by whoever has the most unconsecutive alphabetical characters.
	Date: 12/24/16 
***************************************************************************************************************************************************/


#include <iostream>
#include <cctype>
#include <fstream>
using namespace std;

//start of main
int main(){

	//unneccessary variables, but these are the max limits 
	int person_max = 100;
	int name_max = 20;	
	int case_max = 100;

	//the following variables are placeholders for counters
	int test_cases;
	int num_people;
	int people_counter;
	int name_pos = 0;
	int temp_pos;
        int score = 0;
        int iterator = 0;
        int winner_counter = 0;

	//the following variable is used to determine if there is any repeat letters in the words
	bool is_new;
	
	//the following variables are used to hold the "winner" name (or in this program case, the leader of the country), the scores 
	//that each name hold, etc.	
	int name_score;
	char names[name_max];
	char winning_names[case_max][name_max];

	//the following variables are used for file input
	ifstream input_file;
	input_file.open("test_run.txt", ios::in | ios::binary);


	//takes in the amount of cases (MAX 100)
	cout << "How many test cases will there be? " << endl;
	input_file >> test_cases; //takes the file input
	cout << test_cases << endl; //outputs what the file inputed onto the screen 

	//the following for loop goes through all the cases and encapsulates a majority of the program
	for(int case_counter = 0; case_counter < test_cases; case_counter++){

		//outputs the case number, then asks user how many people are in this case (in this program, case also means country number)
		cout << "For Case #" << case_counter + 1 << ", how many people are in the country?" << endl;
		input_file >> num_people; //user enters number of people in this case
		cout << num_people << endl;

//		cin.ignore(); //causes a runtime error if this statement is not here
		winner_counter = 0; //reset the counter before they are determined
	
		//the following loop lets the user input the name of each person in the case. While the loop runs, the winner is determined 
		//as the user enters the data and the winner is changed when the user enters a name that has a higher score
		for(int person_counter = 0; person_counter < num_people ; person_counter++){
			
			cout << "Name " << person_counter + 1 << ": ";
			names[name_pos] = input_file.get(); //to get the files input of a character of values, we must first seed in the first char
	
			name_pos = 0;
			//to prevent a failure in the readin, we include the following if statement
	                 if(names[name_pos] == '\n')
                                names[name_pos] = input_file.get();
			//now that we seeded and made sure it wasnt the end of a line, we loop through the line of chars in the file until we hit the end of a line.
                        while(names[name_pos] != '\n'){
                                cout << names[name_pos];
                                name_pos++;
                                names[name_pos] = input_file.get();
                        }
			
			name_pos = 0;//reset the name position
			name_score = 0;//reset the name score
			
			//following while loop determines the score for the name the user just inputted
			while((names[name_pos] != '\0') && (names[name_pos] != '\n')){
				
				//this program only looks at character values
				if(isalpha(names[name_pos])){
								
						temp_pos = name_pos;
						is_new = true;
							
						if(names[name_pos] == ' ')
							is_new = false;

						else{
							while((temp_pos != 0) && (is_new)){
								temp_pos--;
							
								if(names[temp_pos] == names[name_pos])
									is_new = false;						
							}
						}
						if(is_new)
							name_score++;
				}
				name_pos++;	
			}

			name_pos = 0;

			//if the score of this name is greater than the current winner score
			if(name_score > winner_counter){

				winner_counter = name_score;
			
				name_pos = 0;
				//clear whatever is in the winning names array
                                while(winning_names[case_counter][name_pos] != '\0'){
                                        winning_names[case_counter][name_pos] = '\0';
					name_pos++;
                                }

				name_pos = 0;
				//put in the new name
				while((names[name_pos] != '\0') && (names[name_pos] != '\n')){
					winning_names[case_counter][name_pos] = names[name_pos];
					name_pos++;
				}
			}

		
			//else if the score of this name is equal to the winner score
			else if(name_score == winner_counter){
				//and the names array at which the characters do not equal each other. at that time, we can
				//compare the two characters
				if(names[name_pos] == winning_names[case_counter][name_pos]){
					while(names[name_pos] == winning_names[case_counter][name_pos])
						name_pos++;
				}
					

				//if the new name character is greater than the winning name character at the given positions,
				//then we want to change the new winning name
				if(names[name_pos] < winning_names[case_counter][name_pos]){

					winner_counter = name_score; //set the new score
					
					name_pos = 0;//the following loop needs the name positon to start at 0, or its initial position
					//clear whatever is in the winning names array at the given positions
		                        while(winning_names[case_counter][name_pos] != '\0'){ //while the sequence is not at the end
	                                	winning_names[case_counter][name_pos] = '\0'; //set the position to null
        	                	        name_pos++; //increment the position
                		        }
									
					name_pos = 0;//the following loop needs the name positon to start at 0, or its initial position
					//writes into the winning names array the new winning names for the given positons.
					//While the position is not null and the position is not a new line indicator,
					while((names[name_pos] != '\0') && (names[name_pos] != '\n')){ 
	                                        winning_names[case_counter][name_pos] = names[name_pos]; //transfer the name data
	  	                                name_pos++; //increment the position
                	                }						
				}
			}
		
			name_pos = 0;//the following array needs to start at its initial name position, so we set that variable to 0
			while(names[name_pos] != '\0'){
				names[name_pos] = '\0';
				name_pos++;
			}
			cout << endl;
			name_pos = 0;
		}//end of person for loop


		//when we kick out of the previous loop, that means we are done with this case and we are moving on 
		//to the next case. that means we want to reset the number of people. this statement isnt really 
		//needed because at the start of a new case it will be overwritten.
		num_people = 0;


	}//end of case for loop
	
	cout << endl; //readability

	//output the leaders	
	for(int i = 0; i < test_cases; i++){
		name_pos = 0;
		cout << endl;
		cout << "Case #" << i + 1 << ": ";
		while((winning_names[i][name_pos] != '\0') && (winning_names[i][name_pos] != '\n') && (name_pos != 20)){

			cout << winning_names[i][name_pos];
			name_pos++;			
		}	
	}
	
	input_file.close(); //as always, close the file
	cout << endl;
	return 0;
}
