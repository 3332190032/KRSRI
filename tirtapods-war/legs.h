#include <SoftwareSerial.h>

namespace legs {
bool isNormalized = false;
bool isStandby = false;
bool kakiNapak = false;

enum MoveType {
  STANDBY,
  NORMALIZE,
  FORWARD,
  FORWARD_LOW,
  FORWARD_HIGHER,
  CAPIT_TURUN,
  CAPIT_LEPAS,
  BACKWARD,
  SHIFT_RIGHT,
  SHIFT_LEFT,
  SHIFT_LEFTHIGHER,
  ROTATE_CW,
  ROTATE_CCW,
  ROTATE_CW_LESS,
  ROTATE_CCW_LESS,
  TURN_RIGHT,
  TURN_LEFT
};

MoveType state_currentMove = NORMALIZE;
unsigned short int state_step2keep = 0;
unsigned long int state_lastMoveRecord = 0;
unsigned short int state_nextStep = 0;
bool state_isComboAUp = true;
bool state_isComboBUp = true;
unsigned short int state_endStep = 3;

SoftwareSerial com(19, 18); // RX, TX

void setup () {
  com.begin(9600);
}


   // START OF CODE GENERATED

  void ssc_standby () {
    com.println(F("#23P1100 #11P1500 T200"));
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1593 #5P2308 #6P2137 #8P1300 #9P2597 #10P2302 #12P1334 #13P2251 #14P2445 #20P1484 #21P752 #22P750 #24P1300 #25P1028 #26P500 #28P1248 #29P786 #30P894 T200"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1593 #5P2308 #6P2137 #8P1300 #9P2597 #10P2302 #12P1334 #13P2251 #14P2445 #20P1484 #21P752 #22P750 #24P1300 #25P1028 #26P500 #28P1248 #29P786 #30P894 T200"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#4P1593 #5P2308 #6P2137 #8P1300 #9P2597 #10P2302 #12P1334 #13P2251 #14P2445 #20P1484 #21P752 #22P750 #24P1300 #25P1028 #26P500 #28P1248 #29P786 #30P894 T200"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#4P1593 #5P2308 #6P2137 #8P1300 #9P2597 #10P2302 #12P1334 #13P2251 #14P2445 #20P1484 #21P752 #22P750 #24P1300 #25P1028 #26P500 #28P1248 #29P786 #30P894 T200"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

  void ssc_normalize () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1593 #5P2308 #6P2137 #12P1334 #13P2251 #14P2445 #24P1300 #25P1028 #26P500 T200"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1593 #5P1953 #6P1925 #12P1334 #13P1950 #14P2242 #24P1300 #25P1395 #26P718 T200"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#8P1300 #9P2597 #10P2302 #20P1484 #21P752 #22P750 #28P1248 #29P786 #30P894 T200"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#8P1300 #9P2259 #10P2079 #20P1484 #21P1107 #22P974 #28P1248 #29P1073 #30P1057 T200"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

  void ssc_normalize_sync () {
    com.println(F("#4P1593 #5P2308 #6P2137 #12P1334 #13P2251 #14P2445 #24P1300 #25P1028 #26P500 T200")); delay(200);
    com.println(F("#4P1593 #5P1953 #6P1925 #12P1334 #13P1950 #14P2242 #24P1300 #25P1395 #26P718 T200")); delay(200);
    com.println(F("#8P1300 #9P2597 #10P2302 #20P1484 #21P752 #22P750 #28P1248 #29P786 #30P894 T200")); delay(200);
    com.println(F("#8P1300 #9P2259 #10P2079 #20P1484 #21P1107 #22P974 #28P1248 #29P1073 #30P1057 T200")); delay(200);
  }

  void ssc_forward_low () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1733 #5P2333 #6P2203 #8P1175 #9P2592 #10P2287 #12P1440 #13P2217 #14P2358 #20P1575 #21P793 #22P846 #24P1195 #25P1033 #26P515 #28P1344 #29P765 #30P843 T200"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1733 #5P2333 #6P2203 #8P1175 #9P2592 #10P2287 #12P1440 #13P2217 #14P2358 #20P1575 #21P793 #22P846 #24P1195 #25P1033 #26P515 #28P1344 #29P765 #30P843 T200"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#4P1482 #5P2267 #6P2047 #8P1425 #9P2592 #10P2287 #12P1201 #13P2272 #14P2508 #20P1371 #21P727 #22P681 #24P1405 #25P1033 #26P515 #28P1172 #29P819 #30P963 T200"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#4P1482 #5P2267 #6P2047 #8P1425 #9P2592 #10P2287 #12P1201 #13P2272 #14P2508 #20P1371 #21P727 #22P681 #24P1405 #25P1033 #26P515 #28P1172 #29P819 #30P963 T200"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

  void ssc_forward_higher () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1733 #5P1792 #6P1855 #8P1175 #9P3081 #10P2505 #12P1440 #13P1824 #14P2067 #20P1575 #21P422 #22P683 #24P1195 #25P1540 #26P841 #28P1344 #29P260 #30P650 T240"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1733 #5P1792 #6P1855 #8P1175 #9P2125 #10P1954 #12P1440 #13P1824 #14P2067 #20P1575 #21P1255 #22P1166 #24P1195 #25P1540 #26P841 #28P1344 #29P1204 #30P1111 T240"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#4P1482 #5P2638 #6P2201 #8P1425 #9P2125 #10P1954 #12P1201 #13P2801 #14P2750 #20P1371 #21P1268 #22P1049 #24P1405 #25P503 #26P301 #28P1172 #29P1194 #30P1196 T240"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#4P1482 #5P1805 #6P1744 #8P1425 #9P2125 #10P1954 #12P1201 #13P1813 #14P2174 #20P1371 #21P1268 #22P1049 #24P1405 #25P1540 #26P841 #28P1172 #29P1194 #30P1196 T240"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

// ============================= Capit Turun =============================

  void ssc_capitTurun () {
    com.println(F("#11P800 T200"));
    delay(200);
    com.println(F("#23P2600 T200"));
    delay(3000);
    com.println(F("#11P1100 T200"));
    delay(200);
    com.println(F("#23P1100 T200"));
    delay(200);
  }
  void ssc_capitLepas () {
    com.println(F("#23P2600 T200"));
    delay(200);
    com.println(F("#11P800 T200"));
    delay(3000);
    com.println(F("#23P1100 T200"));
    delay(200);
    com.println(F("#11P1100 T200"));
    delay(200);
//    switch (state_nextStep) {
//      case 0:
//        com.println(F("#23P2600 T200"));
//        state_isComboBUp = true;
//        state_nextStep = 1;
//        break;
//      case 1:
//        com.println(F("#11P800 T200"));
//        state_isComboBUp = false;
//        state_nextStep = 2;
//        break;
//      case 2:
//        com.println(F("#23P1100 T200"));
//        state_isComboAUp = true;
//        state_nextStep = 3;
//        break;
//      case 3:
//        com.println(F("#11P1100 T200"));
//        state_isComboAUp = false;
//        state_nextStep = 0;
//        break;
//    }
  }

// ============================= Capit Turun =============================

  void ssc_forward () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1733 #5P1947 #6P1973 #8P1175 #9P2695 #10P2340 #12P1440 #13P1945 #14P2172 #20P1575 #21P704 #22P801 #24P1195 #25P1393 #26P729 #28P1344 #29P666 #30P799 T200"));
        state_isComboBUp = true;
        state_nextStep = 1;
        kakiNapak = false;
        break;
      case 1:
        com.println(F("#4P1733 #5P1947 #6P1973 #8P1175 #9P2261 #10P2069 #12P1440 #13P1945 #14P2172 #20P1575 #21P1112 #22P1050 #24P1195 #25P1393 #26P729 #28P1344 #29P1078 #30P1020 T200"));
        state_isComboBUp = false;
        state_nextStep = 2;
        kakiNapak = true;
        break;
      case 2:
        com.println(F("#4P1482 #5P2356 #6P2089 #8P1425 #9P2261 #10P2069 #12P1201 #13P2377 #14P2564 #20P1371 #21P1113 #22P923 #24P1405 #25P922 #26P462 #28P1172 #29P1078 #30P1112 T200"));
        state_isComboAUp = true;
        state_nextStep = 3;
        kakiNapak = false;
        break;
      case 3:
        com.println(F("#4P1482 #5P1948 #6P1853 #8P1425 #9P2261 #10P2069 #12P1201 #13P1945 #14P2288 #20P1371 #21P1113 #22P923 #24P1405 #25P1393 #26P729 #28P1172 #29P1078 #30P1112 T200"));
        state_isComboAUp = false;
        state_nextStep = 0;
        kakiNapak = true;
        break;
    }
  }

  void ssc_forward_sync () {
    com.println(F("#4P1733 #5P1947 #6P1973 #8P1175 #9P2695 #10P2340 #12P1440 #13P1945 #14P2172 #20P1575 #21P704 #22P801 #24P1195 #25P1393 #26P729 #28P1344 #29P666 #30P799 T200")); delay(200);
    com.println(F("#4P1733 #5P1947 #6P1973 #8P1175 #9P2261 #10P2069 #12P1440 #13P1945 #14P2172 #20P1575 #21P1112 #22P1050 #24P1195 #25P1393 #26P729 #28P1344 #29P1078 #30P1020 T200")); delay(200);
    com.println(F("#4P1482 #5P2356 #6P2089 #8P1425 #9P2261 #10P2069 #12P1201 #13P2377 #14P2564 #20P1371 #21P1113 #22P923 #24P1405 #25P922 #26P462 #28P1172 #29P1078 #30P1112 T200")); delay(200);
    com.println(F("#4P1482 #5P1948 #6P1853 #8P1425 #9P2261 #10P2069 #12P1201 #13P1945 #14P2288 #20P1371 #21P1113 #22P923 #24P1405 #25P1393 #26P729 #28P1172 #29P1078 #30P1112 T200")); delay(200);
  }

  void ssc_backward () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1482 #5P1948 #6P1853 #8P1425 #9P2695 #10P2340 #12P1201 #13P1945 #14P2288 #20P1371 #21P604 #22P620 #24P1405 #25P1393 #26P729 #28P1172 #29P747 #30P930 T200"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1482 #5P1948 #6P1853 #8P1425 #9P2261 #10P2069 #12P1201 #13P1945 #14P2288 #20P1371 #21P1113 #22P923 #24P1405 #25P1393 #26P729 #28P1172 #29P1078 #30P1112 T200"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#4P1733 #5P2456 #6P2261 #8P1175 #9P2261 #10P2069 #12P1440 #13P2291 #14P2399 #20P1575 #21P1112 #22P1050 #24P1195 #25P922 #26P462 #28P1344 #29P1078 #30P1020 T200"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#4P1733 #5P1947 #6P1973 #8P1175 #9P2261 #10P2069 #12P1440 #13P1945 #14P2172 #20P1575 #21P1112 #22P1050 #24P1195 #25P1393 #26P729 #28P1344 #29P1078 #30P1020 T200"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

  void ssc_backward_sync () {
    com.println(F("#4P1482 #5P1948 #6P1853 #8P1425 #9P2695 #10P2340 #12P1201 #13P1945 #14P2288 #20P1371 #21P604 #22P620 #24P1405 #25P1393 #26P729 #28P1172 #29P747 #30P930 T200")); delay(200);
    com.println(F("#4P1482 #5P1948 #6P1853 #8P1425 #9P2261 #10P2069 #12P1201 #13P1945 #14P2288 #20P1371 #21P1113 #22P923 #24P1405 #25P1393 #26P729 #28P1172 #29P1078 #30P1112 T200")); delay(200);
    com.println(F("#4P1733 #5P2456 #6P2261 #8P1175 #9P2261 #10P2069 #12P1440 #13P2291 #14P2399 #20P1575 #21P1112 #22P1050 #24P1195 #25P922 #26P462 #28P1344 #29P1078 #30P1020 T200")); delay(200);
    com.println(F("#4P1733 #5P1947 #6P1973 #8P1175 #9P2261 #10P2069 #12P1440 #13P1945 #14P2172 #20P1575 #21P1112 #22P1050 #24P1195 #25P1393 #26P729 #28P1344 #29P1078 #30P1020 T200")); delay(200);
  }

  void ssc_shiftRight () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1684 #5P1933 #6P1783 #8P1300 #9P2756 #10P2457 #12P1249 #13P1933 #14P2104 #20P1412 #21P756 #22P893 #24P1300 #25P1418 #26P663 #28P1310 #29P789 #30P998 T200"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1684 #5P1933 #6P1783 #8P1300 #9P2238 #10P2135 #12P1249 #13P1933 #14P2104 #20P1412 #21P1127 #22P1125 #24P1300 #25P1418 #26P663 #28P1310 #29P1090 #30P1166 T200"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#4P1530 #5P2462 #6P2270 #8P1300 #9P2252 #10P1929 #12P1394 #13P2382 #14P2573 #20P1535 #21P1115 #22P917 #24P1300 #25P1031 #26P648 #28P1205 #29P1080 #30P1015 T200"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#4P1530 #5P1945 #6P1979 #8P1300 #9P2252 #10P1929 #12P1394 #13P1943 #14P2294 #20P1535 #21P1115 #22P917 #24P1300 #25P1402 #26P866 #28P1205 #29P1080 #30P1015 T200"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

  void ssc_shiftLeft () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1530 #5P1945 #6P1979 #8P1300 #9P2594 #10P2151 #12P1394 #13P1943 #14P2294 #20P1535 #21P598 #22P609 #24P1300 #25P1402 #26P866 #28P1205 #29P661 #30P791 T200"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1530 #5P1945 #6P1979 #8P1300 #9P2252 #10P1929 #12P1394 #13P1943 #14P2294 #20P1535 #21P1115 #22P917 #24P1300 #25P1402 #26P866 #28P1205 #29P1080 #30P1015 T200"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#4P1684 #5P2304 #6P2002 #8P1300 #9P2238 #10P2135 #12P1249 #13P2248 #14P2316 #20P1412 #21P1127 #22P1125 #24P1300 #25P855 #26P348 #28P1310 #29P1090 #30P1166 T200"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#4P1684 #5P1933 #6P1783 #8P1300 #9P2238 #10P2135 #12P1249 #13P1933 #14P2104 #20P1412 #21P1127 #22P1125 #24P1300 #25P1418 #26P663 #28P1310 #29P1090 #30P1166 T200"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

  void ssc_shiftLeftHigher () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1530 #5P1790 #6P1860 #8P1300 #9P2821 #10P2250 #12P1394 #13P1811 #14P2179 #20P1535 #21P66 #22P392 #24P1300 #25P1537 #26P969 #28P1205 #29P229 #30P633 T240"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1530 #5P1790 #6P1860 #8P1300 #9P2128 #10P1824 #12P1394 #13P1811 #14P2179 #20P1535 #21P1270 #22P1043 #24P1300 #25P1537 #26P969 #28P1205 #29P1206 #30P1107 T240"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#4P1684 #5P2543 #6P2098 #8P1300 #9P2097 #10P2013 #12P1249 #13P2451 #14P2408 #20P1412 #21P1265 #22P1237 #24P1300 #25PNaN #26PNaN #28P1310 #29P1202 #30P1248 T240"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#4P1684 #5P1795 #6P1677 #8P1300 #9P2097 #10P2013 #12P1249 #13P1816 #14P2002 #20P1412 #21P1265 #22P1237 #24P1300 #25P1571 #26P783 #28P1310 #29P1202 #30P1248 T240"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

  void ssc_rotateCW () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1786 #5P1951 #6P1872 #8P1175 #9P2592 #10P2287 #12P1539 #13P1950 #14P2249 #20P1328 #21P782 #22P821 #24P1405 #25P1393 #26P729 #28P1101 #29P782 #30P886 T200"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1786 #5P1951 #6P1872 #8P1175 #9P2261 #10P2069 #12P1539 #13P1950 #14P2249 #20P1328 #21P1109 #22P1030 #24P1405 #25P1393 #26P729 #28P1101 #29P1074 #30P1051 T200"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#4P1378 #5P2312 #6P2147 #8P1425 #9P2261 #10P2069 #12P1151 #13P2226 #14P2381 #20P1658 #21P1107 #22P966 #24P1195 #25P1033 #26P515 #28P1380 #29P1076 #30P1097 T200"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#4P1378 #5P1953 #6P1933 #8P1425 #9P2261 #10P2069 #12P1151 #13P1948 #14P2191 #20P1658 #21P1107 #22P966 #24P1195 #25P1393 #26P729 #28P1380 #29P1076 #30P1097 T200"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

  void ssc_rotateCW_sync () {
    com.println(F("#4P1786 #5P1951 #6P1872 #8P1175 #9P2592 #10P2287 #12P1539 #13P1950 #14P2249 #20P1328 #21P782 #22P821 #24P1405 #25P1393 #26P729 #28P1101 #29P782 #30P886 T200")); delay(200);
    com.println(F("#4P1786 #5P1951 #6P1872 #8P1175 #9P2261 #10P2069 #12P1539 #13P1950 #14P2249 #20P1328 #21P1109 #22P1030 #24P1405 #25P1393 #26P729 #28P1101 #29P1074 #30P1051 T200")); delay(200);
    com.println(F("#4P1378 #5P2312 #6P2147 #8P1425 #9P2261 #10P2069 #12P1151 #13P2226 #14P2381 #20P1658 #21P1107 #22P966 #24P1195 #25P1033 #26P515 #28P1380 #29P1076 #30P1097 T200")); delay(200);
    com.println(F("#4P1378 #5P1953 #6P1933 #8P1425 #9P2261 #10P2069 #12P1151 #13P1948 #14P2191 #20P1658 #21P1107 #22P966 #24P1195 #25P1393 #26P729 #28P1380 #29P1076 #30P1097 T200")); delay(200);
  }

  void ssc_rotateCCW () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1378 #5P1953 #6P1933 #8P1425 #9P2592 #10P2287 #12P1151 #13P1948 #14P2191 #20P1658 #21P748 #22P740 #24P1195 #25P1393 #26P729 #28P1380 #29P810 #30P945 T200"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1378 #5P1953 #6P1933 #8P1425 #9P2261 #10P2069 #12P1151 #13P1948 #14P2191 #20P1658 #21P1107 #22P966 #24P1195 #25P1393 #26P729 #28P1380 #29P1076 #30P1097 T200"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#4P1786 #5P2278 #6P2070 #8P1175 #9P2261 #10P2069 #12P1539 #13P2254 #14P2455 #20P1328 #21P1109 #22P1030 #24P1405 #25P1033 #26P515 #28P1101 #29P1074 #30P1051 T200"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#4P1786 #5P1951 #6P1872 #8P1175 #9P2261 #10P2069 #12P1539 #13P1950 #14P2249 #20P1328 #21P1109 #22P1030 #24P1405 #25P1393 #26P729 #28P1101 #29P1074 #30P1051 T200"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

  void ssc_rotateCCW_sync () {
    com.println(F("#4P1378 #5P1953 #6P1933 #8P1425 #9P2592 #10P2287 #12P1151 #13P1948 #14P2191 #20P1658 #21P748 #22P740 #24P1195 #25P1393 #26P729 #28P1380 #29P810 #30P945 T200")); delay(200);
    com.println(F("#4P1378 #5P1953 #6P1933 #8P1425 #9P2261 #10P2069 #12P1151 #13P1948 #14P2191 #20P1658 #21P1107 #22P966 #24P1195 #25P1393 #26P729 #28P1380 #29P1076 #30P1097 T200")); delay(200);
    com.println(F("#4P1786 #5P2278 #6P2070 #8P1175 #9P2261 #10P2069 #12P1539 #13P2254 #14P2455 #20P1328 #21P1109 #22P1030 #24P1405 #25P1033 #26P515 #28P1101 #29P1074 #30P1051 T200")); delay(200);
    com.println(F("#4P1786 #5P1951 #6P1872 #8P1175 #9P2261 #10P2069 #12P1539 #13P1950 #14P2249 #20P1328 #21P1109 #22P1030 #24P1405 #25P1393 #26P729 #28P1101 #29P1074 #30P1051 T200")); delay(200);
  }

  void ssc_rotateCWLess () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1662 #5P1953 #6P1913 #8P1258 #9P2597 #10P2300 #12P1401 #13P1950 #14P2249 #20P1429 #21P759 #22P767 #24P1336 #25P1394 #26P719 #28P1199 #29P782 #30P886 T200"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1662 #5P1953 #6P1913 #8P1258 #9P2259 #10P2078 #12P1401 #13P1950 #14P2249 #20P1429 #21P1107 #22P987 #24P1336 #25P1394 #26P719 #28P1199 #29P1074 #30P1051 T200"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#4P1522 #5P2312 #6P2147 #8P1342 #9P2259 #10P2078 #12P1270 #13P2245 #14P2430 #20P1542 #21P1107 #22P966 #24P1264 #25P1028 #26P502 #28P1295 #29P1073 #30P1066 T200"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#4P1522 #5P1953 #6P1933 #8P1342 #9P2259 #10P2078 #12P1270 #13P1950 #14P2230 #20P1542 #21P1107 #22P966 #24P1264 #25P1394 #26P719 #28P1295 #29P1073 #30P1066 T200"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

  void ssc_rotateCCWLess () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1522 #5P1953 #6P1933 #8P1342 #9P2597 #10P2300 #12P1270 #13P1950 #14P2230 #20P1542 #21P748 #22P740 #24P1264 #25P1394 #26P719 #28P1295 #29P791 #30P906 T200"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1522 #5P1953 #6P1933 #8P1342 #9P2259 #10P2078 #12P1270 #13P1950 #14P2230 #20P1542 #21P1107 #22P966 #24P1264 #25P1394 #26P719 #28P1295 #29P1073 #30P1066 T200"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#4P1662 #5P2301 #6P2121 #8P1258 #9P2259 #10P2078 #12P1401 #13P2254 #14P2455 #20P1429 #21P1107 #22P987 #24P1336 #25P1028 #26P502 #28P1199 #29P1074 #30P1051 T200"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#4P1662 #5P1953 #6P1913 #8P1258 #9P2259 #10P2078 #12P1401 #13P1950 #14P2249 #20P1429 #21P1107 #22P987 #24P1336 #25P1394 #26P719 #28P1199 #29P1074 #30P1051 T200"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

  void ssc_turnRight () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1733 #5P1947 #6P1973 #8P1175 #9P2592 #10P2287 #12P1440 #13P1945 #14P2172 #20P1575 #21P793 #22P846 #24P1195 #25P1393 #26P729 #28P1344 #29P765 #30P843 T200"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1733 #5P1947 #6P1973 #8P1175 #9P2261 #10P2069 #12P1440 #13P1945 #14P2172 #20P1575 #21P1112 #22P1050 #24P1195 #25P1393 #26P729 #28P1344 #29P1078 #30P1020 T200"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#4P1378 #5P2312 #6P2147 #8P1425 #9P2261 #10P2069 #12P1151 #13P2226 #14P2381 #20P1658 #21P1107 #22P966 #24P1195 #25P1033 #26P515 #28P1380 #29P1076 #30P1097 T200"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#4P1378 #5P1953 #6P1933 #8P1425 #9P2261 #10P2069 #12P1151 #13P1948 #14P2191 #20P1658 #21P1107 #22P966 #24P1195 #25P1393 #26P729 #28P1380 #29P1076 #30P1097 T200"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

  void ssc_turnLeft () {
    switch (state_nextStep) {
      case 0:
        com.println(F("#4P1733 #5P1947 #6P1973 #8P1175 #9P2592 #10P2287 #12P1440 #13P1945 #14P2172 #20P1575 #21P793 #22P846 #24P1195 #25P1393 #26P729 #28P1344 #29P765 #30P843 T200"));
        state_isComboBUp = true;
        state_nextStep = 1;
        break;
      case 1:
        com.println(F("#4P1733 #5P1947 #6P1973 #8P1175 #9P2261 #10P2069 #12P1440 #13P1945 #14P2172 #20P1575 #21P1112 #22P1050 #24P1195 #25P1393 #26P729 #28P1344 #29P1078 #30P1020 T200"));
        state_isComboBUp = false;
        state_nextStep = 2;
        break;
      case 2:
        com.println(F("#4P1786 #5P2278 #6P2070 #8P1175 #9P2261 #10P2069 #12P1539 #13P2254 #14P2455 #20P1328 #21P1109 #22P1030 #24P1405 #25P1033 #26P515 #28P1101 #29P1074 #30P1051 T200"));
        state_isComboAUp = true;
        state_nextStep = 3;
        break;
      case 3:
        com.println(F("#4P1786 #5P1951 #6P1872 #8P1175 #9P2261 #10P2069 #12P1539 #13P1950 #14P2249 #20P1328 #21P1109 #22P1030 #24P1405 #25P1393 #26P729 #28P1101 #29P1074 #30P1051 T200"));
        state_isComboAUp = false;
        state_nextStep = 0;
        break;
    }
  }

  // END OF GENERATED

  
