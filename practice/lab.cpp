#include<iostream>
#include<unistd.h>

using namespace std;
int main()
{
  int id,i;
  
  cout<<"main function strts..\n";
  
  id=fork();
  if(id>0)
  {
  cout<<"this is parent \n";
  }
  else if(id==0)
  {
  cout<<"this is child\n";
  }
  else{
  cout<<"\n creation failed";
  }
  
  cout<<"printing from 1 to 10\n";
  for(i=1;i<=10;i++)
  cout<<i;
  cout<<"\n";
  cout<<"mmain strts2nd\n";
  return 0;
  }
  
