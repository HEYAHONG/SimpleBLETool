#include "stdio.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct
{
    const char * index;
    const char * companyid;
    const char * desc;
} ble_company_id_t;

extern const ble_company_id_t ble_company_id[];

ble_company_id_t ble_find_company_by_id(uint16_t companyid);


#ifdef __cplusplus
}
#endif // __cplusplus
