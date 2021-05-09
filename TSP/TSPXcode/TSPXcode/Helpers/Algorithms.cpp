//
//  2Opt.cpp
//  Travelling Salesman
//
//  Created by Арсений Токарев on 08.05.2021.
//

#define INPUT_FILE_PATH "/Users/arsenytokarev/Desktop/BMSTU_Practices/TSP/TSPXcode/TSPXcode/Helpers/TextFile.txt"

#include "Tour.cpp"
#include <float.h>

class TSPAlgorithm {
protected:
    virtual Tour giveBestTour(const Tour& initTour) { return {}; }
    
public:
    virtual void run() {
        auto tour = giveBestTour(Tour(INPUT_FILE_PATH));
//        for (auto& x: tour) {
//            std::cout << x << "  ";
//        }
        std::cout << std::endl;
        std::cout << tour.tripLength() << std::endl;
    }
};

class NNAlgorithm : public TSPAlgorithm {
    Tour giveBestTour(const Tour& initTour) {
        auto bestTour = initTour;
        for (size_t i = 0; i < bestTour.count() - 1; ++i) {
            double minRouteCost = DBL_MAX , nextRouteIndex = 0;
            for (size_t j = i + 1; j < bestTour.count(); ++j) {
                
                if (bestTour.distance(i,j) < minRouteCost )
                {
                    minRouteCost = bestTour.distance(i, j);
                    nextRouteIndex = j;
                }
                
            }
            bestTour.swap(i + 1, nextRouteIndex);
        }
        return bestTour;
    }
};

class TwoOptAlgorithm: public TSPAlgorithm {
    Tour giveBestTour(const Tour& initTour) override {
        bool isImproved;
        auto bestTour = initTour;
        do {
            isImproved = false;
            double bestDistance = bestTour.tripLength();
            for (size_t i = 1; i < bestTour.count() - 1; ++i) {
                for (size_t j = i + 1; j < bestTour.count(); ++j) {
                    auto newTour = bestTour.reversed(i, j);
                    const double newDistance = newTour.tripLength();
                    if (newDistance < bestDistance) {
                        isImproved = true;
                        bestTour = newTour;
                        bestDistance = newDistance;
                    }
                }
            }
        } while (isImproved);
        return bestTour;
    }
};
class ThreeOptAlgorithm: public TSPAlgorithm {
    Tour giveBestTour(const Tour& initTour) override {
        auto bestTour = initTour;
        double delta = 0;
        const size_t numberOfRoutes = bestTour.count();
        while (true) {
            for (size_t i = 0; i < numberOfRoutes; ++i) {
                for (size_t j = i + 2; j < numberOfRoutes; ++j) {
                    for (size_t k = j + 2; k < numberOfRoutes + 1; ++k) {
                        delta += reverseIfBetter(bestTour, i, j, k);
                        std::cout << i << "  " << j << "  " << k << std::endl;
                    }
                }
            }
            if (delta >= 0)
                break;
        }
        
        return bestTour;
    }
    
    double reverseIfBetter(Tour& tour, size_t i, size_t j, size_t k) {
        int A = tour[i - 1];
        int B = tour[i];
        int C = tour[j - 1];
        int D = tour[j];
        int E = tour[k - 1];
        int F = tour[k % tour.count()];
        
        double d0 = tour.distance(A, B) + tour.distance(C, D) + tour.distance(E, F);
        double d1 = tour.distance(A, C) + tour.distance(B, D) + tour.distance(E, F);
        double d2 = tour.distance(A, B) + tour.distance(C, E) + tour.distance(D, F);
        double d3 = tour.distance(A, D) + tour.distance(E, B) + tour.distance(C, F);
        double d4 = tour.distance(F, B) + tour.distance(C, D) + tour.distance(E, A);
        
        if(d0 > d1) {
            auto temp = tour.reversed(i, j);
            tour = temp;
            return -d0 + d1;
        }
        else if(d0 > d2) {
            auto temp = tour.reversed(j, k);
            tour = temp;
            return -d0 + d2;
        }
        else if(d0 > d4) {
            auto temp = tour.reversed(i, k);
            tour = temp;
            return -d0 + d4;
        }
        else if(d0 > d3) {
            NumericVector tmp;
            for(size_t z = j; z < k; ++z)
                tmp.push_back(tour[z]);
            for(size_t z = i; z < j; ++z)
                tmp.push_back(tour[z]);
            for(size_t f = i; f < k; ++f)
                tour.replace(f, tmp[f]);
            return -d0 + d3;
        }
        return 0;
    }
};
