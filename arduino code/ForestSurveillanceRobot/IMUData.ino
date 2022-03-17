//******************************************************************************************************
// GET VALUES FROM IMU

void getCompass() {
    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 25) {
            magval();
            getHeading();
            Serial.print("HEADING ");
            Serial.println(compass_heading);
            prev_ms = millis();
        }
    }
}


void magval(){
  mx=mpu.getMagX();
  my=mpu.getMagY();
  mz=mpu.getMagZ(); 
    Serial.print("Mag : ");
    Serial.print(mx);
    Serial.print(", ");
    Serial.print(my);
    Serial.print(", ");
    Serial.print(mz);
    Serial.print(", ");
}

void getHeading(void) {
    compass_heading = 180 * atan2(mx, my) / PI;
    if (compass_heading < 0) {
        compass_heading += 360;
    }
}

//******************************************************************************************************
