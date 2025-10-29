#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

long long fibonacci(int n, vector<long long>&memo);

int main(){
int n;

    cout<<"Enter the number ";
    cin>>n;
    vector<long long>memo(n+1,-1);
    cout<<" "<<fibonacci(n,memo)<<" ";
}




long long fibonacci(int n, vector<long long>&memo){

long long result;
if(memo[n]!=-1){
    return memo[n];
}

if(n==0) return 0;
if(n==1) return 1;

if(memo[n]==-1){
    
result= fibonacci(n-1,memo)+fibonacci(n-2,memo);
memo[n]= result;
return result;
}


return 0;
}
