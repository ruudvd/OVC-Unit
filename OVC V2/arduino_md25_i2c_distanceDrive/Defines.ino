#define CMD                 (byte)0x10                        // Values of 0 eing sent using write have to be cast as a byte to stop them being misinterperted as NULL
#define MD25ADDRESS         0x58                             // Address of the MD25
#define SPEED1              (byte)0x00                        // Byte to send speed to first motor
#define SPEED2              0x01                              // Byte to send speed to second motor
#define ENCODERONE          0x02                              // Byte to read motor encoder 1
#define ENCODERTWO          0x06                              // Byte to read motor encoder 2
#define VOLTREAD            0x0A                              // Byte to read battery volts
#define RESETENCODERS       0x20                              // Byte to reset encoders

#define DriveSpeed 200  //standard drive speed
#define StopSpeed 128   //standard stop speed (255 full forward, 0 full reverse)
#define TurnConst 30
#define PPT 360 //360 pulses per turn
#define WheelDiameter 100 //100mm diameter
#define WheelWidth 470 //distance between middle of wheels
