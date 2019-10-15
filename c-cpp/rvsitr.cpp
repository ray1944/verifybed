#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
#include <sys/stat.h>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::back_inserter;
using std::copy;
using std::find;

/*
 * 分析一个 unix style 绝对路径模式。
 * 分析出path 的目录部分和文件名，如果有的话
 * /path/of/file -- /path/of/file 确定这个是目录还是文件
 * 如果是文件，可进一步确定 path 部分和文件部分
 * 如果是目录可直接输出目录部分和文件通配符。
 * 好像有一个 std::filesystem::path 可以包含很多路径方面的功能 (C++17 :()
 * */

/* unix/linux filesystem basics
 * https://blog.csdn.net/educast/article/details/8585717
 * struct stat {
 *   st_mode
 *   ...
 * }
 * 写一个读取一个文件的类，获得这个文件的属性（是目录还是一般文件或其他）
 * 
 */
class CFileAttr {
public:
    typedef enum ftype {
        eDir,
        eRegularFile,
        eSoftLink,
        eNotExist,
        eInvalid
    }CFileType;

    static const string TYPE_NAME[eInvalid];

    typedef struct stat fstat;

    CFileAttr():_type(eInvalid) {}

    CFileAttr(const string& path):_type(eInvalid) {
        fstat st;
        int ret;

        ret = lstat(path.c_str(), &st);
        if (ret == 0) {
            
            switch (st.st_mode & S_IFMT) { //查看文件类型的正确姿势
            case S_IFREG:
                _type = eRegularFile;
                break;
            case S_IFDIR:
                _type = eDir;
                break;
            case S_IFLNK:
                _type = eSoftLink;
                break;
            default:
                _type = eInvalid;
            }
        } else {
            _type = eNotExist;
        }   

    }

    CFileType GetType() const {
        cout << "type: " << TYPE_NAME[_type] << endl;
        return _type;
    }

    bool isRegularFile() const {
        return eRegularFile == GetType();
    }

    bool isDir() const {
        return eDir == GetType();
    }

private:
    string _name;
    CFileType _type;
};

const string CFileAttr::TYPE_NAME[eInvalid] = {
    "Directory",
    "Regular File",
    "Soft Link",
    "Not Exist"
};

const char SEPARATOR = '/';
const string WILDCARD = "*";
const string CURRENTDIR = ".";
const string PARENTDIR = "..";

/*
 * Devide first parameter into two parts: directory and file name
 */
vector<string> devide_separator(
    const string& str, const char sep = SEPARATOR) {
    vector<string> ret;
    string::const_reverse_iterator critrsep;
    string::const_reverse_iterator critrsepfirst;
    // string::reverse_iterator ritr; 之前我定义成 non-const 导致编译出错， 具体可看编译错误
    // iterator 可想像成指针，它也有类型。也就是他是 non-const 指针，由于str 参数是个 const 的
    // 所以 find 返回的也是 const iterator
    string::iterator itr;
    string::const_iterator citr;
    string directory;
    string file;
    // string& tmp = str;


        critrsep = find(str.rbegin(), str.rend(), sep);
        if (critrsep != str.rend()) { //reverse iterator with find(algorithm) to check result
            critrsepfirst = critrsep;
            while ( (critrsep + 1) != str.rend() &&
                *(critrsep + 1) == sep) {
                critrsep++;
            }
            citr = critrsep.base() - 1;
            // copy(str.begin(), itr, directory.begin()); 第二个参数的类型是 iterator 而非 const_iterator, 会导致错误
            // copy 函数声明的需要前两个参数原型是 const_iterator
            copy(str.begin(), citr, back_inserter(directory));
            if (directory.empty()) {
                directory = str;
                file = WILDCARD;
                ret.push_back(directory);
                ret.push_back(file);

                return ret;
            }
            ret.push_back(directory);
            citr = critrsepfirst.base() - 1;
            copy(citr + 1, str.end(), back_inserter(file));
            if (file.empty()) {
                file = WILDCARD;
            }
            ret.push_back(file);
        }


    return ret;
}

string getCWD() {
    char buf[1024];
    char * p = NULL;
    string ret;

    if ((p = getcwd(buf, sizeof(buf))) == NULL) {
        return ret;
    } else {
        return string(buf, strlen(buf));
    }
}

string getSWDParent() {
    string ret;

    return ret;
}

int main(int argc, const char* argv[]) {
    
    string paths[] = {
        "/Users/ray1944/workspace/learning/verifybed/c-cpp/rvsitr.cpp",
        "/Users/ray1944/workspace/learning/verifybed/c-cpp",
        "/Usssss", // non-exist directory
        "/Users/ray1944/workspace/learning/verifybed",
        "/Users/ray1944/workspace/learning/verifybed/",
        "/Users/ray1944/workspace/learning/verifybed/*",
        "/Users/ray1944/workspace/learning/verifybed/*.cpp",
        "./", // current directory, build in value for stat() which is a generic current directory
        ".", //current directory, build in value
        "..", // parent directory, build in value
        "/Users//////////ray1944" // multiple / is one /
    };
    
    string directory;
    string file;
    vector<string> pathlst;

    for (int idx = 0; idx < sizeof(paths)/sizeof(string); idx++) {
        pathlst.push_back(paths[idx]);
    }

    for (vector<string>::const_iterator citr = pathlst.begin(); citr != pathlst.end(); citr++) {
        string path = *citr;
        CFileAttr fileattr(path);
        string::reverse_iterator ritr;
        string::iterator itr; 
        vector<string> ret;

        cout << "Candidate: " << path << endl;
        if (fileattr.GetType() == CFileAttr::eDir) {
            if (path == CURRENTDIR) {
                directory = getCWD();
            } else {
                directory = path;
            }
            file = WILDCARD;
        } else {
            ret.clear();
            ret = devide_separator(path);
            directory = ret[0];
            file = ret[1];
        }      
        cout << "diretory: " << directory << endl;
        cout << "file: " << file << endl;
    }

    return 0;
}