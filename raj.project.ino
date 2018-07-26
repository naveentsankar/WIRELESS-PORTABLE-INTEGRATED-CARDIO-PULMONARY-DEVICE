// Program code for GSM initialization 

#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7)
unsigned char msg_flag=0;

byte g_ent[10];
byte g_rcv[10];
byte g_red[50];
byte g_msg[20];

unsigned char *p;
unsigned char ph_no[10],ph_sum;
unsigned char s1[50];
unsigned char msg_ch[4];

#define urt_on   enable_interrupts(int_rda)
#define urt_off  disable_interrupts(int_rda)

#int_rda
void message_int()
{
  
   gets(g_rcv); 
   msg_flag=1;
}

void uart_intial()
{
   enable_interrupts(global);
   urt_on;
}

void gsm_intialisation()
{
    printf("AT\r");                              
    gets(g_ent);
    gets(g_ent);
    printf("ATE0\r"); 
    gets(g_ent);
    gets(g_ent);
    printf("AT+CMGF=1\r"); 
    gets(g_ent);
     printf("AT+CMGDA=\"DEL ALL\"\r");
    gets(g_ent);
  
}


void rcv_phno()
{
   unsigned char ph_num=0;
   ph_sum=0;
   
   for(ph_num=0;ph_num<=9;ph_num++)
   {
       ph_no[ph_num]= g_red[25+ph_num];
       ph_sum+=ph_no[ph_num];
   }
}

void rcv_msg()
{
   unsigned char msg_num=0;
     
   for(msg_num=0;msg_num<=3;msg_num++)
{
       msg_ch[msg_num]= g_msg[1+msg_num];
       
   }
   }
void message_read(short rd)
{
   printf("AT+CMGR=1\r");
   gets(g_msg);
   rcv_phno();
   rcv_msg();
   printf("AT+CMGD=1\r");
   gets(g_ent);
}
void send_message(SHORT J)
{
     printf("AT+CMGF=1\r"); 
   gets(g_ent);
printf("AT+CMGS=\"+91%c%c%c%c%c%c%c%c%c%c\"\r",*p++,*p++,*p++,*p++,*p++,*p++,*p++,*p++,*p++,*p++);
    delay_ms(100);
    printf("%s\x1a",s1);
    gets(g_ent);
    delay_ms(3000);  
}
void gsm_int()
{
    gsm_intialisation();  
    uart_intial();
 }


//Program code for LCD initialization

#define DATA_PORT             portd
#define REGISTER_SELECT       porte_1
#define ENABLE                porte_2
#define LCD_DELAY             200
#define CM                    0
#define DT                    1 

/////////////////////////////////   command  send to lcd /////////////////////////////////
void  lcd_write(byte write_data,int1 cod)
{
      int delay;
      DATA_PORT=write_data;
      if(cod==CM) REGISTER_SELECT=0; 
      if(cod==DT) REGISTER_SELECT=1; 
      ENABLE=1;
     // delay_ms(LCD_DELAY);
      for(delay=0;delay<LCD_DELAY;delay++);
      ENABLE=0;
}

void  lcd_write_string(byte word )
{
     lcd_write(word,1);
      
}

void  num_conv_5digit(int16 p_value)
{
      int8 a1,a2,a3,a4,a5;
      
      a1=(p_value/10000)+0x30;
      a2=((p_value%10000)/1000)+0x30;
      a3=(((p_value%10000)%1000)/100)+0x30;
      a4=((((p_value%10000)%1000)%100)/10)+0x30;
      a5=((((p_value%10000)%1000)%100)%10)+0x30;
      
      lcd_write(a1,DT);
      lcd_write(a2,DT);
      lcd_write(a3,DT);
      lcd_write(a4,DT);
      lcd_write(a5,DT);      
         
      
}

/////////////////////////// 4 digit display conversion ///////////////////////////////
void  num_conv_4digit(int16 p_value)
{
      
      int8 a2,a3,a4,a5;
      a2=(p_value/1000)+0x30;
      a3=((p_value%1000)/100)+0x30;
      a4=(((p_value%1000)%100)/10)+0x30;
      a5=(((p_value%1000)%100)%10)+0x30;

      lcd_write(a2,DT);
      lcd_write(a3,DT);
      lcd_write(a4,DT);
      lcd_write(a5,DT);   
    
  }
void  num_conv_4dot(int16 p_value)
{
      
      int8 a2,a3,a4,a5;
      a2=(p_value/1000)+0x30;
      a3=((p_value%1000)/100)+0x30;
      a4=(((p_value%1000)%100)/10)+0x30;
      a5=(((p_value%1000)%100)%10)+0x30;
     
      lcd_write(a2,DT);
      lcd_write(a3,DT);
      lcd_write('.',DT);
      lcd_write(a4,DT);
      lcd_write(a5,DT);         
}

void  num_conv_2dec(int16 p_value)
{
      
      int8 a2,a3,a4,a5;
      a2=(p_value/1000)+0x30;
      a3=((p_value%1000)/100)+0x30;
      a4=(((p_value%1000)%100)/10)+0x30;
      a5=(((p_value%1000)%100)%10)+0x30;
      
      
      lcd_write(a2,DT);
      lcd_write(a3,DT);
      lcd_write_string('.');
      lcd_write(a4,DT);
      lcd_write(a5,DT);   
  }

///////////////////////////////dont care////////////////////////////////////////////

