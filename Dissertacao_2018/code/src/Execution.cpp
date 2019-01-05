/*
 * Execution.cpp
 *
 *  Created on: 19/11/2018
 *      Author: higo
 */

#include "Execution.h"

namespace EXCUTION {

Execution::Execution() {
	// TODO Auto-generated constructor stub

}

Execution::~Execution() {
	// TODO Auto-generated destructor stub
}

void Execution::run(Setup* experiment) {

		experiment->printSetupExperiment();

		if(experiment->bmc == 1)
		{
				if(experiment->alg == 1)
				{
						if(experiment->solver == 1)
							run_ESBMC_G_BOOLECTOR(experiment);
						else if(experiment->solver == 2)
							run_ESBMC_G_Z3(experiment);
						else if(experiment->solver == 3)
							run_ESBMC_G_MATHSAT(experiment);
				}
				else if(experiment->alg== 2)
				{
						if(experiment->solver == 1)
							run_ESBMC_S_BOOLECTOR(experiment);
						else if(experiment->solver == 2)
							run_ESBMC_S_Z3(experiment);
						else if(experiment->solver == 3)
							run_ESBMC_S_MATHSAT(experiment);
				}
				else if(experiment->alg == 3)
				{
						if(experiment->solver == 1)
							run_ESBMC_C_BOOLECTOR(experiment);
						else if(experiment->solver == 2)
							run_ESBMC_C_Z3(experiment);
						else if(experiment->solver == 3)
							run_ESBMC_C_MATHSAT(experiment);
				}
		}
		else if(experiment->bmc == 2)
		{
				if(experiment->alg== 1)
				{
						if(experiment->solver == 4)
						{
							run_CBMC_G_MINISAT(experiment);
						}
				}
				else if(experiment->alg== 2)
				{
						if(experiment->solver == 4)
						{
							run_CBMC_S_MINISAT(experiment);
						}
				}
				else if(experiment->alg== 3)
				{
						if(experiment->solver == 4)
						{
							run_CBMC_C_MINISAT(experiment);
						}
				}
		}
		else if(experiment->bmc == 3)
		{
			if(experiment->alg== 1){}
			else if(experiment->alg== 2){}
			else if(experiment->alg== 3){}
		}

}



//		Configuração do Experimento
//
// ############################################################




void Execution::run_ESBMC_G_BOOLECTOR(Setup* experiment)
{

	//	Configuração do Experimento
	//=================================
	cout << endl;
	cout << " Configuration Optimization" << endl;
	cout << endl;
	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "    Algorithm: CEGIO-G" << endl;
	cout << "          BMC: ESBMC" << endl;
	cout << "       Solver: Boolector" << endl;
	cout << endl;



	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	string new_fiS;
	float compensar_fobj =  0.00001;
	string compensar_fobjS;
	int v_log = 1;
	string v_log_CE;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );


	//	Gerar Restrições ASSUMES
	//=================================
  	experiment->setRestrictions( generate_assumes(experiment) );


  	// Gerar Arquivo C para calcular Mínimo
	//=================================
  	generatefilesAUX.create_f(experiment);
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());


  	// Gerar Especificação
	//=================================
  	generatefilesAUX.create_specification_ESBMC_G_Boolector(experiment);


  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			// Verifica Precisão - While Interno
  			while( stay_precision )
  			{

					 // Incrementa Logs
					cout << " ### Verificação " + convertValue.convertDoubleString(v_log)<< endl;
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);

					 // Verifica Especificação
					command = "./esbmc min_" +experiment->name_function + ".c --boolector > " +v_log_CE;
					cout << "   " + command << endl;
					system(command.c_str());

					// Analisa Contra-Exmplo
					tratar_contra_exemplo.take_CE_ESBMC_Boolector(v_log_CE, experiment);

					// Verificação desconhecida
					if(experiment->getStatusCe() == 2){


							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							//  Stop While Internal
							break;

					// Verificação Sucesso
					}else if(experiment->getStatusCe() == 1){
							v_log++;
							stay_precision = false;
							//  Stop While Internal
							break;

					// Verificação Falhou
					}else{

							// Caso valor encontrado seja menor que o ultimo candidato
							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									// Minimo valor valido é atualizado
									experiment->setFcCurrent(experiment->getFcFc());

									// Logs Incrementados
									v_log++;

									// Atualiza Função Candidata para uma nova especificação
									new_fiS =  new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_G_Boolector(experiment);

							// Caso encontre o mesmo valor
							}else{
									// Increase the Compensator
									compensar_fobj = compensar_fobj * 10;

									// Atualiza Função Candidata para uma nova especificação, Considerando Compensador
									new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Incrementa Log
									v_log++;

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_G_Boolector(experiment);
							}

					}

  			} // Fim While Interno


			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.00001;

			// Atualiza Função Candidata
			new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
			experiment->setFcCurrentString(new_fiS);

			// Gera nova Especificação com nova Função Candidata
			experiment->setFcCurrent( experiment->getFcCurrent() - compensar_fobj);
			generatefilesAUX.create_specification_ESBMC_G_Boolector(experiment);


	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString(experiment->getFcCurrent()) << endl;
    cout << "####################################" << endl ;

}

