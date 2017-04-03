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
	int n = 10;		//Cities
	int pop = 20;		//Numer of policies in the population
	int runs = 10000;	//Number of iterations that the evolutionary algorithm takes
	int sr = 5;		//Statistical Runs
	bool random = false;
	char c;
	float **fitness;
	float dummy;
	FILE *fp = fopen("Learning.txt","w+");
	bool user_input = true;

	srand(time(NULL));

	if (user_input) {
		cout << "How many cities do you want (10, 25, 100)? ";
		cin >> n;
		cout << "How many iterations per statisitcal run? ";
		cin >> runs;
		cout << "How many statistical runs (1-30)? ";
		cin >> sr;
		cout << "Do you want the cities to be placed randomly (Y/N)? ";
		do {
			cin >> c;
			if (c == 'Y') 			random = true;
			else if (c == 'N') 	random = false;
			else 						cout << "Invalid input\n";
		} while (c != 'Y' && c != 'N');
	}

	fitness = new float*[runs]();
	for (int i = 0; i < runs; i++) {
		fitness[i] = new float[3]();
	}

	Agent Darwin (size,n,pop,random);
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
