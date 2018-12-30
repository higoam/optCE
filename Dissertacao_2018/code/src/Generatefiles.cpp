/*
 * Generatefiles.cpp
 *
 *  Created on: 24/11/2018
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
  file << "    "+ setup_aux->getTypeData() +" fobj,x1,x2;\n";
  file << "    x1 = atof(argv[1]);\n";
  file << "    x2 = atof(argv[2]);\n";
  file << "\n\n";
  file << "    " + setup_aux->getCodeFunction() + "\n";
  file << "\n\n";
  file << "    printf(\"%f\", fobj);\n";
  file << "\n";
  file << "    return 0;\n";
  file << "  }\n";
  file.close();
}


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
  	file_min << "    "+ setup_aux->getTypeData() +" f_i = " + setup_aux->fc_current_string + ";\n\n";

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
  	file_min << "    "+ setup_aux->getTypeData() +" f_i = " + setup_aux->fc_current_string + ";\n\n";

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
  	file_min << "    "+ setup_aux->getTypeData() +" f_i = " + setup_aux->fc_current_string + ";\n\n";

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


} /* namespace GENERATEFILES */
