#pragma once

#include "Core.h"
#include <stdint.h>

namespace BMRecord_Lib {
	enum AmplifierSampleRate {
		SampleRate1000Hz = 1,
		SampleRate1250Hz = 2,
		SampleRate1500Hz = 3,
		SampleRate2000Hz = 4,
		SampleRate2500Hz = 5,
		SampleRate3000Hz = 6,
		SampleRate3333Hz = 7,
		SampleRate4000Hz = 8,
		SampleRate5000Hz = 9,
		SampleRate6250Hz = 10,
		SampleRate8000Hz = 11,
		SampleRate10000Hz = 12,
		SampleRate12500Hz = 13,
		SampleRate15000Hz = 14,
		SampleRate20000Hz = 15,
		SampleRate25000Hz = 16,
		SampleRate30000Hz = 17,
		SampleRate33333Hz = 18,
		SampleRate40000Hz = 19,
		SampleRate50000Hz = 20,
	};

	class _BMR_API_ Application
	{
	public:
		static int Init();
		static int CheckConnectedDevice(int& count);
		static int ConnectDeviceByIndex(int index);
		static int Reset();
		static int setSampleRate(enum AmplifierSampleRate sampleRate);
		static int setHighPassCutoffFrequency(int level);
		static int setGain(int level);
		static int startSample();
		static int stopSample();
		static int getSampleData(uint16_t* buffer, int packet_count);
		static int close();
	private:
	};
}