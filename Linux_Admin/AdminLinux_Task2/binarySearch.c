#include<stdio.h>
int binary_search(int *arr, int element, int length)
{
	int start=0, end=length-1, middle=(start+end)/2;
	while(start<=end)
	{
		if(element == arr[middle])
		{
			return middle;
		}
		else if(element < arr[middle])
		{
			end=middle-1;
		}
		else
		{
			start=middle+1;
		}
	}
	return -1;
}

int main()
{
	int arr[5]={4,6,9,15,17};
	int index=binary_search(arr,9,5);
	if(index!=-1)
	{
		printf("The element found at index %d\n",index);
	}
	else
	{
		printf("The element not found\n");
	}
}
