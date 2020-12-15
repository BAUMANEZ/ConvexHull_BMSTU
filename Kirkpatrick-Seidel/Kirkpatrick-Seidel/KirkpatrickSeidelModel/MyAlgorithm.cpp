//
//  MyAlgorithm.cpp
//  Kirkpatrick-Seidel
//
//  Created by Арсений Токарев on 15.12.2020.
//
#include "/Users/arsenytokarev/Desktop/ConvexHull_BMSTU/DataStructures/DataStructures.cpp"

using namespace std;

class KirkpatrickSeidelAlgorithm {
private:
	vector<Point> points;
	vector<Point> convexHullPoints;
	
	double getMedianX() {
		const size_t numberOfPoints = points.size();
		switch (numberOfPoints % 2) {
			case 0:
				{
					double sumOfXCoordinates = 0;
					for (auto &point : points) sumOfXCoordinates += point.x;
					return sumOfXCoordinates / 2;
				}
			default:
				return points.at(numberOfPoints / 2).x;
		}
	}
	
	vector<PointPair> getVectorOfPointPairsFrom(const vector<Point> &setOfPoints) {
		vector<PointPair> pointPairs {};
		if (setOfPoints.size() < 2) {
			return {};
		}
		
		for (auto iterator = setOfPoints.begin();
			 iterator < setOfPoints.end() - 1;
			 ++iterator) {
			pointPairs.push_back(PointPair(*iterator,
										   *(iterator + 1)));
		}
		
		return pointPairs;
	}
	
	vector<double> calculateSlopes(vector<PointPair> &pointPairs,
															vector<Point> &candidates) {
		vector<double> slopes;
		for (auto iterator = pointPairs.begin();
			 iterator < pointPairs.end();
			 ++iterator) {
			const auto pair = *iterator;
			if (pair.first.x == pair.second.x) {
				pointPairs.erase(iterator);
				candidates.push_back(pair.first.y > pair.second.y ? pair.first : pair.second);
			} else {
				const double slope = (pair.first.y - pair.second.y) / (pair.first.x - pair.second.x);
				slopes.push_back(slope);
			}
		}
		return slopes;
	}
	
	PointPair getUpperBridge(const vector<Point> &setOfPoints,
						  double medianX) {
		vector<Point> candidates {};
		const double setCapacity = setOfPoints.size();
		
		if (setCapacity == 2) {
			return PointPair(setOfPoints.at(0),
							 setOfPoints.at(1));
		}
		
		/*
			 My first idea was to use map (aka dictionary in some other PLs).
			 However, considering that size of pointPairs is equal to size of
			 slopes std::map can be omitted
		*/
		vector<PointPair> pointPairs = getVectorOfPointPairsFrom(setOfPoints);
		vector<double> slopes = calculateSlopes(pointPairs,
												candidates);
		if (pointPairs.size() != slopes.size()) exit(-1);
		
		
		
		return getUpperBridge(candidates, medianX);
	}
	
	void formConvexHull() {
		const double medianX = getMedianX();
		getUpperBridge(points, medianX);
		
	}
	
	void saveToTxt() {
		HandleFiles::writeToFile(FILE_SAVE_PATH_KIRKPATRICK_SEIDEL,
								 convexHullPoints);
	}
	
public:
	void run() {
		formConvexHull();
		saveToTxt();
	}
	
	KirkpatrickSeidelAlgorithm(const string &filePath = FILE_COORDINATES_PATH) {
		HandleFiles::fillVectorWithPointsFromTxt(filePath,
												 points);
		sort(this->points.begin(),
			 this->points.end(),
			 [](const Point a, const Point b) {
					return a.x < b.x;
			 }
		);
		convexHullPoints = {};
	}

};
