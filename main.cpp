#include <iostream>
#include <vector>
#include "dsp2.h"

using namespace std;

int main() {

	//double f1 = 98; 1.5 1.5
	//double f2 = 118; 4.5 3
	double f1 = 1.5;
	double f2 = 4.5;
	double T = 1; //1
	double dt = 0.001;

	vector<double> time_values;
	for (double i = -T / 2; i < T / 2; i += dt) {
		time_values.push_back(i);
	}

	vector<double> first_function = Calculate_Function_Values(-T / 2 , T / 2, f1, dt);
	Save_To_File(time_values, first_function, "firstFunction.txt");

	vector<double> second_function = Calculate_Function_Values(-T / 2, T / 2, f2, dt);
	Save_To_File(time_values, second_function, "secondFunction.txt");
	
	//скалярное произведение
	double scalar = 0; 
	scalar = Inner_Product(first_function, second_function);
	cout << "Inner product of two vectors: " << scalar << endl;

	//нормы
	double norm1 = 0, norm2 = 0;
	norm1 = Norm(first_function); 
	cout << "\nFirst vector`s norm: " << norm1 << endl;

	norm2 = Norm(second_function);
	cout << "Second vector`s norm: " << norm2 << endl;

	//ортогональность
	cout << "\nAre the vectors orthogonal? "; 
	double ort = abs(scalar);
	if (round(ort) == 0)
		cout << "Yes.\n" << endl;
	else 
		cout << "No.\n" << endl;


	//ортонормированный базис
	cout << "Is it an orthonormal set of vectors? "; 
	if (Is_orthonormal_set(ort, norm1, norm2))
		cout << "Yes.\n" << endl;
	else
		cout << "No.\n" << endl;

	//как изменить, чтобы образовывали ортонормированный базис 
	//нормируем векторы
	vector<double> first_function1 = Normalization(first_function, norm1);
	vector<double> second_function1 = Normalization(second_function, norm2);

	cout << "Normalised vectors. Is it an orthonormal set of vectors? ";
	if (Is_orthonormal_set_with_all_calculations(first_function1, second_function1))
		cout << "Yes.\n" << endl;
	else
		cout << "No.\n" << endl;

	cout << "Is it an orthonormal set of vectors if f1 = 2f1, f2 = 2f2? ";
	first_function1 = Calculate_Function_Values(-T / 2, T / 2, 2 * f1, dt);
	second_function1 = Calculate_Function_Values(-T / 2, T / 2, 2 * f2, dt);

	if (Is_orthonormal_set_with_all_calculations(first_function1, second_function1))
		cout << "Yes.\n" << endl;
	else
		cout << "No.\n" << endl;


	cout << "Is it an orthonormal set of vectors if T = 2T? ";
	first_function1 = Calculate_Function_Values(-T, T, f1, dt);
	second_function1 = Calculate_Function_Values(-T, T, f2, dt);

	if (Is_orthonormal_set_with_all_calculations(first_function1, second_function1))
		cout << "Yes.\n" << endl;
	else
		cout << "No.\n" << endl;


	cout << "Is it an orthonormal set of vectors if T = T / 2? ";
	first_function1 = Calculate_Function_Values(-T / 4, T / 4, f1, dt);
	second_function1 = Calculate_Function_Values(-T / 4, T / 4, f2, dt);

	if (Is_orthonormal_set_with_all_calculations(first_function1, second_function1))
		cout << "Yes.\n" << endl;
	else
		cout << "No.\n" << endl;




	//задание 3
	double F = 10; 
	T = 10 / F; 
	double Fd = 10000; 
	dt = T / Fd; 

	double Fd1 = 1.5 * F;
	double Fd2 = 1.75 * F;
	double Fd3 = 2 * F;
	double Fd4 = 3 * F;
	double Fd5 = 1000 * F;


	vector<double> time_values2;
	for (double i = 0; i < T; i += dt) {
		time_values2.push_back(i);
	}

	vector<double> original = Calculate_Function_Values(0, T, F, dt);
	Save_To_File(time_values2, original, "original.txt");

	vector<double> discretiz1 = Calculate_Function_Values(0, T, F, T / Fd1);
	vector<double> recovered1 = Signal_Recovery(discretiz1, T / Fd1, 0, T, dt);
	Save_To_File(time_values2, recovered1, "1.5F.txt");

	vector<double> discretiz2 = Calculate_Function_Values(0, T, F, T / Fd2);
	vector<double> recovered2 = Signal_Recovery(discretiz2, T / Fd2, 0, T, dt);
	Save_To_File(time_values2, recovered2, "1.75F.txt");

	vector<double> discretiz3 = Calculate_Function_Values(0, T, F, T / Fd3);
	vector<double> recovered3 = Signal_Recovery(discretiz3, T / Fd3, 0, T, dt);
	Save_To_File(time_values2, recovered3, "2F.txt");

	vector<double> discretiz4 = Calculate_Function_Values(0, T, F, T / Fd4);
	vector<double> recovered4 = Signal_Recovery(discretiz4, T / Fd4, 0, T, dt);
	Save_To_File(time_values2, recovered4, "3F.txt");

	vector<double> discretiz5 = Calculate_Function_Values(0, T, F, T / Fd5);
	vector<double> recovered5 = Signal_Recovery(discretiz5, T / Fd5, 0, T, dt);
	Save_To_File(time_values2, recovered5, "1000F.txt");

	return 0;
}