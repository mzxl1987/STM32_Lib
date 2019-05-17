#ifndef __miniConfig_H__
#define __miniConfig_H__

#include "stm32f1xx_hal.h"


/**==================================================
--- 程序版本 ---
Tang, Song, Yuan, Ming, Qing, Qiii, Chuu, Yann, Zhao, Hann, Weii, Qinn
=====================================================**/
#define VERSION "V1.1.1.20190325_Chuu"
#define RELEASE_NORMAL 1

/** 常量定义  ---------------------------------------------- **/

#define I 0
#define V 1
#define P 2


/** EEPROM存储 --------------------------------------------- **/

/*=================================================================================== 
 *      EEPROM 相关参数的设定  
 ====================================================================================*/
/********************************
 *  EEPROM 中数据的存储结构
 * 1.终端ID              6bytes
 * 2.制造商ID            5bytes
 * 3.终端型号            8bytes
 * 4.开关灯起始日期       2byte  BCD编码
 * 5.开关灯时间           366 * 3  =  1098  ,1440分钟(0x5A0),开机时间：06:30 -> 0x186,关机时间：17:30  -> 0x41A  ,开关机时间表示为:0x18641A
 * 
*********************************/

extern uint8_t equipmentID[] ;   //<----------- 终端ID ------------
extern uint8_t manufacturerID[] ;   //<----------- 制造商ID ----------
extern uint8_t terminalModel[];   //<----------- 终端型号 -----------
extern uint8_t ONOFF_startDate[];  //<---------------- 设置开关灯的起始日期 0x0A0A表示：10月10日 -------------
extern uint8_t ONOFF_todayTime[];  //<---------------- 当日开关灯时间 -------------------
extern uint8_t light_ONOFF_datetime[];   //开关灯策略时间

extern uint8_t TMP_ONOFF_startDate[];  //<---------------- 临时开关灯起始日期 -------------------
extern uint8_t TMP_ONOFF_DayCount[];  //<---------------- 0x00:无效  0x01~0xfe有效天数 0xff:一直有效 -------------------
extern uint8_t TMP_ONOFF_time[];  //<---------------- 临时开关灯时间 -------------------



/**********************************************
 **                                          **
 **                路灯参数                   **
 **                                          **
***********************************************/

/***
起始字节	字段	数据类型	描述及要求
0	配置启用标志	BYTE	0x00 不启用；0x01 启用；0x02~0xff 未知
1	一阶段时间	BCD[2]	BCD[0]时 ，BCD[1]分
3	一阶段阀值	BYTE[4]	见表8.18.2
7	二阶段时间	BCD[2]	
9	二阶段阀值	BYTE[4]	
13	三阶段时间	BCD[2]	
15	三阶段阀值	BYTE[4]	
19	四阶段时间	BCD[2]	
21	四阶段阀值	BYTE[4]	
25	五阶段时间	BCD[2]	
27	五阶段阀值	BYTE[4]	 
****/
extern uint8_t dimmer[]; //<------- 调光参数 --------------------

