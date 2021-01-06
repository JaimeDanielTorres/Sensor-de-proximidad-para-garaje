//Sensor de reversa para cochera - 07/09/20

#define dcomienzo 300
#define dalta 150
#define dmedia 70
#define dcorta 35
#define dparo 15


#define Trigger 4   //Pin digital 4 para el Trigger del sensor
#define Echo 3      //Pin digital 3 para el Echo del sensor
#define ledRed 2
#define ledGreen 1
#define buzzer 0

unsigned long tiempo; //tiempo que demora en llegar el eco
unsigned long distancia; //distancia en centimetros

int interval = 350;
unsigned long previousMillis;

short segundos,modulo,conteo;

void setup() {
  Serial.begin(115200);//iniciailzamos la comunicación
  OSCCAL +=40;
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  pinMode(ledRed, OUTPUT);  
  pinMode(buzzer, OUTPUT);  
  pinMode(ledGreen, OUTPUT);
  
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  digitalWrite(ledRed, HIGH);
  delay(1000);
  digitalWrite(ledRed, LOW);
}

void loop()
{

  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= interval) //ciclo principal
  {
    previousMillis = millis();
    segundos++;
    modulo=segundos%2;
    if(segundos>=600)
    segundos=0;

    if(interval==100 && conteo<=100 && distancia<=dparo){
      conteo++;
    }
  }
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);

  tiempo = pulseIn(Echo, HIGH, 10000000); //obtenemos el ancho del pulso
  distancia = tiempo/40;             //escalamos el tiempo a una distancia en cm


  if(distancia>=dcomienzo){
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(buzzer, LOW);
  }
  
  else if(distancia>=dcomienzo && distancia >= dalta){
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(buzzer, LOW);
  }

  
  else if(distancia<dalta && distancia>=dmedia){    //Distancia alta
    if(modulo==1)
      digitalWrite(ledGreen, HIGH);
    
    else
      digitalWrite(ledGreen, LOW);
    
    digitalWrite(ledRed, LOW);
    digitalWrite(buzzer, LOW);
  }

  
  else if(distancia<dmedia && distancia>=dcorta){   //Distancia media
    interval=350;
    if(modulo==1){
      digitalWrite(buzzer, LOW);
      digitalWrite(ledRed, HIGH);
    }
    
    else{
      digitalWrite(ledRed, LOW);
      digitalWrite(buzzer, HIGH);
    }
    
    digitalWrite(ledGreen, LOW);
  }
  
  else if(distancia<dcorta && distancia>dparo){  //Distancia corta
    interval=100;
    conteo=0;
    if(modulo==1){
      digitalWrite(buzzer, LOW);
      digitalWrite(ledRed, HIGH);
    }
    
    else{
      digitalWrite(buzzer, HIGH);
      digitalWrite(ledRed, LOW);
    }
    
    digitalWrite(ledGreen, LOW);
  }

  
  else if(distancia<=dparo){    //Distancia de paro

    if(conteo<=70){
      digitalWrite(buzzer, HIGH);
      digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, HIGH);
    }
    else{
      digitalWrite(buzzer, LOW);
      digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    }
  }

  
  delay(100);         //Hacemos una pausa de 100ms
}
