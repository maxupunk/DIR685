#ifndef _FCRSS_HANDLER_H_
#define _FCRSS_HANDLER_H_
int alert_cmd_handler(IDirectFBEventBuffer *p_eventbuffer, int cmd);
int client_cmd_handler(IDirectFBEventBuffer *p_eventbuffer, int cmd, FcNode *node);
void subtree_update(FcNode *node_new, FcNode *node_old);
#endif
