#include <stdio.h>
int a[10],n;
void quicksort(int left,int right)
{

int i,j,t,temp;
i=left;
j=right;
temp=a[left];
while(i!=j)
{
	//要从右往左开始！
	while(a[j]>=temp && i<j)
		j--;
	while(a[i]<=temp && i<j)
		i++;
	if(i<j)
	{
		t=a[i];a[i]=a[j];a[j]=t;
	}
}
//基准数归位
a[left]=a[i];
a[i]=temp;
//递归处理以基准数为划分的两旁的数
quicksort(left,i-1);
quicksort(i+1,right);
}
int main()
{
int i,j,t;
scanf("%d",&n);
getchar();
for(i=1;i<=n;i++)
	scanf("%d",&a[i]);
printf("\nyes\n");
quicksort(1,n);
printf("chulaile");
for(i=1;i<=n;i++)
	printf("%d\t",a[i]);
getchar();
getchar();
return 0;
} 