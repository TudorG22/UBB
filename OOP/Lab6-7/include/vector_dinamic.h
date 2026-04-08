#pragma once

#include <cstddef>
#include <new>
#include <utility>

template <typename ElementT>
class VectorDinamic {
private:
    static constexpr std::size_t INIT_CAPACITATE = 2;

    void* date;
    std::size_t dimensiune_element;
    std::size_t dimensiune;
    std::size_t capacitate;

    ElementT* element_ptr(std::size_t index);
    const ElementT* element_ptr(std::size_t index) const;
    static void distruge_interval(void* buffer, std::size_t count);
    void vector_dinamic_resize();

public:
    /* Creeaza vectorul dinamic
    Input: -
    Output: vector nou
    Pre conditii: -
    Post conditii: vector gol, initializat
    */
    VectorDinamic();

    /* Creeaza o copie a vectorului dinamic
    Input: alt vector
    Output: vector nou
    Pre conditii: vector valid
    Post conditii: vector copiat
    */
    VectorDinamic(const VectorDinamic& other);

    /* Creeaza un vector prin mutare
    Input: alt vector temporar
    Output: vector nou
    Pre conditii: vector valid
    Post conditii: resursele sunt mutate
    */
    VectorDinamic(VectorDinamic&& other);

    /* Copiaza un vector dinamic
    Input: alt vector
    Output: referinta la vectorul curent
    Pre conditii: vectori valizi
    Post conditii: vectorul curent este copiat
    */
    VectorDinamic& operator=(const VectorDinamic& other);

    /* Muta un vector dinamic
    Input: alt vector temporar
    Output: referinta la vectorul curent
    Pre conditii: vectori valizi
    Post conditii: resursele sunt mutate in vectorul curent
    */
    VectorDinamic& operator=(VectorDinamic&& other);

    /* Distruge vectorul dinamic
    Input: -
    Output: -
    Pre conditii: vector initializat
    Post conditii: memorie eliberata
    */
    ~VectorDinamic();

    /* Returneaza dimensiunea vectorului
    Input: -
    Output: numar elemente
    Pre conditii: vector initializat
    Post conditii: -
    */
    std::size_t vector_dinamic_dimensiune() const;

    /* Adauga un element in vector
    Input: element
    Output: -
    Pre conditii: vector initializat, element valid
    Post conditii: elementul este adaugat la final
    */
    void vector_dinamic_adauga(const ElementT& element);

    /* Adauga un element in vector
    Input: element
    Output: -
    Pre conditii: vector initializat, element valid
    Post conditii: elementul este adaugat la final
    */
    void push_back(const ElementT& element);

    /* Construieste un element direct in vector
    Input: argumente pentru constructorul elementului
    Output: -
    Pre conditii: vector initializat
    Post conditii: elementul este adaugat la final
    */
    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (dimensiune == capacitate) {
            vector_dinamic_resize();
        }
        new (static_cast<char*>(date) + dimensiune * dimensiune_element) ElementT(std::forward<Args>(args)...);
        dimensiune++;
    }

    /* Seteaza elementul de pe index
    Input: index, element
    Output: -
    Pre conditii: vector initializat, index valid, element valid
    Post conditii: elementul de pe index este inlocuit
    */
    void vector_dinamic_seteaza(std::size_t index, const ElementT& element);

    /* Sterge elementul de pe index
    Input: index
    Output: -
    Pre conditii: vector initializat, index valid
    Post conditii: elementul este eliminat
    */
    void vector_dinamic_sterge(std::size_t index);

    /* Returneaza referinta la element
    Input: index
    Output: referinta la element
    Pre conditii: vector initializat, index valid
    Post conditii: -
    */
    ElementT& vector_dinamic_get(std::size_t index);

    /* Returneaza referinta const la element
    Input: index
    Output: referinta const la element
    Pre conditii: vector initializat, index valid
    Post conditii: -
    */
    const ElementT& vector_dinamic_get_const(std::size_t index) const;

    /* Returneaza dimensiunea vectorului
    Input: -
    Output: numar elemente
    Pre conditii: vector initializat
    Post conditii: -
    */
    std::size_t size() const;

    /* Verifica daca vectorul este gol
    Input: -
    Output: true daca vectorul este gol, false altfel
    Pre conditii: vector initializat
    Post conditii: -
    */
    bool empty() const;

    /* Returneaza elementul de pe index
    Input: index
    Output: referinta la element
    Pre conditii: vector initializat, index valid
    Post conditii: -
    */
    ElementT& operator[](std::size_t index);

    /* Returneaza elementul de pe index
    Input: index
    Output: referinta const la element
    Pre conditii: vector initializat, index valid
    Post conditii: -
    */
    const ElementT& operator[](std::size_t index) const;

    /* Returneaza iterator la primul element
    Input: -
    Output: iterator
    Pre conditii: vector initializat
    Post conditii: -
    */
    ElementT* begin();

    /* Returneaza iterator const la primul element
    Input: -
    Output: iterator const
    Pre conditii: vector initializat
    Post conditii: -
    */
    const ElementT* begin() const;

    /* Returneaza iterator la final
    Input: -
    Output: iterator
    Pre conditii: vector initializat
    Post conditii: -
    */
    ElementT* end();

    /* Returneaza iterator const la final
    Input: -
    Output: iterator const
    Pre conditii: vector initializat
    Post conditii: -
    */
    const ElementT* end() const;

    /* Sterge elementul indicat de iterator
    Input: pozitie
    Output: -
    Pre conditii: vector initializat, pozitie valida
    Post conditii: elementul este eliminat
    */
    void erase(ElementT* position);
};
