
#include <jni.h>
#include "ARDrone.h"
#include "ARDroneAPI.h"

/*
 * Class:     Drone
 * Method:    connect
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Drone_connect(JNIEnv * env, jobject obj){
	
	drone_connect();
}

/*
 * Class:     Drone
 * Method:    disconnect
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Drone_disconnect(JNIEnv * env, jobject obj){
	
	drone_disconnect();
}

/*
 * Class:     Drone
 * Method:    takeoff
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Drone_takeoff(JNIEnv * env, jobject obj){
	
	drone_takeoff();	
}

/*
 * Class:     Drone
 * Method:    land
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Drone_land(JNIEnv * env, jobject obj){
	
	drone_land();
}

/*
 * Class:     Drone
 * Method:    emergency
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Drone_emergency(JNIEnv * env, jobject obj){
	drone_emergency();
}

/*
 * Class:     Drone
 * Method:    get_battery
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_Drone_get_1battery(JNIEnv * env, jobject obj){
	jint returnme = drone_get_battery();
    return returnme;
}

/*
 * Class:     Drone
 * Method:    get_x
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_Drone_get_1x(JNIEnv * env, jobject obj){
	jfloat returnme = drone_get_x();
    return returnme;
}

/*
 * Class:     Drone
 * Method:    get_y
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_Drone_get_1y(JNIEnv * env, jobject obj){
	jfloat returnme = drone_get_y();
    return returnme;
}

/*
 * Class:     Drone
 * Method:    get_z
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_Drone_get_1z(JNIEnv * env, jobject obj){
    jfloat returnme = drone_get_z();
    return returnme;
}

/*
 * Class:     Drone
 * Method:    get_x_velocity
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_Drone_get_1x_1velocity(JNIEnv * env, jobject obj){
	jfloat returnme =  drone_get_x_velocity();
    return returnme;
}

/*
 * Class:     Drone
 * Method:    get_y_velocity
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_Drone_get_1y_1velocity(JNIEnv *, jobject){
    jfloat returnme =  drone_get_y_velocity();
    return returnme;
}

/*
 * Class:     Drone
 * Method:    get_z_velocity
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_Drone_get_1z_1velocity(JNIEnv * env, jobject obj){
    jfloat returnme =  drone_get_z_velocity();
    return returnme;
}

/*
 * Class:     Drone
 * Method:    get_yaw
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_Drone_get_1yaw(JNIEnv * env, jobject obj){
	jfloat returnme = drone_get_yaw();
    return returnme;
}

/*
 * Class:     Drone
 * Method:    front_camera
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Drone_front_1camera(JNIEnv * env, jobject obj){
	drone_front_camera();
}

/*
 * Class:     Drone
 * Method:    down_camera
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Drone_down_1camera(JNIEnv * env, jobject obj){
	drone_down_camera();
}

/*
 * Class:     Drone
 * Method:    enable_drone_vision
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Drone_enable_1drone_1vision(JNIEnv * env, jobject obj){
	enable_drone_vision();
}

/*
 * Class:     Drone
 * Method:    disable_drone_vision
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Drone_disable_1drone_1vision(JNIEnv * env, jobject obj){
	disable_drone_vision();
}

/*
 * Class:     Drone
 * Method:    write_external_camera_data
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Drone_write_1external_1camera_1data(JNIEnv * env, jobject obj){
	write_external_camera_data();
}

/*
 * Class:     Drone
 * Method:    delete_external_camera_data
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Drone_delete_1external_1camera_1data(JNIEnv * env, jobject obj){
	delete_external_camera_data();
}

/*
 * Class:     Drone
 * Method:    set_drone_Mac_Address
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_Drone_set_1drone_1Mac_1Address(JNIEnv * env, jobject obj, jstring str){
    
    // TODO: Make set mac address function


/*
    jboolean iscopy;
    const char *nativeString = (*env)->GetStringUTFChars(env, str, iscopy);
    set_drone_Mac_Address(nativeString);
    (*env)->ReleaseStringUTFChars(env, str, nativeString);
*/
    
}

/*
 * Class:     Drone
 * Method:    drone_move
 * Signature: (FFFF)V
 */
JNIEXPORT void JNICALL Java_Drone_drone_1move(JNIEnv * env, jobject obj, jfloat x, jfloat y , jfloat z , jfloat yaz){
	
    drone_move( x, y, z, yaz);
	
}

/*
 * Class:     Drone
 * Method:    hover
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_Drone_hover(JNIEnv * env, jobject obj){
	
    drone_hover();
}



/*
 * Class:     Drone
 * Method:    hover_on_roundel
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_Drone_hover_1on_1roundel
(JNIEnv * env, jobject obj, jboolean boo){
    
    drone_hover_on_roundel(boo);
}

/*
 * Class:     ARDrone
 * Method:    set_detection
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_ARDrone_set_1detection
  (JNIEnv * env, jobject obj, jint num){
    drone_set_detection(num);
}

