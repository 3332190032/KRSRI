#include "ping.h"
#include "proxy.h"
#include "flame.h"
#include "legs.h"
#include "pump.h"
#include "activation.h"
#include "lcd.h"
#include "line.h"

bool homeState = true;  // cek kondisi apakah di home buat deteksi jalan di awal  default true
bool state_isInversed = false; //true = SLWR, false = SRWR // default false
bool state_isInitialized = false;  // default false
bool naikHR1 = false;  // default false
bool naikHR2 = false;  // default false
bool turunHR1 = false; // default false
bool turunHR2 = false; // default false
bool masukPertigaan = false; // default false
bool sebelumRuang1 = true;  // default true
bool turunKakiSebelumRuang1 = false; // default false
bool udahKeluarRuang1 = false; // default false
bool udahLewatHR2 = false; // default false
bool masukRuang1 = false; // default false
bool udahMasukRuang1 = false; // default false
bool nyalainFlame = false; // default false
bool siapPadamApiR1 = false; // default false
bool pindahArahHR1 = false; //default false
bool ruang1Selesai = false; //default false
bool kucing = false;
bool pulang = false; //default false
bool otwMatiinSensor = false; //default false
bool turuninKorbanR1 = false; //default false
bool fixKeluarR1 = false; //default false
bool capit1 = false; //default false
bool capit2 = false; //default false
bool capit3 = false; //default false
bool keluarR1LewatGaris = false; //default false

bool andiMatiin = false; // default false

float konstantaKalibrasi = 0.9;

unsigned int state_startTime = 0;
unsigned int state_lastSWR = 0;
unsigned long waktu;
unsigned long waktuNaikHR1;
unsigned long waktuAndi;
unsigned long waktuKeluarR1;

int r2ToHome = 0;
int CurrentState = 0;
int CounterRead = 0;
int CounterFire = 0;

bool avoidWall(bool inverse = false);
bool flameDetection();
bool avoid3Ladder(bool inverse = false);
bool getCloser2SRWR(bool inverse = false);
void traceRoute();
void traceRouteInversed();

void setup () {
  Serial.begin(9600);
  ping::setup();
  proxy::setup();
  flame::setup();
  legs::setup();
  pump::setup();
  activation::setup();
  lcd::setup();
  line::setup();
}

