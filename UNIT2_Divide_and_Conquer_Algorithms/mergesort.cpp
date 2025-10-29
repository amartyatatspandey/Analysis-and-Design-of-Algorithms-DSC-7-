#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void merge(int a[], int b[],int m,int n);
int main(){}

void merge(int a[], int b[],int m,int n){
int i=0;
int j=0;
int  c[m+n];
int i;
int j;
int k;

    while(a[i]>b[j]){
        c[k]=b[j];
        j++;
        k++;
    }
    while(a[i]<b[j]){
        c[k]=a[i];
        i++;
        k++;
    }

}


