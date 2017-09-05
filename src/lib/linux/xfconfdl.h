#ifndef __SETBACKGROUND_XFCONFDL_H__
#define __SETBACKGROUND_XFCONFDL_H__

#include <glib.h>

gboolean xfconf_try_init();

typedef struct _XfconfChannel XfconfChannel;

extern gboolean (*xfconf_init)(GError **error);
extern XfconfChannel* (*xfconf_channel_get)(const gchar *channel_name);
extern gboolean (*xfconf_channel_has_property)(XfconfChannel *channel, const gchar *property);
extern gboolean (*xfconf_channel_set_string)(XfconfChannel *channel, const gchar *property, const gchar *value);

#endif /* __SETBACKGROUND_XFCONFDL_H__ */
