#include <iostream>
#include <bitset>
using namespace std;

void print(unsigned char obj){cout << bitset<8>{obj} << endl;}

void add(unsigned char &obj, int i){
    if(i >= 0 && i < 8) obj |= (1<<i);
}

void sorted(unsigned char obj){
    bitset<8> s {obj};
    for(int i = 0;i<8;i++){
        if(s[i]) cout << i << ' ';
    }
}

int main() {
    unsigned char a = 0;
    int b[6]{1, 0, 5, 7, 2, 4};
    print(a);
    for(int i : b){add(a, i);}
    print(a);
    sorted(a);
}

