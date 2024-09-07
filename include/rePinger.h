/* 
   EN: Service for periodically checking the availability of the Internet on one or several public servers
   RU: Служба периодической проверки доступности сети интернет по одному или нескольким публичным серверам
   --------------------------
   (с) 2021 Разживин Александр | Razzhivin Alexander
   kotyara12@yandex.ru | https://kotyara12.ru | tg: @kotyara1971
*/

#ifndef __RE_PINGER_H__
#define __RE_PINGER_H__ 

#include "time.h"
#include "project_config.h"
#include "def_consts.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lwip/opt.h"
#include "lwip/init.h"
#include "lwip/mem.h"
#include "lwip/icmp.h"
#include "lwip/dns.h"
#include "lwip/netif.h"
#include "lwip/sys.h"
#include "lwip/timeouts.h"
#include "lwip/inet.h"
#include "lwip/inet_chksum.h"
#include "lwip/ip.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"
#include "rLog.h"
#include "rePinger.h"
#include "reEvents.h"
#include "reWiFi.h"
#include "reEsp32.h"
#include "rStrings.h"
#include "reParams.h"
typedef struct {
    const char* host_name;
    ip_addr_t host_addr;
    TickType_t host_resolved;
    int sock;
    struct sockaddr_storage target_addr;
    struct icmp_echo_hdr *packet_hdr;
    uint32_t icmp_pkt_size;
    uint32_t transmitted;
    uint32_t received;
    uint32_t elapsed_time_ms;
    uint32_t total_time_ms;
    uint32_t total_duration_ms;
    float total_loss;
    uint8_t tos;
    uint8_t ttl;
    ping_state_t total_state;
    uint32_t limit_unavailable;
    uint32_t count_unavailable;
    time_t time_unavailable;
    bool notify_unavailable; 
} pinger_data_t;



#ifdef __cplusplus
extern "C" {
#endif

bool pingerTaskCreate(bool createSuspended);
bool pingerTaskSuspend();
bool pingerTaskResume();
bool pingerTaskDelete();

bool pingerEventHandlerRegister();
esp_err_t pingerInitSession(pinger_data_t *ep, const char* hostname, uint32_t hostid, uint32_t limit_unavailable);
ping_state_t pingerCheckHostEx(pinger_data_t *ep);


#ifdef __cplusplus
}
#endif

#endif // __RE_PINGER_H__