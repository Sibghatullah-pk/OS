#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
using namespace std;

int main() {
    const char* fifo_path = "/tmp/chatfifo";

    // Create named pipe
    mkfifo(fifo_path, 0666);

    int fd_write = open(fifo_path, O_WRONLY);
    int fd_read = open(fifo_path, O_RDONLY);

    cout << "Process 1 shuru hua. Messages type karo ('bye' se exit):\n";

    while (true) {
        // Write message to pipe
        string message;
        cout << "Process 1: ";
        getline(cin, message);
        message += "\n";
        write(fd_write, message.c_str(), message.length());

        // Check if message is "bye"
        if (message == "bye\n") {
            cout << "Process 1: 'bye' likha, exit kar raha hoon.\n";
            break;
        }

        // Read message from pipe
        char buffer[1024];
        int bytes_read = read(fd_read, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            cout << "Process 1 ko yeh message mila: " << buffer;

            // Check if received message is "bye"
            if (strcmp(buffer, "bye\n") == 0) {
                cout << "Process 1: Process 2 ne 'bye' likha, exit kar raha hoon.\n";
                break;
            }
        }

        sleep(1); // Thoda wait karo taake race condition na ho
    }

    // Cleanup
    close(fd_write);
    close(fd_read);
    unlink(fifo_path);
    return 0;
}

