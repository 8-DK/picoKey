#include "commandParser.h"


CommandParserHelper::CommandParserHelper()
{

}

bool CommandParserHelper::parse(COMMAND_CH cmdCh,const char *data ,const uint32_t currentItem, const uint32_t totalItem)
{
    if(!isValidCommand(cmdCh))
        return false;

    switch (cmdCh)
    {
        case EM_GET_DATA_LIST:
        //create list json send one by one
        
        break;

        EM_SET_DATA_LIST:
        break;
        
        EM_GET_DATA_AT_INDEX:
        break;
        
        EM_SET_DATA_AT_INDEX:
        break;
        
        EM_ADD_NEW_ENTRY:
        break;
        
        EM_DELETE_ENTRY_AT:
        break;
        
        EM_DELETE_ALL_ENTRY:
        break;
        
        EM_ERASE_DEVICE:
        break;
        
        EM_LOGOUT:
        break;
        
        EM_REMOUNT:
        break;
        
        EM_PLAY_ANIMATION:
        break;    
        
        default:
            break;
    }    

    return true;
}

bool CommandParserHelper::isValidCommand(COMMAND_CH cmdCh)
{
    return ( (cmdCh < EM_COMMAND_CH_MAX) && (cmdCh >= EM_GET_DATA_LIST) );
}



