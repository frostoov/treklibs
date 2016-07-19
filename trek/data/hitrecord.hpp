#pragma once

#include <cstdint>
#include <iosfwd>

namespace trek {
namespace data {

/*!
 * \brief Запись хита TDC
 *  Хит содержит номер камеры и проволки (нумерация с 0), измерение (вермя от начала окна в пикосекундах)
 */
class HitRecord {
public:
    enum class Type {
        leading  = 0,
        trailing = 1,
    };
public:
    HitRecord(Type type, uint32_t wire, uint32_t chamber, uint32_t time);
    HitRecord(std::istream& stream);
    /*!
     * \brief Проволка хита
     */
    uint32_t wire() const;
    /*!
     * \brief Камера хита
     */
    uint32_t chamber() const;
    /*!
     * \brief Измерение хита
     */
    uint32_t time() const;
    /*!
     * \brief Тип хита (leading/trailing)
     */
    Type type() const;

    void serialize(std::ostream& stream) const;
    void deserialize(std::istream& stream);
private:
    uint32_t mChannel;
    uint32_t mTime;
};

} //data
} //trek
