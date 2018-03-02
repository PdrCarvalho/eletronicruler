

// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal.h>                              //Biblioteca para o display LCD

// --- Mapeamento de Hardware ---
#define butUp    12                                     //Botão para selecionar tela acima no digital 12
#define butDown  11                                     //Botão para selecionar tela abaixo no digital 11
#define butP     10                                     //Botão de ajuste mais no digital 10
#define butM      9                                     //Botão de ajuste menos no digital 9
int gatilho = 13; // pino TRIG do sensor ultrassônico
int echo = 8; // pino ECHO do sensor ultrassônico
float tempo; // para armazenar o tempo de ida e volta do sinal em microsegundos
float distancia; // para armazenar a distância em centímetros
// --- Protótipo das Funções Auxiliares ---
void changeMenu();                                      //Função para modificar o menu atual
void dispMenu();                                        //Função para mostrar o menu atual
void menu1();                                       //Função do menu1, data e hora
void menu2();                                     //Função do menu2, temperatura
void menu3();                                          //Função do menu3, acionamento de lampadas
void menu4();                                           //Função do menu4
int lado1 = 0 ;
int lado2 = 0 ;
int resu = 0;
int raio=0;
int lado3 = 0;
int lado4 = 0;
// --- Variáveis Globais ---
char menu = 0x01;                                       //Variável para selecionar o menu
char set1 = 0x00, set2 = 0x00;                          //Controle das lâmpadas
boolean t_butUp, t_butDown, t_butP, t_butM;             //Flags para armazenar o estado dos botões

// --- Hardware do LCD ---
LiquidCrystal disp(7,  //RS no digital 7
                   6,  //EN no digital 6
                   5,  //D4 no digital 5
                   4,  //D5 no digital 4
                   3,  //D6 no digital 3
                   2); //D7 no digital 2

// --- Configurações Iniciais ---
void setup()
{
  pinMode(gatilho, OUTPUT);
  digitalWrite(gatilho, LOW);
  delayMicroseconds(10);
  pinMode(echo, INPUT);
  disp.begin(16,2);                                      //Inicializa LCD 16 x 2
  
  for(char i=9; i<13; i++) pinMode(i, INPUT_PULLUP);     //Entrada para os botões (digitais 9 a 12) com pull-ups internos

  
  t_butUp   = 0x00;                                      //limpa flag do botão Up
  t_butDown = 0x00;                                      //limpa flag do botão Down
  t_butP    = 0x00;                                      //limpa flag do botão P
  t_butM    = 0x00;                                      //limpa flag do botão M
  


} //end setup


// --- Loop Infinito ---
void loop()
{
    
   
   changeMenu();
   dispMenu();

} //end loop

// --- Desenvolvimento das Funções Auxiliares ---
void changeMenu()                                       //Modifica o menu atual
{
   if(!digitalRead(butUp))   t_butUp   = 0x01;          //Botão Up pressionado? Seta flag
   if(!digitalRead(butDown)) t_butDown = 0x01;          //Botão Down pressionado? Seta flag
      
   if(digitalRead(butUp) && t_butUp)                    //Botão Up solto e flag setada?
   {                                                    //Sim...
      t_butUp = 0x00;                                   //Limpa flag
      
      disp.clear();                                     //Limpa display
      menu++;                                           //Incrementa menu
      
      if(menu > 0x04) menu = 0x01;                      //Se menu maior que 4, volta a ser 1
   
   } //end butUp
   
   if(digitalRead(butDown) && t_butDown)                //Botão Down solto e flag setada?
   {                                                    //Sim...
      t_butDown = 0x00;                                 //Limpa flag
      
      disp.clear();                                     //Limpa display
      menu--;                                           //Decrementa menu
      
      if(menu < 0x01) menu = 0x04;                      //Se menu menor que 1, volta a ser 4
   
   } //end butDown   

} //end changeMenu

void dispMenu()                                         //Mostra o menu atual
{
    switch(menu)                                        //Controle da variável menu
    {
       case 0x01:                                       //Caso 1
             menu1();                               //Chama a função de relógio
             
             break;                                     //break
       case 0x02:                                       //Caso 2
             menu2();                             //Chama a função do termômetro
             
             break;                                     //break
       case 0x03:                                       //Caso 3
             menu3();                                  //Chama função para acionamento de lâmpadas
            
             break;                                     //break
       case 0x04:                                       //Caso 4
             menu4();                                   //Chama função para o menu4
             
             break;                                     //break
    
    } //end switch menu

} //end dispMenu

