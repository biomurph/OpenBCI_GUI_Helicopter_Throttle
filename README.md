# OpenBCI_GUI_Helicopter_Throttle
variant of OpenBCI GUI that uses strength of alpha wave to control helicopter throttle

Take the entire OpenBCI_GUI folder and put it in your 

    Documents/Processing

folder. If you already have an OpenBCI_GUI and don't want to over-write it, create a subfolder in the Processing folder called 'copter control' for this one to live in.

Take the entire 'CopterControl' folder and put it in your

    Documents/Arduino

folder.


The throttle control code is in the Processing sketch tabs 'EEG_Processing' and 'Helicopter'. The GUI already has a peak detection, so I look to see if the peak is in the alpha range. If it is, and if it's strong enough against the background noise, then a character is sent out to the Arduino that controls the helicopter. The strength of the alpha wave is encoded in the characters 'A' to 'Z'. Then Processing sends the prefix '$' followed by the character code. Arduino gets the prefix, and then applys the next value it gets to the potentiometer. It all took about half a day of hacking on the original OpenBCI_GUI, so I'm sure there's room for improvemnt.

Enjoy!!
