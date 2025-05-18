//BLOQUE DEL LCD
// Pin de selección del registro (RS)
sbit LCD_RS at LATE0_bit;
// Pin de habilitación (EN)
sbit LCD_EN at LATE1_bit;
// Pins de datos D4 a D7
sbit LCD_D4 at LATC0_bit;
sbit LCD_D5 at LATC1_bit;
sbit LCD_D6 at LATC6_bit;
sbit LCD_D7 at LATC7_bit;
// Dirección del pin RS
sbit LCD_RS_Direction at TRISE0_bit;
// Dirección del pin EN
sbit LCD_EN_Direction at TRISE1_bit;
// Dirección de los pines de datos
sbit LCD_D4_Direction at TRISC0_bit;
sbit LCD_D5_Direction at TRISC1_bit;
sbit LCD_D6_Direction at TRISC6_bit;
sbit LCD_D7_Direction at TRISC7_bit;
////////////////////////////////////
//BLOQUE DE VARIABLES
unsigned int temp=0, estadoAire=0, variableADC = 0, leer = 0,estado = 0, seleccion = 0;
char caracter[8];
////////////////////////////////
//BLOQUE DE PROTOTIPO DE METODOS
void condicion1();
void condicion2();
void condicion3();
void imprevisto();
void CustomChar(char pos_row, char pos_char);
////////////////////////////////
//BLOQUE DE CODIGO PRINCIPAL
void main() {
OSCCON = 0XFF; // oscilador a 8 mhz
ADCON0 = 0X01; // Seleccion del canal analogico AN0 habilita el modulo A/D
ADCON1 = 0X1E; // configura de entradas digitales AN1 a la AN11, seleccionando AN0 como entrada analoga
ADCON2 = 0X3C; // justificacion a la izquierda, tiempo de adquisicion de 20TAD (conversion), reloj para el periodo de conversion FOSC/4
CMCON = 0X07;

//CONFIGURACION DE PUERTOS
TRISA = 0XEF;//ENTRADA POTENCIOMETRO Y SWITCH
TRISB = 0X7F;//ENTRADA BOTONES
TRISD = 0;//SALIDA

//LIMPIAMOS LOS PUERTOS
PORTA = 0;//Se iguala el valor de todos los pines del puerto A a 0
PORTB = 0;//Se iguala el valor de todos los pines del puerto B a 0
PORTD = 0;//Se iguala el valor de todos los pines del puerto D a 0

//INICIALIZAMOS EL LCD
Lcd_Init();                  // Inicializa el LCD
Lcd_Cmd(_LCD_CLEAR);         // Limpia la pantalla
Lcd_Cmd(_LCD_CURSOR_OFF);    // Apaga el cursor

//Lcd_Out(1, 1, "ETS DISPOS 3NV40");// Escribe texto en el LCD
Lcd_Out(1, 1, "ETS DISPOS");// Escribe texto en el LCD
Lcd_Out(2, 3, "INVERNADERO");// Escribe texto en el LCD
delay_ms(1000);//RETARDO

while(1){//Bucle principal
if(PORTB.F0==1||estado==1||seleccion==0){//SE LEE TODO EL TIEMPO EN ESPERA DEL BOTON DE LECTURA
/*LA CONDICION SE ACTIVA EN TRES CASOS:
1.-SI EL BOTON ESTA PRESIONADO
2.-SI EL BOTON FUE PRESIONADO PERO NO SE TERMINO LA LECTURA
3.-SI ES LA PRIMERA VEZ QUE CORRE EL PROGRAMA*/
Lcd_Cmd(_LCD_CLEAR);// Limpia la pantalla
estado=1;//SE ACTIVA LA VARIABLE ESTADO PARA SABER SI EL BOTON YA FUE PRESIONADO PREVIAMENTE
Lcd_Out(2, 1, "MODO LECTURA");// Escribe texto en el LCD
delay_ms(200);//RETARDO
           if(PORTB.F1==1){//SI EL BOTON DE TERMINAR LECTURA SE PRESIONA...
           Lcd_Cmd(_LCD_CLEAR);// Limpia la pantalla
           estado=0;//LA VARIABLE ESTADO SE DESACTIVA
                    if(PORTA.F1==0&&PORTA.F2==1){//CONDICION 1
                    //SI LA CONDICION EN EL SWITCH ES 01 SE CUMPLE LA CONDICION 1
                    seleccion = 1;//EL MODO SELECCIONADO ES EL 1
                    Lcd_Out(2, 1, "MODO UNO");// Escribe texto en el LCD
                    }//Termina if
                    else if(PORTA.F1==1&&PORTA.F2==0){//CONDICION 2
                    //SI LA CONDICION EN EL SWITCH ES 10 SE CUMPLE LA CONDICION 2
                    seleccion = 2;//EL MODO SELECCIONADO ES EL 2
                    Lcd_Out(2, 1, "MODO DOS");// Escribe texto en el LCD
                    }//Termina else if
                    else{//SI NO ES NINGUNA CONDICION
                    Lcd_Out(2, 1, "MODO TRES");// Escribe texto en el LCD
                    seleccion = 3;//EL MODO SELECCIONADO ES EL 3
                    }//TERMINA ELSE
                    delay_ms(1000);
           Lcd_Cmd(_LCD_CLEAR);// Limpia la pantalla
           Lcd_Out(1, 1, "C");// Escribe texto en el LCD
           CustomChar(1,2);//Escribe el caracter personalizado ° para representar grados
           Lcd_Out(1, 3, ":");// Escribe texto en el LCD
           }//Termina if
}//Termina if
else{//EN CASO QUE SE HAYA TERMINADO LA LECTURA...
    switch(seleccion){//SE HACE UNA SELECCION DEL MODO CON BASE A LA LECTURA REALIZADA
        case 1:
        condicion1();
        break;
        
        case 2:
        condicion2();
        break;
        
        case 3:
        condicion3();
        break;
        
        default:
        imprevisto();
        break;
    }//Termina switch
}//Termina else
}//Termina while
}//Termina bloque de codigo principal

