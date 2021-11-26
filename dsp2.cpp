#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include "dsp2.h"

using namespace std;

vector<double> Calculate_Function_Values(double t1, double t2, double freaquancy, double dt) {
	int size = static_cast<int>((t2 - t1) / dt); //  ����������� ����� ��� �������� � �������������� ������� 
	vector<double> result(size);                 //  T/2 - (-T/2) �������� �� ���
	double value = 0;
	double t = t1;

	for (int i = 0; i < size; i++) { //���� �� ��������� ��� ��������
		value = Function(t, freaquancy); //������� �������� � �����
		result[i] = value; //���������� ���
		t += dt; //������ ��� -T/2 + dt
	}
	return result;
}

double Function(double time, double frequency) {
	return sin(2 * M_PI * frequency * time);
}

void Save_To_File(vector<double> time, vector<double> values, const string filename) {
	ofstream fout(filename);
	if (fout.is_open()) {
		for (int i = 0; i < values.size(); i++)
			fout << time[i] << " " << values[i] << endl;
	}
	else
		cout << "Can`t open the file" << endl;
	fout.close();
}

double Inner_Product(vector<double> first, vector<double> second) {
	double scalar = 0;
	for (int i = 0; i < first.size(); i++) 
		scalar += first[i] * second[i];
	return scalar;
}

double Norm(vector<double> v) {
	double norm = 0;
	norm = sqrt(Inner_Product(v, v));
	return norm;
}

vector<double> Normalization(vector<double> v, double norm) {
	vector<double> result(v.size());
	for (int i = 0; i < v.size(); i++)
		result.push_back(v[i] / norm);
	return result;

}

/*bool Is_orthonormal_set(double ort, double norm1, double norm2) {
	if ((ort < 0.000001) && (abs(norm1) - 1 < 0.000001) && (abs(norm2)) - 1 < 0.000001)
		return true;
	else
		return false;
}*/

bool Is_orthonormal_set(double ort, double norm1, double norm2) {
	if ((round(ort) == 0) && (round(abs(norm1)) == 1) && (round(abs(norm2)) == 1))
		return true;
	else
		return false;
}

bool Is_orthonormal_set_with_all_calculations(vector<double> first, vector<double> second) {
	double scalar = 0;
	scalar = Inner_Product(first, second);
	double ort = abs(scalar);

	double norm1 = 0, norm2 = 0;
	norm1 = Norm(first); norm2 = Norm(second);
	if (Is_orthonormal_set(ort, norm1, norm2))
		return true;
	else
		return false;
	
}

double sinc(double x) {
	if (x != 0)
		return sin(x) / x;
	else
		return 1;
}

vector<double> Signal_Recovery(vector<double>& signalValues, double dt1, double t1, double t2, double dt) {
	int size_discrete_vector = signalValues.size();
	int size_reconstruct_vector = static_cast<int>((t2 - t1) / dt); // ����� ��� � ������� ��� ������� ������
	vector<double> result(size_reconstruct_vector);                 //  ������� ��� ���������������� �������
	double t = t1;

	for (int i = 0; i < size_reconstruct_vector; i++) { //���� �� �������� ��� ��������
		double total = 0;
		                                //�� ������� ������������
		for (int k = 0; k < size_discrete_vector; k++) // ���� �� ���� ��������� ������� �� �������� ���������������
			total += signalValues[k] * sinc(M_PI * (t / dt1 - k)); //������� �������� �� �������

		result[i] = total;
		t += dt; //������ ��� dt (��� ��� ��������� �������)
	}
	return result;
}


