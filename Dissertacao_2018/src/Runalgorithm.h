/*
 *  Runalgorithm.h
 *
 *  Created on: 03/02/2017
 *  Author: Higo Albuquerque
 */

#include "Set.h"
#include "Tcexamples.h"
#include "Generatefiles.h"
#include "Adjust.h"

#ifndef RUNALGORITHM_H_
#define RUNALGORITHM_H_

  class Run_algorithm
  {
    public:
      string code_function_original;
      string code_function_treated;
      string restrictions;
      string space_limit;
      int matrixA[10][10];
      int matrixB[10];
      int l_A;
      int c_A;
      int l_B;
      int c_B;

      Ajusts convert;

      Run_algorithm();
      virtual ~Run_algorithm();

      bool checks_input_file(Set ex);
      void execute_experiment(Set ex);

      void run_ESBMC_BOOLECTOR_G(Set ex);
      void run_ESBMC_Z3_G(Set ex);
      void run_ESBMC_MATHSAT_G(Set ex);

      void run_ESBMC_BOOLECTOR_S(Set ex);
      void run_ESBMC_Z3_S(Set ex);
      void run_ESBMC_MATHSAT_S(Set ex);

      void run_ESBMC_BOOLECTOR_C(Set ex);
      void run_ESBMC_Z3_C(Set ex);
      void run_ESBMC_MATHSAT_C(Set ex);

      void run_CBMC_MINISAT_G(Set ex);

      void run_CBMC_MINISAT_S(Set ex);

      void run_CBMC_MINISAT_C(Set ex);

      bool treat_input_file(Set ex);
      bool segment_matrix_format_2(Set ex, string Mat);
      bool segment_matrix_format_1(Set ex, string Mat);
      string remove_space(string str);
      string generate_assumes(Set ex, int p);
  };

#endif /* RUNALGORITHM_H_ */
