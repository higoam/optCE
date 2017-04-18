/*
 * Ajusts.h
 *
 *  Created on: 15/04/2017
 *      Author: higo
 */

#ifndef AJUSTS_H_
#define AJUSTS_H_

#include <string>
using namespace std;

class Ajusts {
public:
	Ajusts();
	virtual ~Ajusts();

	int convertStringInt(string str);
	double convertStringDouble(string str);
	string convertDoubleString(double value);
	string convertIntString(int value);

};

#endif /* AJUSTS_H_ */
