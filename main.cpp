#include <iostream>
#include <queue>
#include <bits/stdc++.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

ifstream fin("random.txt");

void read(int data[], int n){
    for(int i = 0; i < n; i++)
        fin>>data[i];
}

void printArray(int data[], int n){
    for(int i = 0; i < n; i++)
        cout<<data[i]<<' ';
}

void insertionsort(int data[], int n){
    for(int i = 1, j; i < n; i++){
        int tmp = data[i];
        for(j = i; j > 0 && tmp < data[j-1]; j--)
            data[j] = data[j-1];
        data[j] = tmp;
    }
}

void selectionsort(int data[], int n){
    for(int i=0, j, least; i < n-1; i++){
        for(j = i+1, least = i; j < n; j++)
            if(data[j]<data[least])
                least = j;
        swap(data[least], data[i]);
    }
}

void bubblesort(int data[], int n){
    bool again = true;
    for(int i = 0; i < n-1 && again; i++)
        for(int j = n-1, again = false; j > i; --j)
            if(data[j] < data[j-1]){
                swap(data[j], data[j-1]);
                again = true;
            }
}

void combsort(int data[], int n){
    int step = n, j, k;
    while((step = int(step/1.3)) > 1)
        for(j = n-1; j >= step; j--){
            k = j-step;
            if(data[j] < data[k]) swap(data[j], data[k]);
        }
        bool again = true;
        for(int i = 0; i < n-1 && again; i++)
            for(j = n-1, again = false; j > i; --j)
                if(data[j] < data[j-1]){
                    swap(data[j], data[j-1]);
                    again = true;
                }
}

void shellsort(int data[], int n){
    register int i, j, hCnt, h;
    int increments[20], k;
    for(h = 1, i = 0; h < n; i++){
        increments[i] = h;
        h = 3*h + 1;
    }
    for(i--; i >= 0; i--){
        h = increments[i];
        for(hCnt = h; hCnt < 2*h; hCnt++){
            for(j = hCnt; j < n; ){
                int tmp = data[j];
                k = j;
                while(k-h >= 0 && tmp < data[k-h]){
                    data[k] = data[k-h];
                    k -= h;
                }
                data[k] = tmp;
                j += h;
            }
        }
    }
}

void moveDown(int data[], int first, int last){
    int largest = 2*first+1;
    while(largest <= last){
        if(largest < last && data[largest] < data[largest+1]) largest++;
        if(data[first] < data[largest]){
            swap(data[first], data[largest]);
            first = largest;
            largest = 2*first+1;
        }
        else largest = last+1;
    }
}

void heapsort(int data[], int n){
    for(int i = n/2 - 1; i >= 0; --i)
        moveDown(data, i, n-1);
    for(int i = n-1; i >= 1; --i){
        swap(data[0], data[i]);
        moveDown(data, 0, i-1);
    }
}

void merge(int arr[], int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]

    // Initial index of first subarray
    int i = 0;

    // Initial index of second subarray
    int j = 0;

    // Initial index of merged subarray
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int arr[],int l,int r){
    if(l>=r){
        return;//returns recursively
    }
    int m =l+ (r-l)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}

void itmerge(int arr[], int l, int m, int r){
    int k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    int i = 0;
    int j = 0;
    k = l;

    while (i < n1 && j < n2){
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void itmergeSort(int arr[], int l, int r){
    if (l < r){
        int m = l + (r - l) / 2;
        itmergeSort(arr, l, m);
        itmergeSort(arr, m + 1, r);
        itmerge(arr, l, m, r);
    }
}

void quicksort(int data[], int first, int last){
    int lower = first+1, upper = last;
    swap(data[first],data[(first+last)/2]);
    int bound = data[first];
    while(lower <= upper){
        while(bound > data[lower]) lower++;
        while(bound < data[upper]) upper--;
        if(lower < upper) swap(data[lower++], data[upper--]);
        else lower++;
    }
    swap(data[upper], data[first]);
    if(first < upper-1) quicksort(data, first, upper-1);
    if(upper+1 < last) quicksort(data, upper+1, last);
}

void quicksort(int data[], int n){
    int i, m;
    if(n < 2) return;
    for(i = 1, m = 0; i < n; i++)
        if(data[m] < data[i])
            m = i;
    swap(data[n-1], data[m]);
    quicksort(data, 0, n-2);
}

void radixsort(int data[], int n){
    register int d, j, k, factor;
    const int radix = 10;
    const int digits = 10;
    queue<int> queues[radix];
    for(d = 0, factor = 1; d < digits; factor *= radix, d++){
        for(j = 0; j < n; j++)
            queues[(data[j] / factor) % radix].push(data[j]);
        for(j = k = 0; j < radix; j++)
            while(!queues[j].empty()){
                data[k++] = queues[j].front();
                queues[j].pop();
            }
    }
}

void countingsort(int data[], const int n){
    int i;
    int largest = data[0];
    int *tmp = new int[n];
    for(i = 1; i < n; i++)
        if(largest < data[i])
            largest = data[i];
    unsigned int *count = new unsigned int[largest+1];
    for(i = 0; i <= largest; i++) count[i] = 0;
    for(i = 0; i < n; i++) count[data[i]]++;
    for(i = 1; i <= largest; i++) count[i] = count[i-1]+count[i];
    for(i = n-1; i >= 0; i--){
        tmp[count[data[i]]-1] = data[i];
        count[data[i]]--;
    }
    for(i = 0; i < n; i++)
        data[i] = tmp[i];
}

int v[100000000];
int n = 1000000;

int main()
{
    read(v, n);
    //insertionsort(v, n);
    //selectionsort(v, n);
    //bubblesort(v, n);
    //combsort(v, n);
    //shellsort(v, n);
    //heapsort(v, n);
    //mergeSort(v, 0, n-1);
    itmergeSort(v, 0, n-1);
    //quicksort(v, n);
    //radixsort(v, n);
    //countingsort(v, n);
    //printArray(v, n);
    //cout<<v[99999999];
    return 0;
}
