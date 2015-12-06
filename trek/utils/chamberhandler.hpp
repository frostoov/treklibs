#pragma once

#include "trektypes.hpp"

#include <trek/data/eventrecord.hpp>

namespace trek {

bool createTrackDescription(
	const data::ChamHits& eventTimes,
	const ChamberDescription& chamDesc,
	TrackDescription& trackDesc);

} //trek
