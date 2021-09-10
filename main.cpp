#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void insertSort(vector<int> nums)
{
    int n = nums.size();

    for(int i = 1; i < n; i++)
    {
        int j = i - 1;
        int temp = nums[i];

        /*
        while(j >= 0 && temp < nums[j])
        {
            nums[j+1] = nums[j];
            j--;
        }

        nums[j+1] = temp;
        //*/

        //* 直接插入
        while(j >= 0 && temp < nums[j])
            j--;

        nums.insert(nums.begin()+j+1, temp);
        nums.erase(nums.begin()+i+1);

    }
}

void shellSort(vector<int> nums)
{
    int n = nums.size();

    int d = n >> 1;

    while(d > 0)
    {
        for(int i = d; i < n; i++)
        {
            int temp = nums[i];
            int k = i - d;

            while(k >= 0 && nums[k] > temp )
            {
                nums[k + d] = nums[k];
                k-=d;
            }

            nums[k + d] = temp;
        }

        d>>=1;
    }
}

void mergeSort1(vector<int>& nums, int l, int r)
{
    if(l >= r) return;

    int m = ( l + r ) / 2;

    mergeSort1(nums,l,m);
    mergeSort1(nums,m+1,r);

    int i = l, j = m + 1;

    while( i < j && j <= r)
    {
        if(nums[i] > nums[j])
        {
            //*
            int k = j - 1;
            int temp = nums[j];
            while(k != i - 1)
            {
                nums[k + 1] = nums[k];
                k--;
            }
            nums[k+1] = temp;
            //*/

            /*直接插入优化
            nums.insert(nums.begin()+i,nums[j]);
            nums.erase(nums.begin()+j+1);
            //*/

            j++;

        }

        i++;
    }
}

vector<int> temp;

void mergeSort2(vector<int>& nums, int l, int r)
{
    if(l >= r) return;

    int m = ( l + r) / 2;

    mergeSort2(nums,l,m);
    mergeSort2(nums,m+1,r);

    int i = l, j = m + 1;

    for(int k = l; k <= r; k++)
    {
        if(i < m + 1 && j < r + 1)
        {
            if(nums[i] < nums[j])
            {
                temp[k] = nums[i];
                i++;
            }
            else
            {
                temp[k] = nums[j];
                j++;
            }
        }

        else if(i < m + 1)
        {
            temp[k] = nums[i];
            i++;
        }

        else
        {
            temp[k] = nums[j];
            j++;
        }
    }

    for(int k = l; k <= r; k++) nums[k] = temp[k];
}

void binarySort(vector<int>& nums, int l, int r)
{

    if(l >= r) return;


    int temp = nums[l];

    int p = l, q = r;

    while(p < q)
    {
        while(q > p && nums[q] >= temp)
            q--;

        nums[p] = nums[q];

        while(p < q && nums[p] < temp)
            p++;

        nums[q] = nums[p];
    }

    nums[p] = temp;

    binarySort(nums, l, p -1);
    binarySort(nums, p + 1, r);
}

void swiftDown(vector<int>& nums, int p, int n)
{
    int j;
    int temp = nums[p];
    while((j=2*p+1) < n)
    {
        if(j + 1 < n && nums[j] < nums[j+1]) ++j;

        if(nums[j] > temp)
        {
            nums[p] = nums[j];
            p = j;
        }
        else
            break;
    }

    nums[p] = temp;
}

void heapSort(vector<int>& nums)
{
    int n = nums.size();

    int last = n / 2 - 1;

    for(int i = last; i >= 0; i--)
        swiftDown(nums, i, n);

    int len = n;
    while(len > 0)
    {
        swap(nums[0], nums[--len]);
        swiftDown(nums, 0, len);
    }
}

int main() {
    freopen("data1m.txt","r" ,stdin);

    /* 测试排序正确性
    freopen("test.out", "w", stdout);
    //*/

    clock_t timer_b, timer_e;

    int n;
    scanf("%d", &n);

    vector<int> a(n);

    for(auto& i : a)
    {
        scanf("%d", &i);
    }

    //*
    timer_b = clock();
    insertSort(a);
    timer_e = clock();
    printf("insertSort: %f ms\n", difftime(timer_e, timer_b));
    //*/

    //*
    timer_b = clock();
    shellSort(a);
    timer_e = clock();
    printf("shellSort: %f ms\n", difftime(timer_e, timer_b));
    //*/

    /*空间复杂度O(1)，在1m数据大小下跑不了，在其他情况下还慢
     vector<int> b = a;
     timer_b = clock();
     mergeSort1(b, 0, n-1);
     timer_e = clock();
     printf("mergeSort1: %f ms\n", difftime(timer_e, timer_b));
     //*/

    //*空间复杂度O(N)
    vector<int> c = a;
    temp.resize(n);
    timer_b = clock();
    mergeSort2(c, 0, n-1);
    timer_e = clock();
    printf("mergeSort2: %f ms\n", difftime(timer_e, timer_b));
    //*/

    //*
    vector<int> d = a;
    timer_b = clock();
    binarySort(d, 0, n - 1);
    timer_e = clock();
    printf("binarySort: %f ms\n", difftime(timer_e, timer_b));
    //*/

    //*
    timer_b = clock();
    heapSort(a);
    timer_e = clock();
    printf("heapSort: %f ms\n", difftime(timer_e, timer_b));
    //*/

    /*
     for(auto i : a)
         printf("%d\n", i);
     //*/

    return 0;

}
