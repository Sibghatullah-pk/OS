#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<sys/types.h>
#include<stdlib.h>
using namespace std;
/*int main()
{
pid_t pid=fork();
if(pid == 0)
{
cout<<"chils proecess:my pid="<<getpid()<<"parent"<<getppid()<<endl;
}
else if(pid>0)
{
cout<<"parent process:my pid="<<getpid()<<"child"<<pid<<endl;
}
else
{
cout<<"failed"<<endl;
exit(1);
}
return 0;
}


int main(){
pid_t pid=fork();
if(pid==0){
cout<<"child ..working"<<endl;
cout<<"child done"<<endl;
exit(5);
}
pid_t pid2=fork();
if (pid2 == 0) {
        cout << "Second child: PID = " << getpid() << endl;
        exit(0);
    }
else if(pid>0 && pid2>0 )
{
cout<<"parent...child"<<endl;
int status;
wait(NULL);
wait(&status);
if(WIFEXITED(status))
{
cout<<"child exieted with "<<WEXITSTATUS(status)<<endl;
cout<<"parent :both child khtm.."<<endl;
}
}
else
{
cout<<"failed";
exit(1);
}
return 0;
}


int main() {
    pid_t pid = fork();
    if (pid == 0) {
        cout << "Child process: PID = " << getpid() << ", sleeping..." << endl;
        sleep(3);
        cout << "Child process: Done!" << endl;
        exit(0);
    } else if (pid > 0) {
        cout << "Parent process: Checking child status..." << endl;
        int status;
        pid_t result;
	while((result =waitpid(pid,&status,WUNTRACED))==0)
{
cout<<"parent:child run..."<<endl;
sleep(1);
}
if(result==pid){
cout<<"parent:child finiched"<<endl;
}
}
else
{
perror("forkfaield");
exit(1);
}
return 0;
}
*/


int main() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        cout << "Child 1: PID = " << getpid() << ", sleeping for 3 seconds..." << endl;
        sleep(3);
        cout << "Child 1: Done!" << endl;
        exit(10);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        cout << "Child 2: PID = " << getpid() << ", sleeping for 1 second..." << endl;
        sleep(1);
        cout << "Child 2: Done!" << endl;
        exit(20);
    }

    if (pid1 > 0 && pid2 > 0) {
        int status;
        // Variant 1: Wait for specific child (pid1) with blocking
        cout << "Parent: Waiting for Child 1 (PID = " << pid1 << ") with blocking..." << endl;
        waitpid(pid1, &status, 0);
        if (WIFEXITED(status)) {
            cout << "Parent: Child 1 exited with status " << WEXITSTATUS(status) << endl;
        }

        // Variant 2: Wait for any child with WNOHANG (non-blocking)
        cout << "Parent: Checking for any child with WNOHANG..." << endl;
        pid_t result;
        while ((result = waitpid(-1, &status, WNOHANG)) == 0) {
            cout << "Parent: No child has finished yet..." << endl;
            sleep(1);
        }
        if (result > 0 && WIFEXITED(status)) {
            cout << "Parent: Child " << result << " exited with status " << WEXITSTATUS(status) << endl;
        }
    } else {
        cout << "Fork failed!" << endl;
        exit(1);
    }
    return 0;
}
