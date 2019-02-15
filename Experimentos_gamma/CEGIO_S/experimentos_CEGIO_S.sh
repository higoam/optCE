#!/bin/bash

declare -a functions=(
'alpine1.func'
'egg_crate.func'
'himmelblau.func'
'leon.func'
'price_4.func'
'schwefel_2_25.func'
'sphere.func'
'wayburn_seader_2.func'
'price_1.func'
);

	echo
	echo "#############  Experiments to --positive CEGIO-S prec2  ##############"	
	echo

	echo "#############  CBMC - MINISAT  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE $func --cbmc --minisat --positive --library=math2.h --precision=2 >> resultado_exp_CEGIO_S_MINISAT.txt) 
		echo
	done

	echo "#############  ESBMC - Mathsat  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE $func --esbmc --mathsat --positive --library=math2.h --precision=2 >> resultado_exp_CEGIO_S_MATHSAT.txt) 
		echo
	done


	echo "#############  ESBMC - Boolector  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE $func --esbmc --boolector --positive --library=math2.h --precision=2 >> resultado_exp_CEGIO_S_BOOLECTOR.txt) 
		echo
	done

	echo "#############  ESBMC - Z3  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE $func --esbmc --z3 --positive --library=math2.h --precision=2 >> resultado_exp_CEGIO_S_Z3.txt) 
		echo
	done

