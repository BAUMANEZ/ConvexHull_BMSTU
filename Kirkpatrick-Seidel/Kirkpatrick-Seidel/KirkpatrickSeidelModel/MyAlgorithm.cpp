//
//  MyAlgorithm.cpp
//  Kirkpatrick-Seidel
//
//  Created by Арсений Токарев on 15.12.2020.
//

#include<iostream>
#include<algorithm>
#include<climits>
#include <vector>
#include "/Users/arsenytokarev/Desktop/ConvexHull_BMSTU/DataStructures/DataStructures.cpp"

using namespace std;

struct KirkpatrickSeidelAlgorithm {

private:
	double getXMedian() {
		const size_t middlePointIndex = points.size() / 2;
		return points.at(middlePointIndex).x;
	}
	
public:
	vector<Point> formConvexHull() {
		
		return {};
	}
	
	void saveToTxt() {
		HandleFiles::writeToFile(FILE_SAVE_PATH_KIRKPATRICK_SEIDEL,
								 convexHullPoints);
	}
	
private:
	vector<Point> points;
	vector<Point> convexHullPoints;

public:
	KirkpatrickSeidelAlgorithm() {
		HandleFiles::fillVectorWithPointsFromTxt(FILE_COORDINATES_PATH,
												 points);
		sort(this->points.begin(),
			 this->points.end(),
			 [](const Point a, const Point b) {
					return a.x < b.x;
			 }
		);
		convexHull = {};
	}
};
