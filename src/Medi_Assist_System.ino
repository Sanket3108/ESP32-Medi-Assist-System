#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

// --------------------------------------------------
// PIN DEFINITIONS
// --------------------------------------------------

const int touchPins[6] = {18, 19, 23, 4, 16, 17};

const int buzzerPin = 5;

const int redLED = 25;
const int greenLED = 26;


// --------------------------------------------------
// VIRTUAL TIME
// --------------------------------------------------

int hour = 7;
int minute = 0;

unsigned long previousMillis = 0;

// 1 real second = 1 virtual minute
const long interval = 1000;


// --------------------------------------------------
// MEDICINE STATUS
// --------------------------------------------------

bool medicineTaken[6] = {
  false,
  false,
  false,
  false,
  false,
  false
};

int previousSlot = -1;


// --------------------------------------------------
// SETUP
// --------------------------------------------------

void setup()
{
  Serial.begin(115200);

  SerialBT.begin("Medicine_Tracker");

  // Touch sensors
  for (int i = 0; i < 6; i++)
  {
    pinMode(touchPins[i], INPUT);
  }

  // Output pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  digitalWrite(buzzerPin, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);

  Serial.println();
  Serial.println("================================");
  Serial.println("     MEDI ASSIST SYSTEM");
  Serial.println("================================");

  SerialBT.println("================================");
  SerialBT.println("     MEDI ASSIST SYSTEM");
  SerialBT.println("================================");

  Serial.println("Virtual Time Started: 07:00 AM");
  SerialBT.println("Virtual Time Started: 07:00 AM");

  SerialBT.println("Bluetooth Monitoring Connected");
}


// --------------------------------------------------
// MAIN LOOP
// --------------------------------------------------

void loop()
{
  // ------------------------------------------------
  // UPDATE VIRTUAL TIME
  // ------------------------------------------------

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    minute++;

    if (minute >= 60)
    {
      minute = 0;
      hour++;

      if (hour >= 24)
      {
        hour = 0;
      }
    }
  }


  // ------------------------------------------------
  // DISPLAY CURRENT TIME
  // ------------------------------------------------

  Serial.print("Time: ");

  if (hour < 10)
    Serial.print("0");

  Serial.print(hour);
  Serial.print(":");

  if (minute < 10)
    Serial.print("0");

  Serial.println(minute);


  // ------------------------------------------------
  // GET ACTIVE MEDICINE SLOT
  // ------------------------------------------------

  int currentSlot = getCurrentSlot(hour, minute);


  // ------------------------------------------------
  // NEW MEDICINE SLOT STARTED
  // ------------------------------------------------

  if (currentSlot != previousSlot)
  {
    // Stop old alarm
    noTone(buzzerPin);
    digitalWrite(redLED, LOW);

    previousSlot = currentSlot;


    // New medicine slot
    if (currentSlot != -1)
    {
      medicineTaken[currentSlot] = false;

      digitalWrite(greenLED, LOW);

      sendMessage("");
      sendMessage("================================");
      sendMessage("       MEDICINE REMINDER");
      sendMessage("================================");

      sendMessage(getMedicineName(currentSlot));

      sendMessage("Please take the correct medicine.");

      sendMessage("Correct Box: " +
                  String(currentSlot + 1));

      sendMessage("================================");
    }
  }


  // ------------------------------------------------
  // ACTIVE MEDICINE
  // ------------------------------------------------

  if (currentSlot != -1)
  {
    // If medicine is not taken,
    // activate reminder alarm

    if (medicineTaken[currentSlot] == false)
    {
      digitalWrite(redLED, HIGH);

      tone(buzzerPin, 1000);
    }


    // ------------------------------------------------
    // CHECK ALL TOUCH SENSORS
    // ------------------------------------------------

    for (int i = 0; i < 6; i++)
    {
      int touchValue = digitalRead(touchPins[i]);


      if (touchValue == HIGH)
      {
        // --------------------------------------------
        // CORRECT MEDICINE
        // --------------------------------------------

        if (i == currentSlot)
        {
          medicineTaken[currentSlot] = true;

          noTone(buzzerPin);

          digitalWrite(redLED, LOW);

          // Green LED indication
          digitalWrite(greenLED, HIGH);

          sendMessage("");
          sendMessage("================================");
          sendMessage("       MEDICINE TAKEN");
          sendMessage("================================");

          sendMessage(
            "Correct: " +
            getMedicineName(currentSlot)
          );

          sendMessage("Status: SUCCESS");
          sendMessage("Buzzer: OFF");
          sendMessage("Red LED: OFF");
          sendMessage("Green LED: ON");

          sendMessage("================================");

          // Keep green LED ON for 3 seconds
          delay(3000);

          digitalWrite(greenLED, LOW);
        }


        // --------------------------------------------
        // WRONG MEDICINE
        // --------------------------------------------

        else
        {
          sendMessage("");
          sendMessage("⚠️ WARNING!");

          sendMessage(
            "Wrong Box Selected: Box " +
            String(i + 1)
          );

          sendMessage(
            "Correct Box: Box " +
            String(currentSlot + 1)
          );

          sendMessage("Medicine NOT taken.");

          // Red LED + buzzer
          digitalWrite(redLED, HIGH);

          tone(buzzerPin, 1500);

          delay(1000);

          noTone(buzzerPin);

          digitalWrite(redLED, LOW);

          // Small delay to prevent repeated detection
          delay(1000);
        }
      }
    }
  }


  // ------------------------------------------------
  // CHECK MISSED MEDICINES
  // ------------------------------------------------

  checkMissedMedicine(hour, minute);


  delay(100);
}


