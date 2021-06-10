#define TACH_PIN 2    // пин тахометра (желательна внешняя подтяжка 10к к VCC)

#include <Tachometer.h>
Tachometer tacho;

#include <GyverUART.h>

#include <GyverOS.h>
GyverOS<3> OS;

#include <EEPROM.h>

int long counter = 0;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(10, 0);
  uart.begin();

  // put your setup code here, to run once:
  pinMode(TACH_PIN, INPUT_PULLUP);

  // настраиваем прерывание
  attachInterrupt(0, isr, CHANGE);

  OS.attach(0, f1, 10);
  OS.attach(1, f2, 500);
  OS.attach(2, f3, 1000);
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

void f3() {
  digitalWrite(10,!digitalRead(10));
}

/*
0. Чтение EEPROM, если пусто, то ожидание меню.
1. Если доступен UART открыть меню
2. Меню - время измерения, задержка запуска счетчика, генератор 1Гц-10кГц, колличество импульсов, ip адрес, сохранить/отменить сохранение в eeprom
3. Запись на SDCARD если файл есть создать новый +1 
4. poll в Eth W5100 + log на SDCARD
5. Формат?
*/
struct{
  int timeC = 0;
  int delayS = 0;
  int freq = 0;
  int freqC = 0;
  byte ippart1 = 192;
  byte ippart2 = 192;
  byte ippart3 = 192;
  byte ippart4 = 192;
  //ip[] = { 192, 168, 1, 177 };  
} settings;