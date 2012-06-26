C++Ticker
=============

Command line stock ticker. Uses Google's Finance API to show information about US stocks and indices. 

Displayed data for each stock/index
-----------------------------------

* last trade
* change amount
* change percent
* day's range


Showing additional symbols
--------------------------

Launching the program with no arguments will default to showing the Dow Jones Industrial Average, the S&P 500, and QQQ (representing the Nasdaq-100). Additional stocks can be shown by including the symbols as arguments (separated by spaces). These are not case sensitive and there is currently no [practical] limit to how many you can add. 

Stock and ETF symbols will be the same as their listed tickers, indices will need to match the Google designated symbol (i.e. [.INX](http://www.google.com/finance?q=INDEXSP:.INX) for the S&P 500) which can be found by looking up the desired index on [Google Finance](http://www.google.com/finance).


Upcoming changes
----------------

The next planned enhancement will allow the user to input desired update intervals. Currently the update interval is set to five minutes between update polling, with two seconds between each stock/index displaying. There will be a cap on how frequently the update polling can occur due to Google's rate limiting.

If this code seems a bit amateurish to you...
---------------------------------------------

Professionally I program almost exclusively in Java and Ruby (on Rails), but I decided it would be beneficial to learn C++. So after going through an appropriate [tutorial](http://www.learncpp.com/) I decided this would be an interesting next step. 