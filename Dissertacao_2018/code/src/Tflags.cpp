/*
 * Tflags.cpp
 *
 *  Created on: 19/11/2018
 *      Author: higo
 */

#include "Tflags.h"

namespace TFLAGS {

Tflags::Tflags() {
	// TODO Auto-generated constructor stub
}

Tflags::~Tflags() {
	// TODO Auto-generated destructor stub
}

Setup setup_experiment_flags;

Setup* Tflags::Checks(int argc, char *argv[])
{

	ADJUST::Adjust auxConvert;

    int i;
    size_t found;
    string auxS;
    string name_funcion;
    string flag_command;
    string flag_value;
    int vet_flag[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


	// Caso tenha apenas 1 argumento, implica dizer não foi inserido a função
    if( argc == 1 )
    {
    	cout << " Insert an input file. Try 'optCE --help' for more information." << endl << endl;
 	    setup_experiment_flags.setFailure(1);
        return &setup_experiment_flags;

    }else if( argc == 2 ) // Verifica se o usuário deseja ver HELP, versão ou execução padrão.
    {
    	if(string(argv[1]) == "--help")
    	{
			setup_experiment_flags.setHv(true);
			print_help();
	        return &setup_experiment_flags;
    	}
    	else if(string(argv[1]) == "--version")
    	{
    		setup_experiment_flags.setHv(true);
    		print_version();
            return &setup_experiment_flags;
    	}
    	else
    	{
    		name_funcion = check_input_file_format(string(argv[1]));

    		if(name_funcion == "")
    		{
            	cout << "Nome do arquivo de entrada com problema"  << endl;
        		setup_experiment_flags.setFailure(1);
    	        return &setup_experiment_flags;
    		}
    		else
    		{
            	cout << "Formato Correto" << endl;
    			setup_experiment_flags.setNameFunction(name_funcion);
    			setup_experiment_flags.setBmc(1);
    			setup_experiment_flags.setSolver(3);
    			setup_experiment_flags.setAlg(1);
    			setup_experiment_flags.setTypeData("float");
    			setup_experiment_flags.setFcStart(create_value());
    			setup_experiment_flags.setLibrary("");
    			setup_experiment_flags.setPrecisionTest(3);
    			setup_experiment_flags.setHv(false);
        		setup_experiment_flags.setFailure(0);
    	        return &setup_experiment_flags;
    		}
    	}
    }
    else //Verificar todos os caminhos de execução
    {
    	name_funcion = check_input_file_format(string(argv[1]));
    	if(name_funcion == "")
    	{
        	cout << "Nome do arquivo de entrada com problema"  << endl;
    		setup_experiment_flags.setFailure(1);
	        return &setup_experiment_flags;
    	}

		setup_experiment_flags.setNameFunction(name_funcion);

    	for(i=2; i<argc; i++){

    		if(string(argv[i]) == "--esbmc" )
    		{
    			vet_flag[0]++;
    		}
    		else if(string(argv[i]) == "--cbmc" )
    		{
    			vet_flag[1]++;
    		}
    		else if(string(argv[i]) == "--cpachecker" )
    		{
    			vet_flag[2]++;
    		}
    		else if(string(argv[i]) == "--boolector" )
    		{
    			vet_flag[3]++;
    		}
    		else if(string(argv[i]) == "--z3" )
    		{
    			vet_flag[4]++;
    		}
    		else if(string(argv[i]) == "--mathsat" )
    		{
    			vet_flag[5]++;
    		}
    		else if(string(argv[i]) == "--minisat" )
    		{
    			vet_flag[6]++;
    		}
    		else if(string(argv[i]) == "--smtinterpol" )
    		{
    			vet_flag[7]++;
    		}
    		else if(string(argv[i]) == "--generalized" )
    		{
    			vet_flag[8]++;
    		}
			else if(string(argv[i]) == "--positive" )
			{
				vet_flag[9]++;
			}
			else if(string(argv[i]) == "--convex" )
			{
				vet_flag[10]++;
			}
			else if(string(argv[i]) == "--float" )
			{
				vet_flag[11]++;
			}
			else if(string(argv[i]) == "--double" )
			{
				vet_flag[12]++;
			}
			else if(string(argv[i]) == "--minmax" )
			{
				vet_flag[13]++;
			}
			else
			{
				auxS = string(argv[i]);
				found = auxS.find("=");

				if(found!=string::npos)  // There is "="
				{
					flag_command = auxS.substr(0, found);
					flag_value = auxS.substr(found+1, auxS.length());

					if(flag_command == "--start-value" )
					{
						vet_flag[14]++;
						if(check_if_number(flag_value))
						{
							setup_experiment_flags.setFcStart(flag_value);
						}
						else
						{
							cout << "Unknown value: " + string(argv[i]) << endl;
					          setup_experiment_flags.setFailure(true);

				//	          setup_experiment_flags_r = &setup_experiment_flags;
				//	      	  return setup_experiment_flags_r;
						}
					}
					else if(flag_command == "--parallelize" )
					{
						vet_flag[13]++;
						setup_experiment_flags.setCore(4); // No momento, sempre paraleliza com 4
					}
					else if(flag_command == "--library" )
					{
						vet_flag[15]++;
						setup_experiment_flags.setLibrary(flag_value);
					}
					else if(flag_command == "--timeout-global" )
					{
						vet_flag[16]++;

						if(check_if_number(flag_value))
						{
							setup_experiment_flags.setTimeoutGlobal(auxConvert.convertStringDouble(flag_value));
						}
						else
						{
							cout << "Unknown value: " + string(argv[i]) << endl;
					          setup_experiment_flags.setFailure(true);

			//		          setup_experiment_flags_r = &setup_experiment_flags;
			//		          return setup_experiment_flags_r;
						}
					}
					else if(flag_command == "--timeout-verification" )
					{
						vet_flag[17]++;

						if(check_if_number(flag_value))
						{
							setup_experiment_flags.setTimeoutGlobal(auxConvert.convertStringDouble(flag_value));
						}
						else
						{
							cout << "Unknown value: " + string(argv[i]) << endl;
					          setup_experiment_flags.setFailure(true);

			//		          setup_experiment_flags_r = &setup_experiment_flags;
			//		      	  return setup_experiment_flags_r;
						}
					}
					else if(flag_command == "--precision")
					{
						vet_flag[18]++;
						if(check_if_number(flag_value))
						{
							setup_experiment_flags.setPrecisionTest(auxConvert.convertStringInt(flag_value));
						}
						else
						{
							cout << "Unknown value: " + string(argv[i]) << endl;
					          setup_experiment_flags.setFailure(true);

		//			          setup_experiment_flags_r = &setup_experiment_flags;
		//			          return setup_experiment_flags_r;
						}
					}
					else
					{
						cout << "Flag unknown: " + string(argv[i]) << endl;
				          setup_experiment_flags.setFailure(true);

	//			          setup_experiment_flags_r = &setup_experiment_flags;
	//			          return setup_experiment_flags_r;
					}
				}
				else   // There is not =
				{
					cout << "Flag unknown: " + string(argv[i]) << endl;
			          setup_experiment_flags.setFailure(true);

	//		          setup_experiment_flags_r = &setup_experiment_flags;
//			          return setup_experiment_flags_r;
				}
			}
    	}



    	// Delete option when delimiting solver without delimiting MC
    	//************************************************
    	if(vet_flag[0]==0 && vet_flag[1]==0 && vet_flag[2]==0 && (vet_flag[3]>=1 || vet_flag[4]>=1 || vet_flag[5]>=1 || vet_flag[6]>=1 || vet_flag[7]>=1))
    	{
    		cout << "Vc nao pode escolher um solver sem escolher um MC" << endl;
            setup_experiment_flags.setFailure(true);

  //          setup_experiment_flags_r = &setup_experiment_flags;
 //           return setup_experiment_flags_r;
     	}

    	// Check the Model Check
    	//***************************************************
    	if(vet_flag[0]==0 && vet_flag[1]==0 && vet_flag[2]==0)
    	{
    		setup_experiment_flags.setBmc(1);
    	}
    	else if(vet_flag[0]>1 || vet_flag[1]>1 || vet_flag[2]>1)
    	{
    		cout << "Choose only one MC"<< endl;
            setup_experiment_flags.setFailure(true);

  //          setup_experiment_flags_r = &setup_experiment_flags;
 //          	return setup_experiment_flags_r;

    	}
    	else if(vet_flag[0]>vet_flag[1] && vet_flag[0]>vet_flag[2])
    	{
    		setup_experiment_flags.setBmc(1);
    	}
    	else if(vet_flag[1]>vet_flag[0] && vet_flag[1]>vet_flag[2])
    	{
    		setup_experiment_flags.setBmc(2);
    	}
    	else if(vet_flag[2]>vet_flag[0] && vet_flag[2]>vet_flag[1])
    	{
    		setup_experiment_flags.setBmc(3);
    	}

      // Check the Solver
      //***************************************************
      if( setup_experiment_flags.getBmc() == 1 )
      {
    	  if(vet_flag[3]==0 && vet_flag[4]==0 && vet_flag[5]==0)
    	  {
    		  setup_experiment_flags.setSolver(3);
    	  }
    	  else if(vet_flag[3]>1 || vet_flag[4]>1 || vet_flag[5]>1)
    	  {
    		  cout << "Choose only one SOLVER"<< endl;
    		  setup_experiment_flags.setFailure(true);

//    		  setup_experiment_flags_r = &setup_experiment_flags;
//    		  return setup_experiment_flags_r;
    	  }
    	  else if(vet_flag[3]>vet_flag[4] && vet_flag[3]>vet_flag[5])
    	  {
    		  setup_experiment_flags.setSolver(1);
    	  }
    	  else if(vet_flag[4]>vet_flag[3] && vet_flag[4]>vet_flag[5])
    	  {
    		  setup_experiment_flags.setSolver(2);
    	  }
    	  else if(vet_flag[5]>vet_flag[3] && vet_flag[5]>vet_flag[4])
    	  {
    		  setup_experiment_flags.setSolver(3);
    	  }
      }
      else if( setup_experiment_flags.getBmc() == 2 )
      {
    	  if(vet_flag[6]==0)
    	  {
    		  setup_experiment_flags.setSolver(4);
    	  }
    	  else if(vet_flag[6]>1)
    	  {
    		  cout << "Choose only one SOLVER"<< endl;
    		  setup_experiment_flags.setFailure(true);

  //  		  setup_experiment_flags_r = &setup_experiment_flags;
//	          return setup_experiment_flags_r;
    	  }
    	  else if(vet_flag[4]>0)
    	  {
    		  setup_experiment_flags.setSolver(4);
    	  }
      }
      else if( setup_experiment_flags.getBmc() == 3 )
      {
    	  setup_experiment_flags.setSolver(3);
      }


      // Verifica Algoritmo
      //************************************************
      if(vet_flag[8]==0 && vet_flag[9]==0 && vet_flag[10]==0)
      {
    	  setup_experiment_flags.setAlg(1);
      }
      else if(vet_flag[8]>1 || vet_flag[9]>1 || vet_flag[10]>1)
      {
    	  cout << "Choose only one Algorithm"<< endl;
          setup_experiment_flags.setFailure(true);

//		  setup_experiment_flags_r = &setup_experiment_flags;
 //         return setup_experiment_flags_r;
      }
      else if(vet_flag[8]>vet_flag[9] && vet_flag[8]>vet_flag[10])
      {
    	  setup_experiment_flags.setAlg(1);
      }
      else if(vet_flag[9]>vet_flag[8] && vet_flag[9]>vet_flag[10])
      {
    	  setup_experiment_flags.setAlg(2);
      }
      else if(vet_flag[10]>vet_flag[8] && vet_flag[10]>vet_flag[9])
      {
    	  setup_experiment_flags.setAlg(3);
      }


      // Verifica Tipo de Dados
      //************************************************
      if(vet_flag[11]==0 && vet_flag[12]==0) // Choosing the default Type
      {
    	  setup_experiment_flags.setTypeData("float");
      }
      else if(vet_flag[11]>1 || vet_flag[12]>1)
      {
    	  cout << "Choose only one Type of Data"<< endl;
          setup_experiment_flags.setFailure(true);

//		  setup_experiment_flags_r = &setup_experiment_flags;
//          return setup_experiment_flags_r;
      }
      else if(vet_flag[11]>vet_flag[12])
      {
    	  setup_experiment_flags.setTypeData("float");
      }
      else if(vet_flag[12]>vet_flag[11])
      {
    	  setup_experiment_flags.setTypeData("double");
      }


      // Verifica a modelagem da restrição
      //***************************************************
      if(vet_flag[13] == 0)
      {
//    	  setup_experiment_flags.setInputFormat(0);
      }
      else
      {
//    	  setup_experiment_flags.setInputFormat(0);
      }


      // Verifica a inicialização
      //***************************************************
      if(vet_flag[14] == 0)
      {
    	  setup_experiment_flags.setFcStart(create_value());
      }

      // Verifica se a biblioteca inserida existe
      //***************************************************
      if(vet_flag[15]>0)
      {
    	  if(!check_exist_file(setup_experiment_flags.getLibrary()))
    	  {
    		  cout << "Library not found -> " + setup_experiment_flags.getLibrary() << endl;
    		  setup_experiment_flags.setFailure(true);

//    		  setup_experiment_flags_r = &setup_experiment_flags;
//	          return setup_experiment_flags_r;
    	  }
      }

      if(vet_flag[18]==0)
      {
    	  setup_experiment_flags.setPrecisionTest(3);
      }
    }


//    setup_experiment_flags_r = &setup_experiment_flags;
	return &setup_experiment_flags;
}



void Tflags::print_help()
{

  ADJUST::Adjust aux;

  cout << endl;
  cout << "###################################################################################" << endl;
  cout << "               OptCE 1.0 - Copyright (C) 2017 (" +  aux.convertIntString(sizeof(void *)*8) + "-bit version)" << endl;
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
  cout << " optSMT <name_function>.func [--library=name_library]    Uses user function implementation                 " << endl;
  cout << " optSMT <name_function>.func [--precision=value]         Configure the precison of solution               " << endl;
  cout << " optSMT <name_function>.func [--timeout=time]            Configure time limit in seconds                 " << endl;
  cout << endl;
  cout << " Additonal options:" << endl;
  cout << endl;
  cout << " --- algorithm configuration ------------------------------------------------------" << endl;
  cout << endl;
  cout << " --generalized                   use generalized algorithm                         " << endl;
  cout << " --positive                      use positive algorithm                            " << endl;
  cout << " --convex                        use convex algorithm                              " << endl;
  cout << endl;
  cout << " --- model check configuration ----------------------------------------------------" << endl;
  cout << endl;
  cout << " --esbmc                         use ESBMC                                         " << endl;
  cout << " --cbmc                          use CBMC                                          " << endl;
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
  cout << " --float                         use float data type                               " << endl;
  cout << " --double                        use double data type                              " << endl;
  cout << endl;
}

void Tflags::print_version()
{
  cout << endl;
  cout << " optSMT version 1.0 64-bit x86_64 linux" << endl;
  cout << endl;
}


string Tflags::create_value()
{
	  ADJUST::Adjust auxConvert;

	  srand((unsigned)time(0));
	  float aux = rand()%100;
	  return auxConvert.convertDoubleString(aux);
}

bool Tflags::check_exist_file(string fileS)
{
  ifstream file;
  file.open(fileS.c_str());
  if(file.is_open( ))
  {
    file.clear();
    file.close();
    return true;
  }
  file.close();
  return false;
}

string Tflags::check_input_file_format(string name)
{
  size_t found = name.find(".");

  if(found!=string::npos)
  {
    string aux = name.substr(found, name.length());
    if(aux == ".func")
    {
      return name.substr(0, found);
    }
  }

  return "";
}

//
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


} /* namespace TFLAGS */
