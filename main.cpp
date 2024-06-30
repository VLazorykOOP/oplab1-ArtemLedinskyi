#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdarg>
#include <filesystem>
using namespace std;
namespace customException
{
class KToZero {};
class ToAlg2 {};
class ToAlg3 {};
}
using namespace customException;





string file1 = "dat1.dat";
string file2 = "dat2.dat";
string file3 = "dat3.dat";

namespace alg2 {
double T(double x)
{
    return atan(acos(sin(2 * x)));
}
double U(double x)
{
    return atan(acos(sin(3 * x)));
}
double Qqn(double x, double y, double z)
{
    return x / U(x) + y * T(y) - U(z) * T(z);
}
double Qnk(double x, double y)
{
    return 1.1 * Qqn(x, y, x + y) - 0.9 * Qqn(y, x, x - y);
}
double Rnk(double x, double y)
{
    return x * Qnk(x, y) + y * Qnk(y, x) - 0.03 * Qnk(x, y) * Qnk(y, x);
}
}

double Max(int num, ...) {
    va_list args;
    va_start(args, num);
    double max_val = va_arg(args, double);

    for (int i = 1; i < num; ++i) {
        double val = va_arg(args, double);
        if (val > max_val) {
            max_val = val;
        }
    }

    va_end(args);
    return max_val;
}

namespace alg1 {
double Y(double x)
{
    if (x * x > 100)
        throw KToZero();
    if (x * sqrt(100 - x * x) < 1)
        throw KToZero();
    return log(x * sqrt(100 - x * x));
}
double Yrr(double f, double r)
{
    return Y(f) * r + 0.5 * Y(r);
}
double Trr(double f, double r)
{
    if (4 * f * f - r < 0)
        throw KToZero();
    return sqrt(4 * f * f - r) + 0.5 * Yrr(r, f);
}
double Rrr(double f, double r, double k)
{
    return f * Trr(f, r) + r * Trr(f, 2 * k);
}
double GText(string text)
{
    fstream fs(file3);
    if (!fs){

        return cout << "unable to open file dat3.dat" << endl, 0;
    }
    string s;
    double value;
    while (!fs.eof())
    {
        fs >> s >> value;
        if (s == text){
            return value;
        }
    }
    return 0;
}
double CText(double x, string text) {
    if (text == ""){
        return GText("set") + GText("get") - x;
    }
    if (x > 0){
        return GText(text) + x;
    }
    return GText("set") + GText(text);
}
double RText(double x, double y, double z, string text)
{
    return CText(Max(4, x, y, x + z, y + z), text);
}
double T(double x)
{
    fstream fs(file2);
    if (!fs)throw ToAlg3();
    if (x < -10 || x > 10){
        throw ToAlg2();
    }
    double X, value;
    fs >> X >> value;
    while (X < x)
    {
        fs >> X >> value;
        if (X == x)return value;
    }
    double nX, nValue;
    fs >> nX >> nValue;
    return value + (nValue - value) * (x - X) / (nX - X);
}
double U(double x)
{
    fstream fs(file1);
    if (!fs){
        throw ToAlg2();
    }
    if (x < -5 || x > 5){
        throw ToAlg2();
    }
    double X, value;
    fs >> X >> value;
    while (X < x)
    {
        fs >> X >> value;
        if (X == x){
            return value;
        }
    }
    double nX, nValue;
    fs >> nX >> nValue;
    return value + (nValue - value) * (x - X) / (nX - X);
}
double Qqn(double x, double y, double z)
{
    return x / U(x) + y * T(y) - U(z) * T(z);
}
double Qnk(double x, double y)
{
    return Qqn(x, y, x + y) - Qqn(y, x, x - y);
}
double Rnk(double x, double y)
{
    try
    {
        return x * Qnk(x, y) + y * Qnk(y, x);
    }
    catch (ToAlg2)
    {
        cout << "switched to Alg 2" << endl;
        return alg2::Rnk(x, y);
    }
}
double Variant(double r, double k)
{
    return 0.8973 * r + 0.1027 * k;
}
}

namespace alg3 {
double T(double x)
{
    return atan(acos(sin(2 * x)));
}
double U(double x)
{
    return atan(acos(sin(3 * x)));
}
double Qqn(double x, double y, double )
{
    return x / U(x) + y * T(y) - 0.9 * U(x) * T(y);
}
double Qnk(double x, double y)
{
    return 1.3 * Qqn(x, y, x) - 0.7 * Qqn(y, x, x);
}
double func(double x, double y, double )
{
    return 1.75 * x * Qnk(x, y) + 1.25 * y * Qnk(y, x) - 1.5 * Qnk(x, y) * Qnk(y, x);
}
}




int main()
{

    cout << "Current working directory: " << filesystem::current_path() << endl;

    double x, y, z;
    string text="aet";
    x=1;
    y=1;
    z=1;
    cout<<"Text: "<<text<<"\nx: "<<x<<"\ny: "<<y<<"\nz: "<<z<<endl;
    double r = 0;
    double k = 0;

    try {
        r = alg1::Rnk(x, y) + alg1::Rnk(y, z) * alg1::Rnk(x, y);
    }
    catch (ToAlg3) {
        cout << "switched to Alg 3" << endl;
        r = alg3::func(x, y, z);
    }

    k = alg1::RText(x, y, z, text);
    double f = alg1::CText(x, text);
    try {
        k = alg1::Rrr(f, r, k);
    }
    catch (KToZero) {
        cout << "K is 0" << endl;
        k = 0;
    }

    double result = alg1::Variant(r, k);

    cout << "Variant(r, k) = " << result << endl;

    return 0;
}
