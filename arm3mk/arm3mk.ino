#include <GyverJoy.h>
#include <Stepper.h>
#include <Servo.h>

Stepper stepper1(100, 4, 6, 5, 7); // подключение моторов
Stepper stepper2(100, 0, 2, 1, 3);
Stepper stepper3(100, 8, 10, 9, 11);

GyverJoy jx1(A0);   // подключение осей стика
GyverJoy jy1(A1);
GyverJoy jy2(A2);
GyverJoy jx2(A3);

Servo servo; //  подключение сервомашинки
int angle = 90;

void setup() 
{
  jx1.invert(true);  // инвертировать
  jy1.invert(true); 
//jx2.invert(true);
//jy2.invert(true);
  
  jx1.calibrate();  // каллибровка
  jy1.calibrate();
  jx2.calibrate();
  jy2.calibrate();
  
  jx1.deadzone(30);  // мёртвая зона
  jy1.deadzone(30);
  jx2.deadzone(30);
  jy2.deadzone(30);
  
  jx1.exponent(GJ_CUBIC);  // экспонента для плавности
  jy1.exponent(GJ_CUBIC);
  jx2.exponent(GJ_CUBIC);
  jy2.exponent(GJ_CUBIC);

  stepper1.setSpeed(100); //  устанавливаем скорость моторов
  stepper2.setSpeed(100);
  stepper3.setSpeed(100);

  servo.attach(12);  // пин сервомашинки
  servo.write(90); // устанавливаем начальное положение машинки
}

void loop() 
{
  jx1.tick(); // опрос стика
  jy1.tick();
  jx2.tick();
  jy2.tick();
  
  int x1 = jx1.value();  // забераем значение стика
  int y1 = jy1.value();  
  int x2 = jx2.value();
  int y2 = jy2.value();
  
  int dir1 = x1 > 0 ? 1 : -1; // выбор направления движения мотора
  int dir2 = y1 > 0 ? 1 : -1; 
  int dir3 = x2 > 0 ? 1 : -1; 
  
  int steps1 = map(abs(x1), 0, 255, 0, 100); // перерасчет отклонения стика в количество шагов мотора
  int steps2 = map(abs(y1), 0, 255, 0, 100);
  int steps3 = map(abs(x2), 0, 255, 0, 100);
  
  angle += map(y2, -255, 255, -4, 4);
  angle = constrain(angle, 85, 160);
  servo.write(angle);
  
  for (int i = 0; i < steps1; i++)  // плавное движение мотора
  {
    stepper1.step(dir1);
  }

  for (int i = 0; i < steps2; i++)  
  {
    stepper2.step(dir2);
  }

  for (int i = 0; i < steps3; i++)  
  {
    stepper3.step(dir3);
  }
}
