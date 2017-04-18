/*
 *  Tcexamples.cpp
 *
 *  Created on: 03/02/2017
 *  Author: higo
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <list>
using namespace std;

#include "Tcexamples.h"
#include "Adjust.h"




	Tcexamples::Tcexamples() 
	{
		_verification = 0;
	}

	Tcexamples::~Tcexamples() 
	{

	}


	/*******************************************************************\
	Method: take_file(string fileS)
	Inputs:  fileS: file 
	Outputs: string: string with file
	Purpose: Function Loads the Log file
	\*******************************************************************/

	string Tcexamples::take_file(string fileS)
	{

		char letter;
		ifstream file;

		file.open(fileS.c_str());
		if(!file.is_open( ))
		{
			cout<<"Could not open file with function!Q\n";
			file.clear( ); //Reset the read object to clear system memory
		}

		// Loads the file into string
		string file_result;
		
		while (file.get(letter)) 
		{
			file_result = file_result + letter;
		}

		file.close();

		return file_result;
	}


	/*******************************************************************\
	Method: take_CE_ESBMC_Boolector(string log, int prec)
	Inputs:  log: Log file name
			 prec: Precision current of algorithm 	
	Outputs: void
	Purpose: Treats the counterexample of the ESBMC Boolector, and obtains the decision variables and candidate functions
	\*******************************************************************/

	void Tcexamples::take_CE_ESBMC_Boolector(string log, int prec)
	{

		// Adjustment Variables
		string command = "";
		string file_log;
		string current_coordinates[2];
		string word = ":x=";
		ostringstream convert;
		string aux_string = "";
	 	size_t position;

		file_log = take_file(log);							// Load Log
		std::size_t found_F = file_log.find("FAILED");		// Search for the word FAILED in the counterexample
		std::size_t found_S = file_log.find("SUCCESSFUL");	// Search for the word SUCCESSFUL in the counterexample 

												
		if(found_F!=std::string::npos)			//	Enter if there is a failure in the counterexample
		{											
															
		 	_verification = 0;								// 	Assign 0 for variable that identifies the state of the counter example

			position = file_log.rfind(word);										//
																					//
			aux_string = file_log.substr(position + 5,file_log.length());			//
			position = aux_string.find(",");										//	Find values of X1 and X2 in the counter Example
			current_coordinates[0] = aux_string.substr(0,position);					//
																					//
			aux_string = aux_string.substr(position + 2,aux_string.length());		//
			position = aux_string.find(",");										//
			current_coordinates[1] = aux_string.substr(0,position);					//

																								
		    double _x1D = convertValue.convertStringDouble(current_coordinates[0].c_str());		//	Converts Values of X1 and X2 into string for Double
		    double _x2D = convertValue.convertStringDouble(current_coordinates[1].c_str());		//


		    if(_x1D > 1000)
		    {														//	For X1
				_x1D = ((_x1D -4294967296)/prec);					//
				_x1 = convertValue.convertDoubleString(_x1D);		//	Evaluates whether it is a BMG overflow and set the value
			}else													//	
			{														//  
				_x1 = convertValue.convertDoubleString(_x1D/prec);	//
			}														//

			if(_x2D > 1000)
			{														//  ForX2
				_x2D = ((_x2D -4294967296)/prec);					//
				_x2 = convertValue.convertDoubleString(_x2D);		//	Evaluates whether it is a BMG overflow and set the value
			}else													//
			{														//	
				_x2 = convertValue.convertDoubleString(_x2D/prec);	//
			}														//


			//Generates the minimum														//
			command  = "./value_min " + _x1 + " " + _x2 + " > min_temporary.txt";		//	Generates the Fobj value with x1 and x2 found
			system(command.c_str());													//	Stores in "min_temporary.txt"

			string minimumS = take_file("min_temporary.txt");					//	Load the generated Fojb
			_fjob = minimumS.substr(0,minimumS.size()).c_str();					//	Convert to float and assign

		}else if(found_S!=std::string::npos)
		{														// If the verification was successful
			_verification = 1;									// If you can not find the fault, "SUCCESS"
		}else 
		{
			cout << "COUNTEREXAMPLE UNKNOWN" << endl;
		}

	}


	/*******************************************************************\
	Method: take_CE_ESBMC_Z3(string log, int prec)
	Inputs:  log: Log file name
			 prec: Precision current of algorithm 	
	Outputs: void
	Purpose: Treats the counterexample of the ESBMC Z3, and obtains the decision variables and candidate functions
	\*******************************************************************/

	void Tcexamples::take_CE_ESBMC_Z3(string log, int prec)
	{

		// Adjustment Variables
		string command = "";
		string file_log;
		string current_coordinates[2];
		string word = ":x=";
		ostringstream convert;
		string aux_string = "";
	 	size_t position;

		file_log = take_file(log);							// Load Log
		std::size_t found_F = file_log.find("FAILED");		// Search for the word FAILED in the counterexample
		std::size_t found_S = file_log.find("SUCCESSFUL");	// Search for the word SUCCESSFUL in the counterexample

												
		if(found_F!=std::string::npos)			//	Enter if there is a failure in the counterexample
		{			
																											//
		 	_verification = 0;								// 	Assign 0 for variable that identifies the state of the counter example
															
			position = file_log.rfind(word);										//
																					//
			aux_string = file_log.substr(position + 5,file_log.length());			//
			position = aux_string.find(",");										//	Find values of X1 and X2 in the counter Example
			current_coordinates[0] = aux_string.substr(0,position);					//
																					//
			aux_string = aux_string.substr(position + 2,aux_string.length());		//
			position = aux_string.find(",");										//
			current_coordinates[1] = aux_string.substr(0,position);					//
																				
		    double _x1D = convertValue.convertStringDouble(current_coordinates[0].c_str());		//	Converts Values of X1 and X2 into string for Double
		    double _x2D = convertValue.convertStringDouble(current_coordinates[1].c_str());		//

		    if(_x1D > 1000)					
		    {																//	For X1
				_x1D = ((_x1D -4294967296)/prec);							//
				_x1 = convertValue.convertDoubleString(_x1D);				//	Evaluates whether it is a BMG overflow and set the value
			}else															//
			{																//  
				_x1 = convertValue.convertDoubleString(_x1D/prec);			//
			}																//

			if(_x2D > 1000)
			{																// For X2
				_x2D = ((_x2D -4294967296)/prec);							//
				_x2 = convertValue.convertDoubleString(_x2D);				//	Evaluates whether it is a BMG overflow and set the value
			}else															//		
			{																//	
				_x2 = convertValue.convertDoubleString(_x2D/prec);			//
			}																//

			//Generates the minimum														//
			command  = "./value_min " + _x1 + " " + _x2 + " > min_temporary.txt";		//	Generates the Fobj value with x1 and x2 found
			system(command.c_str());													//	Stores in "min_temporary.txt"

			string minimumS = take_file("min_temporary.txt");					//	Load the generated Fojb
			_fjob = minimumS.substr(0,minimumS.size()).c_str();					//	Convert to float and assign

		}else if(found_S!=std::string::npos)
		{														//
																// If the verification was successful
			_verification = 1;									// If you can not find the fault, "SUCCESS"

		}else 
		{
			cout << "COUNTEREXAMPLE UNKNOWN" << endl;
		}

	}


	/*******************************************************************\
	Method: take_CE_ESBMC_Mathsat(string log, int prec)
	Inputs:  log: Log file name
			 prec: Precision current of algorithm 	
	Outputs: void
	Purpose: Treats the counterexample of the ESBMC Mathsat, and obtains the decision variables and candidate functions
	\*******************************************************************/

	void Tcexamples::take_CE_ESBMC_Mathsat(string log, int prec){

		// Adjustment Variables
		string command = "";
		string file_log;
		string current_coordinates[2];
		string word = ":x=";
		ostringstream convert;
		string aux_string = "";
	 	size_t position;

		file_log = take_file(log);							// Load Log
		std::size_t found_F = file_log.find("FAILED");		// Search for the word FAILED in the counterexample
		std::size_t found_S = file_log.find("SUCCESSFUL");	// Search for the word SUCCESSFUL in the counterexample

		if(found_F!=std::string::npos)						//	Enter if there is a failure in the counterexample
		{

		 	_verification = 0;								// 	Assign 0 for variable that identifies the state of the counter example

			position = file_log.rfind(word);										//
																					//
			aux_string = file_log.substr(position + 5,file_log.length());			//
			position = aux_string.find(",");										//	Find values of X1 and X2 in the counter Example
			current_coordinates[0] = aux_string.substr(0,position);					//
																					//
			aux_string = aux_string.substr(position + 2,aux_string.length());		//
			position = aux_string.find(",");										//
			current_coordinates[1] = aux_string.substr(0,position);					//


		    double _x1D = convertValue.convertStringDouble(current_coordinates[0].c_str());		//	Converts Values of X1 and X2 into string for Double
		    double _x2D = convertValue.convertStringDouble(current_coordinates[1].c_str());		//


		    if(_x1D > 1000)
		    {														//	For X1
				_x1D = ((_x1D -4294967296)/prec);					//
				_x1 = convertValue.convertDoubleString(_x1D);		//	Evaluates whether it is a BMG overflow and set the value
			}else													//		
			{														// 
				_x1 = convertValue.convertDoubleString(_x1D/prec);	//
			}														//

			if(_x2D > 1000)
			{														//  For X2
				_x2D = ((_x2D -4294967296)/prec);					//
				_x2 = convertValue.convertDoubleString(_x2D);		//	Evaluates whether it is a BMG overflow and set the value
			}else													//
			{														//	
				_x2 = convertValue.convertDoubleString(_x2D/prec);	//
			}														//

			//Generates the minimum														//
			command  = "./value_min " + _x1 + " " + _x2 + " > min_temporary.txt";		//	Generates the Fobj value with x1 and x2 found
			system(command.c_str());													//	Stores in "min_temporary.txt"


			string minimumS = take_file("min_temporary.txt");					//	Load the generated Fojb
			_fjob = minimumS.substr(0,minimumS.size()).c_str();					//	Convert to float and assign

		}else if(found_S!=std::string::npos)
		{					//
																// If the verification was successful
			_verification = 1;									// If you can not find the fault, "SUCCESS"
		}else 
		{
			cout << "COUNTEREXAMPLE UNKNOWN" << endl;
		}
	}


	/*******************************************************************\
	Method: take_CE_CBMC_Minisat(string log, int prec)
	Inputs:  log: Log file name
			 prec: Precision current of algorithm 	
	Outputs: void
	Purpose: Treats the counterexample of the CBMC Minisat, and obtains the decision variables and candidate functions
	\*******************************************************************/

	void Tcexamples::take_CE_CBMC_Minisat(string log, int prec)
	{

			// Adjustment Variables
			string command = "";
			string file_log;
			string current_coordinates[2];

			string word1 = "X[0l]=";
			string word2 = "X[1l]=";
			string wordf = "fobj=";
		 	size_t position1;
		 	size_t position2;
		 	size_t positionf;
		 	size_t parenthesis;

			ostringstream convert;
			string aux_string = "";

			file_log = take_file(log);							// Load Log
			std::size_t found_F = file_log.find("FAILED");		// Search for the word FAILED in the counterexample
			std::size_t found_S = file_log.find("SUCCESSFUL");	// Search for the word SUCCESSFUL in the counterexample

													
			if(found_F!=std::string::npos)			
			{													//	Enter if there is a failure in the counterexample
													
			 	_verification = 0;								// 	Assign 0 for variable that identifies the state of the counter example

				position1 = file_log.rfind(word1);
				position2 = file_log.rfind(word2);
				positionf = file_log.rfind(wordf);

				aux_string = file_log.substr(position1+6,file_log.length());
				parenthesis = aux_string.find(" ");
				_x1 = aux_string.substr(0,parenthesis);

				aux_string = file_log.substr(position2+6,file_log.length());
				parenthesis = aux_string.find(" ");
				_x2 = aux_string.substr(0,parenthesis);

				aux_string = file_log.substr(positionf+5,file_log.length());
				parenthesis = aux_string.find(" ");
				_fjob = aux_string.substr(0,parenthesis);


			}else if(found_S!=std::string::npos)
			{					
																	// If the verification was successful
				_verification = 1;									// If you can not find the fault, "SUCCESS"
			}else 
			{
				cout << "COUNTEREXAMPLE UNKNOWN" << endl;
			}
		}