/**===================================================
*** 报警数据采集
***位	定义	处理说明
0	电容故障	标志维持至报警条件解除
1	光源故障	标志维持至报警条件解除
2	继电器故障	标志维持至报警条件解除
3	保险丝故障	标志维持至报警条件解除
4	存储芯片故障	标志维持至报警条件解除
5	时钟芯片故障	标志维持至报警条件解除
6	读卡模块故障	标志维持至报警条件解除
7	内部参数配置故障	标志维持至报警条件解除
8	漏电报警	标志维持至报警条件解除
9	防盗报警	标志维持至报警条件解除
10	水浸报警	标志维持至报警条件解除
11	电流过大报警	标志维持至报警条件解除
12	功率过大报警	标志维持至报警条件解除
13	功率过小报警	标志维持至报警条件解除
14~31	预留	

-------------------------------------------------------
参数设置
0x10	1	漏电保护启用标志，0x00启用 0x01~0xff禁用
0x11	2	漏电流阀值，单位mA
0x12	2	漏电极限不驱动时间，持续时间超过该值，则关断输出，单位ms
0x13	2	漏电延时重合闸时间，持续时间超过该值，则开合输出，单位ms
0x14	1	漏电压阀值，单位V
0x15	1	经纬度开关时间启用标志，0禁用  1启用
0x16	1	报警间隔分钟数，1~60，默认为1

0x21	1	电容故障报警功率因数限值，单位0.01
0x22	1	电容故障恢复功率因数限值，单位0.01
0x23	1	电流过大报警电流限值，单位0.1A
0x24	1	电流过大恢复电流限值，单位0.1A
0x25	1	功率过大报警限值，单位10W
0x26	1	功率过大恢复限值，单位10W
0x27	1	功率过小报警限值，单位10W
0x28	1	功率过小恢复限值，单位10W
0x29	1	电压报警限值,单位V

0x30	1	数据冻结密度m(存储历史数据的间隔时间)，见表A.8.15.6
0x31	2	开灯后电流过大保护延迟时间，0-该功能禁止，单位秒(s)


***===================================================*/

#define ALARM_MAX_COUNT 10         /** 报警触发最大次数，当报警次数大于这个值时就上传报警 **/
typedef struct {
	uint32_t         value;                    //报警值
	uint32_t         tmp_value;                //临时报警值
	uint32_t         tick_upload;              //报警上报的时间点
	uint8_t          count;                    //报警次数
	uint8_t          isFirst;                  //1：第一次报警，0：非报警
	uint8_t          isCancel;                 //报警是否取消
} AlarmInfo;

extern AlarmInfo alarmInfo;                  //报警信息


#define ALARM_DianRong   (1<<0) // 0x00000001   //电容故障
#define ALARM_GuangYuan  (1<<1) // 0x00000002   //光源故障
#define ALARM_JiDianQi   (1<<2) // 0x00000004   //继电器故障
#define ALARM_BaoXianSi  (1<<3) // 0x00000008   //保险丝故障
#define ALARM_StorageChip (1<<4) // 0x00000010   //存储芯片故障
#define ALARM_TimeChip    (1<<5) // 0x00000020   //时钟芯片故障
#define ALARM_SDMode      (1<<6) // 0x00000040   //读卡模块故障
#define ALARM_InnerParam  (1<<7) // 0x00000080   //内部参数配置故障
#define ALARM_LouDian     (1<<8) // 0x00000100   //漏电报警 
#define ALARM_FangDao     (1<<9) // 0x00000200   //防盗
#define ALARM_JinShui     (1<<10) // 0x00000400   //水浸报警
#define ALARM_iMoreThanMax (1<<11) // 0x00000800   //电流过大报警
#define ALARM_pMoreThanMax (1<<12) // 0x00001000   //功率过大报警
#define ALARM_pLessThanMin (1<<13) // 0x00002000   //功率过小报警


/*====================================================
 * 电流电压以及功率的参考值 ,  及对应的电流电压以及功率的校准值
 * 1.是否已经矫正  1byte   0:未矫正, 1:已矫正
 * 2.I参考电流     2bytes
 * 3.V参考电压     2bytes
 * 4.P参考功率     2bytes
 * 5.I电流的参考频率  2bytes
 * 6.V电压的参考频率  2bytes
 * 7.P功率的参考频率  2bytes
 * EEPROM中地址顺序 :是否校准
 *                   灯0校准电流值,灯0校准电压值,灯0校准功率值,灯1校准电流值,灯1校准电压值,灯1校准功率值,灯2校准电流值,灯2校准电压值,灯2校准功率值,
 *                   灯0校准电流频率,灯0校准电压频率,灯0校准功率频率,灯1校准电流频率,灯1校准电压频率,灯1校准功率频率,灯2校准电流频率,灯2校准电压频率,灯2校准功率频率,
 =====================================================*/
