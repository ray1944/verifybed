#include <iostream>
using namespace std;

int main() {
    int arr[10] = {1, 2, 3, 4};
    int * const & rarr = arr;
    //int const * &  rarr1 = arr;
    //int * & rarr2 = arr;
    int const* const & rarr3 = arr; //const array
    int idx;
    rarr [9] = 13;
    for(idx = 0 ; idx < 10; idx++) {
        cout << rarr[idx] << " ";
    }
    cout << endl;

    // rarr3[3] = 5;

    

    return 0;
}