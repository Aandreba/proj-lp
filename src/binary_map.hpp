#pragma once

#include <stdexcept>
#include <tuple>
#include <vector>

template <class K, class V>
class binary_map {
   private:
    typedef std::vector<std::pair<K, V>> vector;

    vector inner;

   public:
    binary_map() : inner({}) {}
    typedef typename vector::iterator iterator;
    typedef typename vector::const_iterator const_iterator;

    /* Average Case: O(n) */
    std::pair<iterator, bool> insert(K key, V value) {
        const auto search = _binary_search(key, 0, size());
        auto it = this->begin() + search.first;
        this->inner.insert(it, std::make_pair(key, value));
        return std::make_pair(it, search.second);
    }

    /* Worst Case: O(log(n)) */
    V& operator[](K key) {
        const auto search = _binary_search(key, 0, size());
        if (!search.second) {
            auto it = this->begin() + search.first;
            this->inner.insert(it, std::make_pair(key, V()));
            return *it;
        }
        return this->inner[search.first].second;
    }

    V& at(const K& key) {
        const auto search = _binary_search(key, 0, size());
        if (!search.second) {
            throw std::out_of_range("key not found");
        }
        return this->inner.at(search.first).second;
    }

    const V& at(const K& key) const {
        const auto search = _binary_search(key, 0, size());
        if (!search.second) {
            throw std::out_of_range("key not found");
        }
        return this->inner.at(search.first).second;
    }

    /* UTILS */
    inline V&

        inline void
        reserve(size_t capacity) {
        return this->inner.reserve(capacity);
    }

    inline void clear() noexcept {
        return this->inner.clear();
    }

    inline bool empty() const noexcept {
        return this->inner.empty();
    }

    inline std::size_t size() const noexcept {
        return this->inner.size();
    }

    /* ITERATOR  */
    inline iterator begin() noexcept {
        return this->inner.begin();
    }

    inline const_iterator cbegin() const noexcept {
        return this->inner.cbegin();
    }

    inline iterator end() noexcept {
        return this->inner.end();
    }

    inline const_iterator cend() const noexcept {
        return this->inner.cend();
    }

   private:
    std::pair<std::size_t, bool> _binary_search(
        const K& needle, std::size_t start, std::size_t end) const {
        std::size_t midpoint = start + (end - start) / 2;
        if (midpoint >= this->size()) {
            return std::make_pair(midpoint, false);
        }

        const std::pair<K, V>& midvalue = this->inner.at(midpoint);
        if (midvalue.first == needle) {
            return std::make_pair(midpoint, true);
        } else if (end == start) {
            return std::make_pair(midpoint, false);
        } else if (midvalue.first > needle) {
            return _binary_search(needle, start, midpoint);
        } else {
            return _binary_search(needle, midpoint + 1, end);
        }
    }
};
