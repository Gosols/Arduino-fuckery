#include <Servo.h>
#include <Key.h>
#include <Keypad.h>

Servo myServo;

const byte numRows = 4;
const byte numCols = 3;

int servoPin = 10; //PINNIPAIKKA SERVON OHJAUSTA VARTEN
int pos = 0; //MUUTTUJA SERVON SIJAINNILLE


int ledPinRed = 13; //PUNAISEN VALON PINNIPAIKKA
int ledPinGreen = 9;//VIHREÄN VALON PINNIPAIKKA

char keymap[numRows][numCols] =
{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[numRows] = {2, 3, 4, 5};
byte colPins[numCols] = {6, 7, 8};

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

int pincode[] = {1, 2, 3, 4, 5, 6};  //OIKEA NÄPPÄIMISTÖN KOODI
int montaPitaaArvataOikein = 4; //KOODIN PITUUS (LÄHTÖKOHTAISESTI 4, MAKSIMISSAAN 6)
bool pincodeIsCorrect = false; //ONKO KOODI OIKEIN...
int correct = 0; //OIKEIN ARVATUT YKSITTÄISET NROT
bool checkIfLockIsOpen = false; //TARKISTAA ONKO LUKKO AUKI
char key; //???

void setup()
{
  // put your setup code here, to run once:
  
  //KOODI JOLLA ALUSTETAAN ARDUINO (KOMPONENTIT YMS)
  Serial.begin(9600);
  //pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output

  //SERVO
  myServo.attach(servoPin);
}

void correctCode()
{
  //JOS KOODI OIKEIN SUORITETAAN TÄMÄ
  Serial.println();
  Serial.println("Koodi oikein! :)");

  //PITÄÄ LEDIN PÄÄLLÄ 3 SEKUNTIA
  digitalWrite(ledPinGreen, HIGH);
  delay(3000);
  digitalWrite(ledPinGreen, LOW);

  //LUKKO (SERVO) AUKEAA
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
}

void incorrectCode()
{
  //JOS KOODI ON VÄÄRÄ, SUORITETAAN TÄMÄ KOODI
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
    
    montaPitaaArvataOikein++;

  }
}

void resetCorrect()
{
  correct = 0;
}

void addCorrect()
{
  correct++;
}

void loop() //PÄÄKOODI
{
  //jos lukko on auki, odota sen sulkemista ennen jatkamista...
  Serial.print("Koodi on ");
  Serial.print(montaPitaaArvataOikein);
  Serial.println("-numeroinen - vääristä arvauksista koodi vaikeutuu!");

  Serial.print("Anna koodi: ");
  for (int i = 0; i < montaPitaaArvataOikein; i++)
  {
    char key = myKeypad.waitForKey(); //SYÖTÄ...
    int keyInt = key - '0';       //MUUTETAAN NUMEROKSI...
    Serial.print(keyInt);
    if (pincode[i] == keyInt)     //JOS SYÖTETTY YKSITTÄINEN KOODINUMERO ON OIKEIN...
    {
      addCorrect();
    }
  }

  if (correct == montaPitaaArvataOikein)
  { //JOS KOODI ON OIKEIN...
    //TÄHÄN KOODI JOKA SUORITETAAN, KUN KOODI ON OIKEA...

    correctCode();
    resetCorrect();

  } else
  {
    incorrectCode();
    resetCorrect();
  }
}
