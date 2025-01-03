#ifndef LONGEST_MEDIA_FINDER_H
#define LONGEST_MEDIA_FINDER_H

#include <vector>

template <typename T>
class LongestMediaFinder {
private:
    std::vector<T> collection;

public:
    LongestMediaFinder(const std::vector<T>& mediaCollection);
    T getLongestMedia() const;
};

#include "LongestMediaFinder.tpp"

#endif
