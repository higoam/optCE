/*
 * Generatefiles.cpp
 *
 *  Created on: 30 de jan de 2019
 *      Author: higo
 */

#include "Generatefiles.h"

namespace GENERATEFILES {

Generatefiles::Generatefiles() {
	// TODO Auto-generated constructor stub

}

Generatefiles::~Generatefiles() {
	// TODO Auto-generated destructor stub
}

void Generatefiles::create_f(Setup* setup_aux)
{
	int i;
	string name;
	name = setup_aux->getNameFunction() + ".c";
	ofstream file;
	file.open(name.c_str());

	file << "\n";
	file << "    #include <stdio.h> \n";
	file << "    #include <stdlib.h> \n";
	file << "    #include \"math2.h\" \n";
	file << "\n";
	file << "  int main(int argc, char *argv[ ]) {\n";
	file << "\n";
	file << "    "+ setup_aux->getTypeData() +" fobj";

//	cout << "VAR" << endl;
//	cout << setup_aux->getVar() << endl;

	for(i=1;i<=setup_aux->getVar();i++){
		file << ",X" << convertValue.convertDoubleString(i);
	}

	file << ";\n";

	for(i=1;i<=setup_aux->getVar();i++){
		file << "    X" << convertValue.convertDoubleString(i);
		file << " = atof(argv[" << convertValue.convertDoubleString(i);
		file << "]);\n";
	}

	file << "\n\n";
	file << "    " + setup_aux->getInputFunction() + "\n";
	file << "\n\n";
	file << "    printf(\"%f\", fobj);\n";
	file << "\n";
	file << "    return 0;\n";
	file << "  }\n";
	file.close();
}


void Generatefiles::create_specification(Setup* setup_aux)
{
	string library_user="";

	if(setup_aux->getLibrary() != "")
	{
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
	}
	else
	{
		library_user = "\n\n";
	}

	string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
	ofstream file_min;
	file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

  	file_min << library_user;
  	file_min << "#include <math.h>\n";
  	file_min << "\n";
  	file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
  	file_min << "\n";
  	file_min << "    int main() {\n";

  	file_min << "    \n";
//  	file_min << "    "+ setup_aux->getTypeData() +" f_i = " + setup_aux->fc_current_string + ";\n\n";
  	file_min << "    "+ setup_aux->getTypeData() +" f_i = " + convertValue.convertDoubleString(setup_aux->getFcCurrent()) + ";\n\n";

  	file_min << "    int i,j;\n";
  	file_min << "    int x[3];\n";
  	file_min << "    "+ setup_aux->getTypeData() +" X[2];\n";
  	file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

  	file_min << "    for (i = 0; i<2; i++){\n";
  	file_min << "      x[i] = nondet_int();\n";
  	file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
  	file_min << "    }\n";

  	file_min << setup_aux->getRestrictions();


  	file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";

  	file_min << "    __ESBMC_assume(fobj < f_i );\n\n";

  	file_min << "    assert(fobj > f_i);\n";

  	file_min << "    return 0;\n";
  	file_min << "  }\n";
  	file_min.close();


}

void Generatefiles::create_specification_CEGIO_G(Setup* setup_aux){

	if(setup_aux->getInputFormat() == 0){

		if(setup_aux->getTypeLoop() == 0){
			create_specification_CEGIO_G_Matrix_sem_FOR(setup_aux);
		}else if(setup_aux->getTypeLoop() == 1){
			create_specification_CEGIO_G_Matrix_com_FOR(setup_aux);
		}

	}else if(setup_aux->getInputFormat() == 1){

		create_specification_CEGIO_G_Equational(setup_aux);

	}

}


void Generatefiles::create_specification_CEGIO_G_Matrix_com_FOR(Setup* setup_aux){

	string library_user="";

	if(setup_aux->getLibrary() != ""){
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
	}else{
		library_user = "\n\n";
	}

	string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
	ofstream file_min;
	file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

  	file_min << library_user;
  	file_min << "#include <math.h>\n";
  	file_min << "\n";
  	file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
  	file_min << "\n";
  	file_min << "    int main() {\n";

  	file_min << "    \n";
  	file_min << "    "+ setup_aux->getTypeData() +" f_i = " + convertValue.convertDoubleString(setup_aux->getFcCurrent()) + ";\n\n";

  		file_min << "    int i,j;\n";
  	  	file_min << "    int a[" << convertValue.convertDoubleString(setup_aux->getVar()+1) <<  "];\n";
  	  	file_min << "    "+ setup_aux->getTypeData() +" X[" <<  convertValue.convertDoubleString(setup_aux->getVar())<<  "];\n";
  	  	file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

  	  	file_min << "    for (i = 0; i<" <<  convertValue.convertDoubleString(setup_aux->getVar())<<  "; i++){\n";
  	  	file_min << "      a[i] = nondet_int();\n";
  	  	file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
  	  	file_min << "    }\n";



  	  	file_min << "     \n        //-----------------------------------------------------------  ";
  	    file_min << "     \n        // Restrictions\n";

  	    file_min << "     \n        int lim[4] = {";

  	    file_min << convertValue.convertIntString(setup_aux->getInfX1()) + "*p, ";
  	    file_min << convertValue.convertIntString(setup_aux->getSupX1()) + "*p, ";
  	    file_min << convertValue.convertIntString(setup_aux->getInfX2()) + "*p, ";
  	    file_min << convertValue.convertIntString(setup_aux->getSupX2()) + "*p}; ";

  	    file_min <<  "\n";
	    file_min <<  "\n        for (i = 0; i < nv; i++) {";
  	    file_min <<  "\n            __ESBMC_assume( (a[i]>=lim[2*i]) && (a[i]<=lim[2*i+1]) );";
  	    file_min <<  "\n            __ESBMC_assume( X[i] == (float) a[i]/p  ); ";
  	    file_min <<  "\n        }\n";

  	    file_min <<  "     \n        //-----------------------------------------------------------  \n\n";

  	    file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";

  	// Determina se o ASSUME e ASSERT para ESBMC e CBMC
  	if(setup_aux->getBmc() == 1){
  	  	file_min << "    __ESBMC_assume(fobj < f_i );\n\n";
  	  	file_min << "    assert(fobj > f_i);\n";
  	}else if(setup_aux->getBmc() == 2){
  	  	file_min << "    __CPROVER_assume(fobj < f_i );\n\n";
  	  	file_min << "    __CPROVER_assert(fobj > f_i, "");\n";
  	}

  	file_min << "    return 0;\n";
  	file_min << "  }\n";
  	file_min.close();

}

void Generatefiles::create_specification_CEGIO_G_Matrix_sem_FOR(Setup* setup_aux){

//	cout << "create_specification_CEGIO_G_Matrix_sem_FOR" << endl;

	int i;

	string library_user="";

	if(setup_aux->getLibrary() != ""){
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
	}else{
		library_user = "\n\n";
	}

	string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
	ofstream file_min;
	file_min.open(name.c_str());

    	file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";

  		file_min << library_user;
  		file_min << "#include <math.h>\n";
  		file_min << "\n";
  		file_min << "    int nondet_int();\n";
  		file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
  		file_min << "\n";
  		file_min << "    int main() {\n";

  		file_min << "    \n";
		file_min << "    "+ setup_aux->getTypeData() +" f_i = " + convertValue.convertDoubleString(setup_aux->getFcCurrent()) + ";\n\n";
  		file_min << "    "+ setup_aux->getTypeData() +" fobj;";
  		file_min << "    \n";

  		file_min << "    int ";

		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "x" << i << ",";
		}
		file_min << "x" << (i) << ";\n";


