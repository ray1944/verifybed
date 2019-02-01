#include <iostream>
#include <time.h>

using namespace std;
void weatherForcast(char * w="rainy") {
    time_t  t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A ",localtime(&t));
    cout <<tmp<<"todya is weather" << w << endl;
}

int main() {
    weatherForcast();
    weatherForcast("sunny");
    weatherForcast();

    return 0;
}