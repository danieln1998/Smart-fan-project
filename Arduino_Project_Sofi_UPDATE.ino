
#include <DHT_U.h>
#include <DHT.h> 

#define DHTPIN D6     
#define DHTTYPE DHT11   
     
DHT dht(DHTPIN, DHTTYPE); 

#define A1A D2
#define A1B D1

#define btnG D4
#define btnR D3


unsigned long milStart;

int click;
int tempVal;

int cnt;

int debouceTime = 50;

int lastStateGreen = LOW; 
int lastState2Green = LOW;  
int currentState2Green;                  
unsigned long lastBtnReleaseTimeGreen;
unsigned long lastBtnReleaseTime2Green;


int lastStateRed = LOW; 
int lastState2Red = LOW; 
int currentState2Red;                
unsigned long lastBtnReleaseTimeRed;
unsigned long lastBtnReleaseTime2Red;


int currentState;
int pos=0;
float temperature;


void setup() {
  // put your setup code here, to run once:
pinMode(A1A, OUTPUT);
pinMode(A1B, OUTPUT);
pinMode(btnG, INPUT_PULLUP);
pinMode(btnR, INPUT_PULLUP);
dht.begin(); 

Serial.begin(9600);

lastBtnReleaseTimeGreen = millis();
lastBtnReleaseTimeRed=millis();

lastBtnReleaseTime2Green=millis();
lastBtnReleaseTime2Red=millis();


wifi_setup();

}

void loop() {
  

 wifi_loop();
 MainAction();

}
  void MainAction(){
  temperature= dht.readTemperature();
 
    if(pos==1){
      click=1;
      cnt=1;
      milStart=millis();
      pos=0;
     
    }
 
   if(cnt==1){
        click_fan();  
       FanFwd();
      
   }

 
    if(pos==2){
        cnt=5;
        pos=0;
    }


   if(cnt==5){
     fanOff();     
      
   }
  




if(pos==3)
{
 click=1;
  cnt=2;
   pos=0;
 
  //  Serial.println("yes");  
}


  
if (cnt==2){
 
  
    // Serial.println(temperature);
    if(temperature>tempVal){
      cnt=3;
        milStart=millis();
        // Serial.println("ok");
       
    }
    else{
      fanOff();
    }

    if(cnt==2){

        lastState2Green = currentState2Green;
        lastState2Red = currentState2Red;
    }

  

  
  
   }



     if(cnt==3){
      
      
      if(temperature<tempVal){
        cnt=2;
         
        
      
      }
       
       click_fan();
      
        // Serial.println("rr");
        FanFwd();

        lastState2Green = currentState2Green;
        lastState2Red = currentState2Red;
      
    
          
       }

      Click2btn();
     isClick(btnG,lastStateGreen,lastBtnReleaseTimeGreen,1 );
     isClick(btnR,lastStateRed,lastBtnReleaseTimeRed,2);


    
}




void FanFwd(){
  
   
  if(millis()-milStart>2000){
     
   digitalWrite(A1A,LOW);
   digitalWrite(A1B,LOW);

        
  if(millis()-milStart>6000){
     
   digitalWrite(A1A,HIGH);
   digitalWrite(A1B,LOW);

     
  milStart=millis();

  }


  }


    
}


void fanOff() {
	    digitalWrite(A1A, LOW);
	    digitalWrite(A1B, LOW);
	}


void isClick(int btn,int lastState,unsigned long lastBtnReleaseTime,int flag ) {
  
  
  currentState = digitalRead(btn);

  if((lastState == HIGH && currentState == LOW)&&(millis() - lastBtnReleaseTime > debouceTime)){
    
     if(flag==1){
      // Serial.println("The button Green is pressed");
      
     
         pos=1;       
     }

     if(flag==2){
//  Serial.println("The button Red is pressed");
 
   
       pos=2;

     }
   
  }
   
 else if((lastState == LOW && currentState == HIGH)&&(millis() - lastBtnReleaseTime > debouceTime)){

if( flag==1){
  // Serial.println("The button Green is released");

  lastBtnReleaseTimeGreen = millis();

}
 
 if(flag==2){
// Serial.println("The button Red is released");

   lastBtnReleaseTimeRed = millis();


 }


  }
    

  if(flag==1){

    lastStateGreen = currentState;
  }

  if(flag==2){

    lastStateRed = currentState;
  }
  
}



void Click2btn(){

  
currentState2Green = digitalRead(btnG);
currentState2Red = digitalRead(btnR);


if((lastState2Green == HIGH && currentState2Green == LOW)&&(millis() - lastBtnReleaseTime2Green > debouceTime)&&
(lastState2Red == HIGH && currentState2Red == LOW)&&(millis() - lastBtnReleaseTime2Red > debouceTime)){
pos=3;
 
   
}
 else if((lastState2Green == LOW && currentState2Green == HIGH)&&(millis() - lastBtnReleaseTime2Green > debouceTime)){
// Serial.println("The button Green is releasedXXXX");

   lastBtnReleaseTime2Green=millis();
  lastState2Green = currentState2Green;
   
  


  }
   else if((lastState2Red == LOW && currentState2Red == HIGH)&&(millis() - lastBtnReleaseTime2Red > debouceTime)){
// Serial.println("The button Red is releasedXXX");

  lastBtnReleaseTime2Red=millis();
    lastState2Red = currentState2Red;
   

  }


      
        
  
}

void click_fan(){

    if(click==1){
         digitalWrite(A1A,HIGH);
         digitalWrite(A1B,LOW);
         click++;
        
        }
}
 

  






