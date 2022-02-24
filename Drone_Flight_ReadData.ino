#include <EEPROM.h> 

 // Dynamic variables
int i = 0;
String mind_s_Department, mind_s_STATUS, mind_s_STATUS_2, mind_s_ROUTE;




// Main program start
void setup() {

   // set serial band to 9600
  Serial.begin(9600);
  //clear the excel sheet
  Serial.println("CLEARSHEET");

  //set the first row label 
  Serial.println("LABEL,Date,Department,Status_1,Status_2,Doc_ID,Route");

  //set the EEPROM number of locations
  EEPROM.begin(4096);

 


//there are 800 locations from EEPROM 200 times flight*4 variables
for(int addr = 0; addr<800; addr++){
  //read the data from the memory of EEPROM
  int data = EEPROM.read(addr); 


//THE first variable (department ID TO Department name
  if(((addr+1)%4 == 1)){
     //randomly generate 6 different departments ID number and department string name
   
   //write the data to excel
   //call the date data
  Serial.print("DATA,DATE,");

      if ((data==1)) {
        mind_s_Department = "Sales Department";
      }
      else if ((data==2)) {
        mind_s_Department = "Purchasing Department";
      }
      else if ((data==3)) {
        mind_s_Department = "HR Department";
      }
      else if ((data==4)) {
        mind_s_Department = "Advertising Departmen";
      }
      else if ((data==5)) {
        mind_s_Department = "Marketing Department";
      }
      else {
        mind_s_Department = "Technolog Department";
      }


  //which department sent the request
  Serial.print(mind_s_Department);

   Serial.print(",");
    
    }

//THE second variable (status approval 
  if(((addr+1)%4 == 2)){
    
    if((data==1)){
       
          mind_s_STATUS = "Approved";
         
      }else{
         mind_s_STATUS = "Denied";
        }


        //the next department(director office)
   //status of approval in director decision
    Serial.print(mind_s_STATUS);
      Serial.print(",");
    }


//THE third variable (status approval 
  if(((addr+1)%4 == 3)){
    
    if((data==1)){
      mind_s_STATUS_2 = "Approved";
      }else if((data==2)){
          mind_s_STATUS_2 = "Denied";
        }else{
          mind_s_STATUS_2 = "X";
          }


            //the final department (financial department)
      //status of approval in financial decision
    Serial.print(mind_s_STATUS_2);
     Serial.print(",");
      //document ID
     Serial.print(i++);
      Serial.print(",");
    }



   //THE fourth variable (route)
  if(((addr+1)%4 == 0)){
    
    if((data==1)){
       mind_s_ROUTE = mind_s_Department;
      }else if((data==2)){
          mind_s_ROUTE = (String(mind_s_Department) + String("+Direcotor"));
        }
        else{
          mind_s_ROUTE = (String(mind_s_Department) + String("+Direcotor+Financial"));
          }
           //The route of  document department process & skip to next line
          Serial.println(mind_s_ROUTE);
       
    }



    
  }
 
 
}

  

//using loop to generate the data

void loop() {  

   
}
