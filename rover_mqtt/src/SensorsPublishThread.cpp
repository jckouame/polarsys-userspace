#include <unistd.h>

#include <iostream>
#include <thread>

#include <mosquittopp.h>

#include <sensors.pb.h>
#include <SensorsPublishThread.hpp>

#define MQTT_BROKER_ADDR "127.0.0.1"
#define MQTT_BROKER_PORT 1883
#define MQTT_SENSORS_TOPIC "/polarsys-rover/sensors"

SensorsPublishThread::SensorsPublishThread(const RobotSensorValues &sensor_values,
					   MqttInterface &mqtt_interface)
: SelectLoopThread("mqtt-thread", 200),
  m_sensor_values(sensor_values),
  m_mqtt_interface(mqtt_interface),
  m_protobuf_sensors(new PolarsysRover::RoverSensors())
{
	m_protobuf_sensors->set_allocated_accel(new PolarsysRover::Acceleration());
}

void SensorsPublishThread::timeout (void)
{
	std::string encoded;

	m_protobuf_sensors->Clear();

	/* IMU */
	RTIMU_DATA imu_data = m_sensor_values.getIMUData();

	if (imu_data.accelValid) {
	auto accel = m_protobuf_sensors->mutable_accel();
	accel->set_x(imu_data.accel.x());
	accel->set_y(imu_data.accel.y());
	accel->set_z(imu_data.accel.z());
	}
	if (imu_data.gyroValid) {
	auto gyro = m_protobuf_sensors->mutable_gyro();
	gyro->set_x(imu_data.gyro.x());
	gyro->set_y(imu_data.gyro.y());
	gyro->set_z(imu_data.gyro.z());
	}
	if (imu_data.compassValid) {
	auto compass = m_protobuf_sensors->mutable_compass();
	compass->set_x(imu_data.compass.x());
	compass->set_y(imu_data.compass.y());
	compass->set_z(imu_data.compass.z());
	}

	/* Sonar */
	SonarDistance sonar_distance = m_sensor_values.getSonarDistance();

	if (sonar_distance.sonar_distance_valid) {
	m_protobuf_sensors->set_sonar(sonar_distance.sonar_distance);
	}

	m_protobuf_sensors->SerializeToString(&encoded);

	m_mqtt_interface.publish(MQTT_SENSORS_TOPIC, encoded.length(),
				 encoded.c_str());
}

