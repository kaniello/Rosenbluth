// RosenbluthFourier.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <fftw3.h>
#include <fstream>



int main() {

	double const Pi = 3.14159265359;
	double const a = 2;
	int N;
	double sup =5;

	cout << "enter N of points "; cin >> N;
	//cout << "enter sup "; cin >> sup;
	cout << "Interval runs from 0 to " << sup << " and will be divided into " << N-1
	   	<< " intervals." << endl;
	
	double T, Df;
	T = sup / (N-1);
	Df = 1 / sup;
	cout << "Sampling interval T = " << T << endl;
	cout << "Frequency spacing df = " << Df << endl << endl; 

	double *X = new double[N];
	double *Y = new double[N];

	for (int i = 0; i < N; i++) {
		X[i] = T*i;
		Y[i] = X[i] * exp(-pow(X[i],2));
		//Y[i] = exp(-a*X[i]);
		//cout << "X[" << i << "] = " << X[i] << "  Y[" << i << "] = " << Y[i] << endl;
	}

	ofstream results("FFTW.dat");
	ofstream theory("Analytical.dat");

	if (theory.is_open())
	{
	cout << endl << "Analitically tranformed function" << endl << endl ;

	double *f = new double[N];
	double *Yt = new double[N];

	for (int k = 0; k < N; k++) {
		// calc pi*w
		f[k] = Pi*k*Df;
		//Yt[k] = 2.*f[k] * double(sqrt(Pi)) / (pow(f[k],2)+pow(a,2));
		Yt[k] = (1. / 2.)*Pi*f[k] * exp(-pow(f[k] / 2., 2));
		//cout << "f[" << k << "] = " << f[k] << "  Yt[" << k << "] = " << Yt[k] << endl;
		theory << f[k] << " " << Yt[k] << endl;
	}

	cout << endl << "FFTW-tranformed function" << endl << endl;

	fftw_plan p;
	p = fftw_plan_r2r_1d(N, Y, Yt, FFTW_RODFT00, FFTW_ESTIMATE);
	fftw_execute(p);

	//cout << "f[0] = 0  Yt[0] = " << Yt[N] * T * double(sqrt(Pi)) << endl;
	{int k;
		for (k = N; k > 1; k--) {
		Yt[k - 1] = Yt[k - 2] * T * double(sqrt(Pi));
		//cout << "f[" << k << "] = " << f[k] << "  Yt[" << k << "] = " << Yt[k-1] << endl;
		}

		results << 0 << " " << 0 << endl;
		for (k = 1; k < N - 1; k++) {
		results << f[k - 1] << " " << Yt[k - 1] << endl;
		}
	}

		
	fftw_destroy_plan(p);
	//fftw_free(Y);
	//fftw_free(Yt);


	}
	else cout << "Unable to open file";
	results.close();
	theory.close();

	return 0;
}

