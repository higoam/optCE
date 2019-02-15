#!/bin/bash

declare -a functions=(
'adjiman.func'
'bohachevsky_1.func'
'bohachevsky_3.func'
'branin_RCOS.func'
'camel_six.func'
'camel_three.func'
'cosine.func'
'scahffer_1.func'
'styblinski_tang.func'
'trecanni.func'
'tsoulos.func'
'ursem_1.func'
'wayburn_seader_1.func'
'zirilli.func'
#
'alpine1.func'
'egg_crate.func'
'himmelblau.func'
'leon.func'
'price_4.func'
'schwefel_2_25.func'
'sphere.func'
'wayburn_seader_2.func'
'price_1.func'
#
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

