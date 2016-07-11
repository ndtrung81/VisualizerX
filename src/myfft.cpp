#include "StdAfx.h"
#include "myFFT.h"
#include <math.h>

#define PI 3.1415926535897

FFT::FFT(int s) 
{
	size = s;
	depth = 0;
	int n = 1;
	while (n < size) 
	{
		n <<= 1; 
		depth++;
	}
	
	int d;
	sizes = new int[depth];
	multi = new int[depth];
	cosine   = new double* [depth];
	sine   = new double* [depth];
	even  = new double* [depth];
	odd   = new double* [depth];
	
	for (d = 0; d < depth; d++) 
	{
		cosine[d] = new double [size];
		sine[d] = new double [size];
		even[d] = new double [size];
		odd[d] = new double [size];
	}
	
	n = 1;
	for (d = 0; d < depth; d++) 
	{
		sizes[d] = 2 * n;
		multi[d] = size / n;
		for (int k = 0; k < n; k++) 
		{
			double kth = -PI * k / n;
			cosine[d][2*k] = cos(kth);
			sine[d][2*k] = sin(kth);
		}
		n <<= 1;
	}
	
	dataComplex1D = new double [2*size];
	dataComplex2D = new double* [size];
	for (int i = 0; i < size; i++) 
		dataComplex2D[i] = new double [2*size];

	// exp table for looking up
	EXPTABLESIZE = 1024;
	EXPTABLECUTOFF = 20.0;
	expTable = new double [EXPTABLESIZE];
	for (int i = 0; i < EXPTABLESIZE; i++) 
		expTable[i] = exp(-i * EXPTABLECUTOFF / EXPTABLESIZE);
	
}

FFT::~FFT()
{
	delete [] sizes;
	delete [] multi;
	
	for (int d = 0; d < depth; d++) 
	{
		delete [] cosine[d];
		delete [] sine[d];
		delete [] even[d];
		delete [] odd[d];
	}
	
	delete [] cosine;
	delete [] sine;
	delete [] even;
	delete [] odd;
	
	delete [] dataComplex1D;
	
	for (int s = 0; s < size; s++) 
		delete [] dataComplex2D[s];
	delete [] dataComplex2D;

	delete [] expTable;
}

void FFT::fft1D(double* data, int length) 
{
	loop(data, depth, 0);
	double norm = sqrt(1.0 / size);
	for (int i = 0; i < length; i++) 
		data[i] *= norm;
}

void FFT::fft2D(double** data, int row, int col) 
{
	int i;
	for (i = 0; i < row; i++) 
		fft1D(data[i], col);
	swap(data);
	
	for (i = 0; i < row; i++) 
		fft1D(data[i], col);
	swap(data);
}

void FFT::diffraction1D(double* data) 
{
	int i;
	for (i = 0; i < size; i++) 
	{
		dataComplex1D[2*i] = data[i];
		dataComplex1D[2*i+1] = 0.0;
	}
	
	fft1D(dataComplex1D, 2*size);
	
	for (i = 0; i < size; i++) 
	{
		double d1 = dataComplex1D[2*i];
		double d2 = dataComplex1D[2*i+1];
		data[i] = sqrt(d1 * d1 + d2 * d2);
	}
}

void FFT::diffraction2D(double** data) 
{
	int i, j;
	for (i = 0; i < size; i++) 
	{
		for (j = 0; j < size; j++) 
		{
			dataComplex2D[i][2*j] = data[i][j];
			dataComplex2D[i][2*j+1] = 0.0;
			
			if (i % 2 == 1) 
			{
				dataComplex2D[i][2*j] *= -1;
				dataComplex2D[i][2*j+1] *= -1;
			}
			
			if (j % 2 == 1) 
			{
				dataComplex2D[i][2*j] *= -1;
				dataComplex2D[i][2*j+1] *= -1;
			}
		}
	}
	
	fft2D(dataComplex2D, size, 2*size);
	
	for (i = 0; i < size; i++) 
	{
		for (j = 0; j < size; j++) 
		{
			double d1 = dataComplex2D[i][2*j];
			double d2 = dataComplex2D[i][2*j+1];
			data[i][j] = sqrt(d1 * d1 + d2 * d2);
		}
	}
}

