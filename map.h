#pragma once
#include <fstream>
#include <iostream>
using namespace std;

class map {
	ofstream mapf;
	int num;
	char m[2] = { '.','x' };
public:
	void genMap();
};