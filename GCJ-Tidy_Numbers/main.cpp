/******************************************************************************
*  Antonio Santos
*  5/12/17
*  Google Code Jam - 2017 Qulification Round B. Tidy Numbers. A tidy number as
*  described in the problem, is a number that if you were to read from left to
*  right, would be in ascending order. This program takes in numbers, and calc
*  the last tidy number under each number.
*
*  Difficulty: this program was not so difficult to start off; however once I got
*  to the part for conversions (which is what made this program super hard IMO),
*  it took me a while to figure out how to do the proper conversions. Once I had
*  the conversions down, the next difficult task, which wasnt all that difficult,
*  was figuring out how to opimize the tidy_up algorithm so that I am not decrementing
*  a large number O(N^2) times to figure out what the last tidy number was. To solve
*  this part of the program, all it took was a few minutes with a whiteboard and
*  some basic logic thinking.
*
*  What I learned: how to convert an int to a string was what I took away most
*  from this project.
******************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

bool is_tidy(string); //conditional to see if the number is tidy
string tidy_up(string); //tidy's the number

int main(){
  int test_cases;
  string last_num_counted;
  bool cond;

  cin >> test_cases; //first line of input is the amount of test cases
  for(int i = 0; i < test_cases; i++){
    cond = false;
    cin >> last_num_counted; //now we start reading in the test cases
    while(!cond){ //stops when tidy number is found for this Case
      cond = is_tidy(last_num_counted); //checks tidyness
      if(!cond) //not tidy? no problem...
        last_num_counted = tidy_up(last_num_counted); //this function will
                                                        //tidy it up.
    }
    cout << "Case #" << i + 1 << ": " << last_num_counted << endl; //output result
    last_num_counted.erase(last_num_counted.begin(), last_num_counted.end());
  }
  return 0;
}

/*****************************************************************************
*  function: is_tidy(string)
*  checks to see if the string/ case is tidy. returns a boolean yes or no.
******************************************************************************/
bool is_tidy(string arg_str){
  bool is_tidy = true;
  for(int x = 0; x < arg_str.size() - 1; x++) //O(N)
    if((x + 1 != arg_str.size()) && (arg_str[x] > arg_str[x + 1]))
      is_tidy = false;
  return is_tidy;
}


/*****************************************************************************
*  function: tidy_up(string)
*  tidy's up the string by going to the last number before the number given
*  where the number is ascending left to right. To do this efficiently, you must
*  notice some rules about this problem. first rule I noticed was that if the
*  first number in string is a 1, and the following number is a 0, then the result
*  will be all 9's of size - 1. The second rule I noticed was that if i were to
*  go left to right through the string of numbers, and the left number was smaller
*  than the right number, than the result would be to make the right number a 9,
*  and the left number itself - 1 ONLY if that is the first change in the sequence.
*  if that is the second number in the sequence, then both the left and right
*  numbers would be 9.
******************************************************************************/
string tidy_up(string arg_str){
  bool b;

  if((arg_str[0] == '1') && (arg_str[1] == '0')){ //first case: first number is
                                                  //1 and second is 0.
    for(int i = 1; i < arg_str.size(); i++){ //then all numbers are 9
      arg_str[i] = '9';
    }
    arg_str.erase(arg_str.begin()); //and we erase one element from the string
  }

  stringstream s;
  int x = arg_str.size() - 1;
  char temp;
  int l, r;
  b = false;

  for(int i = 0; i < arg_str.size() - 1; i++){ //second case: go through the
                                               //sequence and perform calculations
    if(arg_str[i] > arg_str[i+1]){ //calculation needed if true

      //following converts char to int
      temp = arg_str.at(i); //first, I take a char from string and put it in holder
      l = atoi(&temp); //then i convert it using preset C++ function, atoi

      if(b){ //if we did a calculation already on this sequence, then all numbers
            //will be 9 until the end of string
        l = 9;
      }
      else{ //else this is our first calculation and we just want to decrement
        l--;
      }

      //following is my method of converting a string to an int... which was
      //surprisingly hard to figure out.
      s.clear(); //first, I cleared the stringstream variable
      s.str(""); //then I did this.. whatever it does
      s << l; //and now I read in my first char into the stringstream
      arg_str[i] = *(s.str().c_str()); //and now i convert the string into a char

      //and now I repeat the series of converstions for the right char.
      temp = arg_str.at(i+1);
      r = atoi(&temp);
      r = 9;
      s.clear();
      s.str("");
      s << r;
      arg_str[i + 1] = *(s.str().c_str());
      b = true;
    }
  }
  return arg_str; //once we kick out of loop, that means we went through string,
                  //(which is O(N) time) and now the string is tidy.
}
