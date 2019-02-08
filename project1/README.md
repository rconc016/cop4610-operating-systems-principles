# Disclaimer
Please note that this program was complied and tested using gcc version 8.2.0 on Ubuntu 18.10.

# How to run the program
In order to run the program, you can use included Makefile. For ease of use, the Makefile has two different ways
to execute the program: synchronized and unsynchronized.

To run the program without thread synchronization, type "make run_unsync" and if you want to use the synchronized verison
type "make run_sync".

If you want to change the number of threads to execute, simply edit the THREAD_COUNT inside the Makefile.

# Clean
Running the program using the Makefile will create an output directory. You can remove it by typing the "make clean" command.