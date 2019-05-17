#include "rtcUtil.h"
#include "systemUtil.h"

#include "rtc.h"

_calendar_obj calendar;				//ʱ�ӽṹ�� 

static uint8_t mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31}; 

uint8_t MY_RTC_Init(RTC_HandleTypeDef *hrtc)
{
  
  hrtc->Instance = RTC;
  hrtc->Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc->Init.OutPut = RTC_OUTPUTSOURCE_NONE;
  //����ǲ��ǵ�һ������ʱ��
  if(HAL_RTCEx_BKUPRead(hrtc,RTC_BKP_DR1) != 0x5A5A)//��ָ���ĺ󱸼Ĵ����ж�������:��������д���ָ�����ݲ����
  {
    
    if (HAL_RTC_Init(hrtc) != HAL_OK)
    {
      Error_Handler();
    }
    //HAL_RTCEx_SetSecond_IT(&hrtc);//ʹ��RTC���ж�
    RTC_Set(hrtc,2000,1,1,0,0,0);
    HAL_RTCEx_BKUPWrite(hrtc,RTC_BKP_DR1,0x5A5A);
    
  }
  else
  {
    if (HAL_RTC_Init(hrtc) != HAL_OK)
    {
      Error_Handler();
    }
    //HAL_RTCEx_SetSecond_IT(&hrtc);
  }
  RTC_Get(hrtc);//����ʱ��
  return 0; 
}

//�ж��Ƿ������꺯��
//�·�   1  2  3  4  5  6  7  8  9  10 11 12
//����   31 29 31 30 31 30 31 31 30 31 30 31
//������ 31 28 31 30 31 30 31 31 30 31 30 31
//����:���
//���:������ǲ�������.1,��.0,����
uint8_t Is_Leap_Year(uint16_t year)
{			  
	if(year%4==0) //�����ܱ�4����
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)
        return 1;//�����00��β,��Ҫ�ܱ�400����    
			else 
        return 0;   
		}
    else 
      return 1;   
	}
  else 
    return 0;	
}	

//����ʱ��
//�������ʱ��ת��Ϊ����
//��1970��1��1��Ϊ��׼
//1970~2099��Ϊ�Ϸ����
//����ֵ:0,�ɹ�;����:�������.
//�·����ݱ� 			
//u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //���������ݱ�	  
//ƽ����·����ڱ�
//const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31}; 
HAL_StatusTypeDef RTC_Set(RTC_HandleTypeDef *hrtc,uint16_t syear,uint8_t smon,uint8_t sday,uint8_t hour,uint8_t min,uint8_t sec)
{
  uint16_t t;
	uint32_t seccount=0;
  if(syear<2000||syear>2129)  return HAL_ERROR;	   
		
	for(t=2000;t<syear;t++)	//���������ݵ��������
	{
		if(Is_Leap_Year(t))
      seccount+=31622400;//�����������
		else 
      seccount+=31536000;			  //ƽ���������
	}
	
	smon-=1;
	for(t=0;t<smon;t++)	   //��ǰ���·ݵ����������
	{
		seccount+=(uint32_t)mon_table[t]*86400;//�·����������
		if(Is_Leap_Year(syear)&&t==1)
      seccount+=86400;//����2�·�����һ���������   
	}
	seccount+=(uint32_t)(sday-1)*86400;//��ǰ�����ڵ���������� 
	seccount+=(uint32_t)hour*3600;//Сʱ������
  seccount+=(uint32_t)min*60;	 //����������
	seccount+=sec;//�������Ӽ���ȥ  
  hrtc->State = HAL_RTC_STATE_BUSY;
	
  __HAL_LOCK(hrtc);
  if (RTC_SetCounter(hrtc, seccount) != HAL_OK)
  {
    hrtc->State = HAL_RTC_STATE_ERROR;
    return HAL_ERROR;	
  }
  else
  {
    hrtc->State = HAL_RTC_STATE_READY;
  }
  __HAL_UNLOCK(hrtc); 
	
  return HAL_OK;
  
}

