Funzioni utili CSS

Agguiungere CSS in 3 modi{
    1. Inline CSS
        1. Inline CSS
        CSS viene utilizzato per applicare uno stile specifico a un singolo elemento HTML. Si utilizza l'attributo "style" all'interno del tag HTML.
        <p style="color:blue; font-size:20px;">Questo è un paragrafo con stile inline.</p>

    2. Internal CSS
        2. Internal CSS
        Internal CSS viene utilizzato per definire stili specifici all interno di un documento HTML.
        Si utilizza il tag <style> all interno della sezione <head> del documento.
        <head>
            <style>
                p {
                    color: green;
                    font-size: 18px;
                }
            </style>
        </head>

    3. External CSS
        External CSS viene utilizzato per collegare un file CSS esterno al documento HTML.
        Si utilizza il tag <link> all interno della sezione <head> del documento.
        <head>
            <link rel="stylesheet" type="text/css" href="stile.css">
        </head>
}


Can i use ... {
    https://caniuse.com/
    #per controllare la compatibilità dei vari CSS
}


Unita di misura{
    px : pixel, unità fissa
    em : relativa alla dimensione del font dell elemento padre
    rem : relativa alla dimensione del font della radice (html)
    % : percentuale rispetto all elemento contenitore
    vw : viewport width, percentuale della larghezza della finestra del browser
    vh : viewport height, percentuale dell altezza della finestra del browser
}



Regole{
    nomeregola: valore;
    #esempio
    color: red;
    font-size: 16px;
}

Ereditarietà{
    Alcune proprietà CSS vengono ereditate dagli elementi figli, mentre altre no.
    #esempio
    color: red; #viene ereditato
    margin: 10px; #non viene ereditato
    

    <style >
        body {
            color: blue; /* Questa proprietà verrà ereditata dagli elementi figli */
        }
        h1 {
            color: inherit; # Inherit proprietà non verrà ereditata dall'elemento body
            color: initial; # Initial  riscrive il valore ereditato, andando a impostarlo al valore iniziale del browser
            color: unset; # Unset applica il comportamento base della proprietà, che può essere ereditata o meno a seconda della proprietà stessa
        }

        #Per resettare tutte le proprietà di un elemento
        div {
            all: unset; 
        }
        #Important per forzare l'applicazione di una regola
        p {
            color: red !important; 
        }

    </style>

}


Selettori{
    Tipi di selettori{
        Selettore di tipo{
            Seleziona tutti gli elementi di un determinato tipo
            #esempio
                p {
                    color: blue; /* Seleziona tutti gli elementi <p> */
                }
        }

        Selettore di classe{
            Seleziona tutti gli elementi con una determinata classe
            #esempio
                .mio-paragrafo {
                    font-size: 18px; /* Seleziona tutti gli elementi con la classe "mio-paragrafo" */
                }
        }

        Selettore ID{
            Seleziona un elemento con un ID specifico
            #esempio
            `#header {background-color: gray; /* Seleziona l'elemento con l'ID "header" */}` 
        }

        Selettore universale{
            Seleziona tutti gli elementi
            #esempio
            * {
                margin: 0; /* Seleziona tutti gli elementi */
            }
        }


        Selettore di attributo{
            Seleziona gli elementi in base a un attributo specifico
            #esempio
            a[target="blank"] {
                color: red; /* Seleziona tutti i link che hanno l attributo target impostato su "blank" */
            }
            <a href="pagina.html" target="blank">Link che si apre in una nuova scheda</a> #Viene selezionato
            <a href="pagina.html">Link che si apre nella stessa scheda</a> #Non viene selezionato

            #Esempi avanzati
            a[target~="blank"] #Seleziona tutti i link che hanno l attributo target che contiene la parola "blank", quindi anche un attributo che contine piu parole separate da spazi
            a[target^="box-"] #Seleziona tutti i link che hanno l attributo target che inizia con "box-"
            a[target$="-deb"] #Seleziona tutti i link che hanno l attributo target che termina con "-deb"
            a[target*="er"] #Seleziona tutti i link che hanno l attributo target che contiene "er" in qualsiasi posizione
        }
        
        Pseudo-classi o stati{
            Seleziona gli elementi in base al loro stato
            #esempio
            a:hover {
                color: green; /* Seleziona i link quando il mouse è sopra di essi */
            }
        }


        Pseudo-elementi{
            Seleziona e stila una parte specifica di un elemento
            #esempio
            p::first-line {
                font-size: 24px; /* Seleziona la prima riga di ogni paragrafo */
            }
            #esempio2{
            p::before {
                content: "Nota: "; /* Aggiunge il testo "Nota: " prima di ogni paragrafo */
                font-weight: bold;
            }
        }

        Combinatori{
            Selettore discendente{
                Seleziona gli elementi che sono discendenti di un altro elemento
                #esempio
                div p {
                    color: purple; /* Seleziona tutti gli elementi <p> all interno di un <div> */
                }
            }


            
        Selettore figlio{
            Seleziona gli elementi che sono figli diretti di un altro elemento
            #esempio
            div > p {
                color: orange; /* Seleziona tutti gli elementi <p> che sono figli diretti di un <div> */
            }
        }

        Selettore fratello adiacente{
            Seleziona un elemento che è immediatamente successivo a un altro elemento
            #esempio
            h2 + p {
                margin-top: 0; /* Seleziona il primo <p> subito dopo ogni <h2> */
                }
            }
        }


        Selettore fratello generale{
            Seleziona tutti gli elementi che sono fratelli di un altro elemento
            #esempio
            h2 ~ p {
                color: brown; /* Seleziona tutti i <p> che sono fratelli di un <h2> */
            }
        }
    }
}


