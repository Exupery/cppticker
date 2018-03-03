[![Build Status](https://travis-ci.org/Exupery/cppticker.svg)](https://travis-ci.org/Exupery/cppticker)
# C++Ticker

Command line stock ticker. Uses [IEX's API](https://iextrading.com/developer/) to show information about US stocks and indices (via their ETFs).

## Displayed data for each stock/index

* last trade
* change amount
* change percent
* day's range

## Showing additional symbols

Launching the program with no arguments will default to showing the ETFs tracking the Dow Jones Industrial Average (`DIA`), the S&P 500 (`SPY`), and the Nasdaq-100 (`QQQ`). Additional stocks can be shown by including the symbols as arguments (separated by spaces). These are not case sensitive and there is a limit of 100 symbols.

## Setting the update interval

The default update interval is set to 15 minutes between update polling, with two seconds between each stock/index displaying. If a different polling interval is desired this should be included in the arguments as a number. Arguments can be ordered in any way (the interval can be placed before, after, or between any symbols entered). The update interval should be entered in minutes, this can include fractional minutes (i.e. 1.5 would set the interval to 90 seconds). It is not possible to set an update interval less than one minute.

## Compiling

Regardless of which method is used a `g++` version of [4.9](https://gcc.gnu.org/gcc-4.9/) or higher is *required*.

##### Via [GCC](https://gcc.gnu.org/onlinedocs/gcc-5.4.0/gcc/G_002b_002b-and-GCC.html)
`g++ -std=c++11 src/*.cpp src/json.hpp -lcurl -o cppticker`

##### Via [Make](https://www.gnu.org/software/make/manual/make.html)
`./configure && make`
(If running this results in an error similar to `WARNING: 'automake-1.15' is missing on your system` this _may_ be resolved by running `autoreconf -f -i` first)

## Requirements

* [libcurl](https://curl.haxx.se/libcurl/) - to install [libcurl4-gnutls-dev](https://packages.ubuntu.com/xenial/libcurl4-gnutls-dev) on Ubuntu run `sudo apt install libcurl4-gnutls-dev`
