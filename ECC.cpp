#include <iostream>
using namespace std;

bool ecc(int a, int b, int mod);
void visual_points();

struct Point { int *x = {new int [255]}; int *y = {new int [255]};};

int size_P(Point point){
    for(int i = 0; ; i++){
        if(point.x[i + 1] == 0 && point.y[i + 1] == 0){
            return i + 1;
        }
    }
    return 0;
}

int degree_mod(int ground, int degree, int mod){
    int buff = 1;
    for(int i = 0; i < degree;i++){
        buff *= ground;
        buff %= mod;
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
        return false;
    }else{
        return true;
    }
    return 0;
}

Point generate_points(int a, int b, int mod){
    Point pt;
    if (test_singulyar(a, b, mod) == true){ cout << "Singulyar" << endl; return pt;}
    // y^2 = x^3 + ax + b % mod ???

    for(int i = 0, x = 0, y = 0; i < mod; i++){
        for(int j = 0; j < mod; j++){
            if(degree_mod(j,2,mod) == (degree_mod(i,3,mod) + a * i + b) % mod){
                pt.x[x] = i;
                pt.y[y] = j;
                x++;
                y++;
            }
        }
    }
    return pt;   
}
Point pq(Point xy, int mod, int id_x, int id_y) {
    int lyam, head, footer;
    head = 
    cout << xy.x[id_x - 1] << "," << xy.y[id_x - 1] << endl;
    cout << xy.x[id_y - 1] << "," << xy.y[id_y - 1];
    
    
    
    
    return xy;
}
bool ecc(int a, int b, int mod){
    Point qwe = generate_points(a, b, mod);
    if (test_singulyar(a, b, mod) == true) return false;
    cout << "Format - {x, y} | " << "O{∞, ∞} " << endl;
    for(int i = 0; i < size_P(qwe); i++){
        cout <<  i + 1  << "{" <<  qwe.x[i] << ", " << qwe.y[i] << "};" << endl;
    }
    pq(qwe, mod, 1, 3);
    return false;
}

int main(void){
    
    return ecc(2, 1, 5); // a, b, mod;
    
}
