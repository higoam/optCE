/*
 *   Ajusts.h
 *
 *  Created on: 15/04/2017
 *  Author: Higo Albuquerque
 */

#ifndef ADJUST_H_
#define ADJUST_H_

#include <string>
using namespace std;

class Ajusts
{
  public:
    Ajusts();
    virtual ~Ajusts();

    int convertStringInt(string str);
    double convertStringDouble(string str);
    string convertDoubleString(double value);
    string convertIntString(int value);
};

#endif /* ADJUST_H_ */
