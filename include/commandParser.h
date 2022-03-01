#ifndef _COMMANDPARSER_H
#define _COMMANDPARSER_H
#include "common.h"

class CommandParserHelper{
public:
    CommandParserHelper();
    static bool parse(COMMAND_CH command,const char *data ,const uint32_t currentItem, const uint32_t totalItem);
    static bool isValidCommand(COMMAND_CH command);
};

extern CommandParserHelper cmdParsr;

#endif