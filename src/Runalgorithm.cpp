/*
 * Runalgorithm.cpp
 *
 *  Created on: 03/02/2017
 *      Author: higo
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <list>

#include "Set.h"
#include "Tcexamples.h"
#include "Runalgorithm.h"

using namespace std;

	Run_algorithm::Run_algorithm() {
		// TODO Auto-generated constructor stub
	}

	Run_algorithm::~Run_algorithm() {
		// TODO Auto-generated destructor stub
	}



	//****************************************************************************************************************************
	// Execution Management

	void Run_algorithm::execute_experiment(Set ex){

		ex.type_restrictions = 0;

		if(ex.mc == 1){														// 	ESBMC
			if(ex.alg == 1){												//	├─── GENERALIZED
				if(ex.solver == 1){ run_ESBMC_BOOLECTOR_G(ex); } else		//	│ 	 ├────── BOOLECTOR
				if(ex.solver == 2){ run_ESBMC_Z3_G(ex); } else				//	│	 ├────── Z3
				if(ex.solver == 3){ run_ESBMC_MATHSAT_G(ex); }				//	│	 └────── MATHSAT
																			//	│
			}else if(ex.alg == 2){											//  ├─── POSITIVE
				if(ex.solver == 1){ run_ESBMC_BOOLECTOR_S(ex); } else		//	│ 	 ├────── BOOLECTOR
				if(ex.solver == 2){ run_ESBMC_Z3_S(ex); } else				//	│	 ├────── Z3
				if(ex.solver == 3){ run_ESBMC_MATHSAT_S(ex); }				//	│	 └────── MATHSAT
																			//	│
			}else if(ex.alg == 3){											//	└─── CONVEX
				if(ex.solver == 1){ run_ESBMC_BOOLECTOR_C(ex); } else		//	 	 ├────── BOOLECTOR
				if(ex.solver == 2){ run_ESBMC_Z3_C(ex); } else				//		 ├────── Z3
				if(ex.solver == 3){ run_ESBMC_MATHSAT_C(ex); }				//		 └────── MATHSAT

			}
		}else if(ex.mc == 2){												// 	CBMC
			if(ex.alg == 1){												//	├─── GENERALIZED
				if(ex.solver == 4){run_CBMC_MINISAT_G(ex); }				//	│	 └────── MATHSAT
			}else if(ex.alg == 2){											//  ├─── POSITIVE
				if(ex.solver == 4){ run_CBMC_MINISAT_S(ex); }				//	│	 └────── MATHSAT
			} else if(ex.alg == 3){											//	└─── CONVEX
				if(ex.solver == 4){ run_CBMC_MINISAT_C(ex); }				//		 └────── MATHSAT
			}
		}else if(ex.mc == 3){												//	cpachecker

			if(ex.solver == 1){												//	├─── GENERALIZED

			}else if(ex.solver == 2){

			}else if(ex.solver == 3){

			}
		}
	}


	//****************************************************************************************************************************
	//ESBMC GENERALIZED

	void Run_algorithm::run_ESBMC_BOOLECTOR_G(Set ex){

		cout << "#############################################" << endl;
		cout << "#     ESBMC - Boolector - Alg Generalized   #" << endl;
		cout << "#############################################" << endl;

		// Variáveis de Manipulação com Objetos e funções
			Generate_files gerar_arquivos;
			Tcexamples tratar_contra_exemplo;
			Tcexamples list_fobj;
			list<Tcexamples> conjunto_fobj;

		// Variáveis de Ajustes
			string command = "";
			int p = 1;
			bool manter_precisao = true;
			bool minimo_existente_maior = false;
			string new_fiS;
			float compensar_fobj;
			string compensar_fobjS;
			int v_log = 1;
			string v_logS;

			ex.restrictions = generate_assumes(ex,p);

			gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);		//
			command  = "gcc " + ex.name_function + ".c -o value_min";						//  Cria o binário do função
			system(command.c_str());														//

			cout << endl << "            Boot Value: " + ex.l_sup << endl;
																																							//
			gerar_arquivos.create_mi_ESBMC_G_Boolector(ex, p); 	// Cria o primeiro arquivo min

											//
			compensar_fobj =  0.00001;		//	Definir compensador padrão
											//
																																		//

			while( p<=1000 ){

				cout << endl << " ******************************** " << endl ;

				while( manter_precisao ){
																									//
					v_logS = "log_" + convertDoubleString(v_log);									// Incrementa Log
																									//
					command  = "./esbmc min_" + ex.name_function + ".c --boolector > " + v_logS;	// Executar Verificação
					system(command.c_str());														//

																			//
					tratar_contra_exemplo.take_CE_ESBMC_Boolector(v_logS,p);		//	Busca corretamente o estado da verificação (Sucesso ou Falha)
																			//	Busca valores de x1, x2 e fobj


					if(tratar_contra_exemplo._verification == 1){						//	Verificação Sucesso
						v_log++;
						manter_precisao = false;										//
						break;															//	Parar while Interno
																						//	Muda de Precisão
					}else{

						for (list<Tcexamples>::const_iterator it = conjunto_fobj.begin(); it != conjunto_fobj.end(); ++it){		//
							if((  convertStringDouble(tratar_contra_exemplo._fjob) >= convertStringDouble((*it)._fjob)) ){		// Verifica se Já existe esse Fobj igual
								minimo_existente_maior = true;																	// Verifica se esse Fobj é maior que os outros encontrados
							}																									//
						}

						if(minimo_existente_maior){														// Se verificaou valor

							compensar_fobj = compensar_fobj * 10;										// Aumenta o Compensador
							minimo_existente_maior = false;												// 	Resetar condição deste erro, deste if
							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);			// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;

							gerar_arquivos.create_mi_ESBMC_G_Boolector(ex, p); 							// Cria arquivos min considerando novo F_I com novo compensador

						}else{

							ex.fobj_current /*fobj_valido*/ = tratar_contra_exemplo._fjob;												// Atualiza ultimo valor mínimo Válido
							v_log++;																				// Incrmenta Log
							conjunto_fobj.push_front(tratar_contra_exemplo);										// Salva na Lista de Mínimos

							cout << "	f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;

							gerar_arquivos.create_mi_ESBMC_G_Boolector(ex, p); 	// Cria os outros arquivos min
						}

					}
						//
				}		//	Fim While Interno
						//

				p = p * 10;
				manter_precisao = true;
				compensar_fobj =  0.00001;				// Reset compensator

				new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
				ex.fobj_current = new_fiS;

				gerar_arquivos.create_mi_ESBMC_G_Boolector(ex, p);

			}

			cout << "####################################" << endl ;
			cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

		}

	void Run_algorithm::run_ESBMC_Z3_G(Set ex){

		cout << "###########################################" << endl;
		cout << "#     ESBMC - Z3 - Alg Generalized        #" << endl;
		cout << "###########################################" << endl;

		// Variáveis de Manipulação com Objetos e funções
			Generate_files gerar_arquivos;
			Tcexamples tratar_contra_exemplo;
			Tcexamples list_fobj;
			list<Tcexamples> conjunto_fobj;

		// Variáveis de Ajustes
			string command = "";
			int p = 1;
			bool manter_precisao = true;
			bool minimo_existente_maior = false;
			string new_fiS;
			float compensar_fobj;
			string compensar_fobjS;
			int v_log = 1;
			string v_logS;

			ex.restrictions = generate_assumes(ex,p);

			gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);		//
			command  = "gcc " + ex.name_function + ".c -o value_min";						//  Cria o binário do função
			system(command.c_str());														//

			cout << endl << "            Boot Value: " + ex.l_sup << endl;
																																							//
			gerar_arquivos.create_mi_ESBMC_G_Z3(ex, p); 	// Cria o primeiro arquivo min

											//
			compensar_fobj =  0.00001;		//	Definir compensador padrão
											//
																																		//

			while( p<=1000 ){

				cout << endl << " ******************************** " << endl ;

				while( manter_precisao ){
																									//
					v_logS = "log_" + convertDoubleString(v_log);									// Incrementa Log
																									//
					command  = "./esbmc min_" + ex.name_function + ".c --z3 > " + v_logS;	// Executar Verificação
					system(command.c_str());														//

																			//
					tratar_contra_exemplo.take_CE_ESBMC_Z3(v_logS,p);		//	Busca corretamente o estado da verificação (Sucesso ou Falha)
																			//	Busca valores de x1, x2 e fobj


					if(tratar_contra_exemplo._verification == 1){						//	Verificação Sucesso
						v_log++;
						manter_precisao = false;										//
						break;															//	Parar while Interno
																						//	Muda de Precisão
					}else{

						for (list<Tcexamples>::const_iterator it = conjunto_fobj.begin(); it != conjunto_fobj.end(); ++it){		//
							if((  convertStringDouble(tratar_contra_exemplo._fjob) >= convertStringDouble((*it)._fjob)) ){		// Verifica se Já existe esse Fobj igual
								minimo_existente_maior = true;																	// Verifica se esse Fobj é maior que os outros encontrados
							}																									//
						}

						if(minimo_existente_maior){														// Se verificaou valor

							compensar_fobj = compensar_fobj * 10;										// Aumenta o Compensador
							minimo_existente_maior = false;												// 	Resetar condição deste erro, deste if
							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);			// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;

							gerar_arquivos.create_mi_ESBMC_G_Z3(ex, p); 							// Cria arquivos min considerando novo F_I com novo compensador

						}else{

							ex.fobj_current /*fobj_valido*/ = tratar_contra_exemplo._fjob;												// Atualiza ultimo valor mínimo Válido
							v_log++;																				// Incrmenta Log
							conjunto_fobj.push_front(tratar_contra_exemplo);										// Salva na Lista de Mínimos

							cout << "	f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;

							gerar_arquivos.create_mi_ESBMC_G_Z3(ex, p); 	// Cria os outros arquivos min
						}

					}
						//
				}		//	Fim While Interno
						//

				p = p * 10;
				manter_precisao = true;
				compensar_fobj =  0.00001;				// Reset compensator

				new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
				ex.fobj_current = new_fiS;

				gerar_arquivos.create_mi_ESBMC_G_Z3(ex, p);

			}

			cout << "####################################" << endl ;
			cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

		}

	void Run_algorithm::run_ESBMC_MATHSAT_G(Set ex){

		cout << "#############################################" << endl;
		cout << "#     ESBMC - Mathsat - Alg Generalized     #" << endl;
		cout << "#############################################" << endl;

	// Variáveis de Manipulação com Objetos e funções
		Generate_files gerar_arquivos;
		Tcexamples tratar_contra_exemplo;
		Tcexamples list_fobj;
		list<Tcexamples> conjunto_fobj;

	// Variáveis de Ajustes
		string command = "";
		int p = 1;
		bool manter_precisao = true;
		bool minimo_existente_maior = false;
		string new_fiS;
		float compensar_fobj;
		string compensar_fobjS;
		int v_log = 1;
		string v_logS;

		ex.restrictions = generate_assumes(ex,p);

		gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);		//
		command  = "gcc " + ex.name_function + ".c -o value_min";						//  Cria o binário do função
		system(command.c_str());														//

		cout << endl << "            Boot Value: " + ex.l_sup << endl;
																																						//
		gerar_arquivos.create_mi_ESBMC_G_Mathsat(ex, p); 	// Cria o primeiro arquivo min

										//
		compensar_fobj =  0.00001;		//	Definir compensador padrão
										//

		while( p<=1000 ){

			cout << endl << " ******************************** " << endl ;

			//break;

			while( manter_precisao ){
																								//
				v_logS = "log_" + convertDoubleString(v_log);									// Incrementa Log
																								//

				cout << "Chamou MC" << endl;
				command  = "./esbmc min_" + ex.name_function + ".c --floatbv --mathsat > " + v_logS;	// Executar Verificação
				system(command.c_str());														//

																			//
				tratar_contra_exemplo.take_CE_ESBMC_Mathsat(v_logS,p);		//	Busca corretamente o estado da verificação (Sucesso ou Falha)
																			//	Busca valores de x1, x2 e fobj

																					//
				if(tratar_contra_exemplo._verification == 1){						//	Verificação Sucesso
					v_log++;
					manter_precisao = false;										//
					break;															//	Parar while Interno
																					//	Muda de Precisão
				}else{

					for (list<Tcexamples>::const_iterator it = conjunto_fobj.begin(); it != conjunto_fobj.end(); ++it){		//
						if((  convertStringDouble(tratar_contra_exemplo._fjob) >= convertStringDouble((*it)._fjob)) ){		// Verifica se Já existe esse Fobj igual
							minimo_existente_maior = true;																	// Verifica se esse Fobj é maior que os outros encontrados
						}																									//
					}

					if(minimo_existente_maior){														// Se verificaou valor

						compensar_fobj = compensar_fobj * 10;										// Aumenta o Compensador
						minimo_existente_maior = false;												// 	Resetar condição deste erro, deste if
						new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);			// Generates the new F_I Compensated
						ex.fobj_current = new_fiS;

						gerar_arquivos.create_mi_ESBMC_G_Mathsat(ex, p); 							// Cria arquivos min considerando novo F_I com novo compensador

					}else{

						ex.fobj_current /*fobj_valido*/ = tratar_contra_exemplo._fjob;												// Atualiza ultimo valor mínimo Válido
						v_log++;																				// Incrmenta Log
						conjunto_fobj.push_front(tratar_contra_exemplo);										// Salva na Lista de Mínimos

						cout << "	f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

						new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
						ex.fobj_current = new_fiS;

						gerar_arquivos.create_mi_ESBMC_G_Mathsat(ex, p); 	// Cria os outros arquivos min
					}

				}

			}		//	Fim While Interno

			p = p * 10;
			manter_precisao = true;
			compensar_fobj =  0.00001;				// Reset compensator

			new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
			ex.fobj_current = new_fiS;

			gerar_arquivos.create_mi_ESBMC_G_Mathsat(ex, p);

		}

		cout << "####################################" << endl ;
		cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

	}

	//****************************************************************************************************************************
	//ESBMC POSITIVE

	void Run_algorithm::run_ESBMC_BOOLECTOR_S(Set ex){

		cout << "#############################################" << endl;
		cout << "#     ESBMC - Alg Positive - Boolector      #" << endl;
		cout << "#############################################" << endl;

		// Variáveis de Manipulação com Objetos e funções
			Generate_files gerar_arquivos;
			Tcexamples tratar_contra_exemplo;
			Tcexamples list_fobj;
			list<Tcexamples> conjunto_fobj;

		// Variáveis de Ajustes
			string command = "";
			int p = 1;
			bool manter_precisao = true;
			bool minimo_existente_maior = false;
			string new_fiS;
			float compensar_fobj;
			string compensar_fobjS;
			int v_log = 1;
			string v_logS;

			ex.restrictions = generate_assumes(ex,p);

			gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);		//
			command  = "gcc " + ex.name_function + ".c -o value_min";						//  Cria o binário do função
			system(command.c_str());														//

			cout << endl << "            Boot Value: " + ex.l_sup << endl;
																																							//
			gerar_arquivos.create_mi_ESBMC_S_Boolector(ex, p); 	// Cria o primeiro arquivo min

											//
			compensar_fobj =  0.00001;		//	Definir compensador padrão
											//
			int cont=0, cont2=0;

			while( p<=10000 /*&& cont<=0*/){

				cout << endl << " ******************************** " << endl ;

				while( manter_precisao  /*&& cont2<=0 */){
																									//
					v_logS = "log_" + convertDoubleString(v_log);									// Incrementa Log
																									//

																											//
					command  = "./esbmc min_" + ex.name_function + ".c --boolector > " + v_logS;	// Executar Verificação
					system(command.c_str());																//

																				//
					tratar_contra_exemplo.take_CE_ESBMC_Boolector(v_logS,p);		//	Busca corretamente o estado da verificação (Sucesso ou Falha)
																				//	Busca valores de x1, x2 e fobj

																						//
					if(tratar_contra_exemplo._verification == 1){						//	Verificação Sucesso
						v_log++;
						manter_precisao = false;										//
						break;															//	Parar while Interno
																						//	Muda de Precisão
					}else{

						for (list<Tcexamples>::const_iterator it = conjunto_fobj.begin(); it != conjunto_fobj.end(); ++it){		//
							if((  convertStringDouble(tratar_contra_exemplo._fjob) >= convertStringDouble((*it)._fjob)) ){		// Verifica se Já existe esse Fobj igual
								minimo_existente_maior = true;																	// Verifica se esse Fobj é maior que os outros encontrados
							}																									//
						}

						if(minimo_existente_maior){														// Se verificaou valor

							compensar_fobj = compensar_fobj * 10;										// Aumenta o Compensador
							minimo_existente_maior = false;												// 	Resetar condição deste erro, deste if

							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);			// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;
							gerar_arquivos.create_mi_ESBMC_S_Boolector(ex, p); 							// Cria arquivos min considerando novo F_I com novo compensador


						}else{

							ex.fobj_current /*fobj_valido*/ = tratar_contra_exemplo._fjob;												// Atualiza ultimo valor mínimo Válido
							v_log++;																				// Incrmenta Log
							conjunto_fobj.push_front(tratar_contra_exemplo);										// Salva na Lista de Mínimos

							cout << "	f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;
							gerar_arquivos.create_mi_ESBMC_S_Boolector(ex, p); 	// Cria os outros arquivos min
						}

					}

					cont++;
				}		//	Fim While Interno

				cont2++;

				p = p * 10;
				manter_precisao = true;
				compensar_fobj =  0.00001;				// Reset compensator

				new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
				ex.fobj_current = new_fiS;
				gerar_arquivos.create_mi_ESBMC_S_Boolector(ex, p);

			}

			cout << "####################################" << endl ;
			cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

	}

	void Run_algorithm::run_ESBMC_Z3_S(Set ex){

		cout << "#############################################" << endl;
		cout << "#     ESBMC - Alg Positive - Z3             #" << endl;
		cout << "#############################################" << endl;

		// Variáveis de Manipulação com Objetos e funções
			Generate_files gerar_arquivos;
			Tcexamples tratar_contra_exemplo;
			Tcexamples list_fobj;
			list<Tcexamples> conjunto_fobj;

		// Variáveis de Ajustes
			string command = "";
			int p = 1;
			bool manter_precisao = true;
			bool minimo_existente_maior = false;
			string new_fiS;
			float compensar_fobj;
			string compensar_fobjS;
			int v_log = 1;
			string v_logS;

			ex.restrictions = generate_assumes(ex,p);

			gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);		//
			command  = "gcc " + ex.name_function + ".c -o value_min";						//  Cria o binário do função
			system(command.c_str());														//

			cout << endl << "            Boot Value: " + ex.l_sup << endl;
																																							//
			gerar_arquivos.create_mi_ESBMC_S_Z3(ex, p); 	// Cria o primeiro arquivo min

											//
			compensar_fobj =  0.00001;		//	Definir compensador padrão
											//
			int cont=0, cont2=0;

			while( p<=10000 /*&& cont<=0*/){

				cout << endl << " ******************************** " << endl ;

				while( manter_precisao  /*&& cont2<=0 */){
																									//
					v_logS = "log_" + convertDoubleString(v_log);									// Incrementa Log
																									//

																											//
					command  = "./esbmc min_" + ex.name_function + ".c --z3 > " + v_logS;	// Executar Verificação
					system(command.c_str());																//

																				//
					tratar_contra_exemplo.take_CE_ESBMC_Z3(v_logS,p);		//	Busca corretamente o estado da verificação (Sucesso ou Falha)
																				//	Busca valores de x1, x2 e fobj

																						//
					if(tratar_contra_exemplo._verification == 1){						//	Verificação Sucesso
						v_log++;
						manter_precisao = false;										//
						break;															//	Parar while Interno
																						//	Muda de Precisão
					}else{

						for (list<Tcexamples>::const_iterator it = conjunto_fobj.begin(); it != conjunto_fobj.end(); ++it){		//
							if((  convertStringDouble(tratar_contra_exemplo._fjob) >= convertStringDouble((*it)._fjob)) ){		// Verifica se Já existe esse Fobj igual
								minimo_existente_maior = true;																	// Verifica se esse Fobj é maior que os outros encontrados
							}																									//
						}

						if(minimo_existente_maior){														// Se verificaou valor

							compensar_fobj = compensar_fobj * 10;										// Aumenta o Compensador
							minimo_existente_maior = false;												// 	Resetar condição deste erro, deste if

							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);			// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;
							gerar_arquivos.create_mi_ESBMC_S_Z3(ex, p); 							// Cria arquivos min considerando novo F_I com novo compensador


						}else{

							ex.fobj_current /*fobj_valido*/ = tratar_contra_exemplo._fjob;												// Atualiza ultimo valor mínimo Válido
							v_log++;																				// Incrmenta Log
							conjunto_fobj.push_front(tratar_contra_exemplo);										// Salva na Lista de Mínimos

							cout << "	f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;
							gerar_arquivos.create_mi_ESBMC_S_Z3(ex, p); 	// Cria os outros arquivos min
						}

					}

					cont++;
				}		//	Fim While Interno

				cont2++;

				p = p * 10;
				manter_precisao = true;
				compensar_fobj =  0.00001;				// Reset compensator

				new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
				ex.fobj_current = new_fiS;
				gerar_arquivos.create_mi_ESBMC_S_Z3(ex, p);

			}

			cout << "####################################" << endl ;
			cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

	}

	void Run_algorithm::run_ESBMC_MATHSAT_S(Set ex){

		cout << "#############################################" << endl;
		cout << "#     ESBMC - Mathsat - Alg Simplified      #" << endl;
		cout << "#############################################" << endl;

		// Variáveis de Manipulação com Objetos e funções
			Generate_files gerar_arquivos;
			Tcexamples tratar_contra_exemplo;
			Tcexamples list_fobj;
			list<Tcexamples> conjunto_fobj;

		// Variáveis de Ajustes
			string command = "";
			int p = 1;
			bool manter_precisao = true;
			bool minimo_existente_maior = false;
			string new_fiS;
			float compensar_fobj;
			string compensar_fobjS;
			int v_log = 1;
			string v_logS;

			ex.restrictions = generate_assumes(ex,p);

			gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);		//
			command  = "gcc " + ex.name_function + ".c -o value_min";						//  Cria o binário do função
			system(command.c_str());														//

			cout << endl << "            Boot Value: " + ex.l_sup << endl;
																																							//
			gerar_arquivos.create_mi_ESBMC_S_Mathsat(ex, p); 	// Cria o primeiro arquivo min

											//
			compensar_fobj =  0.00001;		//	Definir compensador padrão
											//
			int cont=0, cont2=0;

			while( p<=10000 /*&& cont<=0*/){

				cout << endl << " ******************************** " << endl ;

				while( manter_precisao  /*&& cont2<=0 */){
																									//
					v_logS = "log_" + convertDoubleString(v_log);									// Incrementa Log
																									//

																											//
					command  = "./esbmc min_" + ex.name_function + ".c --mathsat --floatbv > " + v_logS;	// Executar Verificação
					system(command.c_str());																//

																				//
					tratar_contra_exemplo.take_CE_ESBMC_Mathsat(v_logS,p);		//	Busca corretamente o estado da verificação (Sucesso ou Falha)
																				//	Busca valores de x1, x2 e fobj

																						//
					if(tratar_contra_exemplo._verification == 1){						//	Verificação Sucesso
						v_log++;
						manter_precisao = false;										//
						break;															//	Parar while Interno
																						//	Muda de Precisão
					}else{

						for (list<Tcexamples>::const_iterator it = conjunto_fobj.begin(); it != conjunto_fobj.end(); ++it){		//
							if((  convertStringDouble(tratar_contra_exemplo._fjob) >= convertStringDouble((*it)._fjob)) ){		// Verifica se Já existe esse Fobj igual
								minimo_existente_maior = true;																	// Verifica se esse Fobj é maior que os outros encontrados
							}																									//
						}

						if(minimo_existente_maior){														// Se verificaou valor

							compensar_fobj = compensar_fobj * 10;										// Aumenta o Compensador
							minimo_existente_maior = false;												// 	Resetar condição deste erro, deste if

							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);			// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;
							gerar_arquivos.create_mi_ESBMC_S_Mathsat(ex, p); 							// Cria arquivos min considerando novo F_I com novo compensador


						}else{

							ex.fobj_current /*fobj_valido*/ = tratar_contra_exemplo._fjob;												// Atualiza ultimo valor mínimo Válido
							v_log++;																				// Incrmenta Log
							conjunto_fobj.push_front(tratar_contra_exemplo);										// Salva na Lista de Mínimos

							cout << "	f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;
							gerar_arquivos.create_mi_ESBMC_S_Mathsat(ex, p); 	// Cria os outros arquivos min
						}

					}

					cont++;
				}		//	Fim While Interno

				cont2++;

				p = p * 10;
				manter_precisao = true;
				compensar_fobj =  0.00001;				// Reset compensator

				new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
				ex.fobj_current = new_fiS;
				gerar_arquivos.create_mi_ESBMC_S_Mathsat(ex, p);

			}

			cout << "####################################" << endl ;
			cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

	}


	//****************************************************************************************************************************
	//ESBMC CONVEX

	void Run_algorithm::run_ESBMC_BOOLECTOR_C(Set ex){

		cout << "###########################################" << endl;
		cout << "#     ESBMC - BOOLECTOR - Alg CONVEX      #" << endl;
		cout << "###########################################" << endl;

		// Variáveis de Manipulação com Objetos e funções
			Generate_files gerar_arquivos;
			Tcexamples tratar_contra_exemplo;
			Tcexamples list_fobj;
			list<Tcexamples> conjunto_fobj;

		// Variáveis de Ajustes
			string command = "";
			int p = 1;
			bool manter_precisao = true;
			bool minimo_existente_maior = false;
			string new_fiS;
			float compensar_fobj;
			string compensar_fobjS;
			int v_log = 1;
			string v_logS;

			gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);		//
			command  = "gcc " + ex.name_function + ".c -o value_min";						//  Cria o binário do função
			system(command.c_str());														//

			ex.type_restrictions = 0;
			ex.restrictions = generate_assumes(ex, p);																																							//
			gerar_arquivos.create_mi_ESBMC_C_Boolector(ex, p); 		// Cria o primeiro arquivo min
			compensar_fobj =  0.00001;								//	Definir compensador padrão

			cout << endl << "            Boot Value: " + ex.l_sup << endl;


			while( p <= 1000 ){

				cout << endl << " ******************************** " << endl ;

				while( manter_precisao ){

					v_logS = "log_" + convertDoubleString(v_log);									// Incrementa Log

					command  = "./esbmc min_" + ex.name_function + ".c --boolector > " + v_logS;	// Executar Verificação
					system(command.c_str());

					tratar_contra_exemplo.take_CE_ESBMC_Boolector(v_logS,p);	//	Busca corretamente o estado da verificação (Sucesso ou Falha)
																				//	Busca valores de x1, x2 e fobj

					if(tratar_contra_exemplo._verification == 1){				//	Verificação Sucesso
						v_log++;
						manter_precisao = false;								//
						break;													//	Parar while Interno
																				//	Muda de Precisão
					}else{

						for (list<Tcexamples>::const_iterator it = conjunto_fobj.begin(); it != conjunto_fobj.end(); ++it){		//
							if((  convertStringDouble(tratar_contra_exemplo._fjob) >= convertStringDouble((*it)._fjob)) ){		// Verifica se Já existe esse Fobj igual
								minimo_existente_maior = true;																	// Verifica se esse Fobj é maior que os outros encontrados
							}																									//
						}

						if(minimo_existente_maior){														// Se verificaou valor

							compensar_fobj = compensar_fobj * 10;										// Aumenta o Compensador
							minimo_existente_maior = false;												// 	Resetar condição deste erro, deste if
							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);		// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;
							gerar_arquivos.create_mi_ESBMC_C_Boolector(ex, p);
						}else{

							ex.fobj_current = tratar_contra_exemplo._fjob;											// Atualiza ultimo valor mínimo Válido
							v_log++;																				// Incrmenta Log
							conjunto_fobj.push_front(tratar_contra_exemplo);										// Salva na Lista de Mínimos

							cout << "	f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

							new_fiS = ex.fobj_current + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;

							gerar_arquivos.create_mi_ESBMC_C_Boolector(ex, p); 	// Cria os outros arquivos min

						}

					}

						//
				}		//	Fim While Interno
						//
				ex.type_restrictions = 1;

				p = p * 10;
				manter_precisao = true;

				compensar_fobj =  0.00001;				// Reset compensator

				new_fiS = ex.fobj_current + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
				ex.fobj_current = new_fiS;

				ex._x1 = convertStringDouble(tratar_contra_exemplo._x1);
				ex._x2 = convertStringDouble(tratar_contra_exemplo._x2);

				ex.restrictions = generate_assumes(ex, p);

				gerar_arquivos.create_mi_ESBMC_C_Boolector(ex, p); 	// Cria os outros arquivos min
			}

			cout << "####################################" << endl ;
			cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

	}

	void Run_algorithm::run_ESBMC_Z3_C(Set ex){

		// Variáveis de Manipulação com Objetos e funções
			Generate_files gerar_arquivos;
			Tcexamples tratar_contra_exemplo;
			Tcexamples list_fobj;
			list<Tcexamples> conjunto_fobj;

		// Variáveis de Ajustes
			string command = "";
			int p = 1;
			bool manter_precisao = true;
			bool minimo_existente_maior = false;
			string new_fiS;
			float compensar_fobj;
			string compensar_fobjS;
			int v_log = 1;
			string v_logS;

			gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);		//
			command  = "gcc " + ex.name_function + ".c -o value_min";						//  Cria o binário do função
			system(command.c_str());														//

			ex.type_restrictions = 0;
			ex.restrictions = generate_assumes(ex, p);																																							//
			gerar_arquivos.create_mi_ESBMC_C_Z3(ex, p); 		// Cria o primeiro arquivo min
			compensar_fobj =  0.00001;							//	Definir compensador padrão

			cout << endl << "            Boot Value: " + ex.l_sup << endl;


			while( p <= 1000 ){

				cout << endl << " ******************************** " << endl ;

				while( manter_precisao ){

					v_logS = "log_" + convertDoubleString(v_log);									// Incrementa Log

					command  = "./esbmc min_" + ex.name_function + ".c --z3 > " + v_logS;	// Executar Verificação
					system(command.c_str());

					tratar_contra_exemplo.take_CE_ESBMC_Z3(v_logS,p);		//	Busca corretamente o estado da verificação (Sucesso ou Falha)
																				//	Busca valores de x1, x2 e fobj

					if(tratar_contra_exemplo._verification == 1){						//	Verificação Sucesso
						v_log++;
						manter_precisao = false;										//
						break;															//	Parar while Interno
																						//	Muda de Precisão
					}else{

						for (list<Tcexamples>::const_iterator it = conjunto_fobj.begin(); it != conjunto_fobj.end(); ++it){		//
							if((  convertStringDouble(tratar_contra_exemplo._fjob) >= convertStringDouble((*it)._fjob)) ){		// Verifica se Já existe esse Fobj igual
								minimo_existente_maior = true;																	// Verifica se esse Fobj é maior que os outros encontrados
							}																									//
						}

						if(minimo_existente_maior){														// Se verificaou valor

							compensar_fobj = compensar_fobj * 10;										// Aumenta o Compensador
							minimo_existente_maior = false;												// 	Resetar condição deste erro, deste if
							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);		// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;
							gerar_arquivos.create_mi_ESBMC_C_Z3(ex, p);
						}else{

							ex.fobj_current = tratar_contra_exemplo._fjob;												// Atualiza ultimo valor mínimo Válido
							v_log++;																				// Incrmenta Log
							conjunto_fobj.push_front(tratar_contra_exemplo);										// Salva na Lista de Mínimos

							cout << "	f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

							new_fiS = ex.fobj_current + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;

							gerar_arquivos.create_mi_ESBMC_C_Z3(ex, p); 	// Cria os outros arquivos min

						}

					}

						//
				}		//	Fim While Interno
						//
				ex.type_restrictions = 1;

				p = p * 10;
				manter_precisao = true;

				compensar_fobj =  0.00001;				// Reset compensator

				new_fiS = ex.fobj_current + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
				ex.fobj_current = new_fiS;

				ex._x1 = convertStringDouble(tratar_contra_exemplo._x1);
				ex._x2 = convertStringDouble(tratar_contra_exemplo._x2);

				ex.restrictions = generate_assumes(ex, p);
				gerar_arquivos.create_mi_ESBMC_C_Z3(ex, p); 	// Cria os outros arquivos min
			}

			cout << "####################################" << endl ;
			cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

		}



	void Run_algorithm::run_ESBMC_MATHSAT_C(Set ex){

		cout << "###########################################" << endl;
		cout << "#     ESBMC - MATHSAT - Alg CONVEX        #" << endl;
		cout << "###########################################" << endl;

		// Variáveis de Manipulação com Objetos e funções
			Generate_files gerar_arquivos;
			Tcexamples tratar_contra_exemplo;
			Tcexamples list_fobj;
			list<Tcexamples> conjunto_fobj;

		// Variáveis de Ajustes
			string command = "";
			int p = 1;
			bool manter_precisao = true;
			bool minimo_existente_maior = false;
			string new_fiS;
			float compensar_fobj;
			string compensar_fobjS;
			int v_log = 1;
			string v_logS;

			gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);		//
			command  = "gcc " + ex.name_function + ".c -o value_min";						//  Cria o binário do função
			system(command.c_str());														//

			ex.type_restrictions = 0;
			ex.restrictions = generate_assumes(ex, p);																																							//
			gerar_arquivos.create_mi_ESBMC_C_Mathsat(ex, p); 		// Cria o primeiro arquivo min
			compensar_fobj =  0.00001;							//	Definir compensador padrão

			cout << endl << "            Boot Value: " + ex.l_sup << endl;


			while( p <= 1000 ){

				cout << endl << " ******************************** " << endl ;

				while( manter_precisao ){

					v_logS = "log_" + convertDoubleString(v_log);									// Incrementa Log

					command  = "./esbmc min_" + ex.name_function + ".c --mathsat --floatbv > " + v_logS;	// Executar Verificação
					system(command.c_str());

					tratar_contra_exemplo.take_CE_ESBMC_Mathsat(v_logS,p);		//	Busca corretamente o estado da verificação (Sucesso ou Falha)
																				//	Busca valores de x1, x2 e fobj

					if(tratar_contra_exemplo._verification == 1){						//	Verificação Sucesso
						v_log++;
						manter_precisao = false;										//
						break;															//	Parar while Interno
																						//	Muda de Precisão
					}else{

						for (list<Tcexamples>::const_iterator it = conjunto_fobj.begin(); it != conjunto_fobj.end(); ++it){		//
							if((  convertStringDouble(tratar_contra_exemplo._fjob) >= convertStringDouble((*it)._fjob)) ){		// Verifica se Já existe esse Fobj igual
								minimo_existente_maior = true;																	// Verifica se esse Fobj é maior que os outros encontrados
							}																									//
						}

						if(minimo_existente_maior){														// Se verificaou valor

							compensar_fobj = compensar_fobj * 10;										// Aumenta o Compensador
							minimo_existente_maior = false;												// 	Resetar condição deste erro, deste if
							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);		// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;
							gerar_arquivos.create_mi_ESBMC_C_Mathsat(ex, p);
						}else{

							ex.fobj_current = tratar_contra_exemplo._fjob;												// Atualiza ultimo valor mínimo Válido
							v_log++;																				// Incrmenta Log
							conjunto_fobj.push_front(tratar_contra_exemplo);										// Salva na Lista de Mínimos

							cout << "	f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

							new_fiS = ex.fobj_current + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;

							gerar_arquivos.create_mi_ESBMC_C_Mathsat(ex, p); 	// Cria os outros arquivos min

						}

					}

						//
				}		//	Fim While Interno
						//
				ex.type_restrictions = 1;

				p = p * 10;
				manter_precisao = true;

				compensar_fobj =  0.00001;				// Reset compensator

				new_fiS = ex.fobj_current + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
				ex.fobj_current = new_fiS;

				ex._x1 = convertStringDouble(tratar_contra_exemplo._x1);
				ex._x2 = convertStringDouble(tratar_contra_exemplo._x2);

				ex.restrictions = generate_assumes(ex, p);

				gerar_arquivos.create_mi_ESBMC_C_Mathsat(ex, p); 	// Cria os outros arquivos min
			}

			cout << "####################################" << endl ;
			cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

	}

	//****************************************************************************************************************************
	//CBMC GENERALIZED

	void Run_algorithm::run_CBMC_MINISAT_G(Set ex){

		cout << "#############################################" << endl;
		cout << "#     CBMC - Minisat - Alg Generalized      #" << endl;
		cout << "#############################################" << endl;

		// Variáveis de Manipulação com Objetos e funções
			Generate_files gerar_arquivos;
			Tcexamples tratar_contra_exemplo;
			Tcexamples list_fobj;
			list<Tcexamples> conjunto_fobj;

		// Variáveis de Ajustes
			string command = "";
			int p = 1;
			bool manter_precisao = true;
			bool minimo_existente_maior = false;
			string new_fiS;
			float compensar_fobj;
			string compensar_fobjS;
			int v_log = 1;
			string v_logS;

			ex.type_restrictions = 2;
			ex.restrictions = generate_assumes(ex,p);

			gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);		//
			command  = "gcc " + ex.name_function + ".c -o value_min";						//  Cria o binário do função
			system(command.c_str());														//

			cout << endl << "            Boot Value: " + ex.l_sup << endl;
																																							//
			gerar_arquivos.create_mi_CBMC_G_Minisat(ex, p); 	// Cria o primeiro arquivo min

											//
			compensar_fobj =  0.00001;		//	Definir compensador padrão
											//
																																		//

			while( p<=1000 ){

				cout << endl << " ******************************** " << endl ;

				while( manter_precisao ){
																									//
					v_logS = "log_" + convertDoubleString(v_log);									// Incrementa Log
																									//
					command  = "./cbmc min_" + ex.name_function + ".c  > " + v_logS + " 2>> " + v_logS;	// Executar Verificação
					system(command.c_str());														//

																			//
					tratar_contra_exemplo.take_CE_CBMC_Minisat(v_logS,p);		//	Busca corretamente o estado da verificação (Sucesso ou Falha)
																			//	Busca valores de x1, x2 e fobj


					if(tratar_contra_exemplo._verification == 1){						//	Verificação Sucesso
						v_log++;
						manter_precisao = false;										//
						break;															//	Parar while Interno
																						//	Muda de Precisão
					}else{

						for (list<Tcexamples>::const_iterator it = conjunto_fobj.begin(); it != conjunto_fobj.end(); ++it){		//
							if((  convertStringDouble(tratar_contra_exemplo._fjob) >= convertStringDouble((*it)._fjob)) ){		// Verifica se Já existe esse Fobj igual
								minimo_existente_maior = true;																	// Verifica se esse Fobj é maior que os outros encontrados
							}																									//
						}

						if(minimo_existente_maior){														// Se verificaou valor

							compensar_fobj = compensar_fobj * 10;										// Aumenta o Compensador
							minimo_existente_maior = false;												// 	Resetar condição deste erro, deste if
							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);			// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;

							gerar_arquivos.create_mi_CBMC_G_Minisat(ex, p); 							// Cria arquivos min considerando novo F_I com novo compensador

						}else{

							ex.fobj_current /*fobj_valido*/ = tratar_contra_exemplo._fjob;												// Atualiza ultimo valor mínimo Válido
							v_log++;																				// Incrmenta Log
							conjunto_fobj.push_front(tratar_contra_exemplo);										// Salva na Lista de Mínimos

							cout << "	f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;

							gerar_arquivos.create_mi_CBMC_G_Minisat(ex, p); 	// Cria os outros arquivos min
						}

					}

				}		//	Fim While Interno

				p = p * 10;
				manter_precisao = true;
				compensar_fobj =  0.00001;				// Reset compensator

				new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
				ex.fobj_current = new_fiS;

				gerar_arquivos.create_mi_CBMC_G_Minisat(ex, p);

			}

			cout << "####################################" << endl ;
			cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;
		}



	//****************************************************************************************************************************
	//CBMC POSITIVE

	void Run_algorithm::run_CBMC_MINISAT_S(Set ex){

		cout << "#############################################" << endl;
		cout << "#     CBMC - Minisat  - Alg Simplified      #" << endl;
		cout << "#############################################" << endl;

		// Variáveis de Manipulação com Objetos e funções
			Generate_files gerar_arquivos;
			Tcexamples tratar_contra_exemplo;
			Tcexamples list_fobj;
			list<Tcexamples> conjunto_fobj;

		// Variáveis de Ajustes
			string command = "";
			int p = 1;
			bool manter_precisao = true;
			bool minimo_existente_maior = false;
			string new_fiS;
			float compensar_fobj;
			string compensar_fobjS;
			int v_log = 1;
			string v_logS;

			ex.type_restrictions = 2;
			ex.restrictions = generate_assumes(ex,p);

			gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);		//
			command  = "gcc " + ex.name_function + ".c -o value_min";						//  Cria o binário do função
			system(command.c_str());														//

			cout << endl << "            Boot Value: " + ex.l_sup << endl;
																																							//
			gerar_arquivos.create_mi_CBMC_S_Minisat(ex, p); 	// Cria o primeiro arquivo min

			compensar_fobj =  0.00001;		//	Definir compensador padrão
			int cont=0, cont2=0;

			while( p<=10000 /*&& cont<=0*/){

				cout << endl << " ******************************** " << endl ;

				while( manter_precisao  /*&& cont2<=0 */){

					v_logS = "log_" + convertDoubleString(v_log);											// Incrementa Log

					command  = "./cbmc min_" + ex.name_function + ".c  > " + v_logS + " 2>> " + v_logS;		// Executar Verificação
					system(command.c_str());																//

					tratar_contra_exemplo.take_CE_CBMC_Minisat(v_logS,p);		//	Busca corretamente o estado da verificação (Sucesso ou Falha)
																					//	Busca valores de x1, x2 e fobj

																						//
					if(tratar_contra_exemplo._verification == 1){						//	Verificação Sucesso
						v_log++;
						manter_precisao = false;										//
						break;															//	Parar while Interno
																						//	Muda de Precisão
					}else{

						for (list<Tcexamples>::const_iterator it = conjunto_fobj.begin(); it != conjunto_fobj.end(); ++it){		//
							if((  convertStringDouble(tratar_contra_exemplo._fjob) >= convertStringDouble((*it)._fjob)) ){		// Verifica se Já existe esse Fobj igual
								minimo_existente_maior = true;																	// Verifica se esse Fobj é maior que os outros encontrados
							}																									//
						}

						if(minimo_existente_maior){														// Se verificaou valor

							compensar_fobj = compensar_fobj * 10;										// Aumenta o Compensador
							minimo_existente_maior = false;												// 	Resetar condição deste erro, deste if

							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);			// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;
							gerar_arquivos.create_mi_CBMC_S_Minisat(ex, p); 							// Cria arquivos min considerando novo F_I com novo compensador


						}else{

							ex.fobj_current /*fobj_valido*/ = tratar_contra_exemplo._fjob;												// Atualiza ultimo valor mínimo Válido
							v_log++;																				// Incrmenta Log
							conjunto_fobj.push_front(tratar_contra_exemplo);										// Salva na Lista de Mínimos

							cout << "	f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;
							gerar_arquivos.create_mi_CBMC_S_Minisat(ex, p); 	// Cria os outros arquivos min
						}

					}

					cont++;
				}		//	Fim While Interno

				cont2++;

				p = p * 10;
				manter_precisao = true;
				compensar_fobj =  0.00001;				// Reset compensator

				new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
				ex.fobj_current = new_fiS;
				gerar_arquivos.create_mi_CBMC_S_Minisat(ex, p);

			}

			cout << "####################################" << endl ;
			cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

	}

	//****************************************************************************************************************************
	//CBMC CONVEX

	void Run_algorithm::run_CBMC_MINISAT_C(Set ex){
		cout << "###########################################" << endl;
		cout << "#     CBMC - MINISAT - Alg CONVEX        #" << endl;
		cout << "###########################################" << endl;

		// Variáveis de Manipulação com Objetos e funções
			Generate_files gerar_arquivos;
			Tcexamples tratar_contra_exemplo;
			Tcexamples list_fobj;
			list<Tcexamples> conjunto_fobj;

		// Variáveis de Ajustes
			string command = "";
			int p = 1;
			bool manter_precisao = true;
			bool minimo_existente_maior = false;
			string new_fiS;
			float compensar_fobj;
			string compensar_fobjS;
			int v_log = 1;
			string v_logS;

			gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);		//
			command  = "gcc " + ex.name_function + ".c -o value_min";						//  Cria o binário do função
			system(command.c_str());

			ex.type_restrictions = 3;
			ex.restrictions = generate_assumes(ex, p);																																							//
			gerar_arquivos.create_mi_CBMC_C_Minisat(ex, p); 		// Cria o primeiro arquivo min
			compensar_fobj =  0.00001;								//	Definir compensador padrão

			cout << endl << "            Boot Value: " + ex.l_sup << endl;


			while( p <= 1000 ){

				cout << endl << " ******************************** " << endl ;

				while( manter_precisao ){

					v_logS = "log_" + convertDoubleString(v_log);									// Incrementa Log

					command  = "./cbmc min_" + ex.name_function + ".c  > " + v_logS + " 2>> " + v_logS;		// Executar Verificação
					system(command.c_str());

					tratar_contra_exemplo.take_CE_CBMC_Minisat(v_logS,p);	//	Busca corretamente o estado da verificação (Sucesso ou Falha)
																				//	Busca valores de x1, x2 e fobj

					if(tratar_contra_exemplo._verification == 1){				//	Verificação Sucesso
						v_log++;
						manter_precisao = false;								//
						break;													//	Parar while Interno
																				//	Muda de Precisão
					}else{

						for (list<Tcexamples>::const_iterator it = conjunto_fobj.begin(); it != conjunto_fobj.end(); ++it){		//
							if((  convertStringDouble(tratar_contra_exemplo._fjob) >= convertStringDouble((*it)._fjob)) ){		// Verifica se Já existe esse Fobj igual
								minimo_existente_maior = true;																	// Verifica se esse Fobj é maior que os outros encontrados
							}																									//
						}

						if(minimo_existente_maior){														// Se verificaou valor

							compensar_fobj = compensar_fobj * 10;										// Aumenta o Compensador
							minimo_existente_maior = false;												// 	Resetar condição deste erro, deste if
							new_fiS = ex.fobj_current /*fobj_valido*/ + " -" + convertDoubleString(compensar_fobj);		// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;
							gerar_arquivos.create_mi_CBMC_C_Minisat(ex, p);
						}else{

							ex.fobj_current = tratar_contra_exemplo._fjob;											// Atualiza ultimo valor mínimo Válido
							v_log++;																				// Incrmenta Log
							conjunto_fobj.push_front(tratar_contra_exemplo);										// Salva na Lista de Mínimos

							cout << "	f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

							new_fiS = ex.fobj_current + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
							ex.fobj_current = new_fiS;

							gerar_arquivos.create_mi_CBMC_C_Minisat(ex, p); 	// Cria os outros arquivos min

						}

					}

						//
				}		//	Fim While Interno
						//
				ex.type_restrictions = 3;

				p = p * 10;
				manter_precisao = true;

				compensar_fobj =  0.00001;				// Reset compensator

				new_fiS = ex.fobj_current + " -" + convertDoubleString(compensar_fobj);						// Generates the new F_I Compensated
				ex.fobj_current = new_fiS;

				ex._x1 = convertStringDouble(tratar_contra_exemplo._x1);
				ex._x2 = convertStringDouble(tratar_contra_exemplo._x2);

				ex.restrictions = generate_assumes(ex, p);

				gerar_arquivos.create_mi_CBMC_C_Minisat(ex, p); 	// Cria os outros arquivos min
			}

			cout << "####################################" << endl ;
			cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

	}




	//////////////////////////////////////////////////////////////////
	///  Functions regarding input file handling ////////////////////
	////////////////////////////////////////////////////////////////

	//****************************************************************************************************************************
	//	Treat and Check Input File

	bool Run_algorithm::checks_input_file(Set ex){

		string name = ex.name_function;

		string name_original = name + ".func";
		string file_original_aux = "";
		string function_original_aux = "";
		string function_tratada_aux = "";
		string restrictions_aux = "";
		string assumes = "";

		string matrix_A = "";
		string matrix_B = "";

		std::size_t found;

		int i=0;

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
		found = file_original_aux.find("#");
		function_original_aux = file_original_aux.substr(0,found);
		restrictions_aux = file_original_aux.substr(found+2,file_original_aux.size());

		// Treats the function, x1 -> x [0], x2 -> x [1]
		while(i <= function_original_aux.size()){

			if(function_original_aux[i] == 'x'){
				if(function_original_aux[i+1] == '1'){
					function_tratada_aux = function_tratada_aux + "X[0]";
					i++;
				}else if(function_original_aux[i+1] == '2'){
					function_tratada_aux = function_tratada_aux + "X[1]";
					i++;
				}else if(function_original_aux[i+1] == '3'){
					function_tratada_aux = function_tratada_aux + "X[2]";
					i++;
				}else if(function_original_aux[i+1] == '4'){
					function_tratada_aux = function_tratada_aux + "X[3]";
					i++;
				}else if(function_original_aux[i+1] == '5'){
					function_tratada_aux = function_tratada_aux + "X[4]";
					i++;
				}
			}else{
				function_tratada_aux = function_tratada_aux + function_original_aux[i];
			}
			i++;
		}

		code_function_original = function_original_aux.substr(0,function_original_aux.size()-1);
		code_function_treated = function_tratada_aux.substr(0,function_tratada_aux.size()-1);

		if(ex.input_format == 0){
			if( ! segment_matrix_format_1(ex, restrictions_aux)){
				return false;
			}
		}else{
			if( ! segment_matrix_format_2(ex, restrictions_aux)){
				return false;
			}
		}

		return true;

	}


	//****************************************************************************************************************************
	//	Function that loads the original file with the function and Restrictions
	//	It generates the function in real and adapted format.
	//	Treat and Check Input File



	//****************************************************************************************************************************
	// Organize Matrices format 2

	bool Run_algorithm::segment_matrix_format_2(Set ex, string Mat){

		size_t find;
		string m_a, m_b;
		int i,j,k;
		string value;

		// Treats the restrictions
		find = Mat.find("\n");												//	Segmenta Linha da Matriz A
		m_a = Mat.substr(0,find);											//
		find = Mat.find("B");												//	Segmenta Linha da Matriz B
		m_b = Mat.substr(find,Mat.size());									//

		int cont_A=0;														//
		find = m_a.find("[");												//
		m_a = m_a.substr(find+1);											//	Segmenta Valores da Matriz A
		find = m_a.find("]");												//
		m_a = m_a.substr(0,find+1);											//

		i=0;																//
		while(i <= m_a.size()){												//
			if(m_a[i] == ';'){												//
				cont_A++;													//	Conta a quantidade de Restrições de A (Equações)
			}																//
			i++;															//
		}																	//

		int cont_B=0;														//
		find = m_b.find("[");												//
		m_b = m_b.substr(find+1);											//	Segmenta Valores da Matriz B
		find = m_b.find("]");												//
		m_b = m_b.substr(0,find+1);											//

		i=0;																//
		while(i <= m_b.size()){												//
			if(m_b[i] == ';'){												//
				cont_B++;													//	Conta a quantidade de Restrições de B (Equações)
			}																//
			i++;															//
		}																	//

		if(cont_A != cont_B){
			cout << "Error in Matrices!" << endl;
			return false;
		}

		i=0;																//
		int variable = 0;													//
		int Qvariable = 0;													//
		while( (m_a[i] != ';') && (m_a[i] != ']') ){						//
																			//
			if( (m_a[i]!=' ') && (variable==0)){							//	Descobre quantidade de váriáveis <Qvariable>
				Qvariable++;												//
				variable = 1;												//
			}else if(m_a[i]==' '){											//
				variable = 0;												//
			}																//
																			//
			i++;															//
		}																	//

		value = "";																		//
		for(j=0;j<=cont_A;j++){															// Monta Matrix de A
																						//
			m_a = remove_space(m_a);
			k=0;
			while (m_a[0] != ';' && m_a[0] != ']'){

				i=0;
				while(  (m_a[i] != ' ') && (m_a[i] != ';') && (m_a[i] != ']')  ){
					value = value + m_a[i];
					i++;
				}
				matrixA[j][k] = convertStringInt(value);
				k++;
				value = "";

				m_a = m_a.substr(i,m_a.size());
				m_a = remove_space(m_a);

			}
			m_a = m_a.substr(1,m_a.size());
		}

		value = "";																		//
		for(j=0;j<=cont_B;j++){															// Monta Matrix de B
																						//
			m_b = remove_space(m_b);
			k=0;
			while (m_b[0] != ';' && m_b[0] != ']'){

				i=0;
				while(  (m_b[i] != ' ') && (m_b[i] != ';') && (m_b[i] != ']')  ){
					value = value + m_b[i];
					i++;
				}
				matrixB[j] = convertStringInt(value);
				k++;
				value = "";

				m_b = m_b.substr(i,m_b.size());
				m_b = remove_space(m_b);

			}
			m_b = m_b.substr(1,m_b.size());
		}

		l_A = cont_A + 1;
		c_A = Qvariable;
		l_B = cont_B + 1;
		c_B = 1;

/*
 	 	 for(i=0;i<l_A;i++){
			for(j=0;j<c_A;j++){
				cout << matrixA[i][j];
			}
			cout << endl;
		}
		cout << endl;
*/
		return true;
	}


	//****************************************************************************************************************************
	// Organize Matrices in format 1

	bool Run_algorithm::segment_matrix_format_1(Set ex, string Mat){

		size_t find;
		string m_a;
		int i,j,k;
		string value;

		// Treats the restrictions
		find = Mat.find("\n");												//	Segmenta Linha da Matriz A
		m_a = Mat.substr(0,find);											//

		int cont_A=0;														//
		find = m_a.find("[");												//
		m_a = m_a.substr(find+1);											//	Segmenta Valores da Matriz A
		find = m_a.find("]");												//
		m_a = m_a.substr(0,find+1);											//

		i=0;																//
		while(i <= m_a.size()){												//
			if(m_a[i] == ';'){												//
				cont_A++;													//	Conta a quantidade de Variáveis do Problema
			}																//
			i++;															//
		}																	//

		i=0;																//
		int variable = 0;													//
		int Qvariable = 0;													//
		while( (m_a[i] != ';') && (m_a[i] != ']') ){						//
																			//
			if( (m_a[i]!=' ') && (variable==0)){							//	Descobre se os limites inferiores e superiores estão corretos
				Qvariable++;												//
				variable = 1;												//
			}else if(m_a[i]==' '){											//
				variable = 0;												//
			}																//
																			//
			i++;															//
		}																	//

		if(Qvariable != 2){
			cout << "Error in Matrix" << endl;
			return false;
		}

		value = "";																		//
		for(j=0;j<=cont_A;j++){															// Monta Matrix de A
																						//
			m_a = remove_space(m_a);
			k=0;
			while (m_a[0] != ';' && m_a[0] != ']'){

				i=0;
				while(  (m_a[i] != ' ') && (m_a[i] != ';') && (m_a[i] != ']')  ){
					value = value + m_a[i];
					i++;
				}
				matrixA[j][k] = convertStringInt(value);
				k++;
				value = "";

				m_a = m_a.substr(i,m_a.size());
				m_a = remove_space(m_a);

			}
			m_a = m_a.substr(1,m_a.size());
		}

		l_A = cont_A + 1;
		c_A = Qvariable;
/*
	 	for(i=0;i<l_A;i++){
			for(j=0;j<c_A;j++){
				cout << matrixA[i][j];
			}
			cout << endl;
		}
		cout << endl;
*/
		return true;
	}


	//****************************************************************************************************************************
	// Remove spaces from string

	string Run_algorithm::remove_space(string str){
		int i=0;
		while(str[i] == ' '){
			i++;
		}
		str = str.substr(i,str.size());
		return str;
	}


	//****************************************************************************************************************************
	// Create the assumes in string

	string Run_algorithm::generate_assumes(Set ex, int p){

		cout << "Gera ASSUME "<< endl;

		string generate_assumes = "";
		int i,j;

		cout << "Input: " ;
		cout <<	ex.type_restrictions << endl;

		if(ex.type_restrictions == 0){

			if(ex.input_format==0){

				generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	";
				generate_assumes = generate_assumes + "     \n        // Restrictions\n";

				generate_assumes = generate_assumes + "     \n        int lim[4] = {";

				for(i=0;i<l_A;i++){
					for(j=0;j<c_A;j++){
						generate_assumes = generate_assumes + convertIntString(matrixA[i][j]);
						generate_assumes = generate_assumes + "*p, ";
					}
				}

				generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
				generate_assumes = generate_assumes + "};";

				generate_assumes = generate_assumes + "\n";
				generate_assumes = generate_assumes + "\n        for (i = 0; i < nv; i++) {";
				generate_assumes = generate_assumes + "\n            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );";
				generate_assumes = generate_assumes + "\n            __ESBMC_assume( X[i] == (float) x[i]/p	); ";
				generate_assumes = generate_assumes + "\n        }\n";


				generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	\n\n";

				return generate_assumes;

			}else{

				generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	";
				generate_assumes = generate_assumes + "     \n        // Restrictions\n";

				generate_assumes = generate_assumes + "     \n        int A[nr][nv] = {";

				for(i=0;i<l_A;i++){
					for(j=0;j<c_A;j++){
						generate_assumes = generate_assumes + convertIntString(matrixA[i][j]);
						generate_assumes = generate_assumes + "*p, ";
					}
				}

				generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
				generate_assumes = generate_assumes + "};";

				generate_assumes = generate_assumes + "\n                 int B[nr] = {";

				for(i=0;i<l_A;i++){
					generate_assumes = generate_assumes + convertIntString(matrixB[i]);
					generate_assumes = generate_assumes + "*p, ";
				}

				generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
				generate_assumes = generate_assumes + "};";

				generate_assumes = generate_assumes + "     \n        float s = 0;\n";
				generate_assumes = generate_assumes + "     \n        for (i = 0; i < nr; i++) {\n            for (j = 0; j < nv; j++){\n                 s = s + A[i][j]*x[j]/p;\n            }\n";
				generate_assumes = generate_assumes + "            __ESBMC_assume( s < (float) B[i] );\n           s = 0;\n        }\n";
				generate_assumes = generate_assumes + "		\n        for (i = 0; i < nv; i++) {\n            __ESBMC_assume( X[i] == (float) x[i]/p	);\n        }\n";

				generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	\n\n";

				return generate_assumes;

			}

		}else if(ex.type_restrictions == 1){

			if(ex.input_format == 0){

				generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	";
				generate_assumes = generate_assumes + "     \n        // Restrictions\n";

				string new_spaceS = "\n	int lim[4] = { " + convertDoubleString((ex._x1*p-1)*10) + ", " + convertDoubleString((ex._x1*p+1)*10) + ", " + convertDoubleString((ex._x2*p-1)*10) + ", " + convertDoubleString((ex._x2*p+1)*10) + " };";

//				cout << "AQUI:" << new_spaceS << endl;

/*
 				generate_assumes = generate_assumes + "     \n        int lim[4] = {";

				generate_assumes = generate_assumes + "("+convertDoubleString(ex._x1)+"*"+convertIntString(p)+"-1)*10,";
				generate_assumes = generate_assumes + "("+convertDoubleString(ex._x1)+"*"+convertIntString(p)+"+1)*10,";
				generate_assumes = generate_assumes + "("+convertDoubleString(ex._x2)+"*"+convertIntString(p)+"-1)*10,";
				generate_assumes = generate_assumes + "("+convertDoubleString(ex._x2)+"*"+convertIntString(p)+"+1)*10";

				generate_assumes = generate_assumes + "};";
*/

				generate_assumes = generate_assumes + new_spaceS;

				generate_assumes = generate_assumes + "\n";
				generate_assumes = generate_assumes + "\n        for (i = 0; i < nv; i++) {";
				generate_assumes = generate_assumes + "\n            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );";
				generate_assumes = generate_assumes + "\n            __ESBMC_assume( X[i] == (float) x[i]/p	); ";
				generate_assumes = generate_assumes + "\n        }\n";


				generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	\n\n";

				return generate_assumes;

			}else{

				generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	";
				generate_assumes = generate_assumes + "     \n        // Restrictions\n";

				generate_assumes = generate_assumes + "     \n        int A[nr][nv] = {";

				for(i=0;i<l_A;i++){
					for(j=0;j<c_A;j++){
						generate_assumes = generate_assumes + convertIntString(matrixA[i][j]);
						generate_assumes = generate_assumes + "*p, ";
					}
				}

				generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
				generate_assumes = generate_assumes + "};";

				generate_assumes = generate_assumes + "\n        int B[nr] = {";

				for(i=0;i<l_A;i++){
					generate_assumes = generate_assumes + convertIntString(matrixB[i]);
					generate_assumes = generate_assumes + "*p, ";
				}

				generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
				generate_assumes = generate_assumes + "};";

				generate_assumes = generate_assumes + "     \n        float s = 0;\n";
				generate_assumes = generate_assumes + "     \n        for (i = 0; i < nr; i++) {\n            for (j = 0; j < nv; j++){\n                 s = s + A[i][j]*x[j]/p;\n            }\n";
				generate_assumes = generate_assumes + "            __ESBMC_assume( s < (float) B[i] );\n           s = 0;\n        }\n";
				generate_assumes = generate_assumes + "		\n        for (i = 0; i < nv; i++) {\n            __ESBMC_assume( X[i] == (float) x[i]/p	);\n        }\n";

				generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	\n\n";

				return generate_assumes;

			}

		}else if(ex.type_restrictions == 2){

				if(ex.input_format==0){

					generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	";
					generate_assumes = generate_assumes + "     \n        // Restrictions\n";

//					file_min << "		" + space_limitP + "\n\n";

//					file_min << "		for (i = 0; i<2; i++){\n";
//					file_min << "			__CPROVER_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );\n";
//					file_min << "			__CPROVER_assume( X[i] == ("+type+") x[i]/p	);\n";
//					file_min << "		}\n\n";


					generate_assumes = generate_assumes + "     \n        int lim[4] = {";

					for(i=0;i<l_A;i++){
						for(j=0;j<c_A;j++){
							generate_assumes = generate_assumes + convertIntString(matrixA[i][j]);
							generate_assumes = generate_assumes + "*p, ";
						}
					}

					generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
					generate_assumes = generate_assumes + "};";

					generate_assumes = generate_assumes + "\n";
					generate_assumes = generate_assumes + "\n        for (i = 0; i < nv; i++) {";
					generate_assumes = generate_assumes + "\n            __CPROVER_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );";
					generate_assumes = generate_assumes + "\n            __CPROVER_assume( X[i] == (float) x[i]/p	); ";
					generate_assumes = generate_assumes + "\n        }\n";



					generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	\n\n";

					return generate_assumes;

			}else{

				generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	";
				generate_assumes = generate_assumes + "     \n        // Restrictions\n";

				generate_assumes = generate_assumes + "     \n        int A[nr][nv] = {";

				for(i=0;i<l_A;i++){
					for(j=0;j<c_A;j++){
						generate_assumes = generate_assumes + convertIntString(matrixA[i][j]);
						generate_assumes = generate_assumes + "*p, ";
					}
				}

				generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
				generate_assumes = generate_assumes + "};";

				generate_assumes = generate_assumes + "\n        int B[nr] = {";

				for(i=0;i<l_A;i++){
					generate_assumes = generate_assumes + convertIntString(matrixB[i]);
					generate_assumes = generate_assumes + "*p, ";
				}

				generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
				generate_assumes = generate_assumes + "};";

				generate_assumes = generate_assumes + "     \n        float s = 0;\n";
				generate_assumes = generate_assumes + "     \n        for (i = 0; i < nr; i++) {\n            for (j = 0; j < nv; j++){\n                 s = s + A[i][j]*x[j]/p;\n            }\n";
				generate_assumes = generate_assumes + "            __ESBMC_assume( s < (float) B[i] );\n           s = 0;\n        }\n";
				generate_assumes = generate_assumes + "		\n        for (i = 0; i < nv; i++) {\n            __ESBMC_assume( X[i] == (float) x[i]/p	);\n        }\n";

				generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	\n\n";

				return generate_assumes;

			}

	}else if(ex.type_restrictions == 3){


				if(ex.input_format==0){

					generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	";
					generate_assumes = generate_assumes + "     \n        // Restrictions\n";

					string new_spaceS = "\n	int lim[4] = { " + convertDoubleString((ex._x1*p-1)*10) + ", " + convertDoubleString((ex._x1*p+1)*10) + ", " + convertDoubleString((ex._x2*p-1)*10) + ", " + convertDoubleString((ex._x2*p+1)*10) + " };";

	//				cout << "AQUI:" << new_spaceS << endl;

	/*
	 				generate_assumes = generate_assumes + "     \n        int lim[4] = {";

					generate_assumes = generate_assumes + "("+convertDoubleString(ex._x1)+"*"+convertIntString(p)+"-1)*10,";
					generate_assumes = generate_assumes + "("+convertDoubleString(ex._x1)+"*"+convertIntString(p)+"+1)*10,";
					generate_assumes = generate_assumes + "("+convertDoubleString(ex._x2)+"*"+convertIntString(p)+"-1)*10,";
					generate_assumes = generate_assumes + "("+convertDoubleString(ex._x2)+"*"+convertIntString(p)+"+1)*10";

					generate_assumes = generate_assumes + "};";
	*/

					generate_assumes = generate_assumes + new_spaceS;

					generate_assumes = generate_assumes + "\n";
					generate_assumes = generate_assumes + "\n        for (i = 0; i < nv; i++) {";
					generate_assumes = generate_assumes + "\n            __CPROVER_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );";
					generate_assumes = generate_assumes + "\n            __CPROVER_assume( X[i] == (float) x[i]/p	); ";
					generate_assumes = generate_assumes + "\n        }\n";


					generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	\n\n";

					return generate_assumes;


			}else{

				generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	";
				generate_assumes = generate_assumes + "     \n        // Restrictions\n";

				generate_assumes = generate_assumes + "     \n        int A[nr][nv] = {";

				for(i=0;i<l_A;i++){
					for(j=0;j<c_A;j++){
						generate_assumes = generate_assumes + convertIntString(matrixA[i][j]);
						generate_assumes = generate_assumes + "*p, ";
					}
				}

				generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
				generate_assumes = generate_assumes + "};";

				generate_assumes = generate_assumes + "\n        int B[nr] = {";

				for(i=0;i<l_A;i++){
					generate_assumes = generate_assumes + convertIntString(matrixB[i]);
					generate_assumes = generate_assumes + "*p, ";
				}

				generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
				generate_assumes = generate_assumes + "};";

				generate_assumes = generate_assumes + "     \n        float s = 0;\n";
				generate_assumes = generate_assumes + "     \n        for (i = 0; i < nr; i++) {\n            for (j = 0; j < nv; j++){\n                 s = s + A[i][j]*x[j]/p;\n            }\n";
				generate_assumes = generate_assumes + "            __ESBMC_assume( s < (float) B[i] );\n           s = 0;\n        }\n";
				generate_assumes = generate_assumes + "		\n        for (i = 0; i < nv; i++) {\n            __ESBMC_assume( X[i] == (float) x[i]/p	);\n        }\n";

				generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------	\n\n";

				return generate_assumes;

			}
		}

		return generate_assumes;

	}







	//////////////////////////////////////////////////////////////////
	///  Type conversion functions	/////////////////////////////////
	////////////////////////////////////////////////////////////////

	int Run_algorithm::convertStringInt(string str){
		return atoi(str.c_str());
	}

	double Run_algorithm::convertStringDouble(string str){
		return atof(str.c_str());
	}

	string Run_algorithm::convertDoubleString(double value){
		ostringstream convert;
		convert << value;
		return convert.str();
	}

	string Run_algorithm::convertIntString(int value){
		ostringstream convert;
		convert << value;
		return convert.str();
	}
