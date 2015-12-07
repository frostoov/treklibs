#pragma once

#include <trek/math/hexahedron.hpp>
#include <trek/math/coordsystem.hpp>
#include <trek/data/eventrecord.hpp>

#include "trektypes.hpp"

namespace trek {
/*!
 * \class Chamber
 * \author frostoov
 * \date 03/18/15
 * \file chamber.hpp
 * \brief Дрейфовая камера
 */
class Chamber {
public:
	/*!
	 * \brief Создание камеры по описанию
	 */
	Chamber(const ChamberDescription& chamberInfo);
	/*!
	 * \brief Создание проекции трека
	 * \param chamHits измерения камеры
	 * \return Описание трека
	 * \throw std::domain_error Если нельзя реконструировать трек
	 */
	TrackDescription createTrack(const data::ChamHits& chamHits);
	/*!
	 * \brief Проецирование трехмерной прямой на фронтальную плоскость камеры
	 */
	math::Line2 lineProjection(math::Line3 line) const;

	/*!
	 * \brief Номер плоскости камеры
	 */
	uint32_t plane() const;
	/*!
	 * \brief Номер группы камеры
	 * Группа камер - множество камер по которым можно восстановить трехмерный трек
	 */
	uint32_t group() const;
	/*!
	 * \brief Номер плоскости камеры
	 */
	const ChamberPoints& points() const;
	/*!
	 * \brief Геометрическое представление камеры
	 */
	const math::Hexahedron& hexahedron() const;
protected:
	static math::CoordSystem3 getChamberSystem(const ChamberPoints& pos);
	static math::Hexahedron   getHexahedron(const ChamberPoints& pos);
private:
	ChamberDescription mDescription;
	math::CoordSystem3 mChamberSystem;
	math::Hexahedron   mHexahedron;

	constexpr static double mChamberWidth   = 500;
	constexpr static double mChamberHeight  = 112;
	constexpr static double mChamberLength  = 4000;
};

}
