#include <iostream>
#include <vector>
using namespace std;
vector <int> gen_private_key(int first_num){
    vector <int> priv_key(9,first_num);
    for (size_t i = 0, point = 0; i < 9; i++)
    {
        priv_key[i] += i;
        for (size_t j = 0; j < i; j++)
        {
            point+=priv_key[j];
        }
        priv_key[i] += point;
        point = 0;
    }
    return priv_key;
}
int eqlid(int a, int b){
    if(a % b == 0){
        return b;
    }
    return eqlid(b, a % b);
}
int inverse_numb(int a, int b){
    int x[100] = {1,0}, q, r, mod = b;
    for (size_t i = 2; ;i++)
    {
        r = a % b;
        q = a / b;
        x[i] = x[i - 2] - q * x[i - 1];
        if(r == 0){
            if(x[i - 1] < 0){
                while(x[i - 1] < 0){
                    x[i - 1] += mod;
                }
                return x[i - 1];
            }
            else{
                return x[i - 1];
            }
        }
        a = b;
        b = r;
    }
    return 0;
}
int generate_const(int mod){
    srand(time(0));
    for (size_t i = 0, k; i < mod; i++)
    {   k = rand() % mod;
        if(eqlid(k, mod) == 1){
            return k;
        }
    }
    return 0;
}
vector <int> gen_pub_key(vector <int> priv_key, int n, int mod){
    for (size_t i = 0; i < 8; i++)
    {
        priv_key[i] *= n;
        priv_key[i] % mod;
    }
    return priv_key;
}
vector<int> str_to_binary(string mes){
    vector<int> bin_mes(mes.size() * 8);
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
string bits_to_str(vector<int> bits){
    string mes(bits.size() / 8, char(NULL));
    cout << mes;
    int two_degr[] = {128, 64, 32, 16, 8, 4, 2, 1};
    for (int i = 0, k = 0; i < bits.size() / 8; ++i)
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
vector <int> encrypt(string mes, vector <int> pub_key){
    vector <int> bin_mes(str_to_binary(mes)), encr_mes(mes.size(),0);
    for (size_t i = 0, k = 0; i < bin_mes.size(); i++)
    {     
        if(bin_mes[i] == 1){
            encr_mes[k] += pub_key[i % 8];
        }
        if(i % 8 == 0 and i != 0){
            k++;
        }
        // cout << i % 8 << ") " << bin_mes[i] << "|" << pub_key[i % 8] << "|" << encr_mes[k] << '\n';
    }
    for(int i = 0; i < mes.size();i++){
        // cout << encr_mes[i] << "|";
    }
    return encr_mes;
}
string sort(string mes){
    string buff(mes.size(),char(NULL));
    for (size_t i = 0; i < mes.size(); i++)
    {
        buff[i] = mes[mes.size() - 1 - i];
    }
    return buff;
}
string decrypt(vector<int> encr_mes, vector <int> private_key, int inverse_n){
    vector <int> bin_mes(encr_mes.size() * 8);
    for(int i = 0; i < encr_mes.size();i++){
        encr_mes[i] *= inverse_n;
        encr_mes[i] %= private_key[8];
    }
    for (size_t i = 0, k = encr_mes.size() * 8 - 1; i < encr_mes.size(); i++)
    {
        for (size_t j = 0; j < 8;k--, j++)
        {
            if(encr_mes[i] - private_key[7 - j] >=0){
                bin_mes[k] = 1;
                encr_mes[i] -= private_key[7 - j];
            }else{bin_mes[k] = 0;}
        }
    }
    return sort(bits_to_str(bin_mes));
}
void ranec(string mes, int first_pos){
    vector <int> private_key(gen_private_key(first_pos)); // private key
    int n = generate_const(private_key[8]), inv_n = inverse_numb(n,private_key[8]);
    vector <int> pub_key(gen_pub_key(private_key, n, private_key[8])); // public key
    // cout << inv_n << "<--mod"; // module
    vector<int> encr_mes(encrypt(mes,pub_key)); // encrypt


    cout << decrypt(encr_mes, private_key, inv_n); // decrypt

}
int main(){
    string mes = "P:AAV;ldkl;wer";
    ranec(mes, 3);
    return 0;
}