  		file_min << "    " <<  setup_aux->getTypeData()  << " ";
		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "X" << i << ",";
		}
		file_min << "X" << (i) << ";\n\n";


		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "    x" << i << " = nondet_int();\n";
			file_min << "    X" << i << " = (" << setup_aux->getTypeData() << ") nondet_" << setup_aux->getTypeData() << "();\n";
		}
		file_min << "    x" << i << " = nondet_int();\n";
		file_min << "    X" << i << " = (" << setup_aux->getTypeData() << ") nondet_" << setup_aux->getTypeData() << "();\n";



  	  	file_min << "     \n     //-----------------------------------------------------------  ";
  	    file_min << "     \n     // Restrictions\n\n";

  	  	// Determina se o ASSUME e ASSERT para ESBMC e CBMC
  	  	if(setup_aux->getBmc() == 1){
  			file_min << "          __ESBMC_assume( (x1>="<< convertValue.convertIntString(setup_aux->getInfX1()) << "*p"<<")";
  				file_min << "&& (x1<=" <<  convertValue.convertIntString( setup_aux->getSupX1() ) << "*p) );\n";

  			file_min << "          __ESBMC_assume( (x2>="<< convertValue.convertIntString(setup_aux->getInfX2()) << "*p"<<")";
  				file_min << "&& (x2<=" <<  convertValue.convertIntString( setup_aux->getSupX1() ) << "*p) );\n";

  			file_min << "          __ESBMC_assume( X1 == (" << setup_aux->getTypeData() << ") " << "x1/p );\n";
  			file_min << "          __ESBMC_assume( X2 == (" << setup_aux->getTypeData() << ") " << "x2/p );\n";

  	  	}else if(setup_aux->getBmc() == 2){
  			file_min << "          __CPROVER_assume( (x1>="<< convertValue.convertIntString(setup_aux->getInfX1()) << "*p"<<")";
  				file_min << "&& (x1<=" <<  convertValue.convertIntString( setup_aux->getSupX1() ) << "*p) );\n";

  			file_min << "          __CPROVER_assume( (x2>="<< convertValue.convertIntString(setup_aux->getInfX2()) << "*p"<<")";
  				file_min << "&& (x2<=" <<  convertValue.convertIntString( setup_aux->getSupX1() ) << "*p) );\n";

  			file_min << "          __CPROVER_assume( X1 == (" << setup_aux->getTypeData() << ") " << "x1/p );\n";
  			file_min << "          __CPROVER_assume( X2 == (" << setup_aux->getTypeData() << ") " << "x2/p );\n";

  	  	}

  	    file_min <<  "    //-----------------------------------------------------------  \n\n";

  	    file_min << "    " + setup_aux->getInputFunction() + "\n";

  	// Determina se o ASSUME e ASSERT para ESBMC e CBMC
  	if(setup_aux->getBmc() == 1){
  	  	file_min << "    __ESBMC_assume(fobj < f_i );\n\n";
  	  	file_min << "    assert(fobj > f_i);\n";
  	}else if(setup_aux->getBmc() == 2){
  	  	file_min << "    __CPROVER_assume(fobj < f_i );\n\n";
  	  	file_min << "    __CPROVER_assert(fobj > f_i, \"\");\n";
  	}

  	file_min << "    return 0;\n";
  	file_min << "  }\n";
  	file_min.close();

}

void Generatefiles::create_specification_CEGIO_G_Equational(Setup* setup_aux){

	int i;

	string library_user="";

	if(setup_aux->getLibrary() != ""){
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
	}else{
		library_user = "\n\n";
	}

	string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
	ofstream file_min;
	file_min.open(name.c_str());

    	file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";

  		file_min << library_user;
  		file_min << "#include <math.h>\n";
  		file_min << "\n";
  		file_min << "    int nondet_int();\n";
  		file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
  		file_min << "\n";
  		file_min << "    int main() {\n";

  		file_min << "    \n";
		file_min << "    "+ setup_aux->getTypeData() +" f_i = " + convertValue.convertDoubleString(setup_aux->getFcCurrent()) + ";\n\n";
  		file_min << "    "+ setup_aux->getTypeData() +" fobj;";
  		file_min << "    \n";

  		file_min << "    int ";

		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "x" << i << ",";
		}
		file_min << "x" << (i) << ";\n";


  		file_min << "    " <<  setup_aux->getTypeData()  << " ";
		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "X" << i << ",";
		}
		file_min << "X" << (i) << ";\n\n";


		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "    x" << i << " = nondet_int();\n";
			file_min << "    X" << i << " = (" << setup_aux->getTypeData() << ") nondet_" << setup_aux->getTypeData() << "();\n";
		}
		file_min << "    x" << i << " = nondet_int();\n";
		file_min << "    X" << i << " = (" << setup_aux->getTypeData() << ") nondet_" << setup_aux->getTypeData() << "();\n";



  	  	file_min << "     \n     //-----------------------------------------------------------  ";
  	    file_min << "     \n     // Restrictions\n\n";

  	    file_min << setup_aux->getCodeRestrictionsModified();

  	    file_min <<  "    //-----------------------------------------------------------  \n\n";

  	    file_min << "    " + setup_aux->getInputFunction() + "\n";

  	// Determina se o ASSUME e ASSERT para ESBMC e CBMC
  	if(setup_aux->getBmc() == 1){
  	  	file_min << "    __ESBMC_assume(fobj < f_i );\n\n";
  	  	file_min << "    assert(fobj > f_i);\n";
  	}else if(setup_aux->getBmc() == 2){
  	  	file_min << "    __CPROVER_assume(fobj < f_i );\n\n";
  	  	file_min << "    __CPROVER_assert(fobj > f_i, \"\");\n";
  	}

  	file_min << "    return 0;\n";
  	file_min << "  }\n";
  	file_min.close();



}


