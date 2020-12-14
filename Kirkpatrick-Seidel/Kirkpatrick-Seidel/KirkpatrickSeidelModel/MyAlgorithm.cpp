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
	vector<Point> getConvexHullFrom(const vector<Point> &inputPoints) {
		
		return {};
	}
	
private:
	vector<Point> points;

public:
	KirkpatrickSeidelAlgorithm(const vector<Point> points = vector<Point>()) {
		this->points = points;
		sort(this->points.begin(),
			 this->points.end(),
			 [](const Point a, const Point b) {
					return a.x < b.x;
			 }
		);
	}
};
