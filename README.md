# pseudoGcode
Numerical Control (.nc) instructions to pseudo Gcode (.nc) formatter for home made 3D printer.<br />
Uppsala University

## Compile
* Unix: gcode: $ make
* Windows: gcc -std=c11 main.c main.h -o gcode

## Use
$ ./gcode x.nc<br />
<i>Where "x" is replaced with your filename.</i><br />
<b>OR</b><br />
$ ./gcode x.nc true<br />
<i>Where "x" is replaced with your filename. The flag "true" enables a print of the formatted file in your terminal</i>

## Information
I was looking at this YouTube clip (https://www.youtube.com/watch?v=anIy6eb1fW0) about building your own 3D printer out of a 3D printing pen, a few old CD-ROMs and a PSU. I noticed that the host was manually editing the Numerical Control instructions file (.nc) and figured that automating this process would be a good practice program for me to write.

Here it is, in all its glory.

## Notes
Free to use and abuse as you please.

Documentation is limited/poor, I will work on it when I find time.

Included .nc file for testing, test.nc, which you can use to test the structuring of this program out.

I'm sure there are much better ways to solve this problem, for starters not writing it in C, but I wanted to experiment with this idea for a bit.

You can compile C on Windows, too. Just do a quick google search on "compile C on Windows" and you will find extensive instructions.

## Updates
* Running the same file will no longer corrupt it
* Fixed various bugs with the formatting
* Added automatic "homing" of the Z-axis value at the end of the file
* Some defensive programming implemented (ex. running same file no longer corrupts it)
* Fixed memory leaks/errors completely (valgrind confirmed)
* Minor structuring for improved readability

## Potential future updates
* ~~Make sure files don't get corrupted if you accidently run them twice~~<br />
* Improve code readability and documentation<br />
* Convert all .nc files in the same folder when program is ran?
