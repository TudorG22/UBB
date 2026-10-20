substituie([],_,_,[]).

substituie([H|T], E, L, R):-
    H == E,
    substituie(T, E, L, R1),
    append(L, R1, R).

substituie([H|T], E, L, [H|R]):-
    H \== E,
    substituie(T, E, L, R).