void Execution::run_ESBMC_G_Z3(Setup* experiment)
{

	//	Configuração do Experimento
	//=================================
	cout << endl << " Configuration Optimization" << endl << endl;

	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "    Algorithm: CEGIO-G" << endl;
	cout << "          BMC: ESBMC" << endl;
	cout << "       Solver: Z3" << endl;
	cout << endl;



	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	string new_fiS;
	float compensar_fobj =  0.00001;
	string compensar_fobjS;
	int v_log = 1;
	string v_log_CE;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );


	//	Gerar Restrições ASSUMES
	//=================================
  	experiment->setRestrictions( generate_assumes(experiment) );


  	// Gerar Arquivo C para calcular Mínimo
	//=================================
  	generatefilesAUX.create_f(experiment);
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());


  	// Gerar Especificação
	//=================================
  	generatefilesAUX.create_specification_ESBMC_G_Z3(experiment);


  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			// Verifica Precisão - While Interno
  			while( stay_precision )
  			{

					 // Incrementa Logs
					cout << " ### Verificação " + convertValue.convertDoubleString(v_log)<< endl;
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);

					 // Verifica Especificação
					command = "./esbmc min_" +experiment->name_function + ".c --z3 > " +v_log_CE;
					cout << "   " + command << endl;
					system(command.c_str());

					// Analisa Contra-Exmplo
					tratar_contra_exemplo.take_CE_ESBMC_Z3(v_log_CE, experiment);

					// Verificação desconhecida
					if(experiment->getStatusCe() == 2){

							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							//  Stop While Internal
							break;

					// Verificação Sucesso
					}else if(experiment->getStatusCe() == 1){
							v_log++;
							stay_precision = false;
							//  Stop While Internal
							break;

					// Verificação Falhou
					}else{

							// Caso valor encontrado seja menor que o ultimo candidato
							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									// Minimo valor valido é atualizado
									experiment->setFcCurrent(experiment->getFcFc());

									// Logs Incrementados
									v_log++;

									// Atualiza Função Candidata para uma nova especificação
									new_fiS =  new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_G_Z3(experiment);

							// Caso encontre o mesmo valor
							}else{
									// Increase the Compensator
									compensar_fobj = compensar_fobj * 10;

									// Atualiza Função Candidata para uma nova especificação, Considerando Compensador
									new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Incrementa Log
									v_log++;

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_G_Z3(experiment);
							}

					}

  			} // Fim While Interno


			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.00001;

			// Atualiza Função Candidata
			new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
			experiment->setFcCurrentString(new_fiS);

			// Gera nova Especificação com nova Função Candidata
			experiment->setFcCurrent( experiment->getFcCurrent() - compensar_fobj);
			generatefilesAUX.create_specification_ESBMC_G_Z3(experiment);


	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString(experiment->getFcCurrent()) << endl;
    cout << "####################################" << endl ;

}

void Execution::run_ESBMC_G_MATHSAT(Setup* experiment)
{

	//	Configuração do Experimento
	//=================================
	cout << endl;
	cout << " Configuration Optimization" << endl;
	cout << endl;
	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "    Algorithm: CEGIO-G" << endl;
	cout << "          BMC: ESBMC" << endl;
	cout << "       Solver: Mathsat" << endl;
	cout << endl;



	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	string new_fiS;
	float compensar_fobj =  0.00001;
	string compensar_fobjS;
	int v_log = 1;
	string v_log_CE;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );


	//	Gerar Restrições ASSUMES
	//=================================
  	experiment->setRestrictions( generate_assumes(experiment) );


  	// Gerar Arquivo C para calcular Mínimo
	//=================================
  	generatefilesAUX.create_f(experiment);
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());


  	// Gerar Especificação
	//=================================
  	generatefilesAUX.create_specification_ESBMC_G_Mathsat(experiment);


  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			// Verifica Precisão - While Interno
  			while( stay_precision )
  			{

					 // Incrementa Logs
					cout << " ### Verificação " + convertValue.convertDoubleString(v_log)<< endl;
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);

					 // Verifica Especificação
					command = "./esbmc min_" +experiment->name_function + ".c --mathsat > " +v_log_CE;
					cout << "   " + command << endl;
					system(command.c_str());

					// Analisa Contra-Exmplo
					tratar_contra_exemplo.take_CE_ESBMC_Mathsat(v_log_CE, experiment);

					// Verificação desconhecida
					if(experiment->getStatusCe() == 2){

							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							//  Stop While Internal
							break;

					// Verificação Sucesso
					}else if(experiment->getStatusCe() == 1){
							v_log++;
							stay_precision = false;
							//  Stop While Internal
							break;

					// Verificação Falhou
					}else{

							// Caso valor encontrado seja menor que o ultimo candidato
							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									// Minimo valor valido é atualizado
									experiment->setFcCurrent(experiment->getFcFc());

									// Logs Incrementados
									v_log++;

									// Atualiza Função Candidata para uma nova especificação
									new_fiS =  new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_G_Mathsat(experiment);

							// Caso encontre o mesmo valor
							}else{
									// Increase the Compensator
									compensar_fobj = compensar_fobj * 10;

									// Atualiza Função Candidata para uma nova especificação, Considerando Compensador
									new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Incrementa Log
									v_log++;

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_G_Mathsat(experiment);
							}

					}

  			} // Fim While Interno


			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.00001;

			// Atualiza Função Candidata
			new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
			experiment->setFcCurrentString(new_fiS);

			// Gera nova Especificação com nova Função Candidata
			experiment->setFcCurrent( experiment->getFcCurrent() - compensar_fobj);
			generatefilesAUX.create_specification_ESBMC_G_Mathsat(experiment);


	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString(experiment->getFcCurrent()) << endl;
    cout << "####################################" << endl ;

}