void loop () {
  activation::update();
  Serial.println(CounterRead);
  waktu = millis();

  if (activation::isON) {
    if (homeState == true){
      ping::updateC();
      ping::updateC();
      if((ping::jarakPingC < 70) && (ping::jarakPingC > 50) && (ping::jarakPingA < 25) && (ping::jarakPingA > 10)){  // robot menghadap ke kanan
        lcd::justPrint("Kanan     ", "Moving forward + ");
        homeState = false;
      }
      else if(ping::jarakPingC > 70){  //Robot menghadap ke kiri
        lcd::justPrint("Kiri     ", "Rotate 180 ");
        legs::rotateCCW(4825*konstantaKalibrasi);
        homeState = false;
      }
      else if((ping::jarakPingA < 70) && (ping::jarakPingC < 25) && (ping::jarakPingC > 10)){  // Robot menghadap ke depan
        lcd::justPrint("Depan     ", "Rotate CW 90");
        legs::rotateCW(2300*konstantaKalibrasi);
        homeState = false;
      }
      else if((ping::jarakPingA > 70) && (ping::jarakPingC < 25) && (ping::jarakPingC > 10)){ // Robot menghadap ke belakang
        lcd::justPrint("Belakang     ", "Rotate CCW 90");
        legs::rotateCCW(2462*konstantaKalibrasi);
        homeState = false;
      }
    }
    else{
      // Kodenya
      if (activation::isLowMove) {
        lcd::justPrint("Path on front     ", "Moving forward + ");
        legs::forward(true);
        return;
      }
      if (!state_isInitialized) {
        state_startTime = millis();
        state_isInversed = false;  // default false
        state_isInitialized = true;
      }

      if(sebelumRuang1 == true){
        // Deteksi Halang Rintang
        ping::updateJarak();
        ping::updateJarak();
        line::update();
        line::update();

        // lcd::clean();
        // lcd::justPrintint(ping::jarakPingCandi,(ping::jarakPingCandi != 1));
        // delay(50);

        // Naik Halang Rintang 1
        if((CounterFire == 0) && (turunHR1 == false) && (naikHR1 == false) && (ping::jarakPingCandi == 999) && (line::isDetectedHalangRintang == false)){
          lcd::clean();
          lcd::justPrint("Path on front     ", "Kakti Tinggi");
          // delay(2000);
          lcd::clean();
          lcd::justPrint("Path on front     ", "Pepet kanan ");
          // delay(2000);
          naikHR1 = true;
          // waktuNaikHR1 = waktu;
          pindahArahHR1 = true;
        }
        if((pindahArahHR1 == true) && (line::isDetectedHalangRintang == true)){
          waktuNaikHR1 = waktu;
          pindahArahHR1 = false;
          // lcd::justPrint("Path on front     ", "andi ");
          // delay(2000);
        }
        // Turun Halang Rintang 1
        else if((CounterFire == 0) && (turunHR1 == false) && (naikHR1 == true) && ((waktu - waktuNaikHR1) >= 5000) && (line::isDetectedHalangRintang == true)){
          lcd::clean();
          lcd::justPrint("Path on front     ", "Pepet Kiri ");
          // delay(2000);
          turunHR1 = true;
          naikHR1 = false;
          turunKakiSebelumRuang1 = true;
          otwMatiinSensor = true;
        }

        // matiin sensor line
        else if((line::isDetectedLantai == true) && (otwMatiinSensor == true)){
          waktuAndi = millis();
        }


        // Turunin Kaki
        else if((CounterFire == 0) && (turunHR1 == true) && (line::isDetectedKarpet == true) && (turunKakiSebelumRuang1 == true) && ((waktu - waktuAndi) >= 2000)){
          lcd::clean();
          lcd::justPrint("Path on front     ", "Kaki Pendek ");
          // delay(2000);
          turunKakiSebelumRuang1 = false;
          sebelumRuang1 = false;
          masukRuang1 = true;
        }

        // Tentuin Arah Pepet
        if(naikHR1 == true){
          state_isInversed = false;
        }
        else if(turunHR1 == true){
          state_isInversed = true;
        }
      }

      ping::update();
      proxy::update();
      flame::update();
      line::update();
      // Masuk Ruang 1 lewatin garis
      if((masukRuang1 == true) && (line::isDetectedStiker == true) && (ruang1Selesai == false)){
        udahMasukRuang1 = true;
        // unsigned int startCounter = millis();
        // unsigned int currentCounter = millis();
        // while ((currentCounter - startCounter) < (3000*konstantaKalibrasi)) {
        //   lcd::message(1, lcd::MOVING_FORWARD);
        //   currentCounter = millis();
        //   if (!avoidWall(true)) return;
        //   legs::forward();
        // }
        // legs::rotateCW(2250*konstantaKalibrasi);
        legs::rotateCW(1000*konstantaKalibrasi);
        nyalainFlame = true;
        // lcd::clean();
        // lcd::justPrint(" ", "F Aktif");
        // delay(2000);
        ruang1Selesai = true;
      }
      // // Masuk RUang 1 buat nyalain sensor flame
      // if((CounterFire == 0) && (line::isDetectedKarpet == true) && (udahMasukRuang1 == true) && (siapPadamApiR1 == false)){
      //   nyalainFlame = true;
      //   siapPadamApiR1 = true;
      // }
      // // Keluar Ruang 1     ======= Diganti di flame Detection
      // if((CounterFire == 1) && (line::isDetectedStiker == true) && (udahKeluarRuang1 == false)){
      //   udahKeluarRuang1 = true;
      // }      


    if((CounterFire == 1) && (line::isDetectedKarpet == true) && (udahKeluarRuang1 == true) && (turuninKorbanR1 == false)){
        
      //  ===================================== Perintah untuk Nurunin Capit =====================================

      unsigned int startCountercapit1 = millis();
      unsigned int currentCountercapit1 = millis();
      while ((currentCountercapit1 - startCountercapit1) < (100) && (capit1 == false)) { 
        legs::capitLepas();
        currentCountercapit1 = millis();
      }
      capit1 = true;
      


      //  ===================================== Perintah untuk Nurunin Capit =====================================
        turuninKorbanR1 = true;
    }

      if((CounterFire == 1) && (udahKeluarRuang1 == true) && (turuninKorbanR1 == true) && (line::isDetectedStiker == true) && (fixKeluarR1 == false)){
        fixKeluarR1 = true;
//        delay(2000);
      }


      // Dari ruang 1 ke Ruang 2
      if((CounterFire == 1) && (line::isDetectedKarpet == true) && (udahKeluarRuang1 == true) && (turuninKorbanR1 == true) && (fixKeluarR1 == true) && (keluarR1LewatGaris == false)){
        waktuKeluarR1 = waktu;
        keluarR1LewatGaris = true;
      }
      if((CounterFire == 1) && (line::isDetectedKarpet == true) && (udahKeluarRuang1 == true) && (turuninKorbanR1 == true) && (fixKeluarR1 == true) && ((waktu - waktuKeluarR1) >= 2000)){
        masukPertigaan = true;
      }
      if((masukPertigaan == true) && (naikHR2 == false)){
        // lcd::justPrintint(line::nilaiF, ping::jarakC);
        if((ping::jarakC > 5) && (ping::jarakC < 20) && (line::isDetectedKarpet == false)){
          lcd::clean();
          lcd::justPrint(" ", "Puter Kiri 90 ");
          // delay(2000);
          lcd::clean();
          lcd::justPrint(" ", "Pepet Kanan");
          // delay(2000);
          lcd::clean();
          lcd::justPrint(" ", "Kaki Tinggi ");
          // delay(2000);
          legs::rotateCCW(2462*konstantaKalibrasi);
          // lcd::justPrintint(line::nilaiF, ping::jarakC);
          state_isInversed = false;
          masukPertigaan = false;
          naikHR2 = true;
        }
        if((ping::jarakC > 19)){
          if (!avoidWall(true)) return;
          legs::forward();
          lcd::clean();
          lcd::justPrint(" ", "Nyebrang Lurus");
          // delay(2000);
          // lcd::justPrintint(line::nilaiF, ping::jarakC);
        }
      }
      else{
        // Konfirmasi udah ngelewatin HR2
        if((CounterFire == 1) && (turunHR2 == false) && (naikHR2 == true) && (udahLewatHR2 == false) && (line::isDetectedHalangRintang == true)){
          udahLewatHR2 = true;
          nyalainFlame = true;
          // delay(2000);
        }
        // Turun Halang Rintang 2
        else if((CounterFire == 1) && (turunHR2 == false) && (naikHR2 == true) && (udahLewatHR2 == true) && (ping::jarakC < 20) && (line::isDetectedHalangRintang == false)){
          turunHR2 = true;
          // nyalainFlame = true;
          lcd::clean();
          lcd::justPrint(" ", "API 2");
          // delay(2000);
        }

        // Ruang 2 ke Home  isDetectedLantai
        if((CounterFire == 2) && (line::isDetectedHalangRintang == true) && (r2ToHome == 0) && (ping::jarakA < 40) && (line::isDetectedLantai == false)){
          r2ToHome = 1;
          lcd::clean();
          lcd::justPrint(" ", "Satu");
          // delay(2000);
        }
        else if((CounterFire == 2) && (line::isDetectedHalangRintang == false) && (r2ToHome == 1) && (ping::jarakA > 40) && (line::isDetectedLantai == true)){
          r2ToHome = 2;
          lcd::clean();
          lcd::justPrint(" ", "Dua");
          // delay(2000);
        }
        else if((CounterFire == 2) && (line::isDetectedHalangRintang == true) && (r2ToHome == 2) && (ping::jarakA < 40) && (line::isDetectedLantai == false)){
          r2ToHome = 3;
          lcd::clean();
          lcd::justPrint(" ", "Tiga");
          // delay(2000);
        }
        else if((CounterFire == 2) && (line::isDetectedHalangRintang == false) && (r2ToHome == 3) && (ping::jarakA > 40) && (line::isDetectedLantai == true)){
          r2ToHome = 4;
          lcd::clean();
          lcd::justPrint(" ", "Empat");
          // delay(2000);
        }
        else if((r2ToHome == 4) && (line::isDetectedKarpet == true)){
          unsigned int startCounter = millis();
          unsigned int currentCounter = millis();
          while ((currentCounter - startCounter) < (1800*konstantaKalibrasi)) { //2500
            lcd::clean();
            lcd::justPrint(" ", "Maju Ke Home");
            currentCounter = millis();
            if (!avoidWall(true)) return;
            legs::forward();
            pulang = true;
          }
          while(pulang == true){
              lcd::justPrint(" ", "Berhenti Home");
              legs::standby();
          }
        //   legs::standby();
        //   legs::standby();
        //   legs::standby();
        //   legs::standby();
        //   lcd::clean();
        //   lcd::justPrint(" ", "Berhenti Home");
        //   delay(50000);
        }

        // lcd::justPrint(" ", " ");

        if (state_isInversed) {          // Pepet Kiri
          if (ping::isOnSLWR) {
            state_lastSWR = millis();
          }
          // if (detectLine()) return;
          if (!avoidWall(true)) return;
          if((CounterFire < 3) && (nyalainFlame == true)){
            if (flameDetection()) return;
          }
          // if (!avoid3Ladder(true)) return;
          if (!getCloser2SRWR(true)) return;
          traceRouteInverse();
        } else {                         // Pepet Kanan
          if (ping::isOnSRWR) {
            state_lastSWR = millis();
          }
          // if (detectLine()) return;
          if (!avoidWall()) return;
          if((CounterFire < 3) && (nyalainFlame == true)){
            if (flameDetection()) return;
          }
          // if (!avoid3Ladder()) return;
          if (!getCloser2SRWR()) return;
          traceRoute();
        }
      }

      // yang gua komen
      // line::update();
      // legs::forward();  // Maju cepet
      


      // ping::updateJarak();
      // ping::updateJarak();
      // Serial.print(ping::jarakPingCandi);
      // Serial.println("CM");
      // delay(10);



      // ping::updateC();
      // ping::updateJarak();
      // ping::updateJarak();

      // line::update();
      // line::update();
      // lcd::justPrintint(line::nilaiF, line::isDetectedHalangRintang);
      // delay(100);
      
    //      lcd::message(0, andi);
    //      text.concat(line::nilaiF);
      
    } // Tutup Else
  } else {
    if (state_isInitialized) state_isInitialized = false;

    if (activation::isMenu) {           // Debug
      if (activation::isMenuChanged) lcd::clean();
      switch (activation::activeMenu) {
        case 0:
          lcd::justPrint(ping::debug(), ping::debug1());
          break;
        case 1:
          lcd::justPrint(flame::debug(), flame::debug1());
          break;
        case 2:
          lcd::justPrint(proxy::debug(), activation::debugSoundActivation());
          break;
        case 3:
          lcd::justPrint(line::debug(), line::debug1());
          break;
        case 4:
          lcd::justPrint("Press start to", "extinguish");
          pump::activate(activation::isStartPushed);
          break;
        default:
          lcd::justPrint("== DEBUG MODE ==", "Press stop again");
      }
    } else {
      standBy();
    }
  }
}

