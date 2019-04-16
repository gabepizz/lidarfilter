#include <vector>
/**
 * RangeFilter :
 * Defines a class that bounds an input to curb extraneous values.
 **/
class RangeFilter 
{
  public:
    // functions
    float* update(std::vector<float> X);
    RangeFilter(float min, float max);
  private:
    //fields
    float min_range;
    float max_range;
};