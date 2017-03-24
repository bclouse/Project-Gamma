#include "Classes.h"

//===============================
//	Agent Class
//===============================

Agent::Agent(float size, int c, int p) {
	vector<City> init;
	City dummy;
	cities = c;
	policies = p;
	start = rand()%cities;
	FILE *fp = fopen("Cities.txt","w+");
	double step = (double) 360/c*RADIANS;

	if (policies%2 == 1) {
		policies++;
		cout << "\nNumber of policies wasn't even.\nThe number of policies was set to " << policies << endl;
	}

	City list;
	for (int i = 0; i < cities; i++) {
		list.x = (float) (cos(step*i)+1)*size+5;
		list.y = (float) (sin(step*i)+1)*size+5;
		list.num = i;
		init.push_back(list);
	}
	for (int i = 0; i < policies; i++) {
		policy.push_back(init);
	}
	fclose(fp);
}

void Agent::p_random() {
	vector<City> holder;
	int index;
	for (int j = 0; j < policies; j++) {
		holder.clear();
		for (int i = 0; i < cities; i++) {
			if (i == 0) {
				index = start;
			} else {
				index = rand()%policy[j].size();
			}
			holder.push_back(policy[j][index]);
			policy[j].erase(policy[j].begin()+index);
		}
		policy[j] = holder;
	}
}

void Agent::display() {
	for (int j = 0; j < policy.size(); j++) {
		for (int i = 0; i < cities; i++) {
			printf("%3d  ", policy[j][i].num);
		}
		cout << endl;
	}
}

void Agent::action(float** log, int n) {
	// cout << "eval";
	evaluate();
	log_data(log,n);
	// cout << ", down";
	down_select();
	// cout << ", and repop\n";
	repopulate();		//mutation happens in here
}

void Agent::evaluate() {
	float fit = 0;
	fitness.clear();
	//cout << endl;
	for (int i = 0; i < policies; i++) {
		fit = 0;
		for (int j = 0; j < cities-1; j++) {
			fit += distance(policy[i][j],policy[i][j+1]);
		}
		fitness.push_back(fit);
		// cout << i << ") " << fit << endl;
	}
}

void Agent::down_select() {
	int worst;
	do {
		worst = 0;
		for (int i = 1; i < fitness.size(); i++) {
			if (fitness[worst] < fitness[i]) worst = i;
		}
		policy.erase(policy.begin()+worst);
		fitness.erase(fitness.begin()+worst);
	} while (fitness.size() > policies/2);
	// cout << endl;
	// display();
	// cout << endl;
}

void Agent::repopulate() {
	int n = policy.size();
	for (int i = 0; i < n; i++) {
		policy.push_back(policy[i]);
		mutate(&(policy[n+i]));
	}
}

void Agent::mutate(vector<City> *pol) {
	int id1, id2;
	City dummy;

	id1 = 1+rand()%(cities-1);
	do {
		id2 = 1+rand()%(cities-1);
	} while (id1 == id2);
	dummy = (*pol)[id1];
	(*pol)[id1] = (*pol)[id2];
	(*pol)[id2] = dummy;
}

void Agent::log_data(float** log, int n) {
	int best = 0;
	int worst = 0;
	float avg = fitness[0];
	for (int i = 1; i < fitness.size(); i++) {
		if (fitness[i] < fitness[best]) best = i;
		if (fitness[i] > fitness[worst]) worst = i;
		avg += fitness[i];
	}
	log[n][0] += fitness[best];
	log[n][1] += avg/fitness.size();
	log[n][2] += fitness[worst];
}

void Agent::path() {
	FILE *fp = fopen("Path.txt", "w+");
	int best = 0;

	evaluate();
	for (int i = 1; i < fitness.size(); i++) {
		if (fitness[i] < fitness[best]) best = i;
	}

	for (int i = 0; i < cities; i++) {
		fprintf(fp, "%f\t%f\n", policy[best][i].x, policy[best][i].y);
	}

	fclose(fp);
}

//===============================
//	Functions
//===============================

float distance(City loc1, City loc2) {
	return sqrt(pow(loc1.x-loc2.x,2) + pow(loc1.y-loc2.y,2));
}

