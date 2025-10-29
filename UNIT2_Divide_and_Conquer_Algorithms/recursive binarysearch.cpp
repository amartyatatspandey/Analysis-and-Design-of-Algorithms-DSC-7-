#include<iostream>
#include<vector>
using namespace std;

int binarysearch(vector<int>&arr,int t,int high, int low);

int main(){
int t; 
vector<int>arr={3,4,5,7,8,9,10,45,67,99,100,145,567,789};   
cout<<"Enter target";
cin>>t;
int high=arr.size()-1,low=0,mid=low+(high-low)/2;
int res=binarysearch(arr,t,high,low);
cout<<"Element is present at index "<< res <<endl;
}


int binarysearch(vector<int>&arr, int t, int high, int low){

int mid= low+ (high-low)/2;

if (arr[mid]==t){
    return mid;
}

if (arr[mid]<t){
    low=mid+1;
    return binarysearch(arr,t,high, low);
}
if(arr[mid]>t){
    high=mid-1;
    return binarysearch(arr,t,high,low);
}

return -1;
}
