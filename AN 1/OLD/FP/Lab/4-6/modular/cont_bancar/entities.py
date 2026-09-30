# -------- Entitate tranzactie --------
# Reprezentare cu dictionar: {"data": str, "suma": int, "tip": str}

def creeaza_tranzactie(data: str, suma: int, tip: str) -> dict:
    return {"data": data, "suma": suma, "tip": tip}

def get_data(tr: dict) -> str:
    return tr["data"]

def get_suma(tr: dict) -> int:
    return tr["suma"]

def get_tip(tr: dict) -> str:
    return tr["tip"]

def set_data(tr: dict, data: str) -> None:
    tr["data"] = data

def set_suma(tr: dict, suma: int) -> None:
    tr["suma"] = suma

def set_tip(tr: dict, tip: str) -> None:
    tr["tip"] = tip