extern uint8_t standard[];  //校准数据
extern uint8_t has_adjust;  //0:表示未校准, 1:表示已经校准
extern uint32_t standard_IVP[] ;    //测量的电流值,电压值,以及功率
extern uint32_t frequence_IVP[];  //对应测得的校准频率
extern uint32_t f_IVP;   //待测试的电流电压功率 频率
#define ADJUST_KEEP_TIME 3000   //校准时测试时长，单位ms


/******************************************
**** 设备运行时间计算
*******************************************/
extern uint8_t arr_totalRunningTime[];   //总运行时间
extern uint32_t preRunningTime;     //上次存储时运行时间
extern uint8_t arr_currentTime[];         //当前运行时间
extern uint32_t dtRunningTime;      //本次与上一次存储的差值

#define ADDR_equipmentID                   5
#define ADDR_equipmentID_Size              6

#define ADDR_manufacturerID                (ADDR_equipmentID + ADDR_equipmentID_Size)
#define ADDR_manufacturerID_Size           5

#define ADDR_terminalModel                 (ADDR_manufacturerID + ADDR_manufacturerID_Size)
#define ADDR_terminalModel_Size            8

#define ADDR_light_ONOFF_startDate         (ADDR_terminalModel + ADDR_terminalModel_Size)
#define ADDR_light_ONOFF_startDate_Size     2

#define light_ONOFF_datetime_SIZE           1098   //<----------- 开关灯时间 -----------
#define ADDR_light_ONOFF_datetime           (ADDR_light_ONOFF_startDate + ADDR_light_ONOFF_startDate_Size)

#define ADDR_TMP_ONOFF_startDate            (ADDR_light_ONOFF_datetime + light_ONOFF_datetime_SIZE)
#define ADDR_TMP_ONOFF_startDate_Size       2

#define ADDR_TMP_ONOFF_DayCount             (ADDR_TMP_ONOFF_startDate + ADDR_TMP_ONOFF_startDate_Size)
#define ADDR_TMP_ONOFF_DayCount_Size        1

#define ADDR_TMP_ONOFF_time_SIZE            3
#define ADDR_TMP_ONOFF_time                 (ADDR_TMP_ONOFF_DayCount + ADDR_TMP_ONOFF_DayCount_Size)

#define ADDR_PARAM_SIZE                     52
#define ADDR_PARAM                         (ADDR_TMP_ONOFF_time + ADDR_TMP_ONOFF_time_SIZE)

#define ADDR_Dimmer_SIZE                    31
#define ADDR_Dimmer                         (ADDR_PARAM + ADDR_PARAM_SIZE)

#define ADDR_light_control                  (ADDR_Dimmer + ADDR_Dimmer_SIZE)
#define ADDR_light_control_Size             4

#define ADDR_light_control_mode             (ADDR_light_control + ADDR_light_control_Size)
#define ADDR_light_control_mode_Size         1

#define address_standard                    (ADDR_light_control_mode + ADDR_light_control_mode_Size)
#define address_standard_Size               37

#define address_TOTALRUNNINGTIME            (address_standard + address_standard_Size)
#define address_TOTALRUNNINGTIME_Size        4

#define ADDR_heartbeat                      (address_TOTALRUNNINGTIME + address_TOTALRUNNINGTIME_Size)
#define ADDR_heartbeat_Size                 (4 + 1 + 4)  /** 参数ID + 参数长度 + 参数值 **/

#define ADDR_tcp_responseTime               (ADDR_heartbeat + ADDR_heartbeat_Size)
#define ADDR_tcp_responseTime_Size          9

#define ADDR_tcp_reTransmission_times       (ADDR_tcp_responseTime + ADDR_tcp_responseTime_Size)
#define ADDR_tcp_reTransmission_times_Size  9

#define ADDR_mainServer_apn                 (ADDR_tcp_reTransmission_times + ADDR_tcp_reTransmission_times_Size)
#define ADDR_mainServer_apn_Size            69

#define ADDR_mainServer_username            (ADDR_mainServer_apn + ADDR_mainServer_apn_Size)
#define ADDR_mainServer_username_Size       69


#define ADDR_mainServer_password            (ADDR_mainServer_username + ADDR_mainServer_username_Size)
#define ADDR_mainServer_password_Size       69

