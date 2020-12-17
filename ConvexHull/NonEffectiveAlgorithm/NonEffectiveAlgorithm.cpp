//
//  NonEffectiveAlgorithm.cpp
//  ConvexHull
//
//  Created by Арсений Токарев on 17.12.2020.
//

#include "../DataStructures/DataModule.cpp"

struct NonEffectiveAlgorithm {
private:
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

	void fill(vector<Point> &convexHullPoints,
				const vector<Point> &allPoints) {
		if (allPoints.empty() || convexHullPoints.empty()) {
			cout << "There are no points to form a convex hull!\n";
			exit(-2);
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
	}
public:
	void run() {
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
	}
};
