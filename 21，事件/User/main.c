/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   GPIO���--ʹ�ù̼������LED��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"
#include "board_init.h"


/*
*************************************************************************
*                               ����
*************************************************************************
*/
/* �����߳̿��ƿ� */
static rt_thread_t receive_thread = RT_NULL;
static rt_thread_t send_thread = RT_NULL;
/* �����¼����ƿ� */
static rt_event_t test_event = RT_NULL;

/************************* ȫ�ֱ������� ****************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩȫ�ֱ�����
 */
#define KEY1_EVENT  (0x01 << 0)//�����¼������λ0
#define KEY2_EVENT  (0x01 << 1)//�����¼������λ1

/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void receive_thread_entry(void* parameter);
static void send_thread_entry(void* parameter);

/*
*************************************************************************
*                             main ����
*************************************************************************
*/
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
    /* 
	 * ������Ӳ����ʼ����RTTϵͳ��ʼ���Ѿ���main����֮ǰ��ɣ�
	 * ����component.c�ļ��е�rtthread_startup()����������ˡ�
	 * ������main�����У�ֻ��Ҫ�����̺߳������̼߳��ɡ�
	 */
	rt_kprintf("����һ��[Ұ��]-STM32F407-����-RTT�¼���־��ʵ�飡\n");
   /* ����һ���¼� */
	test_event = rt_event_create("test_event",/* �¼���־������ */
                        RT_IPC_FLAG_PRIO); /* �¼�ģʽ FIFO(0x00)*/
  if (test_event != RT_NULL)
    rt_kprintf("�¼������ɹ���\n\n");
    
	receive_thread =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "receive",              /* �߳����� */
                      receive_thread_entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      512,                 /* �߳�ջ��С */
                      3,                   /* �̵߳����ȼ� */
                      20);                 /* �߳�ʱ��Ƭ */
                   
    /* �����̣߳��������� */
   if (receive_thread != RT_NULL)
        rt_thread_startup(receive_thread);
    else
        return -1;
    
  send_thread =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "send",              /* �߳����� */
                      send_thread_entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      512,                 /* �߳�ջ��С */
                      2,                   /* �̵߳����ȼ� */
                      20);                 /* �߳�ʱ��Ƭ */
                   
    /* �����̣߳��������� */
   if (send_thread != RT_NULL)
        rt_thread_startup(send_thread);
    else
        return -1;
}

/*
*************************************************************************
*                             �̶߳���
*************************************************************************
*/

static void receive_thread_entry(void* parameter)
{		
  rt_uint32_t recved;
  /* ������һ������ѭ�������ܷ��� */
  while(1)
	{
			/* �ȴ������¼���־ */
     rt_event_recv(test_event,  /* �¼������� */
                   KEY1_EVENT|KEY2_EVENT,/* �����̸߳���Ȥ���¼� */
                   RT_EVENT_FLAG_AND|RT_EVENT_FLAG_CLEAR,/* ����ѡ�� */
                   RT_WAITING_FOREVER,/* ָ����ʱ�¼�,һֱ�� */
                   &recved);    /* ָ����յ����¼� */
      if(recved == (KEY1_EVENT|KEY2_EVENT)) /* ���������ɲ�����ȷ */
      {
        rt_kprintf ( "Key1��Key2������\n");		
        LED1_TOGGLE;       //LED1	��ת
      }
      else
        rt_kprintf ( "�¼�����\n");	
  }
}

static void send_thread_entry(void* parameter)
{	
    /* ������һ������ѭ�������ܷ��� */
  while (1)
  {
    if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON )       //���KEY2������
		{
      rt_kprintf ( "KEY1������\n" );
			/* ����һ���¼�1 */
			rt_event_send(test_event,KEY1_EVENT);    					
		}
    
		if( Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON )       //���KEY2������
		{
      rt_kprintf ( "KEY2������\n" );	
			/* ����һ���¼�2 */
			rt_event_send(test_event,KEY2_EVENT);    				
		}
		rt_thread_delay(20);     //ÿ20msɨ��һ��		
  }
}
/********************************END OF FILE****************************/
