def pgcd():
    a = int(input("a = "))
    b = int(input("b = "))
    m = min(a,b)
    result = 1 
    test = 1
    while test < m:
        test += 1
        if a % test == 0 and b % test == 0:
            result = test
    return result

print(pgcd())