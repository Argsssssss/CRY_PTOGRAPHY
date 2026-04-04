#include <iostream>
using namespace std;
void ecc();

struct Point { int x; int y; };

int degree_mod(int ground, int degree, int mod){
    int buff = 1;
    for(int i = 0; i < degree;i++){
        buff *= ground;
        buff % mod;
    }
    return buff;
}
int negative_numb(int numb, int mod){
    if(numb < 0){
        while (numb < 0)
        {
            numb += mod;
        }
        return numb;
    }else{
        numb %= mod;
    }
    return numb;
}
int inverse_numb_on_map_galua_GF(int numb, int mod){
    int x[255] = {1,0};
    int i = 2, b = mod, r, q;
    while(true){
        q = numb / b;
        r = numb % b;
        x[i] = x[i - 2] - (q * x[i - 1]);
        if(r == 0){
            if(x[i - 1] < 0){
                return negative_numb(x[i - 1], mod);
            }else{
                return x[i - 1];
            }
        }
        numb = b;
        b = r;
        i++;
    }
    return 0;
}
bool test_singulyar(int a, int b, int mod){
    // 4a^3 + 27b^2 mod ??? != 0
    if((4 * degree_mod(a, 3, mod) + 27 * degree_mod(b, 2, mod)) % mod != 0){
        return true;
    }else{
        return false;
    }
    return 0;
}
Point generate_points(int a, int b, int mod){
    if (test_singulyar(a, b, mod) == false) return;
    
    
    Point pt;

    return pt;   
}


int main(void){
    cout << test_singulyar(2,2,7);
    // ecc();
    return 0;
}
