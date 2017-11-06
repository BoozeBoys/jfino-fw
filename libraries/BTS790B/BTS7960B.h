#ifndef BTS7960B_H
#define BTS7960B_H

#include "arduino.h"

#define CUR_LEN 100
#define CUR_DX_LEN CUR_LEN
#define CUR_SX_LEN CUR_LEN

#define MOTOR_SX 0
#define MOTOR_DX 1

#define ENABLE_PIN 8

#define PWM_MOTOR_DX_PIN 5
#define DIR_MOTOR_DX_PIN 4
#define CUR_MOTOR_DX_PIN A1

#define PWM_MOTOR_SX_PIN 6
#define DIR_MOTOR_SX_PIN 7
#define CUR_MOTOR_SX_PIN A2

class BTS7960B
{
	public:
		BTS7960B();

		void enable();
		void disable();

		bool write(int motor, int speed);
		
		int read(int motor);
		
		void update();
		
	private:
		unsigned long cur[2];
		unsigned long cur_cnt[2];
		unsigned long cur_sum[2];
};

#endif
