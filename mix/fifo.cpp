#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main() {
    const char* fifo = "myfifo";
    mkfifo(fifo, 0666); // Create FIFO
    int fd = open(fifo, O_WRONLY);
    int number = 42;
    write(fd, &number, sizeof(number));
    cout << "Writer sent: " << number << endl;
    close(fd);
    return 0;
}
