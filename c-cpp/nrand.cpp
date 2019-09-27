/*
 * A random integer [0 , n) generator 
 */
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <ctime>

using std::cout;
using std::endl;
using std::domain_error;
using std::cin;
using std::getline;
using std::time;
using std::srand;

int nrand(int n) {
    if (n <= 0 || n > RAND_MAX) {
        throw domain_error ("Argument to nrand is out of rande");
    }
    const int bucket_size = RAND_MAX / n;
    int r;

    do r = rand() / bucket_size;
    while ( r >= n );

    return r;
}

int main(int argc, const char* argv[]) {
    int n = 0;

    srand(static_cast<unsigned>(time(NULL)));
    cout << "Input a integere: ";
    while (cin >> n) {
        cout << "Random integer [0, "<< n << "): ";
        for (int idx = 0; idx < 10; idx++) {
            cout << nrand(n) << " ";
        }
        cout << endl;
        cout << "Input a integere: " << endl;
    }

    return 0;
}