//
//  main.cpp
//  for testing reasons
//
//  Created by Арсений Токарев on 15.10.2020.
//

#include <algorithm>
#include "/Users/arsenytokarev/Desktop/ConvexHull_BMSTU/DataStructures/DataStructures.cpp"

using namespace std;

size_t giveElementWithGreatestXIn(const vector<Point> &points);

PointPosition determinePointPosition(const Point& lineStartPoint,
									 const Point& lineEndPoint,
									 Point pointToCheck);

void fill(vector<Point> &convexHullPoints,
		  const vector<Point> &allPoints);

void writeToFile(const string filePath,
				 const vector<Point> convexHullPoints);



int main(int argc, const char* argv[]) {
	vector<Point> points;
	
	/*  LOAD POINTS FROM FILE  */
	HandleFiles::fillVectorWithPointsFromTxt(FILE_COORDINATES_PATH,
											 points);
	
	/*  FIND CONVEX HULL  */
	size_t indexOfElementWithMaxXCoord = giveElementWithGreatestXIn(points);
	swap(points.at(0), points.at(indexOfElementWithMaxXCoord));
	vector<Point> convexHullPoints;
	convexHullPoints.push_back(points.at(0));
	fill(convexHullPoints, points);
	
	/* WRITE CH POINTS TO TXT  */
	HandleFiles::writeToFile(FILE_SAVE_PATH_BRUTE_FORCE,
							 convexHullPoints);
	return 0;
}
