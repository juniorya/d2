#define TACH_PIN 2    // пин тахометра (желательна внешняя подтяжка 10к к VCC)

#include <Tachometer.h>
Tachometer tacho;

#include <GyverUART.h>

#include <GyverOS.h>
GyverOS<3> OS;

#include <SPI.h>
#include <SD.h>
File myFile;

int long counter = 0;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  uart.begin();

  // put your setup code here, to run once:
  pinMode(TACH_PIN, INPUT_PULLUP);

  // настраиваем прерывание
  attachInterrupt(0, isr, FALLING);

  OS.attach(0, f1, 10);
  OS.attach(1, f2, 500);
}

void isr() {
  tacho.tick();   // сообщаем библиотеке об этом
  counter++;
}
  //Serial.println(tacho.getRPM());			// RPM
	//Serial.println(tacho.getHz());		// Hz
void loop() {
  // put your main code here, to run repeatedly:
  OS.tick();
  //delay(OS.getLeft());
}

void f1() {
  // выводит свой период в порт
  uart.print(tacho.getUs());	// us
  uart.print(',');
  uart.println(counter);
}

void f2() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}