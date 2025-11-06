#include <WiFi.h>

// Motor Pins
#define ENA 23
#define ENB 22
#define IN1 16
#define IN2 17
#define IN3 19
#define IN4 21

WiFiServer server(80);
String command = "";
int speedVal = 200;

// SoftAP credentials
const char* ssid = "ESP32-Robot";
const char* password = "12345678";

void setup() {
  Serial.begin(115200);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String req = client.readStringUntil('\r');
    client.flush();

    if (req.indexOf("GET /?cmd=") >= 0) {
      int cmdStart = req.indexOf("cmd=") + 4;
      int cmdEnd = req.indexOf("&", cmdStart);
      if (cmdEnd == -1) cmdEnd = req.length();
      command = req.substring(cmdStart, cmdEnd);

      int speedStart = req.indexOf("speed=") + 6;
      int speedEnd = req.indexOf(" ", speedStart);
      String speedStr = req.substring(speedStart, speedEnd);
      speedVal = speedStr.toInt();

      handleCommand(command, speedVal);
    }

    // Send HTML UI
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'>");
    client.println("<title>ESP32 Robot Control</title>");
    client.println("<style>");
    client.println("body { font-family: Arial; background: linear-gradient(to right, #74ebd5, #ACB6E5); text-align: center; margin: 0; padding: 0; }");
    client.println("h2 { margin-top: 20px; color: #333; }");
    client.println(".container { display: flex; flex-direction: column; align-items: center; justify-content: center; padding: 20px; }");
    client.println(".grid { display: grid; grid-template-columns: repeat(3, 100px); grid-gap: 15px; margin-top: 20px; }");
    client.println(".btn { width: 100px; height: 100px; font-size: 20px; border: none; border-radius: 15px; color: white; box-shadow: 0 4px 6px rgba(0,0,0,0.2); }");
    client.println(".btn:active { transform: scale(0.95); }");
    client.println(".forward { background-color: #28a745; }");
    client.println(".backward { background-color: #dc3545; }");
    client.println(".left { background-color: #007bff; }");
    client.println(".right { background-color: #ffc107; color: black; }");
    client.println(".stop { background-color: #6c757d; }");
    client.println("#speedSlider { width: 80%; margin-top: 20px; }");
    client.println("</style></head><body>");
    client.println("<div class='container'>");
    client.println("<h2>ESP32 Robot Control</h2>");
    client.println("<p>Speed: <span id='speedVal'>200</span></p>");
    client.println("<input type='range' min='0' max='255' value='200' id='speedSlider'>");

    client.println("<div class='grid'>");
    client.println("<div></div><button class='btn forward' ontouchstart=\"sendCmd('forward')\" ontouchend=\"sendCmd('stop')\">↑</button><div></div>");
    client.println("<button class='btn left' ontouchstart=\"sendCmd('left')\" ontouchend=\"sendCmd('stop')\">←</button>");
    client.println("<button class='btn stop' ontouchstart=\"sendCmd('stop')\">■</button>");
    client.println("<button class='btn right' ontouchstart=\"sendCmd('right')\" ontouchend=\"sendCmd('stop')\">→</button>");
    client.println("<div></div><button class='btn backward' ontouchstart=\"sendCmd('backward')\" ontouchend=\"sendCmd('stop')\">↓</button><div></div>");
    client.println("</div></div>");

    client.println("<script>");
    client.println("let speed = 200;");
    client.println("document.getElementById('speedSlider').oninput = function() {");
    client.println("  speed = this.value;");
    client.println("  document.getElementById('speedVal').innerText = speed;");
    client.println("};");
    client.println("function sendCmd(cmd) {");
    client.println("  fetch('/?cmd=' + cmd + '&speed=' + speed);");
    client.println("}");
    client.println("</script>");

    client.println("</body></html>");
    client.println();
    client.stop();
  }
}

void handleCommand(String cmd, int pwm) {
  if (cmd == "forward") {
    analogWrite(ENA, pwm);
    analogWrite(ENB, pwm);
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  } else if (cmd == "backward") {
    analogWrite(ENA, pwm);
    analogWrite(ENB, pwm);
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  
  } 
  else if (cmd == "left") {
    analogWrite(ENA, pwm);
    analogWrite(ENB, pwm);
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    
  }else if (cmd == "right") {
    analogWrite(ENA, pwm);
    analogWrite(ENB, pwm);
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    
  } else if (cmd == "stop") {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  }
}

