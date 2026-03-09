#include<stdio.h>
int Deficit(int left,int right,int nums[]);
int main(){
    int n;
    do{
        scanf("%d",&n);
    }while(n<1);
    int nums[n];
    for(int i=0;i<n;i++){
        scanf("%d",&nums[i]);
    }
    int len=sizeof(nums)/sizeof(nums[0]);
    if(Deficit(0,len-1,nums)>=0)printf("true");
    else printf("false");
    return 0;
}
int Deficit(int left,int right,int nums[]){
    int LeftChoose,RightChoose;
    if(left==right)return nums[left];
    else if(left<right){
        LeftChoose=nums[left]-Deficit(left+1,right,nums);
        RightChoose=nums[right]-Deficit(left,right-1,nums);
        return LeftChoose>=RightChoose ? LeftChoose:RightChoose;
    }
}
// 【题目描述】 给你一个整数数组 nums 。玩家 1 和玩家 2 基于这个数组设计了一个游戏。 玩家 1 和玩家 2 轮流进行自己的回合，玩家 1 先手。开始时，两个玩家的初始分值都是 0 。每一回合，玩家从数组的任意一端取一个数字（即nums[0] 或 nums[nums.length - 1]），取到的数字将会从数组中移除（数组长度减 1 ）。玩家选中的数字将会加到他的得分上。当数组中没有剩余数字可取时，游戏结束。 如果玩家 1 能成为赢家，返回 true 。如果两个玩家得分相等，同样认为玩家 1 是游戏的赢家，也返回 true 。你可以假设每个玩家的玩法都会使他的分数最大化。 请你编写递归函数解决这个问题。

// 【输入描述】

// 第一行为整数n，表示数组长度，
// 第二行为数组nums的元素。
// 【输出描述】

// // true或者false