#define ADDR_mainServer_ip                  (ADDR_mainServer_password + ADDR_mainServer_password_Size)
#define ADDR_mainServer_ip_Size             69


#define ADDR_backServer_apn                 (ADDR_mainServer_ip + ADDR_mainServer_ip_Size)
#define ADDR_backServer_apn_Size            69

#define ADDR_backServer_username            (ADDR_backServer_apn + ADDR_backServer_apn_Size)
#define ADDR_backServer_username_Size       69

#define ADDR_backServer_password            (ADDR_backServer_username + ADDR_backServer_username_Size)
#define ADDR_backServer_password_Size       69

#define ADDR_backServer_ip                  (ADDR_backServer_password + ADDR_backServer_password_Size)
#define ADDR_backServer_ip_Size             69


#define ADDR_tcp_port                       (ADDR_backServer_ip + ADDR_backServer_ip_Size)
#define ADDR_tcp_port_Size                  9

#define ADDR_province_id                    (ADDR_tcp_port + ADDR_tcp_port_Size)
#define ADDR_province_id_Size               9

#define ADDR_city_id                        (ADDR_province_id + ADDR_province_id_Size)
#define ADDR_city_id_Size                   9

#define ADDR_equip_phoneNumber              (ADDR_city_id + ADDR_city_id_Size)
#define ADDR_equip_phoneNumber_Size         69              

#define ADDR_light_operationLog_index       (ADDR_equip_phoneNumber + ADDR_equip_phoneNumber_Size)
#define ADDR_light_operationLog_index_Size  2

#define ADDR_light_operationLog             (ADDR_light_operationLog_index + ADDR_light_operationLog_index_Size)
#define ADDR_light_operationLog_Size        700       /** 7*100  100条操作日志  **/

#define ADDR_light_statusLog_index          (ADDR_light_operationLog + ADDR_light_operationLog_Size)
#define ADDR_light_statusLog_index_Size     2

#define ADDR_light_statusLog                (ADDR_light_statusLog_index + ADDR_light_statusLog_index_Size)
#define ADDR_light_statusLog_Size           5200      /**  (1+12) * 400 条路灯状态日志     **/


#define ADDR_light_APN_IP_PORT_CopyFlag        (ADDR_light_statusLog + ADDR_light_statusLog_Size + 10)
#define ADDR_light_APN_IP_PORT_CopyFlag_Size   1

#define ADDR_light_APN_IP_PORT_Copy         (ADDR_light_APN_IP_PORT_CopyFlag + ADDR_light_APN_IP_PORT_CopyFlag_Size)
#define ADDR_light_APN_IP_PORT_Copy_Size    (ADDR_mainServer_apn_Size + ADDR_mainServer_username_Size + ADDR_mainServer_password_Size + ADDR_mainServer_ip_Size + \
                                             ADDR_backServer_apn_Size + ADDR_backServer_username_Size + ADDR_backServer_password_Size + ADDR_backServer_ip_Size + ADDR_tcp_port_Size)

#define BIT_LIGHT0 (1<<0)
#define BIT_LIGHT1 (1<<1)
#define BIT_LIGHT2 (1<<2)




/** 结构体类型的定义 **/

/** 服务器信息 **/
typedef struct {
	uint8_t            APN[64];                                 //主服务器APN
	uint8_t            username[64];                            //用户名
	uint8_t            password[64];                            //密码
	uint8_t            ip[64];                                  //ip
	uint8_t            port[64];                                //port
} ServerInfo;

/** 网络参数信息的定义 **/
typedef struct {
	uint32_t           heartbeat_interval;                           //心跳发送时间间隔
	uint32_t           tcp_overtime;                                 //路灯TCP超时时间间隔
	uint32_t           tcp_retransmission_times;                     //TCP重传次数
	uint32_t           tcp_port;                                     //TCP通讯端口
	uint32_t           province_id;                                  //所在省ID
	uint32_t           city_id;                                      //所在城市ID
	uint8_t            phone_number[64];                             //手机号码
	
	ServerInfo         main;                                         //主服务器信息
	ServerInfo         back;                                         //备用服务器信息
	
	
} NetworkInfo;

