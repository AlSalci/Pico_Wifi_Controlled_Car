
#include "hardware/i2c.h"
#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include <cstdint>
#include "../include/motors.hpp"


class server
{

private:



public:


void server_initialization(const char *WIFI_SSID,const char *WIFI_PASSWORD);

//CGI=============================================
void cgi_init(void);

static const tCGI cgi_handlers[];

static const char * cgi_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
//================================================


//SSI============================================
void ssi_init();
static u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen);
static const char * ssi_tags[];
//===============================================




server();
};