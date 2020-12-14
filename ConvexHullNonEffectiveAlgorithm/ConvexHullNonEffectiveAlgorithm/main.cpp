//
//  main.cpp
//  for testing reasons
//
//  Created by Арсений Токарев on 15.10.2020.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "DataStructures.cpp"

using namespace std;

///Functions
Result fillVectorWithPointsFromTxt(const string &filePath,
								 vector<Point> &points);

size_t giveElementWithGreatestXIn(const vector<Point> &points);

PointPosition determinePointPosition(const Point& lineStartPoint,
									 const Point& lineEndPoint,
									 Point pointToCheck);

Result fill(vector<Point> &convexHullPoints,
		  const vector<Point> &allPoints);

void writeToFile(const string filePath,
				 const vector<Point> convexHullPoints);



int main(int argc, const char* argv[]) {
	vector<Point> points;
	const Result readingPointsResult = fillVectorWithPointsFromTxt(FILE_LOAD_PATH,
																   points);
	if (readingPointsResult == isEmpty) {
		cout << "Could not find the file or read data from it\n";
		return -1;
	}
	
	size_t indexOfElementWithMaxXCoord = giveElementWithGreatestXIn(points);
	swap(points.at(0), points.at(indexOfElementWithMaxXCoord));
	
	vector<Point> convexHullPoints;
	convexHullPoints.push_back(points.at(0));
	
	const Result fillingConvexHullPointsResult = fill(convexHullPoints, points);
	if (fillingConvexHullPointsResult == isEmpty) {
		cout << "Problem with filling CH Points array\n";
		return -2;
	}

	//writeToFile("/Users/arsenytokarev/Desktop/Vortex/Wolfram/Convex Hull Points (Method I).txt", points);
	ofstream saveFile;
	saveFile.open(FILE_SAVE_PATH_FIRST);
	if (saveFile.is_open()) {
		saveFile << convexHullPoints.size() << endl;
		for (int i = 0; i < convexHullPoints.size(); ++i) {
			saveFile << convexHullPoints.at(i).x << " " << convexHullPoints.at(i).y << endl;
		}
	}
	return 0;
}

Result fillVectorWithPointsFromTxt(const string &filePath,
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
	return points.empty() ? isEmpty : isFilled;
}

size_t giveElementWithGreatestXIn(const vector<Point> &points) {
	size_t indexOfElementWithMaxXCoord = 0;
	for (int i = 1; i < points.size() - 1; ++i) {
		if (points.at(i).x > points.at(indexOfElementWithMaxXCoord).x) {
			indexOfElementWithMaxXCoord = i;
		}
	}
	return indexOfElementWithMaxXCoord;
}

PointPosition determinePointPosition(const Point& lineStartPoint,
									 const Point& lineEndPoint,
									 Point pointToCheck) {
	const double result = (pointToCheck.x - lineStartPoint.x) * (lineEndPoint.y - lineStartPoint.y) - (pointToCheck.y - lineStartPoint.y) * (lineEndPoint.x - lineStartPoint.x);

	PointPosition positionFromTheLine;
	if (result < 0) {
		positionFromTheLine = oneSide;
	}
	else if (result > 0) {
		positionFromTheLine = otherSide;
	}
	else {
		positionFromTheLine = within;
	}

	return positionFromTheLine;
}

Result fill(vector<Point> &convexHullPoints,
			const vector<Point> &allPoints) {
	if (allPoints.empty() || convexHullPoints.empty()) {
		return isEmpty;
	}
	
	Point formerPoint = convexHullPoints.back();
	for (int i = 1; i < allPoints.size(); ++i) {
		const Point latterPoint = allPoints.at(i); // A candidate to be the next point of the Convex Hull

		bool areOnTheSameSide = true;
		int indexInAllPoints = 0;
		PointPosition comparator = within;
		/*
				First iteration: find the first non "within the line" point.
				Second iteration: compare remaining points with this comparator.
		*/
		for (; indexInAllPoints < allPoints.size(); ++indexInAllPoints) {
			comparator = determinePointPosition(formerPoint,
												latterPoint,
												allPoints.at(indexInAllPoints));
			if (comparator != within) {
				++indexInAllPoints;
				break;
			}
		}

		for (; indexInAllPoints < allPoints.size(); ++indexInAllPoints) {
			PointPosition currentPointPosition =
				determinePointPosition(formerPoint,
									   latterPoint,
									   allPoints.at(indexInAllPoints));

			// If a point lays within a line we can skip it, because it conforms to our condition that all points should be on the side side from the line

			// If the point is on the other side from the line we break a cycle and go to the next candidate
			if ((currentPointPosition != comparator) && (currentPointPosition != within)) {
				areOnTheSameSide = false;
				break;
			}
		}

		// If all points are on the side side from the line, current candidate is a point of the Convex Hull. That's why we add it to our array of the CH Points
		if (areOnTheSameSide) {
			//if the element already forms a convexHull we skip the iteration
			if (find_if(convexHullPoints.begin(),
						convexHullPoints.end(),
						[latterPoint](const Point& pointOfConvexHull) {
							return latterPoint == pointOfConvexHull;
						}) != convexHullPoints.end()) {
				continue;
			}
			convexHullPoints.push_back(latterPoint);
			formerPoint = latterPoint;
			i = 0;
		}
	}
	return isFilled;
}

void writeToFile(const string filePath,
				 const vector<Point> &convexHullPoints) {
	ofstream saveFile;
	saveFile.open(filePath);
	if (saveFile.is_open()) {
		saveFile << convexHullPoints.size() << endl;
		for (int i = 0; i < convexHullPoints.size(); ++i) {
			saveFile << convexHullPoints.at(i).x << " " << convexHullPoints.at(i).y << endl;
		}
	}
}
