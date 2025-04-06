#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

int main() {
    const char* fifo_path = "/tmp/myfifo";

    // Create named pipe
    mkfifo(fifo_path, 0666);

    // Open pipe for writing
    int fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        cout << "Pipe kholne mein problem hui!\n";
        return 1;
    }

    // Write message to pipe
    string message = "Hello from Writer!\n";
    write(fd, message.c_str(), message.length());
    cout << "Writer ne yeh message bheja: " << message;

    // Cleanup
    close(fd);
    unlink(fifo_path); // Pipe file delete kar do
    return 0;
}
