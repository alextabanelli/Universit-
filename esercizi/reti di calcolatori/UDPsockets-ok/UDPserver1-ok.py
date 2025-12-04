from socket import *

# Create a UDP server socket
# AF_INET is used for IPv4 protocols, and SOCK_DGRAM is used for UDP
serverSocket = socket(AF_INET, SOCK_DGRAM)

# Assign a server port number
serverPort = 12001
#valore della porta >1024 ma minore di 65000



# Bind the socket to the server address and port
serverSocket.bind(("", serverPort))
#lega l'IP della macchina e l'indirizzo di porta

# Server should be up and running, listening for incoming requests
print('The server is ready to receive')

while True:
    try:
        # Receive the request message from the client
        message, clientAddress = serverSocket.recvfrom(2048)
        #ascolta se riceve richiesta, con un buffer a 2048 byte
        
        # Print the client address (for debugging purposes)
        print("Received message from client:", clientAddress)
        #client address contiene IP e indirizzo di porta del client
        #i client possono avere un numero qualsiasi di porta

        # Modify the message (convert to uppercase)
        modifiedMessage = message.decode().upper()
        #decode trasforma i bit del livello blu un stringa, e upper converte le lettere in maiuscolo

        # Print the modified message (for debugging purposes)
        print(f"Modified message: {modifiedMessage}")

        # Send the modified message back to the client
        serverSocket.sendto(modifiedMessage.encode(), clientAddress)

    except Exception as e:
        print(f"Error occurred: {e}")
