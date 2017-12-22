#ifndef BTS7960B_H
#define BTS7960B_H

#define CUR_LEN 100

#define MOTOR_SX 0
#define MOTOR_DX 1
#define MAX_MOTORS 2

#define ENABLE_PIN 0 //8

#define PWM_MOTOR_DX_PIN 20 //5
#define DIR_MOTOR_DX_PIN 18 //4
#define CUR_MOTOR_DX_PIN 0 //A1

#define PWM_MOTOR_SX_PIN 21 //6
#define DIR_MOTOR_SX_PIN 48 //7
#define CUR_MOTOR_SX_PIN 0 //A2

class Motor {
public:
  Motor(int cur_pin, int pwm_pin, int dir_pin);

  void setSpeed(int speed);
  int speed() const;

  void updateCurrent();
  int current() const;

private:
  int cur_pin;
  int pwm_pin;
  int dir_pin;

  int spd;
  unsigned long cur;
  unsigned long cur_cnt;
  unsigned long cur_sum;
};

class BTS7960B {
public:
  BTS7960B();

  void setEnabled(bool enabled);
  bool isEnabled() const;

  void setSpeed(int motor, int speed);
  int speed(int motor) const;

  void update();
  int current(int motor) const;

private:
  bool enabled;
  struct Motor motors[MAX_MOTORS];
};

#endif
