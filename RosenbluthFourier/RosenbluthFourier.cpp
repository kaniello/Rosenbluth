// RosenbluthFourier.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"



int main() {

	int size;
	double sup;

	std::cout << "enter N of points "; std::cin >> size;
	std::cout << "enter sup "; std::cin >> sup;
	std::cout << "Interval runs from 0 to " << sup << " and will be divided in " << size
		<< " intervals " << endl << "whose abscissas are:" << endl << endl;

	double delta;
	delta = sup / size;
	cout << "delta = " << delta << endl << endl;

	double *X = new double[size + 1];

	for (int i = 0; i <= size; i++) {
		X[i] = delta*i;
		cout << "X[" << i << "] = " << X[i] << endl;
	}

	delete[] X;

	return 0;
}