void menu1()                                        //Data e Hora (menu1)
{
    
   disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   disp.print("Quadrado");                           //Imprime mensagem
    
   if(!digitalRead(butP))    t_butP    = 0x01;          //Botão P pressionado? Seta flag
   if(!digitalRead(butM))    t_butM    = 0x01;          //Botão M pressionado? Seta flag
   
   if(digitalRead(butP) && t_butP)                      //Botão P solto e flag setada?
   {                                                    //Sim...
      t_butP = 0x00;                                    //Limpa flag
      
      set1++;                                           //Incrementa set1
      
      if(set1 > 2) set1 = 0x01;                         //Se maior que 2, volta a ser 1
      
      switch(set1)                                      //Controle do set1
      {
          case 0x01:                                    //Caso 1
                disp.setCursor(0,1);                    //Posiciona cursor na coluna 1, linha 2
                // disparar pulso ultrassônico
              digitalWrite(gatilho, HIGH);
              delayMicroseconds(10);
              digitalWrite(gatilho, LOW);
              // medir tempo de ida e volta do pulso ultrassônico
              tempo = pulseIn(echo, HIGH);
              // calcular distâncias
              distancia = tempo / 29.4 / 2;
                disp.print("L1 on ");                   //Imprime mensagem
                lado1= distancia;
                break;                                  //Break
          case 0x02:                                    //Caso 2
                
                disp.setCursor(0,1);                    //Posiciona cursor na coluna 1, linha 2
                disp.print("L1 off");                   //Imprime mensagem
                lado1= 0 ;
                break;                                  //Break
      
      } //end switch set1
   
   } //end butP
  if(digitalRead(butM) && t_butM)                      //Botão D solto e flag setada?
   {                                                    //Sim...
      t_butM = 0x00;                                    //Limpa flag
      
      set2++;                                           //Incrementa set2
      
      if(set2 > 2) set2 = 0x01;                         //Se maior que 2, volta a ser 1
      
      switch(set2)                                      //Controle do set2
      {
          case 0x01:                                    //Caso 1
                disp.setCursor(8,1);                    //Posiciona cursor na coluna 8, linha 2
                disp.print("Area:"); 
                resu = lado1 * lado1 ;
                disp.setCursor(14,1); 
                disp.print( resu);                   //Imprime mensagem

                break;                                  //Break
          case 0x02:                                    //Caso 2
                 disp.setCursor(8,1);                    //Posiciona cursor na coluna 8, linha 2
                disp.print("Peri:"); 
                disp.setCursor(14,1);                    //Posiciona cursor na coluna 8, linha 2
                resu= 4 * lado1;
                disp.print(resu);                   //Imprime mensagem
                break;                                  //Break
      
      } //end switch set1
   
   } //end butM
} //end data_hora

void menu2()                                      //Temperatura (menu2)
{
   disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   disp.print("Retangulo");                           //Imprime mensagem
  if(!digitalRead(butP))    t_butP    = 0x01;          //Botão P pressionado? Seta flag
   if(!digitalRead(butM))    t_butM    = 0x01;          //Botão M pressionado? Seta flag
   
   if(digitalRead(butP) && t_butP)                      //Botão P solto e flag setada?
   {                                                    //Sim...
      t_butP = 0x00;                                    //Limpa flag
      
      set1++;                                           //Incrementa set1
      
      if(set1 > 2) set1 = 0x01;                         //Se maior que 2, volta a ser 1
      
      switch(set1)                                      //Controle do set1
      {
          case 0x01:                                    //Caso 1
             // disparar pulso ultrassônico
              digitalWrite(gatilho, HIGH);
              delayMicroseconds(10);
              digitalWrite(gatilho, LOW);
              // medir tempo de ida e volta do pulso ultrassônico
              tempo = pulseIn(echo, HIGH);
              // calcular distâncias
              distancia = tempo / 29.4 / 2;
                disp.setCursor(0,1);                    //Posiciona cursor na coluna 1, linha 2
                disp.print("L1 on ");                   //Imprime mensagem
                lado1= distancia;
                break;                                  //Break
          case 0x02:                                    //Caso 2
                // disparar pulso ultrassônico
              digitalWrite(gatilho, HIGH);
              delayMicroseconds(10);
              digitalWrite(gatilho, LOW);
              // medir tempo de ida e volta do pulso ultrassônico
              tempo = pulseIn(echo, HIGH);
              // calcular distâncias
              distancia = tempo / 29.4 / 2;
                disp.setCursor(0,1);                    //Posiciona cursor na coluna 1, linha 2
                disp.print("L2 on");                   //Imprime mensagem
                lado2= distancia ;
                break;                                  //Break
      
      } //end switch set1
   
   } //end butP
  if(digitalRead(butM) && t_butM)                      //Botão D solto e flag setada?
   {                                                    //Sim...
      t_butM = 0x00;                                    //Limpa flag
      
      set2++;                                           //Incrementa set2
      
      if(set2 > 2) set2 = 0x01;                         //Se maior que 2, volta a ser 1
      
      switch(set2)                                      //Controle do set2
      {
          case 0x01:                                    //Caso 1
                disp.setCursor(8,1);                    //Posiciona cursor na coluna 8, linha 2
                disp.print("Area:"); 
                resu = lado1 * lado2 ;
                disp.setCursor(14,1); 
                disp.print( resu);                   //Imprime mensagem

                break;                                  //Break
          case 0x02:                                    //Caso 2
                 disp.setCursor(8,1);                    //Posiciona cursor na coluna 8, linha 2
                disp.print("Peri:"); 
                disp.setCursor(14,1);                    //Posiciona cursor na coluna 8, linha 2
                resu= (2*lado1) + (2*lado2);
                disp.print(resu);                   //Imprime mensagem
                break;                                  //Break
      
      } //end switch set1
   
   } //end butM
} //end temperatura()
 
