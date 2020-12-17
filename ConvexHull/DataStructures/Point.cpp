//
//  Point.cpp
//  ConvexHull
//
//  Created by Арсений Токарев on 17.12.2020.
//

#ifndef PointFile
#define PointFile

struct Point {
	double x;
	double y;
	
	bool operator== (const Point& coordinate) const {
		return (coordinate.x == this->x && coordinate.y == this->y);
	}
	
	Point(double coordX = 0.0, double coordY = 0.0) {
		x = coordX;
		y = coordY;
	}
};

#endif
