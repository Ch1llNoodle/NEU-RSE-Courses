/**
 * brief:8255Aʵ���A��B
 * author:��껼�
 * data 2019-12-16
 * */
xdata unsigned char PORTA _at_ 0x8000;
xdata unsigned char PORTB _at_ 0x8001 ;
xdata unsigned char PORTC _at_ 0x8002 ;
xdata unsigned char PORTCMD _at_ 0x8003;

void main()
{
    PORTCMD=0x90;
    while(1)
    {
        PORTB=PORTA;
    }
}
