//g++ -std=c++11 array.cpp -o arraytest

#include <iostream>
#include <math.h>
#include <vector>
#include <chrono>
using namespace std;

#define WIDTH	800
#define LENGTH	600

float fastInvSqrt(float x);

int main()
{
	/*
	int rows[5];
	
	cout << rows.size();
	
	while(1);
	*/
	
	vector<int> test(LENGTH*WIDTH, 2);
	
	// choose some indices to signify point values
	
	int x, currentX, currentY;
		
	auto start = chrono::high_resolution_clock::now();
	
	for(x = 0; x < test.size(); x++){
		
		
	}
	
	auto end = chrono::high_resolution_clock::now();
	
	chrono::duration<double> elapsed = end - start;
	
	cout << "done in " << elapsed.count() << " seconds";	
	
	while(1);
}

float fastInvSqrt(float x) {
	union {
		float f;
		uint32_t i;
	} conv;
	
	float x2;
	const float threehalfs = 1.5F;
	
	x2 = x * 0.5F;
	conv.f = x;
	conv.i = 0x5f3759df - (conv.i >> 1);
	conv.f = conv.f * (threehalfs - (x2 * conv.f * conv.f));
	return conv.f;
}