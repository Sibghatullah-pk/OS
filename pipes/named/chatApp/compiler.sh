#!/bin/bash

# Compile both programs
echo "Programs compile ho rahe hain..."
g++ chat_process1.cpp -o chat_process1
g++ chat_process2.cpp -o chat_process2

# Launch both processes in different terminals
echo "Process 1 shuru ho raha hai..."
xterm -e ./chat_process1 &

echo "Process 2 shuru ho raha hai..."
xterm -e ./chat_process2 &

echo "Chat application shuru ho gayi! Terminal windows check karo."

