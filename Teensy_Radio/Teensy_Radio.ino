/*
External Radio
*/

#include <i2c_t3.h> //Include I2C library instead of the wire library
#include <LiquidCrystal_I2C.h> //liquid crystal i2c library
#include <Bounce.h> //Button debounce library
#include <Encoder.h> //encoder library
LiquidCrystal_I2C lcd(0x27,20,4);  // Set I2C LCD address and colums and lines

//Setup X-plane Variables
//Radio 1
FlightSimInteger com1ActCoarse;
FlightSimInteger com1ActFine;
FlightSimInteger com1StbCoarse;
FlightSimInteger com1StbFine;

FlightSimInteger nav1ActCoarse;
FlightSimInteger nav1ActFine;
FlightSimInteger nav1StbCoarse;
FlightSimInteger nav1StbFine;

FlightSimInteger obs1Val;
FlightSimInteger dme1Val;
FlightSimInteger brg1Val;

//Radio 2
FlightSimInteger com2ActCoarse;
FlightSimInteger com2ActFine;
FlightSimInteger com2StbCoarse;
FlightSimInteger com2StbFine;

FlightSimInteger nav2ActCoarse;
FlightSimInteger nav2ActFine;
FlightSimInteger nav2StbCoarse;
FlightSimInteger nav2StbFine;

FlightSimInteger obs2Val;
FlightSimInteger dme2Val;
FlightSimInteger brg2Val;

//Groundspeed
FlightSimInteger gsdVal;


void setup()
{
  int selNavCom = 0; //Initialize selected radio for initial LCD setup
  
  //Setup X-plane Variables
  //Radio 1  
  com1ActCoarse = XPlaneRef("sim/cockpit2/radios/actuators/com1_frequency_Mhz");
  com1ActFine = XPlaneRef("sim/cockpit2/radios/actuators/com1_frequency_khz");
  com1StbCoarse = XPlaneRef("sim/cockpit2/radios/actuators/com1_standby_frequency_Mhz");
  com1StbFine = XPlaneRef("sim/cockpit2/radios/actuators/com1_standby_frequency_khz");
   
  nav1ActCoarse = XPlaneRef("sim/cockpit2/radios/actuators/nav1_frequency_Mhz");
  nav1ActFine = XPlaneRef("sim/cockpit2/radios/actuators/nav1_frequency_khz");
  nav1StbCoarse = XPlaneRef("sim/cockpit2/radios/actuators/nav1_standby_frequency_Mhz");
  nav1StbFine = XPlaneRef("sim/cockpit2/radios/actuators/nav1_standby_frequency_khz");

  obs1Val = XPlaneRef("sim/cockpit2/radios/actuators/nav1_obs_deg_mag_pilot");
  dme1Val = XPlaneRef("sim/cockpit2/radios/indicators/nav1_dme_distance_nm");
  brg1Val = XPlaneRef("sim/cockpit2/radios/indicators/nav1_bearing_deg_mag");

  //Radio 2
  com2ActCoarse = XPlaneRef("sim/cockpit2/radios/actuators/com2_frequency_Mhz");
  com2ActFine = XPlaneRef("sim/cockpit2/radios/actuators/com2_frequency_khz");
  com2StbCoarse = XPlaneRef("sim/cockpit2/radios/actuators/com2_standby_frequency_Mhz");
  com2StbFine = XPlaneRef("sim/cockpit2/radios/actuators/com2_standby_frequency_khz");
   
  nav2ActCoarse = XPlaneRef("sim/cockpit2/radios/actuators/nav2_frequency_Mhz");
  nav2ActFine = XPlaneRef("sim/cockpit2/radios/actuators/nav2_frequency_khz");
  nav2StbCoarse = XPlaneRef("sim/cockpit2/radios/actuators/nav2_standby_frequency_Mhz");
  nav2StbFine = XPlaneRef("sim/cockpit2/radios/actuators/nav2_standby_frequency_khz");

  obs2Val = XPlaneRef("sim/cockpit2/radios/actuators/nav2_obs_deg_mag_pilot");
  dme2Val = XPlaneRef("sim/cockpit2/radios/indicators/nav2_dme_distance_nm");
  brg2Val = XPlaneRef("sim/cockpit2/radios/indicators/nav2_bearing_deg_mag");

  //Groundspeed
  gsdVal = XPlaneRef("sim/flightmodel/position/groundspeed");

  
  //LCD initialization
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight
  
  //LCD radio display initialization
  //LCD Line 1
  lcd.setCursor ( 0, 0 );//Set cursor for Com course
  lcd.print("000");
  lcd.setCursor ( 3, 0 );//Set cursor for decimal
  lcd.print(".");
  lcd.setCursor ( 4, 0 );//Set cursor for Com fine
  lcd.print("0");
  lcd.setCursor ( 8, 0 );//Set cursor for selected com radio
  lcd.print("COM");
  lcd.setCursor ( 11, 0 );//Set cursor for selected com label
  lcd.print(selNavCom);
  lcd.setCursor ( 12, 0 );//Set cursor for OBS label
  lcd.print("|OBS");
  lcd.setCursor ( 17, 0 );//Set cursor for OBS value
  lcd.print("");

  //LCD Line 2
  lcd.setCursor ( 0, 1 );//Set cursor for Com course
  lcd.print("000");
  lcd.setCursor ( 3, 1 );//Set cursor for decimal
  lcd.print(".");
  lcd.setCursor ( 4, 1 );//Set cursor for Com fine
  lcd.print("0");
  lcd.setCursor ( 12, 1 );//Set cursor for DME label
  lcd.print("|DME");
  lcd.setCursor ( 17, 1 );//Set cursor for DME value
  lcd.print("");

  //LCD Line 3
  lcd.setCursor ( 0, 2 );//Set cursor for Nav course
  lcd.print("000");
  lcd.setCursor ( 3, 2 );//Set cursor for decimal
  lcd.print(".");
  lcd.setCursor ( 4, 2 );//Set cursor for Nav fine
  lcd.print("000");
  lcd.setCursor ( 8, 2 );//Set cursor for selected com radio
  lcd.print("NAV");
  lcd.setCursor ( 11, 2 );//Set cursor for selected com label
  lcd.print(selNavCom);
  lcd.setCursor ( 12, 2 );//Set cursor for BRG label
  lcd.print("|BRG");
  lcd.setCursor ( 17, 2 );//Set cursor for BRG value
  lcd.print("");

  //LCD Line 4
  lcd.setCursor ( 0, 3 );//Set cursor for Nav course
  lcd.print("000");
  lcd.setCursor ( 3, 3 );//Set cursor for decimal
  lcd.print(".");
  lcd.setCursor ( 4, 3 );//Set cursor for Nav fine
  lcd.print("000");
  lcd.setCursor ( 12, 3 );//Set cursor for GSD label
  lcd.print("|GSD");
  lcd.setCursor ( 17, 3 );//Set cursor for GSD value
  lcd.print("");

  
}

