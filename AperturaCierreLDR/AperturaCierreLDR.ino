bool releLDR= 0;
bool puertaAbierta=0;
bool puertaCerrada=0;
bool continuar=0;
bool LDR=0;

unsigned int etapa=0;


int pinLDR = A0;
int valorLDR=0;
int umbralLDR= 300;

const int pinFinalCarreraPuertaAbierta = 3;
const int pinFinalCarreraPuertaCerrada = 4;
const int pinReleLDRNO = 5;

const int pinSalidaAbrir=8;
const int pinSalidaCerrar=10;

unsigned long tiempoAnterior = 0;  
const unsigned long intervalo = 2000;

void setup() {
  //Configuracion de ENTRADAS
    pinMode(pinFinalCarreraPuertaAbierta,INPUT);
    pinMode(pinFinalCarreraPuertaCerrada,INPUT);
    pinMode(pinReleLDRNO,INPUT);
  //Configuracion de SALIDAS
    pinMode(pinSalidaAbrir,OUTPUT);
    pinMode(pinSalidaCerrar,OUTPUT);
  //Configuracion de COMUNICACIONES
    Serial.begin(9600);

    Serial.println("#REALIZADAS COMPROBACIONES INICIALES#");    
}

void loop() {
  unsigned long tiempoActual = millis();
  // Verificar si ha pasado el intervalo de 10 segundos
  if (tiempoActual - tiempoAnterior >= intervalo) {
    Serial.print("#ETAPA ");
    Serial.println(etapa);
    printearEstadoEntradas();
    tiempoAnterior = tiempoActual;
  }
    leerEntradas();
    ejecutarPrograma();
    activarSalidas();
    delay(500);
}

//En esta funcion copiamos el estado de las entradas(PINES) en las variables internas que vamos a usar
void leerEntradas(){
  releLDR=digitalRead(pinReleLDRNO);
  puertaAbierta=digitalRead(pinFinalCarreraPuertaAbierta);
  puertaCerrada=digitalRead(pinFinalCarreraPuertaCerrada);
  valorLDR= analogRead(pinLDR);
}

void ejecutarPrograma(){
//Transformacion de la entrada anologica a un booleando para trabajar mas comodod con el dato.
  if(valorLDR>=umbralLDR){
    LDR =true;
  }else{
    LDR=false;
  }

if(etapa==0 & puertaAbierta){
  etapa=10;
}
/*
PARTE DEL PROGRAMA CON PULSADOR PARA SIMULAR LDR
if(etapa==10 && releLDR){
    etapa=20;
}

if(etapa==10 && !releLDR){
    etapa=30;
}

*/
if(etapa==10 && LDR){
    etapa=20;
}

if(etapa==10 && !LDR){
    etapa=30;
}

if(etapa==20 && puertaAbierta){
  etapa=21;
}

if(etapa==30 && puertaCerrada){
  etapa=31;
}
/*
CON BOTON PARA SIMULAR LDR
if((etapa==21 && !releLDR) ||(etapa==31 && releLDR)){
  etapa=10;
}
*/

if(etapa==21 && !LDR){
  etapa=10;
}

if(etapa==31 && LDR){
  etapa=10;
}
   
}

void activarSalidas(){
switch (etapa) {
  //Etapa inicial abrimos la puerta si no esta abierta para tener un punto de partida.
  case 0:
    if(!puertaAbierta){
      digitalWrite(pinSalidaAbrir,HIGH);
      digitalWrite(pinSalidaCerrar,LOW);
    }
    break;
  //Etapa que decide si debemos tener la puerta abieta o no en funcion del LDR
  case 10:
    digitalWrite(pinSalidaAbrir,LOW);
    digitalWrite(pinSalidaCerrar,LOW);
    break;
  //Etapa para abrir la puerta si el LDR da señal
  case 20:
    digitalWrite(pinSalidaAbrir,HIGH);
    digitalWrite(pinSalidaCerrar,LOW);
    break;
  //Etapa de espera con la puerta abierta
  case 21:
    digitalWrite(pinSalidaAbrir,LOW);
    digitalWrite(pinSalidaCerrar,LOW);
    break;

  //Etapara para cerrar la puerta si el LDR NO da señal
  case 30:
    digitalWrite(pinSalidaAbrir,LOW);
    digitalWrite(pinSalidaCerrar,HIGH);
    break;
  //Etapa de espera con la puerta cerrada  
  case 31:
    digitalWrite(pinSalidaAbrir,LOW);
    digitalWrite(pinSalidaCerrar,LOW);
    break;

  default:
    Serial.println("No hay etapa, error en la ejecucion");
    break;
}
}

void printearEstadoEntradas(){
 // Definir el rango de pines que deseas monitorear (ahora del 2 al 6)
  int pines[] = {3, 4, 5,8,10};
  int totalPines = sizeof(pines)/ sizeof(pines[0]);

  Serial.println("###########################");
  Serial.println("Estado de las entradas 2-6");

  // Iterar a través de los pines definidos
  for (int i = 0; i < totalPines; i++) {
    int estado = digitalRead(pines[i]);

    // Imprimir el estado de cada pin
    Serial.print("Entrada ");
    Serial.print(pines[i]);
    Serial.print(": ");
    Serial.println(estado);
  }

  Serial.print("Valor de A0: ");  
  Serial.println(valorLDR);

  Serial.print("Boolean de LDR: ");  
  Serial.println(LDR);

  Serial.println("###########################");
}