void Execution::run_ESBMC_S_BOOLECTOR(Setup* experiment){

	//	Configuração do Experimento
	//=================================
	cout << endl;
	cout << " Configuration Optimization" << endl;
	cout << endl;
	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "    Algorithm: CEGIO-S" << endl;
	cout << "          BMC: ESBMC" << endl;
	cout << "       Solver: Boolector" << endl;
	cout << endl;



	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	string new_fiS;
	float compensar_fobj =  0.00001;
	string compensar_fobjS;
	int v_log = 1;
	string v_log_CE;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );



	//	Gerar Restrições ASSUMES
	//=================================
  	experiment->setRestrictions( generate_assumes(experiment) );


  	// Gerar Arquivo C para calcular Mínimo
	//=================================
  	generatefilesAUX.create_f(experiment);
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());


  	// Gerar Especificação
	//=================================
  	generatefilesAUX.create_specification_ESBMC_S_Boolector(experiment);

  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			// Verifica Precisão - While Interno
  			while( stay_precision )
  			{

					 // Incrementa Logs
					cout << " ### Verificação " + convertValue.convertDoubleString(v_log)<< endl;
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);

					 // Verifica Especificação
					command = "./esbmc min_" +experiment->name_function + ".c --boolector > " +v_log_CE;
					cout << "   " + command << endl;
					system(command.c_str());

					// Analisa Contra-Exmplo
					tratar_contra_exemplo.take_CE_ESBMC_Boolector(v_log_CE, experiment);

					// Verificação desconhecida
					if(experiment->getStatusCe() == 2){

							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							//  Stop While Internal
							break;

					// Verificação Sucesso
					}else if(experiment->getStatusCe() == 1){
							v_log++;
							stay_precision = false;
							//  Stop While Internal
							break;

					// Verificação Falhou
					}else{

							// Caso valor encontrado seja menor que o ultimo candidato
							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									// Minimo valor valido é atualizado
									experiment->setFcCurrent(experiment->getFcFc());

									// Logs Incrementados
									v_log++;

									// Atualiza Função Candidata para uma nova especificação
									new_fiS =  new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_S_Boolector(experiment);

							// Caso encontre o mesmo valor
							}else{
									// Increase the Compensator
									compensar_fobj = compensar_fobj * 10;

									// Atualiza Função Candidata para uma nova especificação, Considerando Compensador
									new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Incrementa Log
									v_log++;

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_S_Boolector(experiment);
							}

					}

  			} // Fim While Interno


			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.00001;

			// Atualiza Função Candidata
			new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
			experiment->setFcCurrentString(new_fiS);

			// Gera nova Especificação com nova Função Candidata
			experiment->setFcCurrent( experiment->getFcCurrent() - compensar_fobj);
			generatefilesAUX.create_specification_ESBMC_S_Boolector(experiment);


	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString(experiment->getFcCurrent()) << endl;
    cout << "####################################" << endl ;

}

void Execution::run_ESBMC_S_Z3(Setup* experiment){

	//	Configuração do Experimento
	//=================================
	cout << endl;
	cout << " Configuration Optimization" << endl;
	cout << endl;
	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "    Algorithm: CEGIO-S" << endl;
	cout << "          BMC: ESBMC" << endl;
	cout << "       Solver: Z3" << endl;
	cout << endl;



	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	string new_fiS;
	float compensar_fobj =  0.00001;
	string compensar_fobjS;
	int v_log = 1;
	string v_log_CE;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );



	//	Gerar Restrições ASSUMES
	//=================================
  	experiment->setRestrictions( generate_assumes(experiment) );


  	// Gerar Arquivo C para calcular Mínimo
	//=================================
  	generatefilesAUX.create_f(experiment);
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());


  	// Gerar Especificação
	//=================================
  	generatefilesAUX.create_specification_ESBMC_S_Z3(experiment);

  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			// Verifica Precisão - While Interno
  			while( stay_precision )
  			{

					 // Incrementa Logs
					cout << " ### Verificação " + convertValue.convertDoubleString(v_log)<< endl;
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);

					 // Verifica Especificação
					command = "./esbmc min_" +experiment->name_function + ".c --z3 > " +v_log_CE;
					cout << "   " + command << endl;
					system(command.c_str());

					// Analisa Contra-Exmplo
					tratar_contra_exemplo.take_CE_ESBMC_Z3(v_log_CE, experiment);

					// Verificação desconhecida
					if(experiment->getStatusCe() == 2){

							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							//  Stop While Internal
							break;

					// Verificação Sucesso
					}else if(experiment->getStatusCe() == 1){
							v_log++;
							stay_precision = false;
							//  Stop While Internal
							break;

					// Verificação Falhou
					}else{

							// Caso valor encontrado seja menor que o ultimo candidato
							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									// Minimo valor valido é atualizado
									experiment->setFcCurrent(experiment->getFcFc());

									// Logs Incrementados
									v_log++;

									// Atualiza Função Candidata para uma nova especificação
									new_fiS =  new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_S_Z3(experiment);

							// Caso encontre o mesmo valor
							}else{
									// Increase the Compensator
									compensar_fobj = compensar_fobj * 10;

									// Atualiza Função Candidata para uma nova especificação, Considerando Compensador
									new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Incrementa Log
									v_log++;

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_S_Z3(experiment);
							}

					}

  			} // Fim While Interno


			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.00001;

			// Atualiza Função Candidata
			new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
			experiment->setFcCurrentString(new_fiS);

			// Gera nova Especificação com nova Função Candidata
			experiment->setFcCurrent( experiment->getFcCurrent() - compensar_fobj);
			generatefilesAUX.create_specification_ESBMC_S_Z3(experiment);


	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString(experiment->getFcCurrent()) << endl;
    cout << "####################################" << endl ;

}

