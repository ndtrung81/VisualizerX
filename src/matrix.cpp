#include "StdAfx.h"
#include "matrix.h"
#include <math.h>

#define MAXJACOBI 50
#define anint(x) ((x >= 0.5) ? (1.0) : (x < -0.5) ? (-1.0) : (0.0))	

CMatrix::CMatrix()
{
	m_data = new double [NSIZE2];

	int i;
	for (i=0; i<NSIZE2; i++)
		m_data[i] = 0.0;

	// Identity matrix by default
	m_data[0] = m_data[4] = m_data[8] = 1.0;
}

CMatrix::CMatrix(double* data)
{
	m_data = new double [NSIZE2];

	int i;
	for (i=0; i<NSIZE2; i++)
		m_data[i] = data[i];
}

CMatrix::CMatrix(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
{
	m_data = new double [NSIZE2];

	m_data[0] = a11;	m_data[1] = a12; m_data[2] = a13;
	m_data[3] = a21;	m_data[4] = a22; m_data[5] = a23;
	m_data[6] = a31;	m_data[7] = a32; m_data[8] = a33;
}

CMatrix::CMatrix(const CMatrix& obj)
{
	m_data = new double [NSIZE2];

	int i;
	for (i=0; i<NSIZE2; i++)
		m_data[i] = obj.m_data[i];
}

CMatrix::~CMatrix()
{
	delete [] m_data;
}

CMatrix& CMatrix::operator= (const CMatrix& obj)
{
	if (&obj == this)
		return *this;

	int i;
	for (i=0; i<NSIZE2; i++)
		m_data[i] = obj.m_data[i];

	return *this;
}

CMatrix CMatrix::operator* (const CMatrix& obj)
{
	int i, j, k;
	double aij;
	CMatrix result;

	for (i=0; i<NSIZE; i++)
	{
		for (j=0; j<NSIZE; j++)
		{
			aij = 0.0;
			for (k=0; k<NSIZE; k++)
				aij += m_data[i*NSIZE + k] * obj.m_data[NSIZE*k + j];
			
			result.m_data[i*NSIZE + j] = aij;
		}
	}
	
	return result;
}

CMatrix CMatrix::operator+ (const CMatrix& obj)
{
	int i, j;
	CMatrix result;

	for (i=0; i<NSIZE; i++)
		for (j=0; j<NSIZE; j++)
			result.m_data[i*NSIZE + j] = m_data[i*NSIZE + j] + obj.m_data[i*NSIZE + j];
	
	return result;
}

CVector CMatrix::operator* (CVector& vec)
{
	int i, j;
	double ai;
	CVector result;

	for (i=0; i<NSIZE; i++)
	{
		ai = 0.0;
		for (j=0; j<NSIZE; j++)
			ai += m_data[i*NSIZE + j] * vec[j];
			
		result[i] = ai;
	}
	
	return result;
}

CMatrix CMatrix::operator* (double scale)
{
	int i;
	CMatrix result;

	for (i=0; i<NSIZE2; i++)
		result.m_data[i] = m_data[i] * scale;
		
	return result;
}


CMatrix CMatrix::inv()
{
	CMatrix result;
	double det;
	det = m_data[0] * m_data[4] * m_data[8] + m_data[1] * m_data[5] * m_data[6] + m_data[2] * m_data[7] * m_data[3]
		- (m_data[2] * m_data[4] * m_data[6] + m_data[1] * m_data[8] * m_data[3] + m_data[0] * m_data[7] * m_data[5]);

	result(0, 0) =  (m_data[4] * m_data[8] - m_data[5] * m_data[7]) / det;
	result(0, 1) = -(m_data[1] * m_data[8] - m_data[2] * m_data[7]) / det;
	result(0, 2) =  (m_data[1] * m_data[5] - m_data[2] * m_data[4]) / det;

	result(1, 0) = -(m_data[3] * m_data[8] - m_data[5] * m_data[6]) / det;
	result(1, 1) =  (m_data[0] * m_data[8] - m_data[2] * m_data[6]) / det;
	result(1, 2) = -(m_data[0] * m_data[5] - m_data[2] * m_data[3]) / det;

	result(2, 0) =  (m_data[3] * m_data[7] - m_data[4] * m_data[6]) / det;
	result(2, 1) = -(m_data[0] * m_data[7] - m_data[1] * m_data[6]) / det;
	result(2, 2) =  (m_data[0] * m_data[4] - m_data[1] * m_data[3]) / det;

	return result;
}

double& CMatrix::operator() (int i, int j) 
{
	return m_data[i*NSIZE + j];
}

double CMatrix::operator() (int i, int j) const
{
	return m_data[i*NSIZE + j];
}

double* CMatrix::operator[] (int i)
{
	return &m_data[i*NSIZE];
}

double CMatrix::det()
{
	double det;
	det = m_data[0] * m_data[4] * m_data[8] + m_data[1] * m_data[5] * m_data[6] + m_data[2] * m_data[7] * m_data[3]
		- (m_data[2] * m_data[4] * m_data[6] + m_data[1] * m_data[8] * m_data[3] + m_data[0] * m_data[7] * m_data[5]);

	return det;
}

CMatrix CMatrix::transpose()
{
	int i, j;
	CMatrix result;

	for (i=0; i<NSIZE; i++)
		for (j=0; j<NSIZE; j++)
			result.m_data[i*NSIZE + j] = m_data[j*NSIZE + i];
		
	return result;
}


int CMatrix::diagonalize(double *evalues, double** evectors)
{
	int i, j, k, iter;
	double tresh, theta, tau, t, sm, s, h, g, c, b[3], z[3];
	
	for (i=0; i<3; i++) 
	{
		for (j=0; j<3; j++) 
			evectors[i][j] = 0.0;
		
		evectors[i][i] = 1.0;
	}
	
	for (i=0; i<3; i++) 
	{
		b[i] = evalues[i] = m_data[i * NSIZE + i];
		z[i] = 0.0;
	}
	
	for (iter=1; iter<=MAXJACOBI; iter++) 
	{
		sm = 0.0;
		for (i=0; i<2; i++)
			for (j=i+1; j<3; j++)
				sm += fabs(m_data[i * NSIZE + j]);
			if (sm == 0.0) 
				return 0;
			
		if (iter < 4) 
			tresh = 0.2 * sm / (3 * 3);
		else 
			tresh = 0.0;
			
		for (i=0; i<2; i++) 
		{
			for (j=i+1; j<3; j++) 
			{
				g = 100.0*fabs(m_data[i * NSIZE + j]);
				if (iter > 4 && fabs(evalues[i])+g == fabs(evalues[i])
					&& fabs(evalues[j])+g == fabs(evalues[j]))
					m_data[i * NSIZE + j] = 0.0;
				else if (fabs(m_data[i * NSIZE + j]) > tresh) 
				{
					h = evalues[j] - evalues[i];
					if (fabs(h)+g == fabs(h)) 
						t = (m_data[i * NSIZE + j]) / h;
					else 
					{
						theta = 0.5 * h / (m_data[i * NSIZE + j]);
						t = 1.0 / (fabs(theta) + sqrt(1.0 + theta * theta));
						if (theta < 0.0) 
							t = -t;
					}

					c = 1.0 / sqrt(1.0 + t * t);
					s = t * c;
					tau = s / (1.0 + c);
					h = t * m_data[i * NSIZE + j];
					z[i] -= h;
					z[j] += h;
					evalues[i] -= h;
					evalues[j] += h;
					m_data[i * NSIZE + j] = 0.0;
					
					for (k=0; k<i; k++)
						rotate1d(m_data, k, i, k, j, s, tau);
					
					for (k=i+1; k<j; k++) 
						rotate1d(m_data, i, k, k, j, s, tau);
					
					for (k=j+1; k<3; k++) 
						rotate1d(m_data, i, k, j, k, s, tau);
					
					for (k=0; k<3; k++) 
						rotate2d(evectors, k, i, k, j, s, tau);
				}
			}
		}
			
		for (i=0; i<3; i++) 
		{
			evalues[i] = b[i] += z[i];
			z[i] = 0.0;
		}
	}

	return 1;
}

void CMatrix::rotate1d(double* data, int i, int j, int k, int l, double s, double tau)
{
	double g = data[i * NSIZE + j];
	double h = data[k * NSIZE + l];
	data[i * NSIZE + j] = g - s * (h + g * tau);
	data[k * NSIZE + l] = h + s * (g - h * tau);
} 

void CMatrix::rotate2d(double** data, int i, int j, int k, int l, double s, double tau)
{
	double g = data[i][j];
	double h = data[k][l];
	data[i][j] = g - s * (h + g * tau);
	data[k][l] = h + s * (g - h * tau);
} 

CMatrix DyadicProduct(const CVector& u, const CVector& v)
{
	CMatrix mat;
	mat(0, 0) = u[0] * v[0];
	mat(0, 1) = u[0] * v[1];
	mat(0, 2) = u[0] * v[2];
	
	mat(1, 0) = u[1] * v[0];
	mat(1, 1) = u[1] * v[1];
	mat(1, 2) = u[1] * v[2];
	
	mat(2, 0) = u[2] * v[0];
	mat(2, 1) = u[2] * v[1];
	mat(2, 2) = u[2] * v[2];

	return mat;
}

double CMatrix::maximumBoxEdge() 
{
	double Lx = sqrt(m_data[0 * NSIZE + 0]*m_data[0 * NSIZE + 0] 
		+ m_data[1 * NSIZE + 0]*m_data[1 * NSIZE + 0] 
		+ m_data[2 * NSIZE + 0]*m_data[2 * NSIZE + 0]);
	double Ly = sqrt(m_data[0 * NSIZE + 1]*m_data[0 * NSIZE + 1] 
		+ m_data[1 * NSIZE + 1]*m_data[1 * NSIZE + 1] 
		+ m_data[2 * NSIZE + 1]*m_data[2 * NSIZE + 1]);
	double Lz = sqrt(m_data[0 * NSIZE + 2]*m_data[0 * NSIZE + 2] 
		+ m_data[1 * NSIZE + 2]*m_data[1 * NSIZE + 2] 
		+ m_data[2 * NSIZE + 2]*m_data[2 * NSIZE + 2]);
	double Lmax = Lx;
	if (Lmax < Ly) Lmax = Ly;
	if (Lmax < Lz) Lmax = Lz;

	return Lmax;
}

std::ostream& operator<< (std::ostream& os, const CMatrix& a)
{
	for (int i=0; i<NSIZE; i++)
	{
		for (int j=0; j<NSIZE; j++)
			os << a(i, j) << "\t";

		os << std::endl;
	}

	return os;
}

//////////////////////////////////////////////////////

CQuaternion::CQuaternion()
{
	r = i = j = k = 0.0;
}

CQuaternion::CQuaternion(const CQuaternion& q)
{
	r = q.r;
	i = q.i;
	j = q.j;
	k = q.k;
}

CQuaternion::CQuaternion(double _r, double _i, double _j, double _k)
{
	r = _r;
	i = _i;
	j = _j;
	k = _k;
}

CQuaternion::CQuaternion(double s, const CVector& v)
{
	r = s;
	i = v[0];
	j = v[1];
	k = v[2];
}

CQuaternion& CQuaternion::operator= (const CQuaternion& q)
{
	if (&q == this)
		return *this;

	r = q.r;
	i = q.i;
	j = q.j;
	k = q.k;
	return *this;
}

CQuaternion CQuaternion::operator* (double s)
{
	return CQuaternion(s * r, s * i, s * j, s * k);
}

CQuaternion CQuaternion::operator* (const CQuaternion& q)
{
	double s;
	s = r * q.r - (i * q.i + j * q.j + k * q.k);

	CVector v1(i, j, k), v2(q.i, q.j, q.k), v;
	v = v2 * r + v1 * q.r + v1 ^ v2;

	return CQuaternion(s, v);
}

CQuaternion CQuaternion::operator+ (const CQuaternion& q)
{
	double s;
	s = r + q.r; 

	CVector v(i + q.i, j + q.j, k + q.k);
	
	return CQuaternion(s, v);
}

CQuaternion& CQuaternion::operator+= (const CQuaternion& q)
{
	r += q.r; 
	i += q.i;
	j += q.j;
	k += q.k;
	
	return *this;
}

CQuaternion CQuaternion::operator* (const CVector& v)
{
	CQuaternion q(0, v);

	return ((*this) * q);
}

void	CQuaternion::normalize()
{
	double length;
	length = sqrt(r * r + i * i + j * j + k * k);

	r = r / length;
	i = i / length;
	j = j / length;
	k = k / length;
}

CMatrix quaterniontoMatrix(const CQuaternion& q)
{
	CMatrix mat;

	mat(0, 0) = 1 - 2 * q.j * q.j - 2 * q.k * q.k;
	mat(0, 1) = 2 * q.i * q.j - 2 * q.r * q.k;
	mat(0, 2) = 2 * q.i * q.k + 2 * q.r * q.j;

	mat(1, 0) = 2 * q.i * q.j + 2 * q.r * q.k;
	mat(1, 1) = 1 - 2 * q.i * q.i - 2 * q.r * q.k;
	mat(1, 2) = 2 * q.j * q.k - 2 * q.r * q.i;

	mat(2, 0) = 2 * q.i * q.k - 2 * q.r * q.j;
	mat(2, 1) = 2 * q.j * q.k + 2 * q.r * q.i;
	mat(2, 2) = 1 - 2 * q.i * q.i - 2 * q.j * q.j;

	return mat;
}

CQuaternion matrixtoQuaternion(const CMatrix& mat)
{
	CQuaternion q;
	double tr, s;

	tr = mat(0, 0) + mat(1, 1) + mat(2, 2);
	if (tr >= 0)
	{
		s = sqrt(tr + 1);
		q.r = 0.5 * s;
		s = 0.5 / s;

		q.i = (mat(2, 1) - mat(1, 2)) * s;
		q.j = (mat(0, 2) - mat(2, 0)) * s;
		q.k = (mat(1, 0) - mat(0, 1)) * s;
	}
	else
	{
		// find the largest element on the diagonal of the matrix
		int i = 0;

		if (mat(1, 1) > mat(0, 0))
			i = 1;

		if (mat(2, 2) > mat(i, i))
			i = 2;

		switch (i)
		{
		case 0:
			s = sqrt(mat(0, 0) - (mat(1, 1) + mat(2, 2)) + 1);
			q.i = 0.5 * s;
			s = 0.5 / s;
			
			q.j = (mat(0, 1) - mat(1, 0)) * s;
			q.k = (mat(2, 0) - mat(0, 2)) * s;
			q.r = (mat(2, 1) - mat(1, 2)) * s;
			break;
		
		case 1:
			s = sqrt(mat(1, 1) - (mat(2, 2) + mat(0, 0)) + 1);
			q.j = 0.5 * s;
			s = 0.5 / s;
			
			q.k = (mat(1, 2) - mat(2, 1)) * s;
			q.i = (mat(0, 1) - mat(1, 0)) * s;
			q.r = (mat(0, 2) - mat(2, 0)) * s;
			break;

		case 2:
			s = sqrt(mat(2, 2) - (mat(0, 0) + mat(1, 1)) + 1);
			q.k = 0.5 * s;
			s = 0.5 / s;
			
			q.i = (mat(2, 0) - mat(0, 2)) * s;
			q.j = (mat(1, 2) - mat(2, 1)) * s;
			q.r = (mat(1, 0) - mat(0, 1)) * s;
			break;
		}
	}

	// always return normalized quaternion
	q.normalize();

	return q;
}

////////////////////////////////////////////////////

CVector::CVector()
{
	m_data = new double [NSIZE];

	int i;
	for (i=0; i<NSIZE; i++)
		m_data[i] = 0.0;
}

CVector::CVector(double* data)
{
	m_data = new double [NSIZE];

	int i;
	for (i=0; i<NSIZE; i++)
		m_data[i] = data[i];
}

CVector::CVector(double x, double y, double z)
{
	m_data = new double [NSIZE];

	m_data[0] = x;
	m_data[1] = y;
	m_data[2] = z;
}

CVector::CVector(const CVector& obj)
{
	m_data = new double [NSIZE];

	int i;
	for (i=0; i<NSIZE; i++)
		m_data[i] = obj.m_data[i];
}

CVector::~CVector()
{
	delete [] m_data;
}


CVector& CVector::operator= (const CVector& obj)
{
	if (&obj == this)
		return *this;

	int i;
	for (i=0; i<NSIZE; i++)
		m_data[i] = obj.m_data[i];

	return *this;
}

double CVector::operator* (const CVector& obj)
{
	int i;
	double dot;
	
	dot = 0.0;
	for (i=0; i<NSIZE; i++)
		dot += m_data[i] * obj.m_data[i];

	return dot;
}

CVector CVector::operator* (double k)
{
	int i;
	CVector result;
	
	for (i=0; i<NSIZE; i++)
		result[i] = m_data[i] * k;

	return result;
}

CVector CVector::operator/ (double k)
{
	int i;
	CVector result;
	
	for (i=0; i<NSIZE; i++)
		result[i] = m_data[i] / k;

	return result;
}

CVector CVector::operator^ (const CVector& obj)
{
	CVector cross;
	
	cross.m_data[0] = m_data[1] * obj.m_data[2] - m_data[2] * obj.m_data[1];
	cross.m_data[1] = m_data[2] * obj.m_data[0] - m_data[0] * obj.m_data[2];
	cross.m_data[2] = m_data[0] * obj.m_data[1] - m_data[1] * obj.m_data[0];

	return cross;
}

CVector CVector::operator+ (const CVector& obj)
{
	int i;
	CVector sum;
	
	for (i=0; i<NSIZE; i++)
		sum[i] = m_data[i] + obj[i];

	return sum;
}

CVector CVector::operator- (const CVector& obj)
{
	int i;
	CVector sum;
	
	for (i=0; i<NSIZE; i++)
		sum[i] = m_data[i] - obj[i];

	return sum;
}

CVector& CVector::operator+= (const CVector& obj)
{
	int i;
	for (i=0; i<NSIZE; i++)
		m_data[i] = m_data[i] + obj[i];

	return *this;
}

CVector& CVector::operator-= (const CVector& obj)
{
	int i;
	for (i=0; i<NSIZE; i++)
		m_data[i] = m_data[i] - obj[i];

	return *this;
}

double& CVector::operator[] (int i) 
{
	return m_data[i];
}

double CVector::operator[] (int i) const
{
	return m_data[i];
}

double CVector::magnitude()
{
	return sqrt(m_data[0] * m_data[0] + m_data[1] * m_data[1] + m_data[2] * m_data[2]);
}

void CVector::normalize()
{
	double norm = magnitude();
	m_data[0] /= norm;
	m_data[1] /= norm;
	m_data[2] /= norm;
}

void CVector::pbc(double* L)
{
	m_data[0] -= L[0] * anint(m_data[0] / L[0]);
	m_data[1] -= L[1] * anint(m_data[1] / L[1]);
	m_data[2] -= L[2] * anint(m_data[2] / L[2]);
}

std::ostream& operator<< (std::ostream& os, const CVector& u)
{
	for (int i=0; i<NSIZE; i++)
		os << u[i] << "\t";

	os << std::endl;

	return os;
}

void stat(double* data, int n, double& mean, double& error)
{
	int i;
	mean = 0.0;
	error = 0.0;
	
	for (i=0; i<n; i++)
		mean += data[i];
	mean /= n;
	
	for (i=0; i<n; i++)
		error += (data[i] - mean) * (data[i] - mean);
	error = sqrt(error / n);
}

void histogram(double* data, int n)
{
	int i, ibin, nbins=100;
	double *bin;
	double min, max, bin_size;
	
	min = max = data[0];
	for (i=1; i<n; i++)
	{
		if (min > data[i])
			min = data[i];

		if (max < data[i])
			max = data[i];
	}

	bin = new double [nbins];
	bin_size = (max - min) / nbins;

	for (i=0; i<nbins; i++)
		bin[i] = 0.0;

	for (i=0; i<n; i++)
	{
		ibin = (data[i] - min) / bin_size;
		bin[ibin] = bin[ibin] + 1;
	}
	
	FILE* file;
	file = fopen("histogram.txt", "w");
	for (i=0; i<nbins; i++)
		fprintf(file, "%0.3f\t%0.3f\n", min + i * bin_size, bin[i] / n);

	fclose(file);

	delete [] bin;
}	

