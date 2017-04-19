## Synopsis

The OptCE is a verification tool developed for optimizing target functions. 
OptCE employs bounded model checking techniques based on satisfiability modulo 
theories and boolean satisfiability, which are able to obtain global minima 
of convex and nonconvex functions. OptCE is implemented in C/C++, performs 
all optimization steps automatically for CEGIOs algorithms.

## Motivation

Optimization is a tool employed in several research fields, such as computer science 
and engineering with the goal of obtaining maximum system's performance. 
Although there are several available optimization techniques, simulated annealing, 
particle swarm, and genetic algorithms, their main difficulty lies on locating 
the global minima of functions. As a consequence, they often present suboptimal 
solutions; they are trapped by local minima, which commonly leads to low performance 
or even system error.

The OptCE is a tool based on the counterexample-guided inductive 
optimization (CEGIO) algorithms proposed by Araújo et al [1]. 
OptCE  employs non-deterministic representation of decision variables 
and constrains the state-space search based on counterexamples produced 
by a boolean satisfiability (SAT) or satisfiability modulo theories (SMT) solver, 
in order to to perform inductive generalization and thus achieve complete global optimization. 
The OptCE employ model checking verification procedures to  guide the global optima 
convergence, extracting information from counterexamples, which is always able to 
find global minima in optimization functions, unlike traditional methods.

## Organization of the project

	.
	├── benchmarks		-> Test cases	
	├── bin			-> Executables of OptCE and dependencies
	├── experiments		-> Experiments
	│   ├── Matlab		-> Experiments of the benchmarks with other techniques 
	│	│		(genetic algorithm, particle swarm, pattern search, simulated annealing, and nonlinear programming)
	│   └── OptCE		-> Experiments of the benchmarks with OptCE
	├── include		-> Librarys
	└── src			-> Conte code + Makefile

## Installation

To compile the project, just use make in the src directory.

To use OptCE, OptCE, ESBMC, CBMC, the math2.h library, and 
the function input file must be in the same directory.

Tests can be performed as shown in the ##TESTS section. 
In the (experiments/OptCE) directory, there is a script to run 
all experiments automatically.

## Tests

	* Informs the configuration options of the tool
	./optCE --help 

	* Perform optimization with the setting ( ESBMC + Mathsat + SEGIO-G ), by default it establishes precision of 3 decimal places.
	./optCE name_function.func --esbmc --mathsat --generalized --library=math2.h 

	* Perform optimization with the setting ( ESBMC + Mathsat + SEGIO-S ), by default it establishes precision of 3 decimal places.
	./optCE name_function.func --esbmc --mathsat --positive --library=math2.h 

	* Perform optimization with the setting ( ESBMC + Mathsat + SEGIO-F ), by default it establishes precision of 3 decimal places.
	./optCE name_function.func --esbmc --mathsat --convex --library=math2.h 

	* Perform optimization with the setting ( CBMC + MiniSAT + SEGIO-G ), by default it establishes precision of 3 decimal places.
	./optCE name_function.func --cbmc --minisat --generalized --library=math2.h 

	* Perform optimization with the setting ( ESBMC + Mathsat + SEGIO-G ), initialization or algorithm in 25.
	./optCE name_function.func --esbmc --mathsat --generalized --library=math2.h --start-value=25

	* Perform optimization with the setting ( ESBMC + Mathsat + SEGIO-G ), uses precision 2 decimal places.
	./optCE name_function.func --esbmc --mathsat --generalized --library=math2.h --precision=2

	* Perform optimization with the setting ( ESBMC + Mathsat + SEGIO-G ), sets the timeout for 3600s.
	./optCE name_function.func --esbmc --mathsat --generalized --library=math2.h --timeout=3600

## Contributors

Higo Albuquerque <albuquerque.higo@gmail.com>
Rodrigo Araujo <rod.faraujo@gmail.com>
Iury Bessa <iury.bessa@gmail.com>
Lucas Cordeiro <lucas.cordeiro@cs.ox.ac.uk>
Eddie Lima <eddie_batista@yahoo.com.br>


## License

Apache License Version 2.0

## References

[1] Rodrigo Araujo, Iury Bessa, Lucas Carvalho Cordeiro, Joao Edgar Chaves Filho:
SMT-based Verification Applied to Non-convex Optimization Problems. SBESC 2016: 1-8

[2] R. Araújo, H. Albuquerque, I. Bessa, L. Cordeiro, J. E. C. Filho, Counterexample
guided inductive optimization, in: arXiv:1704.03738 [cs.AI], 2017, pp. 1–32.
URL http://arxiv.org/abs/1704.03738
