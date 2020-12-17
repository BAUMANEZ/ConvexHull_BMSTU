//
//  main.cpp
//  Kirkpatrick-Seidel
//
//  Created by Арсений Токарев on 14.12.2020.
//
#include "../Kirkpatrick-Seidel/Kirkpatrick-Seidel Algorithm.cpp"
#include "../NonEffectiveAlgorithm/NonEffectiveAlgorithm.cpp"

int main(int argc, const char *argv[]) {
	NonEffectiveAlgorithm().run();
	KirkpatrickSeidelAlgorithm().run();
	return 0;
}

