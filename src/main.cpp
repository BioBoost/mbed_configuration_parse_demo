#include "mbed.h"
#include <string>

#include "file_reader.h"
#include "device_configuration.h"
#include "json_device_configuration_parser.h"
#include "string_reader.h"


DigitalOut myled(LED1);
Serial pc(USBTX, USBRX);

const std::string DEFAULT_DEVICE_CONFIG = "{ \
  \"version\": \"1.0 alpha\", \
  \"description\": \"Low Power LoraWan GPS module\", \
  \"board\": \"LPC1768\"\r\n \
}";

int main() {
  pc.baud(115200);

  ConfigParser::FileReader reader("/local/config.jsn");
  // ConfigParser::StringReader reader(&DEFAULT_DEVICE_CONFIG);
  JsonDeviceConfigurationParser parser(&reader);
  DeviceConfiguration *devConfig = parser.parse();

  printf("Version = %s\r\n", devConfig->version.c_str());
  printf("Description = %s\r\n", devConfig->description.c_str());
  printf("Board = %s\r\n", devConfig->board.c_str());

  delete devConfig;

  while(1) {
    myled = 1;
    wait(0.2);
    myled = 0;
    wait(0.2);
  }
}
