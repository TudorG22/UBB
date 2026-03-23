# ------------------- Cerinta 4 - Cont bancar -------------------


# -------- Stocare --------
# structura de date:
#   - variablila care contin soldul = int  
#   - lista de tranzactii, unde o tranzactie e o lista de marime 3 : 
#       [ziua, suma, tip] = [string, int, string] = ["01.12.2000", 0, "mancare"]


sold = 0
tranzactii = []


# -------- Functii --------

# --- testare format data ---

def an_bisect(an):
    if an % 400 == 0:
        return True
    elif an % 100 == 0:
        return False
    elif an % 4 == 0:
        return True
    else:
        return False

def este_data(data):
    descompunere = data.split(".")

    # testam daca sunt numere
    test1 = true
    for elt in descompunere:
        if not isdigit(elt):
            test1 = false

    # testam daca e o data valida si in ordinea specificata zi-luna-an
    # luna
    test2 = len(descompunere[1]) == 2 and int(descompunere[1]) > 0 and int(descompunere[1]) < 12

    # anul
    test4 = len(descompunere[2]) == 4 and int(descompunere[2]) > 0

    # ziua
    test3 = false
    if test2 and test:
        if int(descompunere[1]) in [1, 3, 5, 7, 8, 10, 12]:
            test3 = len(descompunere[0]) == 2 and int(descompunere[0]) > 0 and int(descompunere[1]) < 32
        elif int(descompunere[1]) in [4, 6, 7, 9, 11]:
            test3 = len(descompunere[0]) == 2 and int(descompunere[0]) > 0 and int(descompunere[1]) < 31
        else:
            if test4:
                if an_bisect(int(descompunere[2])):
                    test3 = len(descompunere[0]) == 2 and int(descompunere[0]) > 0 and int(descompunere[1]) < 30
                else:
                    test3 = len(descompunere[0]) == 2 and int(descompunere[0]) > 0 and int(descompunere[1]) < 29

    return(test1 and test2 and test3 and test4)


# --- comparare date ---  

def este_dupa_data(data_testata, data_referinta):
    assert(type(data_testata) == type(data_referinta) == string)
    assert(este_data(data_referinta) and este_data(data_testata))

    descompunere_test = list(map(int,data_testata.split(".")))
    descompunere_referinta = list(map(int,data_referinta.split(".")))

    if descompunere_test[2] > descompunere_referinta[2]:
        return True
    elif descompunere_test[2] < descompunere_referinta[2]:
        return False

    elif descompunere_test[1] > descompunere_referinta[1]:
        return True
    elif descompunere_test[1] < descompunere_referinta[1]:
        return False 

    else:
        return descompunere_test[0] >= descompunere_referinta[0]


def este_inainte_data(data_testata, data_referinta):
    assert(type(data_testata) == type(data_referinta) == string)
    assert(este_data(data_referinta) and este_data(data_testata))

    descompunere_test = list(map(int,data_testata.split(".")))
    descompunere_referinta = list(map(int,data_referinta.split(".")))

    if descompunere_test[2] < descompunere_referinta[2]:
        return True
    elif descompunere_test[2] > descompunere_referinta[2]:
        return False

    elif descompunere_test[1] < descompunere_referinta[1]:
        return True
    elif descompunere_test[1] > descompunere_referinta[1]:
        return False 

    else:
        return descompunere_test[0] <= descompunere_referinta[0]
    

# --- cerinte ---

def adauga_tranzactie(data, suma, tip): # tranzactie -> none
    assert(type(data) == string == type(tip) and type(suma) == int)
    assert(este_data(data))
    tranzactii.append([data, suma, tip])

def actualizare_tranzactie(data, suma, tip): # tranzactie -> none
    assert(este_data(data))
    assert(type(data) == string == type(tip) and type(suma) == int)

def sterge_tranz_data(data): # string -> none
    assert(type(data) == string)
    assert(este_data(data))
    for element in tranzactii:
        if element[0] == data:
            tranzactii.remove(element)

def sterge_tranz_perioada(data_inceput, data_final): # string -> string -> None
    assert(type(data_inceput) == string)
    assert(este_data(data_inceput))
    assert(type(data_final) == string)
    assert(este_data(data_final))

    for element in tranzactii:
        if este_dupa_data(element[0, data_inceput]) and este_inainte_data(element[0], data_final):
            tranzactii.remove(element)

def sterge_tranz_tip(tip):
    assert(type(tip) == string)
    for element in tranzactii:
        if element[2] == tip:
            tranzactii.remove(element)



# -------- Testare --------



# -------- Interactiune utilizator --------
