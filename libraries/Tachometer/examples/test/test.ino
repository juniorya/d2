// управляем 4 пин вентилятором и измеряем обороты
#define PWM_PIN 10    // ШИМ пин (подключать через резик 100-1000 Ом)
#define TACH_PIN 2    // пин тахометра (желательна внешняя подтяжка 10к к VCC)

#include <Tachometer.h>
Tachometer tacho;

void setup() {
  Serial.begin(9600);
  pinMode(PWM_PIN, OUTPUT);

  // пин тахометра вентилятора подтягиваем к VCC
  pinMode(TACH_PIN, INPUT_PULLUP);

  // настраиваем прерывание
  attachInterrupt(0, isr, FALLING);

  // включаем вентиль на скорость 150 (из 255)
  analogWrite(PWM_PIN, 190);
  
  //tacho.setWindow(20);		// установка количества тиков для счёта времени (по умолч 10)
  //tacho.setTimeout(2000);	// таймаут прерываний (мс), после которого считается что вращение прекратилось
}

// обработчик прерывания
void isr() {
  tacho.tick();   // сообщаем библиотеке об этом
}

void loop() {
  // выводим несколько раз в секунду
  static uint32_t tmr;
  if (millis() - tmr > 100) {
    tmr = millis();
    Serial.println(tacho.getRPM());			// RPM
	//Serial.println(tacho.getHz());		// Hz
	//Serial.println(tacho.getUs());	// us
  }
}