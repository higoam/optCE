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

	this->failure = 0;
	this->hv = false;
	this->core = 0;
	this->library = "";
}

void Setup::printSetupExperiment()
{
  cout << "####### SETUP ######"<< endl;
  cout << "ALG :" << endl;
  cout << this->alg << endl;
  cout << "Name Function " + getNameFunction() << endl;
  cout << "Fc :" << endl;
  cout << "BMC " + this->getBmc() << endl;


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


const string& Setup::getFobjResult() const {
	return fobj_result;
}

void Setup::setFobjResult(const string& fobjResult) {
	fobj_result = fobjResult;
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
/*
int Setup::getN() const {
	return n;
}

void Setup::setN(int n) {
	this->n = n;
}
*/
const string& Setup::getNameFunction() const {
	return name_function;
}

void Setup::setNameFunction(string nameFunction) {
	this->name_function = nameFunction;
}
/*
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
*/

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

const string& Setup::getX1Result() const {
	return x1_result;
}

void Setup::setX1Result(const string& x1Result) {
	x1_result = x1Result;
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
/*
const string& SETUP::Setup::getFc() const {
	return fc;
}

void SETUP::Setup::setFc(const string& fc) {
	this->fc = fc;
}
*/
int SETUP::Setup::getPrecisionCurrent() const {
	return precision_current;
}

void SETUP::Setup::setPrecisionCurrent(int precisionCurrent) {
	precision_current = precisionCurrent;
}

int SETUP::Setup::getPrecisionTest() const {
	return precision_test;
}

void SETUP::Setup::setPrecisionTest(int precisionTest) {
	precision_test = precisionTest;
}

int SETUP::Setup::getColumnInput() const {
	return N_column_input;
}

void SETUP::Setup::setColumnInput(int columnInput) {
	N_column_input = columnInput;
}

int SETUP::Setup::getLineInput() const {
	return N_line_input;
}

void SETUP::Setup::setLineInput(int lineInput) {
	N_line_input = lineInput;
}

const string& SETUP::Setup::getInputFunction() const {
	return input_function;
}

void SETUP::Setup::setInputFunction(const string& inputFunction) {
	input_function = inputFunction;
}

const string& SETUP::Setup::getInputRestrictions() const {
	return input_restrictions;
}

const string& SETUP::Setup::getFcStart() const {
	return fc_start;
}

double SETUP::Setup::getFcCurrent() const {
	return fc_current;
}

double SETUP::Setup::getX1Current() const {
	return x1_current;
}

void SETUP::Setup::setX1Current(double x1Current) {
	x1_current = x1Current;
}

double SETUP::Setup::getX2Current() const {
	return x2_current;
}

void SETUP::Setup::setX2Current(double x2Current) {
	x2_current = x2Current;
}

void SETUP::Setup::setFcCurrent(double fcCurrent) {
	fc_current = fcCurrent;
}

void SETUP::Setup::setFcStart(const string& fcStart) {
	fc_start = fcStart;
}

void SETUP::Setup::setInputRestrictions(const string& inputRestrictions) {
	input_restrictions = inputRestrictions;
}

double SETUP::Setup::getFcFc() const {
	return fc_fc;
}

void SETUP::Setup::setFcFc(double fcFc) {
	fc_fc = fcFc;
}

const string& SETUP::Setup::getFi() const {
	return fi;
}

void SETUP::Setup::setFi(const string& fi) {
	this->fi = fi;
}

int SETUP::Setup::getStatusCe() const {
	return status_CE;
}

const string& SETUP::Setup::getFcCurrentString() const {
	return fc_current_string;
}

int SETUP::Setup::getCore() const {
	return core;
}

const int* SETUP::Setup::getCoreOpt() const {
	return coreOpt;
}

void SETUP::Setup::setCore(int core) {
	this->core = core;
}

void SETUP::Setup::setFcCurrentString(const string& fcCurrentString) {
	fc_current_string = fcCurrentString;
}

void SETUP::Setup::setStatusCe(int statusCe) {
	status_CE = statusCe;
}
