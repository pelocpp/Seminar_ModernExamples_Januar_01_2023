// =====================================================================================
// TemplatesClassBasics02.cpp // Class Templates Basics 02
// =====================================================================================

#include <iostream>
#include <string>

#include "MyArray.h"         // demonstrating 'Templates Inclusion Model'
#include "AnotherArray.h"    // demonstrating 'Templates Explicit Instantiation Model'

namespace ClassTemplatesBasics_02 {

    // Simple Class Template Definition
    namespace ClassTemplatesBasics_Intro_01 {

        template <typename T>
        class MyContainer
        {
        private:
            T m_data;

        public:
            MyContainer() : m_data{} {}
            T getData() const { return m_data; }
            void setData(const T& data) { m_data = data; }
        };

        // explicit class template instantiation
        template class MyContainer<float>;

        void test_01() {
            MyContainer<double> container;
            container.setData(123.456);
            double value = container.getData();
            std::cout << value << std::endl;
        }

        // implicit instantiation of MyContainer<double>
        void test_02() {
            MyContainer<double> container;
        }
    }

    // Class Templates with several formal Parameters
    namespace ClassTemplatesBasics_Intro_02 {

        template <typename T, typename U>
        class MyPair
        {
        public:
            T m_data_01;
            U m_data_02;

        public:
            MyPair(const T& data_01, const U& data_02) 
                : m_data_01{ data_01 }, m_data_02{ data_02 } { }

            void print(std::ostream& os) {
                os << m_data_01 << " : " << m_data_02 << std::endl;
            }
        };

        void test_02() {
            MyPair<std::string, double> averageTemperature{ "March", 5.5 };
            averageTemperature.print(std::cout);
        }
    }

    // Definition of methods of class template (inside / outside class)
    namespace ClassTemplatesBasics_Intro_03 {

        template <typename T>
        class MyContainer
        {
        private:
            T m_data;

        public:
            MyContainer();
            T getData() const;
            void setData(const T& data);
        };

        template <typename T>
        MyContainer<T>::MyContainer() : m_data{} {}

        template <typename T>
        T MyContainer<T>::getData() const {
            return m_data;
        }

        template <typename T>
        void MyContainer<T>::setData(const T& data) {
            m_data = data;
        }

        void test_03() {
            MyContainer<double> container;
            container.setData(654.321);
            double value = container.getData();
            std::cout << value << std::endl;
        }
    }

    // Template specialization of a single method from a templated class

    // Overriding (specialization) of a single method from a class template
    namespace ClassTemplatesBasics_Intro_04 {

        template <typename T>
        class MyContainer
        {
        private:
            T m_data;

        public:
            MyContainer() : m_data{} {}
            T getData() const { return m_data; }
            void setData(const T& data) { m_data = data; }
        };

        template <>
        void MyContainer<std::string>::setData(const std::string& data) {
            m_data = "[" + data + "]";
        }

        void test_04() {
            MyContainer<std::string> container;
            container.setData("I love C++ Templates :)");
            std::string data = container.getData();
            std::cout << data << std::endl;

            MyContainer<int> anotherContainer;
            anotherContainer.setData(123);
            int value = anotherContainer.getData();
            std::cout << value << std::endl;
        }
    }

    // Overriding (specialization) of a single method from a class template
    namespace ClassTemplatesBasics_Intro_05 {

        template <typename T>
        class MyContainer
        {
        private:
            T m_data;

        public:
            MyContainer() : m_data{} {}
            T getData() const { return m_data; }
            void setData(const T& data) { m_data = data; }
        };

        template <>
        void MyContainer<std::string>::setData(const std::string& data) {
            m_data = "[" + data + "]";
        }

        void test_05() {
            MyContainer<std::string> container;
            container.setData("I love C++ Templates :)");
            std::string data = container.getData();
            std::cout << data << std::endl;

            MyContainer<int> anotherContainer;
            anotherContainer.setData(123);
            int value = anotherContainer.getData();
            std::cout << value << std::endl;
        }
    }

    namespace ClassTemplatesBasics_Intro_06 {

        class Printer {
        private:
            std::ostream& m_target;

        public:
            explicit Printer(std::ostream& target) : m_target(target) {}

            template<typename T>
            Printer& print(const T& arg) {
                m_target << arg;
                return *this;
            }
        };

        void test_06() {

            Printer normalPrinter(std::cout);
            normalPrinter.print<int>(100).print(" --> ").print(123.456).print("\n");

            Printer errorPrinter(std::cerr);
            errorPrinter.print<float>(654.321f).print(" <== ").print(100).print("\n");
        }
    }

    namespace ClassTemplatesBasics_Intro_07 {

        template <typename T, size_t DIM >
        class FixedVector
        {
        private:
            T m_data[DIM];

