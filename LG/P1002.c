#include<stdio.h>
#include<stdlib.h>
int IsNearHorse(int x, int y, int c, int d){
    if((x == c && y == d) || (abs(x - c) + abs(y - d) == 1)){
        return -1;
    }else{
        return 1;
    }
}

int CalculateWays(int x, int y, int a, int b, int c, int d){
    if(abs(x - a) + abs(y - b) == 1 && IsNearHorse(x, y, c, d) == 1){
        return 1;
    }else{
        return CalculateWays(x + 1, y, a, b, c, d) + CalculateWays(x, y + 1, a, b, c, d);
    }
}
int main(){
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    //恭喜获得了B点的坐标(a,b)和马的坐标(c,d)
    int method = CalculateWays(0, 0, a, b, c, d);
    printf("%d",method);
    return 0;
}