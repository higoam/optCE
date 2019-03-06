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
'godstein_price.func'
#'engvall.func'
#
#'alpine1.func'
#'egg_crate.func'
#'himmelblau.func'
#'leon.func'
#'price_4.func'
#'schwefel_2_25.func'
#'sphere.func'
#'wayburn_seader_2.func'
#'price_1.func'
#'dixon_price.func'
#'rosenbrock.func'
#'wayburn_seader_1.func'
#'qing.func'
#'beale.func'
#
#'cube.func'
#'chung_reynolds.func'
#'cigar.func'
#'zakharov.func'
#'sphere.func'
#'schumer.func'
#'sum_squares.func'
#'matyas.func'
#'rotated_ellipse_02.func'
#'zettl.func'
#'power_sum.func'
#'schwefel_2_20.func'
);

	echo "#############  Experiments to --generalized --double CEGIO-G Prec 3  ##############"	>> resultado_exp_CEGIO_G_MINISAT.txt
	echo "#############  Experiments to --generalized --double CEGIO-G Prec 3  ##############"	

#	echo "#############  CBMC - MINISAT  ##############"	>> resultado_exp_CEGIO_G_MINISAT.txt
#	echo "#############  CBMC - MINISAT  ##############"
#	for i in "${functions[@]}"
#	do		
#		line=$i
#		func=${line//,*}       	
#
#		(time ./optCE_1000 $func --cbmc --minisat --generalized --double --library=math2.h --precision=3) &>> resultado_exp_CEGIO_G_MINISAT.txt
#	done

	echo "#############  ESBMC - Mathsat  ##############"	>> resultado_exp_CEGIO_G_MINISAT.txt	
	echo "#############  ESBMC - Mathsat  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		(time ./optCE_1000 $func --esbmc --mathsat --generalized --double --library=math2.h --precision=3) &>> resultado_exp_CEGIO_G_MATHSAT.txt 
	done

	echo "#############  ESBMC - Boolector  ##############"	>> resultado_exp_CEGIO_G_MINISAT.txt
	echo "#############  ESBMC - Boolector  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		(time ./optCE_1000 $func --esbmc --boolector --generalized --double --library=math2.h --precision=3) &>> resultado_exp_CEGIO_G_BOOLECTOR.txt 
	done

	echo "#############  ESBMC - Z3  ##############" >> resultado_exp_CEGIO_G_MINISAT.txt
	echo "#############  ESBMC - Z3  ##############"	
	for i in "${functions[@]}"
	do		
		line=$i
		func=${line//,*}       	

		(time ./optCE_1000 $func --esbmc --z3 --generalized --double --library=math2.h --precision=3) &>> resultado_exp_CEGIO_G_Z3.txt 
	done

