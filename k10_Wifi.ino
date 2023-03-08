#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>



IPAddress    apIP(55, 55, 55, 55); 
const char* ssid = "Daniel"; //שם הרשת שיוצג
const char* password = "88888888";// הסיסמה לרשת אם נרצה להשתמש בה 

ESP8266WebServer server(80); 

void wifi_loop() {
      server.handleClient();//.server is defined at this tab
      delay(10);
  } 
void wifi_setup(){
   WiFi.mode(WIFI_AP_STA);
   WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00   
   WiFi.softAP(ssid); 
//   WiFi.softAP(ssid,password); 

  server.on("/", handleRoot); 
  server.on("/temp", tempPage);  
  server.onNotFound(handleNotFound); 
  server.begin(); 
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  
}
void handleRoot(){
 

       if (server.hasArg("Val")) {
         
       
    if(server.arg("Val")=="הפעל מאוורר תמיד"){
            cnt = 1;
            milStart=millis();
            click=1;
            RetMain();

    }
   }

  if (server.hasArg("Val2")) {   
      
     if(server.arg("Val2")=="כבה מאוורר תמיד" ){
            cnt = 5;
            RetMain();
        

    }
    }
 
        if (server.hasArg("Val3")) {
         
       if(server.arg("Val3")=="הפעל מאוורר לפי הטמפרטורה שהוזנה" ){
            cnt = 2;
             click=1;
            RetMain();

      }
    }



   char tmp[5]=""; 
  char html[2000]="";
  strcat(html, "<html>");
  strcat(html, "<head>");
  strcat(html, "<meta charset=\"UTF-8\">");
  strcat(html, "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
  strcat(html, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
 
     

      strcat(html, "<META HTTP-EQUIV=\"refresh\" CONTENT=\"1\">");
     
   
  
     
  strcat(html, "<title>Smart Fan</title>");
  strcat(html, "<style>");
  strcat(html, "body{");
  strcat(html, "background-color: aquamarine;}");
  strcat(html, "</style>");
  strcat(html, "</head>");
  strcat(html, "<body>");
  strcat(html, "<h1>מאוורר חכם </h1> ");

 

  strcat(html, "<form action=\"\" method=\"get\">");
 
 
  strcat(html, "<input type=\"submit\" name=\"Val\"  value=\"הפעל מאוורר תמיד");
  
  strcat(html, "\">");
    strcat(html, "<br>");
    strcat(html, "<br>");
  strcat(html, "<input type=\"submit\" name=\"Val2\"  value=\"כבה מאוורר תמיד");
  strcat(html, "\">");
    strcat(html, "<br>");
    strcat(html, "<br>");

    strcat(html, "<input type=\"submit\" name=\"Val3\"  value=\"הפעל מאוורר לפי הטמפרטורה שהוזנה");
  strcat(html, "\">");
    strcat(html, "<br>");
    strcat(html, "<br>");    
 
  strcat(html, "</form>");

  strcat(html, "<form id=\"fc\" action=\"\" method=\"get\">");
  strcat(html, "<input type=\"hidden\" id=\"clickG\"  name=\"clickG\"  value=\"update");
  strcat(html, "\">");
   strcat(html, "<input type=\"submit\" id=\"sub\" value=\"לעדכון טמפרטורה לחץ כאן");
   strcat(html, "\">");
    strcat(html, "<br>");
    strcat(html, "<br>");
  
strcat(html, "</form>");

   if(cnt==1){
        strcat(html, "<p>המאורר עובד תמיד");
            strcat(html, " </p> ");
   }

     if(cnt==5){
        strcat(html, "<p>המאוורר כבוי תמיד");
            strcat(html, " </p> ");
   }
      if(cnt==2||cnt==3){
        strcat(html, "<p>המאוורר במצב עבודה לפי הטמפרטורה שהוזנה");
            strcat(html, " </p> ");
   }

     strcat(html, "<br>");
    strcat(html, "<br>");

    strcat(html, "<p>הטמפרטורה עכשיו היא ");
    itoa(temperature, tmp, 10);
    strcat(html, tmp );
    strcat(html, " </p> ");

         if (server.hasArg("clickG")) {
         
       if(server.arg("clickG")=="update"){
           server.sendHeader("Location","/temp");
    server.sendHeader("Cache-Control","no-cache");
    server.send(301);
    return;

      }
    }

  strcat(html, "</body>");
  strcat(html, "</html>");
  
  server.send(200, "text/html", html);
}

// ----------------------------------------------------
// ----------------------------------------------------

void tempPage(){



      if (server.hasArg("ValTemp")) {
      tempVal = server.arg("ValTemp").toInt();
       RetMain();

  }
  char html[2000]="";
char tmp[5]="";
  strcat(html, "<html>");
  strcat(html, "<head>");
  strcat(html, "<meta charset=\"UTF-8\">");
  strcat(html, "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
  strcat(html, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
 
 strcat(html, "<style>");
  strcat(html, "body{");
  strcat(html, "background-color: aquamarine;}");
  strcat(html, "</style>");


  strcat(html, "</head>");
    strcat(html, "<body>");

strcat(html, "<h1>עדכן את הטמפרטורה</h1> ");
strcat(html, "<form action=\"\" method=\"get\">");

     strcat(html, "הכנס טמפרטורה");
  strcat(html, "<input type=\"number\" name=\"ValTemp\"  value=\"");
  itoa(tempVal, tmp, 10);
  strcat(html, tmp );
  strcat(html, "\">");
  strcat(html, "<br>");
  strcat(html, "<button>עדכן טמפרטורה</button>");

    strcat(html, "<br>");
    strcat(html, "<br>");
strcat(html, "</form>");

    strcat(html, "<br>");
    strcat(html, "<br>");

    strcat(html, "<p>הטמפרטורה עכשיו היא ");
    itoa(temperature, tmp, 10);
    strcat(html, tmp );
    strcat(html, " </p> ");

strcat(html, "</body>");
  strcat(html, "</html>");
 server.send(200, "text/html", html);
}

void RetMain(){

      server.sendHeader("Location","/");
      server.sendHeader("Cache-Control","no-cache");
      server.send(301);
      return;
}

  

void handleNotFound(){
  String message = "File Not Foundnn";
      message += "URI: ";
      message += server.uri();
      message += "nMethod: ";
      message += (server.method() == HTTP_GET) ? "GET" : "POST";
      message += "nArguments: ";
      message += server.args();
      message += "n";

      for (uint8_t i = 0; i < server.args(); i++) {
          message += " " + server.argName(i) + ": " + server.arg(i) + "n";
      }

      server.send(404, "text/plain", message);
}
