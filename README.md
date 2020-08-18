Mueen's Algorithm for Similarity Search" (aka MASS) for ESP32
====================

[Mueen's algorithm for similarity search](https://www.cs.unm.edu/~mueen/FastestSimilaritySearch.html) (MASS) is a nearest neighbor algorithm for time series data. Because of the size and speed MASS is ideal for microcontroller use. The shown C implementation in this repo of MASS is directly derived from [here](https://www.cs.unm.edu/~mueen/MASS.cpp) and works also on other platforms for sure.

![C/C++ CI](https://github.com/sebastianPsm/esp32_mass/workflows/C/C++%20CI/badge.svg?branch=master) ![code quality](https://github.com/sebastianPsm/esp32_mass/workflows/code%20quality/badge.svg)

## Comparison
The following figure shows an example time series data (~ 20 sec acceleration data), a query (~ 2.5 sec acceleration data) and results from two MASS implementations: This (esp32-mass), the Python mass_ts module and the official MATLAB code from MASS_V1 (findNN).

![result](https://github.com/sebastianPsm/esp32_mass/raw/master/img/plot.png)

## Benchmark
The following benchmark was executed on a ESP32 with different n (256, 512, 1024) and m (4, 8, 16, 32, 64, 128).

![result](https://github.com/sebastianPsm/esp32_mass/raw/master/img/benchmark.png)

## Dependencies
- [esp32-fft](https://github.com/fakufaku/esp32-fft), simple fft, ifft lib --> files located in components/mass (fft.h, fft.c)
- sqrt(), cosf() and sinf(): Typically from libm, automatically added by the esp32 SDK

## Quick start
1. Check if esp32 SDK is functional
```console
#> idf.py --version
   ESP-IDF v4.2-dev-1126-gd85d3d969

#>
```

2. Clone repo
```console
#> git clone https://github.com/sebastianPsm/esp32_mass.git
Cloning into 'esp32_mass'...
remote: Enumerating objects: 48, done.
remote: Counting objects: 100% (48/48), done.
remote: Compressing objects: 100% (34/34), done.
remote: Total 48 (delta 21), reused 33 (delta 10), pack-reused 0
Unpacking objects: 100% (48/48), done.

#>
```

3. Change into repo
```console
#> cd esp32_mass

#>
```

4. Build
```console
#> idf.py build
Executing action: all (aliases: build)
Running cmake in directory c:\users\sebastian\desktop\esp32_mass\build
Executing "cmake -G Ninja -DPYTHON_DEPS_CHECKED=1 -DESP_PLATFORM=1 --warn-uninitialized -DCCACHE_ENABLE=1 c:\users\sebastian\desktop\esp32_mass"...
Warn about uninitialized values.

...

[100/100] Generating binary image from built executable
esptool.py v3.0-dev
Generated C:/Users/Sebastian/Desktop/esp32_mass/build/bootloader/bootloader.bin
[932/932] Generating binary image from built executable
esptool.py v3.0-dev
Generated C:/Users/Sebastian/Desktop/esp32_mass/build/app-mass-example.bin

Project build complete. To flash, run this command:
C:\Users\Sebastian\.espressif\python_env\idf4.2_py3.8_env\Scripts\python.exe ..\esp-idf-2\components\esptool_py\esptool\esptool.py -p (PORT) -b 460800 --before default_reset --after hard_reset --chip esp32  write_flash --flash_mode dio --flash_size detect --flash_freq 40m 0x1000 build\bootloader\bootloader.bin 0x8000 build\partition_table\partition-table.bin 0x10000 build\app-mass-example.bin
or run 'idf.py -p (PORT) flash'

#>
```

## Todos
- [ ] implementing the other MASS versions (mainly [MASS_V2](https://www.cs.unm.edu/~mueen/MASS_V2.m))
- [ ] Highlight some projects that uses MASS on an esp32

## Acknowledgment
Acknowledging the work of Mueen and his team: Abdullah Mueen, Yan Zhu, Michael Yeh, Kaveh Kamgar, Krishnamurthy Viswanathan, Chetan Kumar Gupta, Eamonn Keogh (2015), The Fastest Similarity Search Algorithm for Time Series Subsequences under Euclidean Distance, URL: [http://www.cs.unm.edu/~mueen/FastestSimilaritySearch.html]

*Code in this repository is in the Public Domain (or CC0 licensed, at your option.)
Unless required by applicable law or agreed to in writing, this
software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied.*
