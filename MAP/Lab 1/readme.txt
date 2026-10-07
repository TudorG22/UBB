PROIECTARE - EXPRESII CU NUMERE COMPLEXE

Programul primeste argumentele:
2 + 3 * i + 5 - 6 * i + -2 + i

CommandLineExpressionParser verifica expresia si grupeaza argumentele care
formeaza fiecare numar complex. ArithmeticExpression aplica operatia de la
stanga la dreapta si obtine rezultatul.

SABLOANE DE PROIECTARE

Strategy:
Operation este interfata comuna, iar Addition, Subtraction, Multiplication si
Division sunt strategiile concrete. ArithmeticExpression poate folosi oricare
dintre ele.

Factory:
OperationFactory creeaza operatia potrivita pentru simbolul +, -, * sau /.

Singleton:
OperationFactory are constructor privat si o singura instanta, obtinuta prin
metoda getInstance.

PRINCIPII SOLID

Single Responsibility:
Fiecare clasa are o singura responsabilitate: numar complex, parsare,
crearea operatiei sau evaluarea expresiei.

Open/Closed si Liskov Substitution:
Operatiile implementeaza aceeasi interfata. O operatie poate fi inlocuita cu
alta fara schimbarea clasei ArithmeticExpression.

Interface Segregation:
Interfetele Operation si ExpressionParser contin doar metodele necesare.

Dependency Inversion:
ArithmeticExpression depinde de interfata Operation, iar Main depinde de
interfata ExpressionParser, nu de implementarile concrete.
