1.) Type make in the command terminal to compile the program

2.) After compiling the syntax for running the program is:-
     ./virtualmem -h (any digit) -f (any numeric no) -r (page rep algo) -i (input file)
      where -h prints with the statistics of all algorithms
      -f is the no of frames
      -r is the page replacement algo
      -i is the input file name 

3.) For sample, two input files have been attached namely test.txt and test1.txt

4.) If -i option is not included then, there is the option of input i in terminal.The message will be displayed      that says "Enter Page sequence". The page sequence can be terminated by entering "Enter".

5.) Some examples are :-
    ./virtualmem -h 1 -f 3 -i test.txt

    ./virtualmem -f 3 -r LFU -i test.txt

    ./virtualmem -f 5 -r LRU-STACK -i test1.txt


