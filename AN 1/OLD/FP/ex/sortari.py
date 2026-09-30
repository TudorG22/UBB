# sortari.py

def _default_cmp(a, b):
    return (a > b) - (a < b)

def _build_cmp(key=None, cmp=None):
    if cmp is not None:
        return cmp
    if key is None:
        return _default_cmp
    return lambda a, b: _default_cmp(key(a), key(b))

def _partition(arr, low, high, cmp):
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if cmp(arr[j], pivot) <= 0:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

def _quick_sort(arr, low, high, cmp):
    if low >= high:
        return
    p = _partition(arr, low, high, cmp)
    _quick_sort(arr, low, p - 1, cmp)
    _quick_sort(arr, p + 1, high, cmp)

def _gnome_sort(arr, cmp):
    i = 0
    n = len(arr)
    while i < n:
        if i == 0 or cmp(arr[i - 1], arr[i]) <= 0:
            i += 1
        else:
            arr[i], arr[i - 1] = arr[i - 1], arr[i]
            i -= 1

def generic_sort(lst, *, key=None, reverse=False, cmp=None, algorithm="quick"):
    """
    Sortare generica tip sorted():
      - key: functie cheie
      - reverse: bool
      - cmp: comparator (-1/0/1)
      - algorithm: "quick" sau "gnome"
    Returneaza o lista NOUA sortata.
    """
    arr = list(lst)
    comparator = _build_cmp(key=key, cmp=cmp)

    if algorithm == "quick":
        _quick_sort(arr, 0, len(arr) - 1, comparator)
    elif algorithm == "gnome":
        _gnome_sort(arr, comparator)
    #elif:
     #   _sortare(arr,comparator)
    else:
        raise ValueError("Algoritm necunoscut.")
    if reverse:
        arr.reverse()
    return arr
