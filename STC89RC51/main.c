#include "reg52.h"
#include "key.h"
#include "lcd.h"
#include "dt.h"
#include "motor.h"

sbit heater=P3^7;//���Ƽ������Ŀ��ؽӿڿ���

void main()
{
	lcd_init();  //��ʼ��lcd��Ļ
	write_string(0,0,"Ture:         ");//��ӡ��һ��
	write_string(0,1,"Set :		     	");//��ӡ�ڶ���

	while(1)
	{
		shows(Read_Data_From_DHT());//��ȡ����ʾDS18B20��⵽���¶�
		key();//����״̬���
		if(T>set_t)//���ʵʱ�¶��Ƿ���������¶�
		{
			if(T-set_t>2)//��������¶��Ƿ����ʵʱ�¶�2
			{
				warning(1);//��������
			}
			motor_start();//��������
		}
		else
		{
			motor_stop();//ֹͣ����
		}
		if(T<set_t)//���ʵʱ�¶��Ƿ� ���������¶�
		{
			if(set_t-T>2)//��������¶��Ƿ����ʵʱ�¶�2
			{
				warning(2);//��������
			}
			heater=1;//����������
		}
		else
		{
			heater=0;//�رռ�����
		}
	}
}




	
	