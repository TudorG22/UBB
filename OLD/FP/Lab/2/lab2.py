# -- 8 ----------
def maxFromDigits():
    n = input("n = ")
    digits = list(n)
    digits_ordered = sorted(digits, reverse = True)
    m = int("".join(digits_ordered))
    return(m)

#print(maxFromDigits())


# -- 8+1 ----------
def palindrom():
    n = input("n = ")
    digits = list(n)
    digits_reverse = reversed(digits)
    m = int("".join(digits_reverse))
    return(m)

print(palindrom())