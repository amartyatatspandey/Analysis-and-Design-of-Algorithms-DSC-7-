#include<iostream>
#include<vector>
using namespace std;

int binarysearch(vector<int>&arr,int t);

int main(){
int t; 
vector<int>arr={3,4,5,7,8,9,10,45,67,99,100,145,567,789};   
cout<<"Enter target";
cin>>t;
int res=binarysearch(arr,t);
cout<<"index is as follows"<< res <<endl;
}


int binarysearch(vector<int>&arr, int t){

int low=0;
int high= arr.size()-1;
int mid= low+(high-low)/2;

while(high>=low){//
     mid= low+(high-low)/2;//mid needs to get recalculated in every iteration

    if(arr[mid]==t){
        return mid;
    }
    if(arr[mid]<t){
        low=mid+1;
    }
    if(arr[mid]>t){
        high=mid-1;
    }
    }
    return -1;
}

