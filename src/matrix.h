#ifndef __MATRIX
#define __MATRIX

#define NSIZE 3
#define NSIZE2 NSIZE*NSIZE

#include <iostream>
#include <vector>

class CVector
{
	friend std::ostream& operator<< (std::ostream& os, const CVector& u);
	friend void	stat(double* data, int n, double& mean, double& error);
	friend void histogram(double* data, int n);
	
public:
	CVector();
	~CVector();

	CVector(const CVector& obj);
	CVector(double* data);
	CVector(double x, double y, double z);
	CVector& operator= (const CVector& obj);

	double operator* (const CVector& obj);
	CVector operator* (double k);
	CVector operator/ (double k);
	CVector operator^ (const CVector& obj);
	CVector operator+ (const CVector& obj);
	CVector operator- (const CVector& obj);
	CVector& operator+= (const CVector& obj);
	CVector& operator-= (const CVector& obj);

	double& operator[] (int i);
	double operator[] (int i) const;

	double magnitude();
	void normalize();
	void pbc(double* L);

private:
	double* m_data;
};

class CMatrix
{
	friend CMatrix DyadicProduct(const CVector& u, const CVector& v);
	friend std::ostream& operator<< (std::ostream& os, const CMatrix& a);
public:
	CMatrix();
	~CMatrix();

	CMatrix(const CMatrix& obj);
	CMatrix(double* data);
	CMatrix(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33);
	CMatrix& operator= (const CMatrix& obj);

	CMatrix operator* (const CMatrix& obj);
	CMatrix operator+ (const CMatrix& obj);
	CVector operator* (CVector& vec);
	CMatrix operator* (double scale);
	CMatrix inv();
	CMatrix transpose();

	int diagonalize(double *evalues, double** evectors);

	double& operator() (int i, int j);
	double operator() (int i, int j) const;

	double* operator[] (int i);
	
	double det();
	double maximumBoxEdge();
private:
	void rotate1d(double* data, int i, int j, int k, int l, double s, double tau);
	void rotate2d(double** data, int i, int j, int k, int l, double s, double tau);

	double* m_data;
};

class CQuaternion
{
	friend CQuaternion matrixtoQuaternion(const CMatrix& mat);
	friend CMatrix quaterniontoMatrix(const CQuaternion& q);
public:
	CQuaternion();
	CQuaternion(const CQuaternion& q);
	CQuaternion(double _r, double _i, double _j, double _k);
	CQuaternion(double s, const CVector& v);
	CQuaternion& operator= (const CQuaternion& q);
	
	CQuaternion operator* (double k);
	CQuaternion operator* (const CQuaternion& q);
	CQuaternion operator* (const CVector& v);
	
	CQuaternion operator+ (const CQuaternion& q);
	CQuaternion& operator+= (const CQuaternion& q);

	void	normalize();

	double r, i, j, k;
};

class CTransform
{
public:
	CTransform()
	{
	}

	void Rotate(const CVector& axis, double angle);
	void Translate(const CVector& direction, double distance);
	void Scale(const CVector& scales);

	CMatrix m_transform;
};

#endif