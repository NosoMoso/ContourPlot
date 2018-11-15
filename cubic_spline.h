#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#ifndef CUBIC_SPLINE_H
#define CUBIC_SPLINE_H

#pragma warning(disable: 4996)// Отключение ошибок в fprintf
#define _CRT_SECURE_NO_WARNINGS

class Cubicspline
{
public:
	// Структура, описывающая сплайн на каждом сегменте сетки
	struct spline_tuple
	{
		double a, b, c, d, x;
	};
	spline_tuple *splines; // Сплайн
	size_t n; // Количество узлов сетки
	
	void free_mem(); // Освобождение памяти

	Cubicspline(){ splines = NULL; }; //конструктор
	~Cubicspline(){ free_mem(); }; //деструктор
	// Построение сплайна
	// x - узлы сетки, должны быть упорядочены по возрастанию, кратные узлы запрещены
	// y - значения функции в узлах сетки
	// n - количество узлов сетки
	//void build_spline(const double *x, const double *y, std::size_t n)
	void build_spline(vector<double>, vector<double>);
	// Вычисление значения интерполированной функции в произвольной точке
	double f(double) const;
};
#endif