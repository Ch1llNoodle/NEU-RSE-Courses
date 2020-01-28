/**
 * @brief: �����շ����������ɨ�衢������ʾ
 * ���ն��뷢�Ͷ�һ��
 * @author: ��껼�
 * @date:2019-12-7
 * 
 * Using GBK encoding
 * */

#include <reg51.h>

//����ӿ�
xdata unsigned char DIS_PORT _at_ 0x8004;    //��ʾ��λ
xdata unsigned char DIS_CS_PORT _at_ 0x8002; //��ʾλ��
xdata unsigned char KEY_CS_PORT _at_ 0x8002; //�����нӿ�
xdata unsigned char KEY_PORT _at_ 0x8001;    //������

//unsigned char code dis_cs[]={1,2,4,8,16,32};
//����ܶ����0-9 A-F ���һ������ɶҲ����ʾ
unsigned char code dis[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0};
//���������Կ����޸ļ�ֵ���� 16��ӦɶҲ����ʾ  ������Ӧ������ֵ
unsigned char code key_value[6][4] = {{16, 16, 16, 16}, {16, 16, 16, 16}, {0x0d, 0x0c, 0x0b, 0x0a}, {0x0e, 3, 6, 9}, {0x0f, 2, 5, 8}, {0, 1, 4, 7}};

//������ѡ��� ����ѭ��ɨ��ʱ��˿ڸ�ֵ��0����ѡ�и���
unsigned char code key_cs[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};
//�������ʾ���黺�棬ֻҪ����������鼴����ʾ��Ӧ������  16��ʾɶҲ����
unsigned char num[6] = {0, 16, 16, 16, 16, 16};

void delayms(unsigned int tt) //@12.000MHz
{
    unsigned char i, j;
    while (--tt)
    {
        i = 2;
        j = 239;
        do
        {
            while (--j)
                ;
        } while (--i);
    }
}

//���ڳ�ʼ�� 9600 ȫ˫��
void uart_init()
{

    TMOD = 0x20;
    SCON = 0x50;
    //TH1=256-(12000000/(384*9600));
    //TL1=256-(12000000/(384*9600));
    TH1 = 0xfd;
    TL1 = 0xfd;
    EA = 1;
    ES = 1;
    TR1 = 1;
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

//����ɨ�躯��
unsigned char keyscan()
{
    char i;
    DIS_PORT = 0;  //����ʾ ���ڸ���  ��ֹ��ͻ
    //ɨ������
    for (i = 0; i < 6; i++)
    {
        KEY_CS_PORT = key_cs[i];//ɨ�赱ǰ�е�IO������ǰ��IO����Ϊ�͵�ƽ

        if (KEY_PORT != 0x0F)  //�а�������
        {
            delayms(5);  //����
            if (KEY_PORT != 0x0F)
            {
                switch (KEY_PORT)
                {
                case 0x0e://��һ�а���
                    while (KEY_PORT != 0x0f)  //���ּ�⣬��ֹ��η���
                    {
                        display();           //������ʾ���������ⰴ�°���ʱ����������
                        KEY_CS_PORT = key_cs[i];  //����ѡ����������Ϊ��ǰɨ����
                    };
                    return key_value[i][0];
                    break;
                case 0x0d://�ڶ��а���
                    while (KEY_PORT != 0x0f)  //���ּ�⣬��ֹ��η���
                    {
                        display();             //������ʾ���������ⰴ�°���ʱ����������
                        KEY_CS_PORT = key_cs[i]; //����ѡ����������Ϊ��ǰɨ����
                    };
                    return key_value[i][1];
                    break;
                case 0x0b: //�����а���
                    while (KEY_PORT != 0x0f)  //���ּ�⣬��ֹ��η���
                    {
                        display();              //������ʾ���������ⰴ�°���ʱ����������
                        KEY_CS_PORT = key_cs[i];  //����ѡ����������Ϊ��ǰɨ����
                    };
                    return key_value[i][2];
                    break;
                case 0x07: //�����а���
                    while (KEY_PORT != 0x0f)  //���ּ�⣬��ֹ��η���
                    {
                        display();                //������ʾ���������ⰴ�°���ʱ����������
                        KEY_CS_PORT = key_cs[i];  //����ѡ����������Ϊ��ǰɨ���У����ں������ּ��
                    };
                    return key_value[i][3];
                    break;
                default:  //������߶������ͬʱ����
                    while (KEY_PORT != 0x0f)  //���ּ�⣬��ֹ��η���
                    {
                        display();
                        KEY_CS_PORT = key_cs[i];
                    };
                    return 255;
                }
            }
        }
    }
    return 255;  //����255��ʾɶҲû����
}

void main()
{
    int i;
    unsigned char a = 255;
    uart_init();
    while (1)
    {
        display();

        a = keyscan();
        //�а������·�������
        if (a != 255)
        {
            SBUF = a;  
        }
    }
}

//�����жϺ���
void UART() interrupt 4
{
    char i;
    if (RI == 1) //������յ��������������
    {
        //����ʾ������ǰƽ�� �µ����ݷ���0�������
        for (i = 6; i > 0; i--)
        {
            num[i] = num[i - 1];
        }

        num[0] = SBUF; //ȡ������
        RI = 0;        //�����־λ
    }
    if (TI == 1) //����������
    {
        TI = 0; //�����־λ
    }
}
