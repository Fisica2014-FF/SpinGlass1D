# SpinGlass1D

Exercise for the course Computational Method for Physics. A Gaussian one-dimensional spin glass simulation using [Metropolis-Hastings' algorithm](https://en.wikipedia.org/wiki/Metropolis%E2%80%93Hastings_algorithm) (a Markov chain Monte Carlo method), with ASCII representation of the spins. Transferred from my prevoius Github account [Fisica2014-FF](https://github.com/Fisica2014-FF).


# Instructions
## Compilation
```
cd project_folder/
```
Now go into one of the alternative versions, like Optimized_Super/, and `make` it
```
cd Optimized_Super/
make
```

## Running
Now run the file  `./Ising`. It has four arguments:
* int L: Atoms in the lattice, 
* float T: Temperature
* int seed: seed Random Nuumber Generator
* int Nsweep: Monte carlo sweeps (time to run)

for example
```
./Ising 150 10.0 43 15
```
# Example output
```
●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●○●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●
●○○●●●●●○○●●●●○●○●●○●●○●●○●●○○○●●●○○●○●●○○●○●○●●●●●●●○●○●○●●○●●●○○●○●●●●○●●●○●●●
○●●●○○●○●●●●●○●●○●●●●○●●●○○●●●●●○●●●●○●●○○●○●●●○●●○○●○○●○○○○●○●●●○●○○○●○●●●●○●●●
●●○●●○●○●●●○●●●●○○○●●●●●○○○●●○○○○●○○●○●○○○●○○●○●○●●●○○●●○○○○○○○●○○○○○○○○○○●●○●●●
●●○●●○○○●●○○●○●●○●○●○○○●○○○○●○●○○●○●●●○○○●●●●●●●○●●●●○○○●○●●●○●○●●○●●●○○○●●●○○●○
○●●●●○●●●●●○●●●●○○●●●○○●○○○●●○●○○○●●○●●○●○●●●●○○○●○○○○○●●○●○○○●○○●●○●○●○●○○●○○●●
○●●●●●○●●○○●○○○○○●○●●○○○○●○○○○●●○○●●●○●○●●●○○○●○○●○○○○○●○○●●●●●●○○○○○●●○●○○●●○●○
●○○●●○●○○●●●○○○○○○●●●●○○○●○○○●●●●●○●○○●●○●●○○○○○○●○○○○○●○●●●●○●●●●○○○●●○○○○●●●●○
●○○●●○●○○●○●○○○○○●○●○●●●○○●●○●●○●●●●○●●○●○●●●○○○○○●○○○●○○○●○○○●●●○○○●●○○○○○○●○●○
○●○●●○○○○○○●●●●○●●○○●○●○●○○●○●●○○●○●○●○○●○●●○●○●○○●●○○●●○○○○○●○○●○○○●●○●●●●○○○○●
○○●●●○○○○●○●●●●○●●●○●●●○●○●●●○●●●○○●○●●●●○●●○●○○○○●○○○○●○○○●○○●○○○○○●●●●○●○○●○●○
●○●○○●●○○○●●●○○○●○○○●○●●●●●○●○●●●●○○●●●○○●●●●○●○○○○○●●●○○○○●●●●●●○●●○●●○○○○○●○●○
●○●○○●●○○○●●●●●○○○●●○●○●●●●○●○●○●○●●●○●○●●○○●○○○●○○●●○○●○○○○●○●○○○●○●●●○○○○○○●○○
○○●○○●○●○○○●○●●○○○●●●○●○○○○●○○●●○●○●○○●●●●●●○●○●●●○○○●○○●●●○●●○●●●●○○●○●○○●●○●●○
○○●●○●●●○○○●○●●●●●●●●○○●○○○○●○●○○●●●○●○●○●●○●●●●○○○●●●○●○●●●●●●●○○●●○●○○●○●●●●●●
▴▲▿▽▲▿▴▲▽▿▴▿▴▲▿▽▿▲▲▽▽▿▲▽▲▴▴▽▴▿▿▴▽▲▿▲▽▿▲▿▿▲▴▿▲▿▴▲▲▽▽▲▿▲▽▽▽▽▴▲▽▲▿▽▽▿▴▴▽▲▲▲▲▿▲▲▿▿▴▲

Media temporale E: -0.0294869
Media temporale M: -0.0166667

```

The last line represent the spin glass structure: a white upper triangle is a ferromagnetic interaction, a black down one is a antiferromagnetic one, with the strenght approximatedly represented by their dimension.
