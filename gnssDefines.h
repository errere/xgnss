#ifndef __GNSSTYPES_H__
#define __GNSSTYPES_H__

#include <inttypes.h>
#include <Arduino.h>

typedef struct
{
    uint8_t Hour = 0;
    uint8_t Minute = 0;
    uint8_t Second = 0;
} UTCTime_t;
typedef struct
{
    uint8_t Day = 0;
    uint8_t Month = 0;
    uint16_t Year = 0;
} UTCDate_t;

typedef enum
{
    NA,
    GGA,//
    GLL,
    GSA,//
    GSV,
    RMC,//
    VTG,//
    TXT
} NMEAType_t;

//GPGGA（定位信息） eg:$GPGGA,,,,,,0,00,99.99,,,,,,*48  $GPGGA,092204.999,4250.5589,S,14718.5084,E,1,04,24.4,12.2,M,19.7,M,,0000*1F
typedef struct
{
    //字段1：UTC 时间，hhmmss.sss，时分秒格式
    UTCTime_t UTC;
    //字段2：纬度ddmm.mmmm，度分格式（前导位数不足则补0）
    double Latitude = 0.0;
    //字段3：纬度N（北纬）或S（南纬）
    char Ns = 0;
    //字段4：经度dddmm.mmmm，度分格式（前导位数不足则补0）
    double Longitude = 0.0;
    //字段5：经度E（东经）或W（西经）
    char Ew = 0;
    //字段6：GPS状态，0=不可用(FIX NOT valid)，1=单点定位(GPS FIX)，2=差分定位(DGPS)，3=无效PPS，4=实时差分定位（RTK FIX），5=RTK FLOAT，6=正在估算
    uint8_t Fix = 0;
    //字段7：正在使用的卫星数量（00 - 12）（前导位数不足则补0）
    uint8_t S_Num = 0;
    //字段8：HDOP水平精度因子（0.5 - 99.9）
    double HDOP = 0.0;
    //字段9：海拔高度（-9999.9 - 99999.9）
    double Altitude = 0.0;
    //字段10：单位：M（米）
    char Metre = 'M';
    //字段11：地球椭球面相对大地水准面的高度 WGS84水准面划分
    double Level = 0.0;
    //字段12：WGS84水准面划分单位：M（米）
    char Level_Unit = 'M';
    //字段13：差分时间（从接收到差分信号开始的秒数，如果不是差分定位将为空）
    double Diff_Time = 0.0;
    //字段14：差分站ID号0000 - 1023（前导位数不足则补0，如果不是差分定位将为空）
    uint16_t Diff_ID = 0;

} gga_t;

//GPGLL (大地坐标信息)
typedef struct
{
    //字段1：纬度ddmm.mmmm，度分格式（前导位数不足则补0）
    double Latitude = 0.0;
    //字段2：纬度N（北纬）或S（南纬）
    char Ns = 0;
    //字段3：经度dddmm.mmmm，度分格式（前导位数不足则补0）
    double Longitude = 0.0;
    //字段4：经度E（东经）或W（西经）
    char Ew = 0;
    //字段5：UTC时间
    UTCTime_t UTC;
    //字段6：数据有效性 A有效  V无效
    char valid;
    //字段7：定位模式，仅 NMEA 2.3 及以上版本有效
    char mode;
} gll_t;

//GPGSA（ 当前卫星信息） eg:$GPGSA,A,1,,,,,,,,,,,,,99.99,99.99,99.99*30  $GPGSA,A,3,01,20,19,13,,,,,,,,,40.4,24.4,32.2*0A
typedef struct
{
    //字段1：定位模式(选择2D/3D)，A=自动选择，M=手动选择
    char Mode = 0;
    //字段2：定位类型，1=未定位，2=2D定位，3=3D定位
    uint8_t Type = 0;
    //字段(3-14)：PRN码（伪随机噪声码），(第1信道-第12信道)正在使用的卫星PRN码编号（00）（前导位数不足则补0）
    uint8_t Sno[12] = {0};
    //字段15：PDOP综合位置精度因子（0.5 - 99.9）
    double PDOP = 0.0;
    //字段16：HDOP水平精度因子（0.5 - 99.9）
    double HDOP = 0.0;
    //字段17：VDOP垂直精度因子（0.5 - 99.9）
    double VDOP = 0.0;

} gsa_t;

//GPRMC（推荐定位信息数据格式）eg:$GPRMC,,V,,,,,,,,,,N*53  $GPRMC,024813.640,A,3158.4608,N,11848.3737,E,10.05,324.27,150706,,,A*50
typedef struct
{
    //字段1：UTC时间
    UTCTime_t UTC;
    //字段2：状态，A=定位，V=未定位
    char State = 0;
    //字段3：纬度
    double Latitude = 0.0;
    //字段4：纬度N（北纬）或S（南纬）
    char Ns = 0;
    //字段5：经度
    double Longitude = 0.0;
    //字段6：经度E（东经）或W（西经）
    char Ew = 0;
    //字段7：速度，节，Knots
    double Velocity = 0.0;
    //字段8：方位角，度
    double Azimuth = 0.0;
    //字段9：UTC日期
    UTCDate_t Date;
    //字段10：磁偏角
    double Declination = 0.0;
    //字段11：磁偏角方向，E=东W=西
    char Dew = 0;
    //字段12：模式，A=自动，D=差分，E=估测，N=数据无效（3.0协议内容）
    char Mode = 0;

} rmc_t;

//GPVTG（地面速度信息） eg:$GPVTG,,,,,,,,,N*30  $GPVTG,89.68,T,,M,0.00,N,0.0,K*5F
typedef struct
{
    //字段1：运动角度，000 - 359，（前导位数不足则补0）
    double T_Angle = 0.0;
    //字段2：T=真北参照系
    char T_Reference = 'T';
    //字段3：运动角度，000 - 359，（前导位数不足则补0）
    double M_Angle = 0.0;
    //字段4：M=磁北参照系
    char M_Reference = 'M';
    //字段5：水平运动速度（0.00）（前导位数不足则补0）
    double N_Horizontal_Velocity = 0.0;
    //字段6：N=节，Knots
    char Knots = 'N';
    //字段7：水平运动速度（0.00）（前导位数不足则补0）
    double K_Horizontal_Velocity = 0.0;
    //字段8：K=公里/时，km/h
    char Kmh = 'K';

} vtg_t;

//TXT
typedef struct
{
    uint8_t MsgNum;
    uint8_t MsgNo;
    uint8_t MsgType;
    String msg;
} txt_t;

#endif