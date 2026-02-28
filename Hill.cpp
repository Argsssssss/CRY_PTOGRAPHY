#include <iostream>
#include <math.h>
#define minors11(a,b){b[0] = a[1][1] * a[2][2] - a[2][1] * a[1][2];}
#define minors12(a,b){b[1] = a[1][0] * a[2][2] - a[2][0] * a[1][2];}
#define minors13(a,b){b[2] = a[1][0] * a[2][1] - a[2][0] * a[1][1];}
#define minors21(a,b){b[3] = a[0][1] * a[2][2] - a[2][1] * a[0][2];}
#define minors22(a,b){b[4] = a[0][0] * a[2][2] - a[2][0] * a[0][2];}
#define minors23(a,b){b[5] = a[0][0] * a[2][1] - a[2][0] * a[0][1];}
#define minors31(a,b){b[6] = a[0][1] * a[1][2] - a[1][1] * a[0][2];}
#define minors32(a,b){b[7] = a[0][0] * a[1][2] - a[1][0] * a[0][2];}
#define minors33(a,b){b[8] = a[0][0] * a[1][1] - a[1][0] * a[0][1];}

class Hill{
    private:
        int _A[9], _mod, _del_K, _inverse_k[3][3], _ch[3] = {0,0,0}, _mes[3] = {0,0,0};
        int negative_module(int num){
            if(num < 0){
                while(num < 0){
                    num += _mod;
                }
                return num;
            }else{
                return num % _mod;
            }
        }
        
        void Mij(int i, int j, int key[3][3]){
            if(i == 0 and j == 0){minors11(key,_A)}
            else if(i == 0 and j == 1){minors12(key,_A)}
            else if(i == 0 and j == 2){minors13(key,_A)}
            else if(i == 1 and j == 0){minors21(key,_A)}
            else if(i == 1 and j == 1){minors22(key,_A)}
            else if(i == 1 and j == 2){minors23(key,_A)}
            else if(i == 2 and j == 0){minors31(key,_A)}
            else if(i == 2 and j == 1){minors32(key,_A)}
            else{minors33(key,_A)}
        }
    	void alg_dls(int key[3][3]) {
    		int k = 0;
    		for (int i = 0; i < 3; i++) {
    			for (int j = 0; j < 3; j++) {
    			    Mij(i,j,key);
    				_A[k] = negative_module(pow(-1, i + j) * _A[k]);
    				k++;
    			}
    		}
    	}
    	int inverse_num(int num){
    	    int x[num / 2] = {1,0},q,r, m = _mod;
    	    for (int i = 2; ; i++) {
    	        q = num / m;
    	        r = num % m;
    	        x[i] = x[i - 2] - q * x[i - 1];
    	        num = m;
    	        m = r;
    	        if(r == 0){
    	            return negative_module(x[i - 1]);
    	        }
    	    }
    	    return 0;
    	}
    	void inverse_matrix(){
    	    int k = 0;
    	    for (int i = 0; i < 3; i++){
    	        for (int j = 0; j < 3; j++) {
    	            _inverse_k[j][i] = _A[k] * _del_K;
    	            _inverse_k[j][i] %= _mod;
    	            k++;
    	        }
    	    }
    	}
    	void encrypt(int key[3][3], int mes[]){
    	    for (int i = 0, k = 0; i < 3; i++) {
    	        for (int j = 0; j < 3; j++) {
    	            _ch[k] += mes[j] * key[i][j];
    	            _ch[k] %= _mod;
    	           if(j % 2 == 0 and j != 0){
    	               k++;
    	           }
    	        }
    	    }
    	}
    	void decrypt(){
    	    for (int i = 0, k = 0; i < 3; i++) {
    	        for (int j = 0; j < 3; j++) {
    	            _mes[k] += _ch[j] *  _inverse_k[i][j];
    	            _mes[k] %= _mod;
    	            if(j % 2 == 0 and j != 0){
    	               k++;
    	           }
    	        }
    	    }
    	}
    	void decrypt(int ch[]){
    	    for (int i = 0, k = 0; i < 3; i++) {
    	        for (int j = 0; j < 3; j++) {
    	            _mes[k] += ch[j] *  _inverse_k[i][j];
    	            _mes[k] %= _mod;
    	            if(j % 2 == 0 and j != 0){
    	               k++;
    	           }
    	        }
    	    }
    	}
    public:
        Hill(int key[3][3],int mes[], int mod, char action){
            _mod = mod;
            alg_dls(key);
            _del_K = inverse_num(negative_module(key[0][0] * _A[0] + key[0][1] * _A[1] + key[0][2] * _A[2]));
            inverse_matrix();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    std::cout << _inverse_k[i][j] << "|";
                }
                std::cout << " " << std::endl;
            }
            switch(action){
                case 'e':
                    encrypt(key,mes);
                    for (int i = 0; i < 3; i++) {
                        std::cout << _ch[i] << std::endl;
                    }
                    decrypt();
                    for (int i = 0; i < 3; i++) {
                        std::cout << char(_mes[i]) << std::endl;
                    }
                    break;
                case 'd':
                    decrypt(mes);
                    for (int i = 0; i < 3; i++) {
                        std::cout << _mes[i] << std::endl;
                    }
            }
        }
};
int main()
{
	int key[3][3] =
	{	      //0 1 2
		/* 0 */{41,2,59},
		/* 1 */{12,41,72},
		/* 2 */{5,94,77}}, mes[] = {65,66,67};
	Hill Bel{key, mes, 131, 'e'};
    
	return 0;
}