void standBy () {
  if (legs::isStandby) {
    lcd::message(0, lcd::STANDBY);
    lcd::message(1, lcd::BLANK);
    return;
  }

  if (legs::isNormalized) {
    legs::standby();
    return;
  }

  lcd::message(0, lcd::NORMALIZING);
  lcd::message(1, lcd::BLANK);
  legs::normalize();
}

bool avoid3Ladder (bool inverse = false) {
  if (proxy::isDetectingSomething && CurrentState == 0 ) {
    lcd::message(0, lcd::THERE_IS_OBSTACLE);
    CurrentState++;
    if (inverse) {
      unsigned int startCounter = millis();
      unsigned int currentCounter = millis();
      while ((currentCounter - startCounter) <= (11800)) {
        legs::forwardHigher();
        currentCounter = millis();
      }
      while ((currentCounter - startCounter) <= (13800)) {
        legs::shiftRight();
        currentCounter = millis();
      }
    }
    pingupdate();
    state_isInversed = false;
    return true;
  }
  return true;
}

bool avoidWall (bool inverse = false) {
  short int minPos = 0;
  short int maxPos = 8;
  bool minPosFound = false;
  bool maxPosFound = false;

  if (!minPosFound && ping::near_a) {
    minPos = 0;
    minPosFound = true;
  }
  if (!minPosFound && ping::near_b) {
    minPos = 2;
    minPosFound = true;
  }
  if (!minPosFound && ping::near_c) {
    minPos = 4;
    minPosFound = true;
  }
  if (!minPosFound && ping::near_d) {
    minPos = 6;
    minPosFound = true;
  }
  if (!minPosFound && ping::near_e) {
    minPos = 8;
    minPosFound = true;
  }

  if (!maxPosFound && ping::near_e) {
    maxPos = 8;
    maxPosFound = true;
  }
  if (!maxPosFound && ping::near_d) {
    maxPos = 6;
    maxPosFound = true;
  }
  if (!maxPosFound && ping::near_c) {
    maxPos = 4;
    maxPosFound = true;
  }
  if (!maxPosFound && ping::near_b) {
    maxPos = 2;
    maxPosFound = true;
  }
  if (!maxPosFound && ping::near_a) {
    maxPos = 0;
    maxPosFound = true;
  }

  if (!minPosFound || !maxPosFound) return true; // this means wall is successfully avoided, if it's not then continue below

  short int avg = (maxPos + minPos) / 2;

  if (avg < 1) {
    lcd::message(0, lcd::WALL_ON_RIGHT);
    lcd::message(1, lcd::SHIFTING_LEFT);
    legs::shiftLeft();
  } else if (1 <= avg && avg <= 3) {
    lcd::message(0, lcd::WALL_ON_RIGHT);
    lcd::message(1, lcd::ROTATING_CCW);
    legs::rotateCCW();
  } else if (3 < avg && avg < 5) {
    lcd::message(0, lcd::WALL_ON_FRONT);

    if ((maxPos - minPos) == 0) {
      lcd::message(1, lcd::MOVING_BACKWARD);
      legs::backward(); // wall surface is flat
    } else {
      lcd::message(1, lcd::ROTATING_CW);

      if (inverse) {
        legs::rotateCCW(); // wall surface detected is not flat
      } else {
        legs::rotateCW(); // wall surface detected is not flat
      }
    }
  } else if (5 <= avg && avg <= 7) {
    lcd::message(0, lcd::WALL_ON_LEFT);
    lcd::message(1, lcd::ROTATING_CW);
    legs::rotateCW();
  } else if (avg > 7) {
    lcd::message(0, lcd::WALL_ON_LEFT);
    lcd::message(1, lcd::SHIFTING_RIGHT);
    legs::shiftRight();
  }

  return false;
}

