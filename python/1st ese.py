
"""Create a program that asks the user to enter their name and their age. Print
out a message addressed to them that tells them the year that they will turn 100
years old.

Extras:

    Add on to the previous program by asking the user for another number and
    printing out that many copies of the previous message. (Hint: order of
    operations exists in Python) Print out that many copies of the previous
    message on separate lines. (Hint: the string "\n is the same as pressing the
    ENTER button)"""



name= input("Inserisci il tuo nome: ")
age= input("Inserisci la tua eta': ")
age=int(age)
if age > 0:
    print("Caro "+name+", tra 100 anni avrai esattamente",age+100,"anni!!!")
else:
    print("Non puoi inserire 0 come eta'!!")
cycle=input("Inserisci un numero: ")
cycle=int(cycle)
for i in range(cycle):
    print("Caro "+name+", tra 100 anni avrai esattamente",age+100,"anni!!!\n")
