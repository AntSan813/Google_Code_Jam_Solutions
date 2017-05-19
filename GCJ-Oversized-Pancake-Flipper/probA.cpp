/******************************************************************************
*  Antonio Santos
*  5/8/2017
*  2017 Google Code Jam Qualification Round
*  Problem A - Oversized Pancake Flipper
******************************************************************************/
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void flip(vector<char>&, int,int); //flips a certain number of pancakes
bool all_sunny(vector<char>, int); //checks to see if all chars in the vector
                                   //passed are '+'
void display(vector<char>, int); //outputs whats contained in the vector.
                                 //This was used for debug and testing
int main(){
  //variables used
  ifstream input;
  int max, num_flips, flipper_size;
  char temp;
  vector<char> cakes;
  string sz;
  bool impossible = false, stop = false;

  input.open("large_input_test.in"); //open the file containing the test strings
  if(!input.is_open()){ //file doesnt open flag
    cout << "ERROR: Unable to open file." << endl;
    return 0;
  }

  //what is given is that the first line of the file gives us the number of
  //cases we would like to test.
  input >> sz; //get first line
  max = atoi(sz.c_str()); //convert it to int.

  for(int z = 0; z < max; z++){
    //make sure our flags are reset for each Case
    impossible = false;
    stop = false;
    num_flips = 0;

    temp = input.get(); //prime read
    while(!input.eof() && temp != ' '){ //now read rest
      cakes.push_back(temp);
      temp = input.get();
    }
    //once we hit a space, the rest of the line contains the flipper size.
    //So now, we get the rest of the line
    input >> sz; //read in until null terminator
    flipper_size = atoi(sz.c_str()); //convert to int

    if(all_sunny(cakes, cakes.size())){ //if the input is all '+'
      impossible = false;
      num_flips = 0;
    }
    else{ //else, we have pancakes on their back
      for(int i = 0; ((i < cakes.size()) && (stop != true)); i++){
        if(cakes[i] == '-'){ //if we hit a char that is '-',
          //we want to check if we can flip it from that point to the flipper
          //size - 1.
          if((i + flipper_size - 1) < cakes.size()){
            flip(cakes, i, i + flipper_size);
            num_flips++;
          }
          //if we cannot flips it, then this case is impossible.
          else{
            impossible = true;
            stop = true;
          }
        }
        //else if the char we're at is '+' and the position we're at + the
        //flipper size - 1 is greater than the rest of the array of pancakes
        else if(i + flipper_size - 1 > cakes.size()){
          stop = true;
          if(!all_sunny(cakes, cakes.size())){ //if the rest of pancakes are
            //not all sunny, then this Case is impossible. else it isnt and the
            //num_flips var contains what we want to output for this case
            impossible = true;
          }
        }
      }
    }
    if(impossible) //if it is impossible, display the following
      cout << "Case #" << z + 1 << ": IMPOSSIBLE";
    else //else display the following
      cout << "Case #" << z + 1 << ": " << num_flips;
    cakes.clear(); //clear whatever is in the array of chars
    cout << endl;
  } //end of for loop
  return 0;
}

/******************************************************************************
*  function: display(vector<char>, int)
*  outputs what is inside the vector to the screen
******************************************************************************/
void display(vector<char> x, int sz){
  for(int i = 0; i < sz; i++){
    cout << x[i];
  }
  cout << endl;
}

/******************************************************************************
*  function: flip(vector<char>&, int, int)
*  flips the pancakes inside the vector starting at position l to position r
******************************************************************************/
void flip(vector<char> &x, int l, int r){
  for(int i = l; i < r; i++){
    if(x[i] == '-')
      x[i] = '+';
    else
      x[i] = '-';
  }
}

/******************************************************************************
*  function: all_sunny(vector<char>, int)
*  boolean function that checks if all elements in the vector are sunny side up
******************************************************************************/
bool all_sunny(vector<char> x, int size){
  for(int i = 0; i < size; i++){
    if(x[i] == '-')
      return false;
  }
  return true;
}