void FFT::filter2D(double** data, double** filter) 
{
	int i, j;
	for (i = 0; i < size; i++) 
	{
		for (j = 0; j < size; j++) 
		{
			dataComplex2D[i][2*j] = data[i][j];
			dataComplex2D[i][2*j+1] = 0.0;
			
			if (i % 2 == 1) 
			{
				dataComplex2D[i][2*j] *= -1;
				dataComplex2D[i][2*j+1] *= -1;
			}
			
			if (j % 2 == 1) 
			{
				dataComplex2D[i][2*j] *= -1;
				dataComplex2D[i][2*j+1] *= -1;
			}
		}
	}
	fft2D(dataComplex2D, size, 2*size);
	
	bool isFilter = false;
	for (i = 0; i < size; i++) 
	{
		for (j = 0; j < size; j++) 
		{
			if (filter[i][j] != 0.0) 
			{
				isFilter = true;
				break;
			}
		}
		
		if (isFilter) 
			break;
	}
	
	for (i = 0; i < size; i++) 
	{
		for (j = 0; j < size; j++) 
		{
			if (isFilter) 
			{
				dataComplex2D[i][2*j] *= filter[i][j];
				dataComplex2D[i][2*j+1] *= filter[i][j];
			}
			
			if (i % 2 == 1) 
			{
				dataComplex2D[i][2*j] *= -1;
				dataComplex2D[i][2*j+1] *= -1;
			}
			
			if (j % 2 == 1) 
			{
				dataComplex2D[i][2*j] *= -1;
				dataComplex2D[i][2*j+1] *= -1;
			}
		}
	}
	
	fft2D(dataComplex2D, size, 2*size);
	
	for (i = 0; i < size; i++) 
	{
		for (j = 0; j < size; j++) 
		{
			double d1 = dataComplex2D[i][2*j];
			double d2 = dataComplex2D[i][2*j+1];
			data[size - i - 1][size - j - 1] = sqrt(d1 * d1 + d2 * d2);
		}
	}
}
	
void FFT::loop(double* x, int d, int off) 
{
	if (d == 1) 
	{
		double tmp = x[0];
		x[0] += x[2];
		x[2]  = tmp - x[2];
		tmp   = x[1];
		x[1] += x[3];
		x[3]  = tmp - x[3];
		return;
	}
	
	d--;
	int N = sizes[d];
	double* e = even[d];
	double* o = odd[d];
	for (int k = 0; k < N; k += 2) 
	{
		int k2 = k << 1;
		e[k]     = x[k2++];
		e[k + 1] = x[k2++];
		o[k]     = x[k2++];
		o[k + 1] = x[k2];
	}
	loop(e, d, off);
	loop(o, d, off + multi[d]);
	
	double* c = cosine[d];
	double* s = sine[d];
	for (int k = 0; k < N; k += 2) 
	{
		double add1 = c[k] * o[k] - s[k] * o[k + 1];
		x[k]         = e[k]     + add1;
		x[k + N]     = e[k]     - add1;
		double add2 = s[k] * o[k] + c[k] * o[k + 1];
		x[k + 1]     = e[k + 1] + add2;
		x[k + 1 + N] = e[k + 1] - add2;
	}
}

void FFT::swap(double** data) 
{
	for (int i = 0; i < size; i++) 
	{
		int i2 = i << 1;
		for (int j = 0; j < i; j++) 
		{
			int j2 = j << 1;
			double tmp  = data[i][j2];
			data[i][j2] = data[j][i2];
			data[j][i2] = tmp;
			tmp             = data[i][j2 + 1];
			data[i][j2 + 1] = data[j][i2 + 1];
			data[j][i2 + 1] = tmp;
		}
	}
}

double FFT::exp_lookup(double x) 
{
	int index = (int)(x / EXPTABLECUTOFF * EXPTABLESIZE);
	if (index >= EXPTABLESIZE) 
		return 0;
	
	return expTable[index];
}