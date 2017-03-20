#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <random>
#include <iomanip>
#include <cmath>

using namespace std;

#define ZERO_TO_ONE (float)rand()/RAND_MAX

#ifndef CLASSES_H
#define CLASSES_H

//===============================
//	Cities Struct
//===============================

struct City {
	float x, y;
	int num;
};

//===============================
//	Agent Class
//===============================

class Agent {
private:
	vector<vector<City>> policy;
	vector<float> distances;
	int start;
	int policies;
	int cities;
public:
	Agent(float,int,int);
	void p_random();
	void display();
	int action();
	void evaluate();
	void down_select();
	void repopulate();
	void mutate();
};

//===============================
//	Functions
//===============================

float distance(City, City);

#endif