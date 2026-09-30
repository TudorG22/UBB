def sumNumbers():
    n = int(input("Numar de numere: "))
    numbers = []
    for i in range(0, n):
        numar_curent = int(input(f"Numarul {i+1}: "))
        numbers.append(numar_curent)
    return sum(numbers)

def checkIfPrime():
    n = int(input("Numar de verificat: "))
    for i in range(2, n-1):
        if n % i == 0:
            return False
    return True

def pgcd(a,b):
    m = min(a,b)
    result = 1 
    test = 1
    while test < m:
        test += 1
        if a % test == 0 and b % test == 0:
            result = test
    return result

print(sumNumbers())
print("==========================")
print(checkIfPrime())
print("==========================")
print(pgcd(7,5))
print(pgcd(10,15))