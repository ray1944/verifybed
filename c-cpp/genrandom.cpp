//Computers are generally incapable of generating random numbers, Instead, they must simulate
//randomness, which is most often done using pseudo-random number generators(PRNG).
// std::srand() sets the initial seed value to a value that is passed in by the caller.
// srand() should only be called once at the beginning of your program.
// std::rand() generates the next random number in the sequence. 
// That number will be a pseudo-random integer between 0 and RAND_MAX, a constant in cstdlib 
// that is typically set to 32767
#include <iostream>
#include <cstdlib>
#include <ctime> // std::time(), returns number of seconds simce midnight on Jan 1, 1970.

/*
 * source code comes from:
 * https://www.learncpp.com/cpp-tutorial/59-random-number-generation/
 * 
 * */

/*
 * std::rand() is a mediocre PRNG
 * algorithm used to implement std::rand() can vary from compiler to compiler.
 * most implementations of rand() use a method called a Linear Congruential Generator - LCG
 * https://en.wikipedia.org/wiki/Linear_congruential_generator
 * Defects:
 * - essentially 15-bits, RAND_MAX (32767). not suitable over a larger range (32-bit)
 * - high-quality PRNG is Mersenne Twister http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
 * - after calling srand(), call rand() once and discard the first result to avoid this issue 
 */

/*
 * C++11 added a ton of random number PRNG into C++ standard library
 * including the Mersenne Twister algorithm
 * this is accessed via <random> header.
 */

int always_same() {
    // in order to make our entire sequence randomized, we need some way to pick a seed that's
    // not a fixed number.
    std::srand(5323);
    return 0;
}

int not_same() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    return 0;
}
int main() {
    always_same();
    //not_same()
    for (int count = 1; count <= 100; ++count) {
        std::cout << std::rand() << "\t";
        if (count % 5 == 0)
            std::cout << std::endl;
    }
    return 0;
}
