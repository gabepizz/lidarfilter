#include "TemporalFilter.hpp"
/******** TemporalFilter Functions *********/


/** TemporalFilter Constructor:
 *    Creates new object, with recents and sorted saved with given N,D values.
 **/
TemporalFilter::TemporalFilter(int Dx, int Nx)
{
  D = (Dx+1);
  N = Nx;
  recents.resize(N, std::vector<float>(D, 0));
  sorted.resize(N, std::vector<int>(D, 0));
  d = 0;
  last = 0;
}


/** TemporalFilter - update(vector<float> X)
 *    Returns a float array stored on heap which contains median of last D scans
 *    and calling scan for each value 1->N.
 *    Uses helpers addScan and getMedian.
 **/
float* TemporalFilter::update(std::vector<float> X)
{
  float * Y = new float[N];

  addScan(X);

  for(int i = 0; i < N ; i++) {
    Y[i] = getMedian(i);
  }
  return Y;
}


/** TemporalFilter - addScan(vector<float> x)
 *    Takes in an array and sorts it, replacing any old values as need be
 *    depending on the value of D.
 * 
 **/
void TemporalFilter::addScan(std::vector<float> X)
{
  int replace =-1;
  
  if(d < D) { // When Haven't gone 'D' iterations
    replace = d;
    d++;
  }
  else {      // When cycling old and new values
    replace = last;
    last = (last+1)%D;
    
    // Find and remove the oldest value from sorted list
    for(int i = 0 ; i < N ; i++)
    {
      bool pull = false;
      for(int j = 0 ; j < d ; j++)
      {
        if(pull == true) {
          sorted[i][j-1] = sorted[i][j];
        }
        else {
          if(sorted[i][j] == replace) {
            pull = true;
          }
        }
      }
    }
  }

  // add new entry to recents and sorted
  for(int i = 0; i < N ; i++) {
    recents[i][replace] = X[i];

    // Add new value to the sorted list
    bool push = false;
    int next = -1;
    for(int j = 0; j < d-1 ; j++) {
      if(push == true) {
        int temp = sorted[i][j];
        sorted[i][j] = next;
        next = temp;
      }
      else {
        if(recents[i][replace] < recents[i][sorted[i][j]]) {
          push = true;
          next = sorted[i][j];
          sorted[i][j] = replace;
        }
      }
    }
    if(push==false)
      next = replace;
    sorted[i][d-1] = next;
  }
}


/** TemporalFilter = getMedian(int index) 
 *    Returns the median from the already sorted pointer array 'sorted'
 *    and gets values to return from recents.
**/
float TemporalFilter::getMedian(int index)
{
  if( (d%2)==0 ) {
    int in1 = sorted[index][((d/2)-1)];
    int in2 = sorted[index][(d/2)];
    return ((recents[index][in1]+recents[index][in2])/2);
  }
  else {
    int in = sorted[index][(d/2)];
    return (recents[index][in]);
  }
}

