# PwmToServo
Uses the PWM output from a motor controller to control a hobby motor via an electronic speed control

We use the [Rev Robotics Hub](http://www.revrobotics.com/rev-31-1153/) in our robots for FIRST First Technology Challenge competitions.  The component selection for those competitions limit the type and size of motor for the robot.  The Rev Robotics Hub is an excellent controller however it also has limitations on how much current it can supply.  I am creating other robots at home with my other kids and wish to use the same software and controller.  So, I needed a way to allow the Rev Robotics Hub to control a larger variety of motors.

Radio Control car motors are very powerful, inexpensive and standardized.  The electronics and software in PwmToServo act like a fake load to the Rev Robotics Hub.  The Arduino measures the voltage output from the Rev Robotics Hub, then translates that to a RC Servo type signal that is sent to the Electronic Speed Control (ESC).

My current configuration is:
* Hobbywing QUICRUN Series 860 Dual 60A Waterproof Brushed Electronic Speed Controller ESC purchased via [AliExpress](aliexpress.com)

* The motor I am controlling is the Goolsky AUSTAR 540 55T Brushed Motor.
