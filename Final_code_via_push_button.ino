 #include<TinyGPSPlus.h>
 #include<SoftwareSerial.h>
 TinyGPSPlus gps;
 SoftwareSerial gsmSerial(2,3);
 SoftwareSerial gpsSerial(6,7);

float latestLat=28.4877,latestLong=77.0660,lastValidLat,lastValidLoc;
float timee=4.00;
int sensorValue=0;
unsigned long starttime=0;
int heartRate,pulse,count=0;
int SMSSent=0,GSMFlag=0;
int SMSTest,push;
int heartrate=0;
String ATResp;
String VRN;
String tempGSM;
boolean counted=false;
String powerGSM=("AT\n"
"OK\0");
String NWGSM=("AT+CREG?\n"
"+CREG: 0,5\n\n"
"OK\0");
String SMSGSM=("AT+CMGF=1\n"
"OK\0");

#define Bench
#define PULSE_THRESHOLD 120
#define SUCCESS 0
#define FAIL    1
#define VRN "HR26MN7160"
#define PRESED     0
#define NOTPRESSED  1
void setup() {
    pinMode(12,INPUT_PULLUP);
  //intialise GPS()
  GPSInit(); //To DO

  //Initialise GSM 
  GSMInit();  //To DO

  //Initialise serial monitor- Only while bench testing
#ifdef Bench
  Serial.begin(9600); 
#endif
pinMode(A0, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Fetch GPS values
// gpsSerial.listen();
  GPSFetch();

   push=PushFetch();
 
  if((push==PRESED)||(SMSSent==FAIL))
  {
    GSMFlag=GSMCheck();
    if (GSMFlag==SUCCESS)
    {
    SMSSent=GSMSMSTx();
    
    }
    else
    {
      //do nothing
      SMSSent=FAIL;
    }
  }
  else
  {
    //Do nothing
  }

}

void GPSInit()
{
 //To DO 
gpsSerial.begin(9600);

}


void GSMInit()
{
  //To do
  gsmSerial.begin(9600);
}

  void GPSFetch()
{  
  gpsSerial.listen();
//  Serial.println("correct0"); 
// Serial.println(gpsSerial.available());
 
 Serial.println("Pre-Initializing...");
 delay(900);
 while(gpsSerial.available()>0)
  {  if(gps.encode(gpsSerial.read()))
      {
            displayInfo();  //To DO - Fetch time
      }
  }

  
}


void displayInfo()
{ 
   gpsSerial.listen();
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    latestLat=(gps.location.lat(), 6);
   // lastValidLat=latestLat;
    latestLong=(gps.location.lng(), 6);
   // lastValidLong=latestLong;
  }
  else
  {
    Serial.print(F("INVALID"));
    Serial.println(latestLat);
    Serial.println(latestLong);
  }
}

int PushFetch()
{ 
 int a;
 a=digitalRead(12);
 if(a==PRESED)
 { Serial.println("Button is pressed");
    return PRESED;
    while(digitalRead(12)==PRESED)
    {//do nothing;
    }
    
 }
 else{
  Serial.println("Button is not pressed");
  return NOTPRESSED;
 }
     
   
}

int GSMCheck()
{   int a;
   gsmSerial.listen();
//   Serial.println("working");
   gsmSerial.println("AT"); 
   delay(30);   //Once the handshake test is successful, it will back to OK
   ATResp=gsmSerial.readString();
   ATResp.trim();
//   Serial.println(ATResp);
//   Serial.println("working2");
//   Serial.println(powerGSM);
   a=ATResp.compareTo(powerGSM);
//   Serial.println(a);
   if(a==3)
  { Serial.println("Sim module is powered");
    //Serial.println("working2'");
//    Serial.println("correct");

    return SUCCESS;
  }
  else
  { Serial.println("Sim module is not powered");
//   Serial.println("working''");
    return FAIL;
  }
  
}

int GSMSMSTx()
{
  //Serial.println("correct2"); 
  int NWTest;
  gsmSerial.listen();
  NWTest=checkNWStrength();
  if(NWTest==SUCCESS)
  {
    SMSTest=SendSMS();
    if(SMSTest==SUCCESS)
    {
      Serial.println("SMS SENT");
      return SUCCESS;
    }
    else
    {
      //Serial.println("correct3");
      return FAIL;
    } 
  } 
  else
  {
    //Serial.println("correct4");
    return FAIL;
  }
//Serial.println("correct4'");
//  delay(10000);
}


void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    gsmSerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(gsmSerial.available()) 
  {  
    Serial.write(gsmSerial.read());//Forward what Software Serial received to Serial Port
  }
}

int checkNWStrength()
{ int a;
  String GSMResp;
  gsmSerial.listen();
  gsmSerial.println("AT+CREG?");
  //updateSerial();
  GSMResp=gsmSerial.readString();
  GSMResp.trim();
  Serial.println(GSMResp);
  Serial.println("ok");
  Serial.println(NWGSM);
  a=GSMResp.compareTo(NWGSM);
  Serial.println(a);
  if(a==3)
  {Serial.println("SIM Module has established network");
    return SUCCESS;
  }
  else
  {
    Serial.println("NW strength fail");
    return FAIL;
  }
}

int SendSMS()
{
    int a;
    String tempGSM;
    gsmSerial.listen();
    gsmSerial.println("AT+CMGF=1");
    tempGSM=gsmSerial.readString();
    tempGSM.trim();
    Serial.println(tempGSM);
    Serial.println(SMSGSM);
         a=tempGSM.compareTo(SMSGSM);
         Serial.println(a);
//    Serial.println(tempGSM.compareTo("AT+CMGF=1\nERROR\0"));
    if(tempGSM.compareTo(SMSGSM)!=3)
    {
      Serial.println("SIM sms test is falied");
      return FAIL;
    }
    else
    { gsmSerial.println("AT+CMGF=1");
     updateSerial();
      gsmSerial.println("AT+CMGS=\"+917494973778\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
      updateSerial();
      gsmSerial.print(" Hello!, your vehicle with VRN: ");
      gsmSerial.print(VRN);
//      gsmSerial.print(" on:");
//      gsmSerial.print(timee);
  gsmSerial.println("has detected a SOS trigger  ");
      gsmSerial.print(" at http://maps.google.com/maps?q=");
      gsmSerial.print(latestLat);
      gsmSerial.print(",");
      gsmSerial.print(latestLong);
      updateSerial();
      Serial.println("\n");
      gsmSerial.write(26);
      Serial.println("Sim test is successful");
      delay(10000);
      return SUCCESS;
      
     
    } 
    
}
