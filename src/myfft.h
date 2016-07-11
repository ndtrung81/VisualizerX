// Adopted from Michael Engel's Injavis FFT Module
#ifndef __INJAVIS_FFT
#define __INJAVIS_FFT

class FFT
{
public:
	FFT(int s);
	~FFT();

	int size;

	void fft1D(double* data, int length);
	void fft2D(double** data, int row, int col); 

	void diffraction1D(double* data);
	void diffraction2D(double** data); 
	
	void filter2D(double** data, double** filter); 

	double exp_lookup(double x);
private:
	int depth;
	int* sizes, *multi;
	double **cosine, **sine, **even, **odd;
	double* dataComplex1D;
	double** dataComplex2D;

	int    EXPTABLESIZE;
	double EXPTABLECUTOFF;
	double* expTable;

	void loop(double* x, int d, int off);
	void swap(double** data);
	
};

#endif