/*
 * Runalgorithm.cpp
 *
 *  Created on: 03/02/2017
 *  Author: Higo Albuquerque
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <list>
#include <math.h>

#include "Set.h"
#include "Tcexamples.h"
#include "Runalgorithm.h"
#include "Adjust.h"

using namespace std;

  Run_algorithm::Run_algorithm()
  {
    // TODO Auto-generated constructor stub
  }

  Run_algorithm::~Run_algorithm()
  {
    // TODO Auto-generated destructor stub
  }

  /*******************************************************************************************************\
  Method: execute_experiment(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Execution Management
  \*******************************************************************************************************/

  void Run_algorithm::execute_experiment(Set ex)
  {
    ex.type_restrictions = 0;

    if(ex.mc == 1)
    {
      if(ex.alg == 1)
      {
        if(ex.solver == 1)
        {
          run_ESBMC_BOOLECTOR_G(ex);
        }
        else if(ex.solver == 2)
        {
          run_ESBMC_Z3_G(ex);
        }
        else if(ex.solver == 3)
        {
          run_ESBMC_MATHSAT_G(ex);
        }
      }
      else if(ex.alg == 2)
      {
        if(ex.solver == 1)
        {
          run_ESBMC_BOOLECTOR_S(ex);
        }
        else if(ex.solver == 2)
        {
          run_ESBMC_Z3_S(ex);
        }
        else if(ex.solver == 3)
        {
          run_ESBMC_MATHSAT_S(ex);
        }
      }
      else if(ex.alg == 3)
      {
        if(ex.solver == 1)
        {
          run_ESBMC_BOOLECTOR_C(ex);
        }
        else if(ex.solver == 2)
        {
          run_ESBMC_Z3_C(ex);
        }
        else if(ex.solver == 3)
        {
          run_ESBMC_MATHSAT_C(ex);
        }
      }
    }
    else if(ex.mc == 2)
    {
      if(ex.alg == 1)
      {
        if(ex.solver == 4)
        {
          run_CBMC_MINISAT_G(ex);
        }
      }
      else if(ex.alg == 2)
      {
        if(ex.solver == 4)
        {
          run_CBMC_MINISAT_S(ex);
        }
      }
      else if(ex.alg == 3)
      {
        if(ex.solver == 4)
        {
          run_CBMC_MINISAT_C(ex);
        }
      }
    }
    else if(ex.mc == 3)
    {
      if(ex.solver == 1)
      {
      }
      else if(ex.solver == 2)
      {
      }
      else if(ex.solver == 3)
      {
      }
    }
  }

  /*******************************************************************************************************\
  Method: run_ESBMC_BOOLECTOR_G(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Performs optimization with ( ESBMC + BOOLECTOR + CEGIO-G)
  \*******************************************************************************************************/

  void Run_algorithm::run_ESBMC_BOOLECTOR_G(Set ex)
  {
    cout << "#############################################" << endl;
    cout << "#     ESBMC - Boolector - Alg Generalized   #" << endl;
    cout << "#############################################" << endl;

    // Manipulation Variables with Objects and Functions
    Generate_files gerar_arquivos;
    Tcexamples tratar_contra_exemplo;
    Tcexamples list_fobj;
    list<Tcexamples> set_fobj;

    // Adjustment Variables
    string command = "";
    int p = 1;
    bool keep_precision = true;
    bool minimo_existente_maior = false;
    string new_fiS;
    float compensar_fobj;
    string compensar_fobjS;
    int v_log = 1;
    string v_logS;
    int precisionLoop = pow(10, ex.precision);

    ex.restrictions = generate_assumes(ex, p);

    gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);
    command  = "gcc " + ex.name_function + ".c -o value_min";
    system(command.c_str());

    cout << endl << "            Start Value: " + ex.l_sup << endl;

    gerar_arquivos.create_mi_ESBMC_G_Boolector(ex, p);

    compensar_fobj =  0.00001;

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

    cout << "####################################" << endl;
    cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;
  }


  /*******************************************************************************************************\
  Method: run_ESBMC_Z3_G(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Performs optimization with ( ESBMC + Z3 + CEGIO-G)
  \*******************************************************************************************************/

  void Run_algorithm::run_ESBMC_Z3_G(Set ex)
  {
    cout << "###########################################" << endl;
    cout << "#     ESBMC - Z3 - Alg Generalized        #" << endl;
    cout << "###########################################" << endl;

    // Manipulation Variables with Objects and Functions
    Generate_files gerar_arquivos;
    Tcexamples tratar_contra_exemplo;
    Tcexamples list_fobj;
    list<Tcexamples> set_fobj;

    // Adjustment Variables
    string command = "";
    int p = 1;
    bool keep_precision = true;
    bool minimo_existente_maior = false;
    string new_fiS;
    float compensar_fobj;
    string compensar_fobjS;
    int v_log = 1;
    string v_logS;
    int precisionLoop = pow(10, ex.precision);

    ex.restrictions = generate_assumes(ex, p);

    gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);
    command  = "gcc " + ex.name_function + ".c -o value_min";
    system(command.c_str());

    cout << endl << "            Start Value: " + ex.l_sup << endl;

    gerar_arquivos.create_mi_ESBMC_G_Z3(ex, p);

    compensar_fobj =  0.00001;    //  Set standard compensator

    while( p<=precisionLoop )
    {
      cout << endl << " ******************************** " << endl;

      while( keep_precision )
      {
        v_logS = "log_" + convert.convertDoubleString(v_log);

        command  = "./esbmc min_" + ex.name_function + ".c --z3 > " + v_logS;
        system(command.c_str());

        tratar_contra_exemplo.take_CE_ESBMC_Z3(v_logS, p);

        if(tratar_contra_exemplo._verification == 1)
        {                                  //  Verification Success
          v_log++;
          keep_precision = false;                    //
          break;                              //  Stop While Internal
                                          //  Changes from precision
        }
        else
        {
          for (list<Tcexamples>::const_iterator it = set_fobj.begin(); it != set_fobj.end(); ++it)
          {
            if((  convert.convertStringDouble(tratar_contra_exemplo._fjob) >= convert.convertStringDouble((*it)._fjob)) )
            {
              minimo_existente_maior = true;
            }
          }

          if(minimo_existente_maior)
          {                                                      // If value check

            compensar_fobj = compensar_fobj * 10;                                  // Increase the Compensator
            minimo_existente_maior = false;                                      //   Reset condition of this error, if this
            new_fiS = ex.fobj_current + " -" + convert.convertDoubleString(compensar_fobj);              // Generates the new F_I Compensated
            ex.fobj_current = new_fiS;

            gerar_arquivos.create_mi_ESBMC_G_Z3(ex, p);               // Creates min files considering new F_I with new compensator

          }
          else
          {

            ex.fobj_current = tratar_contra_exemplo._fjob;              // Update last minimum value Valid
            v_log++;                                        // Incrmenta Log
            set_fobj.push_front(tratar_contra_exemplo);                    // Saved in the Minimal List

            cout << "  f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

            new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
            ex.fobj_current = new_fiS;

            gerar_arquivos.create_mi_ESBMC_G_Z3(ex, p);   // Create the other files min
          }

        }
          
      }    //  Fim While Interno

      p = p * 10;
      keep_precision = true;
      compensar_fobj =  0.00001;        // Reset compensator

      new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
      ex.fobj_current = new_fiS;

      gerar_arquivos.create_mi_ESBMC_G_Z3(ex, p);

    }

    cout << "####################################" << endl ;
    cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

  }


  /*******************************************************************************************************\
  Method: run_ESBMC_Mathsat_G(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Performs optimization with ( ESBMC + MathSAT + CEGIO-G)
  \*******************************************************************************************************/

  void Run_algorithm::run_ESBMC_MATHSAT_G(Set ex)
  {

    cout << "#############################################" << endl;
    cout << "#     ESBMC - Mathsat - Alg Generalized     #" << endl;
    cout << "#############################################" << endl;

  // Manipulation Variables with Objects and Functions
    Generate_files gerar_arquivos;
    Tcexamples tratar_contra_exemplo;
    Tcexamples list_fobj;
    list<Tcexamples> set_fobj;

  // Adjustment Variables
    string command = "";
    int p = 1;
    bool keep_precision = true;
    bool minimo_existente_maior = false;
    string new_fiS;
    float compensar_fobj;
    string compensar_fobjS;
    int v_log = 1;
    string v_logS;
    int precisionLoop = pow(10,ex.precision);

    ex.restrictions = generate_assumes(ex,p);

    gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);    //
    command  = "gcc " + ex.name_function + ".c -o value_min";            //  Creates the function binary
    system(command.c_str());                            //

    cout << endl << "            Start Value: " + ex.l_sup << endl;
                                                                            
    gerar_arquivos.create_mi_ESBMC_G_Mathsat(ex, p);   // Creates the first min file

    compensar_fobj =  0.00001;    //  Set standard compensator

    while( p<=precisionLoop )
    {

      cout << endl << " ******************************** " << endl ;

      //break;

      while( keep_precision )
      {
                                                //
        v_logS = "log_" + convert.convertDoubleString(v_log);              // Increase Log
                                                //

        command  = "./esbmc min_" + ex.name_function + ".c --floatbv --mathsat > " + v_logS;  // Run Verification
        system(command.c_str());                            

                                      //
        tratar_contra_exemplo.take_CE_ESBMC_Mathsat(v_logS,p);    //  Search the status of the verification (Success or Failure)
                                      //  Find values of x1, x2 and fobj

                                          
        if(tratar_contra_exemplo._verification == 1)            
        {                                  //  Verification Success
          v_log++;
          keep_precision = false;                    //
          break;                              //  Stop While Internal
                                          //  Changes from precision
        }else
        {

          for (list<Tcexamples>::const_iterator it = set_fobj.begin(); it != set_fobj.end(); ++it)
          {                                                          //
            if((  convert.convertStringDouble(tratar_contra_exemplo._fjob) >= convert.convertStringDouble((*it)._fjob)) )
            {                                                        // Checks if this Fobj already exists
              minimo_existente_maior = true;                                        // Check if this Fobj is larger than the others found
            }                                                        //
          }

          if(minimo_existente_maior)
          {                                    // If value check

            compensar_fobj = compensar_fobj * 10;                            // Increase the Compensator
            minimo_existente_maior = false;                                //   Reset condition of this error, if this
            new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);      // Generates the new F_I Compensated
            ex.fobj_current = new_fiS;

            gerar_arquivos.create_mi_ESBMC_G_Mathsat(ex, p);               // Creates min files considering new F_I with new compensator

          }else
          {

            ex.fobj_current  = tratar_contra_exemplo._fjob;                      // Update last minimum value Valid
            v_log++;                                        // Incrmenta Log
            set_fobj.push_front(tratar_contra_exemplo);                    // Saved in the Minimal List

            cout << "  f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

            new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);    // Generates the new F_I Compensated
            ex.fobj_current = new_fiS;

            gerar_arquivos.create_mi_ESBMC_G_Mathsat(ex, p);   // Create the other files min
          }

        }

      }    //  Fim While Interno

      p = p * 10;
      keep_precision = true;
      compensar_fobj =  0.00001;        // Reset compensator

      new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
      ex.fobj_current = new_fiS;

      gerar_arquivos.create_mi_ESBMC_G_Mathsat(ex, p);

    }

    cout << "####################################" << endl ;
    cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

  }


  /*******************************************************************************************************\
  Method: run_ESBMC_BOOLECTOR_S(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Performs optimization with ( ESBMC + Boolector + GEGIO-S )
  \*******************************************************************************************************/

  void Run_algorithm::run_ESBMC_BOOLECTOR_S(Set ex)
  {

    cout << "#############################################" << endl;
    cout << "#     ESBMC - Alg Positive - Boolector      #" << endl;
    cout << "#############################################" << endl;

    // Manipulation Variables with Objects and Functions
      Generate_files gerar_arquivos;
      Tcexamples tratar_contra_exemplo;
      Tcexamples list_fobj;
      list<Tcexamples> set_fobj;

    // Adjustment Variables
      string command = "";
      int p = 1;
      bool keep_precision = true;
      bool minimo_existente_maior = false;
      string new_fiS;
      float compensar_fobj;
      string compensar_fobjS;
      int v_log = 1;
      string v_logS;
      int precisionLoop = pow(10,ex.precision);

      ex.restrictions = generate_assumes(ex,p);

      gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);    //
      command  = "gcc " + ex.name_function + ".c -o value_min";            //  Creates the function binary
      system(command.c_str());                            //

      cout << endl << "            Start Value: " + ex.l_sup << endl;
                                                                              
      gerar_arquivos.create_mi_ESBMC_S_Boolector(ex, p);   // Creates the first min file

                      //
      compensar_fobj =  0.00001;    //  Set standard compensator
                      //
      int cont=0, cont2=0;

      while( p<=precisionLoop )
      {

        cout << endl << " ******************************** " << endl ;

        while( keep_precision )
        {
                                                  //
          v_logS = "log_" + convert.convertDoubleString(v_log);              // Increase Log
                                                  //

                                                  //
          command  = "./esbmc min_" + ex.name_function + ".c --boolector > " + v_logS;  // Run Verification
          system(command.c_str());                            //

                                        //
          tratar_contra_exemplo.take_CE_ESBMC_Boolector(v_logS,p);  //  Search the status of the verification (Success or Failure)
                                        //  Find values of x1, x2 and fobj

                                            //
          if(tratar_contra_exemplo._verification == 1)
          {                                  //  Verification Success
            v_log++;
            keep_precision = false;                      //
            break;                              //  Stop While Internal
                                            //  Changes from precision
          }else
          {

            for (list<Tcexamples>::const_iterator it = set_fobj.begin(); it != set_fobj.end(); ++it)
            {            //
              if((  convert.convertStringDouble(tratar_contra_exemplo._fjob) >= convert.convertStringDouble((*it)._fjob)) )
              {                                                          // Checks if this Fobj already exists
                minimo_existente_maior = true;                                          // Check if this Fobj is larger than the others found
              }                                                          //
            }

            if(minimo_existente_maior)
            {                                            // If value check

              compensar_fobj = compensar_fobj * 10;                        // Increase the Compensator
              minimo_existente_maior = false;                            //   Reset condition of this error, if this

              new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);  // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;
              gerar_arquivos.create_mi_ESBMC_S_Boolector(ex, p);                   // Creates min files considering new F_I with new compensator


            }else
            {

              ex.fobj_current  = tratar_contra_exemplo._fjob;                      // Update last minimum value Valid
              v_log++;                                        // Incrmenta Log
              set_fobj.push_front(tratar_contra_exemplo);                        // Saved in the Minimal List

              cout << "  f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

              new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;
              gerar_arquivos.create_mi_ESBMC_S_Boolector(ex, p);   // Create the other files min
            }

          }

          cont++;
        }    //  Fim While Interno

        cont2++;

        p = p * 10;
        keep_precision = true;
        compensar_fobj =  0.00001;        // Reset compensator

        new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
        ex.fobj_current = new_fiS;
        gerar_arquivos.create_mi_ESBMC_S_Boolector(ex, p);

      }

      cout << "####################################" << endl ;
      cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

  }


  /*******************************************************************************************************\
  Method: run_ESBMC_Z3_S(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Performs optimization with ( ESBMC + Z3 + GEGIO-S )
  \*******************************************************************************************************/

  void Run_algorithm::run_ESBMC_Z3_S(Set ex)
  {

    cout << "#############################################" << endl;
    cout << "#     ESBMC - Alg Positive - Z3             #" << endl;
    cout << "#############################################" << endl;

    // Manipulation Variables with Objects and Functions
    Generate_files gerar_arquivos;
    Tcexamples tratar_contra_exemplo;
    Tcexamples list_fobj;
    list<Tcexamples> set_fobj;

    // Adjustment Variables
    string command = "";
    int p = 1;
    bool keep_precision = true;
    bool minimo_existente_maior = false;
    string new_fiS;
    float compensar_fobj;
    string compensar_fobjS;
    int v_log = 1;
    string v_logS;
    int precisionLoop = pow(10,ex.precision);

    ex.restrictions = generate_assumes(ex,p);

    gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);    //
    command  = "gcc " + ex.name_function + ".c -o value_min";            //  Creates the function binary
    system(command.c_str());                            //

    cout << endl << "            Start Value: " + ex.l_sup << endl;
                                                                            
    gerar_arquivos.create_mi_ESBMC_S_Z3(ex, p);   // Creates the first min file

                    //
    compensar_fobj =  0.00001;    //  Set standard compensator
                    //
    int cont=0, cont2=0;

    while( p<=precisionLoop )
    {

      cout << endl << " ******************************** " << endl ;

      while( keep_precision )
      {
                                                //
        v_logS = "log_" + convert.convertDoubleString(v_log);              // Increase Log
                                                //

                                                    //
        command  = "./esbmc min_" + ex.name_function + ".c --z3 > " + v_logS;          // Run Verification
        system(command.c_str());                                //

                                      //
        tratar_contra_exemplo.take_CE_ESBMC_Z3(v_logS,p);      //  Search the status of the verification (Success or Failure)
                                      //  Find values of x1, x2 and fobj

                                          //
        if(tratar_contra_exemplo._verification == 1)
        {                                  //  Verification Success
          v_log++;
          keep_precision = false;                      //
          break;                              //  Stop While Internal
                                          //  Changes from precision
        }else
        {

          for (list<Tcexamples>::const_iterator it = set_fobj.begin(); it != set_fobj.end(); ++it)
          {    //
            if((  convert.convertStringDouble(tratar_contra_exemplo._fjob) >= convert.convertStringDouble((*it)._fjob)) )
            {                                                  // Checks if this Fobj already exists
              minimo_existente_maior = true;                                  // Check if this Fobj is larger than the others found
            }                                                  //
          }

          if(minimo_existente_maior)
          {                                              // If value check

            compensar_fobj = compensar_fobj * 10;                          // Increase the Compensator
            minimo_existente_maior = false;                              //   Reset condition of this error, if this

            new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);    // Generates the new F_I Compensated
            ex.fobj_current = new_fiS;
            gerar_arquivos.create_mi_ESBMC_S_Z3(ex, p);                       // Creates min files considering new F_I with new compensator


          }else
          {

            ex.fobj_current  = tratar_contra_exemplo._fjob;                      // Update last minimum value Valid
            v_log++;                                        // Incrmenta Log
            set_fobj.push_front(tratar_contra_exemplo);                        // Saved in the Minimal List

            cout << "  f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

            new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
            ex.fobj_current = new_fiS;
            gerar_arquivos.create_mi_ESBMC_S_Z3(ex, p);   // Create the other files min
          }

        }

        cont++;
      }    //  Fim While Interno

      cont2++;

      p = p * 10;
      keep_precision = true;
      compensar_fobj =  0.00001;        // Reset compensator

      new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
      ex.fobj_current = new_fiS;
      gerar_arquivos.create_mi_ESBMC_S_Z3(ex, p);

    }

    cout << "####################################" << endl ;
    cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

  }


  /*******************************************************************************************************\
  Method: run_ESBMC_MATHSAT_S(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Performs optimization with ( ESBMC + Mathsat + GEGIO-S )
  \*******************************************************************************************************/

  void Run_algorithm::run_ESBMC_MATHSAT_S(Set ex)
  {

    cout << "#############################################" << endl;
    cout << "#     ESBMC - Mathsat - Alg Simplified      #" << endl;
    cout << "#############################################" << endl;

    // Manipulation Variables with Objects and Functions
    Generate_files gerar_arquivos;
    Tcexamples tratar_contra_exemplo;
    Tcexamples list_fobj;
    list<Tcexamples> set_fobj;

    // Adjustment Variables
    string command = "";
    int p = 1;
    bool keep_precision = true;
    bool minimo_existente_maior = false;
    string new_fiS;
    float compensar_fobj;
    string compensar_fobjS;
    int v_log = 1;
    string v_logS;
    int precisionLoop = pow(10,ex.precision);

    ex.restrictions = generate_assumes(ex,p);

    gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);    //
    command  = "gcc " + ex.name_function + ".c -o value_min";            //  Creates the function binary
    system(command.c_str());                            //

    cout << endl << "            Start Value: " + ex.l_sup << endl;
                                                                          
    gerar_arquivos.create_mi_ESBMC_S_Mathsat(ex, p);   // Creates the first min file

                    //
    compensar_fobj =  0.00001;    //  Set standard compensator
                    //
    int cont=0, cont2=0;

    while( p<=precisionLoop )
    {

      cout << endl << " ******************************** " << endl ;

      while( keep_precision )
      {
                                                //
        v_logS = "log_" + convert.convertDoubleString(v_log);                  // Increase Log
                                                //

                                                    //
        command  = "./esbmc min_" + ex.name_function + ".c --mathsat --floatbv > " + v_logS;  // Run Verification
        system(command.c_str());                                //

                                      //
        tratar_contra_exemplo.take_CE_ESBMC_Mathsat(v_logS,p);    //  Search the status of the verification (Success or Failure)
                                      //  Find values of x1, x2 and fobj

                                        
        if(tratar_contra_exemplo._verification == 1)
        {                                //  Verification Success
          v_log++;
          keep_precision = false;                    //
          break;                            //  Stop While Internal
                                        //  Changes from precision
        }else
        {

          for (list<Tcexamples>::const_iterator it = set_fobj.begin(); it != set_fobj.end(); ++it)
          {            //
            if((  convert.convertStringDouble(tratar_contra_exemplo._fjob) >= convert.convertStringDouble((*it)._fjob)) )
            {                                // Checks if this Fobj already exists
              minimo_existente_maior = true;                  // Check if this Fobj is larger than the others found
            }                                
          }

          if(minimo_existente_maior)
          {                                                // If value check

            compensar_fobj = compensar_fobj * 10;                            // Increase the Compensator
            minimo_existente_maior = false;                                //   Reset condition of this error, if this

            new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);      // Generates the new F_I Compensated
            ex.fobj_current = new_fiS;  
            gerar_arquivos.create_mi_ESBMC_S_Mathsat(ex, p);                       // Creates min files considering new F_I with new compensator


          }else
          {

            ex.fobj_current  = tratar_contra_exemplo._fjob;                        // Update last minimum value Valid
            v_log++;                                          // Incrmenta Log
            set_fobj.push_front(tratar_contra_exemplo);                          // Saved in the Minimal List

            cout << "  f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

            new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);      // Generates the new F_I Compensated
            ex.fobj_current = new_fiS;
            gerar_arquivos.create_mi_ESBMC_S_Mathsat(ex, p);   // Create the other files min
          }

        }

        cont++;
      }    //  Fim While Interno

      cont2++;

      p = p * 10;
      keep_precision = true;
      compensar_fobj =  0.00001;        // Reset compensator

      new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
      ex.fobj_current = new_fiS;
      gerar_arquivos.create_mi_ESBMC_S_Mathsat(ex, p);

    }

    cout << "####################################" << endl ;
    cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

  }


  /*******************************************************************************************************\
  Method: run_ESBMC_BOOLECTOR_C(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Performs optimization with ( ESBMC + Boolector + GEGIO-F )
  \*******************************************************************************************************/

  void Run_algorithm::run_ESBMC_BOOLECTOR_C(Set ex)
  {

    cout << "###########################################" << endl;
    cout << "#     ESBMC - BOOLECTOR - Alg CONVEX      #" << endl;
    cout << "###########################################" << endl;

    // Manipulation Variables with Objects and Functions
      Generate_files gerar_arquivos;
      Tcexamples tratar_contra_exemplo;
      Tcexamples list_fobj;
      list<Tcexamples> set_fobj;

    // Adjustment Variables
      string command = "";
      int p = 1;
      bool keep_precision = true;
      bool minimo_existente_maior = false;
      string new_fiS;
      float compensar_fobj;
      string compensar_fobjS;
      int v_log = 1;
      string v_logS;
      int precisionLoop = pow(10,ex.precision);

      gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);    //
      command  = "gcc " + ex.name_function + ".c -o value_min";            //  Creates the function binary
      system(command.c_str());                            //

      ex.type_restrictions = 0;
      ex.restrictions = generate_assumes(ex, p);                                                                              //
      gerar_arquivos.create_mi_ESBMC_C_Boolector(ex, p);     // Creates the first min file
      compensar_fobj =  0.00001;                //  Set standard compensator

      cout << endl << "            Start Value: " + ex.l_sup << endl;


      while( p<=precisionLoop )
      {

        cout << endl << " ******************************** " << endl ;

        while( keep_precision )
        {

          v_logS = "log_" + convert.convertDoubleString(v_log);              // Increase Log

          command  = "./esbmc min_" + ex.name_function + ".c --boolector > " + v_logS;  // Run Verification
          system(command.c_str());

          tratar_contra_exemplo.take_CE_ESBMC_Boolector(v_logS,p);  //  Search the status of the verification (Success or Failure)
                                        //  Find values of x1, x2 and fobj

          if(tratar_contra_exemplo._verification == 1)
          {                              //  Verification Success
            v_log++;        
            keep_precision = false;                    //
            break;                          //  Stop While Internal
                                        //  Changes from precision
          }else
          {

            for (list<Tcexamples>::const_iterator it = set_fobj.begin(); it != set_fobj.end(); ++it)
            {            //
              if((  convert.convertStringDouble(tratar_contra_exemplo._fjob) >= convert.convertStringDouble((*it)._fjob)) )
              {                                              // Checks if this Fobj already exists
                minimo_existente_maior = true;                              // Check if this Fobj is larger than the others found
              }                                              //
            }

            if(minimo_existente_maior)
            {                                              // If value check

              compensar_fobj = compensar_fobj * 10;                          // Increase the Compensator
              minimo_existente_maior = false;                              //   Reset condition of this error, if this
              new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);    // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;
              gerar_arquivos.create_mi_ESBMC_C_Boolector(ex, p);
            }else
            {

              ex.fobj_current = tratar_contra_exemplo._fjob;                      // Update last minimum value Valid
              v_log++;                                        // Incrmenta Log
              set_fobj.push_front(tratar_contra_exemplo);                        // Saved in the Minimal List

              cout << "  f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

              new_fiS = ex.fobj_current + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;

              gerar_arquivos.create_mi_ESBMC_C_Boolector(ex, p);   // Create the other files min

            }

          }

        }    //  Fim While Interno

        ex.type_restrictions = 1;

        p = p * 10;
        keep_precision = true;

        compensar_fobj =  0.00001;        // Reset compensator

        new_fiS = ex.fobj_current + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
        ex.fobj_current = new_fiS;

        ex._x1 = convert.convertStringDouble(tratar_contra_exemplo._x1);
        ex._x2 = convert.convertStringDouble(tratar_contra_exemplo._x2);

        ex.restrictions = generate_assumes(ex, p);

        gerar_arquivos.create_mi_ESBMC_C_Boolector(ex, p);   // Create the other files min
      }

      cout << "####################################" << endl ;
      cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

  }


  /*******************************************************************************************************\
  Method: run_ESBMC_Z3_C(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Performs optimization with ( ESBMC + Z3 + GEGIO-F )
  \*******************************************************************************************************/

  void Run_algorithm::run_ESBMC_Z3_C(Set ex)
  {

    // Manipulation Variables with Objects and Functions
      Generate_files gerar_arquivos;
      Tcexamples tratar_contra_exemplo;
      Tcexamples list_fobj;
      list<Tcexamples> set_fobj;

    // Adjustment Variables
      string command = "";
      int p = 1;
      bool keep_precision = true;
      bool minimo_existente_maior = false;
      string new_fiS;
      float compensar_fobj;
      string compensar_fobjS;
      int v_log = 1;
      string v_logS;
      int precisionLoop = pow(10,ex.precision);

      gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);    //
      command  = "gcc " + ex.name_function + ".c -o value_min";            //  Creates the function binary
      system(command.c_str());                            //

      ex.type_restrictions = 0;
      ex.restrictions = generate_assumes(ex, p);                                                                              //
      gerar_arquivos.create_mi_ESBMC_C_Z3(ex, p);     // Creates the first min file
      compensar_fobj =  0.00001;              //  Set standard compensator

      cout << endl << "            Start Value: " + ex.l_sup << endl;


      while( p<=precisionLoop )
      {

        cout << endl << " ******************************** " << endl ;

        while( keep_precision )
        {

          v_logS = "log_" + convert.convertDoubleString(v_log);          // Increase Log

          command  = "./esbmc min_" + ex.name_function + ".c --z3 > " + v_logS;  // Run Verification
          system(command.c_str());

          tratar_contra_exemplo.take_CE_ESBMC_Z3(v_logS,p);      //  Search the status of the verification (Success or Failure)
                                        //  Find values of x1, x2 and fobj

          if(tratar_contra_exemplo._verification == 1)
          {                              //  Verification Success
            v_log++;
            keep_precision = false;                  //
            break;                          //  Stop While Internal
                                        //  Changes from precision
          }else
          {

            for (list<Tcexamples>::const_iterator it = set_fobj.begin(); it != set_fobj.end(); ++it)
            {  
              if((  convert.convertStringDouble(tratar_contra_exemplo._fjob) >= convert.convertStringDouble((*it)._fjob)) )
              {                                          // Checks if this Fobj already exists
                minimo_existente_maior = true;                          // Check if this Fobj is larger than the others found
              }                                          //
            }

            if(minimo_existente_maior)
            {                                              // If value check

              compensar_fobj = compensar_fobj * 10;                          // Increase the Compensator
              minimo_existente_maior = false;                              //   Reset condition of this error, if this
              new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);    // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;
              gerar_arquivos.create_mi_ESBMC_C_Z3(ex, p);
            }else
            {

              ex.fobj_current = tratar_contra_exemplo._fjob;                      // Update last minimum value Valid
              v_log++;                                        // Incrmenta Log
              set_fobj.push_front(tratar_contra_exemplo);                        // Saved in the Minimal List

              cout << "  f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

              new_fiS = ex.fobj_current + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;

              gerar_arquivos.create_mi_ESBMC_C_Z3(ex, p);   // Create the other files min

            }

          }

        }    //  Fim While Interno

        ex.type_restrictions = 1;

        p = p * 10;
        keep_precision = true;

        compensar_fobj =  0.00001;        // Reset compensator

        new_fiS = ex.fobj_current + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
        ex.fobj_current = new_fiS;

        ex._x1 = convert.convertStringDouble(tratar_contra_exemplo._x1);
        ex._x2 = convert.convertStringDouble(tratar_contra_exemplo._x2);

        ex.restrictions = generate_assumes(ex, p);
        gerar_arquivos.create_mi_ESBMC_C_Z3(ex, p);   // Create the other files min
      }

      cout << "####################################" << endl ;
      cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

    }


  /*******************************************************************************************************\
  Method: run_ESBMC_MATHSAT_C(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Performs optimization with ( ESBMC + M<athsat + GEGIO-F )
  \*******************************************************************************************************/

  void Run_algorithm::run_ESBMC_MATHSAT_C(Set ex){

    cout << "###########################################" << endl;
    cout << "#     ESBMC - MATHSAT - Alg CONVEX        #" << endl;
    cout << "###########################################" << endl;

    // Manipulation Variables with Objects and Functions
      Generate_files gerar_arquivos;
      Tcexamples tratar_contra_exemplo;
      Tcexamples list_fobj;
      list<Tcexamples> set_fobj;

    // Adjustment Variables
      string command = "";
      int p = 1;
      bool keep_precision = true;
      bool minimo_existente_maior = false;
      string new_fiS;
      float compensar_fobj;
      string compensar_fobjS;
      int v_log = 1;
      string v_logS;
      int precisionLoop = pow(10,ex.precision);

      gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);    //
      command  = "gcc " + ex.name_function + ".c -o value_min";            //  Creates the function binary
      system(command.c_str());                            //

      ex.type_restrictions = 0;
      ex.restrictions = generate_assumes(ex, p);                                                                              //
      gerar_arquivos.create_mi_ESBMC_C_Mathsat(ex, p);     // Creates the first min file
      compensar_fobj =  0.00001;                //  Set standard compensator

      cout << endl << "            Start Value: " + ex.l_sup << endl;


      while( p<=precisionLoop )
      {

        cout << endl << " ******************************** " << endl ;

        while( keep_precision )
        {

          v_logS = "log_" + convert.convertDoubleString(v_log);                  // Increase Log

          command  = "./esbmc min_" + ex.name_function + ".c --mathsat --floatbv > " + v_logS;  // Run Verification
          system(command.c_str());

          tratar_contra_exemplo.take_CE_ESBMC_Mathsat(v_logS,p);    //  Search the status of the verification (Success or Failure)
                                        //  Find values of x1, x2 and fobj

          if(tratar_contra_exemplo._verification == 1)
          {                                //  Verification Success
            v_log++;
            keep_precision = false;                    //
            break;                            //  Stop While Internal
                                          //  Changes from precision
          }else
          {

            for (list<Tcexamples>::const_iterator it = set_fobj.begin(); it != set_fobj.end(); ++it)
            {                //
              if((  convert.convertStringDouble(tratar_contra_exemplo._fjob) >= convert.convertStringDouble((*it)._fjob)) )
              {                                                          // Checks if this Fobj already exists
                minimo_existente_maior = true;                                          // Check if this Fobj is larger than the others found
              }                                                          //
            }

            if(minimo_existente_maior)
            {                                              // If value check

              compensar_fobj = compensar_fobj * 10;                          // Increase the Compensator
              minimo_existente_maior = false;                              //   Reset condition of this error, if this
              new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);    // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;
              gerar_arquivos.create_mi_ESBMC_C_Mathsat(ex, p);
            }else
            {

              ex.fobj_current = tratar_contra_exemplo._fjob;                      // Update last minimum value Valid
              v_log++;                                        // Incrmenta Log
              set_fobj.push_front(tratar_contra_exemplo);                        // Saved in the Minimal List

              cout << "  f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

              new_fiS = ex.fobj_current + " -" + convert.convertDoubleString(compensar_fobj);      // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;

              gerar_arquivos.create_mi_ESBMC_C_Mathsat(ex, p);   // Create the other files min

            }

          }

        }    //  Fim While Interno

        ex.type_restrictions = 1;

        p = p * 10;
        keep_precision = true;

        compensar_fobj =  0.00001;        // Reset compensator

        new_fiS = ex.fobj_current + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
        ex.fobj_current = new_fiS;

        ex._x1 = convert.convertStringDouble(tratar_contra_exemplo._x1);
        ex._x2 = convert.convertStringDouble(tratar_contra_exemplo._x2);

        ex.restrictions = generate_assumes(ex, p);

        gerar_arquivos.create_mi_ESBMC_C_Mathsat(ex, p);   // Create the other files min
      }

      cout << "####################################" << endl ;
      cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

  }


  /*******************************************************************************************************\
  Method: run_CBMC_MINISAT_G(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Performs optimization with ( CBMC + MiniSAT + GEGIO-G )
  \*******************************************************************************************************/

  void Run_algorithm::run_CBMC_MINISAT_G(Set ex){

    cout << "#############################################" << endl;
    cout << "#     CBMC - Minisat - Alg Generalized      #" << endl;
    cout << "#############################################" << endl;

    // Manipulation Variables with Objects and Functions
      Generate_files gerar_arquivos;
      Tcexamples tratar_contra_exemplo;
      Tcexamples list_fobj;
      list<Tcexamples> set_fobj;

    // Adjustment Variables
      string command = "";
      int p = 1;
      bool keep_precision = true;
      bool minimo_existente_maior = false;
      string new_fiS;
      float compensar_fobj;
      string compensar_fobjS;
      int v_log = 1;
      string v_logS;
      int precisionLoop = pow(10,ex.precision);

      ex.type_restrictions = 2;
      ex.restrictions = generate_assumes(ex,p);

      gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);    //
      command  = "gcc " + ex.name_function + ".c -o value_min";            //  Creates the function binary
      system(command.c_str());                            //

      cout << endl << "            Start Value: " + ex.l_sup << endl;
                                                                              
      gerar_arquivos.create_mi_CBMC_G_Minisat(ex, p);   // Creates the first min file

                      //
      compensar_fobj =  0.00001;    //  Set standard compensator
                      //
                                                                    

      while( p<=precisionLoop )
      {

        cout << endl << " ******************************** " << endl ;

        while( keep_precision )
        {
                                                      //
          v_logS = "log_" + convert.convertDoubleString(v_log);                  // Increase Log
                                                      //
          command  = "./cbmc min_" + ex.name_function + ".c  > " + v_logS + " 2>> " + v_logS;    // Run Verification
          system(command.c_str());                                //

                                        //
          tratar_contra_exemplo.take_CE_CBMC_Minisat(v_logS,p);    //  Search the status of the verification (Success or Failure)
                                        //  Find values of x1, x2 and fobj


          if(tratar_contra_exemplo._verification == 1)
          {          //  Verification Success
            v_log++;
            keep_precision = false;                    //
            break;                              //  Stop While Internal
                                            //  Changes from precision
          }else
          {

            for (list<Tcexamples>::const_iterator it = set_fobj.begin(); it != set_fobj.end(); ++it)
            {                                                            //
              if((  convert.convertStringDouble(tratar_contra_exemplo._fjob) >= convert.convertStringDouble((*it)._fjob)) )
              {                                                          // Checks if this Fobj already exists
                minimo_existente_maior = true;                                          // Check if this Fobj is larger than the others found
              }                                                          //
            }

            if(minimo_existente_maior)
            {                                            // If value check

              compensar_fobj = compensar_fobj * 10;                        // Increase the Compensator
              minimo_existente_maior = false;                            //   Reset condition of this error, if this
              new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);  // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;

              gerar_arquivos.create_mi_CBMC_G_Minisat(ex, p);                   // Creates min files considering new F_I with new compensator

            }else
            {

              ex.fobj_current  = tratar_contra_exemplo._fjob;                    // Update last minimum value Valid
              v_log++;                                      // Incrmenta Log
              set_fobj.push_front(tratar_contra_exemplo);                      // Saved in the Minimal List

              cout << "  f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

              new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;

              gerar_arquivos.create_mi_CBMC_G_Minisat(ex, p);   // Create the other files min
            }

          }

        }    //  Fim While Interno

        p = p * 10;
        keep_precision = true;
        compensar_fobj =  0.00001;        // Reset compensator

        new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
        ex.fobj_current = new_fiS;

        gerar_arquivos.create_mi_CBMC_G_Minisat(ex, p);

      }

      cout << "####################################" << endl ;
      cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;
    }


  /*******************************************************************************************************\
  Method: run_CBMC_MINISAT_S(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Performs optimization with ( CBMC + MiniSAT + GEGIO-S )
  \*******************************************************************************************************/

  void Run_algorithm::run_CBMC_MINISAT_S(Set ex)
  {

    cout << "#############################################" << endl;
    cout << "#     CBMC - Minisat  - Alg Simplified      #" << endl;
    cout << "#############################################" << endl;

    // Manipulation Variables with Objects and Functions
      Generate_files gerar_arquivos;
      Tcexamples tratar_contra_exemplo;
      Tcexamples list_fobj;
      list<Tcexamples> set_fobj;

    // Adjustment Variables
      string command = "";
      int p = 1;
      bool keep_precision = true;
      bool minimo_existente_maior = false;
      string new_fiS;
      float compensar_fobj;
      string compensar_fobjS;
      int v_log = 1;
      string v_logS;
      int precisionLoop = pow(10,ex.precision);

      ex.type_restrictions = 2;
      ex.restrictions = generate_assumes(ex,p);

      gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);    //
      command  = "gcc " + ex.name_function + ".c -o value_min";            //  Creates the function binary
      system(command.c_str());                            //

      cout << endl << "            Start Value: " + ex.l_sup << endl;
                                                                              
      gerar_arquivos.create_mi_CBMC_S_Minisat(ex, p);                 // Creates the first min file

      compensar_fobj =  0.00001;                            //  Set standard compensator
      int cont=0, cont2=0;

      while( p<=precisionLoop )
      {

        cout << endl << " ******************************** " << endl ;

        while( keep_precision )
        {

          v_logS = "log_" + convert.convertDoubleString(v_log);                      // Increase Log

          command  = "./cbmc min_" + ex.name_function + ".c  > " + v_logS + " 2>> " + v_logS;    // Run Verification
          system(command.c_str());                                //

          tratar_contra_exemplo.take_CE_CBMC_Minisat(v_logS,p);      //  Search the status of the verification (Success or Failure)
                                          //  Find values of x1, x2 and fobj

                                            //
          if(tratar_contra_exemplo._verification == 1)
          {                                  //  Verification Success
            v_log++;
            keep_precision = false;                      //
            break;                              //  Stop While Internal
                                            //  Changes from precision
          }else
          {

            for (list<Tcexamples>::const_iterator it = set_fobj.begin(); it != set_fobj.end(); ++it)
            {    
              if((  convert.convertStringDouble(tratar_contra_exemplo._fjob) >= convert.convertStringDouble((*it)._fjob)) )
              {                                                  // Checks if this Fobj already exists
                minimo_existente_maior = true;                                  // Check if this Fobj is larger than the others found
              }                                                  //
            }

            if(minimo_existente_maior)
            {                            // If value check

              compensar_fobj = compensar_fobj * 10;                    // Increase the Compensator
              minimo_existente_maior = false;                        //   Reset condition of this error, if this

              new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);      // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;
              gerar_arquivos.create_mi_CBMC_S_Minisat(ex, p);               // Creates min files considering new F_I with new compensator


            }else
            {

              ex.fobj_current  = tratar_contra_exemplo._fjob;                        // Update last minimum value Valid
              v_log++;                                        // Incrmenta Log
              set_fobj.push_front(tratar_contra_exemplo);                    // Saved in the Minimal List

              cout << "  f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

              new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;
              gerar_arquivos.create_mi_CBMC_S_Minisat(ex, p);   // Create the other files min
            }

          }

          cont++;
        }    //  Fim While Interno

        cont2++;

        p = p * 10;
        keep_precision = true;
        compensar_fobj =  0.00001;        // Reset compensator

        new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
        ex.fobj_current = new_fiS;
        gerar_arquivos.create_mi_CBMC_S_Minisat(ex, p);

      }

      cout << "####################################" << endl ;
      cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

  }

  /*******************************************************************************************************\
  Method: run_CBMC_MINISAT_C(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Performs optimization with ( CBMC + MiniSAT + GEGIO-F )
  \*******************************************************************************************************/

  void Run_algorithm::run_CBMC_MINISAT_C(Set ex)
  {
    cout << "###########################################" << endl;
    cout << "#     CBMC - MINISAT - Alg CONVEX        #" << endl;
    cout << "###########################################" << endl;

    // Manipulation Variables with Objects and Functions
      Generate_files gerar_arquivos;
      Tcexamples tratar_contra_exemplo;
      Tcexamples list_fobj;
      list<Tcexamples> set_fobj;

    // Adjustment Variables
      string command = "";
      int p = 1;
      bool keep_precision = true;
      bool minimo_existente_maior = false;
      string new_fiS;
      float compensar_fobj;
      string compensar_fobjS;
      int v_log = 1;
      string v_logS;
      int precisionLoop = pow(10,ex.precision);

      gerar_arquivos.create_f(ex.name_function, ex.code_function, ex.typeData);    //
      command  = "gcc " + ex.name_function + ".c -o value_min";            //  Creates the function binary
      system(command.c_str());

      ex.type_restrictions = 3;
      ex.restrictions = generate_assumes(ex, p);                                                                              //
      gerar_arquivos.create_mi_CBMC_C_Minisat(ex, p);     // Creates the first min file
      compensar_fobj =  0.00001;                //  Set standard compensator

      cout << endl << "            Start Value: " + ex.l_sup << endl;


      while( p<=precisionLoop )
      {

        cout << endl << " ******************************** " << endl ;

        while( keep_precision )
        {

          v_logS = "log_" + convert.convertDoubleString(v_log);                  // Increase Log

          command  = "./cbmc min_" + ex.name_function + ".c  > " + v_logS + " 2>> " + v_logS;    // Run Verification
          system(command.c_str());

          tratar_contra_exemplo.take_CE_CBMC_Minisat(v_logS,p);  //  Search the status of the verification (Success or Failure)
                                      //  Find values of x1, x2 and fobj

          if(tratar_contra_exemplo._verification == 1)
          {                            //  Verification Success
            v_log++;
            keep_precision = false;                //
            break;                        //  Stop While Internal
                                      //  Changes from precision
          }else
          {

            for (list<Tcexamples>::const_iterator it = set_fobj.begin(); it != set_fobj.end(); ++it)
            {                //
              if((  convert.convertStringDouble(tratar_contra_exemplo._fjob) >= convert.convertStringDouble((*it)._fjob)) )
              {                                // Checks if this Fobj already exists
                minimo_existente_maior = true;                // Check if this Fobj is larger than the others found
              }                                //
            }

            if(minimo_existente_maior)
            {                                  // If value check

              compensar_fobj = compensar_fobj * 10;                    // Increase the Compensator
              minimo_existente_maior = false;                        //   Reset condition of this error, if this
              new_fiS = ex.fobj_current  + " -" + convert.convertDoubleString(compensar_fobj);    // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;
              gerar_arquivos.create_mi_CBMC_C_Minisat(ex, p);
            }else
            {

              ex.fobj_current = tratar_contra_exemplo._fjob;                      // Update last minimum value Valid
              v_log++;                                        // Incrmenta Log
              set_fobj.push_front(tratar_contra_exemplo);                    // Saved in the Minimal List

              cout << "  f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

              new_fiS = ex.fobj_current + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
              ex.fobj_current = new_fiS;

              gerar_arquivos.create_mi_CBMC_C_Minisat(ex, p);   // Create the other files min

            }

          }

        }    //  Fim While Interno

        ex.type_restrictions = 3;

        p = p * 10;
        keep_precision = true;

        compensar_fobj =  0.00001;        // Reset compensator

        new_fiS = ex.fobj_current + " -" + convert.convertDoubleString(compensar_fobj);            // Generates the new F_I Compensated
        ex.fobj_current = new_fiS;

        ex._x1 = convert.convertStringDouble(tratar_contra_exemplo._x1);
        ex._x2 = convert.convertStringDouble(tratar_contra_exemplo._x2);

        ex.restrictions = generate_assumes(ex, p);

        gerar_arquivos.create_mi_CBMC_C_Minisat(ex, p);   // Create the other files min
      }

      cout << "####################################" << endl ;
      cout << " Global Minimum f(" + tratar_contra_exemplo._x1 + "," + tratar_contra_exemplo._x2 + ") = " + tratar_contra_exemplo._fjob<< endl;

  }




  //////////////////////////////////////////////////////////////////
  ///  Functions regarding input file handling ////////////////////
  ////////////////////////////////////////////////////////////////

  /*******************************************************************************************************\
  Method: checks_input_file(Set ex)
  Inputs: ex: Optimization configuration
  Outputs: Void  
  Purpose: Treat and Check Input File
  \*******************************************************************************************************/

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

    // Opens the original function files OK
    if(!file_min.is_open( )){
      cout<<"Could not open file with function!\n";
      file_min.clear( ); //reseta o objeto leitura, para limpar memória do sistema}
    }

    // Loads the file into string OK
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
  //  Function that loads the original file with the function and Restrictions
  //  It generates the function in real and adapted format.
  //  Treat and Check Input File



  //****************************************************************************************************************************
  // Organize Matrices format 2

  bool Run_algorithm::segment_matrix_format_2(Set ex, string Mat){

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


  //****************************************************************************************************************************
  // Organize Matrices in format 1

  bool Run_algorithm::segment_matrix_format_1(Set ex, string Mat){

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


    string generate_assumes = "";
    int i,j;

    if(ex.type_restrictions == 0){

      if(ex.input_format==0){

        generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  ";
        generate_assumes = generate_assumes + "     \n        // Restrictions\n";

        generate_assumes = generate_assumes + "     \n        int lim[4] = {";

        for(i=0;i<l_A;i++){
          for(j=0;j<c_A;j++){
            generate_assumes = generate_assumes + convert.convertIntString(matrixA[i][j]);
            generate_assumes = generate_assumes + "*p, ";
          }
        }

        generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
        generate_assumes = generate_assumes + "};";

        generate_assumes = generate_assumes + "\n";
        generate_assumes = generate_assumes + "\n        for (i = 0; i < nv; i++) {";
        generate_assumes = generate_assumes + "\n            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );";
        generate_assumes = generate_assumes + "\n            __ESBMC_assume( X[i] == (float) x[i]/p  ); ";
        generate_assumes = generate_assumes + "\n        }\n";


        generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  \n\n";

        return generate_assumes;

      }else{

        generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  ";
        generate_assumes = generate_assumes + "     \n        // Restrictions\n";

        generate_assumes = generate_assumes + "     \n        int A[nr][nv] = {";

        for(i=0;i<l_A;i++){
          for(j=0;j<c_A;j++){
            generate_assumes = generate_assumes + convert.convertIntString(matrixA[i][j]);
            generate_assumes = generate_assumes + "*p, ";
          }
        }

        generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
        generate_assumes = generate_assumes + "};";

        generate_assumes = generate_assumes + "\n                 int B[nr] = {";

        for(i=0;i<l_A;i++){
          generate_assumes = generate_assumes + convert.convertIntString(matrixB[i]);
          generate_assumes = generate_assumes + "*p, ";
        }

        generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
        generate_assumes = generate_assumes + "};";

        generate_assumes = generate_assumes + "     \n        float s = 0;\n";
        generate_assumes = generate_assumes + "     \n        for (i = 0; i < nr; i++) {\n            for (j = 0; j < nv; j++){\n                 s = s + A[i][j]*x[j]/p;\n            }\n";
        generate_assumes = generate_assumes + "            __ESBMC_assume( s < (float) B[i] );\n           s = 0;\n        }\n";
        generate_assumes = generate_assumes + "    \n        for (i = 0; i < nv; i++) {\n            __ESBMC_assume( X[i] == (float) x[i]/p  );\n        }\n";

        generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  \n\n";

        return generate_assumes;

      }

    }else if(ex.type_restrictions == 1){

      if(ex.input_format == 0){

        generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  ";
        generate_assumes = generate_assumes + "     \n        // Restrictions\n";

        string new_spaceS = "\n  int lim[4] = { " + convert.convertDoubleString((ex._x1*p-1)*10) + ", " + convert.convertDoubleString((ex._x1*p+1)*10) + ", " + convert.convertDoubleString((ex._x2*p-1)*10) + ", " + convert.convertDoubleString((ex._x2*p+1)*10) + " };";


        generate_assumes = generate_assumes + new_spaceS;

        generate_assumes = generate_assumes + "\n";
        generate_assumes = generate_assumes + "\n        for (i = 0; i < nv; i++) {";
        generate_assumes = generate_assumes + "\n            __ESBMC_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );";
        generate_assumes = generate_assumes + "\n            __ESBMC_assume( X[i] == (float) x[i]/p  ); ";
        generate_assumes = generate_assumes + "\n        }\n";


        generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  \n\n";

        return generate_assumes;

      }else{

        generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  ";
        generate_assumes = generate_assumes + "     \n        // Restrictions\n";

        generate_assumes = generate_assumes + "     \n        int A[nr][nv] = {";

        for(i=0;i<l_A;i++){
          for(j=0;j<c_A;j++){
            generate_assumes = generate_assumes + convert.convertIntString(matrixA[i][j]);
            generate_assumes = generate_assumes + "*p, ";
          }
        }

        generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
        generate_assumes = generate_assumes + "};";

        generate_assumes = generate_assumes + "\n        int B[nr] = {";

        for(i=0;i<l_A;i++){
          generate_assumes = generate_assumes + convert.convertIntString(matrixB[i]);
          generate_assumes = generate_assumes + "*p, ";
        }

        generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
        generate_assumes = generate_assumes + "};";

        generate_assumes = generate_assumes + "     \n        float s = 0;\n";
        generate_assumes = generate_assumes + "     \n        for (i = 0; i < nr; i++) {\n            for (j = 0; j < nv; j++){\n                 s = s + A[i][j]*x[j]/p;\n            }\n";
        generate_assumes = generate_assumes + "            __ESBMC_assume( s < (float) B[i] );\n           s = 0;\n        }\n";
        generate_assumes = generate_assumes + "    \n        for (i = 0; i < nv; i++) {\n            __ESBMC_assume( X[i] == (float) x[i]/p  );\n        }\n";

        generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  \n\n";

        return generate_assumes;

      }

    }else if(ex.type_restrictions == 2){

        if(ex.input_format==0){

          generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  ";
          generate_assumes = generate_assumes + "     \n        // Restrictions\n";

          generate_assumes = generate_assumes + "     \n        int lim[4] = {";

          for(i=0;i<l_A;i++){
            for(j=0;j<c_A;j++){
              generate_assumes = generate_assumes + convert.convertIntString(matrixA[i][j]);
              generate_assumes = generate_assumes + "*p, ";
            }
          }

          generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
          generate_assumes = generate_assumes + "};";

          generate_assumes = generate_assumes + "\n";
          generate_assumes = generate_assumes + "\n        for (i = 0; i < nv; i++) {";
          generate_assumes = generate_assumes + "\n            __CPROVER_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );";
          generate_assumes = generate_assumes + "\n            __CPROVER_assume( X[i] == (float) x[i]/p  ); ";
          generate_assumes = generate_assumes + "\n        }\n";



          generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  \n\n";

          return generate_assumes;

      }else{

        generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  ";
        generate_assumes = generate_assumes + "     \n        // Restrictions\n";

        generate_assumes = generate_assumes + "     \n        int A[nr][nv] = {";

        for(i=0;i<l_A;i++){
          for(j=0;j<c_A;j++){
            generate_assumes = generate_assumes + convert.convertIntString(matrixA[i][j]);
            generate_assumes = generate_assumes + "*p, ";
          }
        }

        generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
        generate_assumes = generate_assumes + "};";

        generate_assumes = generate_assumes + "\n        int B[nr] = {";

        for(i=0;i<l_A;i++){
          generate_assumes = generate_assumes + convert.convertIntString(matrixB[i]);
          generate_assumes = generate_assumes + "*p, ";
        }

        generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
        generate_assumes = generate_assumes + "};";

        generate_assumes = generate_assumes + "     \n        float s = 0;\n";
        generate_assumes = generate_assumes + "     \n        for (i = 0; i < nr; i++) {\n            for (j = 0; j < nv; j++){\n                 s = s + A[i][j]*x[j]/p;\n            }\n";
        generate_assumes = generate_assumes + "            __ESBMC_assume( s < (float) B[i] );\n           s = 0;\n        }\n";
        generate_assumes = generate_assumes + "    \n        for (i = 0; i < nv; i++) {\n            __ESBMC_assume( X[i] == (float) x[i]/p  );\n        }\n";

        generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  \n\n";

        return generate_assumes;

      }

  }else if(ex.type_restrictions == 3){


        if(ex.input_format==0){

          generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  ";
          generate_assumes = generate_assumes + "     \n        // Restrictions\n";

          string new_spaceS = "\n  int lim[4] = { " + convert.convertDoubleString((ex._x1*p-1)*10) + ", " + convert.convertDoubleString((ex._x1*p+1)*10) + ", " + convert.convertDoubleString((ex._x2*p-1)*10) + ", " + convert.convertDoubleString((ex._x2*p+1)*10) + " };";


          generate_assumes = generate_assumes + new_spaceS;

          generate_assumes = generate_assumes + "\n";
          generate_assumes = generate_assumes + "\n        for (i = 0; i < nv; i++) {";
          generate_assumes = generate_assumes + "\n            __CPROVER_assume( (x[i]>=lim[2*i]) && (x[i]<=lim[2*i+1]) );";
          generate_assumes = generate_assumes + "\n            __CPROVER_assume( X[i] == (float) x[i]/p  ); ";
          generate_assumes = generate_assumes + "\n        }\n";


          generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  \n\n";

          return generate_assumes;


      }else{

        generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  ";
        generate_assumes = generate_assumes + "     \n        // Restrictions\n";

        generate_assumes = generate_assumes + "     \n        int A[nr][nv] = {";

        for(i=0;i<l_A;i++){
          for(j=0;j<c_A;j++){
            generate_assumes = generate_assumes + convert.convertIntString(matrixA[i][j]);
            generate_assumes = generate_assumes + "*p, ";
          }
        }

        generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
        generate_assumes = generate_assumes + "};";

        generate_assumes = generate_assumes + "\n        int B[nr] = {";

        for(i=0;i<l_A;i++){
          generate_assumes = generate_assumes + convert.convertIntString(matrixB[i]);
          generate_assumes = generate_assumes + "*p, ";
        }

        generate_assumes = generate_assumes.substr(0,generate_assumes.size()-2);
        generate_assumes = generate_assumes + "};";

        generate_assumes = generate_assumes + "     \n        float s = 0;\n";
        generate_assumes = generate_assumes + "     \n        for (i = 0; i < nr; i++) {\n            for (j = 0; j < nv; j++){\n                 s = s + A[i][j]*x[j]/p;\n            }\n";
        generate_assumes = generate_assumes + "            __ESBMC_assume( s < (float) B[i] );\n           s = 0;\n        }\n";
        generate_assumes = generate_assumes + "    \n        for (i = 0; i < nv; i++) {\n            __ESBMC_assume( X[i] == (float) x[i]/p  );\n        }\n";

        generate_assumes = generate_assumes + "     \n        //-----------------------------------------------------------  \n\n";

        return generate_assumes;

      }
    }

    return generate_assumes;

  }
