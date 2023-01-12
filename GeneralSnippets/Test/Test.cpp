// =====================================================================================
// Test.cpp
// =====================================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

// A) my_remove_reference<int> ==> Obere ==> type = int
// B) my_remove_reference<int&> ==> Untere ==> type = int

// primary template
template <typename T>
struct my_remove_reference {
    using type = T;
};

// partielle Template Spezialisierung
template <typename T>
struct my_remove_reference<T&> {
    using type = T;
};

// Lambdas & Templates
auto tueWas = [] (const auto& x) {

    std::vector<int>::iterator pos;

    using T = decltype(x);

    using TypeWithoutReference = my_remove_reference<T>::type;

    using TypeWithoutConstAndReference 
        = std::remove_const<TypeWithoutReference>::type;

    if (std::is_same<int, TypeWithoutConstAndReference>::value)
    {
        std::cout << "bin ein int: x=" << x << std::endl;
    }
    else if (std::is_same<double, decltype(x)>::value)
    {
        std::cout << "bin ein double: x=" << x << std::endl;
    }
    else
    {
        std::cout << "etwas stimmt nicht" << std::endl;
    }
};

void test_seminar()
{
    tueWas(123);
    tueWas(123.456);
}


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
template <typename T, typename U = T>
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

void test_seminar_zum_Ersten()
{
    std::cout << "Hallo Seminar" << std::endl;

    Calculator<int> calculator;    // Objekt
    Calculator<int> calculator2;   // Objekt

    calculator = calculator2;

    int result = Calculator<int>::div(5, 7);
    std::cout << "result:" << result << std::endl;

    double dresult = Calculator<double>::div(11.4, 23.4);
}

// ================================================================

void test_seminar_01()
{
    std::vector<int> vec;
    vec.reserve(100);

    //vec.push_back(1);
    //vec.push_back(2);
    //vec.push_back(3);

    // very classic :)
    for (int i = 0; i < 120; ++i) {

        vec.push_back(2 * i);

        std::cout << "i: " << i << " - " << vec[i] <<
            ", Size: " << vec.size()  <<
            ", Capacity: " << vec.capacity() << std::endl;
    }
}

void eineFunktion(int n)
{
    std::cout << "eineFunktion: " << n << std::endl;
}

int berechneWert ()
{
    static int value = 1;   // 'value' bleibt von Aufruf zu Aufruf

    value = value * 2;

    std::cout << "berechneWert ==>: " << value << std::endl;

    return value;
}

void test_seminar_zum_Dritten()
{
    std::vector<int> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // very iterator specific
    std::vector<int>::iterator pos = vec.begin();
    std::vector<int>::iterator ende = vec.end();
    for (; pos != ende; ++pos) {
        std::cout << *pos << std::endl;
    }
    std::cout << "Ende" << std::endl;

    // STL algorithm specific
    std::for_each(
        vec.begin(),
        vec.end(),
        eineFunktion
    );

    // Wir wollen was machen :) Eine Anregung

    std::vector<int> vec2;
    vec2.resize(20);  // legt die Länge fest
    // vec2.reserve(20); // legt die Größe des intern Speicherbereichs fest

    // very classic :)
    for (int i = 0; i < vec2.size(); ++i) {

        vec2[i] = 1;
    }

    // vs.
    // memset, memcpy, memcmp, 
    // Intel , Mov ,  Rep prefix

    std::fill(
        vec2.begin(),
        vec2.end(),
        1
    );

    // Oder etwas anderes:
    // Vektor mit Indices mal 2 vorbelegen:
    // i  = 0, 1, 2, 3   =>   0, 2, 4, 6, ...

    std::generate(
        vec2.begin(),
        vec2.end(),
        berechneWert  
    );

    std::for_each(
        vec2.begin(),
        vec2.end(),
        eineFunktion
    );

}

// =====================================================================================
// End-of-File
// =====================================================================================
