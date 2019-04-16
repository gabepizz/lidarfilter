#include <vector>
#include "RangeFilter.hpp"
/************** RangeFilter Functions ********************/


/** RangeFilter - Constructor
 *    Saves min and max to object for later use.
 **/
RangeFilter::RangeFilter(float min, float max)
{
  min_range = min;
  max_range = max;
}


/** RangeFilter - update(vector<float>)
 *    Uses min and max to curb values, returns updated array.
 *    Returns array Y stored on heap.
 */
float* RangeFilter::update(std::vector<float> X) 
{
  int N = X.size();
  float* Y = new float[N];

  for(int i = 0; i < N ; i++) {
    if(X[i] < min_range)
      Y[i] = min_range;
    else if(X[i] > max_range)
      Y[i] = max_range;
    else
      Y[i] = X[i];
  }
  return Y;
}