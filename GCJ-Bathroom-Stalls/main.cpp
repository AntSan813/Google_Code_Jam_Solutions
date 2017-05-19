/******************************************************************************
*  Antonio Santos
*  5/13/17
*  GCJ 2017 - Qualification Round C - Bathroom Stalls
* Problem:
*  A certain bathroom has N + 2 stalls in a single row; the stalls on the left
*  and right ends are permanently occupied by the bathroom guards. The other N
*  stalls are for users.
*
*  Whenever someone enters the bathroom, they try to choose a stall that is as
*  far from other people as possible. To avoid confusion, they follow
*  deterministic rules: For each empty stall S, they compute two values LS and
*  RS, each of which is the number of empty stalls between S and the closest
*  occupied stall to the left or right, respectively. Then they consider the set
*  of stalls with the farthest closest neighbor, that is, those S for which
*  min(LS, RS) is maximal. If there is only one such stall, they choose it;
*  otherwise, they choose the one among those where max(LS, RS) is maximal. If
*  there are still multiple tied stalls, they choose the leftmost stall among those.
*
*  K people are about to enter the bathroom; each one will choose their stall
*  before the next arrives. Nobody will ever leave.
*
*  When the last person chooses their stall S, what will the values of
*  max(LS, RS) and min(LS, RS) be?
*
* Difficulty:
*  Aside from the obvious logic challenge in this problem, the most difficult part
*  in my opinion was figuring out the BEST approach. There seems to be many approaches
*  and I must have went through 5 different methods before coming up with this one.
******************************************************************************/
#include <iostream>

using namespace std;

//finds the max distance of empty stalls from a given position
int max(int*, int);

//finds the min distance of empty stalls from a given position
int min(int*, int);

int main(){
  int num_test_cases, num_stalls, num_people, hold, pos, maxima, minima;

  cin >> num_test_cases;

  for(int z = 0; z < num_test_cases; z++){
    cin >> num_stalls;
    cin >> num_people;

  //initialize an array of stalls with each stall == 0
    int bathroom[num_stalls + 2] = {0};

  //first and last stall have someone in them initially
    bathroom[0] = 1;
    bathroom [num_stalls + 1] = 1;

  //following for loop inserts each person into bathroom until we hit the last.
    for(int s = 0; s < num_people; s++){

      //reset all vars to 0
      hold = 0;
      maxima = 0;
      minima = 0;
      pos = 0;

    //following for loop figures out where to insert each person in the bathroom
      for(int i = 1; i < num_stalls + 1; i++){

        if(bathroom[i] != 1){ //if the stall is empty
          hold = min(bathroom, i);

    //find the highest minima value.
          if(hold > minima){
            minima = hold;
            maxima = max(bathroom, i);
            pos = i;
          }

    //in the case that there is multiple minimas with the same value, choose the
    //one with the highes maxima value.
          else if(hold == minima){
            if(max(bathroom, i) > maxima){
              pos = i;
              maxima = max(bathroom, i);
            }
          }
        }
      }

      //if both are 0, then that means all stalls all empty stalls have 1 to the
      //left and right of it. So then we want to stop looping as we know the maxima
      //and minima are 0.
      if((maxima == 0) && (minima == 0)){
        break;
      }

      //insert a 1 at the position selected to indicate it is not vacant
      bathroom[pos] = 1;
    }

    //ouput the solution - which is the maxima and minima of the final person
    cout << "Case #" << z + 1 << ": ";
    cout << maxima << " ";
    cout << minima << endl;
  }
  return 0;
}

//given array s, and position pos, what is the max distance from that point to
//the closest filled stall?
int max(int* s, int pos){
  bool left_check = false, right_check = false;
  int l = pos, r = pos;
  int l_max = 0, r_max = 0;

  //get distance from the left and right side of the stall at position pos
  while((!left_check) && (!right_check)){
    if(!left_check)
      l--;
    if(!right_check)
      r++;

    if(s[l] == 0)
      l_max++;
    else
      left_check = true;

    if(s[r] == 0)
      r_max++;
    else
      right_check = true;
  }

  //then return the distance of whichever side is higher
  if(r_max > l_max)
    return r_max;
  else
    return l_max ;
}

//same as max function, excepts returns the min distance from the left and right
//sides.
int min(int* s, int pos){
  bool left_check = false, right_check = false;
  int l = pos, r = pos;
  int l_max = 0, r_max = 0;

  while((!left_check) && (!right_check)){
    if(!left_check)
      l--;
    if(!right_check)
      r++;

    if(s[l] == 0)
      l_max++;
    else
      left_check = true;

    if(s[r] == 0)
      r_max++;
    else
      right_check = true;
  }

  if(l_max > r_max)
    return r_max;
  else
    return l_max;
}