void move (MoveType id) {
  if (millis() - state_lastMoveRecord > 199) {
    state_lastMoveRecord = millis();

    if (state_currentMove != NORMALIZE || (state_currentMove == NORMALIZE && (state_isComboAUp || state_isComboBUp))) {
      isNormalized = false;
    }

    if (state_currentMove != STANDBY) {
      isStandby = false;
    }

    if (state_step2keep > 0) {
      state_step2keep = state_step2keep - 1;
    } else {
      state_currentMove = id;
    }

    switch (state_currentMove) {
      case STANDBY:
        ssc_standby();
        break;
      case NORMALIZE:
        ssc_normalize();
        break;
      case FORWARD:
        ssc_forward();
        break;
      case FORWARD_LOW:
        ssc_forward_low();
        break;
      case FORWARD_HIGHER:
        ssc_forward_higher();
        break;
      case CAPIT_TURUN:
        ssc_capitTurun();
        break;
      case CAPIT_LEPAS:
        ssc_capitLepas();
        break;
      case BACKWARD:
        ssc_backward();
        break;
      case SHIFT_RIGHT:
        ssc_shiftRight();
        break;
      case SHIFT_LEFT:
        ssc_shiftLeft();
        break;
      case SHIFT_LEFTHIGHER:
        ssc_shiftLeftHigher();
        break;
      case ROTATE_CW:
        ssc_rotateCW();
        break;
      case ROTATE_CCW:
        ssc_rotateCCW();
        break;
      case ROTATE_CW_LESS:
        ssc_rotateCWLess();
        break;
      case ROTATE_CCW_LESS:
        ssc_rotateCCWLess();
        break;
      case TURN_RIGHT:
        ssc_turnRight();
        break;
      case TURN_LEFT:
        ssc_turnLeft();
        break;
    }
  }
}

