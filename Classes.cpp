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

	if (policies%2 == 1) {
		policies++;
		cout << "\nNumber of policies wasn't even.\nThe number of policies was set to " << policies << endl;
	}

	City *list = new City[cities];
	for (int i = 0; i < cities; i++) {
		list[i].x = (float) ZERO_TO_ONE*size;
		list[i].y = (float) ZERO_TO_ONE*size;
		list[i].num = i;
		init.push_back(list[i]);
	}
	for (int i = 0; i < policies; i++) {
		policy.push_back(init);
	}
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

float Agent::action() {
	float best;
	// cout << "eval";
	best = evaluate();
	// cout << ", down";
	down_select();
	// cout << ", and repop\n";
	repopulate();		//mutation happens in here
	return best;
}

float Agent::evaluate() {
	int best = 0;
	int fit = 0;
	fitness.clear();
	//cout << endl;
	for (int i = 0; i < policies; i++) {
		fit = 0;
		for (int j = 0; j < cities-1; j++) {
			fit += distance(policy[i][j],policy[i][j+1]);
		}
		fitness.push_back(fit);
		// cout << i << ") " << fit << endl;
		if (fitness[best] > fitness[i]) best = i;
	}
	return fitness[best];
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

//===============================
//	Functions
//===============================

float distance(City loc1, City loc2) {
	return sqrt(pow(loc1.x-loc2.x,2) + pow(loc1.y-loc2.y,2));
}