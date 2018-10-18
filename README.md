# SoundSamplePlayer

<img src="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/sound_player2-1024x768.jpg" width="500">


This is an analog textile sensor demo box. It plays back mp3 sound files as you manipulate the textile sensor connected to a pair of crocodile clips. Each connection channel is equipped with  adjustable voltage dividers (1k-1M ohm range) to select suitable range for the textile sensors. The readings of the sensors are displayed as LED allays. 

This Demo box is made for the <a href="http://touchcraft.org.uk/" rel="noopener" target="_blank">Touch Craft project of Lucie Hernandez</a> as a part of Wear Sustain Project.

<hr>
<h2>HOW TO USE</h2>
<img src="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/lucie_box_explanation-1024x804.jpg" alt="" width="800" >

<h2>Trigger Mode</h2>
<img src="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2759-1024x768.jpg" width="500">
Trigger mode triggers the sound file when the sensor value reaches the threshold. LED dispay shows white/pink


<h2>Volume Mode</h2>
<img src="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2760-1024x768.jpg" width="500"/>

Volume mode changes the volume like fader as you manipulate the sensor.
LED dispay shows white/green

<h2>Adjust Voltage Divider</h2>
Turn the knob to adjust the voltage divider value.
This will adjust the reading range of the connected
analog sensor.  After adjusting the voltage divider value,
you can use the calibration mode to achieve full
range of reading. There are 1k ohm, 20k ohm, 100k ohm and 1M ohm adjustable resisters connected to the sensor inputs as voltage divider. Choose the size of voltage divider range according to the textile sensor you have made. 
More about Voltage Divider>> <a href="http://www.kobakant.at/DIY/?p=6102" rel="noopener" target="_blank">http://www.kobakant.at/DIY/?p=6102</a>


<h2>Calibration</h2>
<a href="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2762.jpg"><img src="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2762-1024x768.jpg" width="240"/></a>
press long (more than 5 sec)  to enter calibration mode
when in calibration mode, the LED display turns blue.
manipulate the connected analog sensor so it sets max/min
of the sensor and scale it accordingly


<h2>reset Calibration<</h2>
double click and it resets the calibration range

<h2>Select sound files</h2>
<a href="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2763.jpg"><img src="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2763-1024x768.jpg" width="240" /></a>
double click to enter sound select mode
when in sound select mode, the LED display turns green
and shows the current track number. 
push the button to change the track number assigned to 
this channel.  Times out after 5 seconds.


<hr>
<strong>Power</strong>
<a href="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2749.jpg"><img src="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2749-300x225.jpg" ></a> <img src="http://www.3fvape.com/7123-thickbox_default/usb-charger-power-adapter-uk-plug.jpg" width="200">

The power supply comes from micro USB cable connected to the Teensy inside. The idea is to keep the cable with the device and plug in/out the connection to the wall power plug. You can get USB power adapter to connect to the wall plugs. 

<a href="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2754.jpg"><img src="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2754-300x225.jpg" width="240"></a><a href="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2755.jpg"><img src="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2755-300x225.jpg" width="240"></a>

When power is on, you will see the green light.

<strong>Sound File</strong>
<a href="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2750.jpg"><img src="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2750-300x225.jpg"width="240"></a><a href="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2753.jpg"><img src="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/IMG_2753-300x225.jpg"width="240"></a>
Sound files are stored in microSD card. When you want to change the sound files, please take the SD card out from the slot and replace the file with new file you want to play. The sound files must be named as "track001.mp3" to "track008.mp3". 
At the moment it is set to only look for mp3 files of these names.

<strong>Amplification</strong>
<a href="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/amp.jpg"><img src="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/amp-300x225.jpg" width="300" ></a>
You can change the amount of amplification on the amplifier that is connected to speaker. To do so, move the jumper on the side. At the moment it is set as the loudest of this amplifier. As you place the device in a box, it should get louder as the speakers get resonance body. 
Make sure to "normalize" the sound files so all the sound samples are in similar volume range. When you hear clipping sound, it is amplified too much. Either to change the amplitude of the amplifier or reduce the volume on the sound file.

<hr>
<h2>SCHEMATIC</H2>
<a href="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/schematic.jpg"><img src="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/schematic-1024x714.jpg"  width="500"  /></a>
download >><a href="http://www.kobakant.at/KOBA/wp-content/uploads/2018/10/schematic.pdf">schematic PDF</a>
