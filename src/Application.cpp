#include <BMRecord_Lib.h>
#include <spdlog/spdlog.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <errno.h>

#define LOG_INFO_MESEAGE(INFO_MESSAGE) spdlog::info("{0}",INFO_MESSAGE.message)
#define LOG_ERROR_MESEAGE(ERROR_MESSAGE) spdlog::error("err: {0}: - {1}",ERROR_MESSAGE.code, ERROR_MESSAGE.message)

#define APPLICATION_INFO(INFO_MESSAGE) spdlog::info(INFO_MESSAGE)
#define APPLICATION_ERROR(ERROR_MESSAGE) spdlog::error(ERROR_MESSAGE)

// Display sample rate / Display read data
constexpr auto show_sample_rate = true;

constexpr auto sample_per_read = 1000;

//{CH0 ,CH1 ... CH15} X 1000
uint16_t test_data[sample_per_read * 16];

int _count_ = 0;
int _timer_thread_enable_ = true;

void _timer_thread_()
{
	while (_timer_thread_enable_)
	{
		std::chrono::seconds duration(1);
		std::this_thread::sleep_for(duration);
		if (show_sample_rate) std::cout << _count_ * sample_per_read << std::endl;
		_count_ = 0;
	}
}

int main()
{
	// Initializing logs
	BMRecord_Lib::ErrorManager::enableErrorManager(true);
	auto& em = BMRecord_Lib::ErrorManager::getInstance();

	// Initialize the DLL
	if (BMRecord_Lib::Application::Init())
	{
		if (em.hasError())
		{
			auto error = em.getLastError();
			LOG_ERROR_MESEAGE(error);
			return error.code;
		}
	}

	while (em.hasInfo())
	{
		auto info = em.getFirstInfo();
		LOG_INFO_MESEAGE(info);
	}

	int match_device_count = 0;

	// Detect connected devices
	if (BMRecord_Lib::Application::CheckConnectedDevice(match_device_count))
	{
		if (em.hasError())
		{
			auto error = em.getLastError();
			LOG_ERROR_MESEAGE(error);
			return error.code;
		}
		APPLICATION_ERROR("No device is connected, please check the device power supply and connection.");
		return -EEXIST;
	}
	else APPLICATION_INFO("At least one device is matched.");

	while (em.hasInfo())
	{
		auto info = em.getFirstInfo();
		LOG_INFO_MESEAGE(info);
	}

	// Connect to the specified device
	if (BMRecord_Lib::Application::ConnectDeviceByIndex(0))
	{
		if (em.hasError())
		{
			auto error = em.getLastError();
			LOG_ERROR_MESEAGE(error);
			return error.code;
		}
	}
	else APPLICATION_INFO("Success Connected!");

	// Reset device
	if (BMRecord_Lib::Application::Reset())
	{
		if (em.hasError())
		{
			auto error = em.getLastError();
			LOG_ERROR_MESEAGE(error);
			return error.code;
		}
	}
	else APPLICATION_INFO("Success Reset board!");

	// Set high pass cutoff frequency level 0
	if (BMRecord_Lib::Application::setHighPassCutoffFrequency(0))
	{
		if (em.hasError())
		{
			auto error = em.getLastError();
			LOG_ERROR_MESEAGE(error);
			return error.code;
		}
	}
	else APPLICATION_INFO("Success set high pass cutoff frequency level 0");

	// Set gain level 0
	if (BMRecord_Lib::Application::setGain(0))
	{
		if (em.hasError())
		{
			auto error = em.getLastError();
			LOG_ERROR_MESEAGE(error);
			return error.code;
		}
	}
	else APPLICATION_INFO("Success set gain level 0");

	// Set sampling rate 20K
	if (BMRecord_Lib::Application::setSampleRate(BMRecord_Lib::AmplifierSampleRate::SampleRate20000Hz))
	{
		if (em.hasError())
		{
			auto error = em.getLastError();
			LOG_ERROR_MESEAGE(error);
			return error.code;
		}
	}
	else APPLICATION_INFO("Success Set SampleRate to 20000Hz");

	// Start sampling
	if (BMRecord_Lib::Application::startSample())
	{
		if (em.hasError())
		{
			auto error = em.getLastError();
			LOG_ERROR_MESEAGE(error);
			return error.code;
		}
	}
	else APPLICATION_INFO("Success Start Sample");

	while (em.hasError())
	{
		auto error = em.getLastError();
		LOG_ERROR_MESEAGE(error);
		return error.code;
	}

	std::thread t1(_timer_thread_);

	auto start = std::chrono::system_clock::now();

	while (1)
	{
		// Reading data
		BMRecord_Lib::Application::getSampleData(test_data, sample_per_read);
		_count_++;
		if (!show_sample_rate)
		{
			for (int i = 0; i < 16; i++) {
				std::cout << std::dec << static_cast<int>(test_data[i]) << " ";
			}
			std::cout << std::endl;
		}
		auto end = std::chrono::system_clock::now();
		if ((std::chrono::duration_cast<std::chrono::seconds>(end - start)).count() > 10)
			break;
	}

	_timer_thread_enable_ = false;
	t1.join();
	BMRecord_Lib::Application::close();

	APPLICATION_INFO("Stop sampling");

	return 0;
}