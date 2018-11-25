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

void Setup::printSetupExperiment()
{
  cout << "####### SETUP ######"<< endl;
//  cout << "Name Function " + getNameFunction() << endl;

}

int Setup::getAlg() const {
	return alg;
}

void Setup::setAlg(int alg) {
	this->alg = alg;
}

int Setup::getBmc() const {
	return bmc;
}

void Setup::setBmc(int bmc) {
	this->bmc = bmc;
}

const string& Setup::getCodeFunction() const {
	return code_function;
}

void Setup::setCodeFunction(const string& codeFunction) {
	code_function = codeFunction;
}

const string& Setup::getCodeFunctionModified() const {
	return code_function_modified;
}

void Setup::setCodeFunctionModified(const string& codeFunctionModified) {
	code_function_modified = codeFunctionModified;
}

int Setup::getFailure() const {
	return failure;
}

void Setup::setFailure(int failure) {
	this->failure = failure;
}

const string& Setup::getFcCurrent() const {
	return fc_current;
}

void Setup::setFcCurrent(const string& fcCurrent) {
	fc_current = fcCurrent;
}

const string& Setup::getFobjResult() const {
	return fobj_result;
}

void Setup::setFobjResult(const string& fobjResult) {
	fobj_result = fobjResult;
}

bool Setup::isInputFile() const {
	return input_file;
}

void Setup::setInputFile(bool inputFile) {
	input_file = inputFile;
}

int Setup::getInputFormat() const {
	return input_format;
}

void Setup::setInputFormat(int inputFormat) {
	input_format = inputFormat;
}

bool Setup::isInputSetup() const {
	return input_setup;
}

void Setup::setInputSetup(bool inputSetup) {
	input_setup = inputSetup;
}

float Setup::getInfX1() const {
	return l_inf_x1;
}

void Setup::setInfX1(float infX1) {
	l_inf_x1 = infX1;
}

float Setup::getInfX2() const {
	return l_inf_x2;
}

void Setup::setInfX2(float infX2) {
	l_inf_x2 = infX2;
}

float Setup::getSupX1() const {
	return l_sup_x1;
}

void Setup::setSupX1(float supX1) {
	l_sup_x1 = supX1;
}

float Setup::getSupX2() const {
	return l_sup_x2;
}

void Setup::setSupX2(float supX2) {
	l_sup_x2 = supX2;
}

const string& Setup::getLibrary() const {
	return library;
}

void Setup::setLibrary(const string& library) {
	this->library = library;
}

int Setup::getN() const {
	return n;
}

void Setup::setN(int n) {
	this->n = n;
}

const string& Setup::getNameFunction() const {
	return name_function;
}

void Setup::setNameFunction(const string& nameFunction) {
	name_function = nameFunction;
}

int Setup::getNr() const {
	return nr;
}

void Setup::setNr(int nr) {
	this->nr = nr;
}

int Setup::getPrecision() const {
	return precision;
}

void Setup::setPrecision(int precision) {
	this->precision = precision;
}

const string& Setup::getRestrictions() const {
	return restrictions;
}

void Setup::setRestrictions(const string& restrictions) {
	this->restrictions = restrictions;
}

int Setup::getSolver() const {
	return solver;
}

void Setup::setSolver(int solver) {
	this->solver = solver;
}

const string& Setup::getSpaceLimit() const {
	return space_limit;
}

void Setup::setSpaceLimit(const string& spaceLimit) {
	space_limit = spaceLimit;
}

float Setup::getTimeoutGlobal() const {
	return timeout_global;
}

void Setup::setTimeoutGlobal(float timeoutGlobal) {
	timeout_global = timeoutGlobal;
}

float Setup::getTimeoutVerification() const {
	return timeout_verification;
}

void Setup::setTimeoutVerification(float timeoutVerification) {
	timeout_verification = timeoutVerification;
}

int Setup::getTypeRestrictions() const {
	return type_restrictions;
}

void Setup::setTypeRestrictions(int typeRestrictions) {
	type_restrictions = typeRestrictions;
}

const string& Setup::getTypeData() const {
	return typeData;
}

void Setup::setTypeData(const string& typeData) {
	this->typeData = typeData;
}

const string& Setup::getX1Current() const {
	return x1_current;
}

void Setup::setX1Current(const string& x1Current) {
	x1_current = x1Current;
}

const string& Setup::getX1Result() const {
	return x1_result;
}

void Setup::setX1Result(const string& x1Result) {
	x1_result = x1Result;
}

const string& Setup::getX2Current() const {
	return x2_current;
}

void Setup::setX2Current(const string& x2Current) {
	x2_current = x2Current;
}

const string& Setup::getX2Result() const {
	return x2_result;
}

const string& Setup::getMsgError() const {
	return msg_error;
}

void Setup::setMsgError(const string& msgError) {
	msg_error = msgError;
}

void Setup::setX2Result(const string& x2Result) {
	x2_result = x2Result;
}


} /* namespace SETUP */

bool SETUP::Setup::isHv() const {
	return hv;
}

void SETUP::Setup::setHv(bool hv) {
	this->hv = hv;
}

const string& SETUP::Setup::getFc() const {
	return fc;
}

void SETUP::Setup::setFc(const string& fc) {
	this->fc = fc;
}

