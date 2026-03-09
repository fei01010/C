#include<stdio.h>
void MoveSingle(char p,char q){
	printf("Move disk from %c to %c\n",p,q);
}
//n为移动盘个数，p原位置，q目标位置，m空闲 
void MoveN(int n,char p,char q,char m){
	if(n==1){
		MoveSingle(p,q);
	}
	else if(n==2){
		MoveSingle(p,m);
		MoveSingle(p,q);
		MoveSingle(m,q);
	}
	else if(n>2){
		MoveN(n-1,p,m,q);
		MoveSingle(p,q);
		MoveN(n-1,m,q,p);		
	}
}

int main(){
	int n;
	do{
		scanf("%d",&n);
	}while(n<1||n>10);
	char a='A',b='B',c='C';
	MoveN(n-1,a,b,c);
	MoveSingle(a,c);
	MoveN(n-1,b,c,a);
	return 0;
} 
//n=1,a-c
//n=2,a-b,a-c,(此时与n=1只将ab互换)b-c;
//n=3,a-c,a-b,c-b,a-c,(此时与n=2只将ab互换)b-a,b-c,a-c;
//n=4,a-b,a-c,b-c,a-b,c-a,c-b,a-b,a-c,(此时与n=3，只将ab互换),b-c,b-a,c-a,b-c,a-b,a-c,b-c 
//n=5,a-c,a-b,c-b,a-c,b-a,b-c,a-c,a-b,c-b,c-a,b-a,c-b,a-c,a-b,c-a,a-c(此时与n=5只将ab互换)