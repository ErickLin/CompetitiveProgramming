#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define PI 3.14159265359
struct point {
    double latitude, longitude;
};

double degree2radians(double angle) {
    return angle * PI / 180;
}

double distance_between(point point1, point point2) {
    const int EARTH_RADIUS = 6371;
    double point1_lat_in_radians  = degree2radians( point1.latitude );
    double point2_lat_in_radians  = degree2radians( point2.latitude );
    double point1_long_in_radians  = degree2radians( point1.longitude );
    double point2_long_in_radians  = degree2radians( point2.longitude );

    double ret = acos( sin( point1_lat_in_radians ) * sin( point2_lat_in_radians ) +
                 cos( point1_lat_in_radians ) * cos( point2_lat_in_radians ) *
                 cos( point2_long_in_radians - point1_long_in_radians) ) * EARTH_RADIUS;
    return round(ret * 100) / 100;
}

struct attraction {
    int id;
    point loc;
};

int main() {
    int n;
    cin >> n;
    vector<attraction> attractions(n);
    for (int i = 0; i < n; i++) {
        int id;
        double latitude, longitude;
        cin >> id >> latitude >> longitude;
        attractions[i].id = id;
        attractions[i].loc.latitude = latitude;
        attractions[i].loc.longitude = longitude;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        double latitude, longitude, maxTime;
        string transport;
        cin >> latitude >> longitude >> transport >> maxTime;
        int speed;
        if (transport == "metro") {
            speed = 20;
        } else if (transport == "bike") {
            speed = 15;
        } else {
            speed = 5;
        }
        double maxDist = speed * maxTime / 60.0;
        point loc;
        loc.latitude = latitude;
        loc.longitude = longitude;
        vector<attraction> canReach;
        for (int j = 0; j < n; j++) {
            double dist = distance_between(loc, attractions[j].loc);
            if (dist <= maxDist) {
                canReach.push_back(attractions[j]);
            }
        }
        sort(canReach.begin(), canReach.end(), [&loc](attraction a, attraction b) {
            double distA = distance_between(loc, a.loc);
            double distB = distance_between(loc, b.loc);
            if (distA == distB) {
                return a.id < b.id;
            }
            return distA < distB;
        });
        cout << canReach[0].id;
        for (int i = 1; i < canReach.size(); i++) {
            cout << ' ' << canReach[i].id;
        }
        cout << '\n';
    }
}
