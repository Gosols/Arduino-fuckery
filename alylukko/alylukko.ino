#include <Key.h>
#include <Keypad.h>

const byte numRows = 4;
<<<<<<< Updated upstream
const byte numCols = 4;

char keymap[numRows][numCols] =
{
  {'1', '2', '3','A'},
  {'4', '5', '6','B'},
  {'7', '8', '9','C'},
  {'*', '0', '#','D'}
=======
const byte numCols = 3;

int servoPin = 10;

int ledPinRed = 13;
int ledPinGreen = 9;
int ledPinYellow = 10;

char keymap[numRows][numCols] =
{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
>>>>>>> Stashed changes
};

byte rowPins[numRows] = {2, 3, 4, 5};
byte colPins[numCols] = {6, 7, 8, 9};

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

<<<<<<< Updated upstream
int pincode[] = {0, 0, 0, 0};  //OIKEA NÄPPÄIMISTÖN KOODI
=======
int pincode[] = {1, 2, 3, 4, 5, 6};  //OIKEA NÄPPÄIMISTÖN KOODI
int montaPitaaArvataOikein = 4; //KOODIN PITUUS (LÄHTÖKOHTAISESTI 4, MAKSIMISSAAN 6)
>>>>>>> Stashed changes
bool pincodeIsCorrect = false; //ONKO KOODI OIKEIN...
int correct = 0;
bool checkIfLockIsOpen = false;
char key;

void setup()
{
  // put your setup code here, to run once:
  //KOODI JOLLA ALUSTETAAN ARDUINO (KOMPONENTIT YMS)
  Serial.begin(9600);
<<<<<<< Updated upstream
=======
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
>>>>>>> Stashed changes
}

void correctCode()
{
<<<<<<< Updated upstream
    //JOS KOODI OIKEIN; SUORITETAAN TÄMÄ
    //PITÄÄ LEDIN PÄÄLLÄ 5 SEKUNTIA
    digitalWrite(13, HIGH);
    delay(5000);
    digitalWrite(13, LOW);
=======
  //JOS KOODI OIKEIN SUORITETAAN TÄMÄ
  Serial.println();
  Serial.println("Koodi oikein! :)");

  //PITÄÄ LEDIN PÄÄLLÄ 5 SEKUNTIA
  digitalWrite(ledPinGreen, HIGH);
  delay(5000);
  digitalWrite(ledPinGreen, LOW);
>>>>>>> Stashed changes
}

void incorrectCode()
{
  //JOS KOODI ON VÄÄRÄ, SUORITETAAN TÄMÄ KOODI
<<<<<<< Updated upstream
  //VILKUTTAA LEDIÄ 5 KERTAA PUOLEN SEKUNNIN AJAN PUOLEN SEKUNNIN VÄLEIN
    for (int e = 0; e<5; e++)
    {
    
	digitalWrite(13, HIGH);
	delay(500);
  	digitalWrite(13, LOW);
  	delay(500);
    }
=======
  Serial.println();
  Serial.println("Koodi väärin! :(");

  //VILKUTTAA LEDIÄ "e" KERTAA PUOLEN SEKUNNIN AJAN PUOLEN SEKUNNIN VÄLEIN

  for (int e = 0; e < 10; e++) {

    digitalWrite(ledPinRed, HIGH);
    delay(100);
    digitalWrite(ledPinRed, LOW);
    delay(100);
  }

  if (montaPitaaArvataOikein < 6) { //JOS SALASANAA VOI VIELÄ VAIKEUTTAA, VAIKEUTA SAATANA
    Serial.println("Koodi vaikeutuu HÄHÄHÄHÄ");

  for (int e = 0; e < 10; e++) {

    digitalWrite(ledPinYellow, HIGH);
    delay(100);
    digitalWrite(ledPinYellow, LOW);
    delay(100);

  }
    
    montaPitaaArvataOikein++;

  }

  addIncorrect();
}

void resetCorrect()
{
  correct = 0;
}

void addCorrect()
{
  correct++;
}

void addIncorrect() {
  vaaratArvaukset++;
>>>>>>> Stashed changes
}

void loop() //PÄÄKOODI
{
  //jos lukko on auki, odota sen sulkemista ennen jatkamista...
<<<<<<< Updated upstream

  for (int i = 0; i < 4; i++)
=======
  Serial.print("Koodi on ");
  Serial.print(montaPitaaArvataOikein);
  Serial.println("-numeroinen - vääristä arvauksista koodi vaikeutuu!");

  Serial.print("Anna koodi: ");
  for (int i = 0; i < montaPitaaArvataOikein; i++)
>>>>>>> Stashed changes
  {
    
    char key = myKeypad.waitForKey(); //SYÖTÄ...
<<<<<<< Updated upstream
    Serial.println(key);
    int keyInt = key - '0';       //MUUTETAAN NUMEROKSI...
    if (pincode[i] == keyInt)     //JOS SYÖTETTY YKSITTÄINEN KOODINUMERO ON OIKEIN...
    {
      correct++;
=======
    int keyInt = key - '0';       //MUUTETAAN NUMEROKSI...
    Serial.print(keyInt);
    if (pincode[i] == keyInt)     //JOS SYÖTETTY YKSITTÄINEN KOODINUMERO ON OIKEIN...
    {
      addCorrect();
>>>>>>> Stashed changes
    }
  }

  if (correct == 4)
  { //JOS KOODI ON OIKEIN...
    //TÄHÄN KOODI JOKA SUORITETAAN, KUN KOODI ON OIKEA...
<<<<<<< Updated upstream
      correctCode();
  } else {
      incorrectCode();
=======

    correctCode();

    tone(buzzer, 900); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec
    resetCorrect();

  } else
  {
    incorrectCode();

    tone(buzzer, 2000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec
    resetCorrect();
>>>>>>> Stashed changes
  }
}
