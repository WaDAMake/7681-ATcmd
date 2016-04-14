void HttpGet(LC7681Wifi& wifi, char *url)
{
  wifi.print("GET ");
  wifi.print(url);
  wifi.println(" HTTP/1.1");
  
  wifi.print("Host: ");
  wifi.println(url);
  wifi.println("Connection: close");
  wifi.println();
}

void UpdateMCSValue(LC7681Wifi& wifi, char *ch_id, const char *value)
{
  wifi.println("POST /mcs/v2/devices/DFi2z7W3/datapoints.csv HTTP/1.1");
  String data = String(ch_id) + ",," + String(value);
    
  wifi.println("Host: api.mediatek.com");
  wifi.println("deviceKey: XeFmrIZVlDeABktI");
  wifi.print("Content-Length: ");
  wifi.println("20");
  wifi.println("Content-Type: text/csv");
  wifi.println("Connection: close");
  wifi.println();
  wifi.println(data.c_str());

}

