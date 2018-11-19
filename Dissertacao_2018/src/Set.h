/*
 *  Set.h
 *
 *  Created on: 03/02/2017
 *  Author: Higo Albuquerque
 */

  #include <iostream>
  using namespace std;

  #ifndef SET_H_
  #define SET_H_

  class Set {
    private:
    public:
      string name_function;
      int mc;
      int solver;
      int alg;
      float l_inf;
      string l_sup;
      string fobj_current;
      double _x1;
      double _x2;
      string typeData;
      float timeout_global;
      float timeout_verification;
      string code_function;
      string code_function_modified;
      string space_limit;
      string restrictions;
      int type_restrictions;
      string library;
      int input_format;
      int precision;
      int n;
      int nr;

      Set();
      virtual ~Set();
      void printSet();
  };

  #endif /* SET_H_ */
