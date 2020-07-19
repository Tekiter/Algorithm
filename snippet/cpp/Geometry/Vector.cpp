/**
 * Created by Tekiter
 * 
 * 수학에서의 벡터를 표현하는 클래스이다.
 * 기하 문제에서 사용한다. 
 * 
 */


#include <utility>
#include <cmath>

using namespace std;

constexpr double PI() { return acos(0.0) * 2.0; };

class Vect {

    public:
    
    double x, y;
    Vect() : x(0), y(0) {}
    Vect(double x, double y)  {
        this->y = y;
        this->x = x;
    }
    Vect(pair<double, double> a) : Vect(a.first, a.second) {}
    Vect(pair<double, double> a, pair<double, double> b) : Vect(b.first-a.first, b.second-a.second) {}

    bool operator==(const Vect& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator<(const Vect& rhs) const {
        if (x == rhs.x) {
            return y < rhs.y;
        }
        return x < rhs.x;
    }

    Vect operator+(const Vect& rhs) const {
        return Vect(x+rhs.x, y+rhs.y);
    }

    Vect operator-() const {
        return Vect(-x, -y);
    }

    Vect operator-(const Vect& rhs) const {
        return Vect(x-rhs.x, y-rhs.y);
    }

    

    Vect operator*(double rhs) {
        return Vect(x*rhs, y*rhs);
    }

    double length() const {
        return sqrt(x*x+y*y);
    }

    double dot(const Vect& rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    double cross(const Vect& rhs) const {
        return x * rhs.y - y * rhs.x;
    }

    double polarAngle() const {
        return fmod(atan2(y, x) + 2*PI(), 2*PI());
    }
};

