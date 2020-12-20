//
//  main.cpp
//  Kirkpatrick-Seidel
//
//  Created by Арсений Токарев on 14.12.2020.
//
#include "../Kirkpatrick-Seidel/Kirkpatrick-Seidel Algorithm.cpp"
#include "../NonEffectiveAlgorithm/NonEffectiveAlgorithm.cpp"
#include "../Helpers/PointsGenerator.cpp"

int main(int argc, const char *argv[]) {
//	PointsGenerator::generatePoints();
	NonEffectiveAlgorithm().run();
	KirkpatrickSeidelAlgorithm().run();
	return 0;
}