void Execution::run_ESBMC_S_MATHSAT(Setup* experiment){

	//	Configuração do Experimento
	//=================================
	cout << endl;
	cout << " Configuration Optimization" << endl;
	cout << endl;
	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "    Algorithm: CEGIO-S" << endl;
	cout << "          BMC: ESBMC" << endl;
	cout << "       Solver: Mathasat" << endl;
	cout << endl;



	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	string new_fiS;
	float compensar_fobj =  0.00001;
	string compensar_fobjS;
	int v_log = 1;
	string v_log_CE;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );



	//	Gerar Restrições ASSUMES
	//=================================
  	experiment->setRestrictions( generate_assumes(experiment) );


  	// Gerar Arquivo C para calcular Mínimo
	//=================================
  	generatefilesAUX.create_f(experiment);
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());


  	// Gerar Especificação
	//=================================
  	generatefilesAUX.create_specification_ESBMC_S_Mathsat(experiment);

  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			// Verifica Precisão - While Interno
  			while( stay_precision )
  			{

					 // Incrementa Logs
					cout << " ### Verificação " + convertValue.convertDoubleString(v_log)<< endl;
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);

					 // Verifica Especificação
					command = "./esbmc min_" +experiment->name_function + ".c --mathsat > " +v_log_CE;
					cout << "   " + command << endl;
					system(command.c_str());

					// Analisa Contra-Exmplo
					tratar_contra_exemplo.take_CE_ESBMC_Mathsat(v_log_CE, experiment);

					// Verificação desconhecida
					if(experiment->getStatusCe() == 2){

							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							//  Stop While Internal
							break;

					// Verificação Sucesso
					}else if(experiment->getStatusCe() == 1){
							v_log++;
							stay_precision = false;
							//  Stop While Internal
							break;

					// Verificação Falhou
					}else{

							// Caso valor encontrado seja menor que o ultimo candidato
							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									// Minimo valor valido é atualizado
									experiment->setFcCurrent(experiment->getFcFc());

									// Logs Incrementados
									v_log++;

									// Atualiza Função Candidata para uma nova especificação
									new_fiS =  new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_S_Mathsat(experiment);

							// Caso encontre o mesmo valor
							}else{
									// Increase the Compensator
									compensar_fobj = compensar_fobj * 10;

									// Atualiza Função Candidata para uma nova especificação, Considerando Compensador
									new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Incrementa Log
									v_log++;

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_S_Mathsat(experiment);
							}

					}

  			} // Fim While Interno


			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.00001;

			// Atualiza Função Candidata
			new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
			experiment->setFcCurrentString(new_fiS);

			// Gera nova Especificação com nova Função Candidata
			experiment->setFcCurrent( experiment->getFcCurrent() - compensar_fobj);
			generatefilesAUX.create_specification_ESBMC_S_Mathsat(experiment);


	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString(experiment->getFcCurrent()) << endl;
    cout << "####################################" << endl ;


}





void Execution::run_ESBMC_C_BOOLECTOR(Setup* experiment){


	//	Configuração do Experimento
	//=================================
	cout << endl;
	cout << " Configuration Optimization" << endl;
	cout << endl;
	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "    Algorithm: CEGIO-C" << endl;
	cout << "          BMC: ESBMC" << endl;
	cout << "       Solver: Boolector" << endl;
	cout << endl;



	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	string new_fiS;
	float compensar_fobj =  0.00001;
	string compensar_fobjS;
	int v_log = 1;
	string v_log_CE;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );



	//	Gerar Restrições ASSUMES
	//=================================
  	experiment->setRestrictions( generate_assumes(experiment) );


  	// Gerar Arquivo C para calcular Mínimo
	//=================================
  	generatefilesAUX.create_f(experiment);
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());


  	// Gerar Especificação
	//=================================
  	generatefilesAUX.create_specification_ESBMC_C_Boolector(experiment);

  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			// Verifica Precisão - While Interno
  			while( stay_precision )
  			{

					 // Incrementa Logs
					cout << " ### Verificação " + convertValue.convertDoubleString(v_log)<< endl;
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);

					 // Verifica Especificação
					command = "./esbmc min_" +experiment->name_function + ".c --boolector > " +v_log_CE;
					cout << "   " + command << endl;
					system(command.c_str());

					// Analisa Contra-Exmplo
					tratar_contra_exemplo.take_CE_ESBMC_Boolector(v_log_CE, experiment);

					// Verificação desconhecida
					if(experiment->getStatusCe() == 2){

							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							//  Stop While Internal
							break;

					// Verificação Sucesso
					}else if(experiment->getStatusCe() == 1){
							v_log++;
							stay_precision = false;
							//  Stop While Internal
							break;

					// Verificação Falhou
					}else{

							// Caso valor encontrado seja menor que o ultimo candidato
							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									// Minimo valor valido é atualizado
									experiment->setFcCurrent(experiment->getFcFc());

									// Logs Incrementados
									v_log++;

									// Atualiza Função Candidata para uma nova especificação
									new_fiS =  new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_C_Boolector(experiment);

							// Caso encontre o mesmo valor
							}else{
									// Increase the Compensator
									compensar_fobj = compensar_fobj * 10;

									// Atualiza Função Candidata para uma nova especificação, Considerando Compensador
//									new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									new_fiS = convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Incrementa Log
									v_log++;

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_C_Boolector(experiment);
							}

					}

  			} // Fim While Interno


  			experiment->setTypeRestrictions(1);

  			cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") =" + convertValue.convertDoubleString(experiment->getFcCurrent())  << endl;

			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.00001;

			// Atualiza Função Candidata
			new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
			experiment->setFcCurrentString(new_fiS);

			//	Gerar Novas Restrições ASSUMES
			//=================================
		  	experiment->setRestrictions( generate_assumes(experiment) );

			// Gera nova Especificação com nova Função Candidata
			experiment->setFcCurrent( experiment->getFcCurrent() - compensar_fobj);
			generatefilesAUX.create_specification_ESBMC_C_Boolector(experiment);


	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString(experiment->getFcCurrent()) << endl;
    cout << "####################################" << endl ;


}

