#include <iostream>

union
{
    int x;
    uint32_t product_code;
    uint16_t serial_code;
    unsigned char bitstream[sizeof(uint64_t)];
} un;

int main()
{

    //converting float to double represenation, punning. Similar thing being done here in union.
    float f_var = 90.0f;
    double f_var_representation = *((double *)(&f_var));
    std::cout << f_var << "  " << f_var_representation << "\n\n";   

    un.product_code = 435; // we write as uint32 to the union
    std::cout<<un.product_code<<std::endl<<std::endl; //when accessing we acceess using uint_64, which also reads it(the very same data, in unions memory address) as 435
    // if we accessed it as uint_32 or double, it would have been represented in a different way
    
    //trying to print value from bitstream
    std::cout<<std::hex<<(int)un.bitstream[0]<<std::endl;

    
    //printing the bytes
    std::cout<<"As Bitstream: \n";
    for (size_t i = 0; i < sizeof(long); ++i)
        std::cout << std::hex << (long)un.bitstream[i] << " ";
       std::cout  << "\n";
}