// bool detectLine () {
//   //Masuk Room 3
//   if (line::isDetected && CounterRead == 0) {
//     CounterRead += 1;
//     lcd::message(0, lcd::LINE_DETECTED);
//     unsigned int startCounter = millis();
//     unsigned int currentCounter = millis();
//     while ((currentCounter - startCounter) < 2500) {
//       lcd::message(1, lcd::MOVING_FORWARD);
//       currentCounter = millis();
//       legs::forward();
//     }
//      while ((currentCounter - startCounter) < 3200) {
//       lcd::message(1, lcd::ROTATING_CCW);
//       currentCounter = millis();
//       legs::rotateCCW();
//     }
//     return true;
//   }

//   //keluar room 3
//   if (line::isDetected && CounterRead == 1 ) {
//     CounterRead += 1;
//     lcd::message(0, lcd::LINE_DETECTED);
//     unsigned int startCounter = millis();
//     unsigned int currentCounter = millis();
//     while ((currentCounter - startCounter) < 1600) {
//       lcd::message(1, lcd::MOVING_FORWARD);
//       currentCounter = millis();
//       legs::forward();
//     }
//     return true;
//   }

//   //Masuk Room 2
//   if (line::isDetected && CounterRead == 2) {
//     CounterRead += 1;
//     lcd::message(0, lcd::LINE_DETECTED);
//     unsigned int startCounter = millis();
//     unsigned int currentCounter = millis();
//     while ((currentCounter - startCounter) < 3500) {
//       lcd::message(1, lcd::MOVING_FORWARD);
//       currentCounter = millis();
//       legs::forward();
//     }
//     while ((currentCounter - startCounter) < 5500) {
//       lcd::message(1, lcd::ROTATING_CCW);
//       currentCounter = millis();
//       legs::rotateCW();
//     }
//     pingupdate();
//     return true;
//   }

