void Execution::run_CEGIO_G(Setup* experiment) {

	//cout <<  "run_CEGIO_G" << endl;

	//	Configuração do Experimento
	//=================================
	cout << endl;
	cout << " Configuration Optimization" << endl;
	cout << endl;
	cout << "     Function: " + experiment->getNameFunction()<< endl;
	cout << "     Algorithm: CEGIO-G" << endl;
	cout << endl;

	//	Ajuste de Variáveis
	//=================================
	experiment->setPrecisionCurrent(1);
	int precisionLoop = pow(10, experiment->getPrecisionTest());
	string command = "";
	bool stay_precision = true;
	int v_log = 1;
	string v_log_CE;

	float solutionReal;

	float compensar_fobj =  0.0001;
	float acumulador_cont = 0.0;
	int using_comp = 0;


	float vet_solutions[10];
	int cont_solutio = 0;

    experiment->setFcCurrent( convertValue.convertStringDouble(experiment->getFcStart()) );
    experiment->setFcCurrentString( experiment->getFcStart() );

  	generatefilesAUX.create_f(experiment);			// Gerar Arquivo C para calcular Mínimo
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());

//  	generatefilesAUX.create_specification_CEGIO_G(experiment);   	// Gerar Especificação

//  	precisionLoop = -1;

  	// Loop de Otimização
	//=================================
  	while(experiment->getPrecisionCurrent() <= precisionLoop)
  	{

  			cout << endl << "### Precisão Atual " + convertValue.convertDoubleString(experiment->getPrecisionCurrent())<< endl;

  			// Verifica Precisão - While Interno
  			while( stay_precision )
  			{
			  		generatefilesAUX.create_specification_CEGIO_G(experiment);
					v_log_CE = "log_" + convertValue.convertDoubleString(v_log);
					v_log++;

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

					cout << "     ** ";
					cout << command << endl;
					system(command.c_str());

					tratar_contra_exemplo.take_CE(v_log_CE, experiment);

					if(experiment->getStatusCe() == 2){
							cout << "COUNTEREXAMPLE UNKNOWN" << endl;
							break;

					}else if(experiment->getStatusCe() == 1){

							vet_solutions[cont_solutio] = solutionReal;
							cont_solutio++;

							experiment->setFcCurrent(experiment->fc_current - 0.0001);
							stay_precision = false;


								if(experiment->getPrecisionCurrent() == 10){
									if(vet_solutions[0] == vet_solutions[1]){
										experiment->setPrecisionCurrent( precisionLoop );
									}
								}if(experiment->getPrecisionCurrent() == 100){
									if(vet_solutions[1] == vet_solutions[2]){
										experiment->setPrecisionCurrent( precisionLoop );
									}
								}else if(experiment->getPrecisionCurrent() == 1000 && using_comp == 1){
									if(vet_solutions[2] == vet_solutions[3]){
										experiment->setPrecisionCurrent( precisionLoop );
									}
								}


								stay_precision = false;
								compensar_fobj =  0.0001;
								acumulador_cont = 0.0;
								using_comp = 0;

							cout << "     ** Vai cancelar tudo" << endl;
							cout << "     ** Precisão 1: "<< vet_solutions[0] << endl;
							cout << "     ** Precisão 10: "<< vet_solutions[1] << endl;
							cout << "     ** Precisão 100: "<< vet_solutions[2] << endl;
							cout << "     ** Precisão 1000: "<< vet_solutions[3] << endl;

					}else{

							if( experiment->getFcFc() < experiment->getFcCurrent() ){

									solutionReal = experiment->getFcFc();

									experiment->setFcCurrent(experiment->getFcFc());

									cout <<  "f("+ convertValue.convertDoubleString(experiment->getX1Current()) +
							  								"," +
							  								convertValue.convertDoubleString(experiment->getX2Current()) +
							  								")="+
							  								convertValue.convertDoubleString(solutionReal) + " "<< endl;

									compensar_fobj =  0.0001;
									acumulador_cont = 0.0;
									using_comp = 0;

							}else{

									if(using_comp < 2){
										cout << "     ** Incremento Ajust: "<< using_comp << endl;
										using_comp++;
										acumulador_cont = acumulador_cont + compensar_fobj;
										experiment->setFcCurrent(experiment->fc_current - compensar_fobj);
									  	generatefilesAUX.create_specification_CEGIO_G(experiment);
										compensar_fobj = compensar_fobj * 10;
									}else{
										stay_precision = false;
										compensar_fobj =  0.0001;
										acumulador_cont = 0.0;
										using_comp = 0;
									}

							}

					}

  			} // Fim While Interno

			// Atualiza Precisão
			experiment->setPrecisionCurrent(experiment->getPrecisionCurrent() * 10);
			stay_precision = true;
			compensar_fobj =  0.0001;

	} // Fim While Externo

    cout << "####################################" << endl ;
    cout << " Global Minimum: " ;
    cout << "f(" + convertValue.convertDoubleString(experiment->getX1Current()) + "," + convertValue.convertDoubleString(experiment->getX2Current()) + ") = " + convertValue.convertDoubleString( solutionReal ) << endl;
    cout << "####################################" << endl ;

}

