Mueen's Algorithm for Similarity Search" (aka MASS) for ESP32
====================

## Dependencies
- [esp32-fft](https://github.com/fakufaku/esp32-fft), simple fft, ifft lib

## Comparison
The following figure shows an example time series, query and results from two MASS implementations: This (esp32-mass) and the Python mass_ts module.

![Result](https://github.com/sebastianPsm/esp32_mass/raw/master/img/plot.png)

## Todos
- [ ] esp32 benchmark with different sizes
- [ ] implementing the other MASS versions (mainly [MASS_V2](https://www.cs.unm.edu/~mueen/MASS_V2.m))
- [ ] Quick start documentation
- [ ] Highlite some projects that uses MASS on an esp32

## Acknowledgment
Acknowledging the work of Mueen and his team: Abdullah Mueen, Yan Zhu, Michael Yeh, Kaveh Kamgar, Krishnamurthy Viswanathan, Chetan Kumar Gupta, Eamonn Keogh (2015), The Fastest Similarity Search Algorithm for Time Series Subsequences under Euclidean Distance, URL: [http://www.cs.unm.edu/~mueen/FastestSimilaritySearch.html]

*Code in this repository is in the Public Domain (or CC0 licensed, at your option.)
Unless required by applicable law or agreed to in writing, this
software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied.*
