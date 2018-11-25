/*
 * Setup.h
 *
 *  Created on: 19/11/2018
 *      Author: higo
 */

#include <iostream>
using namespace std;

#ifndef SETUP_H_
#define SETUP_H_

namespace SETUP {

class Setup {
public:
	virtual ~Setup();
	Setup();

	bool 	hv;
	bool 	input_setup;
	bool 	input_file;

	int 	failure;
    string 	name_function;
    int 	bmc;
    int 	solver;
    int 	alg;


    string fc;

    float l_sup_x1;
    float l_inf_x1;
    float l_sup_x2;
    float l_inf_x2;


    string fc_current;
    string x1_current;
    string x2_current;
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

    string fobj_result;
    string x1_result;
    string x2_result;

    string msg_error;

	void printSetupExperiment();



	// ---------------------------------------------------------------------------------------------
	int getAlg() const;
	void setAlg(int alg);
	int getBmc() const;
	void setBmc(int bmc);
	const string& getCodeFunction() const;
	void setCodeFunction(const string& codeFunction);
	const string& getCodeFunctionModified() const;
	void setCodeFunctionModified(const string& codeFunctionModified);
	int getFailure() const;
	void setFailure(int failure);
	const string& getFcCurrent() const;
	void setFcCurrent(const string& fcCurrent);
	const string& getFobjResult() const;
	void setFobjResult(const string& fobjResult);
	bool isInputFile() const;
	void setInputFile(bool inputFile);
	int getInputFormat() const;
	void setInputFormat(int inputFormat);
	bool isInputSetup() const;
	void setInputSetup(bool inputSetup);
	float getInfX1() const;
	void setInfX1(float infX1);
	float getInfX2() const;
	void setInfX2(float infX2);
	float getSupX1() const;
	void setSupX1(float supX1);
	float getSupX2() const;
	void setSupX2(float supX2);
	const string& getLibrary() const;
	void setLibrary(const string& library);
	int getN() const;
	void setN(int n);
	const string& getNameFunction() const;
	void setNameFunction(const string& nameFunction);
	int getNr() const;
	void setNr(int nr);
	int getPrecision() const;
	void setPrecision(int precision);
	const string& getRestrictions() const;
	void setRestrictions(const string& restrictions);
	int getSolver() const;
	void setSolver(int solver);
	const string& getSpaceLimit() const;
	void setSpaceLimit(const string& spaceLimit);
	float getTimeoutGlobal() const;
	void setTimeoutGlobal(float timeoutGlobal);
	float getTimeoutVerification() const;
	void setTimeoutVerification(float timeoutVerification);
	int getTypeRestrictions() const;
	void setTypeRestrictions(int typeRestrictions);
	const string& getTypeData() const;
	void setTypeData(const string& typeData);
	const string& getX1Current() const;
	void setX1Current(const string& x1Current);
	const string& getX1Result() const;
	void setX1Result(const string& x1Result);
	const string& getX2Current() const;
	void setX2Current(const string& x2Current);
	const string& getX2Result() const;
	void setX2Result(const string& x2Result);
	const string& getMsgError() const;
	void setMsgError(const string& msgError);
	bool isHv() const;
	void setHv(bool hv);
	const string& getSup() const;
	void setSup(const string& sup);
	const string& getFc() const;
	void setFc(const string& fc);
};

} /* namespace SETUP */

#endif /* SETUP_H_ */
