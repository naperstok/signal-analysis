#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

vector<double> Calculate_Function_Values(double t1, double t2, double freaquancy, double dt);

double Function(double time, double frequency);

double Inner_Product(vector<double> first, vector<double> second);

double Norm(vector<double> vector);

bool Is_orthonormal_set(double ort, double norm1, double norm2);

bool Is_orthonormal_set_with_all_calculations(vector<double> first, vector<double> second);

vector<double> Normalization(vector<double> vector, double norm);

double sinc(double x);

void Save_To_File(vector<double> time, vector<double> values, const string filename);

vector<double> Signal_Recovery(vector<double>& signalValues, double dt1, double t1, double t2, double dt);