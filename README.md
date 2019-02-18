# 387_midterm
This project interfaces a W2812B LED strip with an Arduino in a way which allows a user inexperienced with programming to easily create an LED matrix of their own dimensions and light it up with pixel art/animations.

# Descriptions of Files Uploaded
The following is the order in which the files were created.

*define_colors.ino* - First success at assigning LEDs colors using variables and pointers, and using the 'XY' function.
*matrix_working.ino* - First instance of the 'LightEmUp' function to assign LEDs with a matrix. Changes made to 'XY' function.
*matrix_and_change1.ino* - Added 'Change1LED' function so user can simply use their color variable to change 1 LED at a time.
*art_animation.ino* - Color variables moved from global variables to void loop(). Update to 'XY' function. General cleanup and organization. First full animation of the Miami University Logo using the 'LightEmUp' and 'Change1LED' functions.
*path_follow.ino* - Creation of 'CustomDrawColor' and 'CustomDrawMatrix' functions to use integer matrices to perform animations.
*custom_matrix_for_pixelart_animation.ino* - Current instance of the project. More comments and organization added to make the program easier to understand. The Miami University Logo is fully animated using the different functions to demonstrate how each one works.
