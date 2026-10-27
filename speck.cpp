#include <iostream>
using namespace std;

void ROR(u_int64_t & block, const int shift){
    block = ((block >> shift) | (block << (64 - shift)));
}
void ROL(u_int64_t & block, const int shift){
    block = ((block << shift) | (block >> (64 - shift)));
}
void round_encr(u_int64_t &block_1, u_int64_t &block_2, u_int64_t key){
        ROR(block_1, 8);
        block_1 = (key ^ (block_1 + block_2));
        ROL(block_2, 3);
        block_2 ^=block_1;
}
void round_decr(u_int64_t &block_1, u_int64_t &block_2, u_int64_t key){
        block_2 ^= block_1;
        ROR(block_2, 3);
        block_1 = (block_1 ^ key) - block_2;
        ROL(block_1, 8);
}
void speck_encr(u_int64_t mes[2], u_int64_t key[2]){
    for (size_t i = 0; i < 32; i++)
    {   
        round_encr(mes[0],mes[1],key[1]);
        round_encr(key[0],key[1],i);
    }
}
void speck_decr(u_int64_t mes[2], u_int64_t key[2]){
    for (int i = 31; i > -1; i--)
    {
        round_decr(key[0],key[1],i);
        round_decr(mes[0],mes[1],key[1]);
    }
}
int main(){
    u_int64_t mes[2] = {0xAAAA, 0xBBBB}, key[2] = {0xA, 0xB};
    speck_encr(mes,key);
    cout << hex << mes[0] << mes[1] << endl;
    speck_decr(mes,key);
    cout << hex << mes[0] << mes[1] << endl;
}