void menu3()                                           //Acionamento de lâmpadas (menu3)
{
  
   disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   disp.print("Triangulo");                      //Imprime mensagem do menu 3
  
  
   if(!digitalRead(butP))    t_butP    = 0x01;          //Botão P pressionado? Seta flag
   if(!digitalRead(butM))    t_butM    = 0x01;          //Botão M pressionado? Seta flag
   
   if(digitalRead(butP) && t_butP)                      //Botão P solto e flag setada?
   {                                                    //Sim...
      t_butP = 0x00;                                    //Limpa flag
      
      set1++;                                           //Incrementa set1
      
      if(set1 > 4) set1 = 0x01;                         //Se maior que 2, volta a ser 1
      
      switch(set1)                                      //Controle do set1
      {
          case 0x01:                                    //Caso 1
                // disparar pulso ultrassônico
              digitalWrite(gatilho, HIGH);
              delayMicroseconds(10);
              digitalWrite(gatilho, LOW);
              // medir tempo de ida e volta do pulso ultrassônico
              tempo = pulseIn(echo, HIGH);
              // calcular distâncias
              distancia = tempo / 29.4 / 2;
                disp.setCursor(0,1);                    //Posiciona cursor na coluna 1, linha 2
                disp.print("Base on");                   //Imprime mensagem
                lado1= distancia ;
                break;                                  //Break
          case 0x02:                                    //Caso 2
                // disparar pulso ultrassônico
              digitalWrite(gatilho, HIGH);
              delayMicroseconds(10);
              digitalWrite(gatilho, LOW);
              // medir tempo de ida e volta do pulso ultrassônico
              tempo = pulseIn(echo, HIGH);
              // calcular distâncias
              distancia = tempo / 29.4 / 2;
                disp.setCursor(0,1);                    //Posiciona cursor na coluna 1, linha 2
                disp.print("Alt on");                   //Imprime mensagem
               lado2= distancia ;
                break;                                  //Break
          case 0x03:
              // disparar pulso ultrassônico
              digitalWrite(gatilho, HIGH);
              delayMicroseconds(10);
              digitalWrite(gatilho, LOW);
              // medir tempo de ida e volta do pulso ultrassônico
              tempo = pulseIn(echo, HIGH);
              // calcular distâncias
              distancia = tempo / 29.4 / 2;
              disp.setCursor(0,1);                    //Posiciona cursor na coluna 1, linha 2
                disp.print("lado2 on");                   //Imprime mensagem
               lado3= distancia;
               break;
          case 0x04:
              // disparar pulso ultrassônico
              digitalWrite(gatilho, HIGH);
              delayMicroseconds(10);
              digitalWrite(gatilho, LOW);
              // medir tempo de ida e volta do pulso ultrassônico
              tempo = pulseIn(echo, HIGH);
              // calcular distâncias
              distancia = tempo / 29.4 / 2;
              disp.setCursor(0,1);                    //Posiciona cursor na coluna 1, linha 2
                disp.print("lado3 on");                   //Imprime mensagem
               lado2= distancia ;
      
      } //end switch set1
   
   } //end butP
   
   if(digitalRead(butM) && t_butM)                      //Botão D solto e flag setada?
   {                                                    //Sim...
      t_butM = 0x00;                                    //Limpa flag
      
      set2++;                                           //Incrementa set2
      
      if(set2 > 4) set2 = 0x01;                         //Se maior que 2, volta a ser 1
      
    switch(set2)                                      //Controle do set2
      {
          case 0x01:                                    //Caso 1
                disp.setCursor(8,1);                    //Posiciona cursor na coluna 8, linha 2
                disp.print("Area:"); 
                resu = (lado1 * lado2)/2 ;
                disp.setCursor(14,1); 
                disp.print( resu);                   //Imprime mensagem

                break;                                  //Break
          case 0x02:                                    //Caso 2
                 disp.setCursor(8,1);                    //Posiciona cursor na coluna 8, linha 2
                disp.print("Equi:"); 
                disp.setCursor(14,1);                    //Posiciona cursor na coluna 8, linha 2
                resu= 3* lado1;
                disp.print(resu);                   //Imprime mensagem
                break;                                  //Break
         case 0x03:
                disp.setCursor(8,1);                    //Posiciona cursor na coluna 8, linha 2
                disp.print("iso:"); 
                disp.setCursor(14,1);                    //Posiciona cursor na coluna 8, linha 2
                resu= (2*lado3)+lado1;
                disp.print(resu);                   //Imprime mensagem
                break;                                  //Break
        case 0x04:
                disp.setCursor(8,1);                    //Posiciona cursor na coluna 8, linha 2
                disp.print("Esca:"); 
                disp.setCursor(14,1);                    //Posiciona cursor na coluna 8, linha 2
                resu= lado1+lado3+lado4;
                disp.print(resu);                   //Imprime mensagem
                break;                                  //Break
      } //end switch set1
   
   } //end butM


} //end lights

