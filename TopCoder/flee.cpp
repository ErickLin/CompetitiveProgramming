#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Flee {
    public:
    	double dist(double x1, double y1, double x2, double y2) {
    		return sqrt((x2 - x1) * (x2 - x1)
    			+ (y2 - y1) * (y2 - y1));
    	}

    	double inside(double x1, double y1, double x2, double y2
    			, double x3, double y3, double x, double y) {
    		double alpha = ((y2 - y3)*(x - x3) + (x3 - x2)*(y - y3)) /
        			((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
			double beta = ((y3 - y1)*(x - x3) + (x1 - x3)*(y - y3)) /
			       ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
			double gamma = 1.0 - alpha - beta;
			return alpha > 0 && beta > 0 && gamma > 0;
    	}

    	double maximalSafetyLevel(vector<int> x, vector<int> y) {
    		if (x.size() == 1) {
    			return dist(0, 0, x[0], y[0]);
    		} else if (x.size() == 2) {
    			return min(dist(0, 0, x[0], y[0]), dist(0, 0, x[1], y[1]));
    		} else {
    			double ans = dist(0, 0, x[0], y[0]);
    			for (int i = 1; i < 3; i++) {
    				ans = min(ans, dist(0, 0, x[i], y[i]));
    			}
    			if (inside(x[0], y[0], x[1], y[1], x[2], y[2], 0, 0)) {
    				double ans2 = dist(x[0], y[0], x[1], y[1]) / 2.0;
    				ans2 = max(ans2, dist(x[1], y[1], x[2], y[2]) / 2.0);
    				ans2 = max(ans2, dist(x[0], y[0], x[2], y[2]) / 2.0);
    				ans = min(ans, ans2);
    			}
    			return ans;
    		}
    	}
};

int main() {
	Flee a;
	cout << a.maximalSafetyLevel({1,1,-7}, {5,-5,0}) << '\n';
	cout << a.maximalSafetyLevel({1,1}, {-5,-5}) << '\n';
	cout << a.maximalSafetyLevel({1,1,-8}, {5,-5,0}) << '\n';
	cout << setprecision(9) <<  a.maximalSafetyLevel({232,312,-432}, {498,-374,24}) << '\n';
	cout << a.maximalSafetyLevel({0}, {0}) << '\n';
}