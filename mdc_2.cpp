#include <iostream>
#include <fstream>
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
    key[0] = mes[0];
    key[1] = mes[1];
}
void speck_decr(u_int64_t mes[2], u_int64_t key[2]){
    for (int i = 31; i > -1; i--)
    {
        round_decr(key[0],key[1],i);
        round_decr(mes[0],mes[1],key[1]);
        cout << mes[0] << mes[1] << endl;
    }
}
u_int64_t str_to_uint64(string info){
    u_int64_t buff = 0;
    for (size_t i = 0; i < 8; i++)
    {   
        buff |= info[i];
        i != 7 ? buff <<= 8 : buff;
    }
    return buff;
}
void form_block_8(string &info){
    if(info.size() % 16 != 0){
        while(info.size() % 16 != 0){
            info+='\0';
        }
    }
}
void mdc_2(string file_byte){
    u_int64_t G0[2] = {0x5252525252525252, 0x5252525252525252}, H0[2] = {0x2525252525252525, 0x2525252525252525};
    u_int64_t CT1[2]{}, CT2[2]{};
    form_block_8(file_byte);
    
    for (int i = 0; i < file_byte.size(); i+=16)
    {   
        CT1[0] = str_to_uint64(file_byte.substr(i,8));
        CT2[0] = str_to_uint64(file_byte.substr(i,8));
        CT1[1] = str_to_uint64(file_byte.substr(i + 8,8));
        CT2[1] = str_to_uint64(file_byte.substr(i + 8,8));
        speck_encr(CT1,G0);
        speck_encr(CT2,H0);
        G0[0] ^= str_to_uint64(file_byte.substr(i,8));
        G0[1] ^= str_to_uint64(file_byte.substr(i + 8,8));
        H0[0] ^= str_to_uint64(file_byte.substr(i,8));
        H0[1] ^= str_to_uint64(file_byte.substr(i + 8,8));
        swap(G0[0],H0[0]);
    }
    cout << hex << G0[0] << G0[1] << H0[0] << H0[1];
}
bool openfile(char * filename){
    ifstream file_byte(filename, ios::binary);
    char byte;
    string u_byte_text_file;
    while(file_byte.get(byte)){
        int i = 0;
        u_byte_text_file += static_cast<unsigned char>(byte);
    }
    mdc_2(u_byte_text_file);
    return false;
}
int main(int argc, char* argv[]){
    return openfile(argv[1]);
}