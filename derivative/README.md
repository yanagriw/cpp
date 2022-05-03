# Derivace

Každý řádek standardního vstupu obsahuje předpis reálné funkce, zapsaný jako výraz v infixu. 
Program takový výraz naparsuje do syntaktického stromu (pomocí algoritmu [shunting-yard](https://en.wikipedia.org/wiki/Shunting_yard_algorithm)), funkci zderivuje, výsledek zjednoduší a v infixu vypíše na výstup.

### Vstupní formát

Každý řádek vstupu obsahuje výraz v infixu, který se může skládat z následujících tokenů oddělených bílými znaky (i závorky):

- **Číselná konstanta** - obsahuje jen cifry (znaky '0'-'9') a nejvýše jednu desetinnou tečku
- **Proměnná x** - značí proměnnou, podle které budeme derivovat (pokud se vyskytne proměnná s jiným názvem, je to chybný vstup)
- **Operátory** +, -, * a / pro vyznačení sčítání, odečítání, násobení a dělení s obvyklou prioritou (*+ i - jsou pouze binární, nikoliv unární*)
- **Závorky (** a **)** se standardním významem.

### Test input
        2 + 3 * x - 1
        ( 2 + 3 ) * x - 1
        x / 0.5 + 4 * x

        ( 8 + 45.5 * 2 - 10 ) * x * x
        x * ( 15 + 32.25 / 0.25 * 0.5 )
        1 + 1.5 / ( x * 8 )

        5 * x * x + 4 * x - 42
        x * x + 2 * x + 1
        4 * x * x * x - 3 * x * x + 2 * x - 1

        * 54 - 82 + x
        2 % 8
        ( 2 + 45
        4 * x * x + 84 )
        ( 28 + 95 * ( 82 )
### Output
        3
        5
        6

        ((89 * x) + (89 * x))
        79.5
        (-12 / ((x * 8) * (x * 8)))

        (((5 * x) + (5 * x)) + 4)
        ((x + x) + 2)
        ((((((4 * x) + (4 * x)) * x) + ((4 * x) * x)) - ((3 * x) + (3 * x))) + 2)

        Input error
        Input error
        Input error
        Input error
        Input error
