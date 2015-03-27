# NifSE v1.2 #
> - an OBSE plug-in by DragoonWraith



## Introduction ##

NifSE is an OBSE plug-in that allows Oblivion script to operate on Nif files during run-time. Nif files, or Net Immerse Format files, are 3D meshes which are used by Oblivion. These files have long been editable with 3D software and NifTools' excellent NifSkope utility, but certain operations on Nif files have been desirable for scripters and therefore impossible - until now.

More specifically, NifSE uses the NifTools' incredible "C++ library for loading, modifying, and exporting NIF files," Niflib, to create new functions through OBSE's plug-in API. Much thanks to both the OBSE and NifTools teams for their hard work that has made this possible.

## Changelog ##
  * v1.2 b1 Debug
    * Fixed failure in NiNodeCopyChild function to copy and link bones in skinned meshes.
  * v1.1 Release
    * Fixed bug that caused NifSE to crash if a BSA had a % in the filename.
  * v1.0 Release
    * Suppressed Console messages in Release version
    * Functionally identical to b:6

For full changelog, see NifSE changelog.txt included with the NifSE archive.

## Contact ##

Send an e-mail to dragoonwraith+nifse@gmail.com

Messages or posts on any forum or other website may likely be missed for extended periods of time.

## Credits ##
<ul><li>The Oblivion Script Extender team: ianpatt, behippo, and scruggsywuggsy the ferret<br>
<br>
Without OBSE, I would have lost interest in modding Oblivion long, long ago, and without the plug-in API that they created, this project never could have happened<br>
<br>
Special thanks to Scruggs and behippo for answering myriad questions about coding for the OBSE plug-in API, and to Scruggs for implementing new features just for me!<br>
<br>
Extra-double-thanks for Scruggs's continued support, including writing crucial new hooks that allow NifSE to avoid ever cluttering your HD.</li>

<li>The NifTools NifLib team: Shon, amorilia, tazpn, xoalin, dragongeo2, neomonkius<br>
<br>
The NifTools team had done all the hard work for me - all I did was provide an interface between OBSE and Niflib. Kudos to them on an incredible piece of work.<br>
<br>
Special thanks to amorilia for answering some questions on Nifs in general, and to tazpn for answering some Niflib specific questions. Extra special thanks, again, to amorilia for actually updating Niflib for me.</li>

<li>JRoush, Lojack, shadeMe, scruggsy (again), and Timeslip<br>
<br>
For helping with the BSA-reading capability of NifSE, contributing code and spending far too much time answering my stupid questions. Special thanks to JRoush for providing the code that is used in this version of NifSE, fixing a bug with previous versions.<br>
</li>

<li>Jean-Loup Gailly and Mark Adler<br>
<br>
The zlib code allows me to read BSA files that I otherwise would not be able to read. zlib is an excellent free utility, one of the best products of open source design to date.</li>

<li>Speedo<br>
<br>
Help with statically linking zlib into NifScript, NifSE's predecessor.</li>

<li>throttlekitty, JDFan, and trollf<br>
<br>
For answering questions that I had about Nifs on the CS Forum.</li>

<li>opaj<br>
<br>
For help testing.</li>

<li>HeX_0ff<br>
<br>
For creating Unnecessary Violence, an incredible mod using NifScript, NifSE's precursor and for general help and feedback on NifScript. Also for helping to spur on NifSE's development.</li>

<li>Skycaptain<br>
<br>
For getting me back into the game, and giving great feedback on what should be added to NifScript for NifSE, and then for creating Deadly Reflexes 6, which makes excellent use of NifSE.</li>

<li>cInfidel, KC33, Klaus, MJMax, RoflLizard, sean144800<br>
<br>
For extensive testing of NifSE's bugs in Deadly Reflex 6.<br>
<ul><li>Special thanks to RoflLizard for the initial testing,<br>
</li><li>sean144800 for testing EVERY SINGLE VANILLA WEAPON MESH (absolutely increidble work),<br>
</li><li>Smooth for noticing the version difference between GotY edition meshes and other versions,<br>
</li><li>cInfidel for noticing the Flags difference,<br>
</li><li>cInfidel, MJMax, and Smooth again for testing every conceivable Flag configuration (more utterly incredible work),<br>
</li><li>and again to Smooth for releasing ALL of the affected meshes with corrected Flags.<br>
All of you did absolutely amazing work, put in a lot of hours, and I am deeply indebted to you for it.</li></li></ul>

<li>Showler<br>
<br>
For early support of NifSE and an offer to alpha test.</li>

<li>Wyzard256, zone22, Skycaptain, HeX_0ff, !shadeMe, Gekko64, anithinks, Obliver, and all those who offered good luck and well wishes when my hard drive failed.<br>
<br>
For serious help, advice, links, downloads, and even offers to help pay (!) for a data recovery service when my harddrive failed. Special thanks to zone22 for actually calling me on Skype and spending a good four hours (!) talking me through the data recovery process, and to HeX and shade for offering to do the same. It is only thanks to them that this project, along with ARES and hundreds of my own personal files, did not get entirely destroyed in that failure.</li>

<li>acejoo<br>
<br>
Testing Unnecessary Violence 1 with the updated deprecated functions.</li>

<li>mmmpld<br>
<br>
Testing BSFurnitureMarker functions.</li>

<li>gep5<br>
<br>
Literally the only reason this late update to NifSE happened is because he provided impetus and a testing suite. Much thanks.</li></ul>