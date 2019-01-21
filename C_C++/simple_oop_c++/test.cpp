#include "test.h"
#include "test.h"

Car::Car(string colorName, string brandName, string modelName)
{
	Car::colorName = colorName;
	Car::brandName = brandName;
	Car::modelName = modelName;
}

string Car::getColorName()
{
	return Car::colorName;
}

string Car::getBrandName()
{
	return Car::brandName;
}

string Car::getModelName()
{
	return Car::modelName;
}

void Car::setColorName(string colorName)
{
	Car::colorName = colorName;
}

void Car::setBrandName(string brandName)
{
	Car::brandName = brandName;
}

void Car::setModelName(string modelName)
{
	Car::modelName = modelName;
}

int main(void)
{
	// Create a Car obj
	Car car1 ("Red", "BMW", "Z3");

	// Get info from method getModelName
	cout << car1.getModelName() << endl;

	return 0;
}
