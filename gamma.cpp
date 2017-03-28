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
	int size = 20;		//Range for x and y locations of cities
	int n = 25;		//Cities
	int pop = 20;		//Numer of policies in the population
	int runs = 100000;	//Number of iterations that the evolutionary algorithm takes
	int sr = 1;		//Statistical Runs
	float **fitness;
	float dummy;
	FILE *fp = fopen("Learning.txt","w+");

	srand(time(NULL));

	fitness = new float*[runs]();
	for (int i = 0; i < runs; i++) {
		fitness[i] = new float[3]();
	}

	Agent Darwin (size,n,pop);
	for (int j = 0; j < sr; j++) {
		Darwin.p_random();
		printf("Statisitcal Run #%d\n", j+1);
		for (int i = 0; i < runs; i++) {
			Darwin.action(fitness,i);
		}
	}
	Darwin.path();

	for (int i = 0; i < runs; i++) {
		fprintf(fp, "%d\t%f\t%f\t%f\n", i, fitness[i][0]/sr, fitness[i][1]/sr, fitness[i][2]/sr);
		//printf("%d\t%f\t%f\t%f\n", i, fitness[i][0]/sr, fitness[i][1]/sr, fitness[i][2]/sr);
	}
	cout << endl;
	// Darwin.display();
	
	for (int i = 0; i < runs; i++) {
		delete [] fitness[i];
	}
	delete [] fitness;
	fclose(fp);
	return 0;
}
