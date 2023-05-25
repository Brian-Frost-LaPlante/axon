# axon
Effects of Axonal Swelling on Networks of Spiking Neurons

Research by Brian L. Frost, and Stan Mintchev. Code by Brian L. Frost.

The C++ code is what was originally used to produce the results in the main text. The Julia version is far more readable and should be used if there is interest in modifying the program. It contains a neuron struct definition, a function that updates it according to the integrate and fire rule, a function that applies DAPA and some functions for simulation. The main one, netSim, uses DAPA according to the damage paradigm recorded in the damData file. 


