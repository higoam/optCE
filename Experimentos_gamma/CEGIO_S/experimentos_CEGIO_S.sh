#!/bin/bash

declare -a functions=(
#'adjiman.func'
#'bohachevsky_1.func'
#'bohachevsky_3.func'
#'branin_RCOS.func'
#'camel_six.func'
#'camel_three.func'
#'cosine.func'
#'scahffer_1.func'
#'styblinski_tang.func'
#'trecanni.func'
#'tsoulos.func'
#'ursem_1.func'
#'wayburn_seader_1.func'
#'zirilli.func'
#'rotated_ellipse.func'
#
#'booth.func'
#'price_1.func'
#'himmelblau.func'
#'leon.func'
#'price_4.func'
#'schwefel_2_25.func'
#'rosenbrock.func'
#'wayburn_seader_1.func'
#'qing.func'
#'dixon_price.func'
'beale.func'
#
#'chung_reynolds.func'
#'cube.func'
#'mccormick.func'
#'godstein_price.func'
#'schumer.func'
#'sum_squares.func'
#'matyas.func'
#'rotated_ellipse_02.func'
#'zettl.func'
);

	echo "#############  Experiments to --positive CEGIO-S Prec 3  ##############"	>> resultado_exp_CEGIO_G_MINISAT.txt
	echo "#############  Experiments to --positive CEGIO-S Prec 3  ##############"	

	echo "#############  CBMC - MINISAT  ##############"	>> resultado_exp_CEGIO_G_MINISAT.txt
	echo "#############  CBMC - MINISAT  ##############"
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		(time ./optCE_1000 $func --cbmc --minisat --positive --library=math2.h --precision=3) &>> resultado_exp_CEGIO_G_MINISAT.txt
	done

	echo "#############  ESBMC - Mathsat  ##############"	>> resultado_exp_CEGIO_G_MATHSAT.txt	
	echo "#############  ESBMC - Mathsat  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		(time ./optCE_1000 $func --esbmc --mathsat --positive --library=math2.h --precision=3) &>> resultado_exp_CEGIO_G_MATHSAT.txt 
	done

	echo "#############  ESBMC - Boolector  ##############"	>> resultado_exp_CEGIO_G_BOOLECTOR.txt
	echo "#############  ESBMC - Boolector  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		(time ./optCE_1000 $func --esbmc --boolector --positive --library=math2.h --precision=3) &>> resultado_exp_CEGIO_G_BOOLECTOR.txt 
	done

	echo "#############  ESBMC - Z3  ##############" >> resultado_exp_CEGIO_G_Z3.txt
	echo "#############  ESBMC - Z3  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		(time ./optCE_1000 $func --esbmc --z3 --positive --library=math2.h --precision=3) &>> resultado_exp_CEGIO_G_Z3.txt 
	done

