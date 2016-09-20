#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

int main() {
    int p;
    cin >> p;
    while (p--) {
        int k;
        long double ax, ay, bx, by, cx, cy;
        cin >> k >> ax >> ay >> bx >> by >> cx >> cy;
        long double ab2 = (bx - ax) * (bx - ax) + (by - ay) * (by - ay), ab = sqrt(ab2);
        long double ac2 = (cx - ax) * (cx - ax) + (cy - ay) * (cy - ay), ac = sqrt(ac2);
        long double bc2 = (cx - bx) * (cx - bx) + (cy - by) * (cy - by), bc = sqrt(bc2);
        long double abc = acos((ab2 + bc2 - ac2) / (2.0 * ab * bc));
        long double acb = acos((ac2 + bc2 - ab2) / (2.0 * ac * bc));
        long double bac = acos((ab2 + ac2 - bc2) / (2.0 * ab * ac));
        long double lo = 0, hi = min(min(abc, acb), bac), theta = lo + (hi - lo) / 2.0, lhs, rhs;
        // Brocard condition (derived from Law of Sines): sin^3 theta = sin(abc - theta) sin(acb - theta) sin(bac - theta)
        while (abs((lhs = sin(theta) * sin(theta) * sin(theta)) - (rhs = sin(abc - theta) * sin(acb - theta) * sin(bac - theta))) > 0.0000000000001) {
            if (lhs < rhs) {
                lo = theta;
            } else {
                hi = theta;
            }
            theta = lo + (hi - lo) / 2.0;
        }
        //cout << abc*180/M_PI << ' ' << acb*180/M_PI << ' ' << bac*180/M_PI << ' ' << theta*180/M_PI << '\n';
        long double apSlope, cpSlope, bpSlope;
        if (bx != ax) {
            long double abSlope = (by - ay) / (bx - ax);
            apSlope = (abSlope + tan(theta)) / (1.0 - abSlope * tan(theta));
        } else {
            apSlope = -1.0 / tan(theta);
        }
        if (cx != ax) {
            long double acSlope = (cy - ay) / (cx - ax);
            cpSlope = (acSlope + tan(theta)) / (1.0 - acSlope * tan(theta));
        } else {
            cpSlope = -1.0 / tan(theta);
        }
        if (cx != bx) {
            long double bcSlope = (cy - by) / (cx - bx);
            bpSlope = (bcSlope + tan(theta)) / (1.0 - bcSlope * tan(theta));
        } else {
            bpSlope = -1.0 / tan(theta);
        }
        //cout << apSlope << ' ' << bpSlope << ' ' << cpSlope << '\n';
        // angle in terms of slopes of m_1 and m_2, counterclockwise: tan(theta) = (m_2 - m_1) / (1 + m_1 m_2)
        long double x = (by - ay + apSlope*ax - bpSlope*bx) / (apSlope - bpSlope);
        long double y = cpSlope * (x - cx) + cy;
        cout << setprecision(5) << fixed << k << ' ' << floor(x * 100000.0 + 0.5) / 100000.0 << ' ' << floor(y * 100000.0 + 0.5) / 100000.0 << '\n';
    }
    return 0;
}
