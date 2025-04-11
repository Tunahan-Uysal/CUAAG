#include <stdio.h>
#include <stdlib.h>
#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include "../lib/ini.h"
#include "constants.h"
#include "debug.h"

/**
 * function 'get_configuration_value' takes string param 'name' and returns string of value
 * if name is not found, use default value instead and use debug_error if --verbose
 *
 * function 'reset_configuration' deletes file 'config.ini' with 'delete_config' and
 * creates new one with default values using 'create_config'
 *
 * function 'create_config' creates file 'config.ini' with default values
 *
 * function 'delete_config' renames file 'config.ini' to 'config.ini.bak'
 */

typedef struct {
    // [image] section
    int width;
    int height;
    int dithering;

    // [setting] section
    int color;
    const char* charset;
} Configuration;

static int handler(void* user, const char* section, const char* name, const char* value) {
    Configuration* config = (Configuration*)user;

    if (strcmp(section, "image") == 0) {
        if (strcmp(name, "width") == 0) {
            config->width = atoi(value);
        }
        else if (strcmp(name, "height") == 0) {
            config->height = atoi(value);
        }
        else if (strcmp(name, "dithering") == 0) {
            config->dithering = atoi(value);
        }
    }
    else if (strcmp(section, "setting") == 0) {
        if (strcmp(name, "color") == 0) {
            config->color = atoi(value);
        }
        else if (strcmp(name, "charset") == 0) {
            config->charset = strdup(value);
        }
    } else { return 0; }

    return 1;
}

static void create_config() {
    FILE* config = fopen("config.ini", "w");
    if (config == NULL) {
        DEBUG_MODE = 1;
        debug_error("Could not create config.ini");
        exit(EXIT_FAILURE);
    }

    fprintf(config, "[image]\n");
    fprintf(config, "width = %d\n", DEFAULT_WIDTH);
    fprintf(config, "height = %d\n", DEFAULT_HEIGHT);
    fprintf(config, "dithering = %d\n", DEFAULT_DITHERING);
    fprintf(config, "\n");

    fprintf(config, "[setting]\n");
    fprintf(config, "color = %d\n", DEFAULT_COLOR);
    fprintf(config, "charset = %s\n", DEFAULT_CHARSET);

    fclose(config);

    debug_print("Created a new config.ini");
}

static void delete_config() {
    if (rename("config.ini", "config.ini.bak") != 0) {
        DEBUG_MODE = 1;
        debug_error("Could not rename config.ini to config.ini.bak");
        exit(EXIT_FAILURE);
    }

    debug_print("Renamed config.ini to config.ini.bak");
}

static void reset_configuration() {
    delete_config();
    create_config();

    debug_success("Finished resetting configuration");

    printf("\n"
           "Configuration reset successfully!\n"
           "You can find previous configuration in config.ini.bak\n"
           "Default configuration has been restored to config.ini\n");
}
