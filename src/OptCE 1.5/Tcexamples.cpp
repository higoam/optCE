/*
 * Tcexamples.cpp
 *
 *  Created on: 30 de jan de 2019
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


void Tcexamples::take_CE(string name_file_log, Setup* setup_aux){

//	cout << "take_CE\n" << endl;

		  //ESBMC SEM FOR
	if( (setup_aux->getBmc() == 1) && (setup_aux->getTypeLoop() == 0) ){

		take_CE_ESBMC_sem_For(name_file_log, setup_aux);

	}else //ESBMC COM FOR
	if( (setup_aux->getBmc() == 1) && (setup_aux->getTypeLoop() == 1) ){

		take_CE_ESBMC_com_For(name_file_log, setup_aux);

	}else //CBMC SEM FOR
	if( (setup_aux->getBmc() == 2) && (setup_aux->getTypeLoop() == 0) ){

		take_CE_CBMC_sem_For(name_file_log, setup_aux);

	}else //CBMC COM FOR
	if( (setup_aux->getBmc() == 2) && (setup_aux->getTypeLoop() == 1) ){

		take_CE_CBMC_com_For(name_file_log, setup_aux);

	}

}


void Tcexamples::take_CE_ESBMC_com_For(string name_file_log, Setup* setup_aux){

	int i;

	// Adjustment Variables
	string command = "";
	string file_log;
	string current_coordinates[setup_aux->getVar()];
	string word = ":a=";
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

		for(i=1;i<setup_aux->getVar();i++){
			aux_string = aux_string.substr(position + 2, aux_string.length());
			position = aux_string.find(",");
			current_coordinates[i] = aux_string.substr(0, position);
		}

		double _x1D,_x2D;

		_x1D = convertValue.convertStringDouble(current_coordinates[0].c_str());
		_x2D = convertValue.convertStringDouble(current_coordinates[1].c_str());

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

		command  = "./value_min " + convertValue.convertDoubleString( setup_aux->getX1Current() ) + " " + convertValue.convertDoubleString( setup_aux->getX2Current() ) + " > min_temporary.txt";
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


void Tcexamples::take_CE_ESBMC_sem_For(string name_file_log, Setup* setup_aux){

	int i;

	//cout << "take_CE_ESBMC_sem_For" << endl;

	// Adjustment Variables
	string command = "";
	string file_log;
	string current_coordinates[setup_aux->getVar()];
	string word = "";
	ostringstream convert;
	string aux_string = "";
	size_t position;
	int prec = setup_aux->getPrecisionCurrent();

	file_log = take_file(name_file_log);
	std::size_t found_F = file_log.find("FAILED");
	std::size_t found_S = file_log.find("SUCCESSFUL");

	if(found_F!=std::string::npos)
	{

//		cout << "CONTRA EXEMPLO FALHOU" << endl;

		command  = "./value_min ";

		setup_aux->setStatusCe(0);
		double _xD[10] = {0,0,0,0,0,0,0,0,0,0};

//		cout << "Mínimos Encontrados" << endl;

		for(i=0;i<setup_aux->getVar();i++){
			word = ":x" + convertValue.convertIntString(i+1)  + "=";
			position = file_log.rfind(word);

			aux_string = file_log.substr(position + 4, file_log.length());
			position = aux_string.find("(");
			current_coordinates[i] = aux_string.substr(0, position);
			_xD[i] = convertValue.convertStringDouble(current_coordinates[i].c_str());

			if(_xD[i] > 1000){
				_xD[i] = ((_xD[i] -4294967296)/prec);
			}
			else{
				_xD[i] = (_xD[i]/prec);
			}

			command  = command + convertValue.convertDoubleString( _xD[i] ) + " ";

		}

		setup_aux->setX1Current(_xD[0]);
		setup_aux->setX2Current(_xD[1]);
		setup_aux->setX3Current(_xD[2]);
		setup_aux->setX4Current(_xD[3]);
		setup_aux->setX5Current(_xD[4]);
		setup_aux->setX5Current(_xD[5]);
		setup_aux->setX5Current(_xD[6]);
		setup_aux->setX5Current(_xD[7]);
		setup_aux->setX5Current(_xD[8]);
		setup_aux->setX5Current(_xD[9]);

		command  = command + "> min_temporary.txt";
//		cout << command << endl;
		system(command.c_str());

		string minimumS = take_file("min_temporary.txt");
		setup_aux->setFcFc( convertValue.convertStringDouble(minimumS.substr(0, minimumS.size()).c_str()) );

//		cout << setup_aux->getX1Current() << endl;
//		cout << setup_aux->getX2Current() << endl;
//		cout << setup_aux->getX3Current() << endl;
//		cout << setup_aux->getX4Current() << endl;
//		cout << setup_aux->getX5Current() << endl;

//		cout << setup_aux->getFcFc() << endl;

	}
	else if(found_S!=std::string::npos)
	{
//		cout << "CONTRA EXEMPLO SUCESSO" << endl;
		setup_aux->setStatusCe(1);
	}
	else
	{
//		cout << "CONTRA EXEMPLO DESCONHECIDO" << endl;
		setup_aux->setStatusCe(2);
	}

}


void Tcexamples::take_CE_CBMC_com_For(string name_file_log, Setup* setup_aux){

}


void Tcexamples::take_CE_CBMC_sem_For(string name_file_log, Setup* setup_aux){

	int i;
	//	int prec = setup_aux->precision_current;
	//cout << "take_CE_CBMC_sem_For" << endl;

	// Adjustment Variables
	string command = "";
	string file_log;
	string current_coordinates[setup_aux->getVar()];
	string word = "";
	ostringstream convert;
	string aux_string = "";
	size_t position;
    size_t parenthesis;



	file_log = take_file(name_file_log);
	std::size_t found_F = file_log.find("FAILED");
	std::size_t found_S = file_log.find("SUCCESSFUL");

	if(found_F!=std::string::npos)
	{

		command  = "./value_min ";

		setup_aux->setStatusCe(0);
		double _xD[10] = {0,0,0,0,0,0,0,0,0,0};

		for(i=0;i<setup_aux->getVar();i++){
			word = "X" + convertValue.convertIntString(i+1)  + "=";
			position = file_log.rfind(word);

			aux_string = file_log.substr(position + 3, file_log.length());
			position = aux_string.find("(");
			current_coordinates[i] = aux_string.substr(0, position);
			_xD[i] = convertValue.convertStringDouble(current_coordinates[i].c_str());
		}
		setup_aux->setX1Current(_xD[0]);
		setup_aux->setX2Current(_xD[1]);
		setup_aux->setX3Current(_xD[2]);
		setup_aux->setX4Current(_xD[3]);
		setup_aux->setX5Current(_xD[4]);
		setup_aux->setX5Current(_xD[5]);
		setup_aux->setX5Current(_xD[6]);
		setup_aux->setX5Current(_xD[7]);
		setup_aux->setX5Current(_xD[8]);
		setup_aux->setX5Current(_xD[9]);

		position = file_log.rfind("fobj=");

		aux_string = file_log.substr(position + 5, file_log.length());
        parenthesis = aux_string.find(" ");
        setup_aux->setFcFc(  convertValue.convertStringDouble( aux_string.substr(0, parenthesis)  )  );

        //cout << "Valor encontrado: "<< endl;
        //cout << setup_aux->fc_fc << endl;

	}
	else if(found_S!=std::string::npos)
	{
		//cout << "Tcexamples SUcesso" << endl;
		setup_aux->setStatusCe(1);
	}
	else
	{
		//cout << "Tcexamples Desconhecido" << endl;
		setup_aux->setStatusCe(2);
	}

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

		command  = "./value_min " + convertValue.convertDoubleString( setup_aux->getX1Current() ) + " " + convertValue.convertDoubleString( setup_aux->getX2Current() ) + " > min_temporary.txt";
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

      double _x1D,_x2D;

      _x1D = convertValue.convertStringDouble(current_coordinates[0].c_str());
      _x2D = convertValue.convertStringDouble(current_coordinates[1].c_str());

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

	  command  = "./value_min " + convertValue.convertDoubleString( setup_aux->getX1Current() ) + " " + convertValue.convertDoubleString( setup_aux->getX2Current() ) + " > min_temporary.txt";
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

      double _x1D,_x2D;

      _x1D = convertValue.convertStringDouble(current_coordinates[0].c_str());
      _x2D = convertValue.convertStringDouble(current_coordinates[1].c_str());

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

      command  = "./value_min " + convertValue.convertDoubleString( setup_aux->getX1Current() ) + " " + convertValue.convertDoubleString( setup_aux->getX2Current() ) + " > min_temporary.txt";
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

void Tcexamples::take_CE_ESBMC_CVC(string name_file_log, Setup* setup_aux)
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

		command  = "./value_min " + convertValue.convertDoubleString( setup_aux->getX1Current() ) + " " + convertValue.convertDoubleString( setup_aux->getX2Current() ) + " > min_temporary.txt";
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

void Tcexamples::take_CE_ESBMC_Yices(string name_file_log, Setup* setup_aux)
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

		command  = "./value_min " + convertValue.convertDoubleString( setup_aux->getX1Current() ) + " " + convertValue.convertDoubleString( setup_aux->getX2Current() ) + " > min_temporary.txt";
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


       aux_string = file_log.substr(position1+6, file_log.length());
       parenthesis = aux_string.find(" ");
       setup_aux->setX2Current( convertValue.convertStringDouble( aux_string.substr(0, parenthesis) ) );

       aux_string = file_log.substr(position2+6, file_log.length());
       parenthesis = aux_string.find(" ");
       setup_aux->setX2Current(  convertValue.convertStringDouble( aux_string.substr(0, parenthesis) )  );

       positionf = file_log.rfind(wordf);
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
