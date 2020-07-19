/**
 * Created by Tekiter
 * 
 * 분수 자료구조 클래스
 * 항상 기약분수 형태로 취급한다
 *
 */

template <class T>
class Fraction {
    T numerator;
    T denominator;

    T gcd(T a, T b) {
        if (b == 0) {
            return a;
        }
        return gcd(b, a%b);
    }

    T lcm(T a, T b) {
        return a / gcd(a, b) * b;
    }

    Fraction<T> minify() {
        if (numerator == 0) {
            denominator = 1;
            return *this;
        }

        if (denominator < 0) {
            denominator = -denominator;
            numerator = -numerator;
        }
        T g = gcd(abs(numerator), denominator);
        numerator /= g;
        denominator /= g;
        return *this;
    }

    public:

    Fraction() : numerator(1), denominator(1) {}
    Fraction(T n) : numerator(n), denominator(1) {}
    Fraction(T n, T d) : numerator(n), denominator(d) {
        minify();
    }

    T denom() {
        return denominator;
    }

    T numer() {
        return numerator;
    }

    bool operator==(const Fraction<T> &rhs) {
        return numerator == rhs.numerator && denominator == rhs.denominator;
    }

    bool operator==(const T rhs) {
        return (rhs == 0 && numerator == 0) || (denominator == 1 && numerator == rhs);
    }

    Fraction<T> operator+(const Fraction<T> &rhs) {
        T newd = lcm(denominator, rhs.denominator);
        return Fraction<T>(numerator*(newd/denominator) + rhs.numerator*(newd/rhs.denominator), newd);
    }

    Fraction<T> operator-(const Fraction<T> &rhs) {
        T newd = lcm(denominator, rhs.denominator);
        return Fraction<T>(numerator*(newd/denominator) - rhs.numerator*(newd/rhs.denominator), newd);
    }

    Fraction<T> operator*(const Fraction<T> &rhs) {
        return Fraction<T>(numerator * rhs.numerator, denominator * rhs.denominator);
    }

    Fraction<T> operator/(const Fraction<T> &rhs) {
        return Fraction<T>(numerator * rhs.denominator, denominator * rhs.numerator);
    }

    Fraction<T> reverse() {
        return Fraction<T>(denominator, numerator);
    }

    pair<T, Fraction<T> > split() {
        if (denominator == 1) {
            return {numerator, Fraction<T>(0)};
        }
        if (numerator < 0) {
            T inte = -numerator / denominator;
            inte++;
            auto left = Fraction<T>(1) - Fraction<T>(-numerator % denominator, denominator);
            return {-inte, left};
        }

        T inte = numerator / denominator;
        Fraction<T> left(numerator % denominator, denominator);
        return {inte, left};
    }
};