// ==================================================
// GET CURRENT MEDICINE SLOT
// ==================================================

int getCurrentSlot(int h, int m)
{
  int currentMinutes = h * 60 + m;


  // ----------------------------------------------
  // Medicine 1
  // 7:30 AM - 8:30 AM
  // ----------------------------------------------

  if (currentMinutes >= 450 &&
      currentMinutes < 510)
  {
    return 0;
  }


  // ----------------------------------------------
  // Medicine 2
  // 10:00 AM - 11:00 AM
  // ----------------------------------------------

  if (currentMinutes >= 600 &&
      currentMinutes < 660)
  {
    return 1;
  }


  // ----------------------------------------------
  // Medicine 3
  // 12:30 PM - 1:00 PM
  // ----------------------------------------------

  if (currentMinutes >= 750 &&
      currentMinutes < 780)
  {
    return 2;
  }


  // ----------------------------------------------
  // Medicine 4
  // 2:00 PM - 2:30 PM
  // ----------------------------------------------

  if (currentMinutes >= 840 &&
      currentMinutes < 870)
  {
    return 3;
  }


  // ----------------------------------------------
  // Medicine 5
  // 7:00 PM - 7:30 PM
  // ----------------------------------------------

  if (currentMinutes >= 1140 &&
      currentMinutes < 1170)
  {
    return 4;
  }


  // ----------------------------------------------
  // Medicine 6
  // 9:30 PM - 10:00 PM
  // ----------------------------------------------

  if (currentMinutes >= 1290 &&
      currentMinutes < 1320)
  {
    return 5;
  }


  return -1;
}


// ==================================================
// MEDICINE NAME
// ==================================================

String getMedicineName(int slot)
{
  switch (slot)
  {
    case 0:
      return "Medicine 1 - Before Breakfast";

    case 1:
      return "Medicine 2 - After Breakfast";

    case 2:
      return "Medicine 3 - Before Lunch";

    case 3:
      return "Medicine 4 - After Lunch";

    case 4:
      return "Medicine 5 - Before Dinner";

    case 5:
      return "Medicine 6 - After Dinner";
  }

  return "Unknown Medicine";
}


// ==================================================
// SEND MESSAGE TO SERIAL + BLUETOOTH
// ==================================================

void sendMessage(String message)
{
  Serial.println(message);

  SerialBT.println(message);
}


// ==================================================
// CHECK MISSED MEDICINE
// ==================================================

void checkMissedMedicine(int h, int m)
{
  int currentMinutes = h * 60 + m;


  // Medicine 1 missed
  if (currentMinutes == 510 &&
      medicineTaken[0] == false)
  {
    missedMessage(0);
  }


  // Medicine 2 missed
  if (currentMinutes == 660 &&
      medicineTaken[1] == false)
  {
    missedMessage(1);
  }


  // Medicine 3 missed
  if (currentMinutes == 780 &&
      medicineTaken[2] == false)
  {
    missedMessage(2);
  }


  // Medicine 4 missed
  if (currentMinutes == 870 &&
      medicineTaken[3] == false)
  {
    missedMessage(3);
  }


  // Medicine 5 missed
  if (currentMinutes == 1170 &&
      medicineTaken[4] == false)
  {
    missedMessage(4);
  }


  // Medicine 6 missed
  if (currentMinutes == 1320 &&
      medicineTaken[5] == false)
  {
    missedMessage(5);
  }
}


// ==================================================
// MISSED MEDICINE MESSAGE
// ==================================================

void missedMessage(int slot)
{
  noTone(buzzerPin);

  digitalWrite(redLED, LOW);

  sendMessage("");
  sendMessage("================================");
  sendMessage("       MEDICINE MISSED");
  sendMessage("================================");

  sendMessage(getMedicineName(slot));

  sendMessage("Status: NOT TAKEN");

  sendMessage("Time window expired.");

  sendMessage("================================");
}
