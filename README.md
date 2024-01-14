# Strukture podataka i algoritmi - projekat

Cilj ovog projekta bio je implementirati stablo s određenim funkcionalnostima:

1. **Iterator i reverse iterator za kretanje kroz stablo.**
   - Prolazak kroz čitavo stablo je vremenske kompleksnosti O(n).
   - Radi petlja `for(auto it = s.Begin(); it != s.End(); it++)`.

2. **Funkcija provjere podskupa:**
   - Vremenska složenost: O(m + n), gdje su m i n brojevi elemenata u ta dva stabla.

3. **Funkcija indeksiranja:**
   - `stablo[k]` vraća k-ti po veličini element stabla (indeksiranje kreće od nule).
   - Vremenska složenost: O(h), gdje je h visina stabla.

## Struktura projekta

- `stablo.h` i `stablo.cpp`: Implementacija binarnog stabla pretrage.
- `podstablo.h` i `podstablo.cpp`: Funkcije vezane uz operacije podstabla (dodatno).
- `main.cpp`: Primjeri korištenja i testiranja implementiranih funkcionalnosti.

## Autor

- **Student:** Ema Djedović
- **Profesor:** Prof. dr. Esmir Pilav
- **Asistent:** Mr. Admir Beširević
- **Verzija:** 01/2024, PMF Sarajevo
