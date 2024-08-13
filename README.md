Project Description: POSIX-Compliant Client-Server Application

*1. Introduction*

The project aims to design and implement a POSIX-compliant client-server application using C. The application simulates a messaging system where multiple clients communicate with a single server using shared memory for inter-process communication (IPC). The server manages the clients' requests and responds accordingly, following a stateless communication protocol. The primary objective is to handle client registration, request processing, and response generation in a concurrent and scalable manner.

#### *2. Objectives*

- *Client Registration*: Implement a mechanism for clients to register with the server using a unique name. The server should maintain a list of registered clients, each associated with a unique communication channel.
  
- *Client Requests*: Allow clients to send various types of requests to the server, including arithmetic operations, checking if a number is even or odd, and determining if a number is prime.

- *Server Response*: Design a server response mechanism that sends appropriate results or error codes back to the client. The server must handle multiple clients simultaneously, ensuring that each request is processed correctly.

