#include "options.h"

const char* Options::sysDefaultOptionsPath = "sys_files/default_settings.txt";

const char* Options::sysCurrentOptionsPath = "sys_files/current_settings.txt";

QString Options::defaultPathOption;

QString Options::defaultFontStyle;

QString Options::defaultTextColor;

QString Options::defaultBackColor;

/* used to rapresent the colors in integer RGB */
int Options::defTextColorR;
int Options::defTextColorG;
int Options::defTextColorB;

int Options::defBackColorR;
int Options::defBackColorG;
int Options::defBackColorB;

int Options::defaultFontSize;

Options::Options() {}

void Options::readOptions(FILE *f) {
    char buffer[1024];
    char* token = NULL;

    fgets(buffer, 1024, f);
    buffer[strlen(buffer) - 1] = '\0';

    token = strtok(buffer, ";");
    Options::defaultFontStyle = token;

    token = strtok(NULL, ";");
    Options::defaultTextColor = token;

    token = strtok(NULL, ";");
    Options::defaultBackColor = token;

    token = strtok(NULL, ";");
    Options::defTextColorR = std::atoi(token);

    token = strtok(NULL, ";");
    Options::defTextColorG = std::atoi(token);

    token = strtok(NULL, ";");
    Options::defTextColorB = std::atoi(token);

    token = strtok(NULL, ";");
    Options::defBackColorR = std::atoi(token);

    token = strtok(NULL, ";");
    Options::defBackColorG = std::atoi(token);

    token = strtok(NULL, ";");
    Options::defBackColorB = std::atoi(token);

    token = strtok(NULL, ";");
    Options::defaultFontSize = std::atoi(token);
}

void Options::storeOptions(FILE *f) {
    char buffer[1024];

    sprintf(buffer, "%s;%s;%s;%d;%d;%d;%d;%d;%d;%d\n", Options::defaultFontStyle.toStdString().c_str(), Options::defaultTextColor.toStdString().c_str(),
                                                     Options::defaultBackColor.toStdString().c_str(), Options::defTextColorR, Options::defTextColorG,
                                                     Options::defTextColorB, Options::defBackColorR, Options::defBackColorG, Options::defBackColorB,
                                                     Options::defaultFontSize
            );
    fprintf(f, buffer);
}
