prim(N):-
    N > 1,
    prim_aux(N, 2).

prim_aux(N, D):-
    D * D > N.

prim_aux(N, D):-
    D * D =< N,
    N mod D =\= 0,
    D1 is D + 1,
    prim_aux(N, D1).

dubleaza([], []).

dubleaza([H|T], [H,H|R]):-
    prim(H),
    dubleaza(T, R).

dubleaza([H|T], [H|R]):-
    \+ prim(H),
    dubleaza(T, R).



dubleaza_sub([], []).

dubleaza_sub([[H|T1]|T], [R1|R]):-
    !,
    dubleaza([H|T1], R1),
    dubleaza_sub(T, R).

dubleaza_sub([H|T], [H|R]):-
    dubleaza_sub(T, R).