void Execution::run_ESBMC_C_Z3(Setup* experiment){

	//	Configuração do Experimento
	//=================================
	cout << endl;
	cout << " Configuration Optimization" << endl;
	cout << endl;
	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "    Algorithm: CEGIO-C" << endl;
	cout << "          BMC: ESBMC" << endl;
	cout << "       Solver: Z3" << endl;
	cout << endl;



	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	string new_fiS;
	float compensar_fobj =  0.00001;
	string compensar_fobjS;
	int v_log = 1;
	string v_log_CE;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );



	//	Gerar Restrições ASSUMES
	//=================================
  	experiment->setRestrictions( generate_assumes(experiment) );


  	// Gerar Arquivo C para calcular Mínimo
	//=================================
  	generatefilesAUX.create_f(experiment);
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());


  	// Gerar Especificação
	//=================================
  	generatefilesAUX.create_specification_ESBMC_C_Z3(experiment);

  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			// Verifica Precisão - While Interno
  			while( stay_precision )
  			{

					 // Incrementa Logs
					cout << " ### Verificação " + convertValue.convertDoubleString(v_log)<< endl;
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);

					 // Verifica Especificação
					command = "./esbmc min_" +experiment->name_function + ".c --z3 > " +v_log_CE;
					cout << "   " + command << endl;
					system(command.c_str());

					// Analisa Contra-Exmplo
					tratar_contra_exemplo.take_CE_ESBMC_Z3(v_log_CE, experiment);

					// Verificação desconhecida
					if(experiment->getStatusCe() == 2){

							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							//  Stop While Internal
							break;

					// Verificação Sucesso
					}else if(experiment->getStatusCe() == 1){
							v_log++;
							stay_precision = false;
							//  Stop While Internal
							break;

					// Verificação Falhou
					}else{

							// Caso valor encontrado seja menor que o ultimo candidato
							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									// Minimo valor valido é atualizado
									experiment->setFcCurrent(experiment->getFcFc());

									// Logs Incrementados
									v_log++;

									// Atualiza Função Candidata para uma nova especificação
									new_fiS =  new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_C_Z3(experiment);

							// Caso encontre o mesmo valor
							}else{
									// Increase the Compensator
									compensar_fobj = compensar_fobj * 10;

									// Atualiza Função Candidata para uma nova especificação, Considerando Compensador
//									new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									new_fiS = convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Incrementa Log
									v_log++;

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_C_Z3(experiment);
							}

					}

  			} // Fim While Interno


  			experiment->setTypeRestrictions(1);

  			cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") =" + convertValue.convertDoubleString(experiment->getFcCurrent())  << endl;

			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.00001;

			// Atualiza Função Candidata
			new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
			experiment->setFcCurrentString(new_fiS);

			//	Gerar Novas Restrições ASSUMES
			//=================================
		  	experiment->setRestrictions( generate_assumes(experiment) );

			// Gera nova Especificação com nova Função Candidata
			experiment->setFcCurrent( experiment->getFcCurrent() - compensar_fobj);
			generatefilesAUX.create_specification_ESBMC_C_Z3(experiment);


	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString(experiment->getFcCurrent()) << endl;
    cout << "####################################" << endl ;


}

