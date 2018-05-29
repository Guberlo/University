variabile=eval(input("Inserisci un numero "))
print("Stampo il numero diviso 2")
print(variabile/2)

#//COMANDI LISTA:
lsit=["mangio","bevo","tutto"]
lsit.count(#"<termine_da_cercare") #conta quanti elementi *termine_da_cercare* sono presenti
lsit.remove(#"<termine_da_eliminare") #elimina l'elemento *termine_da_eliminare*
lsit.insert(#<posizione in cui inserire l'elemento>,<elemento_da_inserire)
lsit.append(#<elemento_da_inserire) l'elemento verrà inserito alla fine della LISTA
lsit.reverese()#inverte la lista
len(lsit)#ritorna la lunghezza della lista
#COMANDO IN if("a" in "mamma") la seguente istruzione controlla se il primo
#membro sta nel secondo, in tal caso esegue il corpo sintassi for= for
#<nome_variabile> in a: che auto incrementa la x fino al massimo valore di a

#SINTASSI FOR  for <nome_variabile> in range(<numero_limite>) equivale a for
#x<20, <nome_variabile> parte da 0 istruzione break interrompe, continue salta
#quell'istruzione, pass serve effettivamente per un'implementazione in un
#secondo momento in quanto funziona come se non fosse stato messo alcun
#"blocco". Il range può essere usato anche partendo da uno specifico punto
#(assegnando uno specifico valore alla variabile di controllo).
#ES: for x in range(<valore_start>,<valore_stop>)

#DIZIONARI
#se volessimo ad esempio assegnare un numero ad una stringa non
#potremmo farlo normalmente all'interno di una lista, con i dizionari possiamo
#invece assegnare un numero ad una stringa nel seguente modo:
#x={"arance":10,...} non potremmo più scrivere print(x[2]), ma scriveremo
#print(x[<nomestringa>]), questo ci riporterà il numero affiancato alla stringa.
#per aggiungere un elemento basta scrivere x["<nomestringa>"]=numero, per
#eliminare una chiave basta scrivere del x[<nomestringa>], per eliminare tutto
#il dizionario basta scrivere x.clear()

#APRIRE UN FILE: assegnare un contenitore di flusso dati all'istruzione open -->
#flux=open(<nomefile.estensione>,"<modalità di scrittura/lettura>") ad esempio:
#flux=open("testo.txt","w") questo comando permetterà di aprire il file
#testo.txt e sovrascriverlo da 0 cancellando tutto quello che c'era in
#precedenza. il comando open("testo.txt","a"(che sta per append)) aggiungerà
#solamente quello che vogliamo al file di testo senza cancellarne il contenuto.
#Alla fine delle istruzioni dovrà aggiungersi l'istruzione
#<nome_contenitore>.close()

#LEGGERE UN FILE: stessa cos del sovrascrivere ma a posto del parametro "w" o
#"a", bisogna inserire il parametro "r". dopo aver fatto ciò per memorizzare
#quello che l'istruzione ha calcolato si può assegnare un contenitore alla
#funzione <nome_contenitore_open>.read() es testo=open("testo.txt","r")
#mag=testo.read(), se poi volessivo vedere cosa contiene il file basta mandare
#in stampa mag. questa tecnica può essere utilizzata con qualunque tipo di file.
#Per leggere una singola linea del file esaminato possiamo usare l'istruzione
#<nome_contenitore_open>.readlines(). Se volessimo leggere entro una certa riga
#del testo possiamo utilizzare il for in
#range(<valore_scan_iniziale>,len(<nome_variabile_readlines())) ed eventualmente
#possiamo effettuare un salto di n numero aggiungendo ,n.
#ES: for x in range(0,len(documento),2) partirà da 0 fino alla fine di documento saltando due
#righe alla volta

#STRINGA COME CARATTERE:  Basta scrivere <nome_stringa>[indice che vogliamo
#rappresentare] es stringa=balla stringa[0]==b, stringa[:-1]== balla -1 --> ball
