# Simple HTTP Server in C++

This is a simple HTTP server written in C++ that demonstrates basic socket programming and handling HTTP requests. The server listens for incoming connections, processes HTTP requests, and responds with a simple "Hello, World!" HTML page.

## Features

- **Basic HTTP request handling**: The server listens for HTTP requests and sends a predefined HTML response.
- **Cross-platform**: Supports both Windows and Linux systems with different socket implementations.
- **Multi-client**: Handles multiple incoming connections one after another.

## Prerequisites

Before running this project, ensure that you have the following software installed:

- **C++ compiler**:
  - On **Windows**, use MinGW or any compatible compiler.
  - On **Linux**, GCC or Clang should be installed.

- **For Windows users**:
  - You need **MinGW** or **MSYS2** for compiling and linking.
  - You may need to install **WinSock2** for socket programming.

## How to Build and Run

### Windows

1. Open a terminal (like **Git Bash** or **Command Prompt**).
2. Navigate to the project folder:
   ```bash
   cd path\to\your\project
3. Build the project using g++ (assuming MinGW is installed):
   g++ -o httpServer httpServer.cpp -lws2_32
4. Run the Server:
   ./httpServer
Visit http://localhost:8080 in your browser. You should see the "Hello, World!" message.
