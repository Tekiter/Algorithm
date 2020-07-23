/**
 * Created by Tekiter
 * 
 * 수학에서의 벡터를 표현하는 클래스이다.
 * 기하 문제에서 사용한다. 
 * 
 */


#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

constexpr double PI() { return acos(0.0) * 2.0; };

template <class T>
class VectBase {

    bool valueEquals(double a, double b) const {
        double d = abs(a-b);
        if (d < 1e-10) {
            return true;
        }
        return d <= 1e-8 * max(abs(a), abs(b));
    }

    bool valueEquals(T a, T b) const {
        return a == b;
    }

    public:
    
    T x, y;
    VectBase() : x(0), y(0) {}
    VectBase(T x, T y)  {
        this->y = y;
        this->x = x;
    }
    VectBase(pair<T, T> a) : VectBase(a.first, a.second) {}
    VectBase(pair<T, T> a, pair<T, T> b) : VectBase(b.first-a.first, b.second-a.second) {}

    bool operator==(const VectBase& rhs) const {
        return valueEquals(x, rhs.x) && valueEquals(y, rhs.y);
    }

    bool operator<(const VectBase& rhs) const {
        if (valueEquals(x, rhs.x)) {
            if (valueEquals(y, rhs.y)) {
                return false;
            }
            return y < rhs.y;
        }
        return x < rhs.x;
    }

    bool operator>(const VectBase& rhs) const  {
        if (valueEquals(x, rhs.x)) {
            if (valueEquals(y, rhs.y)) {
                return false;
            }
            return y > rhs.y;
        }
        return x > rhs.x;
    }

    VectBase operator+(const VectBase& rhs) const {
        return VectBase(x+rhs.x, y+rhs.y);
    }

    VectBase operator-() const {
        return VectBase(-x, -y);
    }

    VectBase operator-(const VectBase& rhs) const {
        return VectBase(x-rhs.x, y-rhs.y);
    }

    

    VectBase operator*(T rhs) {
        return VectBase(x*rhs, y*rhs);
    }

    double length() const {
        return sqrt(x*x+y*y);
    }

    double length2() const {
        return x*x + y*y;
    }

    VectBase normalize() const {
        return VectBase(x / length(), y / length());
    }

    T dot(const VectBase& rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    T cross(const VectBase& rhs) const {
        return x * rhs.y - y * rhs.x;
    }

    double polarAngle() const {
        return fmod(atan2(y, x) + 2*PI(), 2*PI());
    }
};

