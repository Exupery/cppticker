# C++Ticker

Command line stock ticker. Uses Google's Finance API to show information about US stocks and indices.

## Displayed data for each stock/index

* last trade
* change amount
* change percent
* day's range

## Showing additional symbols

Launching the program with no arguments will default to showing the Dow Jones Industrial Average, the S&P 500, and QQQ (representing the Nasdaq-100). Additional stocks can be shown by including the symbols as arguments (separated by spaces). These are not case sensitive and there is currently no [practical] limit to how many you can add.

Stock and ETF symbols will be the same as their listed tickers, indices will need to match the Google designated symbol (i.e. [.INX](https://www.google.com/finance?q=INDEXSP:.INX) for the S&P 500) which can be found by looking up the desired index on [Google Finance](https://www.google.com/finance).

## Setting the update interval

The default update interval is set to 15 minutes between update polling, with two seconds between each stock/index displaying. If a different polling interval is desired this should be included in the arguments as a number. Arguments can be ordered in any way (the interval can be placed before, after, or between any symbols entered). The update interval should be entered in minutes, this can include fractional minutes (i.e. 1.5 would set the interval to 90 seconds). It is not possible to set an update interval less than one minute due to Google's rate limiting.

## Compiling

##### Via [GCC](https://gcc.gnu.org/onlinedocs/gcc-5.4.0/gcc/G_002b_002b-and-GCC.html)
`g++ -std=c++11 src/*.cpp -lcurl -o cppticker`

##### Via [Make](https://www.gnu.org/software/make/manual/make.html)
`.configure && make`

## Requirements

* [libcurl](https://curl.haxx.se/libcurl/) - to install [libcurl4-gnutls-dev](https://packages.ubuntu.com/xenial/libcurl4-gnutls-dev) on Ubuntu run `sudo apt install libcurl4-gnutls-dev`
