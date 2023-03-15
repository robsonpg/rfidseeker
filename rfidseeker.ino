/*
*******************************************************************************
* Product: RFID Seeker - QW.Co
* Date: 03/2023
*******************************************************************************
*/

// Biblioteca de Comunicação com leitor de tags
#include "RFID_command.h"


#include "SPI.h"
#include "TFT_eSPI.h"

// The custom font file attached to this sketch must be included
#include "MyFont.h"
#include "Michroma20pt7b.h"
#include "Michroma10pt7b.h"

#define TEST_TEXT "ßäöü ñâàå"   // Text that will be printed on screen in the font
//#define TEST_TEXT "Hello"     // Text that will be printed on screen in the font

// Stock font and GFXFF reference handle
#define GFXFF 1

// Easily remembered name for the font
#define MYFONT20 &Michroma20pt7b
#define MYFONT10 &Michroma10pt7b

// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();

// Interface com leitor de RFID
UHF_RFID RFID;

String comd = " ";
CardpropertiesInfo card;
ManyInfo cards;
SelectInfo Select;
CardInformationInfo Cardinformation;
QueryInfo Query;
ReadInfo Read;
TestInfo Test;

void setup() {

  Serial.begin(115200);
  Serial.println("Iniciando aplicativo.");

  // Inicializa a comunicação com o leitor de RFID
  RFID._debug = 0;

  Serial.println("Iniciando serial 2 de comunicação com leitor.");
  // A serial 2 é usada internamente no objeto UHF_RFID para cominicar com o leitor de RFID
  Serial2.begin(115200, SERIAL_8N1, 27, 26);

  // UHF_RFID set UHF_RFID设置
  Serial.println("Comunicando com leitor...");

  // String soft_version;
  //  RFID.Set_transmission_Power(2600);
  //  Serial.println("Comunicando com leitor 2...");
  //  RFID.Set_the_Select_mode(0);
  //  Serial.println("Comunicando com leitor 3...");
  //  RFID.Delay(100);
  //  Serial.println("Comunicando com leitor 4...");
  //  RFID.Readcallback();
  //  Serial.println("Comunicando com leitor 5...");
  //  RFID.clean_data();

  // Prompted to connect to UHF_RFID 提示连接UHF_RFID
  Serial.println("UHF_RFID na serial 2.");

  String soft_version;
  while (soft_version.indexOf("V2.3.5") == -1) {
       RFID.clean_data();
       RFID.Delay(150);
       RFID.Delay(150);
       soft_version = RFID.Query_software_version();
  }
    
  Serial.println("Leitor de RFID pronto.");

  // Inicialiizando o display
  tft.begin();

  tft.setRotation(1);
  // Set text datum to middle centre (MC_DATUM)
  tft.setTextDatum(TL_DATUM);
  tft.setTextPadding(0);
  tft.fillScreen(TFT_BLACK);   

    // Set text colour to white with black background
  tft.setTextColor(TFT_WHITE, TFT_BLACK);      // White characters on black background

  //tft.fillScreen(TFT_BLUE);                    // Clear screen
  tft.setFreeFont(MYFONT20);                   // Select the font
  tft.drawString("QW.Co", 0, 0, GFXFF); // Print the name of the font
  tft.setFreeFont(MYFONT10);                   // Select the font
  tft.drawString("RFID Seeker", 0, 45, GFXFF); // Print the name of the font
}

void loop() {
    //  A read/write operation specifies a particular card
    //  读写操作需指定某一张卡 comd =
    //  RFID.Set_the_select_parameter_directive("30751FEB705C5904E3D50D70");
    //  Serial.println(comd);
    //  RFID.clean_data();

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     Query the card information once 查询一次卡的信息例子
     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    card = RFID.A_single_poll_of_instructions();
    if (card._ERROR.length() != 0) {
        Serial.println(card._ERROR);
    } else {
        if (card._EPC.length() == 24) {
            Serial.println("RSSI :" + card._RSSI);
            Serial.println("PC :" + card._PC);
            Serial.println("EPC :" + card._EPC);
            Serial.println("CRC :" + card._CRC);
            Serial.println(" ");
        }
    }
    RFID.clean_data();  // Empty the data after using it
                        // 使用完数据后要将数据清空
  tft.setFreeFont(MYFONT10);                   
  tft.drawString("IDs encontrados:", 0, 80, GFXFF); 
    /*Other feature usage examples 其他功能使用例子*/

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      Read multiple RFID cards at once 一次读取多张RFID卡
      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*  cards = RFID.Multiple_polling_instructions(6);
     for (size_t i = 0; i < cards.len; i++)
     {
       if(cards.card[i]._EPC.length() == 24)
         {
            Serial.println("RSSI :" + cards.card[i]._RSSI);
            Serial.println("PC :" + cards.card[i]._PC);
            Serial.println("EPC :" + cards.card[i]._EPC);
            Serial.println("CRC :" + cards.card[i]._CRC);
          }
     }
     Serial.println(" ");
     RFID.clean_data();
     */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      Used to get the SELECT parameter 用于获取Select参数
      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    //  Select = RFID.Get_the_select_parameter();
    //  if(Select.Mask.length() != 0)
    //  {
    //    Serial.println("Mask :" + Select.Mask);
    //    Serial.println("SelParam :" + Select.SelParam);
    //    Serial.println("Ptr :" + Select.Ptr);
    //    Serial.println("MaskLen :" + Select.MaskLen);
    //    Serial.println("Truncate :" + Select.Truncate);
    //    Serial.println(" ");
    //  }
    //    RFID.clean_data();

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      Used to change the PSF bit of the NXP G2X label 用于改变 NXP G2X 标签的
      PSF 位
      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    //  Cardinformation = RFID.NXP_Change_EAS(0x00000000);
    //  if(Cardinformation._UL.length() != 0)
    //  {
    //    Serial.println("UL :" + Cardinformation._UL);
    //    Serial.println("PC :" + Cardinformation._PC);
    //    Serial.println("EPC :" + Cardinformation._EPC);
    //    Serial.println("Parameter :" + Cardinformation._Parameter);
    //    Serial.println("ErrorCode :" + Cardinformation._ErrorCode);
    //    Serial.println("Error :" + Cardinformation._Error);
    //    Serial.println("Data :" + Cardinformation._Data);
    //    Serial.println("Successful :" + Cardinformation._Successful);
    //    Serial.println(" ");
    //   }
    //    RFID.clean_data();

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      Used to get the Query parameters 用于获取Query参数
      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    //  Query = RFID.Get_the_Query_parameter();
    //  if(Query.QueryParameter.length() != 0)
    //  {
    //    Serial.println("QueryParameter :" + Query.QueryParameter);
    //    Serial.println("DR :" + Query.DR);
    //    Serial.println("M :" + Query.M);
    //    Serial.println("TRext :" + Query.TRext);
    //    Serial.println("Sel :" + Query.Sel);
    //    Serial.println("Session :" + Query.Session);
    //    Serial.println("Targetta :" + Query.Target);
    //    Serial.println("Q :" + Query.Q);
    //    Serial.println(" ");
    //  }
    //  RFID.clean_data();

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      Used to get the Query parameters 用于读取接收解调器参数
      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    //  Read = RFID.Read_receive_demodulator_parameters();
    //  if(Read.Mixer_G.length()!= 0)
    //  {
    //    Serial.println("Mixer_G :" + Read.Mixer_G);
    //    Serial.println("IF_G :" + Read.IF_G);
    //    Serial.println("Thrd :" + Read.Thrd);
    //    Serial.println(" ");
    //  }
    //  RFID.clean_data();
}
