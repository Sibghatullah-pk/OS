#include<iostream>
using namespace std;
int main(){
int totalUsers=6;
int printerPool=0;
int maxClaim[6]={2,2,2,2,2,2};
int currentUsage[6]={1,1,1,1,1,1};
int remaining[6];
bool finished[6];
for(int i=0;i<totalUsers;i++){
remaining[i]=maxClaim[i]-currentUsage[i];
finished[i]=false;
}
int completed=0;
while(completed<totalUsers){
bool safeToProceed=false;
for(int u=0;u<totalUsers;u++){
if(!finished[u]&&remaining[u]<=printerPool){
printerPool+=currentUsage[u];
currentUsage[u]+=remaining[u];
remaining[u]=0;
finished[u]=true;
completed++;
cout<<"Request "<<u<<" completed using printers.\n";
safeToProceed=true;
}}
if(!safeToProceed){
cout<<"Circular wait detected. Deadlock present. No safe sequence.\n";
break;
}}
if(completed==totalUsers){
cout<<"All printer requests handled successfully without deadlock.\n";
}
return 0;
}

