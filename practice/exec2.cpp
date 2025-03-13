#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <string.h>  // For strerror
using namespace std;

int main()
{
    cout << "Before execl" << endl;

    if (execl("/home/sibghatullah/Desktop/exec1", "exec1", NULL) == -1)
    {
        cerr << "execl failed: " << strerror(errno) << " (errno: " << errno << ")" << endl;
        return 1;
    }

    cout << "This won't print if execl succeeds" << endl;
    return 0;
}
