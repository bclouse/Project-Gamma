//
//	Bryant Clouse
//	Traveling Salesman Problem
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <random>
#include <iomanip>
#include <cmath>
#include "Classes.h"

using namespace std;

int main() {
	int size = 30;		//Range for x and y locations of cities
	int n = 20;			//Cities
	int pop = 10;		//Numer of policies in the population
	int runs = 1000;		//Number of iterations that the evolutionary algorithm takes
	int sr = 1;			//Statistical Runs

	srand(time(NULL));
	Agent Darwin (size,n,pop);
	Darwin.p_random();
	Darwin.display();
	for (int i = 0; i < runs; i++) {
		Darwin.action();
	}
	cout << endl;
	Darwin.display();
	
	return 0;
}