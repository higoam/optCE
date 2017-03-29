/*
 * Generatefiles.cpp
 *
 *  Created on: 03/02/2017
 *      Author: higo
 */

#include <fstream>
#include <sstream>
#include "Generatefiles.h"
#include <stdlib.h>
#include "Set.h"

	Generate_files::Generate_files() {
		// TODO Auto-generated constructor stub

	}

	Generate_files::~Generate_files() {
		// TODO Auto-generated destructor stub
	}




	//****************************************************************************************************************************
	//	Function creates the <function>.c file to obtain the Fobj according to the parameters

	void Generate_files::create_f(string name_f, string code_f, string type){

		string name;
		name = name_f + ".c";
		ofstream file;
		file.open(name.c_str());

		file << "\n";
		file << "    #include <stdio.h> \n";
		file << "    #include <stdlib.h> \n";
		file << "    #include \"math2.h\" \n";
		file << "\n";
		file << "	int main(int argc, char *argv[ ]) {\n";
		file << "\n";
		file << "		"+type+" fobj,x1,x2;\n";
		file << "		x1 = atof(argv[1]);\n";
		file << "		x2 = atof(argv[2]);\n";
		file << "\n\n";
		file << "		" + code_f + "\n";
		file << "\n\n";
		file << "		printf(\"%f\", fobj);\n";
		file << "\n";
		file << "		return 0;\n";
		file << "	}\n";
		file.close();

	}


	//****************************************************************************************************************************
	//	Function creates the min_<function>.c file (ESBMC + BOOLECTOR + GENERALIZED)

	void Generate_files::create_mi_ESBMC_G_Boolector(Set ex, int prec){

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != ""){
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertIntString(ex.nr) +"\n";

		file_min << library_user;
		file_min << "#include <math.h>\n";
		file_min << "\n";
		file_min << "    int nondet_int();\n";
		file_min << "    " + ex.typeData + " nondet_" + ex.typeData + "();\n";
		file_min << "\n";
		file_min << "    int main() {\n";

		file_min << "		\n";
		file_min << "		"+ ex.typeData +" f_i = "<< ex.fobj_current << ";\n\n";

		file_min << "		int i,j;\n";
		file_min << "		int x[" + convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertIntString(ex.n) +  "; i++){\n";
		file_min << "			x[i] = nondet_int();\n";
		file_min << "			X[i] = nondet_"+ ex.typeData +"();\n";
		file_min << "		}\n";


		file_min << ex.restrictions;


		file_min << "		" + ex.code_function_modified + "\n";

		file_min << "		__ESBMC_assume(fobj < f_i );\n\n";

		file_min << "		assert(fobj > f_i);\n";

		file_min << "		return 0;\n";
		file_min << "	}\n";
		file_min.close();


	}


	//****************************************************************************************************************************
	//	Function creates the min_<function>.c file (ESBMC + Z3 + GENERALIZED)

	void Generate_files::create_mi_ESBMC_G_Z3(Set ex, int prec){

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != ""){
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertIntString(ex.nr) +"\n";

		file_min << library_user;
		file_min << "#include <math.h>\n";
		file_min << "\n";
		file_min << "    int nondet_int();\n";
		file_min << "    " + ex.typeData + " nondet_" + ex.typeData + "();\n";
		file_min << "\n";
		file_min << "    int main() {\n";

		file_min << "		\n";
		file_min << "		"+ ex.typeData +" f_i = "<< ex.fobj_current << ";\n\n";

		file_min << "		int i,j;\n";
		file_min << "		int x[" + convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertIntString(ex.n) +  "; i++){\n";
		file_min << "			x[i] = nondet_int();\n";
		file_min << "			X[i] = nondet_"+ ex.typeData +"();\n";
		file_min << "		}\n";


		file_min << ex.restrictions;


		file_min << "		" + ex.code_function_modified + "\n";

		file_min << "		__ESBMC_assume(fobj < f_i );\n\n";

		file_min << "		assert(fobj > f_i);\n";

		file_min << "		return 0;\n";
		file_min << "	}\n";
		file_min.close();

	}


	//****************************************************************************************************************************
	//	Function creates the min_<function>.c file (ESBMC + MATHSAT + GENERALIZED)

	void Generate_files::create_mi_ESBMC_G_Mathsat(Set ex, int prec){

			ostringstream convert;
			string precS;
			convert << prec;
			precS = convert.str();

			string library_user="";

			if(ex.library != ""){
				library_user = "\n#include \"" + ex.library + "\" \n";
			}else{
				library_user = "\n\n";
			}

			string name;
			name = "min_" + ex.name_function + ".c";
			ofstream file_min;
			file_min.open(name.c_str());

			file_min << "#define p "+ precS +"\n";
			file_min << "#define nv "+ convertIntString(ex.n) +"\n";
			file_min << "#define nr "+ convertIntString(ex.nr) +"\n";

			file_min << library_user;
			file_min << "#include <math.h>\n";
			file_min << "\n";
			file_min << "    int nondet_int();\n";
			file_min << "    " + ex.typeData + " nondet_" + ex.typeData + "();\n";
			file_min << "\n";
			file_min << "    int main() {\n";

			file_min << "		\n";
			file_min << "		"+ ex.typeData +" f_i = "<< ex.fobj_current << ";\n\n";

			file_min << "		int i,j;\n";
			file_min << "		int x[" + convertIntString(ex.n+1) +  "];\n";
			file_min << "		"+ ex.typeData +" X[" + convertIntString(ex.n) +  "];\n";
			file_min << "		"+ ex.typeData +" fobj;\n\n";

			file_min << "		for (i = 0; i<" + convertIntString(ex.n) +  "; i++){\n";
			file_min << "			x[i] = nondet_int();\n";
			file_min << "			X[i] = nondet_"+ ex.typeData +"();\n";
			file_min << "		}\n";


			file_min << ex.restrictions;


			file_min << "		" + ex.code_function_modified + "\n";

			file_min << "		__ESBMC_assume(fobj < f_i );\n\n";

			file_min << "		assert(fobj > f_i);\n";

			file_min << "		return 0;\n";
			file_min << "	}\n";
			file_min.close();

	}


	//****************************************************************************************************************************
	//	Function creates the min_<function>.c (ESBMC + BOOLECTOR + SIMPLIFIED)

	void Generate_files::create_mi_ESBMC_S_Boolector(Set ex, int prec){

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != ""){
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertIntString(ex.nr) +"\n";

		file_min << library_user;
		file_min << "#include <math.h>\n";
		file_min << "\n";
		file_min << "    int nondet_int();\n";
		file_min << "    " + ex.typeData + " nondet_" + ex.typeData + "();\n";
		file_min << "\n";
		file_min << "    int main() {\n";

		file_min << "		\n";
		file_min << "		"+ ex.typeData +" f_c = 0;\n";
		file_min << "		"+ ex.typeData +" f_i = "<< ex.fobj_current << ";\n\n";

		file_min << "		int i,j;\n";
		file_min << "		int x[" + convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertIntString(ex.n) +  "; i++){\n";
		file_min << "			x[i] = nondet_int();\n";
		file_min << "			X[i] = nondet_"+ ex.typeData +"();\n";
		file_min << "		}\n";


		file_min << ex.restrictions;


		file_min << "		" + ex.code_function_modified + "\n";

		file_min << "		__ESBMC_assume(fobj < f_i );\n\n";

		file_min << "		" + ex.typeData + " delta = (f_i-f_c)/5;\n";
		file_min << "		if ((f_i-f_c) > 0.00001){\n";
		file_min << "			while (f_c <= f_i){\n";
		file_min << "				assert(fobj > f_c);\n";
		file_min << "				f_c += delta;\n";
		file_min << "			}\n";
		file_min << "		}\n\n";

		file_min << "		return 0;\n";
		file_min << "	}\n";
		file_min.close();

	}


	//****************************************************************************************************************************
	//	Função cria o arquivo min_<função>.c (ESBMC + Z3 + SIMPLIFIED)

	void Generate_files::create_mi_ESBMC_S_Z3(Set ex, int prec){

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != ""){
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertIntString(ex.nr) +"\n";

		file_min << library_user;
		file_min << "#include <math.h>\n";
		file_min << "\n";
		file_min << "    int nondet_int();\n";
		file_min << "    " + ex.typeData + " nondet_" + ex.typeData + "();\n";
		file_min << "\n";
		file_min << "    int main() {\n";

		file_min << "		\n";
		file_min << "		"+ ex.typeData +" f_c = 0;\n";
		file_min << "		"+ ex.typeData +" f_i = "<< ex.fobj_current << ";\n\n";

		file_min << "		int i,j;\n";
		file_min << "		int x[" + convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertIntString(ex.n) +  "; i++){\n";
		file_min << "			x[i] = nondet_int();\n";
		file_min << "			X[i] = nondet_"+ ex.typeData +"();\n";
		file_min << "		}\n";


		file_min << ex.restrictions;


		file_min << "		" + ex.code_function_modified + "\n";

		file_min << "		__ESBMC_assume(fobj < f_i );\n\n";

		file_min << "		" + ex.typeData + " delta = (f_i-f_c)/5;\n";
		file_min << "		if ((f_i-f_c) > 0.00001){\n";
		file_min << "			while (f_c <= f_i){\n";
		file_min << "				assert(fobj > f_c);\n";
		file_min << "				f_c += delta;\n";
		file_min << "			}\n";
		file_min << "		}\n\n";

		file_min << "		return 0;\n";
		file_min << "	}\n";
		file_min.close();

	}


	//****************************************************************************************************************************
	//	Função cria o arquivo min_<função>.c (ESBMC + MATHSAT + SIMPLIFIED)

	void Generate_files::create_mi_ESBMC_S_Mathsat(Set ex, int prec){

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != ""){
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertIntString(ex.nr) +"\n";

		file_min << library_user;
		file_min << "#include <math.h>\n";
		file_min << "\n";
		file_min << "    int nondet_int();\n";
		file_min << "    " + ex.typeData + " nondet_" + ex.typeData + "();\n";
		file_min << "\n";
		file_min << "    int main() {\n";

		file_min << "		\n";
		file_min << "		"+ ex.typeData +" f_c = 0;\n";
		file_min << "		"+ ex.typeData +" f_i = "<< ex.fobj_current << ";\n\n";

		file_min << "		int i,j;\n";
		file_min << "		int x[" + convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertIntString(ex.n) +  "; i++){\n";
		file_min << "			x[i] = nondet_int();\n";
		file_min << "			X[i] = nondet_"+ ex.typeData +"();\n";
		file_min << "		}\n";


		file_min << ex.restrictions;


		file_min << "		" + ex.code_function_modified + "\n";

		file_min << "		__ESBMC_assume(fobj < f_i );\n\n";

		file_min << "		" + ex.typeData + " delta = (f_i-f_c)/5;\n";
		file_min << "		if ((f_i-f_c) > 0.00001){\n";
		file_min << "			while (f_c <= f_i){\n";
		file_min << "				assert(fobj > f_c);\n";
		file_min << "				f_c += delta;\n";
		file_min << "			}\n";
		file_min << "		}\n\n";

		file_min << "		return 0;\n";
		file_min << "	}\n";
		file_min.close();

	}


	//****************************************************************************************************************************
	//	Função cria o arquivo min_<função>.c (ESBMC + BOOLECTOR + CONVEX)

	void Generate_files::create_mi_ESBMC_C_Boolector(Set ex, int prec){

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != ""){
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertIntString(ex.nr) +"\n";

		file_min << library_user;
		file_min << "#include <math.h>\n";
		file_min << "\n";
		file_min << "    int nondet_int();\n";
		file_min << "    " + ex.typeData + " nondet_" + ex.typeData + "();\n";
		file_min << "\n";
		file_min << "    int main() {\n";

		file_min << "		\n";
		file_min << "		"+ ex.typeData +" f_i = "<< ex.fobj_current << ";\n\n";

		file_min << "		int i,j;\n";
		file_min << "		int x[" + convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertIntString(ex.n) +  "; i++){\n";
		file_min << "			x[i] = nondet_int();\n";
		file_min << "			X[i] = nondet_"+ ex.typeData +"();\n";
		file_min << "		}\n";


		file_min << ex.restrictions;


		file_min << "		" + ex.code_function_modified + "\n";

		file_min << "		__ESBMC_assume(fobj < f_i );\n\n";

		file_min << "		assert(fobj > f_i);\n";

		file_min << "		return 0;\n";
		file_min << "	}\n";
		file_min.close();

	}


	//****************************************************************************************************************************
	//	Função cria o arquivo min_<função>.c (ESBMC + Z3 + CONVEX)

	void Generate_files::create_mi_ESBMC_C_Z3(Set ex, int prec){

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != ""){
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertIntString(ex.nr) +"\n";

		file_min << library_user;
		file_min << "#include <math.h>\n";
		file_min << "\n";
		file_min << "    int nondet_int();\n";
		file_min << "    " + ex.typeData + " nondet_" + ex.typeData + "();\n";
		file_min << "\n";
		file_min << "    int main() {\n";

		file_min << "		\n";
		file_min << "		"+ ex.typeData +" f_i = "<< ex.fobj_current << ";\n\n";

		file_min << "		int i,j;\n";
		file_min << "		int x[" + convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertIntString(ex.n) +  "; i++){\n";
		file_min << "			x[i] = nondet_int();\n";
		file_min << "			X[i] = nondet_"+ ex.typeData +"();\n";
		file_min << "		}\n";


		file_min << ex.restrictions;


		file_min << "		" + ex.code_function_modified + "\n";

		file_min << "		__ESBMC_assume(fobj < f_i );\n\n";

		file_min << "		assert(fobj > f_i);\n";

		file_min << "		return 0;\n";
		file_min << "	}\n";
		file_min.close();

	}


	//****************************************************************************************************************************
	//	Função cria o arquivo min_<função>.c (ESBMC + MATHSAT + CONVEX)

	void Generate_files::create_mi_ESBMC_C_Mathsat(Set ex, int prec){

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != ""){
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertIntString(ex.nr) +"\n";

		file_min << library_user;
		file_min << "#include <math.h>\n";
		file_min << "\n";
		file_min << "    int nondet_int();\n";
		file_min << "    " + ex.typeData + " nondet_" + ex.typeData + "();\n";
		file_min << "\n";
		file_min << "    int main() {\n";

		file_min << "		\n";
		file_min << "		"+ ex.typeData +" f_i = "<< ex.fobj_current << ";\n\n";

		file_min << "		int i,j;\n";
		file_min << "		int x[" + convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertIntString(ex.n) +  "; i++){\n";
		file_min << "			x[i] = nondet_int();\n";
		file_min << "			X[i] = nondet_"+ ex.typeData +"();\n";
		file_min << "		}\n";


		file_min << ex.restrictions;


		file_min << "		" + ex.code_function_modified + "\n";

		file_min << "		__ESBMC_assume(fobj < f_i );\n\n";

		file_min << "		assert(fobj > f_i);\n";

		file_min << "		return 0;\n";
		file_min << "	}\n";
		file_min.close();

	}

	//****************************************************************************************************************************

	void Generate_files::create_mi_CBMC_G_Minisat(Set ex, int prec){

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != ""){
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertIntString(ex.nr) +"\n";

		file_min << library_user;
		file_min << "#include <math.h>\n";
		file_min << "\n";
		file_min << "    int nondet_int();\n";
		file_min << "    " + ex.typeData + " nondet_" + ex.typeData + "();\n";
		file_min << "\n";
		file_min << "    int main() {\n";

		file_min << "		\n";
		file_min << "		"+ ex.typeData +" f_i = "<< ex.fobj_current << ";\n\n";

		file_min << "		int i,j;\n";
		file_min << "		int x[" + convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertIntString(ex.n) +  "; i++){\n";
		file_min << "			x[i] = nondet_int();\n";
		file_min << "			X[i] = nondet_"+ ex.typeData +"();\n";
		file_min << "		}\n";


		file_min << ex.restrictions;


		file_min << "		" + ex.code_function_modified + "\n";

		file_min << "		__CPROVER_assume(fobj < f_i );\n\n";

		file_min << "		//printf(\"###>%d\",fobj);\n";

		file_min << "		__CPROVER_assert(fobj > f_i,\"\");\n";

		file_min << "		return 0;\n";
		file_min << "	}\n";
		file_min.close();

	}

	//****************************************************************************************************************************

	void Generate_files::create_mi_CBMC_S_Minisat(Set ex, int prec){

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != ""){
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertIntString(ex.nr) +"\n";

		file_min << library_user;
		file_min << "#include <math.h>\n";
		file_min << "\n";
		file_min << "    int nondet_int();\n";
		file_min << "    " + ex.typeData + " nondet_" + ex.typeData + "();\n";
		file_min << "\n";
		file_min << "    int main() {\n";

		file_min << "		\n";
		file_min << "		"+ ex.typeData +" f_c = 0;\n";
		file_min << "		"+ ex.typeData +" f_i = "<< ex.fobj_current << ";\n\n";

		file_min << "		int i,j;\n";
		file_min << "		int x[" + convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertIntString(ex.n) +  "; i++){\n";
		file_min << "			x[i] = nondet_int();\n";
		file_min << "			X[i] = nondet_"+ ex.typeData +"();\n";
		file_min << "		}\n";


		file_min << ex.restrictions;


		file_min << "		" + ex.code_function_modified + "\n";

		file_min << "		__ESBMC_assume(fobj < f_i );\n\n";

		file_min << "		" + ex.typeData + " delta = (f_i-f_c)/5;\n";
		file_min << "		if ((f_i-f_c) > 0.00001){\n";
		file_min << "			while (f_c <= f_i){\n";
		file_min << "				assert(fobj > f_c);\n";
		file_min << "				f_c += delta;\n";
		file_min << "			}\n";
		file_min << "		}\n\n";

		file_min << "		return 0;\n";
		file_min << "	}\n";
		file_min.close();

//		file_min << "		" + space_limitP + "\n\n";

//		file_min << "		for (i = 0; i<2; i++){\n";
//		file_min << "			__CPROVER_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );\n";
//		file_min << "			__CPROVER_assume( X[i] == ("+type+") x[i]/p	);\n";
//		file_min << "		}\n\n";

	}

	//****************************************************************************************************************************

	void Generate_files::create_mi_CBMC_C_Minisat(Set ex, int prec){

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != ""){
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertIntString(ex.nr) +"\n";

		file_min << library_user;
		file_min << "#include <math.h>\n";
		file_min << "\n";
		file_min << "    int nondet_int();\n";
		file_min << "    " + ex.typeData + " nondet_" + ex.typeData + "();\n";
		file_min << "\n";
		file_min << "    int main() {\n";
		file_min << "		\n";
		file_min << "		"+ ex.typeData +" f_i = "<< ex.fobj_current << ";\n\n";

		file_min << "		int i,j;\n";
		file_min << "		int x[" + convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertIntString(ex.n) +  "; i++){\n";
		file_min << "			x[i] = nondet_int();\n";
		file_min << "			X[i] = nondet_"+ ex.typeData +"();\n";
		file_min << "		}\n";

		file_min << ex.restrictions;


		file_min << "		" + ex.code_function_modified + "\n";

		file_min << "		__ESBMC_assume(fobj < f_i );\n\n";

		file_min << "		assert(fobj > f_i);\n";

		file_min << "		return 0;\n";
		file_min << "	}\n";
		file_min.close();


	}


	//
	//	Função que carrega o arquivo original com a função e limites
	//	Gera a função no formato real e adaptado.
