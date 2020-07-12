#include <utility>
#include <cmath>

using namespace std;

struct Vect {
    double x, y;
    Vect() : x(0), y(0) {}
    Vect(double x, double y)  {
        this->y = y;
        this->x = x;
    }
    Vect(pair<double, double> a) : Vect(a.first, a.second) {}
    Vect(pair<double, double> a, pair<double, double> b) : Vect(b.first-a.first, b.second-a.second) {}

    Vect operator+(const Vect& target) {
        return Vect(x+target.x, y+target.y);
    }

    Vect operator-() {
        return Vect(-x, -y);
    }

    Vect operator-(const Vect& target) {
        return Vect(x-target.x, y-target.y);
    }

    double length() {
        return sqrt(x*x+y*y);
    }
};
