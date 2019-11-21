/*
 * Network Remote control for old LG TV
 * 
 * hadware list:
 * controller: NodeMCU v1
 * transistor: BC547 
 * ir led: TSAL6100 
 * ir reciever: TSOP4838
 * 
 */

#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

IRsend irsend(4); //send GPIO-4 = D2 on NodeMCU

IPAddress ip(192, 168, 1, 177);  
IPAddress gateway_ip ( 192,  168,   1,   1);
IPAddress subnet_mask(255, 255, 255,   0);

const char* ssid = "Rb";
const char* password = "";
 
WiFiServer server(80);
  
void setup() 
{
  WiFi.config(ip, gateway_ip, subnet_mask);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  irsend.begin();
  server.begin();
}

String responsePage(String code)
{
  String jsonResponse = "{\"command\":"+code+"}";
  String response = "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Connection: close\r\n"
        "Content-Length: " + String(jsonResponse.length()) + "\r\n\r\n";

  return response + jsonResponse;
}

String indexPage()
{
  String htmlResponse = "<!DOCTYPE html>"
        "<html>" 
        "<head>" 
        "<meta charset=\"utf-8\">"
        "<title>LG Remote</title>"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, maximum-scale=1, user-scalable=0\">"
        "<meta name=\"theme-color\" content=\"#dc3545\" />"
        "<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\">"
        "<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\">"
        "<script src=\"https://code.jquery.com/jquery-3.1.1.min.js\" integrity=\"sha256-hVVnYaiADRTO2PzUGmuLJr8BLUSjGIZsDYGmIJLv2b8=\"  crossorigin=\"anonymous\"></script>"
        "<script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js\" integrity=\"sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1\" crossorigin=\"anonymous\"></script>"
        "<script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js\" integrity=\"sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM\" crossorigin=\"anonymous\"></script>"
        "<script>" 
        " var clickTimer; "
        " function sendData(id, event){ " 
            " $.ajax({url:'/send/'+id})" 
            " .done((result) => { if(id === result['command']){  console.log('done'); }else{ console.log(result); } }); " 
            " clickTimer = window.setTimeout(sendData.bind(this, id), 200); "
            " if (typeof event !== 'undefined'){ "
                " event.preventDefault(); "
                " event.stopPropagation(); "
            " } "
            " return false; " 
        " } " 
        " function stopData(){ "
            " if(clickTimer) window.clearTimeout(clickTimer); "
            " clickTimer = null; "
        " } "
        " window.addEventListener(\"mouseup\", stopData); " 
        " window.addEventListener(\"touchend\", stopData); " 
        "</script>" 
        "<style>" 
            ".btn{ width: 6em; }" 
        "</style>" 
        "</head>" 
        "<body>" 
        "<div class=\"container\">"
        "<div class=\"col-xs-1 pt-3 pb-3\" align=\"center\">"
        "<form>"
            "<div class=\"form-group\">"
                "<div class=\"btn-group\">"
                    "<button ontouchstart=\"sendData(551494620,event)\" onmousedown=\"sendData(551494620,event)\" type=\"button\" class=\"btn btn-warning\" >ON</button>"
                    "<button ontouchstart=\"sendData(551527260,event)\" onmousedown=\"sendData(551527260,event)\" type=\"button\" class=\"btn btn-secondary\" >OFF</button>"
                    "<button ontouchstart=\"sendData(551516295,event)\" onmousedown=\"sendData(551516295,event)\" type=\"button\" class=\"btn btn-success\" >FAV</button>"
                    "<button ontouchstart=\"sendData(551489520,event)\" onmousedown=\"sendData(551489520,event)\" type=\"button\" class=\"btn btn-success\" >INP</button>"
                "</div>"
            "</div>"
            "<div class=\"form-group\">"
                "<div class=\"btn-group-vertical\" role=\"group\" >"
                    "<div class=\"btn-group\">"
                        "<button ontouchstart=\"sendData(551520375,event)\" onmousedown=\"sendData(551520375,event)\" type=\"button\" class=\"btn btn-light\" >1</button>"
                        "<button ontouchstart=\"sendData(551504055,event)\" onmousedown=\"sendData(551504055,event)\" type=\"button\" class=\"btn btn-light\" >2</button>"
                        "<button ontouchstart=\"sendData(551536695,event)\" onmousedown=\"sendData(551536695,event)\" type=\"button\" class=\"btn btn-light\" >3</button>"
                        "<button ontouchstart=\"sendData(551495895,event)\" onmousedown=\"sendData(551495895,event)\" type=\"button\" class=\"btn btn-light\" >4</button>"
                    "</div>"
                    "<div class=\"btn-group\">"
                        "<button ontouchstart=\"sendData(551528535,event)\" onmousedown=\"sendData(551528535,event)\" type=\"button\" class=\"btn btn-light\" >5</button>"
                        "<button ontouchstart=\"sendData(551512215,event)\" onmousedown=\"sendData(551512215,event)\" type=\"button\" class=\"btn btn-light\" >6</button>"
                        "<button ontouchstart=\"sendData(551544855,event)\" onmousedown=\"sendData(551544855,event)\" type=\"button\" class=\"btn btn-light\" >7</button>"
                        "<button ontouchstart=\"sendData(551491815,event)\" onmousedown=\"sendData(551491815,event)\" type=\"button\" class=\"btn btn-light\" >8</button>"
                    "</div>"
                    "<div class=\"btn-group\">"
                        "<button ontouchstart=\"sendData(551524455,event)\" onmousedown=\"sendData(551524455,event)\" type=\"button\" class=\"btn btn-light\" >9</button>"
                        "<button ontouchstart=\"sendData(551487735,event)\" onmousedown=\"sendData(551487735,event)\" type=\"button\" class=\"btn btn-light\" >0</button>"
                        "<button ontouchstart=\"sendData(551537205,event)\" onmousedown=\"sendData(551537205,event)\" type=\"button\" class=\"btn btn-secondary\" >list</button>"
                        "<button ontouchstart=\"sendData(551508135,event)\" onmousedown=\"sendData(551508135,event)\" type=\"button\" class=\"btn btn-secondary\" >q.view</button>"
                    "</div>"
                "</div>"
            "</div>"
            "<div class=\"form-group\">"
                "<div class=\"btn-group\">"
                    "<button ontouchstart=\"sendData(551502015,event)\" onmousedown=\"sendData(551502015,event)\" type=\"button\" class=\"btn btn-danger\" >VOL+</button>"
                    "<button ontouchstart=\"sendData(551534655,event)\" onmousedown=\"sendData(551534655,event)\" type=\"button\" class=\"btn btn-light\" >VOL-</button>"
                    "<button ontouchstart=\"sendData(551485695,event)\" onmousedown=\"sendData(551485695,event)\" type=\"button\" class=\"btn btn-danger\" >CH+</button>"
                    "<button ontouchstart=\"sendData(551518335,event)\" onmousedown=\"sendData(551518335,event)\" type=\"button\" class=\"btn btn-light\" >CH-</button>"
                "</div>"
            "</div>"
            "<div class=\"form-group\">"
                "<div class=\"btn-group\">"
                    "<button ontouchstart=\"sendData(551522415,event)\" onmousedown=\"sendData(551522415,event)\" type=\"button\" class=\"btn btn-danger\" >mute</button>"
                    "<button ontouchstart=\"sendData(551541285,event)\" onmousedown=\"sendData(551541285,event)\" type=\"button\" class=\"btn btn-warning\" >exit</button>"
                    "<button ontouchstart=\"sendData(551490795,event)\" onmousedown=\"sendData(551490795,event)\" type=\"button\" class=\"btn btn-warning\" >back</button>"
                    "<button ontouchstart=\"sendData(551507370,event)\" onmousedown=\"sendData(551507370,event)\" type=\"button\" class=\"btn btn-warning\" >info</button>"
                "</div>"
            "</div>"
        "</form>"
        "</div>"
        "</div>"
        "</body>" 
        "</html>"; 
  
  String response = "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n"
        "Content-Length: " + String(htmlResponse.length()) + "\r\n\r\n";
  
  return response + htmlResponse;
}
 
void loop() 
{

  //reset if wifi is not connected
  if (WiFi.status() == 6)
  {
      ESP.reset();
  }
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) 
  {
    
   while(client.connected())
   {
     
     if (client.available()) 
     {  
        String request = client.readStringUntil('\r');
        client.flush();
     
        // Parse request
        if (request.indexOf("GET / HTTP/1.1") != -1)  
        {
          //index page
          client.println(indexPage());
          client.stop();
          return;
        }
        else if (request.indexOf("send") != -1)  
        {
          //response page
          request.replace(" HTTP/1.1", "");
          request.replace("GET /send/", "");
     
          irsend.sendNEC(request.toInt(), 32);
          delay(50);

          client.println(responsePage(request));
          client.stop();

          return;
        }
        else if (request.indexOf("GET /favicon.ico HTTP/1.1") != -1)  
        {
        
        }

        else
        {
          client.println("HTTP/1.1 404 Not Found\n");
          client.stop();
          return;
        }
      }
    }
  }

}
