 // ************************************************************************************************************************************************* 

void getGPS()                                                 // Get Latest GPS coordinates
{
    while (Serial2.available() > 0)
    gps.encode(Serial2.read());
} 

// *************************************************************************************************************************************************
 
void setWaypoint()                                            // Set up to 5 GPS waypoints
{

//if ((wpCount >= 0) && (wpCount < 50))
if (wpCount >= 0)
  {
    Serial.print("GPS Waypoint ");
    Serial.print(wpCount + 1);
    Serial.print(" Set ");
    getGPS();                                                 // get the latest GPS coordinates
    getCompass();                                             // update latest compass heading     
    Home_LATarray[ac] = gps.location.lat();                   // store waypoint in an array   
    Home_LONarray[ac] = gps.location.lng();                   // store waypoint in an array                                                                
    Serial.print("Waypoint #1: ");
    Serial.print(Home_LATarray[0],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[0],6);
    Serial.print("Waypoint #2: ");
    Serial.print(Home_LATarray[1],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[1],6);
    Serial.print("Waypoint #3: ");
    Serial.print(Home_LATarray[2],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[2],6);
    Serial.print("Waypoint #4: ");
    Serial.print(Home_LATarray[3],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[3],6);
    Serial.print("Waypoint #5: ");
    Serial.print(Home_LATarray[4],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[4],6);
    wpCount++;                                                  // increment waypoint counter
    ac++;                                                       // increment array counter
  }         
  else {Serial.print("Waypoints Full");}
}

// ************************************************************************************************************************************************* 

void clearWaypoints()
{
   memset(Home_LATarray, 0, sizeof(Home_LATarray));             // clear the array
   memset(Home_LONarray, 0, sizeof(Home_LONarray));             // clear the array
   wpCount = 0;                                                 // reset increment counter to 0
   ac = 0; 
   Serial.print("GPS Waypoints Cleared");                      // display waypoints cleared
}

 // *************************************************************************************************************************************************
 
 
void gpsInfo()                                                  // displays Satellite data to user
  {
  Number_of_SATS = (int)(gps.satellites.value());         //Query Tiny GPS for the number of Satellites Acquired 
  Distance_To_Home = TinyGPSPlus::distanceBetween(gps.location.lat(),gps.location.lng(),Home_LATarray[ac], Home_LONarray[ac]);  //Query Tiny GPS for Distance to Destination    
  Serial.print("Lat:");
  Serial.print(gps.location.lat(),6);
  Serial.print(" Lon:");
  Serial.print(gps.location.lng(),6);
  Serial.print(" ");
  Serial.print(Number_of_SATS); 
  Serial.print(" SATs ");
  Serial.print(Distance_To_Home);
  Serial.print("m"); 
  Serial.print("Distance to Home ");
  Serial.println(Distance_To_Home);
  }
