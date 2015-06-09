#include"MFSet.h"
#include"MFSet_weighted.h"

Status IsInSet(int *arr,int size,int num)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		if (num == arr[i])
			return 1;
	}
	return 0;
}
int main()
{
	int size1, size2, size3,total_size;
	int *arr1, *arr2, *arr3;
	int temp = 0;
	int i = 0;
	size1 = (rand() % 10) + 1;
	size2 = (rand() % 10) + 1;
	size3 = (rand() % 10) + 1;
	total_size = size1 + size2 + size3;
	MFSet Set;
	Init_MFSet(Set, 9);
	Set.parent[0] = -1;
	Set.parent[1] = -1;
	Set.parent[2] = 1;
	Set.parent[3] = -1;
	Set.parent[4] = 1;
	Set.parent[5] = 3;
	Set.parent[6] = 0;
	Set.parent[7] = 4;
	Set.parent[8] = 3;

	Weighted_MFSet WSet;
	Init_Weighted_MFSet(WSet, 9);
	WSet.parent[0] = -2;
	WSet.parent[1] = -4;
	WSet.parent[2] = 1;
	WSet.parent[3] = -3;
	WSet.parent[4] = 1;
	WSet.parent[5] = 3;
	WSet.parent[6] = 0;
	WSet.parent[7] = 4;
	WSet.parent[8] = 3;

	//Normal Rule
	//DestroyMFSet(Set);
	printf("%d\n", FindMFSet(Set, 8));
	printf("%d\n", FindMFSet(Set, 6));
	Union(Set, 8, 6);
	printf("%d\n", FindMFSet(Set, 6));

	//Weighted Union Rule
	printf("%d\n", FindWeighted_MFSet(WSet, 8));
	printf("%d\n", FindWeighted_MFSet(WSet, 6));
	Union_Weighted_MFSet(WSet, 8, 6);
	printf("%d\n", FindWeighted_MFSet(WSet, 6));
	system("pause");
	return 0;
}