#include <iostream>
#include <limits>
#include <random>

int main()
{
    std::default_random_engine eng((std::random_device())());
    std::uniform_int_distribution<int8_t> idis(0, std::numeric_limits<int8_t>::max());

    for (int i = 0; i < 10; ++i)
    {
        int8_t v = idis(eng);
        std::cout << (int32_t) v << std::endl;
    }

    std::uniform_real_distribution<float> fdis(0, 2.0);

    for (int i = 0; i < 10; ++i)
    {
        float v = fdis(eng);
        std::cout << v << std::endl;
    }

    return 0;
}