//   //keluar room 2
//   if (line::isDetected && CounterRead == 3 ) {
//     CounterRead += 1;
//     lcd::message(0, lcd::LINE_DETECTED);
//     unsigned int startCounter = millis();
//     unsigned int currentCounter = millis();
//     while ((currentCounter - startCounter) < 1600) {
//       lcd::message(1, lcd::MOVING_FORWARD);
//       currentCounter = millis();
//       legs::forward();
//     }
//     return true;
//   }
  
//   //Masuk Room 1
//   if (line::isDetected && CounterRead == 4) {
//     CounterRead += 1;
//     lcd::message(0, lcd::LINE_DETECTED);
//     unsigned int startCounter = millis();
//     unsigned int currentCounter = millis();
//     while ((currentCounter - startCounter) < 4500) {
//       lcd::message(1, lcd::MOVING_FORWARD);
//       currentCounter = millis();
//       legs::forward();
//     }
//     while ((currentCounter - startCounter) < 5000) {
//       lcd::message(1, lcd::ROTATING_CCW);
//       currentCounter = millis();
//       legs::rotateCCW();
//     }
//     while ((currentCounter - startCounter) < 7500) {
//       lcd::message(1, lcd::SHIFTING_RIGHT);
//       currentCounter = millis();
//       legs::shiftRight();
//     }
//     while ((currentCounter - startCounter) < 9000) {
//       lcd::message(1, lcd::MOVING_FORWARD);
//       currentCounter = millis();
//       legs::forward();
//     }
//     pingupdate();
//     state_isInversed = false; // pepet kanan
//     return true;
//   }

