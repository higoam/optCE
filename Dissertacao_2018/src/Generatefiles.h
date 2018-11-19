/*
 *  Generatefiles.h
 *
 *  Created on: 03/02/2017
 *  Author: Higo Albuquerque
 */

#include "Set.h"
#include "Adjust.h"

#ifndef GENERATEFILES_H_
#define GENERATEFILES_H_

class Generate_files
{
  public:
    Ajusts convertValue;

    Generate_files();
    virtual ~Generate_files();


    // General Functions

    void take_function(string name);
    void create_f(string name_f, string code_f, string type);


    // Generation of files related to the ESBMC

    void create_mi_ESBMC_G_Boolector(Set ex, int prec);
    void create_mi_ESBMC_G_Z3(Set ex, int prec);
    void create_mi_ESBMC_G_Mathsat(Set ex, int prec);

    void create_mi_ESBMC_S_Boolector(Set ex, int prec);
    void create_mi_ESBMC_S_Z3(Set ex, int prec);
    void create_mi_ESBMC_S_Mathsat(Set ex, int prec);

    void create_mi_ESBMC_C_Boolector(Set ex, int prec);
    void create_mi_ESBMC_C_Z3(Set ex, int prec);
    void create_mi_ESBMC_C_Mathsat(Set ex, int prec);


    // Generation of files related to the CBMC

    void create_mi_CBMC_G_Minisat(Set ex, int prec);
    void create_mi_CBMC_S_Minisat(Set ex, int prec);
    void create_mi_CBMC_C_Minisat(Set ex, int prec);
};

#endif /* GENERATEFILES_H_ */
