#!/bin/bash

declare -a functions=(
'booth.func'
'chung_reynolds.func'
'cube.func'
'dixon_price.func'
'power_sum.func'
'schumer.func'
'sum_squares.func'
'matyas.func'
'rotated_ellipse.func'
'zettl.func'
'mccormick.func'
'godstein_price.func'
);

	echo
	echo "#############  Experiments to --convex CEGIO-F prec2  ##############"	
	echo

	echo "#############  CBMC - MINISAT  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE $func --cbmc --minisat --convex --library=math2.h --precision=2 >> resultado_exp_CEGIO_F_MINISAT.txt) 
		echo
	done

	echo "#############  ESBMC - Mathsat  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE $func --esbmc --mathsat --convex --library=math2.h --precision=2 >> resultado_exp_CEGIO_F_MATHSAT.txt) 
		echo
	done


	echo "#############  ESBMC - Boolector  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE $func --esbmc --boolector --convex --library=math2.h --precision=2 >> resultado_exp_CEGIO_F_BOOLECTOR.txt) 
		echo
	done

	echo "#############  ESBMC - Z3  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE $func --esbmc --z3 --convex --library=math2.h --precision=2 >> resultado_exp_CEGIO_F_Z3.txt) 
		echo
	done

