#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "SARTHAK";
const char* password = "9765954801";

WebServer server(80);

#define IN1 22
#define IN2 21
#define IN3 19
#define IN4 18
#define IN5 25
#define IN6 26
#define IN7 33
#define IN8 32

#define IR_SENSOR_1 27
#define IR_SENSOR_2 14

int ir1, ir2;
unsigned long lastObstacleTime = 0;
bool obstacleDetected = false;
bool paused = false;
String Status = "H";

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.println(WiFi.localIP());

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(IN5, OUTPUT);
    pinMode(IN6, OUTPUT);
    pinMode(IN7, OUTPUT);
    pinMode(IN8, OUTPUT);

    pinMode(IR_SENSOR_1, INPUT);
    pinMode(IR_SENSOR_2, INPUT);

    stop();

    server.on("/", HTTP_GET, []() {
        server.send(200, "text/html", getHTML());
    });

    server.on("/move", HTTP_GET, []() {
        if (server.hasArg("dir")) {
            String command = server.arg("dir");
            Serial.println(command);
            processCommand(command);
        }
        server.send(200, "text/plain", "OK");
    });

    server.begin();
    Serial.println("Server started");
}

void loop() {
    server.handleClient();
    checkForObstacles();
}

void checkForObstacles() {
    ir1 = digitalRead(IR_SENSOR_1);
    ir2 = digitalRead(IR_SENSOR_2);

    if (ir1 == LOW || ir2 == LOW) {
        if (!obstacleDetected) {
            lastObstacleTime = millis();
            obstacleDetected = true;
        } else if (millis() - lastObstacleTime > 150 && !paused) {
            stop();
            paused = true;
            Serial.println("Obstacle detected! Stopping...");
        }
    } else if (paused) {
        paused = false;
        obstacleDetected = false;
        Serial.println("Obstacle cleared. Resuming...");
    } else {
        obstacleDetected = false;
    }
}

void processCommand(String command) {
    if (command == Status) {
        Serial.print("Robot Already At ");
        Serial.println(command);
    } else {
        if (Status != "H") {
            if (Status == "K") kichantohome();
            else if (Status == "B") bedroomtohome();
            else if (Status == "L") livingroomtohome();
            else if (Status == "A") aaatohome();
        }

        if (command == "K") hometokichan();
        else if (command == "B") hometobedroom();
        else if (command == "L") hometolivingroom();
        else if (command == "A") hometoaaa();
        else if (command == "H") Serial.println("STATUS = H");
        else Serial.println("Something Wrong " + command);

        Status = command; // Update status to allow future commands
    }
}

String getHTML() {
    return R"rawliteral(
        <!DOCTYPE html>
        <html>
        <head>
            <title>ESP32 Robot Control</title>
            <style>
                body { text-align: center; font-family: Arial, sans-serif; }
                button { width: 150px; height: 50px; font-size: 20px; margin: 10px; }
            </style>
            <script>
                function sendCommand(command) {
                    var xhr = new XMLHttpRequest();
                    xhr.open("GET", "/move?dir=" + command, true);
                    xhr.send();
                }
            </script>
        </head>
        <body>
            <h1>ESP32 Robot Control</h1>
            <button onclick="sendCommand('K')">Kitchen</button>
            <button onclick="sendCommand('B')">Bed-Room</button>
            <button onclick="sendCommand('L')">Living-Room</button>
            <button onclick="sendCommand('A')">Extra-Room</button>
            <button onclick="sendCommand('H')">Robo-Home</button>
        </body>
        </html>
    )rawliteral";
}

void hometokichan() {
    moveForwardTimed(2000);
    turnLeftTimed(500);
    moveForwardTimed(1000);
    Serial.println("STATUS = K");
}

void kichantohome() {
    moveBackwardTimed(1000);
    turnRightTimed(413);
    moveBackwardTimed(2000);
    Serial.println("STATUS = H");
}

void hometobedroom() {
    moveForwardTimed(2000);
    turnRightTimed(500);
    moveForwardTimed(1000);
    Serial.println("STATUS = B");
}

void bedroomtohome() {
    moveBackwardTimed(1000);
    turnLeftTimed(413);
    moveBackwardTimed(2000);
    Serial.println("STATUS = H");
}

void hometolivingroom() {
    moveBackwardTimed(2000);
    turnRightTimed(413);
    moveBackwardTimed(1000);
    Serial.println("STATUS = L");
}

void livingroomtohome() {
    moveForwardTimed(1000);
    turnLeftTimed(520);
    moveForwardTimed(2000);
    Serial.println("STATUS = H");
}

void hometoaaa() {
    moveBackwardTimed(2000);
    turnLeftTimed(440);
    moveBackwardTimed(1000);
    Serial.println("STATUS = A");
}

void aaatohome() {
    moveForwardTimed(1000);
    turnRightTimed(520);
    moveForwardTimed(2000);
    Serial.println("STATUS = H");
}

void moveForward() {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    digitalWrite(IN5, HIGH); digitalWrite(IN6, LOW);
    digitalWrite(IN7, HIGH); digitalWrite(IN8, LOW);
}

void moveBackward() {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    digitalWrite(IN5, LOW); digitalWrite(IN6, HIGH);
    digitalWrite(IN7, LOW); digitalWrite(IN8, HIGH);
}

void turnLeft() {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    digitalWrite(IN5, HIGH); digitalWrite(IN6, LOW);
    digitalWrite(IN7, LOW); digitalWrite(IN8, HIGH);
}

void turnRight() {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    digitalWrite(IN5, LOW); digitalWrite(IN6, HIGH);
    digitalWrite(IN7, HIGH); digitalWrite(IN8, LOW);
}

void stop() {
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    digitalWrite(IN5, LOW); digitalWrite(IN6, LOW);
    digitalWrite(IN7, LOW); digitalWrite(IN8, LOW);
}

void moveForwardTimed(unsigned long duration) {
    unsigned long start = millis();
    while (millis() - start < duration) {
        checkForObstacles();
        if (paused) {
            while (paused) checkForObstacles();
            start = millis();
        }
        moveForward();
    }
    stop();
}

void moveBackwardTimed(unsigned long duration) {
    unsigned long start = millis();
    while (millis() - start < duration) {
        checkForObstacles();
        if (paused) {
            while (paused) checkForObstacles();
            start = millis();
        }
        moveBackward();
    }
    stop();
}

void turnLeftTimed(unsigned long duration) {
    unsigned long start = millis();
    while (millis() - start < duration) {
        checkForObstacles();
        if (paused) {
            while (paused) checkForObstacles();
            start = millis();
        }
        turnLeft();
    }
    stop();
}

void turnRightTimed(unsigned long duration) {
    unsigned long start = millis();
    while (millis() - start < duration) {
        checkForObstacles();
        if (paused) {
            while (paused) checkForObstacles();
            start = millis();
        }
        turnRight();
    }
    stop();
}
