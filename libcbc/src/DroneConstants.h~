/// ATCommand.h
#ifndef DRONECONSTANTS_H
#define DRONECONSTANTS_H
#include <string>

const std::string DRONE_IP =  "192.168.1.1";

const int NAVIGATION_DATA_PORT = 5554;
const int VIDEO_DATA_PORT = 5555;
const int ATCOMMAND_PORT = 5556;

//I DONT THINK THESE ARE BEING USED
const int NAVDATA_STATE_DATA_OFFSET =  4;
const int NAVDATA_BATTERY_OFFSET  = 24;
const int NAVDATA_ALTITUDE_OFFSET = 40;
//END

const unsigned int INTERVAL = 100;

//Controller Constants
const std::string ATCONFIG_COMMAND = "AT*CONFIG=";
const std::string ATFLAT_TRIM_COMMAND = "AT*FTRIM=";
const std::string ATSTATE_COMMAND = "AT*REF="; //LAND TAKEOFF TOGGLE_EMERGENCY
const std::string ATMOVE_COMMAND = "AT*PCMD=";
const std::string ATWATCHDOG_COMMAND = "AT*COMWDG=";

const std::string TAKEOFF_ARG = ",290718208";
const std::string LAND_ARG = ",290717696";
const std::string EMERGENCY_ARG = ",290717952";

const int DEFAULT_MAX_ALTITUDE = 4572; //altitude max 4572 mm = 15 ft
const std::string MAX_ALTITUDE_ARG  = ",\"control:altitude_max\",\"";

const int DEFAULT_MAX_VERTICAL_SPEED = 2000; // maximum vertical speed 2000mm/s = 2m/s
const std::string MAX_VERTICAL_SPEED = ",\"control:control_vz_max\",\"";  

const float DEFAULT_MAX_EULER_ANGLE = 0.52; //In Radians .52 Rads = 30 Deg
const std::string MAX_EULER_ANGLE = "\"control:euler_angle_max\",\"";

const float DEFAULT_MAX_YAW_SPEED = 6.00; //maximum yaw speed = 6rad/s ~= 343deg/s
const std::string MAX_YAW_SPEED = ",\"control:control_yaw\",\"";

const int DEFAULT_VIDEO_BITRATE = 10000;
const std::string VIDEO_BITRATE = "\"video:bitrate\",\"";

const std::string MAC_ADDRESS = ",\"network:owner_mac\",\"";

const std::string SHELL_INSIDE_MODE_ARG = ",\"control:flight_without_shell\",\"FALSE\"";
const std::string SHELL_OUTSIDE_MODE_ARG = ",\"control:flight_without_shell\",\"TRUE\"";

const std::string CONTROL_LEVEL = ",\"control:control_level\",\"";

const std::string MINIMAL_NAV_DATA_ARG = ",\"general:navdata_demo\",\"TRUE\"";
const std::string ALL_NAV_DATA_ARG = ",\"general:navdata_demo\",\"FALSE\"";

const std::string REQUEST_VISION_TAG_DATA_ARG = ",\"general:navdata_options\",\"65537\"";

const std::string VIDEO_ENABLE_ARG = ",\"general:video_enable\",\"TRUE\"";
const std::string VIDEO_DISABLE_ARG = ",\"general:video_enable\",\"FALSE\"";

const std::string FRONT_CAMERA = ",\"video:video_channel\",\"0\"";
const std::string DOWN_CAMERA = ",\"video:video_channel\",\"1\"";

const std::string ULTRASOUND_CHANNEL_A_ARG = ",\"pic:ultrasound_freq\",\"8\"";
const std::string ULTRASOUND_CHANNEL_B_ARG = ",\"pic:ultrasound_freq\",\"7\"";

const std::string ENEMY_COLOR_GREEN_ARG = ",\"detect:enemy_colors\",\"1\"";
const std::string ENEMY_COLOR_YELLOW_ARG = ",\"detect:enemy_colors\",\"2\"";
const std::string ENEMY_COLOR_BLUE_ARG = ",\"detect:enemy_colors\",\"3\"";

const std::string DETECT_TYPE_STRIPE_ARG = ",\"detect:detect_type\"),\"6\"";
const std::string DETECT_TYPE_NONE_ARG = ",\"detect:detect_type\"),\"3\"";
const std::string DETECT_TYPE_ROUNDEL_ARG = ",\"detect:detect_type\"),\"12\"";
const std::string DETECT_TYPE_ENEMIES_FRONT_CAMERA_ARG = ",\"detect:detect_type\"),\"13\"";

const std::string GROUND_STRIPE_YELLOW_BLUE_ARG = ",\"detect:enemy_colors\",\"0x11\"";
const std::string GROUND_STRIPE_ORANGE_GREEN_ARG = ",\"detect:enemy_colors\",\"0x10\"";

const std::string FLYING_MODE_NORMAL_ARG = ",\"control:flying_mode\",\"0\"";
const std::string FLYING_MODE_HOVER_ON_ROUNDEL_ARG = ",\"control:flying_mode\",\"1\"";
const std::string FLYING_MODE_HOVER_ON_ORIENTED_ROUNDEL_ARG = ",\"control:flying_mode\",\"2\"";

const std::string VIDEO_CONTROL_MODE_DISABLE_ARG = ",\"video:bitrate_ctrl_mode\",\"0\"";

// ARDroneAPI Constants
const float DRIFT_TOLERANCE = 0.001;
const float TIMESTAMP_PER_SECOND = float(1)/float(1000);
const int MILIMETERS_PER_METER = 1000;

//VideoDecoder
const int kPictureFormatCIF = 1;
const int kPictureFormatVGA = 2;

const int CONST_BlockWidth = 8;
const int CONST_BlockSize = 64;

const int CONST_WidthCif = 88;
const int CONST_HeightCif = 72;

const int CONST_WidthVga = 160;
const int CONST_HeightVga = 120;

const int CONST_TableQuantization = 31;

const int FIX_0_298631336 = 2446;
const int FIX_0_390180644 = 3196;
const int FIX_0_541196100 = 4433;
const int FIX_0_765366865 = 6270;
const int FIX_0_899976223 = 7373;
const int FIX_1_175875602 = 9633;
const int FIX_1_501321110 = 12299;
const int FIX_1_847759065 = 15137;
const int FIX_1_961570560 = 16069;
const int FIX_2_053119869 = 16819;
const int FIX_2_562915447 = 20995;
const int FIX_3_072711026 = 25172;

const int CONST_BITS = 13;
const int PASS1_BITS = 1;

#endif