#include "TestExtins.h"
#include "TestScurt.h"


#include <iostream>
using namespace std;


int main() {

	cout << "Running short tests... \n";	

	testAll();

	cout << "Done\nRunning extended tests... \n";	

	testAllExtins();

	cout << "That's all!" << endl;
	return 0;
}

