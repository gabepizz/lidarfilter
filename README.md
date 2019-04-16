README.md
Gabriel Pizzolato


The files that have most to do with the problem asked are:
	TemporalFilter.hpp, TemporalFilter.cpp, RangeFilter.hpp, RangeFilter.cpp
The file filter.cpp is parsing input, reading from input file, and writing to output file.


Using the program:
Apply range filter:
  => ./filter -r [N] [input file] [output file]

Apply Temporal Filter:
  => ./filter -t [N] [D] [input file] [output file]

Apply range filter, then temporal filter
  => ./filter [N] [D] [input file] [output file]
  
To Compile Program:
  => g++ filter.cpp TemporalFilter.hpp TemporalFilter.cpp RangeFilter.hpp RangeFilter.cpp -o filter


I left a sample file output.txt where I ran 3 different functions on the sample input
from the pdf describing the project. That output is in output.txt, input in input.txt
Ran in order -
  './filter -r 5 input.txt output.txt'
  './filter -t 5 3 input.txt output.txt'
  './filter 5 3 input.txt output.txt'
This ran the range(rows 1-5), the temporal(rows 6-10), and range+temporal(rows 11-15)
showing their respective output with the input from input.txt
