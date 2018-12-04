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

string Execution::run(Setup* experiment) {

	cout << "Execucao" << endl;

	if(experiment->bmc == 1)
	{
		if(experiment->alg == 1)
		{
			if(experiment->solver == 1)
			{
				run_ESBMC_G_BOOLECTOR(experiment);
			}
			else if(experiment->solver == 2)
			{
//				run_ESBMC_G_Z3(ex);
				//
			}
			else if(experiment->solver == 3)
			{
//				run_ESBMC_G_MATHSAT(ex);
			}
		}
		else if(experiment->alg== 2)
		{
			if(experiment->solver == 1)
			{
//				run_ESBMC_S_BOOLECTOR(ex);
			}
			else if(experiment->solver == 2)
			{
//				run_ESBMC_S_Z3(ex);
			}
			else if(experiment->solver == 3)
			{
//				run_ESBMC_S_MATHSAT(ex);
			}
		}
		else if(experiment->alg== 3)
		{
			if(experiment->solver == 1)
			{
//				run_ESBMC_C_BOOLECTOR(ex);
			}
			else if(experiment->solver == 2)
			{
//				run_ESBMC_C_Z3(ex);
			}
			else if(experiment->solver == 3)
			{
//				run_ESBMC_C_MATHSAT(ex);
			}
		}
	}
	else if(experiment->bmc == 2)
	{
		if(experiment->alg== 1)
		{
			if(experiment->solver == 4)
			{
//				run_CBMC_G_MINISAT(ex);
			}
		}
		else if(experiment->alg== 2)
		{
			if(experiment->solver == 4)
			{
//				run_CBMC_S_MINISAT(ex);
			}
		}
		else if(experiment->alg== 3)
		{
			if(experiment->solver == 4)
			{
//				run_CBMC_C_MINISAT(ex);
			}
		}
	}
	else if(experiment->bmc == 3)
	{
		if(experiment->solver == 1)
		{
		}
		else if(experiment->solver == 2)
		{
		}
		else if(experiment->solver == 3)
		{
		}
	}


	string result_experiment;

	return result_experiment;
}




void Execution::run_ESBMC_G_BOOLECTOR(Setup* experiment)
{
	cout << "#############################################" << endl;
	cout << "#     ESBMC - Boolector - Alg Generalized   #" << endl;
	cout << "#############################################" << endl;

	cout << endl << "### Parametros Refrente a Flags" << endl << endl;
	cout << "   Nome Função: ";
	cout << experiment->name_function << endl;
	cout << "   Algoritmo: ";
	cout << experiment->alg << endl;
	cout << "   BMC: ";
	cout << experiment->bmc << endl;
	cout << "   Solver: ";
	cout << experiment->solver << endl;
	cout << "   Inicialização: ";
	cout << experiment->fc << endl;
	cout << "   Biblioteca: ";
	cout << experiment->library << endl;
	cout << "   Precisão: ";
	cout << experiment->precision_test << endl;


	cout << endl << "### Parametros Refrente Arquivo de antrada" << endl << endl;
	cout << "   CODE: ";
	cout << experiment->code_function << endl;
	cout << "   CODE: ";
	cout << experiment->code_function_modified << endl;




	// Adjustment Variables
	string command = "";
	experiment->setPrecisionCurrent(1);



//  bool keep_precision = true;
//  bool minimo_existente_maior = false;
	string new_fiS;
	float compensar_fobj;
	string compensar_fobjS;
//  int v_log = 1;
	string v_logS;
  //int precisionLoop = pow(10, ex.precision);



	// Gerar Restrições
  	experiment->setRestrictions( generate_assumes(experiment,1) );

  	// Gerar Arquivo C para calcular Mínimo
  	generatefilesAUX.create_f(experiment);
  	command  = "gcc " + experiment->getNameFunction() + ".c -o value_min";
  	system(command.c_str());

  	// Gerar Especificação
  	generatefilesAUX.create_mi_ESBMC_G_Boolector(experiment);

  	compensar_fobj =  0.00001;



/*

  while( p<=precisionLoop )
  {
    cout << endl << " ******************************** " << endl;

    while( keep_precision )
    {
      v_logS = "log_" + convert.convertDoubleString(v_log); // Increase Log

      command = "./esbmc min_" +ex.name_function+ ".c --boolector > " +v_logS;
      system(command.c_str());

      tratar_contra_exemplo.take_CE_ESBMC_Boolector(v_logS, p);

      if(tratar_contra_exemplo._verification == 1)
      {
        v_log++;
        keep_precision = false;
        break;
      }
      else
      {
        for(list<Tcexamples>::const_iterator it = set_fobj.begin(); it != set_fobj.end(); ++it)
        {
          if((  convert.convertStringDouble(tratar_contra_exemplo._fjob) >= convert.convertStringDouble((*it)._fjob)) )
          {
            minimo_existente_maior = true;
          }
        }

        if(minimo_existente_maior)
        {
          compensar_fobj = compensar_fobj * 10;
          minimo_existente_maior = false;
          new_fiS = ex.fobj_current + " -" + convert.convertDoubleString(compensar_fobj);
          ex.fobj_current = new_fiS;
          gerar_arquivos.create_mi_ESBMC_G_Boolector(ex, p);
        }
        else
        {
          ex.fobj_current = tratar_contra_exemplo._fjob;
          v_log++;
          set_fobj.push_front(tratar_contra_exemplo);
          cout << "  f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;
          new_fiS = ex.fobj_current + " -" + convert.convertDoubleString(compensar_fobj);
          ex.fobj_current = new_fiS;
          gerar_arquivos.create_mi_ESBMC_G_Boolector(ex, p);
        }
      }
    }    //  Fim While Interno

    p = p * 10;
    keep_precision = true;
    compensar_fobj =  0.00001;    // Reset compensator

    new_fiS = ex.fobj_current + " -" + convert.convertDoubleString(compensar_fobj);
    ex.fobj_current = new_fiS;
    gerar_arquivos.create_mi_ESBMC_G_Boolector(ex, p);
  }
*/
  cout << "####################################" << endl;
//  cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;
}



