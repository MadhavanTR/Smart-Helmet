#include <SoftwareSerial.h>
#include <TinyGPS.h>

long lat,lon; // create variable for latitude and longitude object
double dlat=0,dlon=0;
SoftwareSerial gpsSerial(4, 3); // create gps sensor connection
//SoftwareSerial mySerial(9, 10);

TinyGPS gps; // create gps object
boolean ENABLE =1;
boolean DISABLE=0;

int vib  = 6;
int led = 13;
long sen;
int gpsdetectFlag=0;


void gpsLocation();
static void vibration();
static void gsm();

void setup(){
  Serial.begin(9600); // connect serial
  gpsSerial.begin(9600); // connect gps sensor
  //mySerial.begin(9600);
  delay(100);
  delay(5000);
  pinMode(vib, INPUT);
  pinMode(led , OUTPUT); // not needed
  
}

void loop(){
  
 delay(100);
 vibration();
 //gpsLocation();
}
#if 1
static void gsm()
{
  
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(2000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+919962881127\"\r"); // Replace x with mobile number
  delay(2000);
  dlat=(double)lat;
  dlon=(double)lon;
  dlat=dlat/1000000;
  dlon=dlon/1000000;
  Serial.println("ACCIDENT!!!!!!!!!   LOCATION-----");// The SMS text you want to send
  delay(2000);
  Serial.print("https://www.google.co.in/maps/@");
  delay(2000);
  Serial.print(dlat);
  delay(2000);
      Serial.print(",");
        delay(2000);

      Serial.print(dlon);
        delay(2000);

      Serial.println(",15z");
        delay(2000);


  //dlat=(double)(lat/10000000.0);
    //dlon=(double)(lon/10000000.0);

  //Serial.print(lat);
    //Serial.print(",");

  //delay(1000);
  //Serial.println(dlon);
  //delay(3000);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(3000);
}
#endif

void gpsLocation()
{
     
     gpsdetectFlag=DISABLE;

  while(gpsdetectFlag!=ENABLE)
  {
      //Serial.println("gps data");
  while(gpsSerial.available()){ // check for gps data
   if(gps.encode(gpsSerial.read())){ // encode gps data
    gps.get_position(&lat,&lon); // get latitude and longitude
    gpsdetectFlag=ENABLE;
    // display position
    //Serial.print("Position: ");
    //Serial.print("lat: ");Serial.print(lat);Serial.print(" ");// print latitude
    //Serial.print("lon: ");Serial.println(lon); // print longitude
gsm();    
   }
   
  } 
  //delay(1000);
}

}

static void vibration()
{

  sen=pulseIn(vib, HIGH);
  //Serial.println(sen);

  if  ( sen > 2500)
  {
    //Serial.println("fetching gps");
    gpsLocation();
    digitalWrite(led, HIGH );
    delay (1000);
    digitalWrite(led , 0);
    
    
  }
  
   delay(100);
}


