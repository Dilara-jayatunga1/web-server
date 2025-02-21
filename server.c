#include <stdio.h> 
#include <stdlib.h> // exit
#include <string.h> 
#include <netdb.h>  // getnameinfo
#include <sys/socket.h> // socket APIs
#include <netinet/in.h> // sockaddr_in
#include <unistd.h>     // open,close
#include <signal.h> // signal handling
#include <time.h>  
#include <pthread.h> 

#define SIZE 1024  
#define PORT 8085 
#define BACKLOG 10 // number of pending connections queue

// Generates file URL based on route
void getFileURL(char *route, char *fileURL);

// Sets *MIME to the mime type of file
void getMimeType(char *file, char *mime);

// Handles SIGINT signal
void handleSignal(int signal);


  //Returns a string with the current time in HTTP response date format
 
void getTimeString(char *buf);

// Handles individual client requests in a new thread
void *handleRequest(void *arg);

int serverSocket;

int main()
{
    // register signal handler
    signal(SIGINT, handleSignal);

    // server internet socket address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;                     // IPv4
    serverAddress.sin_port = htons(PORT);                   // port number in network byte order
    serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // localhost

    // socket of type IPv4 using TCP protocol
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // reuse address and port
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));

    // bind socket to address
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        printf("Error: The server is not bound to the address.\n");
        return 1;
    }

    // listen for connections
    if (listen(serverSocket, BACKLOG) < 0)
    {
        printf("Error: The server is not listening.\n");
        return 1;
    }

    printf("\nServer is listening on http://localhost:%d/\n\n", PORT);

    while (1)
    {
        int *newClientSock = malloc(sizeof(int)); // Allocate memory for new socket
        *newClientSock = accept(serverSocket, NULL, NULL);

        if (*newClientSock < 0)
        {
            free(newClientSock);
            continue;
        }

        // Create a new thread to handle the request
        pthread_t thread;
        pthread_create(&thread, NULL, handleRequest, newClientSock);
        pthread_detach(thread); // Automatically clean up thread
    }
}

void *handleRequest(void *arg)
{
    int clientSocket = *(int *)arg;
    free(arg); // Free dynamically allocated memory for the socket

    char *request = (char *)malloc(SIZE * sizeof(char));
    char method[10], route[100];

    read(clientSocket, request, SIZE);

    //HTTP request
    sscanf(request, "%s %s", method, route);
    printf("%s %s\n", method, route);

    // only GET method
    if (strcmp(method, "GET") != 0)
    {
        const char response[] = "HTTP/1.1 400 Bad Request\r\n"
                                "Content-Type: text/html\r\n\n"
                                "<html><body><h1>400 Bad Request</h1></body></html>";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
    else
    {
        char fileURL[100];

        // generate file URL
        getFileURL(route, fileURL);

        // read file
        FILE *file = fopen(fileURL, "r");
        if (!file)
        {
            const char response[] = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\n"
                                    "<html><body><h1>404 Not Found</h1></body></html>";
            send(clientSocket, response, sizeof(response) - 1, 0);
        }
        else
        {
            //HTTP response header
            char resHeader[SIZE];

            //get time
            char timeBuf[100];
            getTimeString(timeBuf);

            //create mime type from file URL
            char mimeType[32];
            getMimeType(fileURL, mimeType);

            sprintf(resHeader, "HTTP/1.1 200 OK\r\nDate: %s\r\nContent-Type: %s\r\n\n", timeBuf, mimeType);
            int headerSize = strlen(resHeader);

            printf(" %s\n", mimeType);

            // file size
            fseek(file, 0, SEEK_END);
            long fsize = ftell(file);
            fseek(file, 0, SEEK_SET);

            // Allocate memory for response buffer
            char *resBuffer = (char *)malloc(fsize + headerSize);
            strcpy(resBuffer, resHeader);

            // Copy file contents to response buffer
            fread(resBuffer + headerSize, fsize, 1, file);

            send(clientSocket, resBuffer, fsize + headerSize, 0);
            free(resBuffer);
            fclose(file);
        }
    }

    free(request);
    close(clientSocket);
    return NULL;
}

void getFileURL(char *route, char *fileURL)
{
    // if route has parameters, remove them
    char *question = strrchr(route, '?');
    if (question)
        *question = '\0';

    // if route is empty, set it to index.html
    if (route[strlen(route) - 1] == '/')
    {
        strcat(route, "index.html");
    }

    // get filename from route
    strcpy(fileURL, "htdocs");
    strcat(fileURL, route);

    // if filename does not have an extension, set it to .html
    const char *dot = strrchr(fileURL, '.');
    if (!dot || dot == fileURL)
    {
        strcat(fileURL, ".html");
    }
}

void getMimeType(char *file, char *mime)
{
    // position in string with period character
    const char *dot = strrchr(file, '.');

    // if period not found, set mime type to text/html
    if (dot == NULL)
        strcpy(mime, "text/html");

    else if (strcmp(dot, ".html") == 0)
        strcpy(mime, "text/html");

    else if (strcmp(dot, ".css") == 0)
        strcpy(mime, "text/css");

    else if (strcmp(dot, ".js") == 0)
        strcpy(mime, "application/javascript");

    else if (strcmp(dot, ".jpg") == 0)
        strcpy(mime, "image/jpeg");

    else if (strcmp(dot, ".png") == 0)
        strcpy(mime, "image/png");

    else if (strcmp(dot, ".gif") == 0)
        strcpy(mime, "image/gif");

    else if (strcmp(dot, ".mp4") == 0)
        strcpy(mime, "video/mp4");

    else
        strcpy(mime, "text/html");
}

void handleSignal(int signal)
{
    if (signal == SIGINT)
    {
        printf("\nShutting down server...\n");
        close(serverSocket);
        exit(0);
    }
}

void getTimeString(char *buf)
{
    time_t now = time(0);
    struct tm tm = *gmtime(&now);
    strftime(buf, 100, "%a, %d %b %Y %H:%M:%S %Z", &tm);
}