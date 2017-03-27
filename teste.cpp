#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

using namespace std;


bool valid(string st)
{
    bool valid = false;
    string numero = "0123456789.";

    if ((st[0] == '+' || st[0] == '-') && st.size() > 1)
        st = st.substr(1);

    if (count(st.begin(), st.end(), '.') <= 1 && st.find_first_not_of(numero) > st.size())
        valid = true;

    if (st[0] == '.' && st.size() == 1)
        valid = false;

    return valid;
}

int main(){

	double valor;
	string valorS = "234.234";


	if(valid(valorS)){
		cout << "blz" << endl;
	}else{
		cout << "erro" << endl;
	}

	return 0;
}
