// =====================================================================================
// Test.cpp
// =====================================================================================

#include <iostream>

//class Calculator
//{
//public:
//    static int add(int x, int y) { return x + y; }
//    static int sub(int x, int y) { return x - y; }
//    static int mul(int x, int y) { return x * y; }
//    static int div(int x, int y) { return x / y; }
//};
//
//class DoubleCalculator
//{
//public:
//    static double add(double x, double y) { return x + y; }
//    static double sub(double x, double y) { return x - y; }
//    static double mul(double x, double y) { return x * y; }
//    static double div(double x, double y) { return x / y; }
//};

// Generische Progr:
// Man instanziiert ein Template mit einem Typ
// Man instanziiert eine Klasse,um ein Objekt zu erhalten

// Primäre Template
template <typename T, typename U = float>
class Calculator
{
public:
    static T add(T x, T y) { return x + y; }
    static T sub(T x, T y) { return x - y; }
    static T mul(T x, T y) { return x * y; }
    static T div(T x, T y) { return x / y; }
};

// Spezialisierung einer Methode
//template <typename U>
//int Calculator<int, U>::div(int x, int y) {
//
//    return  (int)((double(x) / y) + 0.5);
//}

template <>
int Calculator<int>::div(int x, int y) {

    return  (int)((double(x) / y) + 0.5);
}


void test_seminar()
{
    std::cout << "Hallo Seminar" << std::endl;

    Calculator<int> calculator;    // Objekt
    Calculator<int> calculator2;   // Objekt

    calculator = calculator2;

    int result = Calculator<int>::div(5, 7);
    std::cout << "result:" << result << std::endl;

    double dresult = Calculator<double>::div(11.4, 23.4);
}

// =====================================================================================
// End-of-File
// =====================================================================================
