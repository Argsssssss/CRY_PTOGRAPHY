#include <iostream>
#include <math.h>
using namespace std;
struct quotient_and_remainder{u_int64_t r, q;};
u_int64_t counter_bite(u_int64_t hex){
    u_int64_t buff = 0;
    for (size_t i = 0; i < 65; i++)
    {   
        hex - (pow(2, 64 - i)) >= 0 ? buff++ : 0;
    }
    return buff;
}
void print_p(u_int64_t num){
    size_t num_size = counter_bite(num);
    string buff(num_size * 2, '\0');
    for (size_t i = 1; i < num_size + 1; i++)
    {   
        if(num - (pow(2, num_size - i)) >= 0){
            num -= (pow(2, num_size - i));
            num_size - i != 0 ? buff += 'x' + to_string(num_size - i) + '+' : buff += '1';
        }
    }
    buff.size() != 0 ? buff[buff.size() - 1] != '1' ? buff[buff.size() - 1] = char(NULL) : 0 : 0;
    cout << buff;
}
u_int64_t multiplee(u_int64_t numb, u_int64_t mult){
    u_int64_t buff = 0;
    for (size_t i = 0; i < counter_bite(numb); i++)
    {
        for (size_t j = 0; j < counter_bite(mult); j++)
        {
            buff ^= ((((numb >> (counter_bite(numb) - 1) - i)) & 0x01) << (counter_bite(numb) - 1) - i) * ((((mult >> (counter_bite(mult) - 1) - j)) & 0x01) << (counter_bite(mult) - 1) - j);
        }
    }
    return buff;
}
quotient_and_remainder division(u_int64_t dividend, u_int64_t divider){
    quotient_and_remainder qt_rm = {0,0};
    print_p(dividend);
    cout << " / ";
    print_p(divider);
    cout << "\n";
    while(((dividend >> counter_bite(dividend) - 1) << counter_bite(dividend) - 1) >= (divider >> counter_bite(divider) - 1) << counter_bite(divider) - 1){
        if(qt_rm.q == 1){break;}
        size_t buff = 0;
        for (size_t i = 0; i < counter_bite(divider); i++)
        {   
            qt_rm.q |= 1 << (counter_bite(dividend) - counter_bite(divider));
            buff ^= (1 << (counter_bite(dividend) - counter_bite(divider))) * ((((divider >> (counter_bite(divider) - 1) - i)) & 0x01) << (counter_bite(divider) - 1) - i);
            // cout << qt_rm.q << " | " << buff << endl;
        }
        dividend ^= buff;
    }
    qt_rm.r = dividend;
    cout << "q = ";
    print_p(qt_rm.q);
    cout << " | r = ";
    print_p(dividend);
    cout << '\n';
    return qt_rm;
}
void eqlid(u_int64_t ax, u_int64_t px){
    quotient_and_remainder qt_rm = {ax,px};
    u_int64_t buff_r, v0 = 0, v1 = 1, vi = 0, buff_ax = ax, buff_px = px;

    while (qt_rm.r != 1)
    {   buff_r = qt_rm.r;
        qt_rm = division(qt_rm.q, qt_rm.r);
        vi = v0 ^ (multiplee(qt_rm.q,v1));
        v0 = v1; 
        v1 = vi;
        qt_rm.q = buff_r;
    }
    if(division(multiplee(buff_ax,vi), buff_px).r == 1){
        cout << "Inverse number - ";
        print_p(vi);
        cout << '\n';
    }else{cout << "Inverse nimber bad(";}
}
int main(void){

    eqlid(167,3587); // 1 аргумент, полином, которому требуется вычислить обратный элемент, 2 аргумент - модуль
    return 0;
}