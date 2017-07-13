// RosenbluthFourier.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <fftw3.h>
#include <fstream>



int main() {

	double const Pi = 3.14159265359;
	double const a = 2;
	int N,k;
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

	for (k = 0; k < N; k++) {
		X[k] = T*k;
		Y[k] = X[k] * exp(-pow(X[k],2));
		//Y[i] = exp(-a*X[i]);
		//cout << "X[" << i << "] = " << X[i] << "  Y[" << i << "] = " << Y[i] << endl;
	}

	ofstream results("FFTW.dat");
	ofstream Test("SuperTest.dat");
	ofstream theory("Analytical.dat");

	if (theory.is_open())
	{
	cout << endl << "Analitically tranformed function" << endl << endl ;

	double *f = new double[N];
	double *Yt = new double[N];

	for (k = 0; k < N; k++) {
		// calc pi*w
		f[k] = Pi*k*Df;
		//Yt[k] = (1. / 2.)*Pi*f[k] * exp(-pow(f[k] / 2., 2));
		Yt[k] = (1. / 2.)*Pi/(f[k]) * exp(-pow(f[k] / 2., 2));
		//cout << "f[" << k << "] = " << f[k] << "  Yt[" << k << "] = " << Yt[k] << endl;
		theory << f[k] << " " << Yt[k] << endl;
	}

	cout << endl << "FFTW-tranformed function" << endl << endl;

	fftw_plan p;
	p = fftw_plan_r2r_1d(N, Y, Yt, FFTW_RODFT00, FFTW_ESTIMATE);
	fftw_execute(p);

	//cout << "f[0] = 0  Yt[0] = " << Yt[N] * T * double(sqrt(Pi)) << endl;

	for (k = N-1; k >= 1; k--) {
		//cout << k << "   " <<  Yt[k] << "  " << Yt[k - 1] << endl;
		Yt[k] = Yt[k - 1] * T * double(sqrt(Pi)) / (f[k]* f[k]);
		//cout << "f[" << k << "] = " << f[k] << "  Yt[" << k << "] = " << Yt[k-1] << endl;
	}
	
	

	results << 0 << " " << 0 << endl;
	for (k = 1; k <= N - 1; k++) {
		results << f[k] << " " << Yt[k]  << endl;
	}

	//*Yt = *Yt / pow(*f,2);
	//Yt[0] =  Yt[2] + (f[0] - f[2])*(Yt[1] - Yt[2]) / (f[1] - f[2]);
	//for (k = 1; k < N - 1; k++) {
		//Test << k*T << " " << Yt[k - 1] << endl;
		//cout << "f[" << k << "] = " << f[k] << "  Yt[" << k << "] = " << Yt[k - 1] << endl;
	//}
	
	p = fftw_plan_r2r_1d(N, Yt, Y, FFTW_RODFT00, FFTW_ESTIMATE);
	fftw_execute(p);

	for (k = 1; k < N - 1; k++) {
		Test << k*T << " " << Y[k - 1] << endl;
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

