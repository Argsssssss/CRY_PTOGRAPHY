#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;
static const uint8_t __Sbox[8][4][16] = {
    { // 0
        {14, 4 , 13, 1 , 2 , 15, 11, 8 , 3 , 10, 6 , 12, 5 , 9 , 0 , 7 },
        {0 , 15, 7 , 4 , 14, 2 , 13, 1 , 10, 6 , 12, 11, 9 , 5 , 3 , 8 },
        {4 , 1 , 14, 8 , 13, 6 , 2 , 11, 15, 12, 9 , 7 , 3 , 10, 5 , 0 },
        {15, 12, 8 , 2 , 4 , 9 , 1 , 7 , 5 , 11, 3 , 14, 10, 0 , 6 , 13},
    },
    { // 1
        {15, 1 , 8 , 14, 6 , 11, 3 , 4 , 9 , 7 , 2 , 13, 12, 0 , 5 , 10},
        {3 , 13, 4 , 7 , 15, 2 , 8 , 14, 12, 0 , 1 , 10, 6 , 9 , 11, 5 },
        {0 , 14, 7 , 11, 10, 4 , 13, 1 , 5 , 8 , 12, 6 , 9 , 3 , 2 , 15},
        {13, 8 , 10, 1 , 3 , 15, 4 , 2 , 11, 6 , 7 , 12, 0 , 5 , 14, 9 },
    },
    { // 2
        {10, 0 , 9 , 14, 6 , 3 , 15, 5 , 1 , 13, 12, 7 , 11, 4 , 2 , 8 },
        {13, 7 , 0 , 9 , 3 , 4 , 6 , 10, 2 , 8 , 5 , 14, 12, 11, 15, 1 },
        {13, 6 , 4 , 9 , 8 , 15, 3 , 0 , 11, 1 , 2 , 12, 5 , 10, 14, 7 },
        {1 , 10, 13, 0 , 6 , 9 , 8 , 7 , 4 , 15, 14, 3 , 11, 5 , 2 , 12},
    },
    { // 3
        {7 , 13, 14, 3 , 0 , 6 , 9 , 10, 1 , 2 , 8 , 5 , 11, 12, 4 , 15},
        {13, 8 , 11, 5 , 6 , 15, 0 , 3 , 4 , 7 , 2 , 12, 1 , 10, 14, 9 },
        {10, 6 , 9 , 0 , 12, 11, 7 , 13, 15, 1 , 3 , 14, 5 , 2 , 8 , 4 },
        {3 , 15, 0 , 6 , 10, 1 , 13, 8 , 9 , 4 , 5 , 11, 12, 7 , 2 , 14},
    },
    { // 4
        {2 , 12, 4 , 1 , 7 , 10, 11, 6 , 8 , 5 , 3 , 15, 13, 0 , 14, 9 },
        {14, 11, 2 , 12, 4 , 7 , 13, 1 , 5 , 0 , 15, 10, 3 , 9 , 8 , 6 },
        {4 , 2 , 1 , 11, 10, 13, 7 , 8 , 15, 9 , 12, 5 , 6 , 3 , 0 , 14},
        {11, 8 , 12, 7 , 1 , 14, 2 , 13, 6 , 15, 0 , 9 , 10, 4 , 5 , 3 },
    },
    { // 5
        {12, 1 , 10, 15, 9 , 2 , 6 , 8 , 0 , 13, 3 , 4 , 14, 7 , 5 , 11},
        {10, 15, 4 , 2 , 7 , 12, 9 , 5 , 6 , 1 , 13, 14, 0 , 11, 3 , 8 },
        {9 , 14, 15, 5 , 2 , 8 , 12, 3 , 7 , 0 , 4 , 10, 1 , 13, 11, 6 },
        {4 , 3 , 2 , 12, 9 , 5 , 15, 10, 11, 14, 1 , 7 , 6 , 0 , 8 , 13},
    },
    { // 6
        {4 , 11, 2 , 14, 15, 0 , 8 , 13, 3 , 12, 9 , 7 , 5 , 10, 6 , 1 },
        {13, 0 , 11, 7 , 4 , 9 , 1 , 10, 14, 3 , 5 , 12, 2 , 15, 8 , 6 },
        {1 , 4 , 11, 13, 12, 3 , 7 , 14, 10, 15, 6 , 8 , 0 , 5 , 9 , 2 },
        {6 , 11, 13, 8 , 1 , 4 , 10, 7 , 9 , 5 , 0 , 15, 14, 2 , 3 , 12},
    },
    { // 7
        {13, 2 , 8 , 4 , 6 , 15, 11, 1 , 10, 9 , 3 , 14, 5 , 0 , 12, 7 },
        {1 , 15, 13, 8 , 10, 3 , 7 , 4 , 12, 5 , 6 , 11, 0 , 14, 9 , 2 },
        {7 , 11, 4 , 1 , 9 , 12, 14, 2 , 0 , 6 , 10, 13, 15, 3 , 5 , 8 },
        {2 , 1 , 14, 7 , 4 , 10, 8 , 13, 15, 12, 9 , 0 , 3 , 5 , 6 , 11},
    },
};

