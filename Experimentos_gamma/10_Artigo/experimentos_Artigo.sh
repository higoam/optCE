#!/bin/bash

declare -a functions=(
'alpine1.func'
'cosine.func'
'styblinski_tang.func'
'zirilli.func'
'booth.func'
'himmelblau.func'
'leon.func'
'zettl.func'
'sum_squares.func'
'rotated_ellipse_02.func'
);

	echo
	echo "#############  Experiments to --generalized CEGIO-G prec3 ##############"	
	echo

	echo "#############  ESBMC - Mathsat  ##############"	>> resultado_exp_CEGIO_G_MATHSAT.txt
	echo "#############  ESBMC - Mathsat  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		(time ./optCE_1000 $func --esbmc --mathsat --generalized --library=math2.h --precision=3) &>> resultado_exp_CEGIO_G_MATHSAT.txt 
	done

	echo "#############  ESBMC - Z3  ##############" >> resultado_exp_CEGIO_G_Z3.txt
	echo "#############  ESBMC - Z3  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		(time ./optCE_1000 $func --esbmc --z3 --generalized --library=math2.h --precision=3) &>> resultado_exp_CEGIO_G_Z3.txt 
	done

	echo "#############  ESBMC - Boolector  ##############"	>> resultado_exp_CEGIO_G_BOOLECTOR.txt
	echo "#############  ESBMC - Boolector  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		(time ./optCE_1000 $func --esbmc --boolector --generalized --library=math2.h --precision=3) &>> resultado_exp_CEGIO_G_BOOLECTOR.txt 
	done

	echo "#############  CBMC - MINISAT  ##############"	>> resultado_exp_CEGIO_G_MINISAT.txt
	echo "#############  CBMC - MINISAT  ##############"
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		(time ./optCE_1000 $func --cbmc --minisat --generalized --library=math2.h --precision=3) &>> resultado_exp_CEGIO_G_MINISAT.txt
	done


