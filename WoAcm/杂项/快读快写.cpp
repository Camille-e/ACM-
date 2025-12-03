#include<bits/stdc++.h>
template<typename T>
inline void read(T &x) {
    int w = 1; x = 0;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-') w = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    x = x * w;
}
template<typename T>
inline void write1(T x){
    if(x<0){ putchar('-'); x=(~x)+1;}
    if(x>=10){ write(x/10);}
    write(x%10^48); //+'0'是为了让数字类型的x%10变成字符输出
}

inline void write2(int x){
    static int st[32] = {0}; // int 最多32位
    int top = 0; // 指向栈顶的指针
    do{
        st[top++]=x%10;
        x/=10;
    }while(x>0);
    while(top>0){ putchar(st[--top]^48);}
}