// Cellular_Automaton.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <string> 
using namespace std;

//global
int length;
int steps;
int rule;
//output
ofstream daten("automaton_daten.txt", ios::out);

void initialize_world(int site_[]) {
	for (int i = 0; i < length; i++) {
		site_[i] = rand() % 2;
	}
	return;
}

void show_world(int site_[]) {
	for (int i = 0; i < length; i++) {
		if (site_[i] == 1) {
			cout << "o";
		}
		else {
			cout << " ";
		}
	}
	cout << endl;
}

void write_world(int site_[]) {
	for (int i = 0; i < length; i++) {
		daten << site_[i] << " ";
	}
	daten << endl;
}

int calc_110(int left__, int right__, int site__) {
	string sleft = to_string(left__);
	string sright = to_string(right__);
	string ssite = to_string(site__);
	string state = sleft + ssite + sright;

	if (state == "000") return 0;
	else if (state == "100") return 0;
	else if (state == "010") return 1;
	else if (state == "001") return 1;
	else if (state == "110") return 1;
	else if (state == "101") return 1;
	else if (state == "011") return 1;
	else if (state == "111") return 0;
}

int calc_next_val(int left_, int right_, int site_) {
	switch (rule) {
	case 1: return calc_110(left_, right_, site_);
	}
}

void calc_next_state(int site_[]) {
	int * site_tmp = new int[length];

	for (int i = 0; i < length; i++) {
		//left bound
		if (i == 0) {
			site_tmp[i] = calc_next_val(site_[length - 1], site_[0], site_[1]);
		}
		//right bound
		else if (i == length - 1) {
			site_tmp[i] = calc_next_val(site_[length - 2], site_[length - 1], site_[0]);
		}
		//mid
		else {
			site_tmp[i] = calc_next_val(site_[i - 1], site_[i], site_[i + 1]);
		}
	}
	//copy to site
	for (int i = 0; i < length; i++) {
		site_[i] = site_tmp[i];
	}
	
}

int main()
{
	// read parameters from input
	cout << "Length: ";
	cin >> length;
	cout << "Steps: ";
	cin >> steps;
	cout << "Rule: ";
	cin >> rule;

	// randomvalues
	srand(time(0));

	// world
	int * site = new int[length];
	// init
	initialize_world(site);
	for (int i = 0; i < steps; i++) {
		calc_next_state(site);
		write_world(site);
		show_world(site);
	}
	system("pause");
    return 0;
}

