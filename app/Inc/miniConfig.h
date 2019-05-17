#ifndef __miniConfig_H__
#define __miniConfig_H__

#include "stm32f1xx_hal.h"


/**==================================================
--- ����汾 ---
Tang, Song, Yuan, Ming, Qing, Qiii, Chuu, Yann, Zhao, Hann, Weii, Qinn
=====================================================**/
#define VERSION "V1.1.1.20190325_Chuu"
#define RELEASE_NORMAL 1

/** ��������  ---------------------------------------------- **/

#define I 0
#define V 1
#define P 2


/** EEPROM�洢 --------------------------------------------- **/

/*=================================================================================== 
 *      EEPROM ��ز������趨  
 ====================================================================================*/
/********************************
 *  EEPROM �����ݵĴ洢�ṹ
 * 1.�ն�ID              6bytes
 * 2.������ID            5bytes
 * 3.�ն��ͺ�            8bytes
 * 4.���ص���ʼ����       2byte  BCD����
 * 5.���ص�ʱ��           366 * 3  =  1098  ,1440����(0x5A0),����ʱ�䣺06:30 -> 0x186,�ػ�ʱ�䣺17:30  -> 0x41A  ,���ػ�ʱ���ʾΪ:0x18641A
 * 
*********************************/

extern uint8_t equipmentID[] ;   //<----------- �ն�ID ------------
extern uint8_t manufacturerID[] ;   //<----------- ������ID ----------
extern uint8_t terminalModel[];   //<----------- �ն��ͺ� -----------
extern uint8_t ONOFF_startDate[];  //<---------------- ���ÿ��صƵ���ʼ���� 0x0A0A��ʾ��10��10�� -------------
extern uint8_t ONOFF_todayTime[];  //<---------------- ���տ��ص�ʱ�� -------------------
extern uint8_t light_ONOFF_datetime[];   //���صƲ���ʱ��

extern uint8_t TMP_ONOFF_startDate[];  //<---------------- ��ʱ���ص���ʼ���� -------------------
extern uint8_t TMP_ONOFF_DayCount[];  //<---------------- 0x00:��Ч  0x01~0xfe��Ч���� 0xff:һֱ��Ч -------------------
extern uint8_t TMP_ONOFF_time[];  //<---------------- ��ʱ���ص�ʱ�� -------------------



/**********************************************
 **                                          **
 **                ·�Ʋ���                   **
 **                                          **
***********************************************/

/***
��ʼ�ֽ�	�ֶ�	��������	������Ҫ��
0	�������ñ�־	BYTE	0x00 �����ã�0x01 ���ã�0x02~0xff δ֪
1	һ�׶�ʱ��	BCD[2]	BCD[0]ʱ ��BCD[1]��
3	һ�׶η�ֵ	BYTE[4]	����8.18.2
7	���׶�ʱ��	BCD[2]	
9	���׶η�ֵ	BYTE[4]	
13	���׶�ʱ��	BCD[2]	
15	���׶η�ֵ	BYTE[4]	
19	�Ľ׶�ʱ��	BCD[2]	
21	�Ľ׶η�ֵ	BYTE[4]	
25	��׶�ʱ��	BCD[2]	
27	��׶η�ֵ	BYTE[4]	 
****/
extern uint8_t dimmer[]; //<------- ������� --------------------

