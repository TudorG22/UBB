sterge([],_,_,[]).

sterge([_|T], N, I, R):-
    N == I,
    I1 is I + 1,
    sterge(T, N, I1, R).

sterge([H|T], N, I, [H|R]):-
    N \== I,
    I1 is I + 1,
    sterge(T, N, I1, R).