Block e inline box{
    Block{
        Occupa tutta la larghezza disponibile
        Inizia su una nuova riga
        Ha margini e padding che influenzano il layout
        #esempio
        <div>Questo è un elemento block.</div>
    }

    Inline{
        Occupa solo lo spazio necessario per il suo contenuto
        Non inizia su una nuova riga
        I margini e il padding influenzano solo lo spazio intorno al contenuto
        #esempio
        <span>Questo è un elemento inline.</span>
    }

    Proprietà comuni{

        width e height{
            Specificano la larghezza e l altezza di un elemento
            Applicabili principalmente agli elementi block e inline-block
        }

        margin e padding{
            margin : spazio esterno intorno all elemento
            padding : spazio interno tra il contenuto e il bordo dell elemento
        }
    }

    Display{
            Modifica la visualizzazione di un elemento
            block : rende un elemento block
            inline : rende un elemento inline
            inline-block : combina caratteristiche di block e inline
            none : nasconde l elemento
        }

}

Box model{
    content{
        Il contenuto effettivo dell elemento (testo, immagini, ecc.)
    }

    Padding{
        Spazio tra il contenuto e il bordo dell elemento
        #esempio
        div {
            padding: 15px; /* Aggiunge un padding di 15px intorno al contenuto del div */
            padding: 10px 20px; /* padding verticale di 10px e orizzontale di 20px */
            padding: 5px 10px 15px 20px; /* padding in senso orario: top, right, bottom, left */
            padding-top: 10px; /* padding solo in alto */
            padding-right: 5px; /* padding solo a destra */
            padding-bottom: 8px; /* padding solo in basso */
            padding-left: 12px; /* padding solo a sinistra */
        }
    }

    border{
        Linea che circonda il padding (se presente) e il contenuto
        #esempio
        div {
            border: 2px solid black; /* Aggiunge un bordo nero di 2px intorno al div */
            border-width: 3px; /* Imposta la larghezza del bordo a 3px */
            border-style: dashed; /* Imposta lo stile del bordo a tratteggiato */
            border-color: red; /* Imposta il colore del bordo a rosso */
            border-top: 4px dotted blue; /* Bordo superiore di 4px, puntinato e blu */
            border-right: 2px solid green; /* Bordo destro di 2px, solido e verde */
            border-bottom: 5px double orange; /* Bordo inferiore di 5px, doppio e arancione */
            border-left: 1px solid purple; /* Bordo sinistro di 1px, solido e viola */
            border-radius: 10px; /* Angoli arrotondati con raggio di 10px */
                border-radius: 50%; /* Angoli completamente arrotondati, creando un cerchio o un ovale */
        }
    }

    margin{
        Spazio tra il bordo dell elemento e gli elementi circostanti
        #esempio
        div {
            margin: 20px; /* Aggiunge un margine di 20px intorno al div */
            margin: 20px 10px; /* margine verticale di 20px e orizzontale di 10px */
            margin: 10px 15px 20px 25px; /* margine in senso orario: top, right, bottom, left */
            margin-top: 15px; /* margine solo in alto */
            margin-right: 5px; /* margine solo a destra */
            margin-bottom: 10px; /* margine solo in basso */
            margin-left: 8px; /* margine solo a sinistra */
        }
    }

    content box vs border box{
        content-box{
            La larghezza e l altezza specificate si riferiscono solo al contenuto dell elemento
        }

        border-box{
            La larghezza e l altezza specificate includono il contenuto, il padding e il bordo dell elemento
        }
    }
}


