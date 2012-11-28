/*
 * This file is part of CBCJVM.
 * CBCJVM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CBCJVM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CBCJVM.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "cbccore_low_Motor.h"
#include <cbc.h>
#include <stdio.h>

/*
 * cbccore_low_Motor JNI Wrapper Module
 * By: Braden McDorman
 * License: GNU GPLv3
 */

/*
 * Class:     Motor
 * Method:    motor
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Motor_motor(JNIEnv* env, jobject obj, jint port, jint speed)
{
#ifdef CBC
    motor(port, speed);
#else
    printf("Java_cbccore_low_Motor_motor stub\n");
#endif
}

/*
 * Class:     Motor
 * Method:    clear_motor_position_counter
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Motor_clear_1motor_1position_1counter(JNIEnv* env, jobject obj, jint port)
{
#ifdef CBC
    return clear_motor_position_counter(port);
#else
    printf("Java_cbccore_low_Motor_clear_1motor_1position_1counter stub\n");
    return -1;
#endif
}

/*
 * Class:     Motor
 * Method:    move_at_velocity
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Motor_move_1at_1velocity(JNIEnv* env, jobject obj, jint port, jint speed)
{
#ifdef CBC
    return move_at_velocity(port, speed);
#else
    printf("Java_cbccore_low_Motor_move_1at_1velocity stub\n");
    return -1;
#endif
}

/*
 * Class:     Motor
 * Method:    mav
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Motor_mav(JNIEnv* env, jobject obj, jint port, jint speed)
{
#ifdef CBC
    return mav(port, speed);
#else
    printf("Java_cbccore_low_Motor_mav stub\n");
    return -1;
#endif
}

/*
 * Class:     Motor
 * Method:    move_to_position
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Motor_move_1to_1position(JNIEnv* env, jobject obj, jint port, jint speed, jint delta)
{
#ifdef CBC
    return move_to_position(port, speed, delta);
#else
    printf("Java_cbccore_low_Motor_move_1to_1position stub\n");
    return -1;
#endif
}

/*
 * Class:     Motor
 * Method:    mtp
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Motor_mtp(JNIEnv* env, jobject obj, jint port, jint speed, jint delta)
{
#ifdef CBC
    return mtp(port, speed, delta);
#else
    printf("Java_cbccore_low_Motor_mtp stub\n");
    return -1;
#endif
}

/*
 * Class:     Motor
 * Method:    move_relative_position
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Motor_move_1relative_1position(JNIEnv* env, jobject obj, jint port, jint speed, jint delta)
{
#ifdef CBC
    return move_relative_position(port, speed, delta);
#else
    printf("Java_cbccore_low_Motor_move_1relative_1position stub\n");
    return -1;
#endif
}

/*
 * Class:     Motor
 * Method:    mrp
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Motor_mrp(JNIEnv* env, jobject obj, jint port, jint speed, jint delta)
{
#ifdef CBC
    return mrp(port, speed, delta);
#else
    printf("Java_cbccore_low_Motor_mrp stub\n");
    return -1;
#endif
}

/*
 * Class:     Motor
 * Method:    set_pid_gains
 * Signature: (IIIIIII)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Motor_set_1pid_1gains(JNIEnv* env, jobject obj, jint motor, jint p, jint i, jint d, jint pd, jint id, jint dd)
{
#ifdef CBC
    set_pid_gains(motor, p, i, d, pd, id, dd);
#else
    printf("Java_cbccore_low_Motor_set_1pid_1gains stub\n");
#endif
}

/*
 * Class:     Motor
 * Method:    freeze
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Motor_freeze(JNIEnv* env, jobject obj, jint motor)
{
#ifdef CBC
    return freeze(motor);
#else
    printf("Java_cbccore_low_Motor_freeze stub\n");
    return -1;
#endif
}

/*
 * Class:     Motor
 * Method:    get_motor_done
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Motor_get_1motor_1done(JNIEnv* env, jobject obj, jint motor)
{
#ifdef CBC
    return get_motor_done(motor);
#else
    printf("Java_cbccore_low_Motor_get_motor_done stub\n");
    return -1;
#endif
}

/*
 * Class:     Motor
 * Method:    get_motor_position_counter
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Motor_get_1motor_1position_1counter(JNIEnv* env, jobject obj, jint port)
{
#ifdef CBC
	get_motor_position_counter(port);
#else
	printf("Java_cbccore_low_Motor_enable_1servos stub\n");
	return -1;
#endif
}

/*
 * Class:     Motor
 * Method:    block_motor_done
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Motor_block_1motor_1done(JNIEnv* env, jobject obj, jint motor)
{
#ifdef CBC
    return block_motor_done(motor);
#else
    printf("Java_cbccore_low_Motor_block_motor_done stub\n");
#endif
}

/*
 * Class:     Motor
 * Method:    bmd
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Motor_bmd(JNIEnv* env, jobject obj, jint motor)
{
#ifdef CBC
    return bmd(motor);
#else
    printf("Java_cbccore_low_Motor_bmd stub\n");
#endif
}

/*
 * Class:     Motor
 * Method:    setpwm
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Motor_setpwm(JNIEnv* env, jobject obj, jint motor, jint pwm)
{
#ifdef CBC
    return setpwm(motor, pwm);
#else
    printf("Java_cbccore_low_Motor_setpwm stub\n");
    return -1;
#endif
}

/*
 * Class:     Motor
 * Method:    getpwm
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Motor_getpwm(JNIEnv* env, jobject obj, jint motor)
{
#ifdef CBC
    return getpwm(motor);
#else
    printf("Java_cbccore_low_Motor_getpwm stub\n");
    return -1;
#endif
}

/*
 * Class:     Motor
 * Method:    fd
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Motor_fd(JNIEnv* env, jobject obj, jint motor)
{
#ifdef CBC
    return fd(motor);
#else
    printf("Java_cbccore_low_Motor_fd stub\n");
#endif
}

/*
 * Class:     Motor
 * Method:    bk
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Motor_bk(JNIEnv* env, jobject obj, jint motor)
{
#ifdef CBC
    return bk(motor);
#else
    printf("Java_cbccore_low_Motor_bk stub\n");
#endif
}

/*
 * Class:     Motor
 * Method:    off
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Motor_off(JNIEnv* env, jobject obj, jint motor)
{
#ifdef CBC
    return off(motor);
#else
    printf("Java_cbccore_low_Motor_off stub\n");
#endif
}

/*
 * Class:     Motor
 * Method:    ao
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Motor_ao(JNIEnv* env, jobject obj)
{
#ifdef CBC
    return ao();
#else
    printf("Java_cbccore_low_Motor_ao stub\n");
#endif
}

