#include "Arduino.h"

#include "BTS7960B.h"


BTS7960B::BTS7960B()
{
	memset(cur, 0, 2*sizeof(cur[0]));
	memset(cur_cnt, 0, 2*sizeof(cur_cnt[0]));
	memset(cur_sum, 0, 2*sizeof(cur_sum[0]));

	pinMode(ENABLE_PIN, OUTPUT);

	/* MOTOR DX */
	pinMode(CUR_MOTOR_DX_PIN, INPUT);

	pinMode(PWM_MOTOR_DX_PIN, OUTPUT);
	analogWrite(PWM_MOTOR_DX_PIN, 0);

	pinMode(DIR_MOTOR_DX_PIN, OUTPUT);
	digitalWrite(DIR_MOTOR_DX_PIN, LOW);
	/* MOTOR DX */

	/* MOTOR SX */
	pinMode(CUR_MOTOR_SX_PIN, INPUT);

	pinMode(PWM_MOTOR_SX_PIN, OUTPUT);
	analogWrite(PWM_MOTOR_SX_PIN, 0);

	pinMode(DIR_MOTOR_SX_PIN, OUTPUT);
	digitalWrite(DIR_MOTOR_SX_PIN, LOW);
	/* MOTOR SX */
}

void BTS7960B::enable()
{
	digitalWrite(ENABLE_PIN, HIGH);
	Serial.println("BTS7960B::enable()");
}

void BTS7960B::disable()
{
	digitalWrite(ENABLE_PIN, LOW);
	Serial.println("BTS7960B::disable()");
}

bool BTS7960B::write(int motor, int speed)
{
	speed = (speed>255)?255:(speed<-255)?-255:speed;

	int pwm_pin = -1;
	int dir_pin = -1;

	switch(motor)
	{
		case MOTOR_DX:
		{
			pwm_pin = PWM_MOTOR_DX_PIN;
			dir_pin = DIR_MOTOR_DX_PIN;
			break;
		}
		case MOTOR_SX:
		{
			pwm_pin = PWM_MOTOR_SX_PIN;
			dir_pin = DIR_MOTOR_SX_PIN;
			break;
		}
	}
	if (pwm_pin == -1 || dir_pin == -1)
		return false;

	if (speed >= 0)
	{
		analogWrite(pwm_pin, 255-abs(speed));
		digitalWrite(dir_pin, HIGH);
	}
	else
	{
		analogWrite(pwm_pin, abs(speed));
		digitalWrite(dir_pin, LOW);
	}
	Serial.print("BTS7960B::write() -> motor:"); Serial.print((motor==MOTOR_SX)?"MOTOR_SX":"MOTOR_DX"); Serial.print(" speed:"); Serial.println(abs(speed));
	return true;
}

int BTS7960B::read(int motor)
{
	switch(motor)
	{
		case MOTOR_DX:
		{
			Serial.print("BTS7960B::read() -> motor: MOTOR_DX "); Serial.print("curr:"); Serial.println(cur[MOTOR_DX]);
			return cur[MOTOR_DX];
		}
		case MOTOR_SX:
		{
			Serial.print("BTS7960B::read() -> motor: MOTOR_SX "); Serial.print("curr:"); Serial.println(cur[MOTOR_SX]);
			return cur[MOTOR_SX];
		}
	}
	return -1;
}

void BTS7960B::update()
{
	cur_sum[MOTOR_DX] += analogRead(CUR_MOTOR_DX_PIN);
	cur_sum[MOTOR_SX] += analogRead(CUR_MOTOR_SX_PIN);
	if (cur_cnt[MOTOR_DX]++ > CUR_DX_LEN)
	{
		cur[MOTOR_DX] = cur_sum[MOTOR_DX]/cur_cnt[MOTOR_DX];
		cur_sum[MOTOR_DX] = cur_cnt[MOTOR_DX] = 0;
	}
	if (cur_cnt[MOTOR_SX]++ > CUR_SX_LEN)
	{
		cur[MOTOR_SX] = cur_sum[MOTOR_SX]/cur_cnt[MOTOR_SX];
		cur_sum[MOTOR_SX] = cur_cnt[MOTOR_SX] = 0;
	}
}
