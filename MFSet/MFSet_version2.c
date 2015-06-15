#include<stdlib.h>
#include<stdio.h>
typedef int Status;
typedef struct MFSET
{
    int *parent;
    int n;
}MFSet;

//��ʼ�����鼯
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

//���Ѵ��ڵ�3�����������һ�����鼯
void Make_MFSet(MFSet &S,int *arr1,int size1,int *arr2,int size2,int *arr3,int size3)
{
    int i,temp = 1;
    for(i = 1;i < size1;i++)    //Ĭ�Ͻ�ÿ�����ϵĵ�һ��Ԫ����Ϊ����Ԫ���������账��arr[0]
    {
        while(temp == i)
        {
            temp = rand()%size1;    
        }
        S.parent[arr1[i]] = arr1[i-1];  //��˳��һ��һ��������parent
        if(i == size1-1)    //����䵽�ü��ϵ����һ��ʱ�����ⰲ��һ��parent
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

//����Ȩ���鼯������ϸ�ڻ���ͬ��
void Make_MFSet_WUR(MFSet &S,int *arr1,int size1,int *arr2,int size2,int *arr3,int size3)
{
    int i,temp = 1;
    S.parent[arr1[0]] = -(size1);   //��Ϊ��Ȩ������Ҫ�Դ���Ԫ���д���arr[0]������-1
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

//�ݻٲ��鼯
Status DestroyMFSet(MFSet &S)
{
    if (S.parent)
    {
        free(S.parent);
        S.n = 0;
        printf("Destroy Finished\n");
        return 1;
    }
    else    //Ҫ��鲢�鼯�Ƿ��Ѵ��ڣ���Ȼ�����ٿռ�������쳣�ж�
    {
        printf("Set is already empty\n");
        return -1;
    }
}

//���顰������û�����ϵ�ѭ���㷨��ʹ�õݹ�
int FindMFSet(MFSet &S, int i)
{
    if (i < 0 || i > S.n)
    {
        printf("Error perimeter\n");
        return -1;
    }
    if (S.parent[i] < 0)
        return i;
    return FindMFSet(S, S.parent[i]);   //�ݹ����
}

//�ϲ�����
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

//��Ȩ���鼯�ϲ�
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
        S.parent[rj] += S.parent[ri];   //�ؼ���Ҫ�Դ���Ԫ��Ȩֵ�����޸�
        S.parent[ri] = rj;
    }
    else
    {
        S.parent[ri] += S.parent[rj];
        S.parent[rj] = ri;
    }
    return 1;
}

//ѹ��·�����ҷ�
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

//��ӡ���ϵĺ���
void Print_Array(int *arr,int size)
{
    int i = 0;
    for(i = 0;i < size;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n\n");
}

//���ϸ��ƺ���
void Copy_Array(int *obj,int *arr,int begin,int end)
{
    int i = 0;
    for(i = 0;begin != end;i++)
    {
        obj[i] = arr[begin++];
    }
}

//main���������в���
void main()
{   
    int total_size,size1,size2,size3;
    int change_times = rand()%30 + 1;
    int i,j,k,temp;    
    int *array,*arr1,*arr2,*arr3;
    total_size = rand()%30 + 1;
    array = (int *)malloc(sizeof(int) * total_size);
    
    //��ʼ��һ��������������
    for(i = 0;i < total_size;i++)
    {
        array[i] = i;
    }
    //�������change_times�Σ�����ԭ�д����ٽ��л��֣��Բ���������ཻ�ļ���
    for(i = 0;i < change_times;i++)
    {
        j = rand()%total_size;
        k = rand()%total_size;
        temp = array[j];
        array[j] = array[k];
        array[k] = temp;
    }
            
    //���³�ʼ��3���������
    size1 = rand()%total_size;
    arr1 = (int *)malloc(sizeof(int) * size1);
    Copy_Array(arr1,array,0,size1);
    
    size2 = rand()%(total_size - size1);
    arr2 = (int *)malloc(sizeof(int) * size2);
    Copy_Array(arr2,array,size1,size1+size2);
    
    size3 = total_size - size1 - size2;
    arr3 = (int *)malloc(sizeof(int) * size3);
    Copy_Array(arr3,array,size1+size2,total_size);
    
    //��ӡ3�������ʼ�������ļ���
    Print_Array(array,total_size);
    printf("Set#A: ");
    Print_Array(arr1,size1);
    printf("Set#B: ");
    Print_Array(arr2,size2);
    printf("Set#C: ");
    Print_Array(arr3,size3);

    //��ʼ��MFSet
    MFSet Set;
    Init_MFSet(Set,total_size);
    
    //�������������ѯ��
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
    //ѹ��·������
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
    //ѹ��·������
    printf("'%d' belongs to '%d'\n",num1,FindMFSet_PC(Set, num1));
    printf("After path compression:\nMFSet: ");
    Print_Array(Set.parent,Set.n);
    */
}
