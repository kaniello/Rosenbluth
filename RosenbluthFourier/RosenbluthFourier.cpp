// RosenbluthFourier.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <fftw3.h>



int main() {

	int const Pi = 3.14159265359;
	int N;
	double sup;

	cout << "enter N of points "; std::cin >> N;
	cout << "enter sup "; std::cin >> sup;
	cout << "Interval runs from 0 to " << sup << " and will be divided into " << N
	   	<< " intervals." << endl;
	
	double T, Df;
	T = sup / (N-1);
	Df = 1 / sup;
	cout << "Sampling interval T = " << T << endl;
	cout << "Frequency spacing df = " << Df << endl << endl; 

	double *X = new double[N];
	double *Y = new double[N];

	for (int i = 0; i <= N; i++) {
		X[i] = T*i;
		Y[i] = X[i] * exp(-pow(X[i],2));
		cout << "X[" << i << "] = " << X[i] << "  Y[" << i << "] = " << Y[i] << endl;
	}

	cout << endl << "Analitically tranformed function" << endl << endl ;

	double *f = new double[N];
	double *Yt = new double[N];

	for (int k = 0; k <= N; k++) {
		// calc pi*w
		f[k] = Pi*k*Df;
		Yt[k] = (1./2.)*Pi*f[k] * exp(-pow(f[k]/2., 2));
		cout << "f[" << k << "] = " << f[k] << "  Yt[" << k << "] = " << Yt[k] << endl;
	}

	cout << endl << "FFTW-tranformed function" << endl << endl;

	fftw_plan p;
	p = fftw_plan_r2r_1d(N, Y, Yt, FFTW_RODFT00, FFTW_ESTIMATE);
	fftw_execute(p);

	for (int k = 0; k <= N; k++) {
		Yt[k] = Yt[k] * T * double(sqrt(Pi)) ;
		cout << "f[" << k << "] = " << f[k] << "  Yt[" << k << "] = " << Yt[k] << endl;
	}
	
	fftw_destroy_plan(p);
	//fftw_free(Y);
	//fftw_free(Yt);
	return 0;
}

