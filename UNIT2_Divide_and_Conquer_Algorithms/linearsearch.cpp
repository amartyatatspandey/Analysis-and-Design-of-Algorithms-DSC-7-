#include<iostream>
#include<vector>
using namespace std;

int linearsearch(vector<int>&arr, int t );

int main(){
int t; 
vector<int>arr={3,4,5,7,8,9,10,45,67};   
cout<<"Enter target";
cin>>t;
int res=linearsearch(arr,t);
cout<<"index is as follows"<< res <<endl;
}


int linearsearch(vector<int>&arr, int t){

for(int i=0; i<arr.size();i++){

if (arr[i]==t) return i;

}

return -1;




}