        public:
            FixedVector () : m_data{} {}

            size_t size() { return DIM; }

            void set(size_t idx, const T& elem) { m_data[idx] = elem; }

            T get(size_t idx) const { return m_data[idx]; }

            void print(std::ostream& os) {
                for (const auto& elem : m_data) {
                    os << elem << ' ';
                }
                os << '\n';
            }
        };

        void test_07_01() {

            FixedVector<int, 5> vec;

            for (size_t n{}; n < vec.size(); ++n) {
                vec.set(n, 2 * static_cast<int>(n));
            }

            vec.print(std::cout);
        }

        void test_07_02() {

            using namespace ClassTemplatesBasics_02::ClassTemplatesBasics_Intro_01;

            MyContainer<int> cont_1;
            MyContainer<int> cont_2;        // cont_1 and cont_2 have same type
            FixedVector<int, 10> vector_1;
            FixedVector<int, 20> vector_2;  // vector_1 und vector_2 have different types !!!

            // Code Bloat ..........

            //vector_1 = vector_2;         // Error: binary '=': no operator found
        }

        void test_07() {
            test_07_01();
            test_07_02();
        }
    }

    // Template Template-Parameter
    namespace ClassTemplatesBasics_Intro_08 {

        template <template <typename> class Container>
        class DoubleDataCollector
        {
        private:
            Container<double> m_collectedData;  // an arbitrary container is used
        public:
            // ...
        };

        template <typename T, template <typename> class Container>
        class GenericDataCollector
        {
        private:
            Container<T> m_collectedData;  // an arbitrary container is used
        public:
            // ...
        };

        void test_08() {

            using namespace ClassTemplatesBasics_02::ClassTemplatesBasics_Intro_01;

            DoubleDataCollector<MyContainer>         dc{};
            GenericDataCollector<float, MyContainer> gdc{};
        }
    }

    // Default Template-Parameter
    // Alias Templates
    namespace ClassTemplatesBasics_Intro_09 {

        template <typename T = int, size_t DIM = 10>
        class FixedVector
        {
        private:
            T m_data[DIM];

        public:
            FixedVector() : m_data{} {}

            size_t size() { return DIM; }

            void set(size_t idx, const T& elem) { m_data[idx] = elem; }

            T get(size_t idx) const { return m_data[idx]; }

            void print(std::ostream& os) {
                for (const auto& elem : m_data) {
                    os << elem << ' ';
                }
                os << '\n';
            }
        };

        template <int DIM>
        using FixedIntVector2 = FixedVector<int, DIM>;
        
        void test_09_01() {

            typedef FixedVector<int, 10> FixedIntVector;
            FixedIntVector vec0;

            FixedIntVector2<50> vec00;

            FixedVector vec1;
            FixedVector<> vec2;
            FixedVector<double> vec3;
            FixedVector<bool, 10> vec4;


            vec1.print(std::cout);
            vec2.print(std::cout);
            vec3.print(std::cout);
            vec4.print(std::cout);
        }

        template <size_t MAX>
        using FixedIntVector = FixedVector<int, MAX>;

        void test_09_02() {

            FixedIntVector<100> vec;
        }

        void test_09() {
            test_09_01();
            test_09_02();
        }
    }

    // demonstrating 'Templates Inclusion Model'
    void test_10() {

        using namespace ClassTemplatesBasics;

        MyArray<int, 10> array;

        for (size_t i = 0; i != 10; ++i) {
            array[i] = static_cast<int>(2 * i);
        }

        array.print();
    }

    // demonstrating 'Templates Explicit Instantiation Model'
    void test_11() {

        using namespace ClassTemplatesBasics;

        AnotherArray<double, 5> array;
        for (size_t i = 0; i != 5; ++i) {
            array[i] = 2.0 * i + 0.5;
        }
        array.print();

        AnotherArray<double, 5> array2;
        // AnotherArray<double, 10> array3;  // does NOT compile !!! see explicit instantiated classes !!!
    }
}

void main_class_templates_basics_02()
{
    using namespace ClassTemplatesBasics_02;

    //ClassTemplatesBasics_Intro_01::test_01();
    //ClassTemplatesBasics_Intro_02::test_02();
    //ClassTemplatesBasics_Intro_03::test_03();
    //ClassTemplatesBasics_Intro_04::test_04();
    //ClassTemplatesBasics_Intro_05::test_05();
    ClassTemplatesBasics_Intro_06::test_06();
    //ClassTemplatesBasics_Intro_07::test_07();
    //ClassTemplatesBasics_Intro_08::test_08();
    //ClassTemplatesBasics_Intro_09::test_09();

    test_10();
    test_11();
}

// =====================================================================================
// End-of-File
// =====================================================================================