static const uint8_t __IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9 , 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7,
}; // 1

static const uint8_t __FP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9 , 49, 17, 57, 25,
};

static const uint8_t __K1P[28] = {
    57, 49, 41, 33, 25, 17, 9 , 1 , 58, 50, 42, 34, 26, 18,
    10, 2 , 59, 51, 43, 35, 27, 19, 11, 3 , 60, 52, 44, 36,
};

static const uint8_t __K2P[28] = {
    63, 55, 47, 39, 31, 23, 15, 7 , 62, 54, 46, 38, 30, 22,
    14, 6 , 61, 53, 45, 37, 29, 21, 13, 5 , 28, 20, 12, 4 ,
};

static const uint8_t __CP[48] = {
    14, 17, 11, 24, 1 , 5 , 3 , 28, 15, 6 , 21, 10, 
    23, 19, 12, 4 , 26, 8 , 16, 7 , 27, 20, 13, 2 , 
    41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 
    44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32,
};

static const uint8_t __EP[48] = {
    32, 1 , 2 , 3 , 4 , 5 , 4 , 5 , 6 , 7 , 8 , 9 ,
    8 , 9 , 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 ,
};

static const uint8_t __P[32] = {
    16, 7 , 20, 21, 29, 12, 28, 17, 1 , 15, 23, 26, 5 , 18, 31, 10,
    2 , 8 , 24, 14, 32, 27, 3 , 9 , 19, 13, 30, 6 , 22, 11, 4 , 25,
};
static const uint8_t __S[16] = {
    1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};
static const uint8_t __one_lst[16] = {
    0,5, 6,11, 12,17, 18,23, 24,29, 30,35, 36,41, 42,47
};
static const uint8_t __mid[32] = {
    1,2,3,4, 7,8,9,10, 13,14,15,16, 19,20,21,22, 25,26,27,28, 31,32,33,34, 37,38,39,40, 43,44,45,46
};
vector<int> str_to_binary(string mes){
    vector<int> bin_mes(64);
    int two_degr[] = {128, 64, 32, 16, 8, 4, 2, 1};
    int k = 0;
    for(int i = 0; i < mes.size(); i++){
        for (int j = 0; j < 8; j++)
        {
            if(mes[i] - two_degr[j] >= 0){
                mes[i] -= two_degr[j];
                bin_mes[k] = 1;
            }   
            else{
                bin_mes[k] = 0;
            }
            k++;
        }
    }
    return bin_mes;
}

