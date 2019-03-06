void Execution::run_CEGIO_F(Setup* experiment) {

	cout << "run_CEGIO_F" << endl;

	//	Configuração do Experimento
	//=================================
	cout << endl;
	cout << " Configuration Optimization" << endl;
	cout << endl;
	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "    Algorithm: CEGIO-F" << endl;
	cout << endl;

	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	float compensar_fobj =  0.0001;
	int v_log = 1;
	string v_log_CE;
	int cont_comp = 1;
	float acumulador_cont = 0.0;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );

  	generatefilesAUX.create_f(experiment);			// Gerar Arquivo C para calcular Mínimo
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());


  	generatefilesAUX.create_specification_CEGIO_F(experiment);   	// Gerar Especificação

  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			cout << endl << " ### Precisão Atual " + convertValue.convertDoubleString(experiment->getPrecisionCurrent())<< endl;

  			while( stay_precision )
  			{
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);

					// Verifica Especificação
					if(experiment->getSolver() == 1){
						command = "./esbmc --boolector min_" +experiment->name_function + ".c > " +v_log_CE;
					}else if(experiment->getSolver() == 2){
						command = "./esbmc --boolector min_" +experiment->name_function + ".c  > " +v_log_CE;
					}else if(experiment->getSolver() == 3){
						command = "./esbmc --z3 min_" +experiment->name_function + ".c > " +v_log_CE;
					}else if(experiment->getSolver() == 4){
						command = "./esbmc --mathsat min_" +experiment->name_function + ".c > " +v_log_CE;
					}else if(experiment->getSolver() == 5){
						command = "./esbmc --yices min_" +experiment->name_function + ".c > " +v_log_CE;
					}else if(experiment->getSolver() == 6){
						command = "./esbmc --cvc min_" +experiment->name_function + ".c > " +v_log_CE;
					}else if(experiment->getSolver() == 7){
					    command = "./cbmc min_" + experiment->name_function + ".c  > " + v_log_CE   + " 2>> " + v_log_CE;
					}

//					cout << command << endl;

					system(command.c_str());


					// Analisa Contra-Exmplo
					tratar_contra_exemplo.take_CE(v_log_CE, experiment);

					// Verificação desconhecida
					if(experiment->getStatusCe() == 2){
							v_log++;
							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							//  Stop While Internal
							break;

					// Verificação Sucesso
					}else if(experiment->getStatusCe() == 1){
							v_log++;
							stay_precision = false;

					// Verificação Falhou
					}else{

							// Caso valor encontrado seja menor que o ultimo candidato
							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									// Minimo valor valido é atualizado
									experiment->setFcCurrent(experiment->getFcFc());

									// Logs Incrementados
									v_log++;

									// Atualiza Função Candidata para uma nova especificação
									experiment->setFcCurrent(experiment->getFcFc());

									// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
								  	generatefilesAUX.create_specification_CEGIO_F(experiment);   	// Gerar Especificação

									cout <<  "     f("+ convertValue.convertDoubleString(experiment->getX1Current()) +
							  								"," +
							  								convertValue.convertDoubleString(experiment->getX2Current()) +
							  								")="+
							  								convertValue.convertDoubleString(experiment->getFcCurrent()) + " "<< endl;


							// Caso encontre o mesmo valor
							}else{

										// Increase the Compensator
										compensar_fobj = compensar_fobj * 10;
										acumulador_cont = acumulador_cont + compensar_fobj;
//										cout << endl << " COMP: " + convertValue.convertDoubleString(compensar_fobj) << endl;
//										cout << " ACU_COMP: " + convertValue.convertDoubleString(acumulador_cont) << endl;

										// Atualiza Função Candidata para uma nova especificação, Considerando Compensador
										experiment->setFcCurrent(experiment->fc_current - compensar_fobj);

										// Incrementa Log
										v_log++;

										// Gera nova Especificação com nova Função Candidata (Aqui não incrementa a precisão)
									  	generatefilesAUX.create_specification_CEGIO_F(experiment);   	// Gerar Especificação


							}

					}


  			} // Fim While Interno

  			experiment->setLimitSpaceConvex(1);

			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.00001;

			// Gera nova Especificação com nova Função Candidata
		  	generatefilesAUX.create_specification_CEGIO_F(experiment);   	// Gerar Especificação

	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString(experiment->getFcCurrent()) << endl;
    cout << "####################################" << endl ;

}

