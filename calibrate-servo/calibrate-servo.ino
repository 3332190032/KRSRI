#include <SoftwareSerial.h>

SoftwareSerial Leg(19, 18); // RX, TX

void setup() {
  Leg.begin(9600);
}

void loop() {
  newComboA();
}

void newComboA () {
  // LEFT LEGS
  Leg.println("#4P1500 #5P1480 #6P1640 T200"); //coxa, femur,tibia
  Leg.println("#8P1400 #9P1600 #10P1650 T200");
  Leg.println(F("#12P1400 #13P1280 #14P1680 T200"));

  // RIGHT LEGS
  Leg.println(F("#20P1600 #21P1500 #22P1350 T200"));
  Leg.println(F("#24P1450 #25P1480 #26P1050 T200"));
  Leg.println(F("#28P1300 #29P1450 #30P1350 T200"));

  delay(200);
}

void newComboB () {
  // LEFT LEGS
  Leg.println("#4P1280 #5P1950 #6P2100 T200");
  Leg.println("#8P1000 #9P2100 #10P2140 T200");
  Leg.println(F("#12P940 #13P1800 #14P2180 T200"));

  // RIGHT LEGS
  Leg.println(F("#20P1850 #21P1000 #22P850 T200"));
  Leg.println(F("#24P1950 #25P1040 #26P650 T200"));
  Leg.println(F("#28P1770 #29P980 #30P900 T200"));

  delay(200);
}

void comboA () {
  // LEFT LEGS
  Leg.println(F("#0P1500 #1P1380 #2P1440 T200"));
  Leg.println(F("#4P1500 #5P1450 #6P1300 T200"));
  Leg.println(F("#8P1500 #9P1480 #10P1500 T200"));

  // RIGHT LEGS
  Leg.println(F("#16P1400 #17P1400 #18P1500 T200"));
  Leg.println(F("#20P1350 #21P1350 #22P1420 T200"));
  Leg.println(F("#24P1400 #25P1400 #26P1300 T200"));

  delay(200);
}

void comboB () {
  // LEFT LEGS
  Leg.println(F("#0P970 #1P1750 #2P1880 T200"));
  Leg.println(F("#4P1050 #5P1980 #6P1770 T200"));
  Leg.println(F("#8P1100 #9P1880 #10P2000 T200"));

  // RIGHT LEGS
  Leg.println(F("#16P1950 #17P1020 #18P1030 T200"));
  Leg.println(F("#20P1800 #21P950 #22P920 T200"));
  Leg.println(F("#24P1800 #25P1000 #26P720 T200"));

  delay(200);
}
