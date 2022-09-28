#include "ble_company_id.h"
#include "string"

ble_company_id_t ble_find_company_by_id(uint16_t companyid)
{
    const ble_company_id_t *data=ble_company_id;
    ble_company_id_t ret= {"65535","0xFFFF","Unkown"};
    while((data)!=NULL && data->index!=NULL && data->companyid!=NULL && data->desc!=NULL)
    {
        data++;
        try
        {
            if(companyid==std::stoul(std::string(data->companyid),NULL,16))
            {
                ret=(*data);
                break;
            }
        }
        catch(...)
        {
            continue;
        }
    }
    return ret;
}


