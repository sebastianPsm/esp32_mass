Mueen's Algorithm for Similarity Search" (aka MASS) for ESP32
====================

## Dependencies
- [esp32-fft](https://github.com/fakufaku/esp32-fft), simple fft, ifft lib

## Comparison
The following figure shows an example time series, query and results from two MASS implementations: This (esp32-mass) and the Python mass_ts module.

![Result](https://github.com/sebastianPsm/esp32_mass/raw/master/img/plot.png)

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

4. Create components directory and download dependency
```console
#> mkdir components

#> cd components

#> git clone https://github.com/fakufaku/esp32-fft.git
Cloning into 'esp32-fft'...
remote: Enumerating objects: 60, done.
remote: Total 60 (delta 0), reused 0 (delta 0), pack-reused 60
Unpacking objects: 100% (60/60), done.

#>
```

5. Change back to repo root
```console
#> cd ..
```

6. Build
```console
#>
```
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
