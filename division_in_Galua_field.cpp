#include <iostream>
#include <math.h>
using namespace std;
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
void division(u_int64_t dividend, u_int64_t divider){
    u_int64_t q = 0, r = 0;
    print_p(dividend);
    cout << " / ";
    print_p(divider);
    cout << '\n';
    while(dividend > divider){
        size_t buff = 0;
        for (size_t i = 0; i < counter_bite(divider); i++)
        {   
            q |= 1 << (counter_bite(dividend) - counter_bite(divider));
            buff ^= (1 << (counter_bite(dividend) - counter_bite(divider))) * ((((divider >> (counter_bite(divider) - 1) - i)) & 0x01) << (counter_bite(divider) - 1) - i);
        }
        dividend ^= buff;
    }
    cout << "q = ";
    print_p(q);
    cout << " | r = ";
    print_p(dividend);
    cout << '\n';
}
int main(void){
    division(4229,527); //  1000010000101 / 1000001111 = x12 + x7 + x2 + 1 / x9 + x3 + x2 + x + 1
    
    return 0;
}