#include <iostream>
#include <boost/any.hpp>
#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>

/***********************************************************************
 * Knowledge points:
 * 1. boost::any, boost::any_cast<>()
 * 2. vector<boost::any>
 * 3. unary_function<boost::any, void>
 * 4. explicit, double& relationship
 * 5. value.type(), typeid(), std::type_info
 *********************************************************************** */
using namespace std;

typedef boost::any cell_t;
typedef vector<cell_t> db_row_t;

db_row_t get_row(const char* query)
{
    db_row_t row;
    row.push_back(10);
    row.push_back(10.1f);
    row.push_back(string("Hello"));

    return row;
}

struct db_sum: public unary_function<boost::any, void>
{
private:
    double& _sum;
public:
    explicit db_sum(double& sum):_sum(sum) {}

    void operator() (const cell_t& value)
    {
        const type_info& ti = value.type();
        if (ti == typeid(int))
        {
            _sum += boost::any_cast<int>(value);
        } else if (ti == typeid(float))
        {
            _sum += boost::any_cast<float>(value);
        }
    }
};

int main()
{
    db_row_t row = get_row("Query");
    double res = 0.00;

    for_each(row.begin(), row.end(), db_sum(res));
    cout << "Sum of arithmetic types in database row is: " << res << endl;

    return 0;
}