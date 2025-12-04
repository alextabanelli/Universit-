# Import socket module
from socket import * 

# Create a TCP server socket
# (AF_INET is used for IPv4 protocols)
# (SOCK_STREAM is used for TCP, NOT SOCK_DGRAM)
tcpServerSocket = socket(AF_INET, SOCK_STREAM)

# Assign a server port number
serverPort = 12001
#welcoming socket TCP
#il server TCP per ogni richiesta del client crea un nuovo socket dedicato alla comunicazione con quel client
# di solito il numero di porta del client e' compreso tra 32000 e 64000

# Bind the socket to the server address and server port (on local machine only)
tcpServerSocket.bind(("", serverPort))

# Start listening on the socket, queueing a maximum of 1 connection at a time
# (others will be refused if more than 1 connection comes in)
tcpServerSocket.listen(1)

# Print to indicate that the server is ready to receive client connections
print('The server is ready to receive')

# Loop to handle incoming connections
while True:
    # Accept a new client connection
    tcpConnectedClientSocket, addr = tcpServerSocket.accept()
    print('Received a client connection from:', addr)

    # Receive the request message from the client (using recv() for TCP)
    message = tcpConnectedClientSocket.recv(2048).decode()

    # Modify the message (convert to uppercase)
    modifiedMessage = message.upper()

    # Print the modified message to the server's console
    print(modifiedMessage)

    # Send the modified message back to the client (using send() for TCP)
    tcpConnectedClientSocket.send(modifiedMessage.encode())

    # Close the connection with the client after processing the message
    tcpConnectedClientSocket.close()