void moveANDI (MoveType id) {
  if ((millis() - state_lastMoveRecord > 199) && (kakiNapak == true)) {
    state_lastMoveRecord = millis();

    if (state_currentMove != NORMALIZE || (state_currentMove == NORMALIZE && (state_isComboAUp || state_isComboBUp))) {
      isNormalized = false;
    }

    if (state_currentMove != STANDBY) {
      isStandby = false;
    }

    if (state_step2keep > 0) {
      state_step2keep = state_step2keep - 1;
    } else {
      state_currentMove = id;
    }

    switch (state_currentMove) {
      case STANDBY:
        ssc_standby();
        break;
      case NORMALIZE:
        ssc_normalize();
        break;
      case FORWARD:
        ssc_forward();
        break;
    }
  }//
  if ((millis() - state_lastMoveRecord > 149) && (kakiNapak == false)) {
    state_lastMoveRecord = millis();

    if (state_currentMove != NORMALIZE || (state_currentMove == NORMALIZE && (state_isComboAUp || state_isComboBUp))) {
      isNormalized = false;
    }

    if (state_currentMove != STANDBY) {
      isStandby = false;
    }

    if (state_step2keep > 0) {
      state_step2keep = state_step2keep - 1;
    } else {
      state_currentMove = id;
    }

    switch (state_currentMove) {
      case STANDBY:
        ssc_standby();
        break;
      case NORMALIZE:
        ssc_normalize();
        break;
      case FORWARD:
        ssc_forward();
        break;
    }
  }
}

