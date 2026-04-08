#include "vector_dinamic.h"
#include "domain.h"

#include <new>
#include <utility>

template <typename ElementT>
ElementT* VectorDinamic<ElementT>::element_ptr(std::size_t index) {
    return reinterpret_cast<ElementT*>(static_cast<char*>(date) + index * dimensiune_element);
}

template <typename ElementT>
const ElementT* VectorDinamic<ElementT>::element_ptr(std::size_t index) const {
    return reinterpret_cast<const ElementT*>(static_cast<const char*>(date) + index * dimensiune_element);
}

template <typename ElementT>
void VectorDinamic<ElementT>::distruge_interval(void* buffer, std::size_t count) {
    auto* baza = static_cast<ElementT*>(buffer);
    for (std::size_t i = 0; i < count; ++i) {
        baza[i].~ElementT();
    }
}

template <typename ElementT>
void VectorDinamic<ElementT>::vector_dinamic_resize() {
    const std::size_t capacitate_noua = capacitate * 2;
    void* date_noi = ::operator new(capacitate_noua * dimensiune_element);

    for (std::size_t i = 0; i < dimensiune; ++i) {
        new (static_cast<char*>(date_noi) + i * dimensiune_element) ElementT(std::move(*element_ptr(i)));
        element_ptr(i)->~ElementT();
    }

    ::operator delete(date);
    date = date_noi;
    capacitate = capacitate_noua;
}

template <typename ElementT>
VectorDinamic<ElementT>::VectorDinamic()
    : date(::operator new(INIT_CAPACITATE * sizeof(ElementT))),
      dimensiune_element(sizeof(ElementT)),
      dimensiune(0),
      capacitate(INIT_CAPACITATE) {
}

template <typename ElementT>
VectorDinamic<ElementT>::VectorDinamic(const VectorDinamic& other)
    : date(::operator new(other.capacitate * other.dimensiune_element)),
      dimensiune_element(other.dimensiune_element),
      dimensiune(other.dimensiune),
      capacitate(other.capacitate) {
    for (std::size_t i = 0; i < dimensiune; ++i) {
        new (static_cast<char*>(date) + i * dimensiune_element) ElementT(*other.element_ptr(i));
    }
}

template <typename ElementT>
VectorDinamic<ElementT>::VectorDinamic(VectorDinamic&& other) noexcept
    : date(other.date),
      dimensiune_element(other.dimensiune_element),
      dimensiune(other.dimensiune),
      capacitate(other.capacitate) {
    other.date = nullptr;
    other.dimensiune = 0;
    other.capacitate = 0;
    other.dimensiune_element = sizeof(ElementT);
}

template <typename ElementT>
VectorDinamic<ElementT>& VectorDinamic<ElementT>::operator=(const VectorDinamic& other) {
    if (this == &other) {
        return *this;
    }

    VectorDinamic copie(other);
    *this = std::move(copie);
    return *this;
}

template <typename ElementT>
VectorDinamic<ElementT>& VectorDinamic<ElementT>::operator=(VectorDinamic&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    if (date != nullptr) {
        distruge_interval(date, dimensiune);
        ::operator delete(date);
    }

    date = other.date;
    dimensiune_element = other.dimensiune_element;
    dimensiune = other.dimensiune;
    capacitate = other.capacitate;

    other.date = nullptr;
    other.dimensiune = 0;
    other.capacitate = 0;
    other.dimensiune_element = sizeof(ElementT);
    return *this;
}

template <typename ElementT>
VectorDinamic<ElementT>::~VectorDinamic() {
    if (date != nullptr) {
        distruge_interval(date, dimensiune);
        ::operator delete(date);
    }
}

template <typename ElementT>
std::size_t VectorDinamic<ElementT>::vector_dinamic_dimensiune() const {
    return dimensiune;
}

template <typename ElementT>
void VectorDinamic<ElementT>::vector_dinamic_adauga(const ElementT& element) {
    if (dimensiune == capacitate) {
        vector_dinamic_resize();
    }
    new (static_cast<char*>(date) + dimensiune * dimensiune_element) ElementT(element);
    dimensiune++;
}

template <typename ElementT>
void VectorDinamic<ElementT>::push_back(const ElementT& element) {
    vector_dinamic_adauga(element);
}

template <typename ElementT>
void VectorDinamic<ElementT>::vector_dinamic_seteaza(std::size_t index, const ElementT& element) {
    *element_ptr(index) = element;
}

template <typename ElementT>
void VectorDinamic<ElementT>::vector_dinamic_sterge(std::size_t index) {
    element_ptr(index)->~ElementT();
    for (std::size_t i = index; i + 1 < dimensiune; ++i) {
        new (element_ptr(i)) ElementT(std::move(*element_ptr(i + 1)));
        element_ptr(i + 1)->~ElementT();
    }
    dimensiune--;
}

template <typename ElementT>
ElementT& VectorDinamic<ElementT>::vector_dinamic_get(std::size_t index) {
    return *element_ptr(index);
}

template <typename ElementT>
const ElementT& VectorDinamic<ElementT>::vector_dinamic_get_const(std::size_t index) const {
    return *element_ptr(index);
}

template <typename ElementT>
std::size_t VectorDinamic<ElementT>::size() const noexcept {
    return vector_dinamic_dimensiune();
}

template <typename ElementT>
bool VectorDinamic<ElementT>::empty() const noexcept {
    return dimensiune == 0;
}

template <typename ElementT>
ElementT& VectorDinamic<ElementT>::operator[](std::size_t index) {
    return vector_dinamic_get(index);
}

template <typename ElementT>
const ElementT& VectorDinamic<ElementT>::operator[](std::size_t index) const {
    return vector_dinamic_get_const(index);
}

template <typename ElementT>
ElementT* VectorDinamic<ElementT>::begin() noexcept {
    return reinterpret_cast<ElementT*>(date);
}

template <typename ElementT>
const ElementT* VectorDinamic<ElementT>::begin() const noexcept {
    return reinterpret_cast<const ElementT*>(date);
}

template <typename ElementT>
ElementT* VectorDinamic<ElementT>::end() noexcept {
    return begin() + dimensiune;
}

template <typename ElementT>
const ElementT* VectorDinamic<ElementT>::end() const noexcept {
    return begin() + dimensiune;
}

template <typename ElementT>
void VectorDinamic<ElementT>::erase(ElementT* position) {
    vector_dinamic_sterge(static_cast<std::size_t>(position - begin()));
}

template class VectorDinamic<Film>;
template class VectorDinamic<const Film*>;
