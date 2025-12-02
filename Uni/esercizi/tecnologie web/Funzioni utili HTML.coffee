Funzioni utili HTML



Lorem ipsum{
    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor
    incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud
    exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure
    dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.
    Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit
    anim id est laborum.
}



Paragrafo{
    <p>Questo è un paragrafo di esempio.</p>
    per andare a capo: <br>
    #attributo id per identificare un paragrafo:
    <p id="paragrafo1">Paragrafo con ID.</p>
}

Lista non ordinata{
    <ul>
        <li>Elemento 1</li>
        <li>Elemento 2</li>
        <li>Elemento 3</li>
    </ul>
}

Lista ordinata{
    <ol>
        <li>Primo elemento</li>
        <li>Secondo elemento</li>
        <li>Terzo elemento</li>
    </ol>
    #attributo "start" per iniziare da un numero diverso:
    <ol start="5">
        <li>Quinto elemento</li>
        <li>Sesto elemento</li>
    </ol>
    #attributo "type" per cambiare il tipo di numerazione:
    <ol type="A">
        <li>Elemento A</li>
        <li>Elemento B</li>
    </ol>
    #attributo "reversed" per invertire l ordine:
    <ol reversed>
        <li>Elemento 3</li>
        <li>Elemento 2</li>
        <li>Elemento 1</li>
    </ol>

}

Lista di definizioni{
    <dl>
        <dt>Termine 1</dt>
        <dd>Definizione del termine 1.</dd>
        <dt>Termine 2</dt>
        <dd>Definizione del termine 2.</dd>
    </dl>
}

Ancora{
    <a href="https://www.esempio.com">Visita Esempio.com</a>
    #Ancora a una sezione della stessa pagina:
    <a href="#sezione1">Sezione 1</a>

    #Uso target per aprire in una nuova scheda:
    <a href="https://www.esempio.com" target="_blank">Apri in nuova scheda</a>

    #Uso download per scaricare un file:
    <a href="file.pdf" download>Scarica il file PDF</a>
}


Barra di navigazione{
    #Esempio di barra di navigazione, come un menu:
    <nav>
        <ul>
            <li><a href="#home">Home</a></li>
            <li><a href="#about">Chi Siamo</a></li>
            <li><a href="#services">Servizi</a></li>
            <li><a href="#contact">Contatti</a></li>
        </ul>
    </nav>
}

Modifiche sul testo{
    <strong>Testo in grassetto</strong>
    <em>Testo in corsivo</em>
    <u>Testo sottolineato</u>
    <mark>Testo evidenziato</mark>
    <del>Testo barrato</del>
    <ins>Testo sottolineato</ins>
    <small>Testo piccolo</small>
    <sub>Testo in apice</sub>
    <sup>Testo in pedice</sup>
    <code>Codice inline</code>
    <kbd>Input da tastiera</kbd>
    <samp>Output di un programma</samp>
    <var>Variabile</var>
    <q>Citazione breve</q>
    <pre>Per mantenere la formattazione</pre>
    <blockquote>Citazione lunga</blockquote>
    <cite>Citazione di una fonte</cite>
    <dfn>Definizione di un termine</dfn>
    <abbr>Abbreviazione</abbr>
    <time datetime="2024-06-01">Elemento temporale</time>
    <address>
        Contatti:<br>
        Esempio S.r.l.<br>
        Via Roma 1, 00100 Roma, Italia<br>
        Email: info@esempio.com
    </address> 
}

Immagine{
    <img src="immagine.jpg" alt="Descrizione dell'immagine" width="300" height="200" />
    #Alt lo uso sempre per l'accessibilità e SEO, e nel caso l'immagine non venga caricata.
    #Posso usare anche figure e figcaption per didascalie:
    <figure>
        <img src="immagine.jpg" alt="Descrizione dell'immagine" />
        <figcaption>Didascalia dell immagine</figcaption>
    </figure>
}

Audio{
    <audio controls>
        <source src="audio.mp3" type="audio/mpeg" />
        Il tuo browser non supporta l elemento audio.
    </audio>
    #Controls serve per aggiungere i controlli del'audio, vederlo a schermo, andare avanti, indietro e regolare il volume
    #Attributo loop per farlo ripetere in loop
    #Attributo autoplay per farlo partire automaticamente
    #Attributo muted per farlo partire senza audio
}

Video{
    <video width="640" height="360" controls>
        <source src="video.mp4" type="video/mp4" />
        Il tuo browser non supporta l elemento video.
    </video>
    #Attributo poster per mostrare un immagine prima che il video parta
    #Possiamo aggiungere la traccia per l'accessibilità, e posso avere sottotitoli, descrizioni audio, capitoli:
    #Sottotitoli:
    <track
    src="sottotitoli.vtt"
    kind="subtitles" 
    srclang="it" 
    label="Italiano" />

    #Descrizioni Audio:
    <track
    src="descrizione.vtt"
    kind="descriptions"
    srclang="it"
    label="Descrizioni Audio" />

    #Capitoli:
    <track
    src="capitoli.vtt"
    kind="chapters"
    srclang="it"
    label="Capitoli" /> 

}


Iframe{
    <iframe
        src="https://www.esempio.com"
        width="600"
        height="400"
        title="Esempio Iframe"
        frameborder="0"
        allowfullscreen>
    </iframe>
    #Attributo allow per specificare quali funzionalità sono permesse
    #Serve per incorporare contenuti esterni come mappe, video, pagine web
}


