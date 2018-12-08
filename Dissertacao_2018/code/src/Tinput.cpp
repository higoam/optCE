/*
 * Tinput.cpp
 *
 *  Created on: 24/11/2018
 *      Author: higo
 */

#include "Tinput.h"

namespace TINPUT {

Tinput::Tinput() {
	// TODO Auto-generated constructor stub

}

Tinput::~Tinput() {
	// TODO Auto-generated destructor stub
}

Setup setup_setup_aux_input;


Setup* Tinput::Checks(Setup* setup_aux)
{

	// Variáveis Auxiliares
    int i=0;
    std::size_t marcador;
    string file_aux = "";
    string function_original = "";
    string function_tratada = "";
    string matrix_A = "";
    string matrix_B = "";

    // Abrindo arquivo de entrada
    string input_file = setup_aux->getNameFunction() + ".func";
    char letter;
    ifstream file_min;
    file_min.open(input_file.c_str());

    // Em caso de erro na leitura
    if(!file_min.is_open( )){
      cout<<"Could not open file with function!\n";
      file_min.clear( ); //reseta o objeto leitura, para limpar memória do sistema}
    }

    // Converte para string arquivo de entrada
    while (file_min.get(letter)) {
    	file_aux = file_aux + letter;
    }

    // Divide as partes de função e Restrição
    marcador = file_aux.find("#");
    setup_aux->setInputFunction( file_aux.substr(0,marcador) );
    setup_aux->setInputRestrictions(file_aux.substr(marcador+2,file_aux.size()));

    // Variável Auxiliar para rescrever a função com variáveis grandes
    function_original = setup_aux->getInputFunction();

    // Rescreve a função com variáveis grandes
    while( i <= (int)function_original.size() ){

      if(function_original[i] == 'x'){
        if(function_original[i+1] == '1'){
          function_tratada = function_tratada + "X[0]";
          i++;
        }else if(function_original[i+1] == '2'){
          function_tratada = function_tratada + "X[1]";
          i++;
        }else if(function_original[i+1] == '3'){
          function_tratada = function_tratada + "X[2]";
          i++;
        }else if(function_original[i+1] == '4'){
          function_tratada = function_tratada + "X[3]";
          i++;
        }else if(function_original[i+1] == '5'){
          function_tratada = function_tratada + "X[4]";
          i++;
        }
      }else{
        function_tratada = function_tratada + function_original[i];
      }
      i++;
    }

    //     Armazena
    setup_aux->setCodeFunction( function_original.substr(0,function_original.size()-1) );
    setup_aux->setCodeFunctionModified( function_tratada.substr(0,function_tratada.size()-1) );

    segment_matrix(setup_aux);

    return setup_aux;
}


Setup*  Tinput::segment_matrix(Setup* setup_aux){

	size_t find;
	string m_a;
	int i,j,k;
	string value;

	//  Segmenta Linha da Matriz A
	find =setup_aux->getInputRestrictions().find("\n");
	m_a = setup_aux->getInputRestrictions().substr(0,find);

	//  Segmenta Valores da Matriz A
	int cont_A=0;
	find = m_a.find("[");
	m_a = m_a.substr(find+1);
	find = m_a.find("]");
	m_a = m_a.substr(0,find+1);

	//  Conta a quantidade de Variáveis do Problema
	i=0;
	while(i <= m_a.size()){
		if(m_a[i] == ';'){
			cont_A++;
		}
		i++;
	}

	//  Descobre se os limites inferiores e superiores estão corretos
	i=0;
	int variable = 0;
	int Qvariable = 0;

	while( (m_a[i] != ';') && (m_a[i] != ']') ){
                                    //
		if( (m_a[i]!=' ') && (variable==0)){
			Qvariable++;
			variable = 1;
		}else if(m_a[i]==' '){
			variable = 0;
		}
		i++;
	}

	if(Qvariable != 2){
		cout << "Error in Matrix2" << endl;
		return false;
	}

	// Monta Matrix de A
	value = "";
	for(j=0;j<=cont_A;j++){

		m_a = remove_space(m_a);
		k=0;
		while (m_a[0] != ';' && m_a[0] != ']'){

			i=0;
			while(  (m_a[i] != ' ') && (m_a[i] != ';') && (m_a[i] != ']')  ){
				value = value + m_a[i];
				i++;
			}
			matrixA[j][k] = convertValue.convertStringInt(value);

			k++;
			value = "";

			m_a = m_a.substr(i,m_a.size());
			m_a = remove_space(m_a);

		}
		m_a = m_a.substr(1,m_a.size());
	}

	setup_aux->setInfX1(matrixA[0][0]);
	setup_aux->setSupX1(matrixA[0][1]);
	setup_aux->setInfX2(matrixA[1][0]);
	setup_aux->setSupX2(matrixA[1][1]);

	setup_aux->setLineInput(cont_A + 1);
	setup_aux->setColumnInput(Qvariable);

  return setup_aux;
}




// OK
	  string Tinput::remove_space(string str){
	    int i=0;
	    while(str[i] == ' '){
	      i++;
	    }
	    str = str.substr(i,str.size());
	    return str;
	  }


} /* namespace TINPUT */
