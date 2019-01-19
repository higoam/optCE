/*
 * Tcexamples.cpp
 *
 *  Created on: 24/11/2018
 *      Author: higo
 */

#include "Tcexamples.h"

namespace TCEXAMPLES {

Tcexamples::Tcexamples() {
	// TODO Auto-generated constructor stub

}

Tcexamples::~Tcexamples() {
	// TODO Auto-generated destructor stub
}

string Tcexamples::take_file(string fileS)
{
	char letter;
	ifstream file;

	file.open(fileS.c_str());
	if(!file.is_open())
	{
		cout<<"Could not open file with function!Q\n";
		file.clear();
	}

	// Loads the file into string
	string file_result;

	while(file.get(letter))
	{
		file_result = file_result + letter;
	}

	file.close();

	return file_result;
}



void Tcexamples::take_CE_ESBMC_Boolector(string name_file_log, Setup* setup_aux)
{

	// Adjustment Variables
	string command = "";
	string file_log;
	string current_coordinates[2];
	string word = ":x=";
	ostringstream convert;
	string aux_string = "";
	size_t position;
	int prec = setup_aux->getPrecisionCurrent();

	file_log = take_file(name_file_log);
	std::size_t found_F = file_log.find("FAILED");
	std::size_t found_S = file_log.find("SUCCESSFUL");

	if(found_F!=std::string::npos)
	{
		setup_aux->setStatusCe(0);

		position = file_log.rfind(word);

		aux_string = file_log.substr(position + 5, file_log.length());
		position = aux_string.find(",");
		current_coordinates[0] = aux_string.substr(0, position);

		aux_string = aux_string.substr(position + 2, aux_string.length());
		position = aux_string.find(",");
		current_coordinates[1] = aux_string.substr(0, position);

		double _x1D,_x2D;

		_x1D = convertValue.convertStringDouble(current_coordinates[0].c_str());
		_x2D = convertValue.convertStringDouble(current_coordinates[1].c_str());

//		cout << endl;
//		cout << "X1=";
//		cout << _x1D  << endl;
//		cout << "X2=";
//		cout << _x2D  << endl;
//		cout << prec  << endl;


		if(_x1D > 1000)
		{
	        _x1D = ((_x1D -4294967295)/prec);
			setup_aux->setX1Current( _x1D );
		}
		else
		{
			setup_aux->setX1Current(_x1D/prec);
		}

		if(_x2D > 1000)
		{
	        _x2D = ((_x2D -4294967295)/prec);
			setup_aux->setX2Current( _x2D );
		}
		else
		{
			setup_aux->setX2Current(_x2D/prec);
		}

//		cout << endl;
//		cout << "X1=";
//		cout << _x1D  << endl;
//		cout << "X2=";
//		cout << _x2D  << endl;
//		cout << prec  << endl;

		command  = "./value_min " + convertValue.convertDoubleString( setup_aux->getX1Current() ) + " " + convertValue.convertDoubleString( setup_aux->getX2Current() ) + " > min_temporary.txt";
		system(command.c_str());

//		cout << endl;
//		system("cat min_temporary.txt");
//		cout << endl;

		string minimumS = take_file("min_temporary.txt");
		setup_aux->setFcFc( convertValue.convertStringDouble(minimumS.substr(0, minimumS.size()).c_str()) );

//		cout << endl;
//		cout << setup_aux->getFcFc()<< endl;
//		cout << endl;

	}
	else if(found_S!=std::string::npos)
	{
		setup_aux->setStatusCe(1);
	}
	else
	{
		setup_aux->setStatusCe(2);
	}
}

void Tcexamples::take_CE_ESBMC_Z3(string name_file_log, Setup* setup_aux)
{
    // Adjustment Variables
    string command = "";
    string file_log;
    string current_coordinates[2];
    string word = ":x=";
    ostringstream convert;
    string aux_string = "";
    size_t position;
 	int prec = setup_aux->getPrecisionCurrent();

    file_log = take_file(name_file_log);
    std::size_t found_F = file_log.find("FAILED");
    std::size_t found_S = file_log.find("SUCCESSFUL");

    //  Enter if there is a failure in the counterexample
    if(found_F!=std::string::npos)
    {
      setup_aux->setStatusCe(0);

      position = file_log.rfind(word);

      aux_string = file_log.substr(position + 5, file_log.length());
      position = aux_string.find(",");
      current_coordinates[0] = aux_string.substr(0, position);

      aux_string = aux_string.substr(position + 2, aux_string.length());
      position = aux_string.find(",");
      current_coordinates[1] = aux_string.substr(0, position);

      double _x1D = convertValue.convertStringDouble(current_coordinates[0].c_str());
      double _x2D = convertValue.convertStringDouble(current_coordinates[1].c_str());

      if(_x1D > 1000)
      {
        _x1D = ((_x1D -4294967296)/prec);
        setup_aux->setX1Current( _x1D );
      }
      else
      {
    	  setup_aux->setX1Current(_x1D/prec);
      }

      if(_x2D > 1000)
      {
        _x2D = ((_x2D -4294967296)/prec);
        setup_aux->setX2Current( _x2D );
      }
      else
      {
    	  setup_aux->setX2Current(_x2D/prec);
      }

      command  = "./value_min " + convertValue.convertDoubleString( _x1D ) + " " + convertValue.convertDoubleString( _x2D ) + " > min_temporary.txt";
      system(command.c_str());

      string minimumS = take_file("min_temporary.txt");
	  setup_aux->setFcFc( convertValue.convertStringDouble(minimumS.substr(0, minimumS.size()).c_str()) );
    }
    else if(found_S!=std::string::npos)
    {
      setup_aux->setStatusCe(1);
    }
    else
    {
    	setup_aux->setStatusCe(2);
    }

}

void Tcexamples::take_CE_ESBMC_Mathsat(string name_file_log, Setup* setup_aux)
{
    // Adjustment Variables
    string command = "";
    string file_log;
    string current_coordinates[2];
    string word = ":x=";
    ostringstream convert;
    string aux_string = "";
    size_t position;
	int prec = setup_aux->getPrecisionCurrent();

	file_log = take_file(name_file_log);
    std::size_t found_F = file_log.find("FAILED");
    std::size_t found_S = file_log.find("SUCCESSFUL");

    if(found_F!=std::string::npos)
    {
      setup_aux->setStatusCe(0);

      position = file_log.rfind(word);

      aux_string = file_log.substr(position + 5, file_log.length());
      position = aux_string.find(",");
      current_coordinates[0] = aux_string.substr(0, position);

      aux_string = aux_string.substr(position + 2, aux_string.length());
      position = aux_string.find(",");
      current_coordinates[1] = aux_string.substr(0, position);

      double _x1D = convertValue.convertStringDouble(current_coordinates[0].c_str());
      double _x2D = convertValue.convertStringDouble(current_coordinates[1].c_str());

      if(_x1D > 1000)
      {
        _x1D = ((_x1D -4294967296)/prec);
		setup_aux->setX1Current( _x1D );
      }
      else
      {
			setup_aux->setX1Current(_x1D/prec);
      }

      if(_x2D > 1000)
      {
        _x2D = ((_x2D -4294967296)/prec);
		setup_aux->setX2Current( _x2D );
      }
      else
      {
			setup_aux->setX2Current(_x2D/prec);
      }

 	  command  = "./value_min " + convertValue.convertDoubleString( _x1D ) + " " + convertValue.convertDoubleString( _x2D ) + " > min_temporary.txt";
      system(command.c_str());

      string minimumS = take_file("min_temporary.txt");
      setup_aux->setFcFc( convertValue.convertStringDouble(minimumS.substr(0, minimumS.size()).c_str()) );
    }
    else if(found_S!=std::string::npos)
    {
		setup_aux->setStatusCe(1);
    }
    else
    {
		setup_aux->setStatusCe(2);
    }
}


void Tcexamples::take_CE_CBMC_MINISAT(string name_file_log, Setup* setup_aux)
{

	// Adjustment Variables
//	string command = "";
	string file_log;
//	string current_coordinates[2];
//	string word = ":x=";
//	ostringstream convert;
	string aux_string = "";
//	size_t position;
//	int prec = setup_aux->getPrecisionCurrent();

    string word1 = "X[0l]=";
    string word2 = "X[1l]=";
    string wordf = "fobj=";
    size_t position1;
    size_t position2;
    size_t positionf;
    size_t parenthesis;

	file_log = take_file(name_file_log);
	std::size_t found_F = file_log.find("FAILED");
	std::size_t found_S = file_log.find("SUCCESSFUL");

	if(found_F!=std::string::npos)
	{

       position1 = file_log.rfind(word1);
       position2 = file_log.rfind(word2);
       positionf = file_log.rfind(wordf);

       aux_string = file_log.substr(position1+6, file_log.length());
       parenthesis = aux_string.find(" ");
       setup_aux->setX2Current( convertValue.convertStringDouble( aux_string.substr(0, parenthesis) ) );

       aux_string = file_log.substr(position2+6, file_log.length());
       parenthesis = aux_string.find(" ");
       setup_aux->setX2Current(  convertValue.convertStringDouble( aux_string.substr(0, parenthesis) )  );

       aux_string = file_log.substr(positionf+5, file_log.length());
       parenthesis = aux_string.find(" ");
       setup_aux->setFcFc(  convertValue.convertStringDouble( aux_string.substr(0, parenthesis)  )  );


	}
	else if(found_S!=std::string::npos)
	{
		setup_aux->setStatusCe(1);
	}
	else
	{
		setup_aux->setStatusCe(2);
	}
}


} /* namespace TCEXAMPLES */