/*
	void Generate_files::take_function(string name){

		string name_original = name + ".func";
		string file_original_aux = "";
		string function_original_aux = "";
		string function_tratada_aux = "";
		string limits_original_aux = "";

		int i=0;
		int j=0;
		string vet_space[4];

		char letter;
		ifstream file_min;
		file_min.open(name_original.c_str());

		// Opens the original function file
		if(!file_min.is_open( )){
			cout<<"Could not open file with function!\n";
			file_min.clear( ); //reseta o objeto leitura, para limpar memória do sistema}
		}

		// Loads the file into string
		while (file_min.get(letter)) {
			file_original_aux = file_original_aux + letter;
		}

		// Divides the part of the function and the limits
		std::size_t found = file_original_aux.find("#");
		function_original_aux = file_original_aux.substr(0,found);
		limits_original_aux = file_original_aux.substr(found+2,file_original_aux.size());

		// Treats the function, x1 -> x [0], x2 -> x [1]
		while(i <= function_original_aux.size()){

			if(function_original_aux[i] == 'x'){
				if(function_original_aux[i+1] == '1'){
					function_tratada_aux = function_tratada_aux + "X[0]";
					i++;
				}else if(function_original_aux[i+1] == '2'){
					function_tratada_aux = function_tratada_aux + "X[1]";
					i++;
				}
			}else{
				function_tratada_aux = function_tratada_aux + function_original_aux[i];
			}
			i++;
		}
		code_function_original = function_original_aux.substr(0,function_original_aux.size()-1);
		code_function_treated = function_tratada_aux.substr(0,function_tratada_aux.size()-1);

		// Treats the boundaries
		string aux = "";
		i=0;
		j=0;
		//
		while(i<=limits_original_aux.size()){

			aux = aux + limits_original_aux[i];

			if(limits_original_aux[i] == '\n'){
				//cout << aux << endl;
				vet_space[j] = aux.substr(0,aux.size()-1);
				//cout << vet_space[j]<< endl;
				aux = "";
				j++;
			}

			i++;
		}
		space_limit = "int lim[4] = {"+ vet_space[0] +"*p, "+ vet_space[1] +"*p, "+ vet_space[2] +"*p, "+ vet_space[3] +"*p};";

	}
*/




	//////////////////////////////////////////////////////////////////
	///  Type conversion functions	/////////////////////////////////
	////////////////////////////////////////////////////////////////

	string Generate_files::convertDoubleString(double value){
		ostringstream convert;
		convert << value;
		return convert.str();
	}

	string Generate_files::convertIntString(int value){
		ostringstream convert;
		convert << value;
		return convert.str();
	}

