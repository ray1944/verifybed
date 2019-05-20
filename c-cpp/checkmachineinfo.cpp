/*
 * Check machine info
 */
 #include <iostream>
 #include <string>

class MachInfo 
{
public: 
    union BL
    {
        int32_t ori;
        unsigned char bytes[sizeof(int32_t)];
    };

    static bool isBigEndian()
    {
        if (check_endian()) 
        {
            return true;
        }

        return false;
    }

    static int wordWidth()
    {
        typedef char* PTR;
        int wd = sizeof(PTR);

        return wd;
    }

private:
    // 1 is big-endian
    // 0 is little-endian
    static int check_endian() 
    {
        union BL    seed;

        seed.ori = 0x12345678;
        if (seed.bytes[0] == 0x12) 
        {
            return 1;
        }
        else
        {
            return 0;
        }

        return 1; 
    }
};

int main(int argc, const char* argv[]) 
{
    std::string endian = MachInfo::isBigEndian()
                      ? "Big endian"
                      : "Little endian";

    std::cout << "This machine is " << endian << std::endl;
    std::cout << "Width: " << MachInfo::wordWidth() << std::endl;

  return 0;
}