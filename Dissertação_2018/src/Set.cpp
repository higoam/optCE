/*
 *  Set.cpp
 *
 *  Created on: 03/02/2017
 *  Author: Higo Albuquerque
 */

#include "Set.h"

  Set::Set() 
  {
    typeData = "";
    timeout_global = 0;
    timeout_verification = 0;
  }

  Set::~Set()
  {
    // TODO Auto-generated destructor stub
  }


  /*******************************************************************\
  Method: printSet()
  Inputs: Void
  Outputs: Void 
  Purpose: Print the optimization configuration
  \*******************************************************************/

  void Set::printSet()
  {
    cout << "####### SET #########"<< endl;
    cout << "Function: " + name_function << endl;
    cout << "F_I: " + l_sup << endl;
    cout <<  mc << endl;
    cout <<  solver << endl;
    cout <<  alg<< endl;
    cout << "TypeData: " + typeData<< endl;
    cout << "############################" << endl;
    cout << "CodeFunction:"<< endl;
    cout <<  code_function << endl;
    cout <<  space_limit << endl;
  }
