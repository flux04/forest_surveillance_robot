void Startup()
{
     //myservo.detach(); 
     Serial.println("Pause for Startup... ");
             
     for (int i=5; i >= 1; i--)                       // Count down for X seconds
      {         
        Serial.print("Pause for Startup... "); 
        Serial.print(i);
        delay(1000);                                   // Delay for X seconds
      }    
    
  Serial.println("Searching for Satellites "); 
      
  while (Number_of_SATS <= 4)                         // Wait until x number of satellites are acquired before starting main loop
  {                                  
    getGPS();                                         // Update gps data
    Number_of_SATS = (int)(gps.satellites.value());   // Query Tiny GPS for the number of Satellites Acquired       
    comm=ReadComm();                                  // Check to see if there are any bluetooth commands being received     
  }    
  setWaypoint();                                      // set intial waypoint to current location
  wpCount = 0;                                        // zero waypoint counter
  ac = 0;                                             // zero array counter
  
  Serial.print(Number_of_SATS);
  Serial.print(" Satellites Acquired");    
}    
 
