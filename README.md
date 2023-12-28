# Krylov-C-Maximization

This is the code that I used to generate the graphs with maximum $\bar{\mathcal{C}}$-complexity in the paper *Krylov Spread Complexity of Quantum-Walks* . Compile using the command
`g++ -std=c++17 -lm -lgsl -lgslcblas -Ofast -o Krylov optimization.cpp` and run the program with `Krylov seed loadflag`, where seed is an integer that is used to seed the random number generator and loadflag is 0 or 1. Use 0 on the first run. If 1 is used, the best matrix found so far will be loaded from file. 
The Hilbert space dimension is fixed by setting `const int dim = 12;` in optimization.cpp. The number nn of randomly chosen neighbors included in the optimization is set by changing `const int nn = 11;`.

Please cite the paper if you are using the code.
