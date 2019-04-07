#include "OneWireHub.h"
#include "Control.h"

constexpr uint8_t pin_led {13};
constexpr uint8_t pin_onewire {2};

auto hub = OneWireHub(pin_onewire);

#define UNIT_ID 0x03 //change this to be unique for every device in your 1-wire network

auto arduino = Control(Control::family_code, 0x00,0x00,0xB2,0x18,0xDA,UNIT_ID);

#if DEBUG
bool simulating(void);
#endif

void setup() {
  // put your setup code here, to run once:

    Serial.begin(115200);
    Serial.println("OneWire-Hub DS18");
    Serial.flush();


    pinMode(pin_led, OUTPUT);

    // Setup OneWire
    hub.attach(arduino);
    //hub.attach(ds182);
}

void loop() {
    // following function must be called periodically
    hub.poll();
    // this part is just for debugging (USE_SERIAL_DEBUG in OneWire.h must be enabled for output)
    if (hub.hasError()) hub.printError();

#if DEBUG
    if (simulating())
    {
        static uint16_t temperature = 0;
        temperature += 10;
        if (temperature > 4000) temperature = 20;
        arduino.setValue(temperature);
        Serial.println(temperature);
    }
#endif

}

/*
bool simulating(void)
{
    constexpr  uint32_t interval = 10000;          // interval at which to blink (milliseconds)
    static uint32_t nextMillis = millis();     // will store next time LED will updated

    if (millis() > nextMillis)
    {
    	nextMillis += interval;
        return 1;
    }
    return 0;
}
*/