void Generatefiles::create_specification_CEGIO_S(Setup* setup_aux){

	if(setup_aux->getInputFormat() == 0){

		if(setup_aux->getTypeLoop() == 0){
			create_specification_CEGIO_S_Matrix_sem_FOR(setup_aux);
		}else if(setup_aux->getTypeLoop() == 1){
			create_specification_CEGIO_S_Matrix_com_FOR(setup_aux);
		}

	}else if(setup_aux->getInputFormat() == 1){

		create_specification_CEGIO_S_Equational(setup_aux);

	}
}

void Generatefiles::create_specification_CEGIO_S_Matrix_com_FOR(Setup* setup_aux){

}

void Generatefiles::create_specification_CEGIO_S_Matrix_sem_FOR(Setup* setup_aux){

	int i;

	string library_user="";

	if(setup_aux->getLibrary() != ""){
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
	}else{
		library_user = "\n\n";
	}

	string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
	ofstream file_min;
	file_min.open(name.c_str());

    	file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";

  		file_min << library_user;
  		file_min << "#include <math.h>\n";
  		file_min << "\n";
  		file_min << "    int nondet_int();\n";
  		file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
  		file_min << "\n";
  		file_min << "    int main() {\n";

  		file_min << "    \n";
		file_min << "    "+ setup_aux->getTypeData() +" f_i = " + convertValue.convertDoubleString(setup_aux->getFcCurrent()) + ";\n\n";
		file_min << "    "+ setup_aux->getTypeData() +" f_c = 0;\n";
		file_min << "    "+ setup_aux->getTypeData() +" fobj;";
  		file_min << "    \n";

  		file_min << "    int ";

		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "x" << i << ",";
		}
		file_min << "x" << (i) << ";\n";


  		file_min << "    " <<  setup_aux->getTypeData()  << " ";
		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "X" << i << ",";
		}
		file_min << "X" << (i) << ";\n\n";


		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "    x" << i << " = nondet_int();\n";
			file_min << "    X" << i << " = (" << setup_aux->getTypeData() << ") nondet_" << setup_aux->getTypeData() << "();\n";
		}
		file_min << "    x" << i << " = nondet_int();\n";
		file_min << "    X" << i << " = (" << setup_aux->getTypeData() << ") nondet_" << setup_aux->getTypeData() << "();\n";



  	  	file_min << "     \n     //-----------------------------------------------------------  ";
  	    file_min << "     \n     // Restrictions\n\n";

  	  	// Determina se o ASSUME e ASSERT para ESBMC e CBMC
  	  	if(setup_aux->getBmc() == 1){
  			file_min << "          __ESBMC_assume( (x1>="<< convertValue.convertIntString(setup_aux->getInfX1()) << "*p"<<")";
  				file_min << "&& (x1<=" <<  convertValue.convertIntString( setup_aux->getSupX1() ) << "*p) );\n";

  			file_min << "          __ESBMC_assume( (x2>="<< convertValue.convertIntString(setup_aux->getInfX2()) << "*p"<<")";
  				file_min << "&& (x2<=" <<  convertValue.convertIntString( setup_aux->getSupX1() ) << "*p) );\n";

  			file_min << "          __ESBMC_assume( X1 == (" << setup_aux->getTypeData() << ") " << "x1/p );\n";
  			file_min << "          __ESBMC_assume( X2 == (" << setup_aux->getTypeData() << ") " << "x2/p );\n";

  	  	}else if(setup_aux->getBmc() == 2){
  			file_min << "          __CPROVER_assume( (x1>="<< convertValue.convertIntString(setup_aux->getInfX1()) << "*p"<<")";
  				file_min << "&& (x1<=" <<  convertValue.convertIntString( setup_aux->getSupX1() ) << "*p) );\n";

  			file_min << "          __CPROVER_assume( (x2>="<< convertValue.convertIntString(setup_aux->getInfX2()) << "*p"<<")";
  				file_min << "&& (x2<=" <<  convertValue.convertIntString( setup_aux->getSupX1() ) << "*p) );\n";

  			file_min << "          __CPROVER_assume( X1 == (" << setup_aux->getTypeData() << ") " << "x1/p );\n";
  			file_min << "          __CPROVER_assume( X2 == (" << setup_aux->getTypeData() << ") " << "x2/p );\n";

  	  	}

  	    file_min <<  "    //-----------------------------------------------------------  \n\n";

  	    file_min << "    " + setup_aux->getInputFunction() + "\n";

  	// Determina se o ASSUME e ASSERT para ESBMC e CBMC
  	if(setup_aux->getBmc() == 1){
  	  	file_min << "    __ESBMC_assume(fobj < f_i );\n\n";
  	    file_min << "    " + setup_aux->getTypeData() + " delta = (f_i-f_c)/5;\n";
  	    file_min << "    if ((f_i-f_c) > 0.00001){\n";
  	    file_min << "      while (f_c <= f_i){\n";
  	    file_min << "        assert(fobj > f_c);\n";
  	    file_min << "        f_c += delta;\n";
  	    file_min << "      }\n";
  	    file_min << "    }\n\n";

  	}else if(setup_aux->getBmc() == 2){
  	  	file_min << "    __CPROVER_assume(fobj < f_i );\n\n";
  	    file_min << "    " + setup_aux->getTypeData() + " delta = (f_i-f_c)/5;\n";
  	    file_min << "    if ((f_i-f_c) > 0.00001){\n";
  	    file_min << "      while (f_c <= f_i){\n";
  	    file_min << "        __CPROVER_assert(fobj > f_c, \"\");\n";
  	    file_min << "        f_c += delta;\n";
  	    file_min << "      }\n";
  	    file_min << "    }\n\n";

  	}

  	file_min << "    return 0;\n";
  	file_min << "  }\n";
  	file_min.close();



}

