#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

long long fib(int n,vector<long long> tab);
int main(){
int n;
cout<<"Enter the number";
    cin>>n;
    vector<long long> tab(n+1);
    cout<<"Answer is"<<fib(n,tab)<<endl;
}

long long fib(int n,vector<long long> tab){
/*if(n==0){tab[0]=0;}
if(n==1){ tab[1]=1;} THIS LOGIC IS WRONG BECAUSE if n=1 then tab0 isnt initialised so the loop never runs*/ 
tab[0]=0;
tab[1]=1;
for(int i=2;i<=n;i++){
    tab[i]=tab[i-1]+tab[i-2];
}

return tab[n];

}
