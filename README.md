# MOONPATROL SGDK
This is a light weight interpretation of the infamous game MoonPatrol. It is used in this case as a teaching aid since the game mechanics are relatively simple and cover most features of the SGDK (Sega Development kit).
<p>
Each lesson/tutorial is in it's own branch so please check the branches of this repository. The end product is merged into main branch.
<P>
## Tutorial 1
We will be drawing a background and letting that scroll. In order to draw a background you will need a pixel art tool, anyone will do but you need to have a palette for the Genesis. We are using Asprite, it cheap easy and does the trick and you can load the plaette named "Sega Genesis new.pal" from this repository in the root, and you will have the 512 colors that the Genesis/MegaDrive supports.

It's important to know that a Genesis can only handle 16 different color for each background and sprite(s). With palette swapping more colors can be shown on the screen though but that's beyond the basics of this lesson.

A background image when shown in "high res" needs to be 512x256 in order to allow for seamless scrolling.
![alt text](https://github.com/rdoetjes/moonpatrol/blob/main/res/bg_b_v2.png?raw=true)