string Execution::generate_assumes(Setup* experiment,int p){

	string string_assumes = "";
	int i,j;

	if(experiment->type_restrictions == 0){

		string_assumes = string_assumes + "     \n        //-----------------------------------------------------------  ";
		string_assumes = string_assumes + "     \n        // Restrictions\n";

		string_assumes = string_assumes + "     \n        int lim[4] = {";

		for(i=0;i<l_A;i++){
			for(j=0;j<c_A;j++){
				string_assumes = string_assumes + convert.convertIntString(matrixA[i][j]);
				string_assumes = string_assumes + "*p, ";
			}
		}

		string_assumes = string_assumes.substr(0,string_assumes.size()-2);
		string_assumes = string_assumes + "};";

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

//		string new_spaceS = "\n  int lim[4] = { " + convert.convertDoubleString((ex._x1*p-1)*10) + ", " + convert.convertDoubleString((ex._x1*p+1)*10) + ", " + convert.convertDoubleString((ex._x2*p-1)*10) + ", " + convert.convertDoubleString((ex._x2*p+1)*10) + " };";

//		string_assumes = string_assumes + new_spaceS;

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

        for(i=0;i<l_A;i++){
          for(j=0;j<c_A;j++){
            string_assumes = string_assumes + convert.convertIntString(matrixA[i][j]);
            string_assumes = string_assumes + "*p, ";
          }
        }

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



bool Execution::segment_matrix_format_1(Setup ex, string Mat){

  size_t find;
  string m_a;
  int i,j,k;
  string value;

  // Treats the restrictions
  find = Mat.find("\n");                        //  Segmenta Linha da Matriz A
  m_a = Mat.substr(0,find);                      //

  int cont_A=0;                            //
  find = m_a.find("[");                        //
  m_a = m_a.substr(find+1);                      //  Segmenta Valores da Matriz A
  find = m_a.find("]");                        //
  m_a = m_a.substr(0,find+1);                      //

  i=0;                                //
  while(i <= m_a.size()){                        //
    if(m_a[i] == ';'){                        //
      cont_A++;                          //  Conta a quantidade de Variáveis do Problema
    }                                //
    i++;                              //
  }                                  //

  i=0;                                //
  int variable = 0;                          //
  int Qvariable = 0;                          //
  while( (m_a[i] != ';') && (m_a[i] != ']') ){            //
                                    //
    if( (m_a[i]!=' ') && (variable==0)){              //  Descobre se os limites inferiores e superiores estão corretos
      Qvariable++;                        //
      variable = 1;                        //
    }else if(m_a[i]==' '){                      //
      variable = 0;                        //
    }                                //
                                    //
    i++;                              //
  }                                  //

  if(Qvariable != 2){
    cout << "Error in Matrix" << endl;
    return false;
  }

  value = "";                                    //
  for(j=0;j<=cont_A;j++){                              // Monta Matrix de A
                                          //
    m_a = remove_space(m_a);
    k=0;
    while (m_a[0] != ';' && m_a[0] != ']'){

      i=0;
      while(  (m_a[i] != ' ') && (m_a[i] != ';') && (m_a[i] != ']')  ){
        value = value + m_a[i];
        i++;
      }
      matrixA[j][k] = convert.convertStringInt(value);
      k++;
      value = "";

      m_a = m_a.substr(i,m_a.size());
      m_a = remove_space(m_a);

    }
    m_a = m_a.substr(1,m_a.size());
  }

  l_A = cont_A + 1;
  c_A = Qvariable;

  return true;
}



string Execution::remove_space(string str){
  int i=0;
  while(str[i] == ' '){
    i++;
  }
  str = str.substr(i,str.size());
  return str;
}









} /* namespace EXCUTION */
