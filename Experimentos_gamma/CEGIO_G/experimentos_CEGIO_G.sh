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
	echo "#############  Experiments to --generalized CEGIO-G Prec2  ##############"	
	echo

	echo "#############  CBMC - MINISAT  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE $func --cbmc --minisat --generalized --library=math2.h --precision=2 >> resultado_exp_CEGIO_G_MINISAT.txt) 
		echo
	done

	echo "#############  ESBMC - Mathsat  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE $func --esbmc --mathsat --generalized --library=math2.h --precision=2 >> resultado_exp_CEGIO_G_MATHSAT.txt) 
		echo
	done


	echo "#############  ESBMC - Boolector  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE $func --esbmc --boolector --generalized --library=math2.h --precision=2 >> resultado_exp_CEGIO_G_BOOLECTOR.txt) 
		echo
	done

	echo "#############  ESBMC - Z3  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE $func --esbmc --z3 --generalized --library=math2.h --precision=2 >> resultado_exp_CEGIO_G_Z3.txt) 
		echo
	done
