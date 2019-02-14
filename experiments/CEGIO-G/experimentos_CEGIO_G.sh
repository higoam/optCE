#!/bin/bash

declare -a functions_easy=(
#'beale.func'
'bohachevsky_1.func'
'bohachevsky_2.func'
'bohachevsky_3.func'
'booth.func'
'bukin_2.func'
'bukin_4.func'
'bukin_6.func'
'camel_three.func'
'camel_six.func'
'csendes.func'
'egg_crate.func'
'freudenstein.func'
'himmelblau.func'
'leon.func'
'matyas.func'
'price_1.func'
'price_4.func'
'quadratic.func'
'rotated_ellipse.func'
'sphere.func'
'styblinski_tang.func'
'sum_squares.func'
);


declare -a functions_hard=(
'adjiman.func'
'alpine1.func'
'bartels.func'
'branin_RCOS.func'
'chen_bird.func'
'chen_v.func'
'cosine.func'
'deckkers_arts.func'
'el_attar_vidyasager_dutta.func'
'engvall.func'
'scahffer_1.func'
'scahffer_2.func'
'scahffer_4.func'
'schwefel_2_25.func'
'trecanni.func'
'tsoulos.func'
'ursem_1.func'
'wayburn_seader_1.func'
'wayburn_seader_2.func'
'wayburn_seader_3.func'
'zettl.func'
'szirilli.func'
);

declare -a functions_all=(
'adjiman.func'
'alpine1.func'
'bartels.func'
'beale.func'
'bohachevsky_1.func'
'bohachevsky_2.func'
'bohachevsky_3.func'
'booth.func'
'branin_RCOS.func'
'bukin_2.func'
'bukin_4.func'
'bukin_6.func'
'camel_six.func'
'camel_three.func'
'chen_bird.func'
'chen_v.func'
'cosine.func'
'csendes.func'
'deckkers_arts.func'
'egg_crate.func'
'el_attar_vidyasager_dutta.func'
'engvall.func'
'freudenstein.func'
'himmelblau.func'
'leon.func'
'matyas.func'
'price_1.func'
'price_4.func'
'quadratic.func'
'rotated_ellipse.func'
'scahffer_1.func'
'scahffer_2.func'
'scahffer_4.func'
'schwefel_2_25.func'
'sphere.func'
'styblinski_tang.func'
'sum_squares.func'
'trecanni.func'
'tsoulos.func'
'ursem_1.func'
'wayburn_seader_1.func'
'wayburn_seader_2.func'
'wayburn_seader_3.func'
'zettl.func'
'szirilli.func'
#'sum_squares.func'
#'cube.func'
);

	echo
	echo "#############  Experiments to --generalized  ##############"	
	echo


	for i in "${functions_easy[@]}"
	do		
		line=$i
		func=${line//,*}       	

		echo "#############  ESBMC - Boolector  ##############"	
		echo
		(time ./optCE $func --esbmc --boolector --generalized --library=math2.h --precision=2) 
		echo

		echo "#############  ESBMC - Z3  ##############"	
		echo
		(time ./optCE $func --esbmc --z3 --generalized --library=math2.h --precision=2) 

		echo "#############  ESBMC - Mathsat  ##############"	
		echo
		(time ./optCE $func --esbmc --mathsat --generalized --library=math2.h --precision=2)

#		echo "#############  CBMC - MiniSAT  ##############"	
#		echo
#		(time ./optCE $func --cbmc --minisat --generalized --library=math2.h --precision=1)

		echo
	done


















#	echo
#	echo "#############  Experiments to --positive  ##############"	
#	echo
#
#	for i in "${functions_positive[@]}"
#	do		
#		line=$i
#		func=${line//,*}       	
#
#		(./optCE $func --esbmc --boolector --positive --library=math2.h --precision=3) 
#		echo
#		(./optCE $func --esbmc --z3 --positive --library=math2.h --precision=3) 
#		echo
#		(./optCE $func --esbmc --mathsat --positive --library=math2.h --precision=3)
#		echo
#		(./optCE $func --cbmc --minisat --positive --library=math2.h --precision=3) 
#		echo
#
#		echo
#	done
#
#	echo
#	echo "#############  Experiments to --convex  ##############"	
#	echo
#
#	for i in "${functions_positive[@]}"
#	do		
#		line=$i
#		func=${line//,*}       	
#
#		(./optCE $func --esbmc --boolector --convex --library=math2.h --precision=3) 
#		echo
#		(./optCE $func --esbmc --z3 --convex --library=math2.h --precision=3) 
#		echo
#		(./optCE $func --esbmc --mathsat --convex --library=math2.h --precision=3)
#		echo
#		(./optCE $func --cbmc --minisat --convex --library=math2.h --precision=3) 
#		echo



		echo
	done

