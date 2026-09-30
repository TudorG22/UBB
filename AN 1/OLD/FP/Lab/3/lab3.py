def checkPrime(x):
    if x > 0: 
        if x == 1:
            return False
        else:
            for i in range(2,x):
                if x%i == 0:
                    return False
            return True
    else:
        if x == -1:
            return False
        else:
            for i in range(x, -2, 1):
                if x%i == 0:
                    return False
            return True


def checkIf3Times(lst, x):
    count = 0
    for i in range(len(lst)):
        if lst[i] == x:
            count += 1
    return count >= 3

def findFirst(lst, x):
    for i in range(len(lst)):
        if lst[i] == x:
            return i
    return -1

# -- program ----------

print("1. Introducere lista \n4. Stop")

command = input("")
if command == "1":
    lst = input("Introduce-ti lista: ").split(" ")
    lst = list(map(int, lst))

    while True:
        print("---------\n1. Introducere lista noua \n2. Gasire secventa numere prime \n3. Secventa cu cel mult 3 valori distincte \n4. Secventa cu elemente consecutive de semn contrar \n5. Stop")
        command = input("")
        if command == "1":
            lst = input("Introduce-ti noua lista: ").split(" ")
            lst = list(map(int, lst))
            
        # -- 4 ----------
        elif command == "2":
            secvente = []
            temp = []
            for i in range(len(lst)):
                if checkPrime(lst[i]):
                    temp.append(lst[i])
                else:
                    if temp != []:
                        secvente.append(temp)
                    temp = []
            if temp != []:
                secvente.append(temp)
            secvente.sort(key = len)
            print("O secventa de numere prime de lungime maxime e", secvente[len(secvente)-1])

        # -- 2 ----------
        elif command == "3":
            secvente = []
            temp = []
            i = 0
            while i  < len(lst):
                if temp == []:
                    temp.append(lst[i])
                    i += 1

                else:
                    if not checkIf3Times(temp, lst[i]):
                        temp.append(lst[i])
                        i += 1
                    else:
                        secvente.append(temp)
                        i = findFirst(lst, lst[i]) + 1
                        temp = []
            if temp != []:
                secvente.append(temp)
            secvente.sort(key = len)
            secvente.sort(key = len)
            print("O secventa cu cel mult 3 valori distincte de lungime maxima e", secvente[-1])


        # -- 12 ----------
        elif command == "4":
            secvente = []
            temp = []
            i = 0
            while i  < len(lst):
                if temp == []:
                    temp.append(lst[i])
                    i += 1

                else:
                    if (abs(temp[-1]) != temp[-1] and abs(lst[i] == abs(lst[i]))) or (abs(temp[-1]) == temp[-1] and abs(lst[i] != abs(lst[i]))):
                        temp.append(lst[i])
                        i += 1
                    else:
                        secvente.append(temp)
                        temp = []
            if temp != []:
                secvente.append(temp)
            secvente.sort(key = len)
            print("O secventa unde numerele consecutive sunt de semn opus de lungime maxima e", secvente[-1])

        elif command == "5":
            print("Terminare program.")
            break

        else: 
            print("Comanda non recunoscuta. Intrerupere program.")
            break

elif command == "5":
    print("Terminare program.")

else: 
    print("Comanda non recunoscuta. Intrerupere program.")