void Generatefiles::create_specification_CEGIO_S_Equational(Setup* setup_aux){

	int i;

	string library_user="";

	if(setup_aux->getLibrary() != ""){
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
	}else{
		library_user = "\n\n";
	}

	string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
	ofstream file_min;
	file_min.open(name.c_str());

    	file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";

  		file_min << library_user;
  		file_min << "#include <math.h>\n";
  		file_min << "\n";
  		file_min << "    int nondet_int();\n";
  		file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
  		file_min << "\n";
  		file_min << "    int main() {\n";

  		file_min << "    \n";
		file_min << "    "+ setup_aux->getTypeData() +" f_i = " + convertValue.convertDoubleString(setup_aux->getFcCurrent()) + ";\n\n";
		file_min << "    "+ setup_aux->getTypeData() +" f_c = 0;\n";
		file_min << "    "+ setup_aux->getTypeData() +" fobj;";
  		file_min << "    \n";

  		file_min << "    int ";

		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "x" << i << ",";
		}
		file_min << "x" << (i) << ";\n";


  		file_min << "    " <<  setup_aux->getTypeData()  << " ";
		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "X" << i << ",";
		}
		file_min << "X" << (i) << ";\n\n";


		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "    x" << i << " = nondet_int();\n";
			file_min << "    X" << i << " = (" << setup_aux->getTypeData() << ") nondet_" << setup_aux->getTypeData() << "();\n";
		}
		file_min << "    x" << i << " = nondet_int();\n";
		file_min << "    X" << i << " = (" << setup_aux->getTypeData() << ") nondet_" << setup_aux->getTypeData() << "();\n";


  	  	file_min << "     \n     //-----------------------------------------------------------  ";
  	    file_min << "     \n     // Restrictions\n\n";

  	    file_min << setup_aux->getCodeRestrictionsModified();

  	    file_min <<  "    //-----------------------------------------------------------  \n\n";

  	    file_min << "    " + setup_aux->getInputFunction() + "\n";

  	// Determina se o ASSUME e ASSERT para ESBMC e CBMC
  	if(setup_aux->getBmc() == 1){
  	  	file_min << "    __ESBMC_assume(fobj < f_i );\n\n";
  	    file_min << "    " + setup_aux->getTypeData() + " delta = (f_i-f_c)/5;\n";
  	    file_min << "    if ((f_i-f_c) > 0.00001){\n";
  	    file_min << "      while (f_c <= f_i){\n";
  	    file_min << "        assert(fobj > f_c);\n";
  	    file_min << "        f_c += delta;\n";
  	    file_min << "      }\n";
  	    file_min << "    }\n\n";

  	}else if(setup_aux->getBmc() == 2){
  	  	file_min << "    __CPROVER_assume(fobj < f_i );\n\n";
  	    file_min << "    " + setup_aux->getTypeData() + " delta = (f_i-f_c)/5;\n";
  	    file_min << "    if ((f_i-f_c) > 0.00001){\n";
  	    file_min << "      while (f_c <= f_i){\n";
  	    file_min << "        __CPROVER_assert(fobj > f_c, \"\");\n";
  	    file_min << "        f_c += delta;\n";
  	    file_min << "      }\n";
  	    file_min << "    }\n\n";

  	}

  	file_min << "    return 0;\n";
  	file_min << "  }\n";
  	file_min.close();




}


void Generatefiles::create_specification_CEGIO_F(Setup* setup_aux){

	if(setup_aux->getInputFormat() == 0){

		if(setup_aux->getTypeLoop() == 0){
			create_specification_CEGIO_F_Matrix_sem_FOR(setup_aux);
		}else if(setup_aux->getTypeLoop() == 1){
			create_specification_CEGIO_F_Matrix_com_FOR(setup_aux);
		}

	}else if(setup_aux->getInputFormat() == 1){

		create_specification_CEGIO_F_Equational(setup_aux);

	}

}

void Generatefiles::create_specification_CEGIO_F_Matrix_com_FOR(Setup* setup_aux){

}



