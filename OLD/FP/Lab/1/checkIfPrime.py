def checkIfPrime():
    n = int(input("Numar de verificat: "))
    for i in range(2, n-1):
        if n % i == 0:
            return False
    return True

print(checkIfPrime()) # WRONG!! 1 is not prime