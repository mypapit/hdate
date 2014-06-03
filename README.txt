hdate: A simple command-line tool for displaying Hijri date. 

Installation
------------
hdate.c can be compiled with any ANSI C compliance compiler. To install under GNU/Linux or any UNIX-like operating system, type:

make install

by default, 'hdate' executable binary will be installed in '/usr/local/bin' or /usr/bin (depending on your UNIX-like operating system).



Usage
-----

Display current Hijri date:

 hdate [-nm]


Converts Gregorian date to Hijri :

 hdate [-nm] date month year
 hdate 28 2 1990  

-n	: dd/mm/yyyy format
-m	: mm/dd/yyyy format
-h	: prints help


Issues and Suggestions
----------------------
You can report issues or post suggestions regarding 'hdate' through the project website, http://hdate.googlecode.com or by emailing the author - Mohammad Hafiz bin Ismail <mypapit+hdate@gmail.com>


License
-------
This software is licensed under the GNU General Public License version 2 (or at your option) any later version. 