void condicion1(){//Comienza el metodo
//Se lee el valor del potenciometro, se pasa a entero y se convierte a caracter
variableADC = ADC_Read(0);//Se lee el valor del potenciometro en PORTA 0
//temp = variableADC/100;//Para obtener un valor valido yo hago la conversion usando la division por 100
temp = (variableADC*0.488)/50;//Para obtener un valor valido yo hago la conversion usando la division por 100
IntToStr(temp, caracter);//Se convierte el valor del potenciometro a un char pues el LCD solo recibe char
Lcd_Out(1, 5, caracter);// Escribe texto en el LCD

if(temp>=3&&temp<=8){//Si la temperatura esta en el promedio...
   Lcd_Out(2, 1, "TEMPE PROMEDIO");// Escribe texto en el LCD
   if(temp==4&&estadoAire==1){//Revisa que si el aire esta encendido, en caso que si...
   delay_ms(500);//Espera medio segundo
   estadoAire = 0;//Apaga el aire
   PORTD.F0=estadoAire;
   }//Termina if del aire
}//Termina if de la temperatura

else if(temp>8){//De lo contrario, si la temperatura esta sobre el promedio
Lcd_Out(2, 1, "SOBRE PROMEDIO");// Escribe texto en el LCD
estadoAire = 1;//Se activa el ventilador
PORTD.F0=estadoAire;
}//Termina else if

else{//Por el contrario, si la temperatura esta debajo del promedio...
Lcd_Out(2, 1, "BAJO  PROMEDIO");// Escribe texto en el LCD
}//Termina else
}//Termina metodo

void condicion2(){//Comienza el metodo
//Se lee el valor del potenciometro, se pasa a entero y se convierte a caracter
variableADC = ADC_Read(0);//Se lee el valor del potenciometro en PORTA 0
//temp = variableADC;//Para obtener un valor valido yo hago la conversion usando la division por 100
temp = (variableADC*0.488)/50;//Para obtener un valor valido yo hago la conversion usando la division por 100
IntToStr(temp, caracter);//Se convierte el valor del potenciometro a un char pues el LCD solo recibe char
Lcd_Out(1, 5, caracter);// Escribe texto en el LCD

if(temp>=2&&temp<7){//Si la temperatura esta en el promedio...
   Lcd_Out(2, 1, "TEMPE PROMEDIO");// Escribe texto en el LCD
   if(temp==3&&estadoAire==1){//Revisa que si el aire esta encendido, en caso que si...
   delay_ms(500);//Espera medio segundo
   estadoAire = 0;//Apaga el aire
   PORTD.F0=estadoAire;
   }//Termina if del aire
}//Termina if de la temperatura

else if(temp>=7){//De lo contrario, si la temperatura esta sobre el promedio
Lcd_Out(2, 1, "SOBRE PROMEDIO");// Escribe texto en el LCD
estadoAire = 1;//Se activa el ventilador
PORTD.F0=estadoAire;
}//Termina else if

else{//Por el contrario, si la temperatura esta debajo del promedio...
Lcd_Out(2, 1, "BAJO  PROMEDIO");// Escribe texto en el LCD
}//Termina else
}//Termina el metodo

void condicion3(){//El modo tres es unicamente la excepcion en caso que se lea 11 o 00
Lcd_Out(2, 1, "MODO DESCANSO");// Escribe texto en el LCD
delay_ms(200);//Retardo
}//Termina metodo

void imprevisto(){//En caso que se lea cualquier otra condicion que no sea las de la tabla
Lcd_Out(2, 1, "ERROR ERROR");// Escribe texto en el LCD
delay_ms(200);//Retardo
}//Termina metodo

//Metodo para el caracter personalizado
const char character[] = {28,20,28,0,0,0,0,0};
void CustomChar(char pos_row, char pos_char) {//El caracter personalizado es °
  char i;
    Lcd_Cmd(64);
    for (i = 0; i<=7; i++) Lcd_Chr_CP(character[i]);
    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(pos_row, pos_char, 0);
}//Termina metodo
