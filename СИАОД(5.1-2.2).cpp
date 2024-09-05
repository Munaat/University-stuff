#include <iostream>
#include <bitset>
using namespace std;

void print(unsigned char obj){cout << bitset<8>{obj} << endl;}

void add(unsigned char (&obj)[8], int i){
    if(i >= 0 && i < 64) obj[i/8] |= (1<<(i%8));
}

void sorted(unsigned char obj[8]){
    for(int j = 0;j<8;j++) {
        bitset<8> s{obj[j]};
        for (int i = 0; i < 8; i++) {
            if (s[i]) cout << i+(j*8) << ' ';
        }
    }
}

int main() {
    unsigned char a[8]{0};
    int b[15]{32, 63, 29, 20, 43, 47, 2, 40, 5, 22, 4, 23, 60, 45, 9};
    for(int i : b){add(a, i);}
    sorted(a);
}