void Generatefiles::create_specification_CEGIO_F_Matrix_sem_FOR(Setup* setup_aux){

	cout << "create_specification_CEGIO_F_Matrix_sem_FOR" << endl;

	cout << "mudar espaco: " << setup_aux->getLimitSpaceConvex() << endl;

	int i;

	string library_user="";

	if(setup_aux->getLibrary() != ""){
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
	}else{
		library_user = "\n\n";
	}

	string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
	ofstream file_min;
	file_min.open(name.c_str());

    	file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";

  		file_min << library_user;
  		file_min << "#include <math.h>\n";
  		file_min << "\n";
  		file_min << "    int nondet_int();\n";
  		file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
  		file_min << "\n";
  		file_min << "    int main() {\n";

  		file_min << "    \n";
		file_min << "    "+ setup_aux->getTypeData() +" f_i = " + convertValue.convertDoubleString(setup_aux->getFcCurrent()) + ";\n\n";
  		file_min << "    "+ setup_aux->getTypeData() +" fobj;";
  		file_min << "    \n";

  		file_min << "    int ";

		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "x" << i << ",";
		}
		file_min << "x" << (i) << ";\n";


  		file_min << "    " <<  setup_aux->getTypeData()  << " ";
		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "X" << i << ",";
		}
		file_min << "X" << (i) << ";\n\n";


		for(i=1; i<setup_aux->getVar(); i++){
			file_min << "    x" << i << " = nondet_int();\n";
			file_min << "    X" << i << " = (" << setup_aux->getTypeData() << ") nondet_" << setup_aux->getTypeData() << "();\n";
		}
		file_min << "    x" << i << " = nondet_int();\n";
		file_min << "    X" << i << " = (" << setup_aux->getTypeData() << ") nondet_" << setup_aux->getTypeData() << "();\n";



  	  	file_min << "     \n     //-----------------------------------------------------------  ";
  	    file_min << "     \n     // Restrictions\n\n";

 	  //			string new_spaceS = "\n  int lim[4] = { " + convert.convertDoubleString((ex._x1*p-1)*10) + ", " + convert.convertDoubleString((ex._x1*p+1)*10) + ", " + convert.convertDoubleString((ex._x2*p-1)*10) + ", " + convert.convertDoubleString((ex._x2*p+1)*10) + " };";

  	   // string new_spaceS = "\n  int lim[4] = { " +       convertValue.convertDoubleString(  (experiment->x1_current * experiment->getPrecisionCurrent()-1) *10) + ", " +
  	  	//													convertValue.convertDoubleString(  (experiment->x1_current * experiment->getPrecisionCurrent()+1) *10) + ", " +
  	  		//												convertValue.convertDoubleString(  (experiment->x2_current * experiment->getPrecisionCurrent()-1) *10) + ", " +
  	  			//										convertValue.convertDoubleString(  (experiment->x2_current * experiment->getPrecisionCurrent()+1) *10) + " };";

//  	    cout << "AQUI" << endl;

  	    // Deve-se Podar o espaço
  	    if(setup_aux->getLimitSpaceConvex() == 0){
//  	  	    cout << "AQUI 1" << endl;
	    	if(setup_aux->getBmc() == 1){
//	  	  	    cout << "AQUI 2" << endl;
	  			file_min << "          __ESBMC_assume( (x1>="<< convertValue.convertIntString(setup_aux->getInfX1()) << "*p"<<")";
	  				file_min << "&& (x1<=" <<  convertValue.convertIntString( setup_aux->getSupX1() ) << "*p) );\n";

	  			file_min << "          __ESBMC_assume( (x2>="<< convertValue.convertIntString(setup_aux->getInfX2()) << "*p"<<")";
	  				file_min << "&& (x2<=" <<  convertValue.convertIntString( setup_aux->getSupX1() ) << "*p) );\n";

	  			file_min << "          __ESBMC_assume( X1 == (" << setup_aux->getTypeData() << ") " << "x1/p );\n";
	  			file_min << "          __ESBMC_assume( X2 == (" << setup_aux->getTypeData() << ") " << "x2/p );\n";

	  	  	}else if(setup_aux->getBmc() == 2){
	  			file_min << "          __CPROVER_assume( (x1>="<< convertValue.convertIntString(setup_aux->getInfX1()) << "*p"<<")";
	  				file_min << "&& (x1<=" <<  convertValue.convertIntString( setup_aux->getSupX1() ) << "*p) );\n";

	  			file_min << "          __CPROVER_assume( (x2>="<< convertValue.convertIntString(setup_aux->getInfX2()) << "*p"<<")";
	  				file_min << "&& (x2<=" <<  convertValue.convertIntString( setup_aux->getSupX1() ) << "*p) );\n";

	  			file_min << "          __CPROVER_assume( X1 == (" << setup_aux->getTypeData() << ") " << "x1/p );\n";
	  			file_min << "          __CPROVER_assume( X2 == (" << setup_aux->getTypeData() << ") " << "x2/p );\n";
	  	  	}

  	    }else if(setup_aux->getLimitSpaceConvex() == 1){
//  	  	    cout << "AQUI 3" << endl;
	    	if(setup_aux->getBmc() == 1){
//	  	  	    cout << "AQUI 4" << endl;
	    		file_min << "          __ESBMC_assume( (x1>=" << convertValue.convertIntString((setup_aux->getX1Current() * setup_aux->getPrecisionCurrent()-1)*10) <<")";
	  				                   file_min << "&& (x1<=" << convertValue.convertIntString((setup_aux->getX1Current() * setup_aux->getPrecisionCurrent()+1)*10) << ") );\n";

 	  			file_min << "          __ESBMC_assume( (x2>=" << convertValue.convertIntString((setup_aux->getX2Current() * setup_aux->getPrecisionCurrent()-1)*10) <<")";
                					   file_min << "&& (x2<=" << convertValue.convertIntString((setup_aux->getX2Current() * setup_aux->getPrecisionCurrent()+1)*10) << ") );\n";

                file_min << "          __ESBMC_assume( X1 == (" << setup_aux->getTypeData() << ") " << "x1/p );\n";
	  			file_min << "          __ESBMC_assume( X2 == (" << setup_aux->getTypeData() << ") " << "x2/p );\n";

	  	  	}else if(setup_aux->getBmc() == 2){
	  			file_min << "          __CPROVER_assume( (x1>=" << convertValue.convertIntString((setup_aux->getX1Current() * setup_aux->getPrecisionCurrent()-1) *10) <<")";
	  				                   file_min << "&& (x1<=" << convertValue.convertIntString((setup_aux->getX1Current() * setup_aux->getPrecisionCurrent()+1) *10) << " ) );\n";

 	  			file_min << "          __CPROVER_assume( (x2>=" << convertValue.convertIntString((setup_aux->getX2Current() * setup_aux->getPrecisionCurrent()-1) *10) <<")";
                					   file_min << "&& (x2<=" << convertValue.convertIntString((setup_aux->getX2Current() * setup_aux->getPrecisionCurrent()+1) *10) << " ) );\n";

	  			file_min << "          __CPROVER_assume( X1 == (" << setup_aux->getTypeData() << ") " << "x1/p );\n";
	  			file_min << "          __CPROVER_assume( X2 == (" << setup_aux->getTypeData() << ") " << "x2/p );\n";
	  	  	}

  	    }


  	    file_min <<  "    //-----------------------------------------------------------  \n\n";

  	    file_min << "    " + setup_aux->getInputFunction() + "\n";

  	// Determina se o ASSUME e ASSERT para ESBMC e CBMC
  	if(setup_aux->getBmc() == 1){
  	  	file_min << "    __ESBMC_assume(fobj < f_i );\n\n";
  	  	file_min << "    assert(fobj > f_i);\n";
  	}else if(setup_aux->getBmc() == 2){
  	  	file_min << "    __CPROVER_assume(fobj < f_i );\n\n";
  	  	file_min << "    __CPROVER_assert(fobj > f_i, \"\");\n";
  	}

  	file_min << "    return 0;\n";
  	file_min << "  }\n";
  	file_min.close();

}

