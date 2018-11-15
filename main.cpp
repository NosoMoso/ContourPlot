#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <string>
#include <sstream>
#include <algorithm>

#include "cubic_spline.h"
using namespace std;

struct ray{
	Cubicspline pt;
	Cubicspline xt;
	Cubicspline yt;
	vector<double> x;// coordinate
	vector<double> y;// coordinate
	vector<double> t;// parameter

	vector<double> path;
	vector<double> time;

};

struct front{
	vector<double> x;// coordinate
	vector<double> y;// coordinate
	double cntr;// parameter
};

class Contour{
public:
	int n = 1; // rays number
	int m = 2; // contour number
	vector<vector<double>> contour;// matrix n*m
	vector<ray> full_rays;

	double step = 0;

	vector<front> fronts;

	Contour(double start, double end, int number){
		step = (end - start) / (number);
		double cnt_value = start;
		front null;
		for (int i = 0; i < number + 1; i++)
		{
			fronts.push_back(null);
			if (i == 0)
				cnt_value = start;
			else
				cnt_value = cnt_value + step;
			fronts[i].cntr = cnt_value;
		}

	};
	void read_data(string name)
	{
		string line;//

		int number = 0;
		fstream f1;// открытие файла
		f1.open((name + ".dat").c_str(), ios::in);

		while (!f1.eof()){
			getline(f1, line);
			if (line == "\0\0")
			{
				number++;
				if (number == 1){
					number = 0;
					n++;
				}
			}
		}
		f1.close();
		line.clear();

		//cout << n << endl;
		//system("pause");

		ray null;
		for (int i = 0; i < n; i++)
			full_rays.push_back(null);

		fstream file;// открытие файла
		file.open((name + ".dat").c_str(), ios::in);
		if (!file.eof()){
			cout << "File is opened !\n\n";
			int k = 0, g = 0;
			double curr;
			char mass[10];
			const char ch = '\n';

			double value;
			int h = 0;
			int null_str = 0;

			while (!file.eof()){
				getline(file, line);
				stringstream tokenizer(line);
				
				if (line == "\0\0"){
					null_str++;
					if (null_str == 1){
						null_str = 0;
						k++;
					}
				}

				while (tokenizer >> value){
					if (h == 0)
							full_rays[k].x.push_back(value);
					if (h == 1)
							full_rays[k].y.push_back(value);
					if (h == 4)
							full_rays[k].path.push_back(value);
					if (h == 4){
						h = 0;
						break;
					}
					h++;
				}
			}
			//cout << k << endl;
			/*
			while (!file.eof()){
				file.getline(mass, 9, ch);
				file >> curr;
				cout << strlen(mass) << endl;
				/*
				if (!strlen(mass)){
					file >> curr;// 1

					if (curr > 1e9){// проверка на пустое число (строку)
						file >> curr;// 2
						file >> curr;// 3
						file >> curr;// 4
						file >> curr;// 5
						file >> curr;// 6
						file >> curr;// 1
						//break;
						k++;
					}

					full_rays[k].x.push_back(curr);

					file >> curr;// 2
					full_rays[k].y.push_back(curr);
					file >> curr;// 3
					file >> curr;// 4
					file >> curr;// 5
					full_rays[k].path.push_back(curr);
					file >> curr;// 6
				}
				*/
			//}
			/*
			cout.precision(2);
			cout << fixed;

			for (int j = 0; j < n; j++){
				for (int i = 0; i < full_rays[j].x.size(); i++){
					cout << full_rays[j].x[i] << " " << full_rays[j].y[i] << " " << full_rays[j].path[i] << endl;
				}
				cout << "\n";
			}
			*/
		}
		else
			cout << "File is NOT opened !\n\n";
		file.close();
	};
	void spline_interpolation(){
		//
		for (int r = 0; r < full_rays.size(); r++){
			for (int i = 0; i < full_rays[r].x.size(); i++)
				full_rays[r].t.push_back(0);
			for (int i = 1; i < full_rays[r].x.size(); i++)
				full_rays[r].t[i] = full_rays[r].t[i - 1] + sqrt((full_rays[r].x[i] - full_rays[r].x[i - 1])*(full_rays[r].x[i] - full_rays[r].x[i - 1]) + (full_rays[r].y[i] - full_rays[r].y[i - 1])*(full_rays[r].y[i] - full_rays[r].y[i - 1]));

			full_rays[r].xt.build_spline(full_rays[r].t, full_rays[r].x);
			full_rays[r].yt.build_spline(full_rays[r].t, full_rays[r].y);
			full_rays[r].pt.build_spline(full_rays[r].path, full_rays[r].t);
			
			double t_curr = 0;

			//double end = 10;
			//double start = 0;
			//int number = 10;
			//double step = (end - start) / (number);

			for (int i = 0; i < fronts.size(); i++){
				
				t_curr = full_rays[r].pt.f(fronts[i].cntr);
				fronts[i].x.push_back(full_rays[r].xt.f(t_curr));
				fronts[i].y.push_back(full_rays[r].yt.f(t_curr));
				//t_curr += step;
			}
			full_rays[r].xt.free_mem();
			full_rays[r].yt.free_mem();
			full_rays[r].pt.free_mem();
			//system("pause");
		}
	};

	void show(){
		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < full_rays[j].x.size(); i++)
				cout << full_rays[j].x[i] << " " << full_rays[j].y[i] << " " << full_rays[j].path[i] << " " << full_rays[j].t[i] << endl;
			cout << "\n";
		}

		for (int j = 0; j < fronts.size(); j++){
			cout << fronts[j].cntr << "\n";
			for (int k = 0; k < n; k++){
				cout << fronts[j].x[k] << " " << fronts[j].y[k] << "\n";
			}
			cout << endl;
		}
			
	};

	void write_in_file(string name){
		FILE *file;
		file = fopen((name + ".dat").c_str(), "w");
		for (int j = 0; j < fronts.size(); j++){
			for (int k = 0; k < n; k++)
				fprintf(file, "\n %10.4f  %10.4f", fronts[j].x[k], fronts[j].y[k]);
			fprintf(file, "\n\n");
		}
		fclose(file);
	};
		
	void full_contour(){};
};

int main()
{
	double to = 0, tn = 1, n = 1;


	int i = 0;
	string name = "center";
	Contour ctr(to, tn, n);
	ctr.read_data(name);
	ctr.spline_interpolation();
	//ctr.show();
	ctr.write_in_file(name + "_fronts");

	name = "right";
	Contour ctr1(to, tn, n);
	ctr1.read_data(name);
	ctr1.spline_interpolation();
	//ctr.show();
	ctr1.write_in_file(name + "_fronts");

	name = "left";
	Contour ctr2(to, tn, n);
	ctr2.read_data(name);
	ctr2.spline_interpolation();
	//ctr.show();
	ctr2.write_in_file(name + "_fronts");

	return 0;
}