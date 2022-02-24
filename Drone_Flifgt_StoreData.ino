#include <RMTT_Effect.h>
#include <RMTT_Fonts.h>
#include <RMTT_GamesirT1d.h>
#include <RMTT_Libs.h>
#include <RMTT_Matrix.h>
#include <RMTT_Protocol.h>
#include <RMTT_RGB.h>
#include <RMTT_Shell.h>
#include <RMTT_TOF.h>
#include <Wire.h>
#include <RMTT_Libs.h>
#include <EEPROM.h>


// Dynamic variables
volatile int  mind_n_Department_ID, mind_n_RANDOM_NUM;
  //Store the data in to flash address(using EEPROM) each turn   ( 4 vaiables *200 times)
  int addr = 0; 
   
// Function declaration
void matrixDisplayText(int text, char color, uint8_t light);

// Create an object
RMTT_Protocol protocol;
RMTT_TOF      tt_sensor;
RMTT_Matrix   tt_matrix;
RMTT_RGB      tt_rgb;


// Main program start
void setup() {
  
  //random seed
  randomSeed(analogRead(2));
  Serial1.begin(1000000, 23, 18, SERIAL_8N1);
 
 //Using EEPROM to save data during the flight
 //only have 4096 locations on EEPROM memory (byte value 0-4096) 
  EEPROM.begin(4096);
 Wire.begin(27, 26);
 
  tt_sensor.Init();
  tt_matrix.Init(127);
  tt_matrix.SetLEDStatus(RMTT_MATRIX_CS, RMTT_MATRIX_SW, RMTT_MATRIX_LED_ON);
  matrix_effect_init(255);
  tt_rgb.Init();
  led_effect_init();

  
  //press the monitor button start the program 
  protocol.startUntilControl();

  //wait for 5 secs
  delay(5000);

  //the 4 motors start to move
  protocol.sendTelloCtrlMsg("motoron");
  
  //The drone start to fly up
  protocol.sendTelloCtrlMsg("takeoff");
  
  protocol.sendTelloCtrlMsg((char *)String(String("up ")+int(50)).c_str());
  


  
  //set 200 times loop for the number of the flight
   for (int index = 0; index < 200; index++) {

 
  //randomly generate 6 different departments ID number and department string name
      mind_n_Department_ID = (random(1, 6+1));


     //Writing department ID to location 
    // int data= mind_n_Department_ID;
       EEPROM.write(addr, mind_n_Department_ID);
       addr++;
      //go to the position "B" X=285CM,Y=275CM
      protocol.sendTelloCtrlMsg((char *)String(String("go ")+int(285)+" "+int(275)+" "+int(0)+" "+int(50)).c_str());

       //randomly generate the number to decide the dicision of the document approval
      mind_n_RANDOM_NUM = (random(1, 2+1));
      if ((mind_n_RANDOM_NUM<2)) {

        //if manager(director office) accept the document
        //the document got accept and the display monitor for blue "A"
        matrixDisplayText('A', 'b', 255);

         //go to the next position X=285CM,Y=275CM
        protocol.sendTelloCtrlMsg((char *)String(String("go ")+int(285)+" "+int(275)+" "+int(0)+" "+int(50)).c_str());
        delay(3000);

         //randomly generate the number to decide the dicision of the document approval
           //the dicision will go to financial department
        mind_n_RANDOM_NUM = (random(1, 2+1));

      
        //if financial manager approve the document
        if ((mind_n_RANDOM_NUM<2)) {
          matrixDisplayText('A', 'b', 255);
           //make the clockwise 90 degree turn back to the first postion
          protocol.sendTelloCtrlMsg((char *)String(String("cw ")+int(90)).c_str());
          protocol.sendTelloCtrlMsg((char *)String(String("go ")+int(285)+" "+int(275)+" "+int(0)+" "+int(50)).c_str());
       

         //Writng status approval to location2  1 for approved 2 for denied 
          int data2= 1;
          EEPROM.write(addr, data2);
           addr++;

           //Writng status approval to location3 1 for approved 2 for denied 
            int data3= 1;
         EEPROM.write(addr, data3);
           addr++;

           //write the route number (3 for all three points)
           int data4= 3;
          EEPROM.write(addr, data4);
           addr++;      
        }
        else {
           //the document got denied and set the display monitor for red "D"
          matrixDisplayText('D', 'r', 255);

           //make the clockwise 90 degree turn back to the first postion
          protocol.sendTelloCtrlMsg((char *)String(String("cw ")+int(90)).c_str());
          protocol.sendTelloCtrlMsg((char *)String(String("go ")+int(285)+" "+int(275)+" "+int(0)+" "+int(50)).c_str());
            //land to the ground
          protocol.sendTelloCtrlMsg("land");
 
          //Writng status approval to location2  1 for approved 2 for denied 
           int data2= 1;
          EEPROM.write(addr, data2);
           addr++; 
           //Writng second status approval to location2  1 for approved 2 for denied 
          int data3= 2;
          EEPROM.write(addr, data3);
           addr++; 
            //write the route number (2 for two points)
         int data4= 2;
          EEPROM.write(addr, data4);
           addr++; 
        }
      }
      else {
         //the document got denied and set the display monitor for red "D"
        matrixDisplayText('D', 'r', 255);
         //make the clockwise 90 degree turn back to the first postion
        protocol.sendTelloCtrlMsg((char *)String(String("cw ")+int(90)).c_str());
        protocol.sendTelloCtrlMsg((char *)String(String("go ")+int(285)+" "+int(275)+" "+int(0)+" "+int(50)).c_str());
        protocol.sendTelloCtrlMsg("land");

        
        //the status got denied
        //Writng status approval to location2  1 for approved 2 for denied 
         int data2= 2;
          EEPROM.write(addr, data2);
           addr++; 

        //Writng second status approval to location2  1 for approved 2 for denied 
        int data3= 0;
          EEPROM.write(addr, data3);
           addr++; 
           
        //back to the original department
         //write the route number (1 for only the first points)
         int data4= 1;
          EEPROM.write(addr, data4);
           addr++;
 
      }

 }
 //save the EEPROM data
   EEPROM.commit(); 
 Serial.println("End write");

  protocol.sendTelloCtrlMsg("land");
  led_effect_deinit();
  protocol.sendTelloCtrlMsg("motoroff");
  
}
void loop() {
 
  
}



// Function declaration 
void matrixDisplayText(int text, char color, uint8_t light){
  uint8_t buff[128];
  mled_font2buff(buff, text, color, light);
  matrix_effect_set_graph(buff);
}
