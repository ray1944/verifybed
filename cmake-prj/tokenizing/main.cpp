#include <iostream>
#include <vector>
#include <string>
#include  <sstream>
#include <boost/tokenizer.hpp>

using namespace std;
vector<string> tokenizeBySS(string t_src, char t_delimit)
{
    stringstream check1(t_src);
    string intermediate;
    vector<string> ret;

    while (getline(check1, intermediate, t_delimit))
    {   
        ret.push_back(intermediate);
    }

    for (int i  = 0; i < ret.size(); i++)
    {
        cout << ret[i] << ", ";
    }
    cout << endl;
}

void tokenizeByBoost(string t_src, string t_delimit)
{
    boost::char_separator<char> sep(t_delimit.c_str());
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    tokenizer tok(t_src, sep);
     
    for (tokenizer::iterator beg = tok.begin(); beg != tok.end(); ++beg)
    {
        cout << *beg << ", ";
    }
    cout << endl;
}

int main(int argc, char* argv[])
{

    // tokenizeBySS("Gkk ks is a must try", ' ');
    /*
     * unable to parse following string
     * */
    //tokenizeBySS("G/..////./m*", '/');

    tokenizeByBoost("G/..////./m*", "/");
    tokenizeByBoost("b*/.././////////////common*", "/");

    return 0;
}