void Generatefiles::create_specification_CEGIO_F_Equational(Setup* setup_aux){



}





















///////////////////////////


void Generatefiles::create_specification_ESBMC_G_Boolector(Setup* setup_aux)
{

	string library_user="";

	if(setup_aux->getLibrary() != "")
	{
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
	}
	else
	{
		library_user = "\n\n";
	}

	string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
	ofstream file_min;
	file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

  	file_min << library_user;
  	file_min << "#include <math.h>\n";
  	file_min << "\n";
  	file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
  	file_min << "\n";
  	file_min << "    int main() {\n";

  	file_min << "    \n";
  	file_min << "    "+ setup_aux->getTypeData() +" f_i = " + convertValue.convertDoubleString(setup_aux->getFcCurrent()) + ";\n\n";

  	file_min << "    int i,j;\n";
  	file_min << "    int x[3];\n";
  	file_min << "    "+ setup_aux->getTypeData() +" X[2];\n";
  	file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

  	file_min << "    for (i = 0; i<2; i++){\n";
  	file_min << "      x[i] = nondet_int();\n";
  	file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
  	file_min << "    }\n";

  	file_min << setup_aux->getRestrictions();


  	file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";

  	file_min << "    __ESBMC_assume(fobj < f_i );\n\n";

  	file_min << "    assert(fobj > f_i);\n";

  	file_min << "    return 0;\n";
  	file_min << "  }\n";
  	file_min.close();
}


void Generatefiles::create_specification_ESBMC_G_Z3(Setup* setup_aux)
{

	string library_user="";

	if(setup_aux->getLibrary() != "")
	{
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
	}
	else
	{
		library_user = "\n\n";
	}

	string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
	ofstream file_min;
	file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

  	file_min << library_user;
  	file_min << "#include <math.h>\n";
  	file_min << "\n";
  	file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
  	file_min << "\n";
  	file_min << "    int main() {\n";

  	file_min << "    \n";
  	file_min << "    "+ setup_aux->getTypeData() +" f_i = " + convertValue.convertDoubleString(setup_aux->getFcCurrent()) + ";\n\n";

  	file_min << "    int i,j;\n";
  	file_min << "    int x[3];\n";
  	file_min << "    "+ setup_aux->getTypeData() +" X[2];\n";
  	file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

  	file_min << "    for (i = 0; i<2; i++){\n";
  	file_min << "      x[i] = nondet_int();\n";
  	file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
  	file_min << "    }\n";

  	file_min << setup_aux->getRestrictions();


  	file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";

  	file_min << "    __ESBMC_assume(fobj < f_i );\n\n";

  	file_min << "    assert(fobj > f_i);\n";

  	file_min << "    return 0;\n";
  	file_min << "  }\n";
  	file_min.close();
}

void Generatefiles::create_specification_ESBMC_G_Mathsat(Setup* setup_aux)
{

	string library_user="";

	if(setup_aux->getLibrary() != "")
	{
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
	}
	else
	{
		library_user = "\n\n";
	}

	string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
	ofstream file_min;
	file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

  	file_min << library_user;
  	file_min << "#include <math.h>\n";
  	file_min << "\n";
  	file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
  	file_min << "\n";
  	file_min << "    int main() {\n";

  	file_min << "    \n";
  	file_min << "    "+ setup_aux->getTypeData() +" f_i = " + convertValue.convertDoubleString(setup_aux->getFcCurrent()) + ";\n\n";

  	file_min << "    int i,j;\n";
  	file_min << "    int x[3];\n";
  	file_min << "    "+ setup_aux->getTypeData() +" X[2];\n";
  	file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

  	file_min << "    for (i = 0; i<2; i++){\n";
  	file_min << "      x[i] = nondet_int();\n";
  	file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
  	file_min << "    }\n";

  	file_min << setup_aux->getRestrictions();


  	file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";

  	file_min << "    __ESBMC_assume(fobj < f_i );\n\n";

  	file_min << "    assert(fobj > f_i);\n";

  	file_min << "    return 0;\n";
  	file_min << "  }\n";
  	file_min.close();
}



void Generatefiles::create_specification_ESBMC_S_Boolector(Setup* setup_aux)
{

    string library_user="";

	if(setup_aux->getLibrary() != "")
    {
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
    }
    else
    {
      library_user = "\n\n";
    }

    string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
    ofstream file_min;
    file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

    file_min << library_user;
    file_min << "#include <math.h>\n";
    file_min << "\n";
    file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
    file_min << "\n";
    file_min << "    int main() {\n";

    file_min << "    \n";
    file_min << "    "+ setup_aux->getTypeData() +" f_c = 0;\n";
    file_min << "    "+ setup_aux->getTypeData() +" f_i = "<< setup_aux->fc_current_string << ";\n\n";

    file_min << "    int i,j;\n";
    file_min << "    int x[3];\n";
    file_min << "    "+ setup_aux->getTypeData() +" X[2];\n";
    file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

    file_min << "    for (i = 0; i<2; i++){\n";
    file_min << "      x[i] = nondet_int();\n";
    file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
    file_min << "    }\n";

    file_min << setup_aux->getRestrictions();

  	file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";
    file_min << "    __ESBMC_assume(fobj < f_i );\n\n";

    file_min << "    " + setup_aux->getTypeData() + " delta = (f_i-f_c)/5;\n";
    file_min << "    if ((f_i-f_c) > 0.00001){\n";
    file_min << "      while (f_c <= f_i){\n";
    file_min << "        assert(fobj > f_c);\n";
    file_min << "        f_c += delta;\n";
    file_min << "      }\n";
    file_min << "    }\n\n";

    file_min << "    return 0;\n";
    file_min << "  }\n";
    file_min.close();

}

