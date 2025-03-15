<img src=".github/images/NeuricsTech.png "/>

<div align="center">

[![Build status](https://img.shields.io/badge/vs2022-pass-green)](https://github.com/NeuricsTech/BMR2116_Demo)&nbsp;
[![GitHub Release](https://img.shields.io/github/v/release/NeuricsTech/BMR2116_Demo?color=green)](https://github.com/NeuricsTech/BMR2116_Demo/releases/latest)

</div>

# BMR2116_Lib_Demo

BMR2116 is an acquisition chip used to collect electrophysiological signals. In order to facilitate the data acquisition of the host computer, NeuricsTech supports the corresponding complete data acquisition hardware, and the library develops a dynamic link library for the corresponding required software.

## Library

### Install
Just download the [BMR2216-lib-windows-x86_64.zip](https://github.com/NeuricsTech/BMR2116_Demo/releases/latest) file in the Release build. Then copy the header and library files to your project directory and get started.

ConfigNeuricsTech.bit needs to be copied to the executable directory.

### Platform
* Windows (64 bit)

### Usage samples

#### Global macro

````c++
#define _BMR_PLATFORM_WINDOWS_
#define _BMR_DYNAMIC_LINK_
````

#### Basic usage

````c++
#include <BMR2116_Lib.h>

constexpr auto sample_per_read = 1000;
uint16_t test_data[sample_per_read * 16];

int main()
{
    BMR2116_Lib::Application::Init();
    BMR2116_Lib::Application::ConnectDeviceByIndex(0);
    BMR2116_Lib::Application::Reset();
    BMR2116_Lib::Application::setSampleRate(BMR2116_Lib::AmplifierSampleRate::SampleRate20000Hz);
    BMR2116_Lib::Application::startSample();
    BMR2116_Lib::Application::getSampleData(test_data, sample_per_read);
    BMR2116_Lib::Application::close();

    return 0;
}
````

#### Reading error messages
````c++
#include <BMR2116_Lib.h>
#include <iostream>

int main()
{
    BMR2116_Lib::ErrorManager::enableErrorManager(true);
	auto& em = BMR2116_Lib::ErrorManager::getInstance();

    if (BMR2116_Lib::Application::Init())
	{
		if (em.hasError())
		{
			auto error = em.getLastError();
			std::cout << error.message << std::endl;
			return error.code;
		}
	}

    return 0;
}
````

#### Set Chip Parameters

````c++
// BMR2116_Lib::Application::setChipParameters( [Parameter], [Value] )
BMR2116_Lib::Application::setChipParameters(BMR2116_Lib::ChipParameter_F_HP, 1);
````

Configurable chip parameters include:
| Parameter |   Min  |   Max  |  Default Value |   Meaning   |
|   :----:  | :----: | :----: |      :----:    |   :----:    |
|    F_HP   |   0    |  255   |        0       | 高通截止频率 |
|    CALC   |   0    |    1   |        1       |     测量    |
|    CMFB   |   0    |    1   |        0       |   共模反馈  |
|  PGA_GAIN |   0    |    3   |        0       |   PGA增益   |
| PGA_IBIAS |   0    |   15   |        1       |  PGA_I_ss  |
|  LNA_BIAS |   0    |   15   |        0       |  电流源I_ss |

#### Set Chip Sample Rate

````c++
// BMR2116_Lib::Application::setSampleRate( [Value] )
BMR2116_Lib::Application::setSampleRate(BMR2116_Lib::AmplifierSampleRate::SampleRate20000Hz);
````

The configurable sampling rates include: 
**SampleRate1000Hz** , **SampleRate1250Hz** , **SampleRate1500Hz** , **SampleRate2000Hz** , **SampleRate2500Hz**
**SampleRate3000Hz** , **SampleRate3333Hz** , **SampleRate4000Hz** , **SampleRate5000Hz** , **SampleRate6250Hz**
**SampleRate8000Hz** , **SampleRate10000Hz** , **SampleRate12500Hz** , **SampleRate15000Hz** , **SampleRate20000Hz**
**SampleRate25000Hz** , **SampleRate30000Hz** , **SampleRate33333Hz** , **SampleRate40000Hz** , **SampleRate50000Hz**

## Demo Project

The Demo Project provides an example of rapid development of an acquisition program.
Just download [Demo-release-windows-x86_64.zip](https://github.com/NeuricsTech/BMR2116_Demo/releases/latest) from the Release to quickly test whether the hardware is working.
Demo will sample continuously for 10s at a sampling rate of 20K.

### Platform
* Windows (64 bit)

### Build

The Demo program uses [Premake](https://github.com/premake/premake-core) to generate project files and [spdlog](https://github.com/gabime/spdlog) to output logs.

Visual Studio 2022 is used by default.

```console
$ git clone --recursive https://github.com/NeuricsTech/BMR2116_Demo.git
$ cd BMR2116_Demo
$ .\GenerateProject.bat
```

It will generate the BMR2116_Demo.sln file in the current directory.
See the [Premake documentation](https://premake.github.io/docs/Using-Premake) for support for other project files, and create your project with the following command:

```console
$ .\tools\premake5.exe vs2022
```

### Run

The result looks like this:

<img src=".github/images/Demo.png "/>