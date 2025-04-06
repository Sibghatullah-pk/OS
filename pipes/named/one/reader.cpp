#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

int main() {
    const char* fifo_path = "/tmp/myfifo";

    // Open pipe for reading
    int fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        cout << "Pipe kholne mein problem hui!\n";
        return 1;
    }

    // Read message from pipe
    char buffer[100];
    int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        cout << "Reader ko yeh message mila: " << buffer;
    }

    // Cleanup
    close(fd);
    return 0;
}
