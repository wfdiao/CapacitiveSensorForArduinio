#include <CapacitiveSensor.h>

/*
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */
int ledr = 21;
int ledg = 20;
int ledb = 19;
int motor = 0;
int motor2 = 3;

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

void setup()                    
{
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
   pinMode(ledr, OUTPUT);
   pinMode(ledg, OUTPUT);
   pinMode(ledb, OUTPUT);
   pinMode(motor,OUTPUT);
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);
    
      

   // Serial.print(millis() - start);        // check on performance in milliseconds
   // tab character for debug windown spacing

    Serial.print(total1);                  // print sensor output 1
   Serial.print("\n");
  if (total1>200)
    { 
     if (total1>1500)
        {
          if( total1>3000)
            { digitalWrite(ledr,LOW);
              analogWrite(motor, 175);
              analogWrite(motor2, 175);
              
            delay(1000);  
            analogWrite(motor,0);
            analogWrite(motor2, 0);
            digitalWrite(ledr,HIGH);
            }
            
            else 
                {
                  digitalWrite(ledg,LOW);
                analogWrite(motor, 130 );
                delay(1000); 
               analogWrite(motor,0); 
               digitalWrite(ledg,HIGH);
                 }
         }
         else {digitalWrite(ledb,LOW);analogWrite(motor, 50);delay(1000); analogWrite(motor, 0); digitalWrite(ledb,HIGH);}
    }
    else {
    digitalWrite(ledr,HIGH);
    digitalWrite(ledg,HIGH);
    digitalWrite(ledb,HIGH);
    analogWrite(motor, 0);
    analogWrite(motor2,0);
    
    }
      
    delay(10);                             // arbitrary delay to limit data to serial port 
}