Background {
    background-color{
        Imposta il colore di sfondo di un elemento
        #esempio
        div {
            background-color: lightblue; /* Imposta il colore di sfondo del div a azzurro chiaro */
        }
    }

    background-image{
        Imposta un immagine di sfondo per un elemento
        #esempio
        div {
            background-image: url(immagine.jpg); /* Imposta l immagine di sfondo del div */
        }

        Gradienti come sfondo{
            linear-gradient(to right, red, yellow) : crea un gradiente lineare da rosso a giallo
            radial-gradient(circle, blue, green) : crea un gradiente radiale da blu a verde
            link: https://cssgradient.io/
        }
    }

    background-size{
        Controlla le dimensioni dell immagine di sfondo
        #esempio
        div {
            background-size: cover; /* L immagine copre l intero elemento */
            background-size: contain; /* L immagine è contenuta all interno dell elemento */
            background-size: 100px 200px; /* L immagine ha una larghezza di 100px e un altezza di 200px */
        }
    }

    background-repeat{
        Controlla se e come l immagine di sfondo si ripete
        #esempio
        div {
            background-repeat: no-repeat; /* L immagine non si ripete */
            background-repeat: repeat-x; /* L immagine si ripete solo orizzontalmente */
            background-repeat: repeat-y; /* L immagine si ripete solo verticalmente */
            background-repeat: repeat; /* L immagine si ripete sia orizzontalmente che verticalmente */
        }
    }

    background-position{
        Controlla la posizione dell immagine di sfondo all interno dell elemento
        #esempio
        div {
            background-position: center; /* L immagine è centrata nell elemento */
            background-position: top right; /* L immagine è posizionata in alto a destra */
            background-position: 50px 100px; /* L immagine è posizionata a 50px da sinistra e 100px dall alto */
            background-position-x: left; /* L immagine è posizionata a sinistra */
            background-position-y: bottom; /* L immagine è posizionata in basso */
        }
    }

    background-attachment{
        Controlla se l immagine di sfondo scorre con il contenuto o rimane fissa
        #esempio
        div {
            background-attachment: scroll; /* L immagine scorre con il contenuto */
            background-attachment: fixed; /* L immagine rimane fissa mentre il contenuto scorre */
            background-attachment: local; /* L immagine scorre con il contenuto all interno dell elemento */
        }
    }
}


Overflow{
    Controlla come gestire il contenuto che supera le dimensioni di un elemento
    visible: Il contenuto in eccesso è visibile oltre i confini dell elemento (default)
    hidden: Il contenuto in eccesso è nascosto e non visibile
    scroll: Vengono aggiunte barre di scorrimento per visualizzare il contenuto in eccesso
    auto: Vengono aggiunte barre di scorrimento solo se necessario
    #esempio
    div {
        width: 200px;
        height: 100px;
        overflow: scroll; /* Aggiunge barre di scorrimento se il contenuto supera le dimensioni del div */
    }

    word-break{
        Controlla come le parole vengono spezzate quando superano i confini di un elemento
        normal: Le parole non vengono spezzate (default)
        break-all: Le parole possono essere spezzate in qualsiasi punto per adattarsi ai confini
        keep-all: Le parole non vengono spezzate, utile per lingue come il cinese o il giapponese
        #esempio
        div {
            width: 150px;
            word-break: keep-all; /* Le parole non vengono spezzate per adattarsi alla larghezza del div */
        }
    }

    #Esempio di un classico caso con barra di scorrimento verticale e non orizzontale
    div {
        width: 200px;
        height: 100px;
        overflow-y: scroll; /* Aggiunge barre di scorrimento verticali se il contenuto supera le dimensioni del div */
        word-break: keep-all; /* Le parole non vengono spezzate per adattarsi alla larghezza del div */
    }
}

Operazioni su immagini{
    object-fit{
        Controlla come un immagine si adatta al contenitore
        fill: L immagine riempie l intero contenitore, potrebbe deformarsi
        contain: L immagine viene ridimensionata per essere completamente visibile all interno del contenitore, mantenendo le proporzioni
        cover: L immagine viene ridimensionata per coprire l intero contenitore, potrebbe essere ritagliata
        none: L immagine mantiene le sue dimensioni originali
        scale-down: L immagine viene ridimensionata solo se è più grande del contenitore, altrimenti mantiene le sue dimensioni originali
        #esempio
        img {
            width: 200px;
            height: 150px;
            object-fit: cover; /* L immagine copre l intero contenitore */
        }
    }
}


Operazioni sulle tabelle{
    
}
