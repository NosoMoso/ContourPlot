#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#ifndef CUBIC_SPLINE_H
#define CUBIC_SPLINE_H

#pragma warning(disable: 4996)// ���������� ������ � fprintf
#define _CRT_SECURE_NO_WARNINGS

class Cubicspline
{
public:
	// ���������, ����������� ������ �� ������ �������� �����
	struct spline_tuple
	{
		double a, b, c, d, x;
	};
	spline_tuple *splines; // ������
	size_t n; // ���������� ����� �����
	
	void free_mem(); // ������������ ������

	Cubicspline(){ splines = NULL; }; //�����������
	~Cubicspline(){ free_mem(); }; //����������
	// ���������� �������
	// x - ���� �����, ������ ���� ����������� �� �����������, ������� ���� ���������
	// y - �������� ������� � ����� �����
	// n - ���������� ����� �����
	//void build_spline(const double *x, const double *y, std::size_t n)
	void build_spline(vector<double>, vector<double>);
	// ���������� �������� ����������������� ������� � ������������ �����
	double f(double) const;
};
#endif