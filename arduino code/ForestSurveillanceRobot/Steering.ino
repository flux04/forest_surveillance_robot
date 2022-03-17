
void Forward()
{
digitalWrite(enR, HIGH);
digitalWrite(enL, HIGH);
analogWrite(pwmR, 200);
analogWrite(pwmL, 200);
}

void backward(){
digitalWrite(enR, LOW);
digitalWrite(enL, LOW);
analogWrite(pwmR, 150);
analogWrite(pwmL, 150);
}

// **********************************************************************************************************************************************************************


void LeftTurn()
{
   
  analogWrite(pwmR, 100);
  analogWrite(pwmL, 180);         
  digitalWrite(enR, LOW);
  digitalWrite(enL, HIGH);
}

// **********************************************************************************************************************************************************************

// Turning too fast will over-shoot the compass and GPS course


void RightTurn()                                                            //replace with functions for L298P
{
   
  analogWrite(pwmR, 180);
  analogWrite(pwmL, 100);         

  digitalWrite(enR, HIGH);
  digitalWrite(enL, LOW);
}

// **********************************************************************************************************************************************************************

//motor functions-------------------------------------------------------------------------------------------------------------------------------------------------------------------
void leftshort()
{
  
  digitalWrite(enR, LOW);
  digitalWrite(enL, HIGH);
  analogWrite(pwmR, 175);
  analogWrite(pwmL, 255);
  delay(100);
  StopCar();
}

void rightshort()
{
  digitalWrite(enR, HIGH);
  digitalWrite(enL, LOW);
  analogWrite(pwmR, 255);
  analogWrite(pwmL, 175);
  delay(100);
  StopCar();
}

// **********************************************************************************************************************************************************************

// right and left turn for scanning function (90 degree turns)
void rightscan()
{
digitalWrite(enR, HIGH);
digitalWrite(enL, LOW);
analogWrite(pwmR, 255);
analogWrite(pwmL, 200);
delay(700);
StopCar();
}

void leftscan()
{
digitalWrite(enR, LOW);
digitalWrite(enL, HIGH);
analogWrite(pwmR, 200);
analogWrite(pwmL, 255);
delay(700);
StopCar();
}

void forward(){
digitalWrite(enR, HIGH);
digitalWrite(enL, HIGH);
analogWrite(pwmR, 150);
analogWrite(pwmL, 150);
delay(100);
}

void StopCar(){
analogWrite(pwmR, 0);
analogWrite(pwmL,0);
delay(250);
}



   
    

  
