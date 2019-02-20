#!/bin/bash

declare -a functions=(
'chen_v.func'
'chen_bird.func'
'h1.func'
);

	echo
	echo "#############  Experiments to --generalized CEGIO-G prec3 ##############"	
	echo

	echo "#############  CBMC - MINISAT  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE_1000 $func --cbmc --minisat --generalized --library=math2.h --precision=5 >> resultado_exp_maximum_MINISAT.txt) 
		echo
	done

	echo "#############  ESBMC - Mathsat  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE_1000 $func --esbmc --mathsat --generalized --library=math2.h --precision=5 >> resultado_exp_maximum_MATHSAT.txt) 
		echo
	done


	echo "#############  ESBMC - Boolector  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE_1000 $func --esbmc --boolector --generalized --library=math2.h --precision=5 >> resultado_exp_maximum_BOOLECTOR.txt) 
		echo
	done

	echo "#############  ESBMC - Z3  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE_1000 $func --esbmc --z3 --generalized --library=math2.h --precision=5 >> resultado_exp_maximum_Z3.txt) 
		echo
	done