void Execution::run_ESBMC_C_MATHSAT(Setup* experiment){


	//	Configuração do Experimento
	//=================================
	cout << endl;
	cout << " Configuration Optimization" << endl;
	cout << endl;
	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "    Algorithm: CEGIO-C" << endl;
	cout << "          BMC: ESBMC" << endl;
	cout << "       Solver: MATHSAT" << endl;
	cout << endl;



	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	string new_fiS;
	float compensar_fobj =  0.00001;
	string compensar_fobjS;
	int v_log = 1;
	string v_log_CE;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );



	//	Gerar Restrições ASSUMES
	//=================================
  	experiment->setRestrictions( generate_assumes(experiment) );


  	// Gerar Arquivo C para calcular Mínimo
	//=================================
  	generatefilesAUX.create_f(experiment);
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());


  	// Gerar Especificação
	//=================================
  	generatefilesAUX.create_specification_ESBMC_C_Mathsat(experiment);

  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			// Verifica Precisão - While Interno
  			while( stay_precision )
  			{

					 // Incrementa Logs
					cout << " ### Verificação " + convertValue.convertDoubleString(v_log)<< endl;
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);

					 // Verifica Especificação
					command = "./esbmc min_" +experiment->name_function + ".c --mathsat > " +v_log_CE;
					cout << "   " + command << endl;
					system(command.c_str());

					// Analisa Contra-Exmplo
					tratar_contra_exemplo.take_CE_ESBMC_Mathsat(v_log_CE, experiment);

					// Verificação desconhecida
					if(experiment->getStatusCe() == 2){

							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							//  Stop While Internal
							break;

					// Verificação Sucesso
					}else if(experiment->getStatusCe() == 1){
							v_log++;
							stay_precision = false;
							//  Stop While Internal
							break;

					// Verificação Falhou
					}else{

							// Caso valor encontrado seja menor que o ultimo candidato
							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									// Minimo valor valido é atualizado
									experiment->setFcCurrent(experiment->getFcFc());

									// Logs Incrementados
									v_log++;

									// Atualiza Função Candidata para uma nova especificação
									new_fiS =  new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_C_Mathsat(experiment);

							// Caso encontre o mesmo valor
							}else{
									// Increase the Compensator
									compensar_fobj = compensar_fobj * 10;

									// Atualiza Função Candidata para uma nova especificação, Considerando Compensador
//									new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									new_fiS = convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Incrementa Log
									v_log++;

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_C_Mathsat(experiment);
							}

					}

  			} // Fim While Interno


  			experiment->setTypeRestrictions(1);

  			cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") =" + convertValue.convertDoubleString(experiment->getFcCurrent())  << endl;

			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.00001;

			// Atualiza Função Candidata
			new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
			experiment->setFcCurrentString(new_fiS);

			//	Gerar Novas Restrições ASSUMES
			//=================================
		  	experiment->setRestrictions( generate_assumes(experiment) );

			// Gera nova Especificação com nova Função Candidata
			experiment->setFcCurrent( experiment->getFcCurrent() - compensar_fobj);
			generatefilesAUX.create_specification_ESBMC_C_Mathsat(experiment);


	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString(experiment->getFcCurrent()) << endl;
    cout << "####################################" << endl ;


}


void Execution::run_CBMC_G_MINISAT(Setup* experiment)
{

	//	Configuração do Experimento
	//=================================
	cout << endl;
	cout << " Configuration Optimization" << endl;
	cout << endl;
	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "    Algorithm: CEGIO-G" << endl;
	cout << "          BMC: CBMC" << endl;
	cout << "       Solver: Minisat" << endl;
	cout << endl;


	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	string new_fiS;
	float compensar_fobj =  0.00001;
	string compensar_fobjS;
	int v_log = 1;
	string v_log_CE;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );


	//	Gerar Restrições ASSUMES
	//=================================
  	experiment->setRestrictions( generate_assumes(experiment) );


  	// Gerar Arquivo C para calcular Mínimo
	//=================================
  	generatefilesAUX.create_f(experiment);
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());


  	// Gerar Especificação
	//=================================
  	generatefilesAUX.create_specification_CBMC_G_MINISAT(experiment);


  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			// Verifica Precisão - While Interno
  			while( stay_precision )
  			{

					 // Incrementa Logs
					cout << " ### Verificação " + convertValue.convertDoubleString(v_log)<< endl;
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);

					 // Verifica Especificação
//				    command = "./cbmc min_" + ex.name_function + 		  ".c  > " + v_log 		+ " 2>> " + v_log;
				    command = "./cbmc min_" + experiment->name_function + ".c  > " + v_log_CE   + " 2>> " + v_log_CE;
					cout << "   " + command << endl;
					system(command.c_str());

					// Analisa Contra-Exmplo
					tratar_contra_exemplo.take_CE_CBMC_MINISAT(v_log_CE, experiment);

					// Verificação desconhecida
					if(experiment->getStatusCe() == 2){


							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							//  Stop While Internal
							break;

					// Verificação Sucesso
					}else if(experiment->getStatusCe() == 1){
							v_log++;
							stay_precision = false;
							//  Stop While Internal
							break;

					// Verificação Falhou
					}else{

							// Caso valor encontrado seja menor que o ultimo candidato
							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									// Minimo valor valido é atualizado
									experiment->setFcCurrent(experiment->getFcFc());

									// Logs Incrementados
									v_log++;

									// Atualiza Função Candidata para uma nova especificação
									new_fiS =  new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_CBMC_G_MINISAT(experiment);

							// Caso encontre o mesmo valor
							}else{
									// Increase the Compensator
									compensar_fobj = compensar_fobj * 10;

									// Atualiza Função Candidata para uma nova especificação, Considerando Compensador
									new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Incrementa Log
									v_log++;

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_CBMC_G_MINISAT(experiment);
							}

					}

  			} // Fim While Interno


			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.00001;

			// Atualiza Função Candidata
			new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
			experiment->setFcCurrentString(new_fiS);

			// Gera nova Especificação com nova Função Candidata
			experiment->setFcCurrent( experiment->getFcCurrent() - compensar_fobj);
			generatefilesAUX.create_specification_CBMC_G_MINISAT(experiment);


	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString(experiment->getFcCurrent()) << endl;
    cout << "####################################" << endl ;

}