//   //keluar room 1
//   if (line::isDetected && CounterRead == 5) {
//     CounterRead += 1;
//     lcd::message(0, lcd::LINE_DETECTED);
//     unsigned int startCounter = millis();
//     unsigned int currentCounter = millis();
//     while ((currentCounter - startCounter) < 1600) {
//       lcd::message(1, lcd::MOVING_FORWARD);
//       currentCounter = millis();
//       legs::forward();
//     }
//     while ((currentCounter - startCounter) < 3100) {
//       lcd::message(1, lcd::ROTATING_CW);
//       currentCounter = millis();
//       legs::rotateCW();
//     }
//     while ((currentCounter - startCounter) < 5100) {
//       lcd::message(1, lcd::MOVING_BACKWARD);
//       currentCounter = millis();
//       legs::backward();
//     }
//     pingupdate();
//     state_isInversed = true; // pepet kiri
//     return true;
//   }

//   //Indikator Room 1 ke Home
//   if (line::isDetectedGlue && CounterRead == 6) {
//     CounterRead = CounterRead + 1;
//     lcd::message(0, lcd::LINE_DETECTED);
//     unsigned int startCounter = millis();
//     unsigned int currentCounter = millis();
//     while ((currentCounter - startCounter) < 2000) {
//       lcd::message(1, lcd::MOVING_FORWARD);
//       currentCounter = millis();
//       legs::forward();
//     }
//      while ((currentCounter - startCounter) < 2300) {
//       lcd::message(1, lcd::ROTATING_CCW);
//       currentCounter = millis();
//       legs::rotateCCW();
//     }
//     while ((currentCounter - startCounter) < 4300) {
//       lcd::message(1, lcd::MOVING_FORWARD);
//       currentCounter = millis();
//       legs::forward();
//     }
//     while ((currentCounter - startCounter) < 4800) {
//       lcd::message(1, lcd::ROTATING_CW);
//       currentCounter = millis();
//       legs::rotateCW();
//     }
//     while ((currentCounter - startCounter) < 5800) {
//       lcd::message(1, lcd::MOVING_FORWARD);
//       currentCounter = millis();
//       legs::forward();
//     }
//     while ((currentCounter - startCounter) < 8000) {
//       lcd::message(1, lcd::ROTATING_CW);
//       currentCounter = millis();
//       legs::rotateCW();
//     }
//     while ((currentCounter - startCounter) < 35200) {
//       lcd::message(1, lcd::ROCK_AND_ROLL);
//       currentCounter = millis();
//       legs::shiftLeftHigher();
//     }
//     while ((currentCounter - startCounter) < 38200) {
//       lcd::message(1, lcd::MOVING_BACKWARD);
//       currentCounter = millis();
//       legs::backward();
//     }
//     while ((currentCounter - startCounter) < 41200) {
//       lcd::message(1, lcd::ROCK_AND_ROLL);
//       currentCounter = millis();
//       legs::shiftLeftHigher();
//     }
//     pingupdate();
//     state_isInversed = true;
//     return true;
//   }
//   if (CounterRead == 7) {
//     standBy();
//     return true;
//   }
//   return false;
// }

