#include <reg51.h>

//����ӿ�

xdata unsigned char KEY_CS_PORT _at_ 0x8002; //�����нӿ�
xdata unsigned char KEY_PORT _at_ 0x8001;    //������


//���������Կ����޸ļ�ֵ���� 16��ӦɶҲ����ʾ  ������Ӧ������ֵ
unsigned char code key_value[6][4] = {{16, 16, 16, 16}, {16, 16, 16, 16}, {0x0d, 0x0c, 0x0b, 0x0a}, {0x0e, 3, 6, 9}, {0x0f, 2, 5, 8}, {0, 1, 4, 7}};

//������ѡ��� ����ѭ��ɨ��ʱ��˿ڸ�ֵ��0����ѡ�и���
unsigned char code key_cs[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};

//����ɨ�躯��
unsigned char keyscan()
{
    char i;
    //DIS_PORT = 0;  //����ʾ ���ڸ���  ��ֹ��ͻ
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
                        // //������ʾ���������ⰴ�°���ʱ����������
                        // display(); 
                        // //����ѡ����������Ϊ��ǰɨ����
                        // KEY_CS_PORT = key_cs[i];  
                    };
                    return key_value[i][0];
                    break;
                case 0x0d://�ڶ��а���
                    while (KEY_PORT != 0x0f)  //���ּ�⣬��ֹ��η���
                    {
                        // //������ʾ���������ⰴ�°���ʱ����������
                        // display();  
                        // //����ѡ����������Ϊ��ǰɨ����           
                        // KEY_CS_PORT = key_cs[i]; 
                    };
                    return key_value[i][1];
                    break;
                case 0x0b: //�����а���
                    while (KEY_PORT != 0x0f)  //���ּ�⣬��ֹ��η���
                    {
                        // //������ʾ���������ⰴ�°���ʱ����������
                        // display();  
                        //  //����ѡ����������Ϊ��ǰɨ����
                        // KEY_CS_PORT = key_cs[i]; 
                    };
                    return key_value[i][2];
                    break;
                case 0x07: //�����а���
                    while (KEY_PORT != 0x0f)  //���ּ�⣬��ֹ��η���
                    {
                        // display();               
                        // KEY_CS_PORT = key_cs[i];  
                    };
                    return key_value[i][3];
                    break;
                default:  //������߶������ͬʱ����
                    while (KEY_PORT != 0x0f)  //���ּ�⣬��ֹ��η���
                    {
                        // display();
                        // KEY_CS_PORT = key_cs[i];
                    };
                    return 255;
                }
            }
        }
    }
    return 255;  //����255��ʾɶҲû����
}