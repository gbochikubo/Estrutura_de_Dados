#include <iostream>

//AND &
//OR |
//NOT ~
//XOR ^
//SHIFT << >> 

using namespace std;

int bit(int numero, int pos){
    return (numero >> pos) & 1;
}

int seta(int numero, int pos){
    //setar é mudar para 1
    return (1 << pos) | numero;
}

int resetar(int numero, int pos){
    //resetar é mudar para 0
    return ~(1 << pos) & numero;
}


int main (){
    
    
    int x;
    x = ',';
    cout << x << endl;
    
    //~ for(int i = 3; i >= 0; i--){
    //~ cout <<bit (10,i);
    //~ }
    
    
    
    
    
    
    return 0;
}