/**===================================================
*** �������ݲɼ�
***λ	����	����˵��
0	���ݹ���	��־ά���������������
1	��Դ����	��־ά���������������
2	�̵�������	��־ά���������������
3	����˿����	��־ά���������������
4	�洢оƬ����	��־ά���������������
5	ʱ��оƬ����	��־ά���������������
6	����ģ�����	��־ά���������������
7	�ڲ��������ù���	��־ά���������������
8	©�籨��	��־ά���������������
9	��������	��־ά���������������
10	ˮ������	��־ά���������������
11	�������󱨾�	��־ά���������������
12	���ʹ��󱨾�	��־ά���������������
13	���ʹ�С����	��־ά���������������
14~31	Ԥ��	

-------------------------------------------------------
��������
0x10	1	©�籣�����ñ�־��0x00���� 0x01~0xff����
0x11	2	©������ֵ����λmA
0x12	2	©�缫�޲�����ʱ�䣬����ʱ�䳬����ֵ����ض��������λms
0x13	2	©����ʱ�غ�բʱ�䣬����ʱ�䳬����ֵ���򿪺��������λms
0x14	1	©��ѹ��ֵ����λV
0x15	1	��γ�ȿ���ʱ�����ñ�־��0����  1����
0x16	1	���������������1~60��Ĭ��Ϊ1

0x21	1	���ݹ��ϱ�������������ֵ����λ0.01
0x22	1	���ݹ��ϻָ�����������ֵ����λ0.01
0x23	1	�������󱨾�������ֵ����λ0.1A
0x24	1	��������ָ�������ֵ����λ0.1A
0x25	1	���ʹ��󱨾���ֵ����λ10W
0x26	1	���ʹ���ָ���ֵ����λ10W
0x27	1	���ʹ�С������ֵ����λ10W
0x28	1	���ʹ�С�ָ���ֵ����λ10W
0x29	1	��ѹ������ֵ,��λV

0x30	1	���ݶ����ܶ�m(�洢��ʷ���ݵļ��ʱ��)������A.8.15.6
0x31	2	���ƺ�������󱣻��ӳ�ʱ�䣬0-�ù��ܽ�ֹ����λ��(s)


***===================================================*/

#define ALARM_MAX_COUNT 10         /** ���������������������������������ֵʱ���ϴ����� **/
typedef struct {
	uint32_t         value;                    //����ֵ
	uint32_t         tmp_value;                //��ʱ����ֵ
	uint32_t         tick_upload;              //�����ϱ���ʱ���
	uint8_t          count;                    //��������
	uint8_t          isFirst;                  //1����һ�α�����0���Ǳ���
	uint8_t          isCancel;                 //�����Ƿ�ȡ��
} AlarmInfo;

extern AlarmInfo alarmInfo;                  //������Ϣ


#define ALARM_DianRong   (1<<0) // 0x00000001   //���ݹ���
#define ALARM_GuangYuan  (1<<1) // 0x00000002   //��Դ����
#define ALARM_JiDianQi   (1<<2) // 0x00000004   //�̵�������
#define ALARM_BaoXianSi  (1<<3) // 0x00000008   //����˿����
#define ALARM_StorageChip (1<<4) // 0x00000010   //�洢оƬ����
#define ALARM_TimeChip    (1<<5) // 0x00000020   //ʱ��оƬ����
#define ALARM_SDMode      (1<<6) // 0x00000040   //����ģ�����
#define ALARM_InnerParam  (1<<7) // 0x00000080   //�ڲ��������ù���
#define ALARM_LouDian     (1<<8) // 0x00000100   //©�籨�� 
#define ALARM_FangDao     (1<<9) // 0x00000200   //����
#define ALARM_JinShui     (1<<10) // 0x00000400   //ˮ������
#define ALARM_iMoreThanMax (1<<11) // 0x00000800   //�������󱨾�
#define ALARM_pMoreThanMax (1<<12) // 0x00001000   //���ʹ��󱨾�
#define ALARM_pLessThanMin (1<<13) // 0x00002000   //���ʹ�С����


/*====================================================
 * ������ѹ�Լ����ʵĲο�ֵ ,  ����Ӧ�ĵ�����ѹ�Լ����ʵ�У׼ֵ
 * 1.�Ƿ��Ѿ�����  1byte   0:δ����, 1:�ѽ���
 * 2.I�ο�����     2bytes
 * 3.V�ο���ѹ     2bytes
 * 4.P�ο�����     2bytes
 * 5.I�����Ĳο�Ƶ��  2bytes
 * 6.V��ѹ�Ĳο�Ƶ��  2bytes
 * 7.P���ʵĲο�Ƶ��  2bytes
 * EEPROM�е�ַ˳�� :�Ƿ�У׼
 *                   ��0У׼����ֵ,��0У׼��ѹֵ,��0У׼����ֵ,��1У׼����ֵ,��1У׼��ѹֵ,��1У׼����ֵ,��2У׼����ֵ,��2У׼��ѹֵ,��2У׼����ֵ,
 *                   ��0У׼����Ƶ��,��0У׼��ѹƵ��,��0У׼����Ƶ��,��1У׼����Ƶ��,��1У׼��ѹƵ��,��1У׼����Ƶ��,��2У׼����Ƶ��,��2У׼��ѹƵ��,��2У׼����Ƶ��,
 =====================================================*/
