//
//  Data Structures.cpp
//  for testing reasons
//
//  Created by Арсений Токарев on 07.12.2020.
//

#ifndef DataStructures
#define DataStructures

#define FILE_LOAD_PATH "/Users/arsenytokarev/Desktop/ConvexHull_BMSTU/Helpers/Text files/coordinates.txt"
#define FILE_SAVE_PATH_BRUTE_FORCE "/Users/arsenytokarev/Desktop/ConvexHull_BMSTU/Helpers/Text files/ConvexHullPoints(MethodI).txt"
#define FILE_SAVE_PATH_KIRKPATRICK_SEIDEL "/Users/arsenytokarev/Desktop/ConvexHull_BMSTU/Helpers/Text files/ConvexHullPoints(MethodII).txt"

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
	PointPair(Point firstPoint, Point secondPoint) {
		first = firstPoint;
		second = secondPoint;
	}
	
	Point first;
	Point second;
};


#endif
