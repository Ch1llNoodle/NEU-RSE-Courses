/**
 * @brief: ������ʾ
 * @author: ��껼�
 * @date:2019-12-7
 * 
 * */
#include <reg52.h>

xdata unsigned char DIS_PORT _at_ 0x8004;
xdata unsigned char DIS_CS_PORT _at_ 0x8002;


unsigned char code dis[]={0x3f,0x06,0x5b,0x4f, 0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0}; //16������ʾ

unsigned char num[6]={4,2,3,4,5,6};  //�ı����������� ��Ӧ�ı���ʾ����

void delayms(unsigned int tt)		//@12.000MHz
{
	unsigned char i, j;
    while(--tt)
    {
        i = 2;
        j = 239;
        do
        {
            while (--j);
        } while (--i);
    }
}

//��ʾ��������Ҫ���ϵ��ã�����һ�ν���һ��ˢ��
void display()
{
    char i;
    for (i = 0; i < 6; i++)
    {
        DIS_PORT = 0;  //����ʾ����ֹ��Ӱ
        DIS_CS_PORT = 0x01 << i; //ѡ��ˢ�µ�����ܣ�����λ�룩
        DIS_PORT = dis[num[i]];  //������ʾ�ַ�

        delayms(2);
    }
}

void main()
{

    while (1)
    {
        display();
    }

}
