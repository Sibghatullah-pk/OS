#include<iostream>
using namespace std;
int main(){
int processes=2,resources=2;
int alloc[2][2]={{1,0},{1,3}};
int max[2][2]={{2,2},{2,3}};
int avail[2]={1,1};
int need[2][2];
for(int i=0;i<processes;i++){
for(int j=0;j<resources;j++){
need[i][j]=max[i][j]-alloc[i][j];
}}
bool finished[2]={false,false};
int safeSequence[2];
int index=0;
for(int count=0;count<processes;count++){
bool found=false;
for(int p=0;p<processes;p++){
if(!finished[p]){
bool canProceed=true;
for(int r=0;r<resources;r++){
if(need[p][r]>avail[r]){
canProceed=false;
break;
}}
if(canProceed){
for(int r=0;r<resources;r++){
avail[r]+=alloc[p][r];
}
safeSequence[index++]=p;
finished[p]=true;
found=true;
}}}
if(!found)break;
}
bool deadlock=false;
for(int i=0;i<processes;i++){
if(!finished[i]){
deadlock=true;
break;
}}
if(deadlock){
cout<<"Deadlock detected among the processes.\n";
}else{
cout<<"No deadlock found. Safe sequence: ";
for(int i=0;i<processes;i++){
cout<<"P"<<safeSequence[i]<<" ";
}
cout<<endl;
}
return 0;
}

