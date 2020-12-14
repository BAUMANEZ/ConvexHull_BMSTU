//
//  main.cpp
//  Kirkpatrick-Seidel
//
//  Created by Арсений Токарев on 14.12.2020.
//

#include "KirkpatrickSeidelModel/MyAlgorithm.cpp"

int main(int argc, const char *argv[]) {
	KirkpatrickSeidelAlgorithm result = {};
	result.formConvexHull();
	result.saveToTxt();
	return 0;
}
