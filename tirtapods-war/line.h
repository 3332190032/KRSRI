#define PIN_LINE_SENSOR A8
#define PIN_LINE_SENSOR2 A9

namespace line {
  bool isDetected = false;
  bool isDetectedGlue = false;
  bool isDetectedFloor = false;
  bool isDetectedKarpet = false;
  bool isDetectedHalangRintang = false;
  bool isDetectedStiker = false;
  bool isDetectedLantai = false;
  unsigned int nilaiF = 0;
  unsigned int nilaiC = 0;

  void setup () {
    pinMode(PIN_LINE_SENSOR, INPUT);
    pinMode(PIN_LINE_SENSOR2, INPUT);
  }

  void update () {
    // if (analogRead(PIN_LINE_SENSOR) >= 900 || analogRead(PIN_LINE_SENSOR2) >= 900) {
    //   isDetected = true;
    // } else {
    //   isDetected = false;
    // }
    // if (analogRead(PIN_LINE_SENSOR) >= 250 || analogRead(PIN_LINE_SENSOR2) >= 250){
    //   isDetectedGlue = true;
    // } else {
    //   isDetectedGlue = false;
    // }
    // if (analogRead(PIN_LINE_SENSOR) >= 350 || analogRead(PIN_LINE_SENSOR2) >= 350){
    //   isDetectedFloor = true;
    // } else {
    //   isDetectedFloor = false;
    // }

    // if ((analogRead(PIN_LINE_SENSOR) >= 220) && (analogRead(PIN_LINE_SENSOR) < 284) && (analogRead(PIN_LINE_SENSOR2) >= 270) && (analogRead(PIN_LINE_SENSOR2) < 321)){
//    if ((analogRead(PIN_LINE_SENSOR2) >= 270) && (analogRead(PIN_LINE_SENSOR2) < 321)){

//    if ((analogRead(PIN_LINE_SENSOR2) >= 204) && (analogRead(PIN_LINE_SENSOR2) < 240)){   //Ini yang lama bener
//    if ((analogRead(PIN_LINE_SENSOR2) >= 155) && (analogRead(PIN_LINE_SENSOR2) < 220)){
//    if ((analogRead(PIN_LINE_SENSOR2) >= 147) && (analogRead(PIN_LINE_SENSOR2) < 170)){

    if (((analogRead(PIN_LINE_SENSOR) >= 55) && (analogRead(PIN_LINE_SENSOR) < 190)) || ((analogRead(PIN_LINE_SENSOR2) >= 100) && (analogRead(PIN_LINE_SENSOR2) < 250))){
      isDetectedKarpet = true;
    } else {
      isDetectedKarpet = false;
    }

    
    if (((analogRead(PIN_LINE_SENSOR) >= 0) && (analogRead(PIN_LINE_SENSOR) < 50)) || ((analogRead(PIN_LINE_SENSOR2) >= 0) && (analogRead(PIN_LINE_SENSOR2) < 90))){
      isDetectedLantai = true;
    } else {
      isDetectedLantai = false;
    }

    if (((analogRead(PIN_LINE_SENSOR) >= 220)) || ((analogRead(PIN_LINE_SENSOR2) >= 280))){
      isDetectedStiker = true;
    } else {
      isDetectedStiker = false;
    }
    
    if (((analogRead(PIN_LINE_SENSOR) >= 220) && (analogRead(PIN_LINE_SENSOR) < 1000)) || ((analogRead(PIN_LINE_SENSOR2) >= 280) && (analogRead(PIN_LINE_SENSOR2) < 1000))){
      isDetectedHalangRintang = true;
    } else {
      isDetectedHalangRintang = false;
    }
    nilaiF = analogRead(PIN_LINE_SENSOR);
    nilaiC = analogRead(PIN_LINE_SENSOR2);
  }

  String debug () {
    String text = "Line F: ";
    text.concat(analogRead(PIN_LINE_SENSOR));
    text.concat("         ");
    return text;
  }

  String debug1 () {
    String text = "Line C: ";
    text.concat(analogRead(PIN_LINE_SENSOR2));
    text.concat("         ");
    return text;
  }
}
