/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/

#ifndef FILE_PUT_HPP
#define FILE_PUT_HPP

/* This is a low level file type API call */

#include "rods.hpp"
#include "rcMisc.hpp"
#include "procApiRequest.hpp"
#include "apiNumber.hpp"


#include "fileOpen.hpp"

typedef struct {
    char file_name[ MAX_NAME_LEN ];
} filePutOut_t;

#define filePutOut_PI "str file_name[MAX_NAME_LEN];"


#if defined(RODS_SERVER)
#define RS_FILE_PUT rsFilePut
/* prototype for the server handler */
int
rsFilePut( rsComm_t *rsComm,
           fileOpenInp_t *filePutInp,
           bytesBuf_t *filePutInpBBuf,
           filePutOut_t** );
int
_rsFilePut( rsComm_t *rsComm, fileOpenInp_t *filePutInp,
            bytesBuf_t *filePutInpBBuf, rodsServerHost_t *rodsServerHost,
            filePutOut_t** );
int
remoteFilePut( rsComm_t *rsComm, fileOpenInp_t *filePutInp,
               bytesBuf_t *filePutInpBBuf, rodsServerHost_t *rodsServerHost,
               filePutOut_t** );
#else
#define RS_FILE_PUT NULL
#endif

/* prototype for the client call */
#ifdef __cplusplus
extern "C" {
#endif
int
rcFilePut( rcComm_t *conn, fileOpenInp_t *filePutInp,
           bytesBuf_t *filePutInpBBuf,
           filePutOut_t** );
#ifdef __cplusplus
}
#endif

#endif  /* FILE_PUT_H */
