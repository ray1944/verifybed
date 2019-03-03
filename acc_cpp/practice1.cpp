/*
 * 从终端读入用户输入，然后分析这个字符串将他们分解成 vector<string>向量
 * 要求尽量用 STL 标准库的容器，算法
 * istream& getline(istream& is, string& str);
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;
using std::find_if;

bool space(char c) {
    return isspace(c);
}

bool not_space(char c) {
    return !isspace(c);
}

vector<string> split(string line) {
    vector<string> ret;
    string::iterator wb = line.begin();
    string::iterator we;
    
    while (wb != line.end()) {
        wb = find_if(wb, line.end(), not_space);
        we = find_if(wb, line.end(), space);
        // cout << *wb << "--" << we[-1] << endl;
        if (wb != line.end() 
            || we != line.end()) {
            string word = string(wb, we);
            // cout << "Word: " << word << endl;
            ret.push_back(string(wb, we));
            wb = find_if(we, line.end(), not_space);
        }
    }

    return ret;
}

int main(int argc, const char* argv[]) {
    string line;
    vector<string> parse_result;
    typedef vector<string>::const_iterator parse_it;
    parse_it cit;

    cout << "Input your line: " << endl;
    while (getline(cin, line)) {
        parse_result = split(line);
        cout << "There are " << parse_result.size() << " words" << endl;
        for (cit = parse_result.begin(); cit != parse_result.end(); cit++) {
            cout << *cit << endl;
        }
        cout << "Input your line: " << endl;
    }
    if (!cin) {
        cout << "Good bye!" << endl;
        cin.clear();
    }

    return 0;
}