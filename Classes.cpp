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
	for (int j = 0; j < policies; j++) {
		for (int i = 0; i < cities; i++) {
			printf("%3d  ", policy[j][i].num);
		}
		cout << endl;
	}
}

int Agent::action() {

}

void Agent::evaluate() {

}

void Agent::down_select() {

}

void Agent::repopulate() {

}

void Agent::mutate() {
	int id1, id2;
	City dummy;
	for (int i = 0; i < policies; i++) {
		id1 = 1+rand()%(cities-1);
		do {
			id2 = 1+rand()%(cities-1);
		} while (id1 == id2);
		dummy = policy[i][id1];
		policy[i][id1] = policy[i][id2];
		policy[i][id2] = dummy;
	}
}

//===============================
//	Functions
//===============================

float distance(City loc1, City loc2) {
	return sqrt(pow(loc1.x-loc2.x,2) + pow(loc1.y-loc2.y,2));
}
