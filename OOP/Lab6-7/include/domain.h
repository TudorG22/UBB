#pragma once

#include <iostream>
#include <string>

using std::string;

class Film {
    private:
        string titlu;
        string gen;
        int an = 0;
        string actor;

    public:
        /* Creeaza un film
        Input: titlu, gen, an, actor
        Output: -
        Pre conditii: date valide pentru initializarea unui film
        Post conditii: film initializat
        */
        Film(const string& titlu, const string& gen, int an, const string& actor);

        /* Creeaza o copie a unui film
        Input: alt film
        Output: -
        Pre conditii: film initializat
        Post conditii: film copiat
        
        Film(const Film& other);

        Film(Film&& other) noexcept = default;
        Film& operator=(const Film& other) = default;
        Film& operator=(Film&& other) noexcept = default;*/

        /* Returneaza titlul filmului
        Input: -
        Output: titlul filmului
        Pre conditii: film initializat
        Post conditii: -
        */
        const string& getTitlu() const;
        /* Seteaza titlul filmului
        Input: titluNou
        Output: -
        Pre conditii: film initializat
        Post conditii: titlu actualizat
        */
        void setTitlu(const string& titluNou);

        /* Returneaza genul filmului
        Input: -
        Output: genul filmului
        Pre conditii: film initializat
        Post conditii: -
        */
        const string& getGen() const;
        /* Seteaza genul filmului
        Input: genNou
        Output: -
        Pre conditii: film initializat
        Post conditii: gen actualizat
        */
        void setGen(const string& genNou);

        /* Returneaza anul aparitiei filmului
        Input: -
        Output: anul aparitiei
        Pre conditii: film initializat
        Post conditii: -
        */
        int getAn() const;
        /* Seteaza anul aparitiei filmului
        Input: anNou
        Output: -
        Pre conditii: film initializat
        Post conditii: an actualizat
        */
        void setAn(int anNou);

        /* Returneaza actorul principal al filmului
        Input: -
        Output: actorul principal
        Pre conditii: film initializat
        Post conditii: -
        */
        const string& getActor() const;

        /* Seteaza actorul principal al filmului
        Input: actorNou
        Output: -
        Pre conditii: film initializat
        Post conditii: actor actualizat
        */
        void setActor(const string& actorNou);
};