void Execution::run_CBMC_S_MINISAT(Setup* experiment){

	//	Configuração do Experimento
	//=================================
	cout << endl;
	cout << " Configuration Optimization" << endl;
	cout << endl;
	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "    Algorithm: CEGIO-S" << endl;
	cout << "          BMC: ESBMC" << endl;
	cout << "       Solver: Boolector" << endl;
	cout << endl;



	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	string new_fiS;
	float compensar_fobj =  0.00001;
	string compensar_fobjS;
	int v_log = 1;
	string v_log_CE;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );



	//	Gerar Restrições ASSUMES
	//=================================
  	experiment->setRestrictions( generate_assumes(experiment) );


  	// Gerar Arquivo C para calcular Mínimo
	//=================================
  	generatefilesAUX.create_f(experiment);
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());


  	// Gerar Especificação
	//=================================
  	generatefilesAUX.create_specification_ESBMC_S_Boolector(experiment);

  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			// Verifica Precisão - While Interno
  			while( stay_precision )
  			{

					 // Incrementa Logs
					cout << " ### Verificação " + convertValue.convertDoubleString(v_log)<< endl;
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);

					 // Verifica Especificação
					command = "./esbmc min_" +experiment->name_function + ".c --boolector > " +v_log_CE;
					cout << "   " + command << endl;
					system(command.c_str());

					// Analisa Contra-Exmplo
					tratar_contra_exemplo.take_CE_ESBMC_Boolector(v_log_CE, experiment);

					// Verificação desconhecida
					if(experiment->getStatusCe() == 2){

							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							//  Stop While Internal
							break;

					// Verificação Sucesso
					}else if(experiment->getStatusCe() == 1){
							v_log++;
							stay_precision = false;
							//  Stop While Internal
							break;

					// Verificação Falhou
					}else{

							// Caso valor encontrado seja menor que o ultimo candidato
							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									// Minimo valor valido é atualizado
									experiment->setFcCurrent(experiment->getFcFc());

									// Logs Incrementados
									v_log++;

									// Atualiza Função Candidata para uma nova especificação
									new_fiS =  new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_S_Boolector(experiment);

							// Caso encontre o mesmo valor
							}else{
									// Increase the Compensator
									compensar_fobj = compensar_fobj * 10;

									// Atualiza Função Candidata para uma nova especificação, Considerando Compensador
									new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Incrementa Log
									v_log++;

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_S_Boolector(experiment);
							}

					}

  			} // Fim While Interno


			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.00001;

			// Atualiza Função Candidata
			new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
			experiment->setFcCurrentString(new_fiS);

			// Gera nova Especificação com nova Função Candidata
			experiment->setFcCurrent( experiment->getFcCurrent() - compensar_fobj);
			generatefilesAUX.create_specification_ESBMC_S_Boolector(experiment);


	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString(experiment->getFcCurrent()) << endl;
    cout << "####################################" << endl ;

}


void Execution::run_CBMC_C_MINISAT(Setup* experiment){


	//	Configuração do Experimento
	//=================================
	cout << endl;
	cout << " Configuration Optimization" << endl;
	cout << endl;
	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "    Algorithm: CEGIO-C" << endl;
	cout << "          BMC: ESBMC" << endl;
	cout << "       Solver: Boolector" << endl;
	cout << endl;



	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	string new_fiS;
	float compensar_fobj =  0.00001;
	string compensar_fobjS;
	int v_log = 1;
	string v_log_CE;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );



	//	Gerar Restrições ASSUMES
	//=================================
  	experiment->setRestrictions( generate_assumes(experiment) );


  	// Gerar Arquivo C para calcular Mínimo
	//=================================
  	generatefilesAUX.create_f(experiment);
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());


  	// Gerar Especificação
	//=================================
  	generatefilesAUX.create_specification_ESBMC_C_Boolector(experiment);

  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			// Verifica Precisão - While Interno
  			while( stay_precision )
  			{

					 // Incrementa Logs
					cout << " ### Verificação " + convertValue.convertDoubleString(v_log)<< endl;
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);

					 // Verifica Especificação
					command = "./esbmc min_" +experiment->name_function + ".c --boolector > " +v_log_CE;
					cout << "   " + command << endl;
					system(command.c_str());

					// Analisa Contra-Exmplo
					tratar_contra_exemplo.take_CE_ESBMC_Boolector(v_log_CE, experiment);

					// Verificação desconhecida
					if(experiment->getStatusCe() == 2){

							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							//  Stop While Internal
							break;

					// Verificação Sucesso
					}else if(experiment->getStatusCe() == 1){
							v_log++;
							stay_precision = false;
							//  Stop While Internal
							break;

					// Verificação Falhou
					}else{

							// Caso valor encontrado seja menor que o ultimo candidato
							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									// Minimo valor valido é atualizado
									experiment->setFcCurrent(experiment->getFcFc());

									// Logs Incrementados
									v_log++;

									// Atualiza Função Candidata para uma nova especificação
									new_fiS =  new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_C_Boolector(experiment);

							// Caso encontre o mesmo valor
							}else{
									// Increase the Compensator
									compensar_fobj = compensar_fobj * 10;

									// Atualiza Função Candidata para uma nova especificação, Considerando Compensador
//									new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									new_fiS = convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
									experiment->setFcCurrentString(new_fiS);

									// Incrementa Log
									v_log++;

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									generatefilesAUX.create_specification_ESBMC_C_Boolector(experiment);
							}

					}

  			} // Fim While Interno


  			experiment->setTypeRestrictions(1);

  			cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") =" + convertValue.convertDoubleString(experiment->getFcCurrent())  << endl;

			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.00001;

			// Atualiza Função Candidata
			new_fiS = new_fiS + convertValue.convertDoubleString(experiment->getFcCurrent())  + " -" + convertValue.convertDoubleString(compensar_fobj);
			experiment->setFcCurrentString(new_fiS);

			//	Gerar Novas Restrições ASSUMES
			//=================================
		  	experiment->setRestrictions( generate_assumes(experiment) );

			// Gera nova Especificação com nova Função Candidata
			experiment->setFcCurrent( experiment->getFcCurrent() - compensar_fobj);
			generatefilesAUX.create_specification_ESBMC_C_Boolector(experiment);


	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString(experiment->getFcCurrent()) << endl;
    cout << "####################################" << endl ;


}



