# Laboratorio 

## Login message
Se si vuole visualizzare un messaggio prima della richiesta dell'inserimento delle credenziali, andremo a modificare il file:
`/etc/issues`

Nel caso in cui volessimo mostrare l'indirizzo IPv4 della macchina inseriremo la seguente stringa:
`IP:\4`

## Post login message
Se si vuole modificare il messaggio che viene stampato dopo il primo login del giorno, andremo a modificare il file:
`/etc/motd`

## PING structure
Per realizzare un'applicazione simile al comando ping abbiamo bisogno di:
- Comunicazione tra due macchina
- Misurazione del tempo intercorso tra l'invio e la ricezione dell'ACK

Il processo A dovrà necessariamente fare una fork in modo tale da poter inviare pacchetti senza la necessità di aspettare per un pacchetto (che potrebbe non arrivare).

Come facciamo a misurare il tempo intercorso tra l'invio (T0) e la ricezione di un ACK per lo stesso pacchetto? Il problema risiede nel fatto che i due processi figli hanno memoria separata e non possono quindi lavorare sulla stessa variabile.

Invece di utilizzare strutture di inter process communication, aggiungeremo l'informazioni direttamente all'interno del pacchetto che abbiamo spedito.

## File interfaces
Al suo interno si trovano le configurazioni di base della scheda di rete.

```
    allow-hotplug enp0s3
    iface enp0s3 inet static
    address 10.0.0.1/24
    gateway 10.0.0.254
```

## Organizzazione rete

Dato l'indirizzo e la maschera le riportiamo in binario.
La parte di indirizzi della maschera che è settata ad 255 sarà bloccata, mentre per quelli rimanenti possiamo giostrarli come vogliamo.

Ad esempio: 145.67.0.0/16 -> 65.536 diversi indirizzi disponibili:
questo perché abbiamo 2 byte che possono cambiare, 2^8*2^8 = 65.536

1. Divido in due: 145.67.0.0/17 e 145.67.128.0/17, ovvero:
 - Il primo gruppo = Da 145.67.0.0 a 145.67.127.255
 - Il secondo gruppo = Da 145.67.128.0.0 a 145.67.255.255

 Continuiamo la divisione per due fino a quando raggiungiamo il minimo numero che ci interessa (RICORDIAMO CHE 2 INDIRIZZO SONO SEMPRE RISERVATI!)

 ## Tabella ARP

 Per visualizzare la tabella ARP all'interno della macchina possiamo inserire il comando:
 `ip n`


## Esercizio 2A
 1) 1.1.1.1 16
 2) 1.1.2.2 16
 3) 1.1.1.3 24

 mask 16 = 11111111.11111111.00000000.00000000 11111111111111110000000000000000
 mask 24 = 11111111.11111111.11111111.00000000 11111111111111111111111100000000

1) 00000001.00000001.00000001.00000001 00000001000000010000000100000001
2) 00000001.00000001.00000010.00000010 00000001000000010000001000000010
3) 00000001.00000001.00000001.00000011 00000001000000010000000100000011

### AND tra A e B 
 00000001.00000001.00000001.00000001
 11111111.11111111.00000000.00000000
 00000001.00000001.00000000.00000000 A

 00000001.00000001.00000010.00000010
 11111111.11111111.00000000.00000000
 00000001.00000001.00000000.00000000


