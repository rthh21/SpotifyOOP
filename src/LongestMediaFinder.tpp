/**
 * @brief Construct a new Longest Media Finder< T>:: Longest Media Finder object
 * 
 * @tparam T 
 * @param mediaCollection 
 */

template <typename T>
LongestMediaFinder<T>::LongestMediaFinder(const std::vector<T>& mediaCollection) : collection(mediaCollection) {}

template <typename T>
T LongestMediaFinder<T>::getLongestMedia() const {
    if (collection.empty()) {
        return T();
    }

    T longest = collection[0];
    for (const auto& media : collection) {
        if (media.getDuration() > longest.getDuration()) {
            longest = media;
        }
    }

    return longest;
}