void Generatefiles::create_specification_ESBMC_S_Z3(Setup* setup_aux)
{

    string library_user="";

	if(setup_aux->getLibrary() != "")
    {
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
    }
    else
    {
      library_user = "\n\n";
    }

    string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
    ofstream file_min;
    file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

    file_min << library_user;
    file_min << "#include <math.h>\n";
    file_min << "\n";
    file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
    file_min << "\n";
    file_min << "    int main() {\n";

    file_min << "    \n";
    file_min << "    "+ setup_aux->getTypeData() +" f_c = 0;\n";
    file_min << "    "+ setup_aux->getTypeData() +" f_i = "<< setup_aux->fc_current_string << ";\n\n";

    file_min << "    int i,j;\n";
    file_min << "    int x[3];\n";
    file_min << "    "+ setup_aux->getTypeData() +" X[2];\n";
    file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

    file_min << "    for (i = 0; i<2; i++){\n";
    file_min << "      x[i] = nondet_int();\n";
    file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
    file_min << "    }\n";

    file_min << setup_aux->getRestrictions();

  	file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";
    file_min << "    __ESBMC_assume(fobj < f_i );\n\n";

    file_min << "    " + setup_aux->getTypeData() + " delta = (f_i-f_c)/5;\n";
    file_min << "    if ((f_i-f_c) > 0.00001){\n";
    file_min << "      while (f_c <= f_i){\n";
    file_min << "        assert(fobj > f_c);\n";
    file_min << "        f_c += delta;\n";
    file_min << "      }\n";
    file_min << "    }\n\n";

    file_min << "    return 0;\n";
    file_min << "  }\n";
    file_min.close();

}

void Generatefiles::create_specification_ESBMC_S_Mathsat(Setup* setup_aux)
{

    string library_user="";

	if(setup_aux->getLibrary() != "")
    {
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
    }
    else
    {
      library_user = "\n\n";
    }

    string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
    ofstream file_min;
    file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

    file_min << library_user;
    file_min << "#include <math.h>\n";
    file_min << "\n";
    file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
    file_min << "\n";
    file_min << "    int main() {\n";

    file_min << "    \n";
    file_min << "    "+ setup_aux->getTypeData() +" f_c = 0;\n";
    file_min << "    "+ setup_aux->getTypeData() +" f_i = "<< setup_aux->fc_current_string << ";\n\n";

    file_min << "    int i,j;\n";
    file_min << "    int x[3];\n";
    file_min << "    "+ setup_aux->getTypeData() +" X[2];\n";
    file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

    file_min << "    for (i = 0; i<2; i++){\n";
    file_min << "      x[i] = nondet_int();\n";
    file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
    file_min << "    }\n";

    file_min << setup_aux->getRestrictions();

  	file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";
    file_min << "    __ESBMC_assume(fobj < f_i );\n\n";

    file_min << "    " + setup_aux->getTypeData() + " delta = (f_i-f_c)/5;\n";
    file_min << "    if ((f_i-f_c) > 0.00001){\n";
    file_min << "      while (f_c <= f_i){\n";
    file_min << "        assert(fobj > f_c);\n";
    file_min << "        f_c += delta;\n";
    file_min << "      }\n";
    file_min << "    }\n\n";

    file_min << "    return 0;\n";
    file_min << "  }\n";
    file_min.close();

}



void Generatefiles::create_specification_ESBMC_C_Boolector(Setup* setup_aux)
{

    string library_user="";

	if(setup_aux->getLibrary() != "")
    {
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
    }
    else
    {
      library_user = "\n\n";
    }

    string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
    ofstream file_min;
    file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

    file_min << library_user;
    file_min << "#include <math.h>\n";
    file_min << "\n";
    file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
    file_min << "\n";
    file_min << "    int main() {\n";

    file_min << "    \n";
    file_min << "    "+ setup_aux->getTypeData() +" f_i = "<< setup_aux->fc_current_string << ";\n\n";

    file_min << "    int i,j;\n";
    file_min << "    int x[3];\n";
    file_min << "    "+ setup_aux->getTypeData() +" X[2];\n";
    file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

    file_min << "    for (i = 0; i<2; i++){\n";
    file_min << "      x[i] = nondet_int();\n";
    file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
    file_min << "    }\n";

    file_min << setup_aux->getRestrictions();

  	file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";
    file_min << "    __ESBMC_assume(fobj < f_i );\n\n";
    file_min << "    assert(fobj > f_i);\n";

    file_min << "    return 0;\n";
    file_min << "  }\n";
    file_min.close();

}

void Generatefiles::create_specification_ESBMC_C_Z3(Setup* setup_aux)
{

    string library_user="";

	if(setup_aux->getLibrary() != "")
    {
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
    }
    else
    {
      library_user = "\n\n";
    }

    string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
    ofstream file_min;
    file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

    file_min << library_user;
    file_min << "#include <math.h>\n";
    file_min << "\n";
    file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
    file_min << "\n";
    file_min << "    int main() {\n";

    file_min << "    \n";
    file_min << "    "+ setup_aux->getTypeData() +" f_i = "<< setup_aux->fc_current_string << ";\n\n";

    file_min << "    int i,j;\n";
    file_min << "    int x[3];\n";
    file_min << "    "+ setup_aux->getTypeData() +" X[2];\n";
    file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

    file_min << "    for (i = 0; i<2; i++){\n";
    file_min << "      x[i] = nondet_int();\n";
    file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
    file_min << "    }\n";

    file_min << setup_aux->getRestrictions();

  	file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";
    file_min << "    __ESBMC_assume(fobj < f_i );\n\n";
    file_min << "    assert(fobj > f_i);\n";

    file_min << "    return 0;\n";
    file_min << "  }\n";
    file_min.close();

}

