#include <Key.h>
#include <Keypad.h>


const byte numRows = 4; //NÄPPÄIMISTÖN RIVIEN MÄÄRÄ
const byte numCols = 3; //NÄPPÄIMISTÖN KOLUMNIEN MÄÄRÄ

int ledPinRed = 13; //PUNAISEN VALON PINNIPAIKKA
int ledPinGreen = 9;//VIHREÄN VALON PINNIPAIKKA

char keymap[numRows][numCols] = //LUODAAN NÄPPÄIMISTÖN "LAYOUTTI"
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
int correct = 0; //OIKEIN ARVATUT YKSITTÄISET NROT

void setup()
{
  //KOODI JOLLA ALUSTETAAN ARDUINO (KOMPONENTIT YMS)
  Serial.begin(9600);
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

//resetointi
void resetCode() {
  montaPitaaArvataOikein = 4;
  correct = 0;
}
