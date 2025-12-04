from socket import *

# Put server address here
serverName = "130.136.5.36"
serverPort = 12001

# Create a TCP socket
clientSocket = socket(AF_INET, SOCK_STREAM)
# SOCK_STREAM per TCP

# Open TCP connection
clientSocket.connect((serverName, serverPort))
# la connect apre la connessione TCP con i 3 messaggi di handshake
# a differenza di UDP se il server non e' raggiungibile la connect fallisce subito

# Read input from the user
message = input('Inserire frase in minuscolo: ')

# Send the message to the server
clientSocket.send(message.encode())

# Receive the modified message from the server
modifiedMessage = clientSocket.recv(2048)

# Print the server's response
print(modifiedMessage.decode())

# Close the connection
clientSocket.close()
# close è diversa da close() in UDP perché in TCP si chiude la connessione, quindi mando un segnale al server, mentre in UDP semplicemente chiudo il socket locale
# e anche il server mi manda l'ack di chiusura
