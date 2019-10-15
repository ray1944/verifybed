#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

/*
 * Input Output type iterator usage
 * istream_iterator<T>(istream) is a istream input iterator
 * back_inserter(container) is a kind of output iterator
 * ostream_iterator<T>(ostream, c) is a ostream output iterator
 * */
int main(int argc, const char* arcv[]) {
   vector<int> v;

   copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(v));
   copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));

   return 0;

}