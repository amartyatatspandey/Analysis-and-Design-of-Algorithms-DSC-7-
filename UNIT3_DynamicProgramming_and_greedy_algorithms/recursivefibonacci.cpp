#include<iostream>
using namespace std;
int fib (int n);

int main(){
int n;
    cout<<"Enter the number";
    cin>>n;
    cout<<"Answer is"<<fib(n)<<endl;
}


int fib(int n){

if(n==1)return 1;
if(n==0) return 0;

return fib(n-2)+ fib(n-1);
}