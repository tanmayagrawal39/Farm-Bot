# Farm-Bot
A CNC (Computerized Numberical Control) is created which moves in 3 axes to a specified location. 3 stepper motors are used for movement in each direction.
A camera is installed on the CNC head which captures image of the field and uploads to the firebase.
DHT11 temperature and humidity sensor, soil moisture sensor and LDR are installed on the CNC which gathers real-time information about the surroundings and uploads the data to the firebase.


An arduino is used for specifying the movement in each axes by providing the number of steps the stepper motor needs to move.
A raspberry Pi 3B is used for directing the CNC to move to each location, uploading the data to firebase database and clicking image and uploading it.


Crops will be planted in a grid and when the execution starts, the CNC will move to the first crop. The soil moisture sensor which is installed on the head will dip into the soil to check it's humidity.
If the moisture of the soil is found to be less than 35% (the sensor returns values from 0 to 100), the water pipe (also installed on the head) will be triggered and the crop will be irrigated.
The head then moves to the next crop and continues the same process.

Once every crop is checked, the head moves to the origin.
