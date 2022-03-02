#include "commandParser.h"
#include "usbHelper.h"
#include "mainApp.h"
#include "cJSON.h"

CommandParserHelper::CommandParserHelper()
{

}

bool CommandParserHelper::parse(COMMAND_CH cmdCh,const char *data ,const uint32_t currentItem, const uint32_t totalItem, char *respBuffer )
{
    if(!isValidCommand(cmdCh))
        return false;

   char *out;
   cJSON *root, *jcommand, *jdata, *jcurrentItem,*jtotalItem;

   /* create root node and array */
   root = cJSON_CreateObject();
   cars = cJSON_CreateArray();
    switch (cmdCh)
    {
        case EM_GET_DATA_LIST:
        //create list json send one by one
         cJSON_AddItemToObject(root, "command",jcommand);
         cJSON_AddItemToObject(root, "data",jdata);
         cJSON_AddItemToObject(root, "currentItem",jtotalItem);
         cJSON_AddItemToObject(root, "totalItem",jtotalItem);
        MainApp::readSingleEntryFromEeprom(currentItem,respBuffer);

        mPrintf("Command Received A\n");
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



