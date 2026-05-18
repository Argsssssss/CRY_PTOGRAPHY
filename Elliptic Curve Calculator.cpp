#include <iostream>
using namespace std;

struct Point { int *x = {new int [255]{0}}; int *y = {new int [255]{0}};};
struct L_R_Viershtrass { int *l = {new int [255]{0}}; int *r = {new int [255]{0}};};

int size_P(Point point){
    for(int i = 0; ; i++){
        if(point.x[i + 1] == 0 && point.y[i + 1] == 0){
            return i + 1;
        }
    }
    return 0;
}int degree_mod(int ground, int degree, int mod){
    int buff = 1;
    for(int i = 0; i < degree;i++){
        buff *= ground;
        buff %= mod;
    }
    return buff;
}int negative_numb(int numb, int mod){
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
}int inverse_numb_in_map_galua_GF(int numb, int mod){
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
void print_P(Point point, int id_p){
    cout << "{" <<  point.x[id_p] << ", " << point.y[id_p] << "}; ";
}
string print_i(int i){
    string buff = " ";
    if(i < 10){
        buff = " " + to_string(i) + " ";
        return buff;
    }
    else if(i >= 10 && i < 100){
        buff = " " + to_string(i);
        return buff;
    }else{return to_string(i);}
    return to_string(i);
}
L_R_Viershtrass L_R_Points(int a, int b, int mod){
    L_R_Viershtrass result;
    for(int i = 0; i < mod; i++){
        result.l[i] = degree_mod(i,2,mod);
        result.r[i] = (degree_mod(i,3,mod) + a * i + b) % mod;
    }
    return result;
}
void visual_generate_points(int a, int b, int mod){
    L_R_Viershtrass result = L_R_Points(a, b, mod);
    char point = '*';
    cout << "y/x|";
    for(int i = 0; i < mod; i++){
        cout << print_i(i) << "|";
    }
    cout << " L\n";
    for(int i = 0; i < mod; i++){
        cout << print_i(i) << "| ";
        for(int j = 0; j < mod; j++){
            if(degree_mod(i,2,mod) == (degree_mod(j,3,mod) + a * j + b) % mod){
                cout << point << " | ";
            }else{cout << " " << " | ";}
            
        }
        cout << result.l[i] << "  \n";
    }
    
    cout << " R |";

    for(int i = 0; i < mod; i++){
        cout << print_i(result.r[i]) << "|";
    }
    cout <<'\n';
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
Point pq(Point xy, int mod, int id_p, int id_q) { // Сложение разных точек
    Point buff;
    int lyam;
    // id_p = p
    // id_q = q
    // xy.x[id_p - 1] = xP
    // xy.y[id_p - 1] = yP
    // xy.x[id_q - 1] = xQ
    // xy.y[id_q - 1] = yQ ... для удобного копирования при разработке...удобно

    if(negative_numb(xy.y[id_p - 1] - xy.y[id_q - 1], mod) == negative_numb(xy.x[id_p - 1] - xy.x[id_q - 1], mod)){lyam = 1;}
    else if(negative_numb(xy.x[id_p - 1] - xy.x[id_q - 1], mod) == 0){lyam = negative_numb(xy.y[id_p - 1] - xy.y[id_q - 1], mod);}
    else{lyam = (negative_numb(xy.y[id_p - 1] - xy.y[id_q - 1], mod) * inverse_numb_in_map_galua_GF(negative_numb(xy.x[id_p - 1] - xy.x[id_q - 1], mod), mod)) % mod;}
    cout << "λ = " << lyam << "; ";

    buff.x[0] = negative_numb(degree_mod(lyam, 2, mod) - (xy.x[id_p - 1] + xy.x[id_q - 1]), mod);
    buff.y[0] = negative_numb(lyam * (xy.x[id_p - 1] - buff.x[0]) - xy.y[id_p - 1], mod);
    
    return buff;
}
Point pp(Point xy,int a, int mod, int id_p){
    Point buff;
    int lyam;
    if(negative_numb(3 * degree_mod(xy.x[id_p - 1], 2, mod) + a, mod) == negative_numb(2 * xy.y[id_p - 1], mod)){lyam = 1;}
    else if(2 * xy.y[id_p - 1] == 0){negative_numb(3 * degree_mod(xy.x[id_p - 1], 2, mod) + a, mod) % mod;}
    else{lyam = (negative_numb(3 * degree_mod(xy.x[id_p - 1], 2, mod) + a, mod) * inverse_numb_in_map_galua_GF(negative_numb(2 * xy.y[id_p - 1], mod), mod)) % mod;}
    cout << "λ = " << lyam << "; ";

    buff.x[0] = negative_numb(degree_mod(lyam,2,mod) - 2 * xy.x[id_p - 1], mod);
    buff.y[0] = negative_numb(lyam * (xy.x[id_p - 1] - buff.x[0]) - xy.y[id_p - 1], mod);
    
    return buff;
}
int search_id_in_points(Point xy, Point buff){ // Функция возвращает идентификатор точки из списка, которая совпадает с buff
    for(int i = 0; i < size_P(xy); i++){
        if(buff.x[0] == xy.x[i] && buff.y[0] == xy.y[i]){
            return i + 1;
        }
    }
    return 0;
}
Point px(Point xy, int a, int mod, int id_p, int mult){
    Point buff;
    if(mult == 0){
        return buff;
    }else if(mult == 1){
        buff.x[0] = xy.x[id_p - 1];
        buff.y[0] = xy.y[id_p - 1];
        return buff;
    }else{
        buff.x[0] = xy.x[id_p - 1];
        buff.y[0] = xy.y[id_p - 1];

        for(int i = 0; i < mult - 1; i++){
            cout << i + 2 << "X: ";
            if(buff.x[0] == xy.x[id_p - 1] && buff.y[0] == xy.y[id_p - 1]){
                buff = pp(xy, a, mod, id_p);
            }else{
                
                buff = pq(xy, mod, id_p, search_id_in_points(xy, buff));
            }

            cout << "{" << buff.x[0] << ", " << buff.y[0] << "}" << endl;
        }
    }
    return buff;
}
bool ecc(int a, int b, int mod){
    if (test_singulyar(a, b, mod) == true) return false;
    Point qwe = generate_points(a, b, mod), buff;
    int select = 0;
    int p, q;
    int mult = 0;
    while(true){
        visual_generate_points(a, b, mod);
        cout << "\n----------------------------------------\n";
        cout << "Format - №{x, y} | " << "O{∞, ∞} " << endl;
        for(int i = 0; i < size_P(qwe); i++){
            cout << i + 1;
            print_P(qwe, i);
        }
        cout << "\n----------------------------------------\n";

        cout << "\nSelect:\n1 - P + P\n2 - P + Q\n3 - Px\n4 - Exit\n";
        cin >> select;
        switch(select){
            case 1:
                cout << "Number point: ";
                select = 0;
                cin >> select;
                buff = pp(qwe, a, mod, select);
                print_P(buff,0);
                break;
            case 2:
                cout << "Number points: ";
                cin >> p >> q;
                buff = pq(qwe, mod, p, q);
                print_P(buff,0);
                break;
            case 3:
                cout << "Number point: ";
                select = 0;
                cin >> select;
                cout << "Factor: ";
                cin >> mult;
                buff = px(qwe, a, mod, select, mult);
                break;
            case 4:
                return false;
            default:
                return false;
        }
        cout << "\n----------------------------------------\n";
    }
    return false;
}

int main(void){
    return ecc(2, 1, 5); // a, b, mod;
}