void keep (int num) {
  if (state_step2keep < 1) {
    state_step2keep = num;
  }
}

void force () {
  state_step2keep = 0;
}

void standby () {
  move(STANDBY);
  if (state_currentMove == STANDBY) isStandby = true;
}

void normalize () {
  if (state_currentMove != NORMALIZE) {
    if (state_isComboAUp) {
      state_nextStep = 1;
    } else if (state_isComboBUp) {
      state_nextStep = 3;
    }
  }

  move(NORMALIZE);

  if (state_currentMove == NORMALIZE && !state_isComboAUp && !state_isComboBUp) {
    isNormalized = true;
  }
}

void forward (bool low = false) {
  if (low) move(FORWARD_LOW);
  else moveANDI(FORWARD);
}

void forwardHigher () {
  move(FORWARD_HIGHER);
}
// ========================== Capit ==========================
void capitTurun () {
  move(CAPIT_TURUN);
}
void capitLepas () {
  move(CAPIT_LEPAS);
}
// ========================== Capit ==========================

void backward () {
  move(BACKWARD);
}

void shiftRight () {
  move(SHIFT_RIGHT);
}

void shiftLeft () {
  move(SHIFT_LEFT);
}

void shiftLeftHigher () {
  move(SHIFT_LEFTHIGHER);
}

void rotateCW (unsigned int keep = 0) {
  if (keep > 0) {
    unsigned int startCounter = millis();
    unsigned int currentCounter = millis();
    while ((currentCounter - startCounter) < keep) {
      move(ROTATE_CW);
      currentCounter = millis();
    }
  } else {
    move(ROTATE_CW);
  }
}

void rotateCCW (unsigned int keep = 0) {
  if (keep > 0) {
    unsigned int startCounter = millis();
    unsigned int currentCounter = millis();
    while ((currentCounter - startCounter) < keep) {
      move(ROTATE_CCW);
      currentCounter = millis();
    }
  } else {
    move(ROTATE_CCW);
  }
}

void rotateCWLess () {
  move(ROTATE_CW_LESS);
}

void rotateCCWLess () {
  move(ROTATE_CCW_LESS);
}

void turnRight () {
  move(TURN_RIGHT);
}

void turnLeft () {
  move(TURN_LEFT);
}
}
