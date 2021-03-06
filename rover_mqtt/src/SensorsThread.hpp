#ifndef SENSORSTHREAD_HPP_
#define SENSORSTHREAD_HPP_

#include "RobotSensorValues.hpp"
#include "SelectLoopThread.hpp"
#include <RTIMULib.h>

#include "UltraBorg.hpp"
#include "PiSenseHat.hpp"
#include "ADS1115.hpp"

class SensorsThread : public SelectLoopThread {
public:
	SensorsThread(RobotSensorValues &sensor_values, UltraBorg &ultra_borg,
			  PiSenseHat &pi_sense_hat, ADS1115 &ads1115);
	virtual ~SensorsThread();

	virtual void timeout(void);

private:
	RobotSensorValues &m_sensor_values;
	UltraBorg &m_ultra_borg;
	PiSenseHat &m_pi_sense_hat;
	ADS1115 &m_ads1115;

	SensorsThread(const SensorsThread&) = delete;
	void operator=(const SensorsThread&) = delete;
};

#endif /* SENSORSTHREAD_HPP_ */
