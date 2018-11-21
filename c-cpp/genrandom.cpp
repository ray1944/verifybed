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
