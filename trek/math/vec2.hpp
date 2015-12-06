#pragma once

#include <cstddef>
#include <iosfwd>

namespace trek {
namespace math {

/**
 * @class Vec2
 * @author frostoov
 * @date 03/18/15
 * @file vec2.hpp
 * @brief Вектор в двухмерном пространстве
 */
struct Vec2 {
	double x, y;

	Vec2(double x = 0, double y = 0);
	/**
	 * @brief Унарный плюс
	 * @return Возрщает себя
	 */
	Vec2 operator +() const;
	/**
	 * @brief  Унарный минус
	 * @return Возвращает обраный вектор
	 */
	Vec2 operator -() const;
	/**
	 * @brief Сложение с данным вектором
	 * @param vec Вектор, который прибавляется к данному
	 */
	void operator+= (const Vec2& vec);
	/**
	 * @brief Вычитание из данного вектора
	 * @param vec Вектор, который отнимается от данного
	 */
	void operator-= (const Vec2& vec);
	/**
	 * @brief Вычисление орта данного вектора
	 * @return Орт данного вектора
	 */
	Vec2 ort() const;
	/**
	 * @brief Вычисление длины данного вектора
	 * @return Длина данного вектора
	 */
	double abs() const;
	/**
	 * @brief Вращение вектора
	 * @param ang Угол, на которое производится вращение
	 */
	void rotate(double ang);
};

/**
 * @brief Оператор сравнения
 * @param vec Вектор, с которым производится сравнение
 * @return true - векторы равны, false - если векторы не равны
 */
bool operator==(const Vec2& a, const Vec2& b);
/**
 * @brief operator + Сложение векторов
 * @param a Вектор в двухмерном пространстве
 * @param b Вектор в двухмерном пространстве
 * @return Сумма векторов a и b
 */
Vec2 operator+(const Vec2& a, const Vec2& b);
/**
 * @brief operator - Сложение векторов
 * @param a Вектор в двухмерном пространстве
 * @param b Вектор в двухмерном пространстве
 * @return Разность векторов a и b
 */
Vec2 operator-(const Vec2& a, const Vec2& b);
/**
 * @brief operator * Умножение векторов
 * @param a Вектор в двухмерном пространстве
 * @param b Вектор в двухмерном пространстве
 * @return Скалярное произведение векторов a и b
 */
double operator*(const Vec2& a, const Vec2& b);
/**
 * @brief Оператор умножения вектора на число
 */
Vec2 operator*(const Vec2& vec, double num);
/**
 * @brief Оператор умножения вектора на число
 */
Vec2 operator*(double num, const Vec2& vec);
/**
 * @brief Нахождения угла между векторами
 * @param other
 * @return
 */
double angle(const Vec2& a, const Vec2& b);

std::ostream& operator<<(std::ostream& stream, const Vec2& vec);

} //math
} //trek