Tabella{
    <table>
        <caption>Tabella di esempio</caption>
        <thead>
            <tr>
                <th>Intestazione 1</th>
                <th>Intestazione 2</th>
                <th>Intestazione 3</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td>Dati 1</td>
                <td>Dati 2</td>
                <td>Dati 3</td>
            </tr>
            <tr>
                <td>Dati 4</td>
                <td>Dati 5</td>
                <td>Dati 6</td>
            </tr>
        </tbody>
        <tfoot>
            <tr>
                <td>Totale 1</td>
                <td>Totale 2</td>
                <td>Totale 3</td>
            </tr>
        </tfoot>
    </table>

    #Attributo border per aggiungere bordi alla tabella:
    <table border="1">...</table>

    #Attributo colspan per unire celle orizzontalmente:
    <td colspan="2">Cella che unisce 2 colonne</td>
    #Attributo rowspan per unire celle verticalmente:
    <td rowspan="2">Cella che unisce 2 righe</td>
    #Attributo scope per migliorare l'accessibilità:
    <th scope="col">Intestazione Colonna</th>
    <th scope="row">Intestazione Riga</th>


}


Forum{
    <form action="/submit" method="post">
        <label for="nome">Nome:</label>
        <input type="text" id="nome" name="nome" required />

        <label for="email">Email:</label>
        <input type="email" id="email" name="email" required />

        <label for="messaggio">Messaggio:</label>
        <textarea id="messaggio" name="messaggio" rows="4" required></textarea>

        <button type="submit">Invia</button>
    </form>
    #Attributo action specifica dove inviare i dati del formulario
    #Attributo method specifica il metodo HTTP (GET o POST)
    #Attributo required per campi obbligatori
    #Attributo placeholder per suggerimenti nei campi di input
    #Attributo maxlength per limitare il numero di caratteri
}

Tag semantici di struttura{
    <header>
        <h1>Intestazione della pagina</h1>
    </header>

    <nav>
        <ul>
            <li><a href="#home">Home</a></li>
            <li><a href="#about">Chi Siamo</a></li>
        </ul>
    </nav>

    <main>
        <h2>Contenuto principale</h2>
        <p>Questo è il contenuto principale della pagina.</p>
    </main>

    <aside>
        <h3>Barra laterale</h3>
        <p>Contenuti correlati o annunci.</p>
    </aside>

    <footer>
        <p>© 2024 Esempio S.r.l. Tutti i diritti riservati.</p>
    </footer>
}


Div e span{
    <div>
        <h2>Sezione con div</h2>
        <p>Questo è un paragrafo all interno di un div.</p>
    </div>

    <span>Testo inline con span</span>
    #Div è un contenitore di blocco, si usa praticamente per ogni cosa, ogni oggetto che si vuole creare
    #Span è un contenitore inline per il testo, si usa per modificare parti di testo specifiche
}


Popover e dialog {
    #Dialog per finestre modali:
    <dialog id="dialogo1">
        <h2>Finestra Modale</h2>
        <p>Questo è un esempio di finestra modale.</p>
        <button onclick="document.getElementById('dialogo1').close()">Chiudi</button>
    </dialog>
    <button onclick="document.getElementById('dialogo1').showModal()">Apri Finestra Modale</button>

    #Popover per contenuti aggiuntivi:
    <button id="popoverButton" aria-describedby="popoverContent">Mostra Popover</button>
    <div id="popoverContent" role="tooltip" style="display:none;">
        <p>Contenuto del popover.</p>
    </div>
    <script>
        const button = document.getElementById('popoverButton');
        const popover = document.getElementById('popoverContent');

        button.addEventListener('click', () => {
            if (popover.style.display === 'none') {
                popover.style.display = 'block';
            } else {
                popover.style.display = 'none';
            }
        });
    </script>
    #Popover è un contenitore che appare sopra altri contenuti, spesso usato per suggerimenti o informazioni aggiuntive,
    #come una notifica in basso a destra dello schermo
    #Dialog è un elemento per creare finestre modali, usato per avvisi, conferme o moduli di input
    #quando ti si apra una mini finestra al centro dello schermo che ti oscura il resto della pagina

}








Head di base HTML{
    <!DOCTYPE html>
    <html lang="it">
    <head>
        #Cosa un html di base dovrebbe contenere nel suo head
        <!-- CHARSET: Codifica dei caratteri (sempre primo) -->
        <meta charset="UTF-8" />

        <!-- VIEWPORT: Per dispositivi mobili (sempre secondo) -->
        <meta name="viewport" content="width=device-width, initial-scale=1.0" />

        <!-- TITLE: Titolo della pagina -->
        <title>Formulario</title>

        <!-- DESCRIPTION: Descrizione della pagina -->
        <meta
        name="description"
        content="Pagina di formulario per la raccolta dati."
        />

        <!-- ICON: Icona della pagina 16x16, 32x32-->
        <link rel="icon" href="favicon.ico" sizes="16x16" type="image/x-icon" />
        <link rel="icon" type="image/png" sizes="32x32" href="favicon-32x32.png" />
        <link rel="apple-touch-icon" sizes="180x180" href="apple-touch-icon.png" />
    </head>
    </html>
}