void loop() 
{
  int selNavCom = 1;
  // normally the first step in loop() should update from X-Plane
  FlightSim.update();
  if (selNavCom == 1){ //If radio 1 is selected, interact with this radio
          lcd_val_write(selNavCom, 11, 0);// Write active radio to LCD     
          lcd_val_write(com1ActCoarse, 0, 0);// Write active Com 1 coarse to LCD
          lcd_val_write(com1ActFine, 4, 0);// Write active Com 1 fine to LCD
          lcd_val_write(com1StbCoarse, 0, 1);// Write standby Com 1 coarse to LCD
          lcd_val_write(com1StbFine, 4, 1);// Write standby Com 1 fine to LCD

          lcd_val_write(selNavCom, 11, 2);// Write active radio to LCD     
          lcd_val_write(nav1ActCoarse, 0, 2);// Write active Com 1 coarse to LCD
          lcd_val_write(nav1ActFine, 4, 2);// Write active Com 1 fine to LCD
          lcd_val_write(nav1StbCoarse, 0, 3);// Write standby Com 1 coarse to LCD
          lcd_val_write(nav1StbFine, 4, 3);// Write standby Com 1 fine to LCD
          
          //OBS
          lcd_val_cln(obs1Val, 0);//function to clear excess values
          lcd_val_write(obs1Val, 17, 0);//write OBS
          //DME
          lcd_val_cln(dme1Val, 1);
          lcd_val_write(dme1Val, 17, 1);//write DME
          //BRG
          lcd_val_cln(brg1Val, 2);
          lcd_val_write(brg1Val, 17, 2);//write bearing
  }

    else if (selNavCom == 2){ //If radio 2 is selected, interact with this radio
          lcd_val_write(selNavCom, 11, 0);// Write active radio to LCD      
          lcd_val_write(com2ActCoarse, 0, 0);// Write active Com 1 coarse to LCD
          lcd_val_write(com2ActFine, 4, 0);// Write active Com 1 fine to LCD
          lcd_val_write(com2StbCoarse, 0, 1);// Write standby Com 1 coarse to LCD
          lcd_val_write(com2StbFine, 4, 1);// Write standby Com 1 fine to LCD

          lcd_val_write(selNavCom, 11, 2);// Write active radio to LCD   
          lcd_val_write(nav2ActCoarse, 0, 2);// Write active Com 1 coarse to LCD
          lcd_val_write(nav2ActFine, 4, 2);// Write active Com 1 fine to LCD
          lcd_val_write(nav2StbCoarse, 0, 3);// Write standby Com 1 coarse to LCD
          lcd_val_write(nav2StbFine, 4, 3);// Write standby Com 1 fine to LCD
          
          //OBS
          lcd_val_cln(obs2Val, 0);//function to clear excess values
          lcd_val_write(obs2Val, 17, 0);//write OBS
          //DME
          lcd_val_cln(dme2Val, 1);
          lcd_val_write(dme2Val, 17, 1);//write DME
          //BRG
          lcd_val_cln(brg2Val, 2);
          lcd_val_write(brg2Val, 17, 2);//write bearing
  }
  
  
  //GSD
  long gsdValK = gsdVal * 1.94; //Groundspeed conversion from m/s to knots
  lcd_val_write( gsdValK, 17, 3);//write ground speed
  lcd_val_cln(gsdValK, 3);
}

void lcd_val_cln(long val, int row)// function that removes excess variables from lcd when going from a higher number of digits to a lower one
  {
    if (val<10){
        lcd.setCursor ( 18, row );//Set cursor for character clear
        lcd.print("  "); 
    }
    else if (val <100){
        lcd.setCursor ( 19, row );//Set cursor for character clear
        lcd.print(" "); 
    }
      
  }

void lcd_val_write(long val, int col, int row) //LCD writing function
  {
    lcd.setCursor ( col, row );//Set cursor for value
    lcd.print(val);   //print value
}
/************************************************************/
