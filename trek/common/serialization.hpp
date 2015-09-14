#ifndef TREK_COMMON_SERIALIZTION_HPP
#define TREK_COMMON_SERIALIZTION_HPP

#include <ostream>
#include <istream>
#include <vector>

namespace trek {

template<typename T, typename = std::enable_if_t< std::is_fundamental<T>::value> >
void serialize(std::ostream& stream, T val) {
    stream.write(reinterpret_cast<const char*>(&val), sizeof(T));
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value> >
inline void deserialize(std::istream& stream, T& val) {
    stream.read(reinterpret_cast<char*>(&val), sizeof(T));
}

template<typename T, typename = std::enable_if_t<std::is_pointer<T>::value> >
inline void serialize(std::ostream& stream, const T val, size_t size) {
    stream.write(reinterpret_cast<const char*>(val), size);
}

template<typename T, typename = std::enable_if_t<std::is_pointer<T>::value> >
inline void deserialize(std::istream& stream, T val, size_t size) {
    stream.read(reinterpret_cast<char*>(val), size);
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value> >
inline void serialize(std::ostream& stream, const std::vector<T>& vec) {
    stream.write(reinterpret_cast<const char*>(vec.data()), vec.size() * sizeof(T));
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value> >
inline void deserialize(std::istream& stream, std::vector<T>& vec) {
    stream.read(reinterpret_cast<char*>(vec.data()), vec.size() * sizeof(T));
}

template<typename T, typename = std::enable_if_t<std::is_class<T>::value> >
inline void serialize(std::ostream& stream, const T& object) {
    object.serialize(stream);
}

template<typename T, typename = std::enable_if_t<std::is_class<T>::value> >
inline bool deserialize(std::istream& stream, T& object) {
    object.deserialize(stream);
    return true;
}

template<typename T, typename = std::enable_if_t<std::is_fundamental<T>::value> >
constexpr size_t getSize() {
    return sizeof(T);
}

template<typename T, typename = std::enable_if_t<std::is_class<T>::value> >
constexpr size_t getSize(void* = nullptr) {
    return T::getSize();
}

} //trek

#endif // TREK_COMMON_SERIALIZTION_HPP

