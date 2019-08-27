# EvgaI2C
This is a small project for sending commands to EVGA's I2C. This project only changes the LED colors, but you can do much more.
This is going to work with EVGA FTW boards.

I didn't knew EVGA sent through I2C, but I eventually figured out by disassemblying/debugging EVGA Precision X software. 

I found the pointer of nvapi_queryinterface from disassemblying Precision X. Then I searched for how it works and found out it's I2C.

I've found the piece of memory that the second parameter was pointing to:

> 40 00 03 00 00 00 00 00 00 92 00 00 00 00 00 00

> A8 DF 3C A1 9A 00 00 00 01 00 00 00 00 00 00 00 

> 18 E0 3C A1 9A 00 00 00 01 00 00 00 FF FF 00 00

This was setting G to 255.

EVGA communicates 3 times with i2c, one for each color. 

> R = 0x09
> G = 0x0A
> B = 0x0B`

There's also breathing etc present, but I didn't mess around with those: I got what I wanted.

rgb_port and rgb_color vars (uchar) doesn't use their real name of course, it should be pbI2cRegAddress and pbData accordingly.

datw always points to an array containing 2 unsigned long with the value of 0.

So, basically, pbI2cRegAddress sets which led it's binding to (as I said above, 0x09, 0x0A, 0x0B), and pbData to the color (char).

I'm not a good C++ developer, but nevertheless there you go.

I'm not sure if there'll be any problems with the version, but I guess not. I could've implemented it, but I didn't want to get that far.
