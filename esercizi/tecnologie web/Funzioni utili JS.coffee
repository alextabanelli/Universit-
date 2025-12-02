Funzioni utili JavaScript

stringhe{
    .lenght : ritorna la lunghezza
    .toUpperCase() : trasforma in maiuscolo
    .toLowerCase() : trasforma in minuscolo
    .trim() : rimuove gli spazi vuoti all inizio e alla fine
    .includes('testo') : ritorna true se il testo è contenuto nella stringa
    .replace('vecchio','nuovo') : sostituisce il testo vecchio con il testo nuovo
    .indexOf('testo') : ritorna la posizione del testo all interno della stringa, -1 se non lo trova
    .indexOf('testo', posizione) : ritorna la posizione del testo all interno della stringa, iniziando la ricerca dalla posizione specificata
    .slice(inizio, fine) : ritorna una porzione di stringa dall indice inizio fino a fine (escluso)
}

array{
    .split(',') : eseguito su una stringa con un separatore tipo ',' genero un array
    .join('-') : contrario di split, genera una stringa da un array che ha come separatore l argomento
    .push('valore') : aggiunge un elemento alla fine dell array
    .pop() : rimuove l ultimo elemento dell array
    .shift() : rimuove il primo elemento dell array
    .unshift('valore') : aggiunge un elemento all inizio dell array
    .indexOf('valore') : ritorna la posizione dell elemento nell array, -1 se non lo trova
    .slice(inizio, fine) : ritorna una porzione di array dall indice inizio fino a fine (escluso)
}

continue {
    interrompe l iterazione corrente e passa alla successiva in un ciclo
}

operatore spread{
    ...array : permette di espandere un array in singoli elementi
    ES: let numeri = [1, 2, 3]
    ES: let nuoviNumeri = [...numeri, 4, 5] // nuoviNumeri è [1, 2, 3, 4, 5]
}


template literals{
    `Testo con variabile ${variabile}` : permette di inserire variabili all interno di stringhe usando il backtick `
    `Testo su
    piu righe senza usare \n` : permette di creare stringhe su piu righe senza usare il carattere di nuova linea \n
}

ternary operator{
    condizione ? valore_se_vero : valore_se_falso : permette di assegnare un valore in base a una condizione in una sola riga
    ES: let risultato = (eta >= 18) ? 'Maggiorenne' : 'Minorenne'
}

funzioni freccia{
    (parametro) => { corpo_della_funzione } : sintassi compatta per definire funzioni
    ES: let somma = (a, b) => { return a + b }
    ES: let quadrato = x => x * x : se c è un solo parametro e una sola espressione, si possono omettere le parentesi e le graffe
}


manipolazione DOM{
    document.getElementById('id') : seleziona un elemento per id
    document.getElementsByClassName('classe') : seleziona elementi per classe
    document.getElementsByTagName('tag') : seleziona elementi per tag
    document.querySelector('.classe o #id o tag') : seleziona il primo elemento che corrisponde al selettore CSS
    document.querySelectorAll('.classe o tag') : seleziona tutti gli elementi che corrispondono al selettore CSS
    elemento.innerHTML : ottiene o imposta il contenuto HTML di un elemento
    elemento.textContent : ottiene o imposta il contenuto testuale di un elemento
    elemento.style.proprietaCSS : modifica lo stile CSS di un elemento
    elemento.classList.add('classe') : aggiunge una classe a un elemento
    elemento.classList.remove('classe') : rimuove una classe da un elemento
    elemento.classList.toggle('classe') : aggiunge o rimuove una classe in base alla sua presenza
}