/*
 * Author: Nemirtingas
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"

#if __has_include(<android-base/logging.h>)
#include <android-base/logging.h>
#include <android-base/properties.h>
#define LOG_ERROR_INIT(msg) LOG(ERROR) << "init: " << msg
#else
#include "log.h"
#include "property_service.h"
#include "util.h"
#define LOG_ERROR_INIT(msg) ERROR("init: %s\n", msg)
#endif

#include "init_pxa1908.h"

__attribute__ ((weak))
void init_target_properties()
{
}

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

static int read_file2(const char *fname, char *data, int max_size)
{
    int fd, rc;

    if (max_size < 1)
        return 0;

    fd = open(fname, O_RDONLY);
    if (fd < 0) {
        LOG_ERROR_INIT("failed to open file");
        return 0;
    }

    rc = read(fd, data, max_size - 1);
    if ((rc > 0) && (rc < max_size))
        data[rc] = '\0';
    else
        data[0] = '\0';
    close(fd);

    return 1;
}

static void init_alarm_boot_properties()
{
    char const *alarm_file = "/proc/sys/kernel/boot_reason";
    char buf[64];

    if (read_file2(alarm_file, buf, sizeof(buf))) {
        const char *val = (buf[0] == '3') ? "true" : "false";
#if __has_include(<android-base/properties.h>)
        android::base::SetProperty("ro.alarm_boot", val);
#else
        property_set("ro.alarm_boot", val);
#endif
    }
}

void vendor_load_properties()
{
    init_target_properties();
    init_alarm_boot_properties();
}
