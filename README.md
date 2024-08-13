Project Description: POSIX-Compliant Client-Server Application

1. Introduction:

The project aims to design and implement a POSIX-compliant client-server application using C. The application simulates a messaging system where multiple clients communicate with a single server using shared memory for inter-process communication (IPC). The server manages the clients' requests and responds accordingly, following a stateless communication protocol. The primary objective is to handle client registration, request processing, and response generation in a concurrent and scalable manner.

2. Objectives:

- Client Registration: Implement a mechanism for clients to register with the server using a unique name. The server should maintain a list of registered clients, each associated with a unique communication channel.
  
- Client Requests: Allow clients to send various types of requests to the server, including arithmetic operations, checking if a number is even or odd, and determining if a number is prime.

- Server Response: Design a server response mechanism that sends appropriate results or error codes back to the client. The server must handle multiple clients simultaneously, ensuring that each request is processed correctly.
- Inter-Process Communication (IPC): Utilize POSIX shared memory for communication between clients and the server. Ensure that the server is multi-threaded, with each thread handling a specific client request.

3. System Architecture

The system follows a request-response architecture, with the following key components:

- Server: 
  - Manages client registration, request processing, and response generation.
  - Maintains shared memory segments for communication with clients.
  - Uses multi-threading to handle multiple client requests concurrently.

- Client:
  - Registers with the server and sends requests via a shared memory segment.
  - Receives responses from the server on the same shared memory segment.
  - Can perform various operations like arithmetic calculations and checking properties of numbers.

4. Communication Mechanism:

The communication between the server and clients is facilitated through shared memory, ensuring efficient and fast data exchange. The shared memory is divided into three segments:
  
- Connect Channel: Used by clients to register with the server.
- Request Channel: Clients send their requests to the server using this channel.
- Response Channel: The server sends the results or error codes back to the clients through this channel.

  5. Functional Requirements:

  Client Registration (REGISTER):
   - Clients connect to the server via the connect channel.
   - The client provides a unique name, and the server verifies that the name is not already in use.
   - Upon successful registration, the server returns a unique key (string) to the client, which will be used for future communication on the request and response channels.

    Client Request (CLIENT_REQUEST):
   - After registration, clients can send requests to the server using their unique key.
   - Supported operations include:
     - Arithmetic operations: Addition, Subtraction, Multiplication, Division.
     - Even or Odd check: Determine if a number is even or odd.
     - Prime check: Determine if a number is prime.
   - The server processes the request and returns the result to the client.

    Server Response (SERVER_RESPONSE):
   - The server sends a response code indicating success (0) or a custom error code.
   - The response includes a sequence number for tracking purposes.
   - The response also contains the result of the client's request or an error message if the operation was invalid (e.g., division by zero).

    Client Unregistration (UNREGISTER):
   - Clients can deregister from the server at any time by sending an unregister request.
   - The server will clean up all resources allocated for that client, including the shared memory segment associated with the client's communication.

     6. Implementation Details

      Inter-Process Communication:
       - The system uses shared memory for all IPC. Each client has its own shared memory segment, linked to the server by a unique key.
       - Synchronization is achieved using POSIX mutexes or read-write locks to avoid race conditions in the shared memory.

      Multi-threading:
     - The server is implemented as a multi-threaded process where each thread is responsible for handling a specific client's requests.
     - The main server thread listens for incoming client connections (registration) and spawns a new thread for each client.

      Logging:
       - The server logs all significant events, including client registrations, requests, and responses.
       - This helps in debugging and provides a trace of client-server interactions.

      Error Handling:
     - The system is designed to handle various error states, such as invalid operations, division by zero, or duplicate client names.
     - Error codes are returned to clients to inform them of issues with their requests.
    
       7. Intermediate States
      The server logs the following intermediate states to ensure proper functioning and debugging:
      Server Initialization: Creation of the connect channel.
      Client Registration: Client registers, and the server creates the communication channel.
      Client Request Handling: Server receives and processes client requests.
      Client Unregistration: Server cleans up resources after a client unregisters.
      Server Summary: The server maintains and prints a summary of all registered clients and processed requests.

      8. Scalability and Concurrency

    - The system is designed to handle multiple clients concurrently by leveraging multi-threading.
    - The shared memory and mutex locks ensure that the system is scalable and can handle additional operations and clients without significant performance degradation.

    9. Potential Enhancements

    - Additional Operations: Extend the types of operations that the client can request, such as factorial calculation, GCD/LCM, or matrix operations.
    - Security: Implement security features like encryption for client-server communication and authentication mechanisms.
    - Persistence: Store the results and client data in a persistent database for future reference and analysis.

      10. Conclusion

      This project demonstrates the practical use of POSIX-compliant mechanisms to implement a robust and scalable client-server application. By focusing on inter-process communication, concurrency, and error handling,           the system provides a reliable platform for client-server interactions, making it a valuable exercise in system programming and network communication.





