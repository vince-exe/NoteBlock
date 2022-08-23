#ifndef OPTIONS_H
#define OPTIONS_H

#include <QString>

class Options {
public:
    static const char* sysCurrentOptionsPath;

    static const char* sysDefaultOptionsPath;

    static QString defaultPathOption;

    static QString defaultFontStyle;

    static QString defaultTextColor;

    static QString defaultBackColor;

    /* used to rapresent the colors in integer RGB */
    static int defTextColorR;
    static int defTextColorG;
    static int defTextColorB;

    static int defBackColorR;
    static int defBackColorG;
    static int defBackColorB;

    static int defaultFontSize;

    static bool wantsNewFile;

public:
    Options();

    static void readOptions(FILE* f);

    static void storeOptions(FILE* f);
};

#endif // OPTIONS_H
