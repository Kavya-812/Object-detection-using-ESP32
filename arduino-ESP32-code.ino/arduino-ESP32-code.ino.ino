#include "eloquent.h"
#include "eloquent/print.h"
#include "eloquent/tinyml/voting/quorum.h"
#include "WiFi.h"
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>


// replace 'm5wide' with your own model
// possible values are 'aithinker', 'eye', 'm5stack', 'm5wide', 'wrover'
#include "eloquent/vision/camera/aithinker.h"

#include "HogPipeline.h"
#include "HogClassifier.h"

WiFiClientSecure client;

Eloquent::TinyML::Voting::Quorum<7> quorum;

// Wifi network station credentials
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"

// Telegram bot API token
#define BOT_TOKEN "6030113177:AAFvj043OCcjIaaqtEnPI_a322ZrrK87TxU"

// Telegram chat ID to send messages to
#define CHAT_ID "1070677764"

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("Begin");

 // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  // Initialize camera
  camera.qqvga();
  camera.grayscale();

  while (!camera.begin())
    Serial.println("Cannot init camera");
}

void loop() {
  if (!camera.capture()) {
      Serial.println(camera.getErrorMessage());
      delay(1000);
      return;
  }
  
  // apply HOG pipeline to camera frame
  hog.transform(camera.buffer);

  // get a stable prediction
  // this is optional, but will improve the stability of predictions
  uint8_t prediction = classifier.predict(hog.features);
  int8_t stablePrediction = quorum.vote(prediction);

  if (quorum.isStable()) {
    eloquent::print::printf(
      Serial, 
      "Stable prediction: %s \t(DSP: %d ms, Classifier: %d us)\n", 
      classifier.getLabelOf(stablePrediction),
      hog.latencyInMillis(),
      classifier.latencyInMicros()
    );
    
    // Send message to Telegram
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    String message = "Stable prediction: " + String(classifier.getLabelOf(stablePrediction)) + "\n" +
                     "DSP: " + String(hog.latencyInMillis()) + " ms\n" +
                     "Classifier: " + String(classifier.latencyInMicros()) + " us";
    bot.sendMessage(CHAT_ID, message);
  }
  camera.free();
}
