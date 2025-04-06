#include<iostream>
#include<queue>
using namespace std;

struct Process
{
int id;
int at;
int bt;
int wt;
int tat;//turn..
int rt;
bool completed;
bool in_queue;
};
int main()
{
int n,time_q;
cout<<"enter number of proceses and time quantum:";
cin>>n>>time_q;

Process p[n];
for(int i=0;i<n;i++){
cout<<"enter arivaltime/brusttime for process"<<i+1<<endl;
cin>>p[i].at>>p[i].bt;
p[i].id=i+1;
p[i].rt=p[i].bt;
p[i].completed=false;
p[i].in_queue=false;
p[i].wt=0;
p[i].tat=0;
}
queue<int> ready_queue;
int current_time=0,completed_count=0;
float total_waiting_time=0;

while(completed_count<n)
{
for(int i=0;i<n;i++){
if(p[i].at<=current_time && !p[i].completed && !p[i].in_queue)
{
ready_queue.push(i);
p[i].in_queue=true;
}
if(ready_queue.empty())
{
current_time++;
continue;
}
int k=ready_queue.front();
ready_queue.pop();
p[k].in_queue=false;

if (p[k].rt <= time_q) { // 3 <= 2 is false, so else block
    current_time = current_time + p[k].rt;
    p[k].rt = 0;
    cout << "Time " << current_time - p[k].rt << ": Process " << p[k].id << " running (Remaining Time: 0)\n";
} else {
    p[k].rt = p[k].rt - time_q; // 3 - 2 = 1
    current_time = current_time + time_q; // 0 + 2 = 2
    cout << "Time " << current_time - time_q << ": Process " << p[k].id << " running (Remaining Time: " << p[k].rt << ")\n"; // Time 0: Process 1 running (Remaining Time: 1)
}
if(p[k].rt>0)
{
ready_queue.push(k);

p[k].in_queue=true;
}
else
{
p[k].completed=true;
completed_count++;
p[k].tat=current_time-p[k].at;
p[k].wt=p[k].tat-p[k].bt;
total_waiting_time+=p[k].wt;
cout<<"time"<<current_time<<" :process "<<p[k].id<<" completed"<<endl;
}}

cout<<"\nprocess id | waiting time |trunAround time\n";
for(int i=0;i<n;i++)
{
cout<<"  "<<p[i].id<<"\t\t"<<p[i].wt<<"\t\t"<<p[i].tat<<endl;
}
cout<<"avg wait time: "<<total_waiting_time<<endl;
return 0;
}}
