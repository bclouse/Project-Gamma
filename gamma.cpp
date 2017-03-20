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
	int n = 20;	//Cities
	int sr = 1;

	srand(time(NULL));
	Agent Darwin (30,n,10);
	Darwin.p_random();
	Darwin.display();
	for (int i = 0; i < 50; i++) {
		Darwin.mutate();
	}
	cout << "\n\nNEW:\n";
	Darwin.display();
	
	return 0;
}