#include <reg52.h>

#define STEP 8              //��λ��
#define DELAY_FACTOR 5     //��ʱϵ����1*DELAY_FACTOR--8*DELAY_FACTOR��
 //��λ��
unsigned char code motor_state[STEP] = {0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09}; 

sbit start_button = P3^3;  //������ͣ�ӿ�
sbit rotation = P3^4;      //������ת����

void delay1ms(unsigned int tt)      //@12.000MHz
{
    unsigned char i, j;

    while(--tt)
    {
        i = 2;
        j = 239;
        do
        {
            while (--j);
        }
        while (--i);
    }
}

unsigned int speed_get(unsigned char i)  //����P3��״̬�趨�ٶ�
{
    unsigned char speed = i&0x07;       //ֻʹ�õ���λȷ������λ��û�и���
    speed +=1;
    return speed *DELAY_FACTOR  ;
}

void main()
{
    char i;  //��λ��ű���
    unsigned int speed;
    while(1)
    {
        if(start_button)
        {
            P1=motor_state[i];
            speed = speed_get(P3);   
            delay1ms(speed);

            //����������Ա�֤�����л���ת����
            if(rotation)
            {
                i++;
                if(i>=STEP)i=0;
            }
            else
            {
                i--;
                if(i<0)i=(STEP -1);
            }
        }

    }
}
