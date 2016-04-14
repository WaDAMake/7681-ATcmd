#include "Arduino.h"
#include <IPAddress.h>

static int base64_encode_len(int len);
static uint8_t base64_enc_map(uint8_t n);
static void base64_encode(const uint8_t* src, int len, uint8_t* dest);
static int base64_decode_len(int len);
static uint32_t base64_dec_map(uint8_t n);
static int base64_decode(const uint8_t* src, int len, uint8_t* dest);

class LC7681Wifi
{
  public:
  typedef void (*LC7681WifiCallback)(int event, const uint8_t* data, int dataLen);

  enum {
    EVENT_NONE,
    EVENT_DATA_RECEIVED,
    EVENT_SOCKET_DISCONNECT,
    EVENT_AP_DISCONNECT,
    EVENT_MAX
  };
  
public:
  LC7681Wifi(Stream *s, Stream* l = NULL);

  void begin(int rst);
  void Version();
  void EnterSmartConnection();
  
  bool connectAP(const char* ssid, const char* key,int type=0);
  IPAddress s2ip(const char* str);
  IPAddress IP();
  IPAddress nslookup(const char* server);
  bool connect(IPAddress ip, int port, bool udp = false);
  bool connect(const char* ip, int port, bool udp = false);
  bool print(const char* data, int dataLen);
  bool print(const char* data = NULL);
  bool println(const char* data = NULL);
  void process(LC7681WifiCallback cb);
  String _wait_for(const char* pattern,uint32_t timeout = 300);
  void logger(Stream *s = NULL);
  
private:
  int freeRam();
private: 
  Stream *m_stream;
  Stream *m_log;
  
  int m_lport;
  int m_bufferPos;
  char m_buffer[256];
};
