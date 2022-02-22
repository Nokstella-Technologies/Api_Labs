
#include "./header/server.h"

int main(void)
{
  struct mg_mgr mgr; 
                               
  mg_mgr_init(&mgr);
  mg_http_listen(&mgr, s_http_addr, routes, NULL);  
  mg_http_listen(&mgr, s_https_addr, routes, (void *) 1);     // Create listening connection
  for (;;) mg_mgr_poll(&mgr, 1000);
  mg_mgr_free(&mgr);                                        // Cleanup
  return 0;
}