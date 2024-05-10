#include <iostream>
#include <fstream>
#include "map.h"
using namespace std;

void map::genMap() {
	mapf.open("map.txt", ios::out | ios::trunc);
	for (int i = 0; i < 40; i++) {
		mapf << 'x';
	};
	mapf << endl;
	for (int i = 0; i < 22; i++) {
		mapf << 'x';
		for (int i = 0; i < 38; i++) {
			num = rand() % 2;
			mapf << m[num];
		};
		mapf << 'x'<<endl;
	};
	for (int i = 0; i < 40; i++) {
		mapf << 'x';
	};
	// Close the file
	mapf.close();
}
	
