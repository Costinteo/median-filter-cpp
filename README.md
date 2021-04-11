# median-filter-cpp
A simple C++ program to apply median filters to photos. Median filter is usually used to denoise pictures. It uses merge sort or bubble sort, depending on what the user wishes to sort with.

It requires an input file of pgm format.

General form of standard input:

sorting_algorithm_chosen size_of_median_window inputfilename.pgm outputfilename.pgm

Example standard stream input:

merge 3 test_in.pgm test_out.pgm

bubble 5 test_in.pgm test_out.pgm


Specifications:
You can only choose "merge" or "bubble" for your sorting algorithm.
Window size should be an odd positive number. The bigger it is, the blurrier the image becomes.


Before:

![BEFORE:](https://user-images.githubusercontent.com/39965799/114322722-69bf2b80-9b2a-11eb-83f7-d7fa1a797611.png)

After (window size 3):

![AFTER (window size 3):](https://user-images.githubusercontent.com/39965799/114322728-73489380-9b2a-11eb-919c-64973d670f14.png)
