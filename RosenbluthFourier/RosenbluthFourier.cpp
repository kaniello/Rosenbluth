// RosenbluthFourier.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <fftw3.h>
#include <fstream>


tk::spline s;
int N,k;
double *f;
double *X;

int main() {

	double const Pi = acos(-1);
	double inf = numeric_limits<double>::infinity();
	double sup =10.;

	cout << "enter N of points "; cin >> N;
	cout << "Space interval runs from 0 to " << sup << " and will be divided into " << N-1 << " intervals." << endl;
	
	double T, Df;
	T = sup / (N-1);
	Df = 1 / sup;
	cout << "Sampling interval T = " << T << endl;
	cout << "Frequency spacing df = " << Df << endl; 
	cout << "Frequency interval runs from 0 to " << (Pi*(N-1)*Df) << endl << endl;

	X = new double[N];
	double *Y = new double[N];



	ofstream results("FFTW.dat");
	ofstream Test("SuperTest.dat");
	ofstream theory("Analytical.dat");

	if (theory.is_open())
	{
	cout << endl << "Evaluating the analitically tranformed function .. " << endl << endl ;

	double *Yt = new double[N];
	f = new double[N];


	// Calculate the Sin-transformed of r*f(r) for comparison with numerical result
	for (k = 0; k < N; k++) { // k=0...N-1
		f[k] = Pi*k*Df;  // omega_k = pi*vi*k
		Yt[k] = (1. / 2.)*Pi*f[k] * exp(-pow(f[k] / 2., 2));
		theory << f[k] << " " << Yt[k] << endl;
		Yt[k] = 0.;
	}


/* -------------------            FOURIER TRANSFORM     --------------------                 */

	cout << endl << "Evaluating the FFTw-tranformed function.." << endl << endl;

	// PREPROCESSING : Prepare the input function for the Sin-transform : r * f(r)
	for (k = 0; k < N; k++) {
		X[k] = T*(k);
		Y[k] = X[k] * exp(-1.*pow(X[k], 2));
	}

	// EXECUTION : Evaluate the FFTw -tranformed function
	fftw_plan p;
	p = fftw_plan_r2r_1d(N, Y, Yt, FFTW_RODFT00, FFTW_ESTIMATE);
	fftw_execute(p);

	// POSTPROCESSING : Reorder the array(, clean from negative values) and normalize ...
	for (k = N-1; k >= 1; k--) {
		if (Yt[k] < 0.) { Yt[k] = 0.0; } // must be removed; Yt must be more accurate;
		else { Yt[k] = Yt[k - 1] * T * double(sqrt(Pi)); }		 
	}
	// ...because the first position is always zero and will not be written in the output array
	Yt[0] = 0.0;
	for (k = 0; k <= N - 1; k++) {
		results << f[k] << " " << Yt[k]  << endl;
	}
			
	fftw_destroy_plan(p);

}