#if 1
#define currentTeam 1
#define oppositeTeam 2
int piecePos[] = {0, 0, 6, 5, 4, 2, 3, 7};

#else

#define currentTeam 2
#define oppositeTeam 1
int piecePos[] = {0, 0, 6, 5, 4, 3, 7, 2};
#endif

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

int count = 0;

void setup() {
  Serial.begin(9600);
  nfc.begin();
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}
void loop()
{
  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    if (tag.hasNdefMessage())
    {
      NdefMessage message = tag.getNdefMessage();
      //int recordCount = message.getRecordCount();
      NdefRecord record = message.getRecord(0);
      int payloadLength = record.getPayloadLength();
      byte payload[payloadLength];
      record.getPayload(payload);
      String payloadAsString = "";
      for (int c = 0; c < payloadLength; c++) {
        payloadAsString += (char)payload[c];
      }
      int team = payloadAsString.substring(3).toInt();
      int piece = payloadAsString.substring(5).toInt();
      if (team == currentTeam)
      {
        digitalWrite(piece, HIGH);
        delay(200);
        digitalWrite(piece, LOW);
        delay(500);
      }
      else if (team == oppositeTeam && count == 0)
      {
        for (int i = 0; i < 3; i++)
        {
          digitalWrite(piece, HIGH);
          delay(200);
          digitalWrite(piece, LOW);
          delay(500);
        }
        count = 1;
      }
    }
  }
}
