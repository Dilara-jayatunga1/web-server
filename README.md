# web-server
This project is a web server implemented in the C language. The server listens for incoming HTTP requests from clients (e.g., web browsers) and serves files or error responses based on the request. It is designed to be lightweight, easy to understand, and serves as a great learning tool for understanding how web servers work at a low level.

# Features

# Basic Web Server Functionality:
Listens on a specified port (default: 8085) for incoming HTTP requests.
Serves a simple "Hello, World!" response for all requests (basic version).
# File Serving:
Serves different files (e.g., index.html, image.jpg) based on the client's request.
Handles requests for specific files (e.g., GET /index.html).
# Error Handling:
Returns a 404 Not Found response if the requested file does not exist.
Returns a 400 Bad Request response 
Handles basic errors like file access issues.
Support for Multiple File Types:
Detects file extensions (e.g., .html, .jpg, .png) and sets the appropriate Content-Type header in the HTTP response.
# Optimizations:
Basic multithreading support to handle multiple client connections simultaneously.
Lightweight and efficient design for learning purposes.

# Run the server
To run the server:
``` Bash
./server
```

Using `make`, we can build and run the server with ease.

To build the server:
``` Bash
make build
```

To build and run the server:
``` Bash
make run
```
