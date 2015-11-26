# pseudoGcode
Numerical Control instructions to pseudo Gcode translator.<br />
Uppsala University

## Compile
gcode: $ make

## Use
$ ./gcode *.nc<br />
<i>Where "*" is replaced with your filename.</i><br />

## Information
I was looking at this YouTube clip (https://www.youtube.com/watch?v=anIy6eb1fW0) about building your own 3D printer out of a 3D printing pen, a few old CD-ROMs and a PSU. I noticed that the host was manually editing the Numerical Control instructions file (.nc) and figured that automating this process would be a good practice program for me to write.

Here it is, in all its glory.

## Notes
Free to use and abuse as you please.

Documentation is limited/poor, I will work on it when I find time.

I'm sure there are much better ways to solve this problem, for starters not writing it in C, but I wanted to experiment with this idea for a bit.

You can compile C on Windows, too. Just do a quick google search on "compile C on Windows" and you will find extensive instructions.