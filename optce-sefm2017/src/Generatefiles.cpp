/*
 * 	Generatefiles.cpp
 *
 *  Created on: 03/02/2017
 *  Author: Higo Albuquerque
 */

#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "Generatefiles.h"
#include "Set.h"
#include "Adjust.h"

	Generate_files::Generate_files() 
	{

	}

	Generate_files::~Generate_files() 
	{

	}


	/*******************************************************************************************************\
	Method: create_f(string name_f, string code_f, string type)
	Inputs: name_f: Name of function 
			code_f: Description of the function of the input file
			type:   Data type
	Outputs: Void	
	Purpose: Function creates the <function>.c file to obtain the Fobj according to the parameters
	\*******************************************************************************************************/

	void Generate_files::create_f(string name_f, string code_f, string type)
	{

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


	/*******************************************************************************************************\
	Method: create_mi_ESBMC_G_Boolector(Set ex, int prec)
	Inputs: ex    Experiment configuration
			prec  precision in the file
	Outputs: Void	
	Purpose: Function creates the min_<function>.c file (ESBMC + BOOLECTOR + CEGIO-G)
	\*******************************************************************************************************/

	void Generate_files::create_mi_ESBMC_G_Boolector(Set ex, int prec)
	{

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != "")
		{
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else
		{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertValue.convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertValue.convertIntString(ex.nr) +"\n";

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
		file_min << "		int x[" + convertValue.convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertValue.convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertValue.convertIntString(ex.n) +  "; i++){\n";
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


	/*******************************************************************************************************\
	Method: create_mi_ESBMC_G_Z3(Set ex, int prec)
	Inputs: ex    Experiment configuration
			prec  precision in the file
	Outputs: Void	
	Purpose: Function creates the min_<function>.c file (ESBMC + Z3 + CEGIO-G)
	\*******************************************************************************************************/

	void Generate_files::create_mi_ESBMC_G_Z3(Set ex, int prec)
	{

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != "")
		{
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else
		{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertValue.convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertValue.convertIntString(ex.nr) +"\n";

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
		file_min << "		int x[" + convertValue.convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertValue.convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertValue.convertIntString(ex.n) +  "; i++){\n";
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


	/*******************************************************************************************************\
	Method: create_mi_ESBMC_G_Mathsat(Set ex, int prec)
	Inputs: ex    Experiment configuration
			prec  precision in the file
	Outputs: Void	
	Purpose: Function creates the min_<function>.c file (ESBMC + MATHSAT + CEGIO-G)
	\*******************************************************************************************************/

	void Generate_files::create_mi_ESBMC_G_Mathsat(Set ex, int prec)
	{

			ostringstream convert;
			string precS;
			convert << prec;
			precS = convert.str();

			string library_user="";

			if(ex.library != "")
			{
				library_user = "\n#include \"" + ex.library + "\" \n";
			}else
			{
				library_user = "\n\n";
			}

			string name;
			name = "min_" + ex.name_function + ".c";
			ofstream file_min;
			file_min.open(name.c_str());

			file_min << "#define p "+ precS +"\n";
			file_min << "#define nv "+ convertValue.convertIntString(ex.n) +"\n";
			file_min << "#define nr "+ convertValue.convertIntString(ex.nr) +"\n";

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
			file_min << "		int x[" + convertValue.convertIntString(ex.n+1) +  "];\n";
			file_min << "		"+ ex.typeData +" X[" + convertValue.convertIntString(ex.n) +  "];\n";
			file_min << "		"+ ex.typeData +" fobj;\n\n";

			file_min << "		for (i = 0; i<" + convertValue.convertIntString(ex.n) +  "; i++){\n";
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


	/*******************************************************************************************************\
	Method: create_mi_ESBMC_S_Boolector(Set ex, int prec)
	Inputs: ex    Experiment configuration
			prec  precision in the file
	Outputs: Void	
	Purpose: Function creates the min_<function>.c (ESBMC + BOOLECTOR + CEGIO-S)
	\*******************************************************************************************************/

	void Generate_files::create_mi_ESBMC_S_Boolector(Set ex, int prec)
	{

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != "")
		{
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else
		{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertValue.convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertValue.convertIntString(ex.nr) +"\n";

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
		file_min << "		int x[" + convertValue.convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertValue.convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertValue.convertIntString(ex.n) +  "; i++){\n";
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


	/*******************************************************************************************************\
	Method: create_mi_ESBMC_S_Z3(Set ex, int prec)
	Inputs: ex    Experiment configuration
			prec  precision in the file
	Outputs: Void	
	Purpose: Function creates the min_<function>.c (ESBMC + Z3 + CEGIO-S)
	\*******************************************************************************************************/

	void Generate_files::create_mi_ESBMC_S_Z3(Set ex, int prec)
	{

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != "")
		{
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else
		{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertValue.convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertValue.convertIntString(ex.nr) +"\n";

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
		file_min << "		int x[" + convertValue.convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertValue.convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertValue.convertIntString(ex.n) +  "; i++){\n";
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


	/*******************************************************************************************************\
	Method: create_mi_ESBMC_S_Mathsat(Set ex, int prec)
	Inputs: ex    Experiment configuration
			prec  precision in the file
	Outputs: Void	
	Purpose: Function creates the min_<function>.c (ESBMC + MATHSAT + CEGIO-S)
	\*******************************************************************************************************/

	void Generate_files::create_mi_ESBMC_S_Mathsat(Set ex, int prec)
	{

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != "")
		{
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else
		{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertValue.convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertValue.convertIntString(ex.nr) +"\n";

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
		file_min << "		int x[" + convertValue.convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertValue.convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertValue.convertIntString(ex.n) +  "; i++){\n";
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


	/*******************************************************************************************************\
	Method: create_mi_ESBMC_C_Boolector(Set ex, int prec)
	Inputs: ex    Experiment configuration
			prec  precision in the file
	Outputs: Void	
	Purpose: Function creates the min_<function>.c (ESBMC + BOOLECTOR + CEGIO-F)
	\*******************************************************************************************************/

	void Generate_files::create_mi_ESBMC_C_Boolector(Set ex, int prec)
	{

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != "")
		{
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else
		{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertValue.convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertValue.convertIntString(ex.nr) +"\n";

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
		file_min << "		int x[" + convertValue.convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertValue.convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertValue.convertIntString(ex.n) +  "; i++){\n";
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


	/*******************************************************************************************************\
	Method: create_mi_ESBMC_C_Z3(Set ex, int prec)
	Inputs: ex    Experiment configuration
			prec  precision in the file
	Outputs: Void	
	Purpose: Function creates the min_<function>.c (ESBMC + Z3 + CEGIO-F)
	\*******************************************************************************************************/

	void Generate_files::create_mi_ESBMC_C_Z3(Set ex, int prec)
	{

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != "")
		{
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else
		{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertValue.convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertValue.convertIntString(ex.nr) +"\n";

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
		file_min << "		int x[" + convertValue.convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertValue.convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertValue.convertIntString(ex.n) +  "; i++){\n";
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


	/*******************************************************************************************************\
	Method: create_mi_ESBMC_C_Mathsat(Set ex, int prec)
	Inputs: ex    Experiment configuration
			prec  precision in the file
	Outputs: Void	
	Purpose: Function creates the min_<function>.c (ESBMC + MATHSAT + CEGIO-F)
	\*******************************************************************************************************/

	void Generate_files::create_mi_ESBMC_C_Mathsat(Set ex, int prec)
	{

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != "")
		{
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else
		{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertValue.convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertValue.convertIntString(ex.nr) +"\n";

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
		file_min << "		int x[" + convertValue.convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertValue.convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertValue.convertIntString(ex.n) +  "; i++){\n";
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


	/*******************************************************************************************************\
	Method: create_mi_CBMC_G_Minisat(Set ex, int prec)
	Inputs: ex    Experiment configuration
			prec  precision in the file
	Outputs: Void	
	Purpose: Function creates the min_<function>.c (CBMC + MINISAT + CEGIO-G)
	\*******************************************************************************************************/

	void Generate_files::create_mi_CBMC_G_Minisat(Set ex, int prec)
	{

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != "")
		{
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else
		{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertValue.convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertValue.convertIntString(ex.nr) +"\n";

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
		file_min << "		int x[" + convertValue.convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertValue.convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertValue.convertIntString(ex.n) +  "; i++){\n";
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


	/*******************************************************************************************************\
	Method: create_mi_CBMC_S_Minisat(Set ex, int prec)
	Inputs: ex    Experiment configuration
			prec  precision in the file
	Outputs: Void	
	Purpose: Function creates the min_<function>.c (CBMC + MINISAT + CEGIO-S)
	\*******************************************************************************************************/

	void Generate_files::create_mi_CBMC_S_Minisat(Set ex, int prec)
	{

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != "")
		{
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else
		{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertValue.convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertValue.convertIntString(ex.nr) +"\n";

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
		file_min << "		int x[" + convertValue.convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertValue.convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertValue.convertIntString(ex.n) +  "; i++){\n";
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


	/*******************************************************************************************************\
	Method: create_mi_CBMC_C_Minisat(Set ex, int prec)
	Inputs: ex    Experiment configuration
			prec  precision in the file
	Outputs: Void	
	Purpose: Function creates the min_<function>.c (CBMC + MINISAT + CEGIO-F)
	\*******************************************************************************************************/

	void Generate_files::create_mi_CBMC_C_Minisat(Set ex, int prec)
	{

		ostringstream convert;
		string precS;
		convert << prec;
		precS = convert.str();

		string library_user="";

		if(ex.library != "")
		{
			library_user = "\n#include \"" + ex.library + "\" \n";
		}else
		{
			library_user = "\n\n";
		}

		string name;
		name = "min_" + ex.name_function + ".c";
		ofstream file_min;
		file_min.open(name.c_str());

		file_min << "#define p "+ precS +"\n";
		file_min << "#define nv "+ convertValue.convertIntString(ex.n) +"\n";
		file_min << "#define nr "+ convertValue.convertIntString(ex.nr) +"\n";

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
		file_min << "		int x[" + convertValue.convertIntString(ex.n+1) +  "];\n";
		file_min << "		"+ ex.typeData +" X[" + convertValue.convertIntString(ex.n) +  "];\n";
		file_min << "		"+ ex.typeData +" fobj;\n\n";

		file_min << "		for (i = 0; i<" + convertValue.convertIntString(ex.n) +  "; i++){\n";
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