extern NetworkInfo networkInfo;

/** 内部信息的定义 **/
typedef struct{

  uint8_t             version[3];                                    //版本信息：byte[0]:硬件版本，byte[1]:程序版本，byte[2]:协议版本
	uint8_t             addr[5];                                       //单灯地址
	uint32_t            lamppost_number;                               //灯杆编号
	uint32_t            lat;                                           //经度
	uint32_t            lng;                                           //纬度
	uint8_t             light_count;                                   //灯盏数量
	uint8_t             light_order;                                   //灯输出顺序,bit0~1:灯1，bit2~3:灯2：bit4~5:灯3，bit:6~7:灯4
	uint32_t            alarm_ignore;                                  //报警屏蔽字，与单灯报警标志相对应；相应位为1,则相应报警屏蔽
	uint32_t            alarm_key;                                     //关键标识，与单灯报警标志相对应；相应位为1，则为关键报警
	uint8_t             leakage_enable;                                //漏电保护启用标志，0x00:启用，0x01~0xFF：禁用
	uint16_t            leakage_I;                                     //漏电电流阀值，mA
	uint16_t            leakage_OFF_time;                              //漏电极限不驱动时间，持续时间超过该值，则关断输出，单位ms
	uint16_t            leakage_ON_time;                               //漏电延时重合闸时间, 持续时间超过该值，则开合输出，单位ms
	uint8_t             leakage_V;                                     //漏电电压阀值，单位V
	uint8_t             latlng_ONOFF_enable;                           //经纬度开关时间启用标志,0:禁用，1:启用
	uint8_t             alarm_interval;                                //报警时间间隔，1~60，默认5，单位min
	uint8_t             C_alarm_PF;                                    //电容故障报警功率因数，单位0.01
	uint8_t             C_normal_PF;                                   //电容故障恢复功率因数，单位0.01
	uint8_t             I_alarm_tooBig;                                //电流过大报警限值，单位0.1A
	uint8_t             I_normal_tooBig;                               //电流过大恢复限值，单位0.1A
	uint8_t             P_alarm_tooBig;                                //功率过大报警限值，单位10W
	uint8_t             P_normal_tooBig;                               //功率过大报警恢复限值，单位10W
	uint8_t             P_alarm_tooSmall;                              //功率过小报警限值，单位10W
	uint8_t             P_norm_tooSmall;                               //功率过小报警恢复限值，单位10W
	uint8_t             V_alarm;                                       //电压报警限值，单位V
	uint8_t             lock_min;                                      //数据冻结密度，0：不冻结,1:15min,2:30min,3:60min,其他：备用
	uint16_t            I_tooBig_project_delay_time;                   //开灯后电流过大保护延迟时间，0:禁用，单位s

} InnerInfo;

extern InnerInfo innerInfo;

typedef struct {
	uint32_t            start;                               //数据帧头下标
	uint32_t            size;                                //数据帧长度
} Frame;



/** 单灯信息 **/

#define LIGHT_MAX_COUNT 3    //每个灯杆最多路灯数量，下标从0开始