bool flameDetection () {
  if (flame::is_right && (ping::near_b || ping::near_a)) {
    lcd::message(0, lcd::FIRE_ON_RIGHT);
    lcd::message(1, lcd::SHIFTING_LEFT);
    legs::shiftLeft();
    return true;
  }

  if (flame::is_left && (ping::near_d || ping::near_e)) {
    lcd::message(0, lcd::FIRE_ON_LEFT);
    lcd::message(1, lcd::SHIFTING_RIGHT);
    legs::shiftRight();
    return true;
  }

  if (flame::is_right && !flame::is_left && !flame::is_center) {
    lcd::message(0, lcd::FIRE_ON_RIGHT);
    lcd::message(1, lcd::ROTATING_CW);
    legs::rotateCW();
    return true;
  }

  if (flame::is_left && !flame::is_right && !flame::is_center) {
    lcd::message(0, lcd::FIRE_ON_LEFT);
    lcd::message(1, lcd::ROTATING_CCW);
    legs::rotateCCW();
    return true;
  }

  if (flame::is_right && !flame::is_left && flame::is_center) {
    lcd::message(0, lcd::FIRE_ON_RIGHT);
    lcd::message(1, lcd::ROTATING_CW);
    legs::rotateCWLess();
    return true;
  }

  if (flame::is_left && !flame::is_right && flame::is_center) {
    lcd::message(0, lcd::FIRE_ON_LEFT);
    lcd::message(1, lcd::ROTATING_CCW);
    legs::rotateCCWLess();
    return true;
  }

  //Pemadaman Api Ruang 1
  if (flame::is_center && CounterFire == 0) {
    lcd::message(0, lcd::FIRE_ON_CENTER);
    if (proxy::isDetectingSomething2) {
      lcd::message(1, lcd::EXTINGUISHING);
      unsigned int startCounter = millis();
      unsigned int currentCounter = millis();
      while ((currentCounter - startCounter) < (400*konstantaKalibrasi)) { // def 400
        lcd::message(1, lcd::ROTATING_CW);
        pump::menyebar();
        legs::rotateCW();
        currentCounter = millis();
      }
      pump::menyebarstop();
      startCounter = millis();
      while ((currentCounter - startCounter) < (1000*konstantaKalibrasi)) { // def 700
        lcd::message(1, lcd::ROTATING_CW);
        pump::menyebar();
        legs::rotateCCW();
        currentCounter = millis();
      }
      pump::menyebarstop();
      // pump::extinguish(1000);
      // lcd::clean();
      // lcd::justPrint(" ", "Puter Balik");
      // delay(2000);
      // lcd::clean();
      // lcd::justPrint(" ", "Pepet Kanan");
      // delay(2000);
      if (flame::state_isIndicatorOn) {
        digitalWrite(PIN_FLAME_INDICATOR, HIGH);
      }
      unsigned int startCounterMundur = millis();
      unsigned int currentCountermundur = millis();
      while ((currentCountermundur - startCounterMundur) < (2000*konstantaKalibrasi)) {
        lcd::message(1, lcd::MOVING_FORWARD);
        currentCountermundur = millis();
        if (!avoidWall(true)) return;
        legs::backward();
      }
      legs::rotateCW(4800*konstantaKalibrasi); // Kalibrasi lagi biar arah keluar   4500
      CounterFire += 1;
    //   nyalainFlame = false;
      state_isInversed = false;
      line::update();
      unsigned int startCounterMaju = millis();
      unsigned int currentCounterMaju = millis();
      while ((currentCounterMaju - startCounterMaju) < (500*konstantaKalibrasi)) {
        lcd::message(1, lcd::MOVING_FORWARD);
        currentCounterMaju = millis();
        if (!avoidWall(true)) return;
        legs::shiftRight();
      }

      //  ===================================== Perintah untuk Nurunin Capit =====================================

      
      unsigned int startCountercapit2 = millis();
      unsigned int currentCountercapit2 = millis();
      while ((currentCountercapit2 - startCountercapit2) < (100) && (capit2 == false)) { 
        legs::capitTurun();
        currentCountercapit2 = millis();
      }
      capit2 = true;
      


      //  ===================================== Perintah untuk Nurunin Capit =====================================
      udahKeluarRuang1 = true;
    }
    else {
      lcd::message(1, lcd::MOVING_FORWARD);
      legs::forward();
    }
    return true;
  }
  //Pemadaman Api Ruang 2
  if (flame::is_center && CounterFire == 1) {
    lcd::message(0, lcd::FIRE_ON_CENTER);
    if (proxy::isDetectingSomething2) {
      unsigned int startCounterMundurLilin = millis();
      unsigned int currentCountermundurLilin = millis();
      while ((currentCountermundurLilin - startCounterMundurLilin) < (300*konstantaKalibrasi)) {
        lcd::message(1, lcd::MOVING_FORWARD);
        currentCountermundurLilin = millis();
        if (!avoidWall(true)) return;
        legs::backward();
      }
      lcd::message(1, lcd::EXTINGUISHING);
      unsigned int startCounter = millis();
      unsigned int currentCounter = millis();
      while ((currentCounter - startCounter) < (400*konstantaKalibrasi)) {
        lcd::message(1, lcd::ROTATING_CW);
        pump::menyebar();
        legs::rotateCW();
        currentCounter = millis();
      }
      pump::menyebarstop();
      startCounter = millis();
      while ((currentCounter - startCounter) < (1700*konstantaKalibrasi)) { // def 1500
        lcd::message(1, lcd::ROTATING_CW);
        pump::menyebar();
        legs::rotateCCW();
        currentCounter = millis();
      }
      pump::menyebarstop();
      unsigned int startCounterMundur = millis();
      unsigned int currentCountermundur = millis();
      while ((currentCountermundur - startCounterMundur) < (3000*konstantaKalibrasi)) {
        lcd::message(1, lcd::MOVING_FORWARD);
        currentCountermundur = millis();
        if (!avoidWall(true)) return;
        legs::backward();
      } 
      if (flame::state_isIndicatorOn) {
        digitalWrite(PIN_FLAME_INDICATOR, HIGH);
      }
      legs::rotateCCW(3825*konstantaKalibrasi); //def 4025
      unsigned int startCounterMajuCapit = millis();
      unsigned int currentCounterMajuCapit = millis();
      while ((currentCounterMajuCapit - startCounterMajuCapit) < (1000*konstantaKalibrasi)) {
        lcd::message(1, lcd::MOVING_FORWARD);
        currentCounterMajuCapit = millis();
        if (!avoidWall(true)) return;
        legs::forward();
      }

    //  ===================================== Perintah untuk Nurunin Capit =====================================

    unsigned int startCountercapit3 = millis();
    unsigned int currentCountercapit3 = millis();
    while ((currentCountercapit3 - startCountercapit3) < (100) && (capit3 == false)) { 
      legs::capitTurun();
      currentCountercapit3 = millis();
    }
    capit3 = true;
    


    //  ===================================== Perintah untuk Nurunin Capit =====================================
      CounterFire += 1;
      nyalainFlame = false;
      state_isInversed = true;
    }
    else {
      lcd::message(1, lcd::MOVING_FORWARD);
      legs::forward();
    }
    return true;
  }
  return false;
}