void  num_conv_2digit(int8 p_value)
{
      int8 a4,a5;
      
      a4=((p_value%100)/10)+0x30;
      a5=((p_value%100)%10)+0x30;
           
      lcd_write(a4,DT);
      lcd_write(a5,DT);   
         
      
}

void  num_conv_3digit(int16 p_value)
{
      int8 a3,a4,a5;
      
      a3=((p_value%1000)/100)+0x30;
      a4=((p_value%100)/10)+0x30;
      a5=((p_value%100)%10)+0x30;
            
      lcd_write(a3,DT);
      lcd_write(a4,DT);
      lcd_write(a5,DT);   
      
}

void  num_conv_3digit_D(int16 p_value)
{
      int8 a3,a4,a5;
      
      a3=(p_value/100)+0x30;
      a4=((p_value%100)/10)+0x30;
      a5=((p_value%100)%10)+0x30;
          
      lcd_write(a3,DT);
      lcd_write('.',DT);
      lcd_write(a4,DT);
      lcd_write(a5,DT);   
      
}

void  num_conv_1digt(int8 p_value)
{
      int8 a5;
      a5=((p_value%100)%10)+0x30;
      lcd_write(a5,DT);
}
/////////////////////////////////dont care//////////////////////////////////////////////////

/////////////////////////////////////// lcd  intialisation ////////////////////////////////////

void  lcd_int()
{
      lcd_write(0x38,CM);
      lcd_write(0x0c,CM);
      delay_ms(100);
      lcd_write(0x06,CM);
      delay_ms(100);
      lcd_write(0x80,CM);
      delay_ms(100);
      lcd_write(0x01,CM);
      delay_ms(1000);
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////

//MAIN PROGRAM CODE

#include <16f877a.h>
#use delay(clock=20000000)
#fuses HS,PROTECT,NOWDT,NOBROWNOUT,NOLVP,NOPUT


unsigned char *p;
unsigned int16 heart_rate_count=0,time_count=0,pulse_rate=0,oxygen_rate=00;
int1 set=0,flag_gsm=0;


#include <lcd_drive_2.c>
#include <gsm_drive.c>

#INT_EXT
void  key_scan()
{
   int8 count;
   ++heart_rate_count;

   break;
}

#INT_TIMER1
void speed_calc()
{
    set_timer1(0x0bdb); 
   time_count+=1;
   if(time_count==100)
   {
      time_count=0;
      set=1;
      break;
   }
}
void interrupt_initials()
{
    enable_interrupts(GLOBAL);
   enable_interrupts(INT_EXT);
   ext_int_edge(L_TO_H);   
}

void timer_initials()
{
     setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);   // setup interrupts
     enable_interrupts(INT_TIMER1);
     enable_interrupts(GLOBAL);
}

void pulse_timing()
{
  
   int16 i=0,j=0;
   int1 flag=0;
   float oxy;
   while(true)
   {
    if(portb_0==0)
     {
             
         while(true)
         {
            if(portb_0==1)
              {
               
                  flag=1;
                  break;
              }
         }
    
     }
     if(flag==1) break;
     
   } 
   flag=0;
 
  while(1)
  {
     i++;
     if(portb_0==0)
     {
        break;
     }
      
   }
    
   while(1)
  {
      j++;
      if(portb_0==1)
     {
             break;
     }
    }
   
   oxy=((float)i/(float)40502) * 95.00;
   oxygen_rate=(unsigned long)(oxy * 100);
 
     lcd_write(0xca,CM);
     num_conv_2dec(oxygen_rate); 
}

void main()
{
      io_init(0x00,0xf1,0x80,0x00,0x00);
      lcd_int();
      lcd_write_string("INTIALISING...");
      gsm_int();
      lcd_clear();
      lcd_write(0x80,CM);
      lcd_write_string("HEART Rate/m:");
      lcd_write(0xc0,CM);
      lcd_write_string("OXY_LEVEL:     %");
      interrupt_initials();
      timer_initials();
      
      while(true)
      {
              if(msg1_flag==1)
         {
             message_read();
             if(g1_msg[1]=='S')
             {
               tr="P_R:   \rO_L:     %";
               tr[4]=(unsigned char)(pulse_rate/100) + 0x30; 
               tr[5]=(unsigned char)((pulse_rate%100)/10) + 0x30;
               tr[6]=(unsigned char)((pulse_rate%100)%10) + 0x30;
               tr[12]=(unsigned char)(oxygen_rate/1000) + 0x30;
               tr[13]=(unsigned char)((oxygen_rate%1000)/100) + 0x30;
               tr[14]='.';
               tr[15]=(unsigned char)(((oxygen_rate%1000)%100)/10) + 0x30;
               tr[16]=(unsigned char)(((oxygen_rate%1000)%100)%10) + 0x30;
               p=ph1_no;
               send_message(1);
               g1_msg[1]='\0';
             }
               flag_gsm=0;
               enable_interrupts(int_ext);
               enable_interrupts(int_timer1);
              msg1_flag=0;      
          }
         if(set==1)
        {
            disable_interrupts(int_ext);
            disable_interrupts(int_timer1);
            lcd_write(0x8d,CM);
            num_conv_3digit(heart_rate_count * 6) ;
            pulse_rate=heart_rate_count * 6;
            delay_ms(100);
            pulse_timing();
           
            heart_rate_count=0;
            set=0;
            time_count=0;
            enable_interrupts(int_ext);
            enable_interrupts(int_timer1);
        }
    }     
}