void menu4()                                            //Função genérica para um quarto menu...
{
  
   disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
   disp.print("Circulo");                                //Imprime mensagem
  if(!digitalRead(butP))    t_butP    = 0x01;          //Botão P pressionado? Seta flag
   if(!digitalRead(butM))    t_butM    = 0x01;          //Botão M pressionado? Seta flag
   
   if(digitalRead(butP) && t_butP)                      //Botão P solto e flag setada?
   {                                                    //Sim...
      t_butP = 0x00;                                    //Limpa flag
      
      set1++;                                           //Incrementa set1
      
      if(set1 > 2) set1 = 0x01;                         //Se maior que 2, volta a ser 1
      
      switch(set1)                                      //Controle do set1
      {
          case 0x01:                                    //Caso 1
                // disparar pulso ultrassônico
              digitalWrite(gatilho, HIGH);
              delayMicroseconds(10);
              digitalWrite(gatilho, LOW);
              // medir tempo de ida e volta do pulso ultrassônico
              tempo = pulseIn(echo, HIGH);
              // calcular distâncias
              distancia = tempo / 29.4 / 2;
                disp.setCursor(0,1);                    //Posiciona cursor na coluna 1, linha 2
                disp.print("Diam on ");                   //Imprime mensagem
                lado1= distancia ;
                raio = lado1/2 ;
                break;                                  //Break
          case 0x02:                                    //Caso 2
                // disparar pulso ultrassônico
              digitalWrite(gatilho, HIGH);
              delayMicroseconds(10);
              digitalWrite(gatilho, LOW);
              // medir tempo de ida e volta do pulso ultrassônico
              tempo = pulseIn(echo, HIGH);
              // calcular distâncias
              distancia = tempo / 29.4 / 2;
                disp.setCursor(0,1);                    //Posiciona cursor na coluna 1, linha 2
                disp.print("Diam off");                   //Imprime mensagem
                lado1= distancia ;
                raio = lado1/2 ;
                break;                                  //Break
      
      } //end switch set1
   
   } //end butP
   
   if(digitalRead(butM) && t_butM)                      //Botão D solto e flag setada?
   {                                                    //Sim...
      t_butM = 0x00;                                    //Limpa flag
      
      set2++;                                           //Incrementa set2
      
      if(set2 > 2) set2 = 0x01;                         //Se maior que 2, volta a ser 1
      
    switch(set2)                                      //Controle do set2
      {
          case 0x01:                                    //Caso 1
                disp.setCursor(8,1);                    //Posiciona cursor na coluna 8, linha 2
                disp.print("Area:"); 
                resu = 3.14 * raio * raio ;
                disp.setCursor(14,1); 
                disp.print( resu);                   //Imprime mensagem

                break;                                  //Break
          case 0x02:                                    //Caso 2
                 disp.setCursor(8,1);                    //Posiciona cursor na coluna 8, linha 2
                disp.print("Peri:"); 
                disp.setCursor(14,1);                    //Posiciona cursor na coluna 8, linha 2
                resu= 2 * 3.14 * raio;
                disp.print(resu);                   //Imprime mensagem
                break;                                  //Break
      
      } //end switch set1
   
   } //end butM


} //end menu4




















