//
// Created by xih on 8/7/2017.
//

#include <iostream>
using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

//直接选择排序
void selectSort(int A[], int n){
    for (int i=0; i<n; i++ ) {
        // 在A[i, ... n-1]中选取最小的元素
        int minIndex = i;
        for (int j=i+1; j<n; j++){
            if (A[j] < A[minIndex])
                minIndex = j;
        }

        if (minIndex != i){
            swap(A[minIndex], A[i]);
        }
    }
}


//直接插入排序
void insertSort(int A[], int n){
    int i, j, temp;
    for (i=1; i<n; i++) {
        int temp = A[i];
        j=i-1;
        //将大于A[i]的元素后移
        for (; j>=0 && A[j]>temp; j--) {
            A[j+1] = A[j];
        }
        //j+1 的位置插入A[i]
        A[j+1] = temp;
    }
}

// -----------------------------------------------------大根堆排序----------------------------------------------------//
//大根堆的自上而下调整
void heapAdjustDown(int A[], int i, int n){
    int temp = A[i];
    int j = 2*i + 1;

    while (j < n){
        //A[j] A[j+1] 中较大者
        if ((j + 1 < n) && (A[j+1] > A[j])) {
            j++;
        }

        if (A[j] <= temp)
            break;

        A[i] = A[j]; //把较大的节点往上移动，替换它的父节点
        i = j;
        j = 2*i + 1;
    }
    A[i] = temp;
}

void heapSort(int A[], int n){
    //第一步： 从有叶子节点的节点(n-1-1)/2开始，调整大根堆
    for (int i = n/2 - 1; i >= 0; i--) {
        heapAdjustDown(A, i, n);
        }

    //第二步：将A[0] 与最后一个元素互换， 并调整堆的顺序。这样，最大的元素总是在数组的末尾
    for (int j=n-1; j>0; j--) {
        swap(A[0], A[j]);
        heapAdjustDown(A, 0, j);
    }
}

// End-----------------------------------------------------大根堆排序----------------------------------------------------//

// -------------------------------------------快速排序-------------------------------------------------------------------//
//快速排序. 将数组分区
int partition(int A[], int low, int high){   //partition函数的复杂度为O(n)
    int pivot = A[low];
    int i = low, j = high;

    while (i < j){
        while(i < j && A[j] >= pivot) j--; //注意：从右向左寻找第一个小于pivot的数。>= !!!
        A[i] = A[j];

        while(i < j && A[i] <= pivot) i++; //<=. 如果没有等于判断的话，将陷入死循环。
        A[j] = A[i];
    }
    A[i] = pivot;
    return i;
}

//快速排序算法
void quickSort(int A[], int low, int high){
    if (low < high){
        int pivotIndex = partition(A, low, high);
        quickSort(A, low, pivotIndex-1);
        quickSort(A, pivotIndex+1, high);
    }
}

// End -------------------------------------------快速排序-------------------------------------------------------------------//



// -----------------------------------------------归并排序-------------------------------------------------------------//
//归并排序 -- 合并两个有序数组
void mergeTwoArrays(int A[], int start, int mid, int end, int temp[]){
    int i = start, j = mid + 1, k = 0;
    //从两个有序数组中遍历，选取较小者插入temp数组

    while (i <= mid && j <= end) {
        if (A[i] <= A[j]){
            temp[k++] = A[i++];
        }

        else if (A[j] < A[i]) {
            temp[k++] = A[j++];
        }
    }

    while (i <= mid) temp[k++] = A[i++];
    while (j <= end) temp[k++] = A[j++];

    //需要将临时数组拷贝回A[]
    for (int p = 0; p < k; p++) {
        A[start+p] = temp[p];
    }

}

//归并排序 -- 递归
void mergeSort(int A[], int start, int end, int temp[]) {
    if (start < end) {
        int mid = (start + end) / 2;
        mergeSort(A, start, mid, temp);
        mergeSort(A, mid + 1, end, temp);
        mergeTwoArrays(A, start, mid, end, temp);
    }
}

////归并排序 -- 主函数
void MergeSortMain(int A[], int n){
    int *temp = new int[n]; //一次性开辟一个临时数组。避免频繁的new
    mergeSort(A, 0, n-1, temp);
    delete[] temp;
}

// End -----------------------------------------------归并排序-------------------------------------------------------------//

/*
int main(){
    // 直接选择排序
    int test[] = {9,1,4,6,2,7,10,0,8};
    int size = sizeof(test)/sizeof(test[0]);
    selectSort(test, size);


    cout << "Selection sort result: " << endl;
    for (int i=0; i<size; i++)
        cout << test[i] << endl;

    //直接插入排序
    int test2[] = {9,1,4,6,2,7,10,0,8};
    int size2 = sizeof(test2)/sizeof(test2[0]);
    insertSort(test2, size2);
    cout << "Insert sort result: " << endl;
    for (int i=0; i<size2; i++)
        cout << test2[i] << endl;


    //大根堆排序
    int test3[] = {9,1,4,6,2,7,10,0,8};
    int size3 = sizeof(test3)/sizeof(test3[0]);
    heapSort(test3, size3);
    cout << "Heap Sort Result: " << endl;
    for (int i = 0; i < size; i++)
        cout << test3[i] << endl;

    //快速排序
    int test4[] = {9,1,4,6,2,7,10,0,8,0,20,1,4,8};
    int size4 = sizeof(test4)/sizeof(test4[0]);
    quickSort(test4, 0, size4-1);
    cout << "Quick Sort Result: " << endl;
    for (int i = 0; i < size4; i++)
        cout << test4[i] << endl;

    //归并排序
    int test5[] = {9,1,4,6,2,7,10,0,8,0,20,1,4,8};
    int size5 = sizeof(test5)/sizeof(test5[0]);
    MergeSortMain(test5, size5);
    cout << "Merge Sort Result: " << endl;
    for (int i = 0; i < size5; i++)
        cout << test5[i] << endl;
}
*/