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
/* �����ź������ƿ� */
static rt_sem_t test_sem = RT_NULL;

/************************* ȫ�ֱ������� ****************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩȫ�ֱ�����
 */
uint8_t ucValue [ 2 ] = { 0x00, 0x00 };

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
	rt_kprintf("����һ��[Ұ��]-STM32F407����-RTT��ֵ�ź���ͬ��ʵ�飡\n");
  rt_kprintf("ͬ���ɹ������Successful,��֮���Fail\n");
   /* ����һ���ź��� */
	test_sem = rt_sem_create("test_sem",/* �ź������� */
                     1,     /* �ź�����ʼֵ��Ĭ����һ���ź��� */
                     RT_IPC_FLAG_FIFO); /* �ź���ģʽ FIFO(0x00)*/
  if (test_sem != RT_NULL)
    rt_kprintf("�ź��������ɹ���\n\n");
    
	receive_thread =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "receive",            /* �߳����� */
                      receive_thread_entry, /* �߳���ں��� */
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
  /* ������һ������ѭ�������ܷ��� */
  while(1)
	{
		rt_sem_take(test_sem,	/* ��ȡ�ź��� */
                RT_WAITING_FOREVER); 	/* �ȴ�ʱ�䣺һֱ�� */
		if ( ucValue [ 0 ] == ucValue [ 1 ] )
		{ 			
			rt_kprintf ( "Successful\n" );			
		}
		else
		{
			rt_kprintf ( "Fail\n" );			
		}
		rt_sem_release(	test_sem	);   //�ͷŶ�ֵ�ź��� 
		
		rt_thread_delay ( 100 );  					      //ÿ1s��һ��		
  }
  
  
}

static void send_thread_entry(void* parameter)
{	
    /* ������һ������ѭ�������ܷ��� */
    while (1)
    {
			rt_sem_take(test_sem,	/* ��ȡ�ź��� */
                  RT_WAITING_FOREVER); /* �ȴ�ʱ�䣺һֱ�� */		
		ucValue [ 0 ] ++;		
		rt_thread_delay ( 100 );        	 /* ��ʱ100ms */		
		ucValue [ 1 ] ++;		
		rt_sem_release(	test_sem	);	//�ͷŶ�ֵ�ź���
		rt_thread_yield();  			//����ʣ��ʱ��Ƭ������һ�������л�	
    }
}

/********************************END OF FILE****************************/
