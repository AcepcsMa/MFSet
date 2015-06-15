#include<stdlib.h>
#include<stdio.h>
typedef int Status;
typedef struct MFSET
{
    int *parent;
    int n;
}MFSet;

//初始化并查集
Status Init_MFSet(MFSet &S,int n)
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

//用已存在的3个集合来填充一个并查集
void Make_MFSet(MFSet &S,int *arr1,int size1,int *arr2,int size2,int *arr3,int size3)
{
    int i,temp = 1;
    for(i = 1;i < size1;i++)    //默认将每个集合的第一个元素作为代表元，所以无需处理arr[0]
    {
        while(temp == i)
        {
            temp = rand()%size1;    
        }
        S.parent[arr1[i]] = arr1[i-1];  //按顺序一个一个安排其parent
        if(i == size1-1)    //当填充到该集合的最后一个时就随意安排一个parent
        {
            S.parent[arr1[i]] = arr1[temp];
        }    
    }
    for(i = 1,temp = 1;i < size2;i++)
    {
        while(temp == i)
        {
            temp = rand()%size2;
        }
        S.parent[arr2[i]] = arr2[i-1];
        if(i == size2-1)
        {
            S.parent[arr2[i]] = arr2[temp];
        }
    }
    for(i = 1,temp = 1;i < size3;i++)
    {
        while(temp == i)
        {
            temp = rand()%size3;
        }
        S.parent[arr3[i]] = arr3[i-1];
        if(i == size3-1)
        {
            S.parent[arr3[i]] = arr3[temp];
        }
    }
}

//填充带权并查集，具体细节基本同上
void Make_MFSet_WUR(MFSet &S,int *arr1,int size1,int *arr2,int size2,int *arr3,int size3)
{
    int i,temp = 1;
    S.parent[arr1[0]] = -(size1);   //因为带权，所以要对代表元进行处理，arr[0]不再是-1
    for(i = 1;i < size1;i++)
    {
        while(temp == i)
        {
            temp = rand()%size1;    
        }
        S.parent[arr1[i]] = arr1[i-1];
        if(i == size1-1)
        {
            S.parent[arr1[i]] = arr1[temp];
        }    
    }
    S.parent[arr2[0]] = -(size2);
    for(i = 1,temp = 1;i < size2;i++)
    {
        while(temp == i)
        {
            temp = rand()%size2;
        }
        S.parent[arr2[i]] = arr2[i-1];
        if(i == size2-1)
        {
            S.parent[arr2[i]] = arr2[temp];
        }
    }
    S.parent[arr3[0]] = -(size3);
    for(i = 1,temp = 1;i < size3;i++)
    {
        while(temp == i)
        {
            temp = rand()%size3;
        }
        S.parent[arr3[i]] = arr3[i-1];
        if(i == size3-1)
        {
            S.parent[arr3[i]] = arr3[temp];
        }
    }
}

//摧毁并查集
Status DestroyMFSet(MFSet &S)
{
    if (S.parent)
    {
        free(S.parent);
        S.n = 0;
        printf("Destroy Finished\n");
        return 1;
    }
    else    //要检查并查集是否已存在，不然乱销毁空间会引起异常中断
    {
        printf("Set is already empty\n");
        return -1;
    }
}

//“查“操作，没用书上的循环算法，使用递归
int FindMFSet(MFSet &S, int i)
{
    if (i < 0 || i > S.n)
    {
        printf("Error perimeter\n");
        return -1;
    }
    if (S.parent[i] < 0)
        return i;
    return FindMFSet(S, S.parent[i]);   //递归调用
}

//合并操作
Status UnionMFSet(MFSet &S, int i, int j)
{
    if (i < 0 || i > S.n || j < 0 || j > S.n)
    {
        printf("Error perimeter\n");
        return -1;
    }
    if (FindMFSet(S, i) == FindMFSet(S, j))
    {
        printf("i and j are in the Same Set\n");
        return -1;
    }
    S.parent[FindMFSet(S,i)] = FindMFSet(S,j);
    return 1;
}

//带权并查集合并
Status UnionMFSet_WUR(MFSet &S, int i, int j)
{
    if (i < 0 || i > S.n || j < 0 || j > S.n)
    {
        printf("Error parameter\n");
        return -1;
    }
    int ri, rj;
    ri = FindMFSet(S, i);
    rj = FindMFSet(S, j);
    if (ri == rj)
    {
        printf("i and j are in the Same Set\n");
        return -1;
    }
    if (S.parent[ri] > S.parent[rj])
    {
        S.parent[rj] += S.parent[ri];   //关键点要对代表元的权值进行修改
        S.parent[ri] = rj;
    }
    else
    {
        S.parent[ri] += S.parent[rj];
        S.parent[rj] = ri;
    }
    return 1;
}

