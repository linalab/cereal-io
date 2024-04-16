# cereal-io
Serial Communication between Arduino and Unity

## *provisional documentation*

This library allows for a "shared-memory-like" communication between Arduino and unity using Serial communication. 

The main idea is that we have 128 float and 128 channels that communicate values between the two 
environments. Example:

```c++
// Arduino code
#include "Cereal.h"

Cereal cereal(9600);

void setup()
{
  cereal.begin();
}

float x, y, z = 0;
long count = 0;

void loop()
{
  count += 1;
  count %= 10;
  cereal.sendInt(0, count);

  x += .1;
  y += .002;
  z += .003;

  cereal.sendFloat(0, x); // float an int channels don't overlap
  cereal.sendFloat(1, y);
  cereal.sendFloat(2, z);
}
```

This can be read in unity like so:

```c#
private Cereal cereal;
using System;
using System.Linq;
using System.IO.Ports; // Requires .NET 4 in Project Settings

public void ConnectToPort() // this should be called from a uinity game object
{
    string port = _ports[PortsDropdown.value];
    cereal.InitCereal(port, 9600);
    StartCoroutine(cereal.ReadCereal());
}
// will contain values from arduino
int count = cereal.ReadInt(0);
float x = cereal.ReadFloat(0);
float y = cereal.ReadFloat(1);
float z = cereal.ReadFloat(2);
```
It also works in the opposite direction

```c#
//unity
cereal.SendInt(1, 42); // send and read channels also don't overlap
cereal.SendFloat(1, 23.0f); // floats not doubles
```

```c++
//arduino
int value = cereal.readInt(1); // send and read channels also don't overlap
float othervalue = cereal.readFloat(1); // floats not doubles
```


Setting the arduino environment should be as easy as copying the `Cereal` library into the libs directory
of you arduino project. (path in this repo: `/arudino/lib/Cereal`).

Setting up the unity environment requires a tiny bit more work. Roughly:

- Setting up .NET4 in project.
- Copying `Cereal.cs` into your assets. 
- Creating a Game Object to contain your unity inputs.
- Having a widget that allows you to select from a list of open Serial Ports, and call
`ConnectToPort`. 
- Connecting game objects to functions that send or read the values you want. 

A full-feature working example can be found in:

- Arduino code: `/arduino/src/SendAndReadCereal.ino`
- Unity code: `/unity/Assets/CeralTest.cs`


*Disclaimer*: This library is currently not thoroughly tested. It has only been tested for
the UNO R3 board.



