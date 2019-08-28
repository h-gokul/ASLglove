# ASLglove
A low cost, minimal calibration, DIY sensor glove designed for recognizing alphabets in American Sign Language ASL gestures. 

This research project was aimed to make the best use of low cost, off the shelf components to design a translator system for  audio vocally disabled people who communicate using sign language. This research was accepted by the IEEE iThings 2019 conference in Atlanta, USA.

The system comprises of 4 flex sensors which provide an analog signal corresponding to the amount of bending it is subjected to. Works similar to a strain gauge.

There is one inertial measurement unit (IMU) used in order to capture the dynamic motion of the hand while performing gestures. 

The entire work is a classification problem solved by extracting data points from the sensors. The software design is provided in the research.

Contents:
The arduino file "DataExtraction" consists of the arduino code necessary to extract the data from sensors. The algorithm for solving the classification problem is was solved in python environment in run time.
The code for realtime implementation will be provided once the paper is published.
