#ifndef PISENSEHATREAL_HPP_
#define PISENSEHATREAL_HPP_

#include "PiSenseHat.hpp"

#include <mutex>
#include <memory>

class PiSenseHatReal : public PiSenseHat {
public:
	PiSenseHatReal(std::mutex &mutex);
	virtual ~PiSenseHatReal();

	bool init(void);
	void fini(void);

	RTIMU_DATA ReadValues(void);

private:

	PiSenseHatReal(const PiSenseHatReal &) = delete;
	void operator=(const PiSenseHatReal &) = delete;

	RTIMUSettings m_imu_settings;
	std::unique_ptr<RTIMU> m_imu;
	std::mutex &m_mutex;
};

#endif /* PISENSEHATREAL_HPP_ */
