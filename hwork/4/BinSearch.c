#include<stdio.h>
int  BinSearch(long num[], long x, int n) 
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = low+(high-mid)/2;   // 填空①

		if (x > num[mid])
		{
			low = mid + 1;
		}
		else if (x < num[mid])
		{
			high = mid - 1;
		}
		else
		{
			return low;        // 填空②
		}
	}
	return -1;
}

int main(){
    return 0;
}