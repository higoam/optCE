#!/bin/bash

 	declare -a functions_all=(
		'alpine1.func'  
		'cosine.func'
		'styblinski_tang.func'
		'zirilli.func'
		'booth.func'
		'himmelblau.func'
		'leon.func'               
		'zettl.func'
		'sum_squares.func'
      	'rotated_ellipse.func'        
	);

 	declare -a functions_positive=(
		'booth.func'
		'himmelblau.func'
		'leon.func'               
	);

 	declare -a functions_convex=(
		'zettl.func'
		'sum_squares.func'
      	'rotated_ellipse.func'        
	);

	echo
	echo "#############  Experiments to --generalized  ##############"	
	echo

	for i in "${functions_all[@]}"
	do		
		line=$i
		func=${line//,*}       	

#		(./optCE $func --esbmc --boolector --generalized --library=math2.h --precision=3) #
#		echo""
#		(./optCE $func --esbmc --z3 --generalized --library=math2.h --precision=3) 
#		echo""
#		(./optCE $func --esbmc --mathsat --generalized --library=math2.h --precision=3)
#		echo""
		(./optCE $func --cbmc --minisat --generalized --library=math2.h --precision=3) 
		echo""

		echo
	done

