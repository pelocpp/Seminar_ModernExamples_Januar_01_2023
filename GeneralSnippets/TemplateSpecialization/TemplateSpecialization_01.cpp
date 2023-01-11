// =====================================================================================
// TemplateSpecialization_01.cpp // Template Specialization
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

namespace TemplateSpecialization {

    // Explicit Template Specialization
    namespace ClassTemplates_ExplicitTemplateSpecialization {

        template<typename T>
        class GenericSorter
        {
        public:
            static void sort(std::vector<T>&) { /* ... */ }
        };

        // T = char :  besser, anders, performanter sortieren



        template<>
        class GenericSorter<char>   // T = char  FOLGE
        {
        public:
            static void sort(std::vector<char>&) { /* ... */ }
        };

        void test_01() {
            std::vector<int>  intVector;
            std::vector<char> charVector;

            GenericSorter<int>::sort(intVector);    // calls sort<std::vector<int>&>
            GenericSorter<char>::sort(charVector);  // calls specialized sort<std::vector<char>&>
        }
    }

    // Partial Template Specialization
    namespace ClassTemplates_PartialTemplateSpecialization {

        // Primäres Template
        template<typename T>
        class GenericSorter
        {
        public:
            static void sort(std::vector<T>&) { /* ... */ }
        };


        // T  passt   // Pointer:  Werte von T sortieren
        //            NICHT Pointer sortieren, T*

        // Partielle Spezialisierung:
        // A) Schablone: Für ALLE Typen T
        // b) Für alle Typen T:  Davon abgeleite Menge von Pointertypen
        // c) Partielle Spezialisierung: Für alle Typen, die ein Pointer sind

        // Weitere Beispiele: 
        // Ja: Viele Beispiele: MetaProgrammierung
        // T    T&      const T&    //  T&    ==>  T
        // Type Traits: 

        template<typename T>
        class GenericSorter<T*>
        {
        public:
            static void sort(std::vector<T*>&) { /* ... */ }
        };

        void test_02() {
            std::vector<int> intVector;
            std::vector<int*> pointerVector;

            GenericSorter<int>::sort(intVector);       // calls sort<std::vector<int>&>
            GenericSorter<int*>::sort(pointerVector);  // calls specialized sort<std::vector<char>&>
        }
    }
}

void main_template_specialization()
{
    using namespace TemplateSpecialization;
    ClassTemplates_ExplicitTemplateSpecialization::test_01();
    ClassTemplates_PartialTemplateSpecialization::test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
