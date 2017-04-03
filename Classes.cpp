#include "Classes.h"

//===============================
//	Agent Class
//===============================

Agent::Agent(float size, int c, int p, bool random) {
	vector<City> init;
	City dummy;
	cities = c;
	policies = p;
	start = 0;
	double step = (double) 360/c*RADIANS;

	if (policies%2 == 1) {
		policies++;
		cout << "\nNumber of policies wasn't even.\nThe number of policies was set to " << policies << endl;
	}

	City list;
	for (int i = 0; i < cities; i++) {
		if (random) {
			list.x = ZERO_TO_ONE*2*size+5;
			list.y = ZERO_TO_ONE*2*size+5;
		} else {
			list.x = (float) (cos(step*i)+1)*size+5;
			list.y = (float) (sin(step*i)+1)*size+5;
		}
		list.num = i;
		init.push_back(list);
	}
	for (int i = 0; i < policies; i++) {
		policy.push_back(init);
	}
	assert(policy.size() != 0);	//MR_1
}

void Agent::p_random() {
	vector<City> holder;
	int index;
	int dummy;

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
		assert(policy[j][0].num == start);				//LR_5
	}
}

void Agent::display() {
	for (int j = 0; j < policy.size(); j++) {
		for (int i = 0; i < cities; i++) {
			printf("%3d  ", policy[j][i].num);
		}
		cout << endl;
		// if (j == 4) cout << endl;
	}
}

void Agent::action(float** log, int n) {
	evaluate();
	log_data(log,n);
	down_select();
	repopulate();
}

void Agent::evaluate() {
	float fit = 0;
	fitness.clear();
	for (int i = 0; i < policies; i++) {
		fit = 0;
		for (int j = 0; j < cities-1; j++) {
			fit += distance(policy[i][j],policy[i][j+1]);
		}
		fitness.push_back(fit);
		assert(fitness[fitness.size()-1] != 0);			//LR_8, MR_2 and MR_3
	}
}

void Agent::down_select() {
	int first, second;
	int old = fitness.size();

	for (int i = 0; i < policies/2; i++) {
		first = rand()%fitness.size();
		do {
			second = rand()%fitness.size();
		} while (second == first);
		if (fitness[first] <= fitness[second]) {
			policy.erase(policy.begin()+second);
			fitness.erase(fitness.begin()+second);
		} else {
			policy.erase(policy.begin()+first);
			fitness.erase(fitness.begin()+first);
		}
	}
	assert(old/2 == fitness.size());					//MR_4
}

void Agent::repopulate() {
	int count = 0;
	int n = policy.size();
	int old = policy.size();

	for (int i = 0; i < n; i++) {
		policy.push_back(policy[i]);
		mutate(&(policy[n+i]));
		count = 0;
		for (int j = 0; j < cities; j++) {
			if (policy[i][j].num != policy[n+i][j].num) {
				count++;
			}
		}
		assert(0.5 > (float)count/cities);					//LR_4
	}
	assert(old*2 == policy.size());							//MR_5
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
	float dist = sqrt(pow(loc1.x-loc2.x,2) + pow(loc1.y-loc2.y,2));
	assert(dist != 0);																//LR_7
	return dist;
}



