/* This file is part of CBCJVM.
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

#include "cbccore_low_Create.h"
#include <cbc.h>
#include <stdio.h>

/*
 * cbccore_low_Create JNI Wrapper Module
 * By: Tommy MacWilliam (Bugfixes by Benjamin Woodruff)
 * License: GNU GPLv3
 */

 /*
 * Class:     cbccore_low_Create
 * Method:    create_connect
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_create_1connect(JNIEnv *env, jobject obj)
{
#ifdef CBC
    return create_connect();
#else
   	printf("Java_cbccore_low_Create_create_1connect stub\n");
   	return -1;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_disconnect
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1disconnect(JNIEnv *env, jobject obj)
{
#ifdef CBC
    create_disconnect();
#else
    printf("Java_cbccore_low_Create_create_1disconnect stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1start(JNIEnv *env, jobject obj)
{
#ifdef CBC
    create_start();
#else
    printf("Java_cbccore_low_Create_create_1start stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_passive
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1passive(JNIEnv *env, jobject obj)
{
#ifdef CBC
    create_passive();
#else
    printf("Java_cbccore_low_Create_create_1passive stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_safe
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1safe(JNIEnv *env, jobject obj)
{
#ifdef CBC
    create_safe();
#else
    printf("Java_cbccore_low_Create_create_1safe stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_full
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1full(JNIEnv *env, jobject obj)
{
#ifdef CBC
    create_full();
#else
    printf("Java_cbccore_low_Create_create_1full stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_spot
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1spot(JNIEnv *env, jobject obj)
{
#ifdef CBC
    create_spot();
#else
    printf("Java_cbccore_low_Create_create_1spot stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_cover
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1cover(JNIEnv *env, jobject obj)
{
#ifdef CBC
    create_cover();
#else
    printf("Java_cbccore_low_Create_create_1cover stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_demo
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1demo(JNIEnv *env, jobject obj, jint d)
{
#ifdef CBC
    create_demo(d);
#else
    printf("Java_cbccore_low_Create_create_demo1 stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_cover_dock
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1cover_1dock(JNIEnv *env, jobject obj)
{
#ifdef CBC
    create_cover_dock();
#else
    printf("Java_cbccore_low_Create_create_1cover_1dock stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_mode
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1mode(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_mode(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1mode stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_lbump
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1lbump(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_lbump(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1lbump stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_rbump
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1rbump(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_rbump(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1rbump stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_lwbump
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1lwbump(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_lwbump(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1lwbump stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_cwbump
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1cwbump(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_cwbump(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1cwbump stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_rwbump
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1rwbump(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_rwbump(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1rwbump stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_wall
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1wall(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_wall(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1wall stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_lcliff
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1lcliff(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_lcliff(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1lcliff stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_rcliff
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1rcliff(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_rcliff(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1rcliff stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_lfcliff
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1lfcliff(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_lfcliff(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1lfcliff stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_rfcliff
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1rfcliff(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_rfcliff(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1rfcliff stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_vwall
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1vwall(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_vwall(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1vwall stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_overcurrents
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1overcurrents(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_overcurrents(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1overcurrents stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_infrared
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1infrared(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_infrared(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1infrared stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_advance_button
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1advance_1button(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_advance_button(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1advance_1button stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_play_button
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1play_1button(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_play_button(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1play_1button stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_distance
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1distance(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_distance(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1distance stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_normalized_angle
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1normalized_1angle(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_normalized_angle(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1normalized_1angle stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_total_angle
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1total_1angle(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_total_angle(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1total_1angle stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    set_create_normalized_angle
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_set_1create_1normalized_1angle(JNIEnv *env, jobject obj, jint angle)
{
#ifdef CBC
    set_create_normalized_angle(angle);
#else
    printf("Java_cbccore_low_Create_set_1create_1normalized_1angle stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    set_create_total_angle
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_set_1create_1total_1angle(JNIEnv *env, jobject obj, jint angle)
{
#ifdef CBC
    set_create_total_angle(angle);
#else
    printf("Java_cbccore_low_Create_set_1create_1total_1angle stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_battery_charging_state
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1battery_1charging_1state(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_battery_charging_state(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1battery_1charging_1state stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_battery_voltage
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1battery_1voltage(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_battery_voltage(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1battery_1voltage stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_battery_current
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1battery_1current(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_battery_current(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1battery_1current stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_battery_temp
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1battery_1temp(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_battery_temp(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1battery_1temp stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_battery_charge
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1battery_1charge(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_battery_charge(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1battery_1charge stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_battery_charge
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1battery_1capacity(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_battery_capacity(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1battery_1capacity stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_wall_amt
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1wall_1amt(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_wall_amt(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1wall_1amt stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_lcliff_amt
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1lcliff_1amt(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_lcliff_amt(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1lcliff_1amt stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_rcliff_amt
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1rcliff_1amt(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_rcliff_amt(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1rcliff_1amt stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_lfcliff_amt
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1lfcliff_1amt(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_lfcliff_amt(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1lfcliff_1amt stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_rfcliff_amt
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1rfcliff_1amt(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_rfcliff_amt(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1rfcliff_1amt stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_bay_DI
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1bay_1DI(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_bay_DI(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1bay_1DI stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_bay_AI
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1bay_1AI(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_bay_AI(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1bay_1AI stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_song_number
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1song_1number(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_song_number(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1song_1number stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_song_playing
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1song_1playing(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_song_playing(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1song_1playing stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_number_of_stream_packets
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1number_1of_1stream_1packets(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_number_of_stream_packets(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1number_1of_1stream_1packets stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_requested_velocity
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1requested_1velocity(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_requested_velocity(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1requested_1velocity stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_requested_radius
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1requested_1radius(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_requested_radius(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1requested_1radius stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_requested_right_velocity
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1requested_1right_1velocity(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_requested_right_velocity(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1requested_1right_1velocity stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    get_create_requested_left_velocity
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_get_1create_1requested_1left_1velocity(JNIEnv *env, jobject obj, jfloat lag)
{
#ifdef CBC
    return get_create_requested_left_velocity(lag);
#else
    printf("Java_cbccore_low_Create_get_1create_1requested_1left_1velocity stub\n");
    return 0;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1stop(JNIEnv *env, jobject obj)
{
#ifdef CBC
    create_stop();
#else
    printf("Java_cbccore_low_Create_create_1stop stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_drive
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1drive(JNIEnv *env, jobject obj, jint speed, jint radius)
{
#ifdef CBC
    create_drive(speed, radius);
#else
    printf("Java_cbccore_low_Create_create_1drive stub\n");
#endif
}


/*
 * Class:     cbccore_low_Create
 * Method:    create_drive_straight
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1drive_1straight(JNIEnv *env, jobject obj, jint speed)
{
#ifdef CBC
    create_drive_straight(speed);
#else
    printf("Java_cbccore_low_Create_create_1drive_1straight stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_spin_CW
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1spin_1CW(JNIEnv *env, jobject obj, jint speed)
{
#ifdef CBC
    create_spin_CW(speed);
#else
    printf("Java_cbccore_low_Create_create_1spin_1CW stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_spin_CCW
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1spin_1CCW(JNIEnv *env, jobject obj, jint speed)
{
#ifdef CBC
    create_spin_CCW(speed);
#else
    printf("Java_cbccore_low_Create_create_1spin_1CCW stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_drive_direct
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1drive_1direct(JNIEnv *env, jobject obj, jint r_speed, jint l_speed)
{
#ifdef CBC
    create_drive_direct(r_speed, l_speed);
#else
    printf("Java_cbccore_low_Create_create_1drive_1direct stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_spin_block
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_create_1spin_1block(JNIEnv *env, jobject obj, jint speed, jint angle)
{
#ifdef CBC
    return create_spin_block(speed, angle);
#else
    printf("Java_cbccore_low_Create_create_1spin_1block stub\n");
    return -1;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_advance_led
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1advance_1led(JNIEnv *env, jobject obj, jint on)
{
#ifdef CBC
    create_advance_led(on);
#else
    printf("Java_cbccore_low_Create_create_1advance_1led stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_play_led
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1play_1led(JNIEnv *env, jobject obj, jint on)
{
#ifdef CBC
    create_play_led(on);
#else
    printf("Java_cbccore_low_Create_create_1play_1led stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_power_led
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1power_1led(JNIEnv *env, jobject obj, jint color, jint brightness)
{
#ifdef CBC
    create_power_led(color, brightness);
#else
    printf("Java_cbccore_low_Create_create_1power_1led stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_digital_output
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1digital_1output(JNIEnv *env, jobject obj, jint bits)
{
#ifdef CBC
    create_digital_output(bits);
#else
    printf("Java_cbccore_low_Create_1digital_1output stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_pwm_low_side_drivers
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1pwm_1low_1side_1drivers(JNIEnv *env, jobject obj, jint pwm2, jint pwm1, jint pwm0)
{
#ifdef CBC
    create_pwm_low_side_drivers(pwm2, pwm1, pwm0);
#else
    printf("Java_cbccore_low_Create_create_1pwm_1low_1side_1drivers stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_low_side_drivers
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1low_1side_1drivers(JNIEnv *env, jobject obj, jint pwm2, jint pwm1, jint pwm0)
{
#ifdef CBC
    create_low_side_drivers(pwm2, pwm1, pwm0);
#else
    printf("Java_cbccore_low_Create_create_1low_1side_1drivers stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_load_song
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1load_1song(JNIEnv *env, jobject obj, jint num)
{
#ifdef CBC
    create_load_song(num);
#else
    printf("Java_cbccore_low_Create_create_1load_1song stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_play_song
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1play_1song(JNIEnv *env, jobject obj, jint num)
{
#ifdef CBC
    create_play_song(num);
#else
    printf("Java_cbccore_low_Create_create_1play_1song stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_read_block
 * Signature: ([CI)I
 */
JNIEXPORT jint JNICALL Java_cbccore_low_Create_create_1read_1block(JNIEnv *env, jobject obj, jbyteArray data, jint count)
{
#ifdef CBC
	char cdata[count];
    jint ret = create_read_block(cdata, count);
	(*env)->SetByteArrayRegion(env, data, 0, count, (jbyte*)cdata);
	return ret;
#else
    printf("Java_cbccore_low_Create_create_1read_1block stub\n");
	return -1;
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_write_byte
 * Signature: (C)V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1write_1byte(JNIEnv *env, jobject obj, jchar write_byte)
{
#ifdef CBC
    create_write_byte(write_byte);
#else
    printf("Java_cbccore_low_Create_create_1write_1byte stub\n");
#endif
}

/*
 * Class:     cbccore_low_Create
 * Method:    create_clear_serial_buffer
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cbccore_low_Create_create_1clear_1serial_1buffer(JNIEnv *env, jobject obj)
{
#ifdef CBC
    create_clear_serial_buffer();
#else
    printf("Java_cbccore_low_Create_create_1clear_1serial_1buffer stub\n");
#endif
}

#ifdef __cplusplus
}
#endif

