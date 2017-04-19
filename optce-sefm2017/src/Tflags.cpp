/*
 * 	Tflags.cpp
 *
 *  Created on: 03/02/2017
 *  Author: Higo Albuquerque
 */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
using namespace std;

#include "Tflags.h"

	Tflags::Tflags() 
	{
		// TODO Auto-generated constructor stub
	}

	Tflags::~Tflags() 
	{
		// TODO Auto-generated destructor stub
	}

	/*******************************************************************************************************\
	Method: Checks(int argc, char *argv[])
	Inputs: argc: Nuber of flags
			argv[]: flags 
	Outputs: flase, if there are errors, true for OK	
	Purpose: Treats All input flags
	\*******************************************************************************************************/

	bool Tflags::Checks(int argc, char *argv[])
	{

		int i;
		size_t found;
		string auxS;
		string flag_command;
		string flag_value;
		int vet_flag[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

		if( argc == 1 ) // Check Help, Version and Standard Execution, 2 tickets
		{	
			cout << "Insert an input file." << endl;
			cout << "Try 'optCE --help' for more information." << endl;

			return false;
		}
							
		if( argc == 2 ) // Check Help, Version and Standard Execution, 2 tickets
		{	
							
			if(string(argv[1]) == "--help")
			{
			
				print_value();
				return false;
			
			} else if(string(argv[1]) == "--version")
			{

				print_version();
				return false;

			} else 
			{

				if(check_input_file_format(string(argv[1])) == false)
				{

					cout << "Incorrect file extension" << endl;
					return false;

				}else 
				{

					mc = 1;
					solver = 3;
					alg = 1;
					typeData = "float";
					l_sup = create_value();
					timeout_global = -1;
					timeout_verification = -1;
					library = "";
					input_formt = 0;

				}

			}
						
		}else // Check variations of executions, variations tickets
		{	 		
						
			if(check_input_file_format(string(argv[1])) == false)
			{
				cout << "Incorrect file extension" << endl;
				return false;
			}

			for(i=2;i<argc;i++){

				if(string(argv[i]) == "--esbmc" )
				{
					vet_flag[0]++;
				}else if(string(argv[i]) == "--cbmc" )
				{
					vet_flag[1]++;
				}else if(string(argv[i]) == "--cpachecker" )
				{
					vet_flag[2]++;
				}else if(string(argv[i]) == "--boolector" )
				{
					vet_flag[3]++;
				}else if(string(argv[i]) == "--z3" )
				{
					vet_flag[4]++;
				}else if(string(argv[i]) == "--mathsat" )
				{
					vet_flag[5]++;
				}else if(string(argv[i]) == "--minisat" )
				{
					vet_flag[6]++;
				}else if(string(argv[i]) == "--smtinterpol" )
				{
					vet_flag[7]++;
				}else if(string(argv[i]) == "--generalized" )
				{
					vet_flag[8]++;
				}else if(string(argv[i]) == "--positive" )
				{
					vet_flag[9]++;
				}else if(string(argv[i]) == "--convex" )
				{
					vet_flag[10]++;
				}else if(string(argv[i]) == "--float" )
				{
					vet_flag[11]++;
				}else if(string(argv[i]) == "--double" )
				{
					vet_flag[12]++;
				}else if(string(argv[i]) == "--minmax" )
				{
					vet_flag[13]++;
				}else
				{

					auxS = string(argv[i]);
					found = auxS.find("=");

					if(found!=string::npos)	// There is "="
					{ 

						flag_command = auxS.substr(0,found);
						flag_value = auxS.substr(found+1,auxS.length());

						if(flag_command == "--start-value" )
						{
							vet_flag[14]++;
							if(check_if_number(flag_value))
							{
								l_sup = flag_value;
							}else
							{
								cout << "Unknown value: " + string(argv[i]) << endl;
								return false;
							}

						}else if(flag_command == "--library" )
						{
							vet_flag[15]++;
							library = flag_value;

						}else if(flag_command == "--timeout-global" )
						{
							vet_flag[16]++;

							if(check_if_number(flag_value))
							{
								timeout_global = convertValue.convertStringDouble(flag_value);
							}else
							{
								cout << "Unknown value: " + string(argv[i]) << endl;
								return false;
							}

						}else if(flag_command == "--timeout-verification" )
						{
							vet_flag[17]++;

							if(check_if_number(flag_value))
							{
								timeout_verification = convertValue.convertStringDouble(flag_value);
							}else
							{
								cout << "Unknown value: " + string(argv[i]) << endl;
								return false;
							}

						}else if(flag_command == "--precision")
						{

							vet_flag[18]++;
							if(check_if_number(flag_value))
							{
								precision = convertValue.convertStringInt(flag_value);
							}else
							{
								cout << "Unknown value: " + string(argv[i]) << endl;
								return false;
							}

						}else
						{
							cout << "Flag unknown: " + string(argv[i]) << endl;
							return false;
						}

					}else 	// There is not =
					{	
						cout << "Flag unknown: " + string(argv[i]) << endl;
						return false;
					}

				}// End od ELSE to flags with sign "="

			} // End of FOR


			// Delete option when delimiting solver without delimiting MC
			//************************************************
			if(vet_flag[0]==0 && vet_flag[1]==0 && vet_flag[2]==0 && (vet_flag[3]>=1 || vet_flag[4]>=1 || vet_flag[5]>=1 || vet_flag[6]>=1 || vet_flag[7]>=1))
			{
				cout << "Vc nao pode escolher um solver sem escolher um MC" << endl;
				return false;
			}

			// Check the Model Check
			//***************************************************
			if(vet_flag[0]==0 && vet_flag[1]==0 && vet_flag[2]==0) // Choosing the default MC
			{	
				mc = 1;

			} else if(vet_flag[0]>1 || vet_flag[1]>1 || vet_flag[2]>1)
			{
				cout << "Choose only one MC"<< endl;
				return false;

			} else if(vet_flag[0]>vet_flag[1] && vet_flag[0]>vet_flag[2])
			{
				mc = 1;

			} else if(vet_flag[1]>vet_flag[0] && vet_flag[1]>vet_flag[2])
			{
				mc = 2;

			} else if(vet_flag[2]>vet_flag[0] && vet_flag[2]>vet_flag[1])
			{
				mc = 3;
			}

			// Check the Solver
			//***************************************************
			if( mc == 1 )
			{

				if(vet_flag[3]==0 && vet_flag[4]==0 && vet_flag[5]==0)
				{
					solver = 3;
				}else if(vet_flag[3]>1 || vet_flag[4]>1 || vet_flag[5]>1)
				{
					cout << "Choose only one SOLVER"<< endl;
					return false;
				}else if(vet_flag[3]>vet_flag[4] && vet_flag[3]>vet_flag[5])
				{
					solver = 1;//Boolector
				}else if(vet_flag[4]>vet_flag[3] && vet_flag[4]>vet_flag[5])
				{
					solver = 2;//Z3
				}else if(vet_flag[5]>vet_flag[3] && vet_flag[5]>vet_flag[4])
				{
					solver = 3;//Mathsat
				}

			}else if( mc == 2 )
			{

				if(vet_flag[6]==0)
				{
					solver = 4;//MiniSat
				}else if(vet_flag[6]>1)
				{
					cout << "Choose only one SOLVER"<< endl;
					return false;
				}else if(vet_flag[4]>0)
				{
					solver = 4;//MiniSat
				}

			}	else if( mc == 3 )
			{
				solver = 3;
			}


			// Verifica Algoritmo
			//************************************************
			if(vet_flag[8]==0 && vet_flag[9]==0 && vet_flag[10]==0) // Choosing the default ALG
			{	
				alg = 1;
			} else if(vet_flag[8]>1 || vet_flag[9]>1 || vet_flag[10]>1)
			{
				cout << "Choose only one Algorithm"<< endl;
				return false;
			} else if(vet_flag[8]>vet_flag[9] && vet_flag[8]>vet_flag[10])
			{
				alg = 1;
			} else if(vet_flag[9]>vet_flag[8] && vet_flag[9]>vet_flag[10])
			{
				alg = 2;
			} else if(vet_flag[10]>vet_flag[8] && vet_flag[10]>vet_flag[9])
			{
				alg = 3;
			}


			// Verifica Tipo de Dados
			//************************************************
			if(vet_flag[11]==0 && vet_flag[12]==0) // Choosing the default Type
			{	
				typeData = "float";
			} else if(vet_flag[11]>1 || vet_flag[12]>1)
			{
				cout << "Choose only one Type of Data"<< endl;
				return false;
			} else if(vet_flag[11]>vet_flag[12])
			{
				typeData = "float";
			} else if(vet_flag[12]>vet_flag[11])
			{
				typeData = "double";
			}


			// Verifica a modelagem da restrição
			//***************************************************
			if(vet_flag[13] == 0)
			{
				input_formt = 0;
			}else
			{
				input_formt = 1;
			}


			// Verifica a inicialização
			//***************************************************
			if(vet_flag[14] == 0)
			{
				l_sup = create_value();
			}

			// Verifica se a biblioteca inserida existe
			//***************************************************
			if(vet_flag[15]>0)
			{
				if(!check_exist_file(library))
				{
					cout << "Library not found -> " + library << endl;
					return false;
				}
			}

			if(vet_flag[18]==0)
			{
				precision = 3;
			}
		}

		return true;
	}


	/*******************************************************************************************************\
	Method: print_version()
	Inputs: void 
	Outputs: Void	
	Purpose: Prints the version of the tool
	\*******************************************************************************************************/

	void Tflags::print_version()
	{
		cout << endl;
		cout << " optSMT version 1.0 64-bit x86_64 linux" << endl;
		cout << endl;
	}


	/*******************************************************************************************************\
	Method: print_value()
	Inputs: Void
	Outputs: Void	
	Purpose: Prints the help screen of the tool
	\*******************************************************************************************************/

	void Tflags::print_value()
	{


//"* * Higo Albuquerque, Rodrigo Araujo, Iury Bessa, Lucas Cordeiro, and Eddie Batista * *\n"
//"* * Federal University of Amazonas, University of Oxford * *\n"


		cout << endl;
		cout << "###################################################################################" << endl;
		cout << "               OptCE 1.0 - Copyright (C) 2017 (" +  convertValue.convertIntString(sizeof(void *)*8) + "-bit version)" << endl;
		cout << "  -------------------------------------------------------------------------------  " << endl;
		cout << "  Higo Albuquerque, Rodrigo Araujo, Iury Bessa, Lucas Cordeiro, and Eddie Batista  " << endl;
		cout << "               Federal University of Amazonas, University of Oxford                " << endl;	
		cout << "###################################################################################" << endl;	


		cout << endl;
		cout << " Usage:                                                  Purpose:" << endl;
		cout << endl;
		cout << " optSMT [--help]                                         show help" << endl;
		cout << " optSMT [--version]                                      show version" << endl;
		cout << " optSMT <name_function>.func                             Minimum global check of the function with the default setting" << endl;
		cout << " optSMT <name_function>.func [--start-value=value]       Indicates the initialization of the algorithm                " << endl;
		cout << " optSMT <name_function>.func [--library=name_library]    Uses user function implementation							   " << endl;
		cout << " optSMT <name_function>.func [--precision=value]         Configure the precison of solution						   " << endl;
		cout << " optSMT <name_function>.func [--timeout=time]            Configure time limit in seconds							   " << endl;
		cout << endl;
		cout << " Additonal options:" << endl;
		cout << endl;
		cout << " --- algorithm configuration ------------------------------------------------------" << endl;
		cout << endl;
		cout << " --generalized                   use generalized algorithm 				        " << endl;
		cout << " --positive                      use positive algorithm							" << endl;
		cout << " --convex                        use convex algorithm                              " << endl;
		cout << endl;
		cout << " --- model check configuration ----------------------------------------------------" << endl;
		cout << endl;
		cout << " --esbmc                         use ESBMC 				                        " << endl;
		cout << " --cbmc                          use CBMC											" << endl;
		cout << " --cpachecker                    use CPAchecker                                    " << endl;
		cout << endl;
		cout << " --- solver configuration ---------------------------------------------------------" << endl;
		cout << endl;
		cout << " --boolector                     use Boolector (Only with ESBMC)                   " << endl;
		cout << " --z3                            use Z3 (Only with ESBMC)                          " << endl;
		cout << " --mathsat                       use MathSat (Only with ESBMC)                     " << endl;
		cout << " --minisat                       use MiniSAT (Only with CBMC)                      " << endl;
		cout << endl;
		cout << " --- data type --------------------------------------------------------------------" << endl;
		cout << endl;
		cout << " --float                         use float data type 				                " << endl;
		cout << " --double                        use double data type                              " << endl;
		cout << endl;
	}


	/*******************************************************************************************************\
	Method: create_value()
	Inputs: void
	Outputs: void	
	Purpose: Generates a random value less than 100
	\*******************************************************************************************************/

	string Tflags::create_value()
	{
		srand((unsigned)time(0));
		float aux = rand() % 100;
		return convertValue.convertDoubleString(aux);
	}


	/*******************************************************************************************************\
	Method: check_exist_file(string fileS)
	Inputs: fileS: Name of file
	Outputs: True for existing files, False for nonexistent files 	
	Purpose: Checks whether a file exists
	\*******************************************************************************************************/

	bool Tflags::check_exist_file(string fileS)
	{
		ifstream file;
		file.open(fileS.c_str());
		if(file.is_open( ))
		{
			file.clear( );
			file.close();
			return true;
		}
		file.close();
		return false;
	}

	
	/*******************************************************************************************************\
	Method: check_input_file_format(string name)
	Inputs: name: input file
	Outputs: True for existing format, False for format nonexistent 	
	Purpose: Check the file format
	\*******************************************************************************************************/

	bool Tflags::check_input_file_format(string name)
	{

		size_t found = name.find(".");

		if(found!=string::npos)
		{
			string aux = name.substr(found,name.length());

			if(aux == ".func")
			{
				name_function = name.substr(0,found);
				return true;
			}
		}

		return false;
	}


	/*******************************************************************************************************\
	Method: check_if_number(string value)
	Inputs: value: integer value 
	Outputs: True for integer value	
	Purpose: Check if the value is a real value
	\*******************************************************************************************************/

	bool Tflags::check_if_number(string value)
	{

	    bool valid = false;
	    string numero = "0123456789.";

	    if ((value[0] == '+' || value[0] == '-') && value.size() > 1)
	    {	
	    	value = value.substr(1);
	    }

	    if (count(value.begin(), value.end(), '.') <= 1 && value.find_first_not_of(numero) > value.size())
	    {	
	        valid = true;
	    }

	    if (value[0] == '.' && value.size() == 1)
	    {
	        valid = false;
	    }

	    return valid;
	}


	/*******************************************************************************************************\
	Method: get_*()
	Inputs: void 
	Outputs: Values of the variables	
	Purpose: Return values of variables of the optimization configuration
	\*******************************************************************************************************/

	string Tflags::get_name_function()
	{
		return name_function;
	}

	int Tflags::get_mc()
	{
		return mc;
	}

	int Tflags::get_solver()
	{
		return solver;
	}

	int Tflags::get_alg()
	{
		return alg;
	}

	float Tflags::get_l_inf()
	{
		return l_inf;
	}

	string Tflags::get_l_sup()
	{
		return l_sup;
	}

	string Tflags::get_typeData()
	{
		return typeData;
	}

	float Tflags::get_timeout_global()
	{
		return timeout_global;
	}

	float Tflags::get_timeout_verification()
	{
		return timeout_verification;
	}

	string Tflags::get_library()
	{
		return library;
	}

	int Tflags::get_input_formt()
	{
		return input_formt;
	}

	int Tflags::get_precision()
	{
		return precision;
	}
