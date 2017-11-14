#include "Arduino.h"

#include "BTS7960B.h"

Motor::Motor(int cur_pin, int pwm_pin, int dir_pin) {
  pinMode(cur_pin, INPUT);
  this->cur_pin = cur_pin;

  pinMode(pwm_pin, OUTPUT);
  analogWrite(pwm_pin, 0);
  this->pwm_pin = pwm_pin;

  pinMode(dir_pin, OUTPUT);
  digitalWrite(dir_pin, LOW);
  this->dir_pin = dir_pin;
}

void Motor::setSpeed(int speed) {
  speed = (speed > 255) ? 255 : (speed < -255) ? -255 : speed;

  if (speed >= 0) {
    analogWrite(this->pwm_pin, 255 - abs(speed));
    digitalWrite(this->dir_pin, HIGH);
  } else {
    analogWrite(this->pwm_pin, abs(speed));
    digitalWrite(this->dir_pin, LOW);
  }
  this->spd = speed;
}

int Motor::speed() const { return this->spd; }

void Motor::updateCurrent() {
  cur_sum += analogRead(this->cur_pin);

  if (cur_cnt++ > CUR_LEN) {
    cur = cur_sum / cur_cnt;
    cur_sum = cur_cnt = 0;
  }
}

int Motor::current() const { return this->cur; }

BTS7960B::BTS7960B()
    : motors{Motor(CUR_MOTOR_SX_PIN, PWM_MOTOR_SX_PIN, DIR_MOTOR_SX_PIN),
             Motor(CUR_MOTOR_DX_PIN, PWM_MOTOR_DX_PIN, DIR_MOTOR_DX_PIN)} {}

void BTS7960B::setEnabled(bool enabled) {
  digitalWrite(ENABLE_PIN, enabled);
  this->enabled = enabled;
}

bool BTS7960B::isEnabled() const { return this->enabled; }

void BTS7960B::setSpeed(int motor, int speed) {
  if (motor >= MAX_MOTORS) {
    return;
  }

  this->motors[motor].setSpeed(speed);
}

int BTS7960B::speed(int motor) const { return this->motors[motor].speed(); }

void BTS7960B::update() {
  for (int i = 0; i < MAX_MOTORS; i++) {
    this->motors[i].updateCurrent();
  }
}

int BTS7960B::current(int motor) const { return this->motors[motor].current(); }
