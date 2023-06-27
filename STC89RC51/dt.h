#include <reg52.h>
#include "delay.h"
#include "intrins.h"
#include "math.h"
#include "lcd.h"

int T=0;				//ʵʱ�¶�
sbit DH= P3^4; 	// IO������DHT11

void DHT11_init();				//DHT11��ʼ����������
char Read_Data_From_DHT();//��ȡDHT11�¶Ⱥ���
void shows(char count); 	//����ȡ�����¶ȴ�ӡ����Ļ�ϵĺ���
	
char datas[5];//������¼��DHT11��������5���ֽ�����

void DHT11_init()//DHT11��ʼ����������
{
	DH = 1;
	DH = 0;
	delay_ms(30);//��ʱ30ms
	DH = 1;
	while(DH);
	while(!DH);
	while(DH);
}


char Read_Data_From_DHT()//��ȡDHT11�¶Ⱥ���
{
	int i;//��
	int j;//ÿһ�ֶ����ٴ�
	char tmp;
	char flag;
	DHT11_init();//DHT11��ʼ������
	for(i= 0;i < 5;i++)
	{
		for(j=0;j<8;j++)
		{
			while(!DH);
			delay_us(15);//��Ч���ݶ��Ǹߵ�ƽ������ʱ�䲻һ��
			if(DH == 1)
			{
				flag = 1;
				while(DH);
			}
			else
			{	
				flag = 0;
			} 
			tmp = tmp << 1;
			tmp |= flag;
		}
		datas[i] = tmp;
	}
	return datas[2];//����Ҫ���¶�����λ����
}


void shows(char count) //����ȡ�����¶ȴ�ӡ����Ļ�ϵĺ���
{
	  T=count;//��¼ʵʱ�¶�
    
		datas[0]=count/10;//ʮλ��
		datas[1]=count%10;//��λ��
		
		write_com(0x80+6);//�ӵڶ��е�6λ��ʼд
		write_data(datas[0]+'0');//��ӡ����Ļ��
		write_data(datas[1]+'0');//��ӡ����Ļ��
    write_data(0xDF);	
		write_data('C');//��ӡ���϶ȵ�λ
}