bool getCloser2SRWR (bool inverse = false) {
  if (inverse) {
    if (ping::far_e && !ping::far_d && !ping::isOnSLWR) {
      lcd::message(0, lcd::FOUND_SLWR);
      lcd::message(1, lcd::SHIFTING_LEFT);
      legs::shiftLeft();
      return false;
    }
  } else {
    if (ping::far_a && !ping::far_b && !ping::isOnSRWR) {
      lcd::message(0, lcd::FOUND_SRWR);
      lcd::message(1, lcd::SHIFTING_RIGHT);
      legs::shiftRight();
      return false;
    }
  }

  return true;
}

void traceRoute () {
  if (!ping::far_a && !ping::far_b) {
    lcd::message(0, lcd::PATH_ON_RIGHT);
    lcd::message(1, lcd::TURNING_RIGHT);
    legs::turnRight();
  } else if (ping::far_a && !ping::far_c) {
    lcd::message(0, lcd::PATH_ON_FRONT);
    lcd::message(1, lcd::MOVING_FORWARD);

    if((turunKakiSebelumRuang1 == true) || (naikHR1 == true) || (CounterFire == 2) || ((naikHR2 == true) && (turunHR2 == false))){
      legs::forwardHigher(); //Maju Kaki tinggi
    }
    else{
      legs::forward();
    }
  } else if (ping::far_a && ping::far_c && !ping::far_e) {
    lcd::message(0, lcd::PATH_ON_LEFT);
    lcd::message(1, lcd::TURNING_LEFT);
    legs::turnLeft();
  } else {
    lcd::message(0, lcd::NO_PATH);
    lcd::message(1, lcd::ROTATING_CCW);
    legs::rotateCCW(700*konstantaKalibrasi);
    pingupdate();
  }
}

void traceRouteInverse () {
  if (!ping::far_e && !ping::far_d) {
    lcd::message(0, lcd::PATH_ON_LEFT);
    lcd::message(1, lcd::TURNING_LEFT);
    legs::turnLeft();
  } else if (ping::far_e && !ping::far_c) {
    lcd::message(0, lcd::PATH_ON_FRONT);
    lcd::message(1, lcd::MOVING_FORWARD);

    if((turunKakiSebelumRuang1 == true) || (naikHR1 == true) || (CounterFire == 2) || ((naikHR2 == true) && (turunHR2 == false))){
      legs::forwardHigher(); //Maju Kaki tinggi
    }
    else{
      legs::forward();
    }
  } else if (ping::far_e && ping::far_c && !ping::far_a) {
    lcd::message(0, lcd::PATH_ON_RIGHT);
    lcd::message(1, lcd::TURNING_RIGHT);
    legs::turnRight();
  } else {
    lcd::message(0, lcd::NO_PATH);
    lcd::message(1, lcd::ROTATING_CW);
    legs::rotateCW(700*konstantaKalibrasi);
    pingupdate();
  }
}

void pingupdate() {
  ping::update();
  ping::update();
  ping::update();
  ping::update();
  ping::update();
}