//压缩路径查找法
int FindMFSet_PC(MFSet &S, int i)
{
    if (i < 0 || i >= S.n)
    {
        return -1;
    }
    if (S.parent[i] < 0)
    {
        return i;
    }
    S.parent[i] = FindMFSet_PC(S, S.parent[i]);
    return S.parent[i];
}

//打印集合的函数
void Print_Array(int *arr,int size)
{
    int i = 0;
    for(i = 0;i < size;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n\n");
}

//集合复制函数
void Copy_Array(int *obj,int *arr,int begin,int end)
{
    int i = 0;
    for(i = 0;begin != end;i++)
    {
        obj[i] = arr[begin++];
    }
}

//main函数，进行测试
void main()
{   
    int total_size,size1,size2,size3;
    int change_times = rand()%30 + 1;
    int i,j,k,temp;    
    int *array,*arr1,*arr2,*arr3;
    total_size = rand()%30 + 1;
    array = (int *)malloc(sizeof(int) * total_size);
    
    //初始化一个连续完整序列
    for(i = 0;i < total_size;i++)
    {
        array[i] = i;
    }
    //随机交换change_times次，打乱原有次序再进行划分，以产生多个不相交的集合
    for(i = 0;i < change_times;i++)
    {
        j = rand()%total_size;
        k = rand()%total_size;
        temp = array[j];
        array[j] = array[k];
        array[k] = temp;
    }
            
    //以下初始化3个随机集合
    size1 = rand()%total_size;
    arr1 = (int *)malloc(sizeof(int) * size1);
    Copy_Array(arr1,array,0,size1);
    
    size2 = rand()%(total_size - size1);
    arr2 = (int *)malloc(sizeof(int) * size2);
    Copy_Array(arr2,array,size1,size1+size2);
    
    size3 = total_size - size1 - size2;
    arr3 = (int *)malloc(sizeof(int) * size3);
    Copy_Array(arr3,array,size1+size2,total_size);
    
    //打印3个随机初始化出来的集合
    Print_Array(array,total_size);
    printf("Set#A: ");
    Print_Array(arr1,size1);
    printf("Set#B: ");
    Print_Array(arr2,size2);
    printf("Set#C: ");
    Print_Array(arr3,size3);

    //初始化MFSet
    MFSet Set;
    Init_MFSet(Set,total_size);
    
    //随机生成两个查询数
    int num1 = rand()%total_size;
    int num2 = rand()%total_size;

    //Normal Rule
    //DestroyMFSet(Set);
    
    Make_MFSet(Set,arr1,size1,arr2,size2,arr3,size3);
    printf("MFSet: ");
    Print_Array(Set.parent,Set.n);
    printf("'%d' belongs to '%d'\n",num1,FindMFSet(Set, num1));
    printf("'%d' belongs to '%d'\n",num2,FindMFSet(Set, num2));
    printf("After Union:\n");
    UnionMFSet(Set, num1, num2);
    printf("MFSet: ");
    Print_Array(Set.parent,Set.n);
    //压缩路径查找
    printf("'%d' belongs to '%d'\n",num1,FindMFSet_PC(Set, num1));
    printf("After path compression:\nMFSet: ");
    Print_Array(Set.parent,Set.n);                             
    
    
    //Weighted Union Rule
    //DestroyMFSet(Set);
    /*
    Make_MFSet_WUR(Set,arr1,size1,arr2,size2,arr3,size3);
    printf("MFSet: ");
    Print_Array(Set.parent,Set.n);
    printf("'%d' belongs to '%d'\n",num1,FindMFSet(Set, num1));
    printf("'%d' belongs to '%d'\n",num2,FindMFSet(Set, num2));
    printf("After Union:\n");
    UnionMFSet_WUR(Set, num1, num2);
    printf("MFSet: ");
    Print_Array(Set.parent,Set.n);
    //压缩路径查找
    printf("'%d' belongs to '%d'\n",num1,FindMFSet_PC(Set, num1));
    printf("After path compression:\nMFSet: ");
    Print_Array(Set.parent,Set.n);
    */
}
