#include<stdlib.h>
#include<stdio.h>
typedef int Status;
typedef struct Weighted_MFSet
{
	int *parent;
	int n;
}Weighted_MFSet;

Status Init_Weighted_MFSet(Weighted_MFSet &S, int n)
{
	if (n <= 0)
	{
		printf("Error perimeter\n");
		S.parent = NULL;
		return -1;
	}
	S.parent = (int *)malloc(sizeof(int)* n);
	if (!S.parent)
	{
		printf("Malloc Error!\n");
		return -1;
	}
	S.n = n;
	for (int i = 0; i < n; i++)
	{
		S.parent[i] = -1;
	}
	return 1;
}

Status DestroyWeighted_MFSet(Weighted_MFSet &S)
{
	if (S.parent)
	{
		free(S.parent);
		S.n = 0;
		printf("Destroy Finished\n");
		return 1;
	}
	else
	{
		printf("Set is already empty\n");
		return -1;
	}
}

int FindWeighted_MFSet(Weighted_MFSet &S, int i)
{
	if (i < 0 || i > S.n)
	{
		printf("Error perimeter\n");
		return -1;
	}
	if (S.parent[i] < 0)
		return i;
	return FindWeighted_MFSet(S, S.parent[i]);
}

Status Union_Weighted_MFSet(Weighted_MFSet &S, int i, int j)
{
	if (i < 0 || i > S.n || j < 0 || j > S.n)
	{
		printf("Error perimeter\n");
		return -1;
	}
	int ri, rj;
	ri = FindWeighted_MFSet(S, i);
	rj = FindWeighted_MFSet(S, j);
	if (ri == rj)
	{
		printf("i and j are in the Same Set\n");
		return -1;
	}
	if (S.parent[ri] > S.parent[rj])
	{
		S.parent[rj] += S.parent[ri];
		S.parent[ri] = rj;
	}
	else
	{
		S.parent[ri] += S.parent[rj];
		S.parent[rj] = ri;
	}
	return 1;
}