void Generatefiles::create_specification_ESBMC_C_Mathsat(Setup* setup_aux)
{

    string library_user="";

	if(setup_aux->getLibrary() != "")
    {
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
    }
    else
    {
      library_user = "\n\n";
    }

    string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
    ofstream file_min;
    file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

    file_min << library_user;
    file_min << "#include <math.h>\n";
    file_min << "\n";
    file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
    file_min << "\n";
    file_min << "    int main() {\n";

    file_min << "    \n";
    file_min << "    "+ setup_aux->getTypeData() +" f_i = "<< setup_aux->fc_current_string << ";\n\n";

    file_min << "    int i,j;\n";
    file_min << "    int x[3];\n";
    file_min << "    "+ setup_aux->getTypeData() +" X[2];\n";
    file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

    file_min << "    for (i = 0; i<2; i++){\n";
    file_min << "      x[i] = nondet_int();\n";
    file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
    file_min << "    }\n";

    file_min << setup_aux->getRestrictions();

  	file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";
    file_min << "    __ESBMC_assume(fobj < f_i );\n\n";
    file_min << "    assert(fobj > f_i);\n";

    file_min << "    return 0;\n";
    file_min << "  }\n";
    file_min.close();

}



void Generatefiles::create_specification_CBMC_G_MINISAT(Setup* setup_aux)
{

	string library_user="";

	if(setup_aux->getLibrary() != "")
	{
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
	}
	else
	{
		library_user = "\n\n";
	}

	string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
	ofstream file_min;
	file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

  	file_min << library_user;
  	file_min << "#include <math.h>\n";
  	file_min << "\n";
  	file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
  	file_min << "\n";
  	file_min << "    int main() {\n";

  	file_min << "    \n";
  	file_min << "    "+ setup_aux->getTypeData() +" f_i = " + convertValue.convertDoubleString(setup_aux->getFcCurrent()) + ";\n\n";

  	file_min << "    int i,j;\n";
  	file_min << "    int x[3];\n";
  	file_min << "    "+ setup_aux->getTypeData() +" X[2];\n";
  	file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

  	file_min << "    for (i = 0; i<2; i++){\n";
  	file_min << "      x[i] = nondet_int();\n";
  	file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
  	file_min << "    }\n";

  	file_min << setup_aux->getRestrictions();


  	file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";

    file_min << "    __CPROVER_assume(fobj < f_i );\n\n";

    file_min << "    __CPROVER_assert(fobj > f_i,\"\");\n";

  	file_min << "    return 0;\n";
  	file_min << "  }\n";
  	file_min.close();
}

void Generatefiles::create_specification_CBMC_S_MINISAT(Setup* setup_aux)
{

    string library_user="";

	if(setup_aux->getLibrary() != "")
    {
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
    }
    else
    {
      library_user = "\n\n";
    }

    string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
    ofstream file_min;
    file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

    file_min << library_user;
    file_min << "#include <math.h>\n";
    file_min << "\n";
    file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
    file_min << "\n";
    file_min << "    int main() {\n";

    file_min << "    \n";
    file_min << "    "+ setup_aux->getTypeData() +" f_c = 0;\n";
    file_min << "    "+ setup_aux->getTypeData() +" f_i = "<< setup_aux->fc_current_string << ";\n\n";

    file_min << "    int i,j;\n";
    file_min << "    int x[3];\n";
    file_min << "    "+ setup_aux->getTypeData() +" X[2];\n";
    file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

    file_min << "    for (i = 0; i<2; i++){\n";
    file_min << "      x[i] = nondet_int();\n";
    file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
    file_min << "    }\n";

    file_min << setup_aux->getRestrictions();

  	file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";
    file_min << "    __CPROVER_assume(fobj < f_i );\n\n";

    file_min << "    " + setup_aux->getTypeData() + " delta = (f_i-f_c)/5;\n";
    file_min << "    if ((f_i-f_c) > 0.00001){\n";
    file_min << "      while (f_c <= f_i){\n";
    file_min << "        __CPROVER_assert(fobj > f_c);\n";
    file_min << "        f_c += delta;\n";
    file_min << "      }\n";
    file_min << "    }\n\n";

    file_min << "    return 0;\n";
    file_min << "  }\n";
    file_min.close();

}

void Generatefiles::create_specification_CBMC_C_MINISAT(Setup* setup_aux)
{

    string library_user="";

	if(setup_aux->getLibrary() != "")
    {
		library_user = "\n#include \"" + setup_aux->getLibrary() + "\" \n";
    }
    else
    {
      library_user = "\n\n";
    }

    string name;
	name = "min_" + setup_aux->getNameFunction() + ".c";
    ofstream file_min;
    file_min.open(name.c_str());

    file_min << "#define p "+ convertValue.convertDoubleString(setup_aux->getPrecisionCurrent()) +"\n";
	file_min << "#define nv 2 \n";//+ convertValue.convertIntString(2) +"\n";
  	file_min << "#define nr 2 \n";//+ convertValue.convertIntString(2) +"\n";

    file_min << library_user;
    file_min << "#include <math.h>\n";
    file_min << "\n";
    file_min << "    int nondet_int();\n";
  	file_min << "    " + setup_aux->getTypeData() + " nondet_" + setup_aux->getTypeData()  + "();\n";
    file_min << "\n";
    file_min << "    int main() {\n";

    file_min << "    \n";
    file_min << "    "+ setup_aux->getTypeData() +" f_i = "<< setup_aux->fc_current_string << ";\n\n";

    file_min << "    int i,j;\n";
    file_min << "    int x[3];\n";
    file_min << "    "+ setup_aux->getTypeData() +" X[2];\n";
    file_min << "    "+ setup_aux->getTypeData() +" fobj;\n\n";

    file_min << "    for (i = 0; i<2; i++){\n";
    file_min << "      x[i] = nondet_int();\n";
    file_min << "      X[i] = nondet_"+ setup_aux->getTypeData() +"();\n";
    file_min << "    }\n";

    file_min << setup_aux->getRestrictions();

  	file_min << "    " + setup_aux->getCodeFunctionModified() + "\n";
    file_min << "    __CPROVER_assume(fobj < f_i );\n\n";
    file_min << "    __CPROVER_assert(fobj > f_i);\n";

    file_min << "    return 0;\n";
    file_min << "  }\n";
    file_min.close();

}


} /* namespace GENERATEFILES */
