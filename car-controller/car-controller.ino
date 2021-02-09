// definice konstant
const int buttonPin = 7;    // tlacitko
const int ledPin = 3;      // ovladani signalizacni led - stav rele
const int enginePin = 13;  // ovldadani rele

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// promenne pro aktualni stav
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// vychozi nastaveni arduino uno
void setup() {
  // nastaveni serioveho portu
  Serial.begin(9600);
  Serial.println("setup");

  // otevreni pinu v danem modu
  pinMode(buttonPin, INPUT);    // vstup - tlacitko pro start/konec pohonu
  pinMode(ledPin, OUTPUT);      // indikace stavu pohonu
  pinMode(enginePin, OUTPUT);   // ovladani pohonu

  // nastaveni pinu do pozadovaneho pocatecniho stavu
  digitalWrite(ledPin, ledState);
  digitalWrite(enginePin, ledState);
}


// nekonecna smycka probihajici na arduino uno
void loop() {
  // precti stav tlacitka
  int reading = digitalRead(buttonPin);

  // otestuj, zda nastala zmena stavu signalu z tlacitka
  // + ignoruj noise
  if (reading != lastButtonState) {
    // reset referncniho casu - https://www.arduino.cc/reference/en/language/functions/time/millis/
    lastDebounceTime = millis();
  }

  // pokud rozdil aktualniho cas je vetsi nez limit
  if ((millis() - lastDebounceTime) > debounceDelay) {
     // a nastala zmena stavu
    if (reading != buttonState) {
      // uloz stav tlacitka
      buttonState = reading;

      // zmen stav signalizacni led
      if (buttonState == HIGH) {
        ledState = !ledState;
        Serial.println(ledState);
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);
  digitalWrite(enginePin, !ledState);
  
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