extern uint8_t standard[];  //У׼����
extern uint8_t has_adjust;  //0:��ʾδУ׼, 1:��ʾ�Ѿ�У׼
extern uint32_t standard_IVP[] ;    //�����ĵ���ֵ,��ѹֵ,�Լ�����
extern uint32_t frequence_IVP[];  //��Ӧ��õ�У׼Ƶ��
extern uint32_t f_IVP;   //�����Եĵ�����ѹ���� Ƶ��
#define ADJUST_KEEP_TIME 3000   //У׼ʱ����ʱ������λms


/******************************************
**** �豸����ʱ�����
*******************************************/
extern uint8_t arr_totalRunningTime[];   //������ʱ��
extern uint32_t preRunningTime;     //�ϴδ洢ʱ����ʱ��
extern uint8_t arr_currentTime[];         //��ǰ����ʱ��
extern uint32_t dtRunningTime;      //��������һ�δ洢�Ĳ�ֵ

#define ADDR_equipmentID                   5
#define ADDR_equipmentID_Size              6

#define ADDR_manufacturerID                (ADDR_equipmentID + ADDR_equipmentID_Size)
#define ADDR_manufacturerID_Size           5

#define ADDR_terminalModel                 (ADDR_manufacturerID + ADDR_manufacturerID_Size)
#define ADDR_terminalModel_Size            8

#define ADDR_light_ONOFF_startDate         (ADDR_terminalModel + ADDR_terminalModel_Size)
#define ADDR_light_ONOFF_startDate_Size     2

#define light_ONOFF_datetime_SIZE           1098   //<----------- ���ص�ʱ�� -----------
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
#define ADDR_heartbeat_Size                 (4 + 1 + 4)  /** ����ID + �������� + ����ֵ **/

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
#define ADDR_light_operationLog_Size        700       /** 7*100  100��������־  **/

#define ADDR_light_statusLog_index          (ADDR_light_operationLog + ADDR_light_operationLog_Size)
#define ADDR_light_statusLog_index_Size     2

#define ADDR_light_statusLog                (ADDR_light_statusLog_index + ADDR_light_statusLog_index_Size)
#define ADDR_light_statusLog_Size           5200      /**  (1+12) * 400 ��·��״̬��־     **/


#define ADDR_light_APN_IP_PORT_CopyFlag        (ADDR_light_statusLog + ADDR_light_statusLog_Size + 10)
#define ADDR_light_APN_IP_PORT_CopyFlag_Size   1

#define ADDR_light_APN_IP_PORT_Copy         (ADDR_light_APN_IP_PORT_CopyFlag + ADDR_light_APN_IP_PORT_CopyFlag_Size)
#define ADDR_light_APN_IP_PORT_Copy_Size    (ADDR_mainServer_apn_Size + ADDR_mainServer_username_Size + ADDR_mainServer_password_Size + ADDR_mainServer_ip_Size + \
                                             ADDR_backServer_apn_Size + ADDR_backServer_username_Size + ADDR_backServer_password_Size + ADDR_backServer_ip_Size + ADDR_tcp_port_Size)

#define BIT_LIGHT0 (1<<0)
#define BIT_LIGHT1 (1<<1)
#define BIT_LIGHT2 (1<<2)




/** �ṹ�����͵Ķ��� **/

/** ��������Ϣ **/
typedef struct {
	uint8_t            APN[64];                                 //��������APN
	uint8_t            username[64];                            //�û���
	uint8_t            password[64];                            //����
	uint8_t            ip[64];                                  //ip
	uint8_t            port[64];                                //port
} ServerInfo;

/** ���������Ϣ�Ķ��� **/
typedef struct {
	uint32_t           heartbeat_interval;                           //��������ʱ����
	uint32_t           tcp_overtime;                                 //·��TCP��ʱʱ����
	uint32_t           tcp_retransmission_times;                     //TCP�ش�����
	uint32_t           tcp_port;                                     //TCPͨѶ�˿�
	uint32_t           province_id;                                  //����ʡID
	uint32_t           city_id;                                      //���ڳ���ID
	uint8_t            phone_number[64];                             //�ֻ�����
	
	ServerInfo         main;                                         //����������Ϣ
	ServerInfo         back;                                         //���÷�������Ϣ
	
	
} NetworkInfo;

