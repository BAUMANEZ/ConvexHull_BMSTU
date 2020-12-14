//
//  Data Structures.cpp
//  for testing reasons
//
//  Created by Арсений Токарев on 07.12.2020.
//

#ifndef DataStructures
#define DataStructures

#define FILE_COORDINATES_PATH "/Users/arsenytokarev/Desktop/ConvexHull_BMSTU/Helpers/Text files/coordinates.txt"

#define FILE_SAVE_PATH_BRUTE_FORCE "/Users/arsenytokarev/Desktop/ConvexHull_BMSTU/Helpers/Text files/ConvexHullPoints(MethodI).txt"

#define FILE_SAVE_PATH_KIRKPATRICK_SEIDEL "/Users/arsenytokarev/Desktop/ConvexHull_BMSTU/Helpers/Text files/ConvexHullPoints(MethodII).txt"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

enum Result { isEmpty, isFilled };
enum PointPosition { oneSide, otherSide, within };

struct Point {
	Point(double coordX = 0.0, double coordY = 0.0) {
		x = coordX;
		y = coordY;
	}
	
	double x;
	double y;
	
	bool operator== (const Point& coordinate) const {
		return (coordinate.x == this->x && coordinate.y == this->y);
	}
};

struct PointPair {
	PointPair(const Point firstPoint, const Point secondPoint) {
		first = firstPoint;
		second = secondPoint;
	}
	
	Point first;
	Point second;
};

struct HandleFiles {
	static void fillVectorWithPointsFromTxt(const string &filePath,
											vector<Point> &points) {
		size_t numberOfPoints = 0;
		ifstream file(filePath);
		if (file.is_open()) {
			file >> numberOfPoints;
			points.reserve(numberOfPoints);

			double xCoord, yCoord;
			while (file >> xCoord >> yCoord) {
				points.push_back(Point(xCoord, yCoord));
			}
			file.close();
		}
		
		if (points.empty()) {
			cout << "Could not find the file or read data from it\n";
			exit(-1);
		}
	}
	
	static void writeToFile(const string filePath,
							const vector<Point> &convexHullPoints) {
	  ofstream saveFile;
	  saveFile.open(filePath);
	  if (saveFile.is_open()) {
		  saveFile << convexHullPoints.size() << endl;
		  for (int i = 0; i < convexHullPoints.size(); ++i) {
			  saveFile << convexHullPoints.at(i).x << " " << convexHullPoints.at(i).y << endl;
		  }
	  } else {
		  cout << "Could not write points to file\n";
		  exit(-1);
	  }
  }
	
};


#endif
