#include "vector_dinamic.h"
#include "domain.h"

template <typename ElementT>
void VectorDinamic<ElementT>::redimensioneaza() {
    capacitate *= 2;
    ElementT* elemente_noi = new ElementT[capacitate];
    for (std::size_t i = 0; i < dimensiune; ++i) {
        elemente_noi[i] = elemente[i];
    }
    delete[] elemente;
    elemente = elemente_noi;
}

template <typename ElementT>
VectorDinamic<ElementT>::VectorDinamic()
    : elemente(new ElementT[INIT_CAPACITATE]), dimensiune(0), capacitate(INIT_CAPACITATE) {
}

template <typename ElementT>
VectorDinamic<ElementT>::VectorDinamic(const VectorDinamic& other)
    : elemente(new ElementT[other.capacitate]), dimensiune(other.dimensiune), capacitate(other.capacitate) {
    for (std::size_t i = 0; i < dimensiune; ++i) {
        elemente[i] = other.elemente[i];
    }
}

template <typename ElementT>
VectorDinamic<ElementT>::~VectorDinamic() {
    delete[] elemente;
}

template <typename ElementT>
void VectorDinamic<ElementT>::push_back(const ElementT& element) {
    if (dimensiune == capacitate) {
        redimensioneaza();
    }
    elemente[dimensiune] = element;
    dimensiune++;
}

template <typename ElementT>
std::size_t VectorDinamic<ElementT>::size() const {
    return dimensiune;
}

template <typename ElementT>
bool VectorDinamic<ElementT>::empty() const {
    return dimensiune == 0;
}

template <typename ElementT>
ElementT& VectorDinamic<ElementT>::get(std::size_t pozitie) {
    return elemente[pozitie];
}

template <typename ElementT>
const ElementT& VectorDinamic<ElementT>::get(std::size_t pozitie) const {
    return elemente[pozitie];
}

template <typename ElementT>
ElementT* VectorDinamic<ElementT>::begin() {
    return elemente;
}

template <typename ElementT>
const ElementT* VectorDinamic<ElementT>::begin() const {
    return elemente;
}

template <typename ElementT>
ElementT* VectorDinamic<ElementT>::end() {
    return elemente + dimensiune;
}

template <typename ElementT>
const ElementT* VectorDinamic<ElementT>::end() const {
    return elemente + dimensiune;
}

template <typename ElementT>
void VectorDinamic<ElementT>::erase(std::size_t pozitie) {
    for (std::size_t i = pozitie; i + 1 < dimensiune; ++i) {
        elemente[i] = elemente[i + 1];
    }
    dimensiune--;
}

template class VectorDinamic<Film>;
template class VectorDinamic<const Film*>;
