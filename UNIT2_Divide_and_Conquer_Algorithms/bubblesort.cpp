#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
void bubblesort(vector<int>&arr);
void printvector(vector<int>&arr);
int main(){


vector<int>arr={3,10,4,5,78,54,32,56,67,78,1,2,456};
bubblesort(arr);

printvector(arr);

}


void bubblesort(vector<int>&arr){
int n=arr.size();

for (int i=0;i<n;i++){
//this loop is to track wether swaps are occuring or no
    bool swapped=false;

    for(int j=0;j<n-i-1;j++){// if ure at i then all i are already swapped
if(arr[j+1]>arr[j]){
    swap(arr[j+1],arr[j]);
    swapped=true;
}
}
if(swapped==false) break;
}





}


void printvector(vector<int>&arr){
int n=arr.size();
for (int i=0;i<n;i++){

    cout<<" "<<arr[i]<<" ";
}

}

