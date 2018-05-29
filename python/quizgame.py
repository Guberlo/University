opencontainer=open("/home/guberlo/Documenti/python/quizgame.txt","r")
readcontainer=opencontainer.readlines()
opencontainer.close()

points=0;

for x in range(0,len(readcontainer),2):
    risposta=input(readcontainer[x]).capitalize() #prima lettera maiuscola
    if risposta==readcontainer[x+1][:-1]:
        print("Complimenti, hai indovinato")
        points+=1
    else:
        print("Mi dispiace, risposta errata")
        print("La risposta esatta era: ",readcontainer[x+1],"")
if points == 0:
    print("Ups... Il tuo punteggio è uguale a zero, non conosci proprio Salvo..\n")
elif points > 0 and points <= 6:
    print("Complimenti, il tuo punteggio è buono, non lo conosci perfettamente ma può andare!\n")
