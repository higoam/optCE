/*
 * Setup.cpp
 *
 *  Created on: 19/11/2018
 *      Author: higo
 */

#include "Setup.h"

namespace SETUP {

Setup::~Setup() {
	// TODO Auto-generated destructor stub
}

Setup::Setup() {
	// TODO Auto-generated constructor stub

}

int Setup::getAlg() const {
	return alg;
}

void Setup::setAlg(int alg) {
	this->alg = alg;
}


const string& Setup::getNameFunction() const {
	return name_function;
}

void Setup::setNameFunction(const string& nameFunction) {
	name_function = nameFunction;
}

int Setup::getSolver() const {
	return solver;
}


void Setup::setSolver(int solver) {
	this->solver = solver;
}

void Setup::printSetupExperiment()
{
  cout << "####### SETUP ######"<< endl;
  cout << "Name Function " + getNameFunction() << endl;

}

} /* namespace SETUP */

bool SETUP::Setup::isAbleInput() const {
	return ableINPUT;
}

void SETUP::Setup::setAbleInput(bool ableInput) {
	ableINPUT = ableInput;
}

int SETUP::Setup::getBmc() const {
	return bmc;
}

void SETUP::Setup::setBmc(int bmc) {
	this->bmc = bmc;
}

const string& SETUP::Setup::getCodeFunction() const {
	return code_function;
}

void SETUP::Setup::setCodeFunction(const string& codeFunction) {
	code_function = codeFunction;
}

const string& SETUP::Setup::getCodeFunctionModified() const {
	return code_function_modified;
}

void SETUP::Setup::setCodeFunctionModified(const string& codeFunctionModified) {
	code_function_modified = codeFunctionModified;
}

int SETUP::Setup::getFailure() const {
	return failure;
}

void SETUP::Setup::setFailure(int failure) {
	this->failure = failure;
}

const string& SETUP::Setup::getFcCurrent() const {
	return fc_current;
}

void SETUP::Setup::setFcCurrent(const string& fcCurrent) {
	fc_current = fcCurrent;
}

const string& SETUP::Setup::getFobjResult() const {
	return fobj_result;
}

void SETUP::Setup::setFobjResult(const string& fobjResult) {
	fobj_result = fobjResult;
}

int SETUP::Setup::getInputFormat() const {
	return input_format;
}

void SETUP::Setup::setInputFormat(int inputFormat) {
	input_format = inputFormat;
}

float SETUP::Setup::getInfX1() const {
	return l_inf_x1;
}

void SETUP::Setup::setInfX1(float infX1) {
	l_inf_x1 = infX1;
}

float SETUP::Setup::getInfX2() const {
	return l_inf_x2;
}

void SETUP::Setup::setInfX2(float infX2) {
	l_inf_x2 = infX2;
}

float SETUP::Setup::getSupX1() const {
	return l_sup_x1;
}

void SETUP::Setup::setSupX1(float supX1) {
	l_sup_x1 = supX1;
}

float SETUP::Setup::getSupX2() const {
	return l_sup_x2;
}

void SETUP::Setup::setSupX2(float supX2) {
	l_sup_x2 = supX2;
}

const string& SETUP::Setup::getLibrary() const {
	return library;
}

void SETUP::Setup::setLibrary(const string& library) {
	this->library = library;
}

int SETUP::Setup::getN() const {
	return n;
}

void SETUP::Setup::setN(int n) {
	this->n = n;
}

int SETUP::Setup::getNr() const {
	return nr;
}

void SETUP::Setup::setNr(int nr) {
	this->nr = nr;
}

int SETUP::Setup::getPrecision() const {
	return precision;
}

void SETUP::Setup::setPrecision(int precision) {
	this->precision = precision;
}

const string& SETUP::Setup::getRestrictions() const {
	return restrictions;
}

void SETUP::Setup::setRestrictions(const string& restrictions) {
	this->restrictions = restrictions;
}

const string& SETUP::Setup::getSpaceLimit() const {
	return space_limit;
}

void SETUP::Setup::setSpaceLimit(const string& spaceLimit) {
	space_limit = spaceLimit;
}

float SETUP::Setup::getTimeoutGlobal() const {
	return timeout_global;
}

void SETUP::Setup::setTimeoutGlobal(float timeoutGlobal) {
	timeout_global = timeoutGlobal;
}

float SETUP::Setup::getTimeoutVerification() const {
	return timeout_verification;
}

void SETUP::Setup::setTimeoutVerification(float timeoutVerification) {
	timeout_verification = timeoutVerification;
}

int SETUP::Setup::getTypeRestrictions() const {
	return type_restrictions;
}

void SETUP::Setup::setTypeRestrictions(int typeRestrictions) {
	type_restrictions = typeRestrictions;
}

const string& SETUP::Setup::getTypeData() const {
	return typeData;
}

void SETUP::Setup::setTypeData(const string& typeData) {
	this->typeData = typeData;
}

const string& SETUP::Setup::getX1Current() const {
	return x1_current;
}

void SETUP::Setup::setX1Current(const string& x1Current) {
	x1_current = x1Current;
}

const string& SETUP::Setup::getX1Result() const {
	return x1_result;
}

void SETUP::Setup::setX1Result(const string& x1Result) {
	x1_result = x1Result;
}

const string& SETUP::Setup::getX2Current() const {
	return x2_current;
}

void SETUP::Setup::setX2Current(const string& x2Current) {
	x2_current = x2Current;
}

const string& SETUP::Setup::getX2Result() const {
	return x2_result;
}

void SETUP::Setup::setX2Result(const string& x2Result) {
	x2_result = x2Result;
}
