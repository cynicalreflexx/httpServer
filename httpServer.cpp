#include <iostream>   // For input/output operations
#include <string>     // To work with strings
#include <cstring>    // For functions like memset() for clearing memory
#include <cstdlib>    // For EXIT_FAILURE
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>  // For more advanced network functions
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h> // For close() function
#endif

using namespace std;

#define PORT 8080 // Defines the port the server will listen on

// Function to handle the client request
void handle_request(int client_socket) {
    char buffer[1024] = {0};
    
    // Read the request using recv() for portability
    int bytes_read = recv(client_socket, buffer, 1024, 0);  
    if (bytes_read < 0) {
        perror("Read failed");
        return;
    }

    cout << "Request received:\n" << buffer << endl;

    // Prepare the HTTP response
    string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n\r\n"
        "<html><body><h1>Hello, World!</h1></body></html>";

    // Send the response
    send(client_socket, response.c_str(), response.length(), 0);
    
#ifdef _WIN32
    closesocket(client_socket);  // On Windows, use closesocket() instead of close()
#else
    close(client_socket);  // On Unix-based systems, use close()
#endif
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

#ifdef _WIN32
    // Initialize Winsock (Windows only)
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Winsock initialization failed!" << endl;
        return -1;  // Exit the program if initialization fails
    }
#endif

    // Create the Socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Setup the socket address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Listen on any interface
    address.sin_port = htons(PORT);        // Port number to listen on

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    cout << "Server is listening on port " << PORT << "...\n";

    // Accept and handle incoming connections
    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            continue;  // Try accepting the next connection
        }
        // Handle the HTTP request
        handle_request(new_socket);
    }

#ifdef _WIN32
    WSACleanup();
#endif

#ifdef _WIN32
    closesocket(server_fd);  
#else
    close(server_fd);  
#endif
    
    return 0;
}