typedef struct{

	uint8_t             status;                             //单灯开关灯状态,灯状态,按照位表示灯状态,第0位:表示灯1,1：表示灯2,2表示灯3
	uint8_t             pre_status;                         //前一次开关灯状态
	
	uint8_t             test_index;                         //测试序号
	
	uint8_t             flag_login;                         //判断是否登录到中间层,0:未登录,1:登录
	uint8_t             first_login;                        //第一次登录
	uint8_t             flag_fault;                         //0x00:表示没有故障，0x01:表示有故障
	uint8_t             flag_record;                        //0:表示没有记录过, 1:表示已经记录过
	uint8_t             flag_testing;                       //0:尚未测试/测试成功, 1:测试中 
	uint8_t             flag_testing_finished;              //表示是否测试完一个周期，0：未完成，1：完成
	uint8_t             flag_counting;                      //计量计数是否结束，0:未结束，1：结束
	
	/*====================================================
	** 电量采集
	** 最多采集4盏灯的数据
	** 存放数据的顺序:漏电电压1byte 漏电电流2byte
	** 灯1序号1byte 电压V1byte 电流2byte 有功功率2byte
	** 灯2序号1byte 电压V1byte 电流2byte 有功功率2byte
	** 灯3序号1byte 电压V1byte 电流2byte 有功功率2byte
	**====================================================*/
	uint8_t             item[21];
	uint8_t             percent[4];                          //调光百分比
	uint8_t             mode;                                //控制模式，0：自动，1：手动，2~255:保留
	uint32_t            tick_heartbeat;                      //心跳时间戳
	uint32_t            tick_upload_version;                 //上传版本信息的时间戳
	uint32_t            tick_last_rec;                       //最后一次接收到【路灯管理处数据帧】的时间戳
	uint32_t            tick_testI;                          //检测电流的时间戳
	uint32_t            tick_testV;                          //检测电压时间戳
	uint32_t            tick_login;                          //登录时间戳
	
	Frame               frame;                               //数据帧
	
}SingleLamp;

extern SingleLamp SL;

typedef struct {

	uint32_t VI_frequency;                           //电压/电流频率
	uint32_t P_frequency;                           //功率频率
	
	uint32_t V_value;                                     //电压V
	uint32_t I_value;                                     //电流mA
	uint32_t P_value;                                     //功率W
	
} VIP;

extern VIP vip0,vip1,vip2;                          //灯0，灯1，灯2的测试数据

/*********************************************************
//ADC1通道的采样数据 , Channel0:漏电电流，Channel1:灯杆电压  
多通道轮流采集，所以数据分布是
C0 C1 C0 C1 C0 C1 ...... 如此分布
**********************************************************/
#define ADC_SAMPLE_SIZE 20
extern uint32_t adc1_sample[ADC_SAMPLE_SIZE];                    

/** 串口接收数据信息 **/
#define UART_BUFFER_MAX_LENGTH 1024

typedef struct {

	uint32_t            MAX_LENGTH;                          //串口接收最大长度
	uint8_t   *         data;                                //数组接收内容
	uint32_t            index;                               //游标
	uint32_t            length;                              //当前已接收数据长度
	uint8_t             idle;                                //当前是否空闲
	uint8_t             sending;                             //发送中
	
} UartBuffer;

extern UartBuffer uartBuffer1,uartBuffer3;


/** TCP连接信息 **/
typedef struct {
  
	uint8_t              status;                             //0:连接失败，1：连接成功
	
	uint8_t              connected_str[50];                  //连接成功时的字符串
	uint32_t             connected_str_length;               //连接成功时的字符串长度
	uint8_t              closed_str[50];                     //连接失败时的字符串
	uint32_t             closed_str_length;                  //连接失败时的字符串长度
	
	uint32_t             tick_closed;                        //TCP断开时的时间戳

} TcpInfo;

extern TcpInfo tcp0,tcp1;


extern uint8_t global_frame[];

/**  Debug 串口 ----------------------------------------------------------**/

extern uint32_t flash_addr_offset;
extern uint32_t frame_size;


/** NB参数  ------------------------------------------------------------------------- **/

typedef struct {
	
	uint8_t             status;                        //模块当前的状态
	uint32_t            tick_check;                    //检查后的时间点
	uint8_t             times_check;                   //网络状态检查次数
	
} LTE;

extern LTE lte;

/** 设备升级 ------------------------------------------------------------ **/
extern uint32_t crc_data[];

#define LD_OPERATOR_LOG_MAX 100    /** 路灯事件日志记录最大数量 **/
#define LD_OPERATOR_LOG_SIZE 7      /** 路灯事件日志记录单条长度 **/

#define LD_STATUS_LOG_MAX 400    /** 路灯状态日志记录最大数量 **/
#define LD_STATUS_LOG_SIZE 13      /** 路灯状态日志记录单条长度 **/



#endif