void RTC_Get(RTC_HandleTypeDef *hrtc)
{
  static uint16_t daycnt=0;
	uint32_t timecount=0; 
	uint32_t temp=0;
	uint16_t temp1=0;	  
	
  timecount=RTC_ReadTimeCounter(hrtc);
 	temp=timecount/86400;   //�õ�����(��������Ӧ��)
	if(daycnt!=temp)//����һ����
	{	  
		daycnt=temp;
		temp1=2000;	//��2000�꿪ʼ
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//������
			{
				if(temp>=366)
          temp-=366;//�����������
				else 
        {
          temp1++;
          break;
        }  
			}
			else 
        temp-=365;	  //ƽ�� 
			temp1++;  
		}   
		
		calendar.w_year=temp1;//�õ����
		temp1=0;
		while(temp>=28)//������һ����
		{
			if(Is_Leap_Year(calendar.w_year)&&temp1==1)//�����ǲ�������/2�·�
			{
				if(temp>=29)
          temp-=29;//�����������
				else 
          break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])
          temp-=mon_table[temp1];//ƽ��
				else 
          break;
			}
			temp1++;  
		}
		calendar.w_month=temp1+1;	
		calendar.w_date=temp+1;  	
	}
	temp=timecount%86400;     		//�õ�������   	  	   
	calendar.hour=temp/3600;     	//Сʱ
	calendar.min=(temp%3600)/60; 	//����	
	calendar.sec=(temp%3600)%60; 	//����
	calendar.week=RTC_Get_Week(calendar.w_year,calendar.w_month,calendar.w_date);//��ȡ����   
	
}



static HAL_StatusTypeDef RTC_SetCounter(RTC_HandleTypeDef* hrtc, uint32_t TimeCounter)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Set Initialization mode */
  if(RTC_EnterInitMode(hrtc) != HAL_OK)
  {
    status = HAL_ERROR;
  } 
  else
  {
    /* Set RTC COUNTER MSB word */
    WRITE_REG(hrtc->Instance->CNTH, (TimeCounter >> 16));
    /* Set RTC COUNTER LSB word */
    WRITE_REG(hrtc->Instance->CNTL, (TimeCounter & RTC_CNTL_RTC_CNT));
    
    /* Wait for synchro */
    if(RTC_ExitInitMode(hrtc) != HAL_OK)
    { 
      status = HAL_ERROR;
    }
  }
  
  return status;
}

uint32_t RTC_GETTICK(){
	
}

static uint32_t RTC_ReadTimeCounter(RTC_HandleTypeDef* hrtc)
{
  uint16_t high1 = 0, high2 = 0, low = 0;
  uint32_t timecounter = 0;
  
  high1 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);
  low   = READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT);
  high2 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);
  
  if (high1 != high2)
  { /* In this case the counter roll over during reading of CNTL and CNTH registers, 
    read again CNTL register then return the counter value */
    timecounter = (((uint32_t) high2 << 16 ) | READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT));
  }
  else
  { /* No counter roll over during reading of CNTL and CNTH registers, counter 
    value is equal to first value of CNTL and CNTH */
    timecounter = (((uint32_t) high1 << 16 ) | low);
  }
  
  return timecounter;
}
static HAL_StatusTypeDef RTC_EnterInitMode(RTC_HandleTypeDef* hrtc)
{
  uint32_t tickstart = 0;
  
  tickstart = HAL_GetTick();
  /* Wait till RTC is in INIT state and if Time out is reached exit */
  while((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
  {
    if((HAL_GetTick() - tickstart) >  RTC_TIMEOUT_VALUE)
    {       
      return HAL_TIMEOUT;
    } 
  }
  
  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);
  
  
  return HAL_OK;  
}
static HAL_StatusTypeDef RTC_ExitInitMode(RTC_HandleTypeDef* hrtc)
{
  uint32_t tickstart = 0;
  
  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
  
  tickstart = HAL_GetTick();
  /* Wait till RTC is in INIT state and if Time out is reached exit */
  while((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
  {
    if((HAL_GetTick() - tickstart) >  RTC_TIMEOUT_VALUE)
    {       
      return HAL_TIMEOUT;
    } 
  }
  
  return HAL_OK;  
}

//������������ڼ�
//��������:���빫�����ڵõ�����(ֻ����2000-2129��)
//������������������� 
//����ֵ�����ں�
uint8_t RTC_Get_Week(uint16_t year,uint8_t month,uint8_t day)
{	
  int iweek = 0;
	uint8_t y,c;
  uint8_t m,d;
  if(month == 1 || month == 2)
  {
    c = (year-1)/100;
    y = (year-1)%100;
    m = month+12;
    
  }
  else
  {
    c = year/100;
    y = year%100;
    m = month;        
  }
  d = day;
  iweek = y +y/4 +c/4 - 2*c +26*(m+1)/10 + d - 1;
  iweek = iweek >= 0 ? (iweek%7):(iweek%7 + 7);
//  if(iweek == 0)
//  {
//    iweek = 7;
//  }
  return iweek;
}	

void printRTCTime(void){
	printf("*****************************************************\r\n");
	printf("**   RTC��ǰʱ�� : %04d-%02d-%02d %02d:%02d:%02d   **\r\n",
		calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec
	);
	printf("*****************************************************\r\n");
}

/** ��ӡ��־��ʱ��ǰ�����ʱ�� **/
void printRTCTime_Log(void){
	printf("[ RTC��ǰʱ�� : %04d-%02d-%02d %02d:%02d:%02d ]  :  ",
		calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec
	);
}





