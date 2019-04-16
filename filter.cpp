/**
 * Gabriel Pizzolato - filter.cpp
 * Robotic Engineer LIDAR sensor filter
 * Brain Corporation Co-Op Coding Challenge
**/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
#include "RangeFilter.hpp"
#include "TemporalFilter.hpp"

#define RANGE_MIN 0.03  // default min
#define RANGE_MAX 50.0  // default max

using namespace std;



/** This parses input from the command line to do a specific operation
 * and then parses the input file input, runs operations on that data
 * and outputs to the given output file, if not specified, output file is
 * "output.txt". Actual assigned code is in RangeFilter.* and TemporalFilter.*
 * If both range and temporal filters are assigned(what happens when no flags
 * are provided), range runs before temporal.
 */
int main(int argc, char *argv[]) {
  
  char* output;
  char* input;
  int N;
  int D;
  
  // would use boost library for cmd-line input, but this is very simple
  // (a little to precise, but it gets the job done at the moment.)
  bool range =  false;
  bool temporal = false;
  if(argc > 1) {
    if(strcmp(argv[1], "-t") == 0)
      temporal = true;
    else if(strcmp(argv[1], "-r") == 0)
      range = true;
    else {
      temporal = true;
      range = true;
    }
  }

  if(temporal && range && (argc == 5)) {
    N = atoi(argv[1]);
    D = atoi(argv[2]);
    input  = argv[3];
    output = argv[4];
  }
  else if(temporal && !range && (argc == 6)) {
    N = atoi(argv[2]);
    D = atoi(argv[3]);
    input  = argv[4];
    output = argv[5];
  }
  else if(!temporal && range && (argc == 5)) {
    N = atoi(argv[2]);
    D = 1; // not used in sole range calculation
    input  = argv[3];
    output = argv[4];
  }
  else {
    cerr << "Incorrect command line input, refer to README\n";
    return 0;
  }
  
  
  RangeFilter* RF = new RangeFilter(RANGE_MIN, RANGE_MAX);
  TemporalFilter* TF =  new TemporalFilter(D, N);
  
  // parse input file, run operations on data, output to output file
  ofstream oFile;
  oFile.open(output, std::ios_base::app);
  string line;
  ifstream iFile (input);
  
  if (iFile.is_open() && oFile.is_open())
  {
    while ( getline (iFile,line) )
    {
      // get array of strings representing the data
      vector<string> strl;
      boost::split(strl,line,boost::is_any_of(","));

      if(N != strl.size()) {
        cerr << "Each row of data must be of size N." << endl;
        return 0;
      }

      // turn string vector to float vector
      vector<float> X(N);
      for(int i = 0; i < N ; i++) {
        X[i] = strtof((strl[i]).c_str(),0);
      }
      
      // Update the X to get Y.
      float* Y = NULL;
      if(range) {
        float* y1 = (RF->update(X));
        if(temporal) {
          std::vector<float> v1(y1, y1 + sizeof y1 / sizeof y1[0]);
          Y = TF->update(v1);
          delete y1;
        }
        else
          Y = y1;
      }
      else {
        Y = TF->update(X);
      }

      // Save Y to output file
      bool first = true;
      for(int i = 0 ; i<N;i++) {
        if(first) {
          oFile << Y[i];
          first = false;
        }
        else
          oFile << "," << Y[i];
      }
      oFile << endl;
      
      delete Y;
    }
    iFile.close();
    oFile.close();
  }
  else cout << "Unable to open file\n"; 
  
  delete RF;
  delete TF;

  return 0;
} //main