string Execution::generate_assumes(Setup* experiment){

	string string_assumes = "";
	int i,j;

	if(experiment->type_restrictions == 0){

			string_assumes = string_assumes + "     \n        //-----------------------------------------------------------  ";
			string_assumes = string_assumes + "     \n        // Restrictions\n";

			string_assumes = string_assumes + "     \n        int lim[4] = {";

			string_assumes = string_assumes + convertValue.convertIntString(experiment->getInfX1()) + "*p, ";
			string_assumes = string_assumes + convertValue.convertIntString(experiment->getSupX1()) + "*p, ";
			string_assumes = string_assumes + convertValue.convertIntString(experiment->getInfX2()) + "*p, ";
			string_assumes = string_assumes + convertValue.convertIntString(experiment->getSupX2()) + "*p}; ";

			string_assumes = string_assumes + "\n";
			string_assumes = string_assumes + "\n        for (i = 0; i < nv; i++) {";
			string_assumes = string_assumes + "\n            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );";
			string_assumes = string_assumes + "\n            __ESBMC_assume( X[i] == (float) x[i]/p  ); ";
			string_assumes = string_assumes + "\n        }\n";

			string_assumes = string_assumes + "     \n        //-----------------------------------------------------------  \n\n";

			return string_assumes;

	}else if(experiment->type_restrictions == 1){

			string_assumes = string_assumes + "     \n        //-----------------------------------------------------------  ";
			string_assumes = string_assumes + "     \n        // Restrictions\n";

//			string new_spaceS = "\n  int lim[4] = { " + convert.convertDoubleString((ex._x1*p-1)*10) + ", " + convert.convertDoubleString((ex._x1*p+1)*10) + ", " + convert.convertDoubleString((ex._x2*p-1)*10) + ", " + convert.convertDoubleString((ex._x2*p+1)*10) + " };";
			string new_spaceS = "\n  int lim[4] = { " + convertValue.convertDoubleString(  (experiment->x1_current * experiment->getPrecisionCurrent()-1) *10) + ", " +
														convertValue.convertDoubleString(  (experiment->x1_current * experiment->getPrecisionCurrent()+1) *10) + ", " +
														convertValue.convertDoubleString(  (experiment->x2_current * experiment->getPrecisionCurrent()-1) *10) + ", " +
														convertValue.convertDoubleString(  (experiment->x2_current * experiment->getPrecisionCurrent()+1) *10) + " };";

			string_assumes = string_assumes + new_spaceS;

			string_assumes = string_assumes + "\n";
			string_assumes = string_assumes + "\n        for (i = 0; i < nv; i++) {";
			string_assumes = string_assumes + "\n            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );";
			string_assumes = string_assumes + "\n            __ESBMC_assume( X[i] == (float) x[i]/p  ); ";
			string_assumes = string_assumes + "\n        }\n";

			string_assumes = string_assumes + "     \n        //-----------------------------------------------------------  \n\n";

			return string_assumes;

	}else if(experiment->type_restrictions == 2){

        string_assumes = string_assumes + "     \n        //-----------------------------------------------------------  ";
        string_assumes = string_assumes + "     \n        // Restrictions\n";

        string_assumes = string_assumes + "     \n        int lim[4] = {";

//        for(i=0;i<l_A;i++){
//         for(j=0;j<c_A;j++){
//            string_assumes = string_assumes + convert.convertIntString(matrixA[i][j]);
//            string_assumes = string_assumes + "*p, ";
//          }
//        }

        string_assumes = string_assumes.substr(0,string_assumes.size()-2);
        string_assumes = string_assumes + "};";

        string_assumes = string_assumes + "\n";
        string_assumes = string_assumes + "\n        for (i = 0; i < nv; i++) {";
        string_assumes = string_assumes + "\n            __CPROVER_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );";
        string_assumes = string_assumes + "\n            __CPROVER_assume( X[i] == (float) x[i]/p  ); ";
        string_assumes = string_assumes + "\n        }\n";


        string_assumes = string_assumes + "     \n        //-----------------------------------------------------------  \n\n";

        return string_assumes;

	}else if(experiment->type_restrictions == 3){

        string_assumes = string_assumes + "     \n        //-----------------------------------------------------------  ";
        string_assumes = string_assumes + "     \n        // Restrictions\n";

//        string new_spaceS = "\n  int lim[4] = { " + convert.convertDoubleString((ex._x1*p-1)*10) + ", " + convert.convertDoubleString((ex._x1*p+1)*10) + ", " + convert.convertDoubleString((ex._x2*p-1)*10) + ", " + convert.convertDoubleString((ex._x2*p+1)*10) + " };";
//        string_assumes = string_assumes + new_spaceS;

        string_assumes = string_assumes + "\n";
        string_assumes = string_assumes + "\n        for (i = 0; i < nv; i++) {";
        string_assumes = string_assumes + "\n            __CPROVER_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );";
        string_assumes = string_assumes + "\n            __CPROVER_assume( X[i] == (float) x[i]/p  ); ";
        string_assumes = string_assumes + "\n        }\n";


        string_assumes = string_assumes + "     \n        //-----------------------------------------------------------  \n\n";

        return string_assumes;
	}

	return string_assumes;

}


} /* namespace EXCUTION */
