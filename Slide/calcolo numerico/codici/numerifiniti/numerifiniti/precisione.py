def calcola_precisione_macchina():

    # Calcola la precisione di macchina
    epsilon = 1.0
    while 1.0 + epsilon / 2.0 != 1.0:
        epsilon /= 2.0
    return epsilon

# Esegui il programma
precisione = calcola_precisione_macchina()
print("Precisione di macchina:", precisione)


