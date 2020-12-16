//
//  MyAlgorithm.cpp
//  Kirkpatrick-Seidel
//
//  Created by Арсений Токарев on 15.12.2020.
//
#include "/Users/arsenytokarev/Desktop/ConvexHull_BMSTU/DataStructures/DataStructures.cpp"
#include <type_traits>
#include <tuple>

#define EPS 0.000001

using namespace std;

class KirkpatrickSeidelAlgorithm {
private:
	vector<Point> points;
	vector<Point> convexHullPoints;
	
	template<
		typename T,
		typename = typename enable_if<is_arithmetic<T>::value, T>::type
	>
	double getMedianIn(vector<T> values) {
		sort(values.begin(), values.end());
		const size_t numberOfValues = values.size();
		switch (numberOfValues % 2) {
			case 0:
				{
					double sumOfValues = 0;
					for (auto &value : values) sumOfValues += value;
					return sumOfValues / 2;
				}
			default:
				return values.at(numberOfValues / 2);
		}
	}
	
	vector<PointPair> makePointPairs(const vector<Point> &setOfPoints,
									 vector<Point> &candidates) {
		
		vector<PointPair> pointPairs {};
		size_t startIndex = 0;
		if (setOfPoints.size() % 2 != 0) {
			candidates.push_back(*(setOfPoints.begin()));
			startIndex = 1;
		}
		for (auto iterator = setOfPoints.begin() + startIndex;
			 iterator < setOfPoints.end();
			 iterator += 2) {
			pointPairs.push_back(PointPair(*iterator,
										   *(iterator + 1)));
		}
		
		return pointPairs;
	}
	
	
	tuple<vector<PointPair>, vector<PointPair>, vector<PointPair>> getSlopeCharacterPairs(const vector<double> &slopes,
																						  const vector<PointPair> pointPairs,
																						  const double medianSlope) {
		if (slopes.size() != pointPairs.size()) exit(-4);
		vector<PointPair> smallPairs {}, equalPairs {}, largePairs {};
		for (int i = 0; i < pointPairs.size(); ++i) {
			const double slope = slopes.at(i);
			const PointPair pointPair = pointPairs.at(i);
			if (slope < medianSlope) {
				smallPairs.push_back(pointPair);
			}
			else if (slope > medianSlope) {
				largePairs.push_back(pointPair);
			}
			else if (abs(slope - medianSlope) < EPS){
				equalPairs.push_back(pointPair);
			}
		}
		return make_tuple(smallPairs, equalPairs, largePairs);
	}
	
	vector<double> calculateSlopes(vector<PointPair> &pointPairs,
								   vector<Point> &candidates) {
		vector<double> slopes {};
		for (auto iterator = pointPairs.begin();
			 iterator < pointPairs.end();
			 ++iterator) {
			const auto pair = *iterator;
			if (pair.first.x == pair.second.x) {
				candidates.push_back(pair.first.y > pair.second.y ? pair.first : pair.second);
				pointPairs.erase(iterator);
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
		const size_t setCapacity = setOfPoints.size();
		
		if (setCapacity == 2) {
			return PointPair(setOfPoints.at(0),
							 setOfPoints.at(1));
		}
		
		vector<PointPair> pointPairs = makePointPairs(setOfPoints, candidates);
		
		
		const auto slopes = calculateSlopes(pointPairs,
											candidates);
		const double medianSlope = getMedianIn(slopes);
		
		// C++17 and higher!!!
		const auto [smallPairs, equalPairs, largePairs] = getSlopeCharacterPairs(slopes,
																				 pointPairs,
																				 medianSlope);
		
		double h = INT_MIN;
		for(auto iterator = points.begin();
			iterator < points.end();
			++iterator) {
			const Point currentPoint = *iterator;
			const double currentH = (currentPoint.y - medianSlope * currentPoint.x);
			if (currentH > h)
				h = currentH;
		 }
		
		Point maximizingMin = Point(INT_MAX, INT_MAX), maximizingMax = Point(INT_MIN, INT_MIN);
		for(auto iterator = points.begin();
			iterator < points.end();
			++iterator) {
			const Point currentPoint = *iterator;
			const double currentH = (currentPoint.y - medianSlope * currentPoint.x);
			if (abs(currentH - h) < EPS) {
				if (currentPoint.x < maximizingMin.x)
					maximizingMin = currentPoint;
				
				if (currentPoint.x > maximizingMax.x)
					maximizingMax = currentPoint;
			}
		}
		
		const PointPair maximizingPointPair = PointPair(maximizingMin, maximizingMax); 
		
		if (maximizingPointPair.first.x <= medianX && maximizingPointPair.second.x > medianX) {
			return maximizingPointPair;
		}
		
		if (maximizingPointPair.second.x <= medianX) {
			vector<PointPair> largeAndEqualPairs;
			largeAndEqualPairs.reserve(largePairs.size() + equalPairs.size());
			largeAndEqualPairs.insert(largeAndEqualPairs.end(),
									  largePairs.begin(),
									  largePairs.end());
			largeAndEqualPairs.insert(largeAndEqualPairs.end(),
									  equalPairs.begin(),
									  equalPairs.end());
			
			for (auto &pointPair : largeAndEqualPairs) candidates.push_back(pointPair.second);
			for (auto &pointPair : smallPairs) {
				candidates.push_back(pointPair.first);
				candidates.push_back(pointPair.second);
			}
		}
		
		if (maximizingPointPair.first.x > medianX) {
			vector<PointPair> smallAndEqualPairs;
			smallAndEqualPairs.reserve(smallPairs.size() + equalPairs.size());
			smallAndEqualPairs.insert(smallAndEqualPairs.end(),
									  smallPairs.begin(),
									  smallPairs.end());
			smallAndEqualPairs.insert(smallAndEqualPairs.end(),
									  equalPairs.begin(),
									  equalPairs.end());
			
			for (auto &pointPair : smallAndEqualPairs) candidates.push_back(pointPair.first);
			for (auto &pointPair : largePairs) {
				candidates.push_back(pointPair.first);
				candidates.push_back(pointPair.second);
			}
		}
		sort(candidates.begin(),
			 candidates.end(),
			 [](const Point a, const Point b) {
					return a.x < b.x;
			 }
		);
		
		return getUpperBridge(candidates, medianX);
	}
	
	vector<double> getXCoordinates() {
		vector<double> result(points.size());
		for (auto &point : points) result.push_back(point.x);
		return result;
	}
	
	void formConvexHull(const vector<Point> &setOfPoints) {
		const double medianX = getMedianIn(getXCoordinates());
		const auto upperBridge = getUpperBridge(points, medianX);
		vector<Point> leftSetOfPoints {upperBridge.first};
		for (auto &point : points) {
			if (point.x < upperBridge.first.x) leftSetOfPoints.push_back(point);
		}
		
		vector<Point> rightSetOfPoints {upperBridge.second};
		for (auto &point : points) {
			if (point.x > upperBridge.first.x) leftSetOfPoints.push_back(point);
		}
		
		if (upperBridge.first == *points.begin()) {
			convexHullPoints.push_back(upperBridge.first);
		} else {
			formConvexHull(leftSetOfPoints);
		}
		
		if (upperBridge.second == *(points.end() - 1)) {
			convexHullPoints.push_back(upperBridge.second);
		} else {
			formConvexHull(rightSetOfPoints);
		}
		
	}
	
	void saveToTxt() {
		HandleFiles::writeToFile(FILE_SAVE_PATH_KIRKPATRICK_SEIDEL,
								 convexHullPoints);
	}
	
public:
	void run() {
		formConvexHull(points);
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