extern NetworkInfo networkInfo;

/** �ڲ���Ϣ�Ķ��� **/
typedef struct{

  uint8_t             version[3];                                    //�汾��Ϣ��byte[0]:Ӳ���汾��byte[1]:����汾��byte[2]:Э��汾
	uint8_t             addr[5];                                       //���Ƶ�ַ
	uint32_t            lamppost_number;                               //�Ƹ˱��
	uint32_t            lat;                                           //����
	uint32_t            lng;                                           //γ��
	uint8_t             light_count;                                   //��յ����
	uint8_t             light_order;                                   //�����˳��,bit0~1:��1��bit2~3:��2��bit4~5:��3��bit:6~7:��4
	uint32_t            alarm_ignore;                                  //���������֣��뵥�Ʊ�����־���Ӧ����ӦλΪ1,����Ӧ��������
	uint32_t            alarm_key;                                     //�ؼ���ʶ���뵥�Ʊ�����־���Ӧ����ӦλΪ1����Ϊ�ؼ�����
	uint8_t             leakage_enable;                                //©�籣�����ñ�־��0x00:���ã�0x01~0xFF������
	uint16_t            leakage_I;                                     //©�������ֵ��mA
	uint16_t            leakage_OFF_time;                              //©�缫�޲�����ʱ�䣬����ʱ�䳬����ֵ����ض��������λms
	uint16_t            leakage_ON_time;                               //©����ʱ�غ�բʱ��, ����ʱ�䳬����ֵ���򿪺��������λms
	uint8_t             leakage_V;                                     //©���ѹ��ֵ����λV
	uint8_t             latlng_ONOFF_enable;                           //��γ�ȿ���ʱ�����ñ�־,0:���ã�1:����
	uint8_t             alarm_interval;                                //����ʱ������1~60��Ĭ��5����λmin
	uint8_t             C_alarm_PF;                                    //���ݹ��ϱ���������������λ0.01
	uint8_t             C_normal_PF;                                   //���ݹ��ϻָ�������������λ0.01
	uint8_t             I_alarm_tooBig;                                //�������󱨾���ֵ����λ0.1A
	uint8_t             I_normal_tooBig;                               //��������ָ���ֵ����λ0.1A
	uint8_t             P_alarm_tooBig;                                //���ʹ��󱨾���ֵ����λ10W
	uint8_t             P_normal_tooBig;                               //���ʹ��󱨾��ָ���ֵ����λ10W
	uint8_t             P_alarm_tooSmall;                              //���ʹ�С������ֵ����λ10W
	uint8_t             P_norm_tooSmall;                               //���ʹ�С�����ָ���ֵ����λ10W
	uint8_t             V_alarm;                                       //��ѹ������ֵ����λV
	uint8_t             lock_min;                                      //���ݶ����ܶȣ�0��������,1:15min,2:30min,3:60min,����������
	uint16_t            I_tooBig_project_delay_time;                   //���ƺ�������󱣻��ӳ�ʱ�䣬0:���ã���λs

} InnerInfo;

extern InnerInfo innerInfo;

typedef struct {
	uint32_t            start;                               //����֡ͷ�±�
	uint32_t            size;                                //����֡����
} Frame;



/** ������Ϣ **/

#define LIGHT_MAX_COUNT 3    //ÿ���Ƹ����·���������±��0��ʼ

