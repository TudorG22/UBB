#pragma once

#include <string>

using std::string;

class Film {
    private:
        string titlu;
        string gen;
        int an;
        string actor;

    public:
        //
        Film(const string& titlu, const string& gen, int an, const string& actor);

        //
        const string& getTitlu() const;
        //
        void setTitlu(const string& titluNou);

        //
        const string& getGen() const;
        //
        void setGen(const string& genNou);

        //
        int getAn() const;
        //
        void setAn(int anNou);

        //
        const string& getActor() const;

        //
        void setActor(const string& actorNou);
};
