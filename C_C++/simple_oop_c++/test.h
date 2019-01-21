// Header guard
#ifndef TEST_H
#define TEST_H

#include <iostream>
using namespace std;

// Contents
class Car
{
private:
	string colorName;
	string brandName;
	string modelName;

public:
	Car(string colorName, string brandName, string modelName);

	string getColorName();
	void setColorName(string colorName);

	string getBrandName();
	void setBrandName(string brandName);

	string getModelName();
	void setModelName(string modelName);
};

// Header guard end
#endif
