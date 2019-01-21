#include <iostream>
#include <string.h>

using namespace std;

main(void)
{
	string s = "geeksforgeeks";
	// must be constant
	const char* test;

	// c_str: convert the C++-style string to a C-style string
	test = s.c_str();

	// strlen: length for C-style strings
	for (int i = 0; i < strlen(test); i++)
		cout << test[i] << endl;

	return 0;
}
