from socket import *

# Server address and port
serverName = "130.136.5.36"
#posso scrivere anche il nome, tipo flora.cs.unibo.it, però così facendo coinvolto il DNS
serverPort = 12001

# Create a UDP socket
clientSocket = socket(AF_INET, SOCK_DGRAM)

try:
    # Get the message from the user
    message = input('Inserire frase in minuscolo: ')

    # Send the message to the server
    clientSocket.sendto(message.encode(), (serverName, serverPort))

    # Receive the modified message from the server
    modifiedMessage, serverAddress = clientSocket.recvfrom(2048)
    #la receive from è bloccante

    # Print the server's response
    print(f"Server response: {modifiedMessage.decode()}")

except Exception as e:
    print(f"Error occurred: {e}")

finally:
    # Close the socket
    clientSocket.close()
    #il buffer da 2048 viene deallocato
