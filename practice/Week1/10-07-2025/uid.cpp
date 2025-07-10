#include <iostream>
#include <cstring>

typedef struct {
    int serial_id; 
    char prod_id[8];
}uuid;

typedef union{
    uuid id;
    unsigned char bitstream[sizeof(uint64_t)];
}serializer;

int main(){
uuid id1;
std::memcpy(id1.prod_id, "KiseiXmN", 8);
id1.serial_id = 834923;

serializer s1;
s1.id = id1;


for(int i=0;i<sizeof(uint64_t);i++){
    std::cout<<std::hex<<s1.bitstream[i];
}
std::cout<<std::endl;
}