#include <iostream>

template<bool small, int I> struct prettyPrinter;

#define smallPrettyPrinter(num, string) template<> struct prettyPrinter<true, num> \
{\
    static void print()\
    {\
        std::cout << string;\
    }\
};

smallPrettyPrinter(0, "No")
smallPrettyPrinter(1, "One")
smallPrettyPrinter(2, "Two")
smallPrettyPrinter(3, "Three")
smallPrettyPrinter(4, "Four")
smallPrettyPrinter(5, "Five")
smallPrettyPrinter(6, "Six")
smallPrettyPrinter(7, "Seven")
smallPrettyPrinter(8, "Eight")
smallPrettyPrinter(9, "Nine")
smallPrettyPrinter(10, "Ten")
smallPrettyPrinter(11, "Eleven")
smallPrettyPrinter(12, "Twelve")
smallPrettyPrinter(13, "Thirteen")
smallPrettyPrinter(14, "Fourteen")
smallPrettyPrinter(15, "Fifteen")
smallPrettyPrinter(16, "Sixteen")
smallPrettyPrinter(17, "Seventeen")
smallPrettyPrinter(18, "Eighteen")
smallPrettyPrinter(19, "Nineteen")

#undef smallPrettyPrinter

template<int ones> inline void printOnes();

#define onesPrinter(ones, string) template<> inline void printOnes<ones>() \
{\
    std::cout << string;\
}

onesPrinter(0, " ")
onesPrinter(1, " one")
onesPrinter(2, " two")
onesPrinter(3, " three")
onesPrinter(4, " four")
onesPrinter(5, " five")
onesPrinter(6, " six")
onesPrinter(7, " seven")
onesPrinter(8, " eight")
onesPrinter(9, " nine")

#undef onesPrinter

template<int tens> inline void printTens();

#define tensPrinter(tens, string) template<> inline void printTens<tens>() \
{\
    std::cout << string;\
}

tensPrinter(2, "Twenty")
tensPrinter(3, "Thirty")
tensPrinter(4, "Forty")
tensPrinter(5, "Fifty")
tensPrinter(6, "Sixty")
tensPrinter(7, "Seventy")
tensPrinter(8, "Eighty")
tensPrinter(9, "Ninety")

#undef tensPrinter

template<int I> struct prettyPrinter<false, I>
{
    static void print()
    {
        printTens<(I - I % 10) / 10>();
        printOnes<(I % 10)>();
    }
};

template<int I> void prettyPrint()
{
    prettyPrinter<(I < 20), I>::print();
}

template<int I> inline void BottlesOfBeer()
{
    prettyPrint<I>();
    std::cout << " bottles of beer";
}

template<> inline void BottlesOfBeer<1>()
{
    prettyPrint<1>();
    std::cout << " bottle of beer";
}

int main()
{
    return 0;
}