typedef struct{

	uint8_t             status;                             //���ƿ��ص�״̬,��״̬,����λ��ʾ��״̬,��0λ:��ʾ��1,1����ʾ��2,2��ʾ��3
	uint8_t             pre_status;                         //ǰһ�ο��ص�״̬
	
	uint8_t             test_index;                         //�������
	
	uint8_t             flag_login;                         //�ж��Ƿ��¼���м��,0:δ��¼,1:��¼
	uint8_t             first_login;                        //��һ�ε�¼
	uint8_t             flag_fault;                         //0x00:��ʾû�й��ϣ�0x01:��ʾ�й���
	uint8_t             flag_record;                        //0:��ʾû�м�¼��, 1:��ʾ�Ѿ���¼��
	uint8_t             flag_testing;                       //0:��δ����/���Գɹ�, 1:������ 
	uint8_t             flag_testing_finished;              //��ʾ�Ƿ������һ�����ڣ�0��δ��ɣ�1�����
	uint8_t             flag_counting;                      //���������Ƿ������0:δ������1������
	
	/*====================================================
	** �����ɼ�
	** ���ɼ�4յ�Ƶ�����
	** ������ݵ�˳��:©���ѹ1byte ©�����2byte
	** ��1���1byte ��ѹV1byte ����2byte �й�����2byte
	** ��2���1byte ��ѹV1byte ����2byte �й�����2byte
	** ��3���1byte ��ѹV1byte ����2byte �й�����2byte
	**====================================================*/
	uint8_t             item[21];
	uint8_t             percent[4];                          //����ٷֱ�
	uint8_t             mode;                                //����ģʽ��0���Զ���1���ֶ���2~255:����
	uint32_t            tick_heartbeat;                      //����ʱ���
	uint32_t            tick_upload_version;                 //�ϴ��汾��Ϣ��ʱ���
	uint32_t            tick_last_rec;                       //���һ�ν��յ���·�ƹ�������֡����ʱ���
	uint32_t            tick_testI;                          //��������ʱ���
	uint32_t            tick_testV;                          //����ѹʱ���
	uint32_t            tick_login;                          //��¼ʱ���
	
	Frame               frame;                               //����֡
	
}SingleLamp;

extern SingleLamp SL;

typedef struct {

	uint32_t VI_frequency;                           //��ѹ/����Ƶ��
	uint32_t P_frequency;                           //����Ƶ��
	
	uint32_t V_value;                                     //��ѹV
	uint32_t I_value;                                     //����mA
	uint32_t P_value;                                     //����W
	
} VIP;

extern VIP vip0,vip1,vip2;                          //��0����1����2�Ĳ�������

/*********************************************************
//ADC1ͨ���Ĳ������� , Channel0:©�������Channel1:�Ƹ˵�ѹ  
��ͨ�������ɼ����������ݷֲ���
C0 C1 C0 C1 C0 C1 ...... ��˷ֲ�
**********************************************************/
#define ADC_SAMPLE_SIZE 20
extern uint32_t adc1_sample[ADC_SAMPLE_SIZE];                    

/** ���ڽ���������Ϣ **/
#define UART_BUFFER_MAX_LENGTH 1024

typedef struct {

	uint32_t            MAX_LENGTH;                          //���ڽ�����󳤶�
	uint8_t   *         data;                                //�����������
	uint32_t            index;                               //�α�
	uint32_t            length;                              //��ǰ�ѽ������ݳ���
	uint8_t             idle;                                //��ǰ�Ƿ����
	uint8_t             sending;                             //������
	
} UartBuffer;

extern UartBuffer uartBuffer1,uartBuffer3;


/** TCP������Ϣ **/
typedef struct {
  
	uint8_t              status;                             //0:����ʧ�ܣ�1�����ӳɹ�
	
	uint8_t              connected_str[50];                  //���ӳɹ�ʱ���ַ���
	uint32_t             connected_str_length;               //���ӳɹ�ʱ���ַ�������
	uint8_t              closed_str[50];                     //����ʧ��ʱ���ַ���
	uint32_t             closed_str_length;                  //����ʧ��ʱ���ַ�������
	
	uint32_t             tick_closed;                        //TCP�Ͽ�ʱ��ʱ���

} TcpInfo;

extern TcpInfo tcp0,tcp1;


extern uint8_t global_frame[];

/**  Debug ���� ----------------------------------------------------------**/

extern uint32_t flash_addr_offset;
extern uint32_t frame_size;


/** NB����  ------------------------------------------------------------------------- **/

typedef struct {
	
	uint8_t             status;                        //ģ�鵱ǰ��״̬
	uint32_t            tick_check;                    //�����ʱ���
	uint8_t             times_check;                   //����״̬������
	
} LTE;

extern LTE lte;

/** �豸���� ------------------------------------------------------------ **/
extern uint32_t crc_data[];

#define LD_OPERATOR_LOG_MAX 100    /** ·���¼���־��¼������� **/
#define LD_OPERATOR_LOG_SIZE 7      /** ·���¼���־��¼�������� **/

#define LD_STATUS_LOG_MAX 400    /** ·��״̬��־��¼������� **/
#define LD_STATUS_LOG_SIZE 13      /** ·��״̬��־��¼�������� **/



#endif
