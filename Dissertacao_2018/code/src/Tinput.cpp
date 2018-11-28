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

Setup setup_experiment_input;

Setup* Tinput::Checks(Setup* setup_aux)
{
    int i=0;
    std::size_t marcador;

    string input_original = setup_aux->getNameFunction() + ".func";
    string file_aux = "";

    string function_original = "";
    string function_tratada = "";
    string restrictions = "";
 //   string assumes = "";

    string matrix_A = "";
    string matrix_B = "";

    char letter;
    ifstream file_min;
    file_min.open(input_original.c_str());




//    string vet_space[4];


    // Opens the original function file
    if(!file_min.is_open( )){
      cout<<"Could not open file with function!\n";
      file_min.clear( ); //reseta o objeto leitura, para limpar memória do sistema}
    }

    // Loads the file into string
    while (file_min.get(letter)) {
    	file_aux = file_aux + letter;
    }

    // Divides the part of the function and the limits
    marcador = file_aux.find("#");
    function_original = file_aux.substr(0,marcador);
    restrictions = file_aux.substr(marcador+2,file_aux.size());

    // Treats the function, x1 -> x [0], x2 -> x [1]
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

    setup_aux->setCodeFunction( function_original.substr(0,function_original.size()-1) );
    setup_aux->setCodeFunctionModified( function_tratada.substr(0,function_tratada.size()-1) );


/*
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
*/

  return setup_aux;
}



//****************************************************************************************************************************
// Organize Matrices format 2
/*
bool Tinput::segment_matrix_format(Setup ex, string Mat){

  size_t find;
  string m_a, m_b;
  int i,j,k;
  string value;

  // Treats the restrictions
  find = Mat.find("\n");                        //  Segmenta Linha da Matriz A
  m_a = Mat.substr(0,find);                      //
  find = Mat.find("B");                        //  Segmenta Linha da Matriz B
  m_b = Mat.substr(find,Mat.size());                  //

  int cont_A=0;                            //
  find = m_a.find("[");                        //
  m_a = m_a.substr(find+1);                      //  Segmenta Valores da Matriz A
  find = m_a.find("]");                        //
  m_a = m_a.substr(0,find+1);                      //

  i=0;                                //
  while(i <= m_a.size()){                        //
    if(m_a[i] == ';'){                        //
      cont_A++;                          //  Conta a quantidade de Restrições de A (Equações)
    }                                //
    i++;                              //
  }                                  //

  int cont_B=0;                            //
  find = m_b.find("[");                        //
  m_b = m_b.substr(find+1);                      //  Segmenta Valores da Matriz B
  find = m_b.find("]");                        //
  m_b = m_b.substr(0,find+1);                      //

  i=0;                                //
  while(i <= m_b.size()){                        //
    if(m_b[i] == ';'){                        //
      cont_B++;                          //  Conta a quantidade de Restrições de B (Equações)
    }                                //
    i++;                              //
  }                                  //

  if(cont_A != cont_B){
    cout << "Error in Matrices!" << endl;
    return false;
  }

  i=0;                                //
  int variable = 0;                          //
  int Qvariable = 0;                          //
  while( (m_a[i] != ';') && (m_a[i] != ']') ){            //
                                    //
    if( (m_a[i]!=' ') && (variable==0)){              //  Descobre quantidade de váriáveis <Qvariable>
      Qvariable++;                        //
      variable = 1;                        //
    }else if(m_a[i]==' '){                      //
      variable = 0;                        //
    }                                //
                                    //
    i++;                              //
  }                                  //

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

  value = "";                                    //
  for(j=0;j<=cont_B;j++){                              // Monta Matrix de B
                                          //
    m_b = remove_space(m_b);
    k=0;
    while (m_b[0] != ';' && m_b[0] != ']'){

      i=0;
      while(  (m_b[i] != ' ') && (m_b[i] != ';') && (m_b[i] != ']')  ){
        value = value + m_b[i];
        i++;
      }
      matrixB[j] = convert.convertStringInt(value);
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

  return true;
}
*/



} /* namespace TINPUT */
