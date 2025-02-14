#include "Wrapper.h"

#define GSM_AUTOBAUD_MIN 9600
#define GSM_AUTOBAUD_MAX 57600

SIM7000Wrapper::SIM7000Wrapper(HardwareSerial &serialPort, uint8_t rx, uint8_t tx, 
    const char* server, int port, const char* apn, const char* user, const char* pass)
: serial(&serialPort), modem(*serial), client(modem), http(client, server, port), 
rxPin(rx), txPin(tx), apn(apn), user(user), pass(pass), isPoweredOn(false) {}

bool SIM7000Wrapper::begin() {


    serial->begin(115200, SERIAL_8N1, rxPin, txPin);
    delay(3000);


    Serial.println("Initializing modem...");
    if (!modem.init()) { 
        Serial.println("Failed to init modem.");
        return false;
    }
    Serial.println("Modem initialized successfully.");
    return true;
}

bool SIM7000Wrapper::sendSMS(const String &phoneNumber, const String &message) {
    Serial.println("Sending SMS...");
    if (!modem.sendSMS(phoneNumber, message)) {
        Serial.println("Failed to send SMS");
        return false;
    }
    Serial.println("SMS sent successfully");
    return true;
}

void SIM7000Wrapper::sendsms(const String &phoneNumber, const String &message) {
    if (sendSMS(phoneNumber, message)) {
        Serial.println("SMS successfully sent via sendsms method.");
    } else {
        Serial.println("SMS sending failed via sendsms method.");
    }
}

String SIM7000Wrapper::httpRequest(const String &url, const String &payload, const String &method, bool useHTTPS) {
    Serial.println("Connecting to GPRS...");
    if (!modem.gprsConnect(apn, user, pass)) {
        Serial.println("Failed to connect to GPRS");
        return "ERROR";
    }

    if (!modem.isNetworkConnected()) {
        Serial.println("Modem is not connected to the network");
        return "ERROR";
    }

    String domain = url.substring(url.indexOf("://") + 3);
    String path = "/";
    int slashIndex = domain.indexOf("/");
    if (slashIndex != -1) {
        path = domain.substring(slashIndex);
        domain = domain.substring(0, slashIndex);
    }

    int port = useHTTPS ? 443 : 80;
    Serial.printf("Connecting to %s on port %d...\n", domain.c_str(), port);

    if (!client.connect(domain.c_str(), port)) {
        Serial.println("Connection to server failed");
        return "ERROR";
    }

    Serial.println("Sending HTTP request...");

    client.println(method + " " + path + " HTTP/1.1");
    client.println("Host: " + domain);

    client.println("User-Agent: ESP32-SIM7000");
    
    if (method == "POST" || method == "PUT") {
        client.println("Content-Type: application/json");
        client.print("Content-Length: ");
        client.println(payload.length());
        client.println();
        client.println(payload);
    } else {
        client.println(); 
    }

    String response = "";
    int statusCode = -1;

    while (client.connected() || client.available()) {
        String line = client.readStringUntil('\n');
        if (line.startsWith("HTTP/1.1")) {
            statusCode = line.substring(9, 12).toInt();
        }
        if (line == "\r") {
            break; 
        }
    }

    while (client.available()) {
        response += client.readString();
    }

    Serial.printf("Response status: %d\n", statusCode);
    Serial.println("Response body: " + response);

    client.stop();
    modem.gprsDisconnect();

    return response;
}