vector<int> permutation(vector<int> bits, const uint8_t pattern[], int size){
    vector<int> buff(size);
    for (int i = 0; i < size; i++)
    {
        buff[i] = bits[pattern[i] - 1];
    }
    return buff;
}
void key56_to28(vector<int> key, vector<int> &key_l, vector<int> &key_r){
    for (int i = 0; i < 28; i++)
    {
        key_l[i] = key[__K1P[i] - 1];
        key_r[i] = key[__K2P[i] - 1];
    }
}
vector<int> shift_to_left(vector<int> contain, int shifts){
    vector<int> buff(28);
    for (int i = shifts, j = 0; i < 28;j++, i++)
    {
        buff[i] = contain[j];
    }
    for (int i = 0; i < shifts; i++)
    {
        buff[28 - shifts + 1] = contain[i];
    }
    return buff;
}
vector<int> key_two_block_to_one(vector<int> key_l,vector<int> key_r){
    vector<int> buff(56);
    for (int i = 0; i < 28; i++)
    {
        buff[i] = key_l[i];
        buff[i + 28] = key_r[i];
    }
    return buff;
}
vector<int> add_round_key(vector<int> key, const int num_round){
    vector<int> key_l(28);
    vector<int> key_r(28);
    key56_to28(key, key_l, key_r);
    key_l = shift_to_left(key_l, __S[num_round]);
    key_r = shift_to_left(key_r, __S[num_round]);
    key = permutation(key_two_block_to_one(key_l, key_r), __CP, 48);
    return key;
}
void one_block_mes_to_two(vector<int> block_mes, vector<int> &mes_l, vector<int> &mes_r){
    for(int i = 0; i < 32;i++){
        mes_l[i] = block_mes[i];
        mes_r[i] = block_mes[i + 32];
    }
}
vector<int> XOR_blocks(vector<int> block_mes, vector<int> block_round_key,const int size){
    for (int i = 0; i < size; i++)
    {
        block_mes[i] ^= block_round_key[i];
    }
    return block_mes;
}
vector<int> bin_to_dec(vector<int> bin,const uint8_t pattern[], int size_bin){
    vector<int> buff(8);
    vector<int> degree_two = {2,1};
    vector<int> degree_four = {8,4,2,1};
    switch (size_bin){
        case 2:
            for (int i = 0, j = 0; i < 8; ++i, j += 2)
            {
                if (bin[pattern[j]] == 1)
                {
                    buff[i] += degree_two[0];
                }if (bin[pattern[j + 1]] == 1){
                    buff[i] += degree_two[1];
                }
            }
            break;
        case 4:
            for (int i = 0, j = 0; i < 8; ++i, j += 4)
            {
                if (bin[pattern[j]] == 1)
                {
                    buff[i] += degree_four[0];
                }if (bin[pattern[j + 1]] == 1)
                {
                    buff[i] += degree_four[1];
                }if (bin[pattern[j + 2]] == 1)
                {
                    buff[i] += degree_four[2];
                }if (bin[pattern[j + 3]] == 1)
                {
                    buff[i] += degree_four[3];
                }
            }
    }
    return buff;
}
vector<int> S_bin_to_dec(vector<int> block_S){
    vector<int> buff(32);
    int two_degr[] = {8, 4, 2, 1};
    for (int i = 0, k = 0; i < 8; ++i)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block_S[i] - two_degr[j] >= 0)
            {
                block_S[i] -= two_degr[j];
                buff[k] = 1;
            }
            else{buff[k] = 0;}
            k++;
        }
        
    }
    return buff;
}
vector<int> S_8_t(vector<int> mes_48){
    vector<int> S_main_block(8), S_one_lst = bin_to_dec(mes_48, __one_lst, 2), S_mid = bin_to_dec(mes_48, __mid, 4);
    
    for (int i = 0; i < 8; ++i)
    {
        S_main_block[i] = __Sbox[i][S_one_lst[i]][S_mid[i]];
    }
    
    return S_bin_to_dec(S_main_block);
}
vector<int> feistel(vector<int> block, vector<int> round_key){
    return S_8_t(XOR_blocks(permutation(block, __EP, 48), round_key, 48));
}
vector<int> two_mes_to_one(vector<int> bin_mes_l, vector<int> bin_mes_r){
    vector<int> buff(64);
    for (int i = 0; i < 32; i++)
    {
        buff[i] = bin_mes_l[i];
        buff[i + 32] = bin_mes_r[i];
    }
    return buff;
}
vector<int> bits_to_str(vector<int> bits, const int size){
    vector<int> mes(size);
    int two_degr[] = {128, 64, 32, 16, 8, 4, 2, 1};
    for (int i = 0, k = 0; i < size; ++i)
    {
        for (int j = 0; j < 8; j++) {
            if(bits[k] == 1){
                mes[i] += two_degr[j];
            }
            k++;
        }
    }
    return mes;
}
vector<int> DES_ENCRYPTION(string mes, string key){
    vector<int> bin_mes = permutation(str_to_binary(mes), __IP, 64);
    vector<int> bin_key(48);
    vector<int> mes_l(32), mes_r(32);
    
    for (int i = 0; i < 16; i++) {
        one_block_mes_to_two(bin_mes, mes_l, mes_r);
        mes_l = XOR_blocks(feistel(mes_r, add_round_key(str_to_binary(key), i)), mes_l, 32);
        swap(mes_l, mes_r);
    }
    
    bin_mes = permutation(two_mes_to_one(mes_l,mes_r), __FP, 64);
    // 
    return bin_mes;
}
vector<int> DES_DECRYPTION(vector<int> ch_text, string key, const int size){
    vector<int> ch_l(32), ch_r(32);
    ch_text = permutation(ch_text, __IP, 64);
    
    for (int i = 15; i >= 0; i--) {
        one_block_mes_to_two(ch_text, ch_l, ch_r);
        ch_r = XOR_blocks(feistel(ch_l, add_round_key(str_to_binary(key), i)), ch_r, 32);
        swap(ch_l, ch_r);
    }
    
    return bits_to_str(permutation(two_mes_to_one(ch_l,ch_r), __FP, 64), size);
}
int main(void){
    string mes = "PRIVET", key = "0xFFFFFF";
    vector<int> encryption_mes =  DES_ENCRYPTION(mes,key);
    vector<int> dectyption_mes = DES_DECRYPTION(encryption_mes, key, mes.size());
    
    for (auto i : dectyption_mes) {
        std::cout << static_cast<char>(i);
    }
    cout << '\n';
    for (auto i : encryption_mes)
    {
        cout << i;
    }
    
}