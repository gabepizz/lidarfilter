#include<vector>
/**
 * TemporalFilter Class:
 * Defines an object that keeps temporal data in order to create a median
 * value over a given time period D to reduce noise.
**/

class TemporalFilter
{
  public:
    // functions
    TemporalFilter(int Dx, int Nx);
    float* update(std::vector<float> X);

  private:
    // fields
    std::vector< std::vector<float> > recents;
    std::vector< std::vector<int> > sorted;
    int d, last;
    int D, N;

    // helper functions for update
    void addScan(std::vector<float> X);
    float getMedian(int index);
};
