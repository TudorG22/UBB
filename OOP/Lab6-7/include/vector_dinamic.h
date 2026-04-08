#pragma once

#include <cstddef>

template <typename ElementT>
class VectorDinamic {
private:
    std::size_t INIT_CAPACITATE = 2;

    ElementT* elemente;
    std::size_t dimensiune;
    std::size_t capacitate;

    void redimensioneaza();

public:
    VectorDinamic();
    VectorDinamic(const VectorDinamic& other);
    ~VectorDinamic();

    void push_back(const ElementT& element);

    std::size_t size() const;
    bool empty() const;

    ElementT& get(std::size_t pozitie);
    const ElementT& get(std::size_t pozitie) const;

    ElementT* begin();
    const ElementT* begin() const;
    ElementT* end();
    const ElementT* end() const;

    void erase(std::size_t pozitie);
};
