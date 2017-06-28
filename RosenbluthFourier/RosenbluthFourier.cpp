// RosenbluthFourier.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <fftw3.h>



int main() {

	int size;
	double sup;

	std::cout << "enter N of points "; std::cin >> size;
	std::cout << "enter sup "; std::cin >> sup;
	std::cout << "Interval runs from 0 to " << sup << " and will be divided into " << size
		<< " intervals " << endl << "whose abscissas are:" << endl << endl;

	double delta;
	delta = sup / size;
	cout << "delta = " << delta << endl << endl;

	double *X = new double[size + 1];
	double *Y = new double[size + 1];

	for (int i = 0; i <= size; i++) {
		X[i] = delta*i;
		Y[i] = X[i] * exp(-pow(X[i],2));
		cout << "X[" << i << "] = " << X[i] << "  Y[" << i << "] = " << Y[i] << endl << endl;
	}

	delete[] X,Y;

	fftw_complex *in, *out;
	fftw_plan p;

	int N = 32;

	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

	fftw_execute(p); /* repeat as needed */

	fftw_destroy_plan(p);
	fftw_free(in); fftw_free(out);

	return 0;
}

