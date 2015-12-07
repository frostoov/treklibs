#pragma once

#include <iosfwd>

namespace trek {
namespace math {

struct Vec3 {
	double x, y, z;
	Vec3(double x_ = 0, double y_ = 0, double z_ = 0);

	/*!
	 * \brief Унарный плюс
	 * \return Возрщает себя
	 */
	Vec3 operator+() const;
	/*!
	 * \brief  Унарный минус
	 * \return Возвращает обраный вектор
	 */
	Vec3 operator-() const;
	/*!
	 * \brief Сложение с данным вектором
	 * \param vec Вектор, который прибавляется к данному
	 */
	void operator+= (const Vec3& vec);
	/*!
	 * \brief Вычитание из данного вектора
	 * \param vec Вектор, который отнимается от данного
	 */
	void operator-= (const Vec3& vec);
	/*!
	 * \brief Вычисление орта данного вектора
	 * \return Орт данного вектора
	 */
	Vec3 ort() const;
	/*!
	 * \brief Вычисление длины данного вектора
	 * \return Длина данного вектора
	 */
	double abs() const;

	/*!
	 * \brief Вращение вектора вокруг оси X
	 * \param ang Угол, на которое производится вращение
	 */
	void rotateX(double ang);
	/*!
	 * \brief Вращение вектора вокруг оси Y
	 * \param ang Угол, на которое производится вращение
	 */
	void rotateY(double ang);
	/*!
	 * \brief Вращение вектора вокруг оси Z
	 * \param ang Угол, на которое производится вращение
	 */
	void rotateZ(double ang);
	/*!
	 * \brief Вращение вектора вокруг заданого вектора
	 * \param vec Вектор, вокруг которого, производится вращение
	 * \param ang Угол, на которое производится вращение
	 */
	void rotate(const Vec3& vec, double ang);
};

/*!
 * \brief Оператор сравнения
 * \param vec Вектор, с которым производится сравнение
 * \return true - векторы равны, false - если векторы не равны
 */
bool operator==(const Vec3& a, const Vec3& b);
/*!
 * \brief operator * Скалярное умножение векторов
 * \param a Вектор в трехмерном пространстве
 * \param b Вектор в трехмерном пространстве
 * \return Скалярное произведение векторов a и b
 */
double operator* (const Vec3& a, const Vec3& b);
/*!
 * \brief operator * Векторное умножение векторов
 * \param a Вектор в трехмерном пространстве
 * \param b Вектор в трехмерном пространстве
 * \return Векторное произведение векторов a и b
 */
Vec3 operator& (const Vec3& a, const Vec3& b);
/*!
 * \brief Оператор умножения вектора на число
 */
Vec3 operator* (const Vec3& vec, double num);
/*!
 * \brief Оператор умножения вектора на число
 */
Vec3 operator/ (const Vec3& vec, double num);
/*!
 * \brief operator + Сложение векторов
 * \param a Вектор в трехмерном пространстве
 * \param b Вектор в трехмерном пространстве
 * \return Сумма векторов a и b
 */
Vec3 operator+ (const Vec3& a, const Vec3& b);
/*!
 * \brief operator - Вычитание векторов
 * \param a Вектор в трехмерном пространстве
 * \param b Вектор в трехмерном пространстве
 * \return Разность векторов a и b
 */
Vec3 operator- (const Vec3& a, const Vec3& b);
/*!
 * \brief Нахождения угла между векторами
 * \param other
 */
double angle(const Vec3& a, const Vec3& b);

std::ostream& operator<<(std::ostream& stream, const Vec3& vec);

} //math
} //trek
