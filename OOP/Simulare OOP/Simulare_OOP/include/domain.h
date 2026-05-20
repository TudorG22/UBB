#pragma once

#include <iostream>
#include <string>

using std::string;

class Carte {
    private:
        int isbn;
        string titlu;
        string autor;
        string gen;
        int pret;
        int stoc;

    public:
        Carte() = default;

        /* Creeaza o carte
        Input: isbn, titlu, autor, gen, pret, stoc
        Output: -
        Pre conditii: date valide pentru initializarea unei carti
        Post conditii: carte initializata
        */
        Carte(int isbn, const string& titlu, const string& autor, const string& gen, int pret, int stoc);

        /* Creeaza o copie a unei carti
        Input: alta carte
        Output: -
        Pre conditii: carte initializata
        Post conditii: carte copiata
        
        Carte(const Carte& other);

        Carte(Carte&& other) noexcept = default;
        Carte& operator=(const Carte& other) = default;
        Carte& operator=(Carte&& other) noexcept = default;*/

        /* Returneaza isbn-ul cartii
        Input: -
        Output: isbn-ul cartii
        Pre conditii: carte initializata
        Post conditii: -
        */
        int getIsbn() const;
        /* Seteaza isbn-ul cartii
        Input: isbnNou
        Output: -
        Pre conditii: carte initializata
        Post conditii: isbn actualizat
        */
        void setIsbn(int isbnNou);

        /* Returneaza titlul cartii
        Input: -
        Output: titlul cartii
        Pre conditii: carte initializata
        Post conditii: -
        */
        const string& getTitlu() const;
        /* Seteaza titlul cartii
        Input: titluNou
        Output: -
        Pre conditii: carte initializata
        Post conditii: titlu actualizat
        */
        void setTitlu(const string& titluNou);

        /* Returneaza autorul cartii
        Input: -
        Output: autorul cartii
        Pre conditii: carte initializata
        Post conditii: -
        */
        const string& getAutor() const;
        /* Seteaza autorul cartii
        Input: autorNou
        Output: -
        Pre conditii: carte initializata
        Post conditii: autor actualizat
        */
        void setAutor(const string& autorNou);

        /* Returneaza genul cartii
        Input: -
        Output: genul cartii
        Pre conditii: carte initializata
        Post conditii: -
        */
        const string& getGen() const;

        /* Seteaza genul cartii
        Input: genNou
        Output: -
        Pre conditii: carte initializata
        Post conditii: gen actualizat
        */
        void setGen(const string& genNou);

        /* Returneaza pretul cartii
        Input: -
        Output: pretul cartii
        Pre conditii: carte initializata
        Post conditii: -
        */
        int getPret() const;
        /* Seteaza pretul cartii
        Input: pretNou
        Output: -
        Pre conditii: carte initializata
        Post conditii: pret actualizat
        */
        void setPret(int pretNou);

        /* Returneaza stocul cartii
        Input: -
        Output: stocul cartii
        Pre conditii: carte initializata
        Post conditii: -
        */
        int getStoc() const;
        /* Seteaza stocul cartii
        Input: stocNou
        Output: -
        Pre conditii: carte initializata
        Post conditii: stoc actualizat
        */
        void setStoc(int stocNou);
};
