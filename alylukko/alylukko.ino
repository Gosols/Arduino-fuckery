#include <Key.h>
#include <Keypad.h>

const byte numRows = 4;
const byte numCols = 4;

int servoPin = 10;

int ledPin = 13;

char keymap[numRows][numCols] =
{
  {'1', '2', '3','A'},
  {'4', '5', '6','B'},
  {'7', '8', '9','C'},
  {'*', '0', '#','D'}
};

byte rowPins[numRows] = {2, 3, 4, 5};
byte colPins[numCols] = {6, 7, 8, 9};

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

int pincode[] = {0, 0, 0, 0};  //OIKEA NÄPPÄIMISTÖN KOODI
bool pincodeIsCorrect = false; //ONKO KOODI OIKEIN...
int correct = 0;
bool checkIfLockIsOpen = false;
char key;

void setup()
{
  // put your setup code here, to run once:
  //KOODI JOLLA ALUSTETAAN ARDUINO (KOMPONENTIT YMS)
    pinMode(servoPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}

void correctCode() 	//JOS KOODI OIKEIN NIIN SUORITETAAN TÄMÄ KOODI JOSSA LED PÄÄLLÄ 5 SEKUNTIA
			//JA SERVO PYÖRII 90 ASTETTA ELI "LUKKO" AVAUTUU
{
    digitalWrite(ledPin, HIGH);
    delay(5000);
    digitalWrite(ledPin, LOW);
    
  	for (int i = 0; i<30; i++)
    {
    
    digitalWrite(servoPin, HIGH);
    delay(500);
    digitalWrite(servoPin, LOW);
    delay(20);
    }
}

void incorrectCode()
{
  //JOS KOODI ON VÄÄRÄ, SUORITETAAN TÄMÄ KOODI JOSSA LED VÄLKKYY PUOLEN SEKUNNIN INTERVALLILLA 5 KERTAA
    for (int e = 0; e<5; e++)
    {
    
	digitalWrite(13, HIGH);
	delay(500);
  	digitalWrite(13, LOW);
  	delay(500);
    }
}

void loop() //PÄÄKOODI
{
  //jos lukko on auki, odota sen sulkemista ennen jatkamista...

  for (int i = 0; i < 4; i++)
  {
    
    char key = myKeypad.waitForKey(); //SYÖTÄ...
    Serial.println(key);
    int keyInt = key - '0';       //MUUTETAAN NUMEROKSI...
    if (pincode[i] == keyInt)     //JOS SYÖTETTY YKSITTÄINEN KOODINUMERO ON OIKEIN...
    {
      correct++;
    }
  }

  if (correct == 4)
  { //JOS KOODI ON OIKEIN...
    //TÄHÄN KOODI JOKA SUORITETAAN, KUN KOODI ON OIKEA...
      correctCode();
  } else {
      incorrectCode();
  }
}
