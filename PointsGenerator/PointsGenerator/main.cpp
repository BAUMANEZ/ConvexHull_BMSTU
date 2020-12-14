#define FILE_WRITE_PATH "/Users/arsenytokarev/Desktop/ConvexHull_BMSTU/WolframVisualization/coordinates.txt"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


struct Point {

	double coordX;
	double coordY;

	bool operator== (Point coordinate) {
		return (coordinate.coordX == this->coordX && coordinate.coordY == this->coordY);
	}
};


template <typename T>
void checkIfInputIsCorrect(T &value,
						   const string &message) {
	while (cout << message << "\n>> " && !(cin >> value)) {
		cin.clear(); //clear bad input flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		cout << "Invalid input; press ENTER to try again.\n";
		cin.get();
	}
}

int main(int argc,
		 const char* argv[]) {
	ofstream writeToTxt;
	writeToTxt.open(FILE_WRITE_PATH);

	if (writeToTxt.is_open()) {
		bool isRandomFilling;
		checkIfInputIsCorrect(isRandomFilling, "Random(1) or Manual(0) filling?");

		vector<Point> coordinates;

		int numberOfPoints = 0;
		checkIfInputIsCorrect(numberOfPoints, "How many points do you need?");
		writeToTxt << numberOfPoints << endl;

		if (isRandomFilling) {
			for (int i = 0; i < numberOfPoints; ++i) {
				double coordX = ((double)(-1 + (rand() % 2) * 2)) * (double)rand() / RAND_MAX * 10000;
				double coordY = ((double)(-1 + (rand() % 2) * 2)) * (double)rand() / RAND_MAX * 10000;
				Point temporaryPoint = { coordX, coordY };
				while (find(coordinates.begin(), coordinates.end(), temporaryPoint) != coordinates.end()) {
					temporaryPoint.coordX = ((double)(-1 + (rand() % 2) * 2)) * (double)rand() / RAND_MAX * 10000;
					temporaryPoint.coordY = ((double)(-1 + (rand() % 2) * 2)) * (double)rand() / RAND_MAX * 10000;
				}
				coordinates.push_back(temporaryPoint);
				writeToTxt << temporaryPoint.coordX << " " << temporaryPoint.coordY << endl;
			}

			return 0;
		}

		for (int i = 0; i < numberOfPoints; ++i) {
			//Now I have no idea whether we have to make all these points unique. I am not going to handle
			//duplicates check in case a user chooses manual input of points.

			cout << "POINT" << i + 1 << endl;
			double coordX = 0.0, coordY = 0.0;
			checkIfInputIsCorrect(coordX, "Coordinate X");
			checkIfInputIsCorrect(coordY, "Coordinate Y");
			const Point temporaryPoint = { coordX, coordY };
			coordinates.push_back(temporaryPoint);
			writeToTxt << temporaryPoint.coordX << " " << temporaryPoint.coordY << endl;
			cout << "\n------------------\n\n";
		}
		return 0;
	}
}
