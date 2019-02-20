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

	echo "#############  CBMC - MINISAT  ##############"	
#	for i in "${functions[@]}"
#	do		
#		line=$i
#		func=${line//,*}       	
#
#		echo
#		(time ./optCE_1000 $func --cbmc --minisat --generalized --library=math2.h --precision=3 >> resultado_exp_Artigo_MINISAT.txt) 
#		echo
#	done
#
	echo "#############  ESBMC - Mathsat  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE_1000 $func --esbmc --mathsat --generalized --library=math2.h --precision=3 >> resultado_exp_Artigo_MATHSAT.txt) 
		echo
	done


	echo "#############  ESBMC - Boolector  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE_1000 $func --esbmc --boolector --generalized --library=math2.h --precision=3 >> resultado_exp_Artigo_BOOLECTOR.txt) 
		echo
	done

	echo "#############  ESBMC - Z3  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo
		(time ./optCE_1000 $func --esbmc --z3 --generalized --library=math2.h --precision=3 >> resultado_exp_Artigo_Z3.txt) 
		echo
	done

