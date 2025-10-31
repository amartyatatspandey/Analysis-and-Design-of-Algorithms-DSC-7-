#include<iostream> 
#include<vector>
#include<algorithm>
#include<string>
using namespace std;



int lcs( string s1,string s2,int m, int n,vector<vector<int>>&memo );
int main (){
    string s1,s2;
    

    cout<<"Please Enter The first String"<<endl;
    cin>>s1;
    cout<<"Please Enter the Second string"<<endl;
    cin>>s2;

    int m= s1.length();
    int n= s2.length();
    vector<vector<int>>memo(m+1,vector<int>(n+1,-1)); /*first you stacked the -1s in
 the initialisation inside then you stacked those rows on top of each other in the oter initialisation
 */
    int result =lcs(s1,s2,m,n,memo);
    cout<<"The longest common subsequence is: "<<result<<endl;

    return 0;

}

int lcs(string s1,string s2, int m, int n,vector<vector<int>>& memo){


if(memo[m][n]!=-1) return memo[m][n];
//now to cover base cases when one of the sequence vanishes
if(m==0||n==0){ memo[m][n]=0;}
else {
    if(s1[m-1]==s2[n-1]){
       return 1+lcs(s1,s2,m-1,n-1,memo);
    }
    else{
     return max(lcs(s1,s2,m,n-1,memo),lcs(s1,s2,m-1,n,memo));   
    }

}

}