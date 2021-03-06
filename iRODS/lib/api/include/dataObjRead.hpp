/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/* dataObjRead.h - This file may be generated by a program or script
 */

#ifndef DATA_OBJ_READ_HPP
#define DATA_OBJ_READ_HPP

/* This is a high level type API call */

#include "rods.hpp"
#include "rcMisc.hpp"
#include "procApiRequest.hpp"
#include "apiNumber.hpp"
#include "fileRead.hpp"

#if defined(RODS_SERVER)
#define RS_DATA_OBJ_READ rsDataObjRead
/* prototype for the server handler */
int
rsDataObjRead( rsComm_t *rsComm, openedDataObjInp_t *dataObjReadInp,
               bytesBuf_t *dataObjReadOutBBuf );
int
l3Read( rsComm_t *rsComm, int l1descInx, int len,
        bytesBuf_t *dataObjReadOutBBuf );
int
_l3Read( rsComm_t *rsComm, int l3descInx,
         void *buf, int len );
#else
#define RS_DATA_OBJ_READ NULL
#endif

#ifdef __cplusplus
extern "C" {
#endif
/* prototype for the client call */
/* rcDataObjRead - Read an opened iRODS data object descriptor.
 * Input -
 *   rcComm_t *conn - The client connection handle.
 *   dataObjInp_t *fileReadInp - Relevant items are:
 *      l1descInx - the iRODS data object descriptor to read.
 *      len - the number of bytes to read
 *
 * OutPut -
 *   int status of the operation - >= 0 ==> success, < 0 ==> failure.
 *   bytesBuf_t *dataObjReadOutBBuf - the bytesBuf for the read output.
 */

int
rcDataObjRead( rcComm_t *conn, openedDataObjInp_t *dataObjReadInp,
               bytesBuf_t *dataObjReadOutBBuf );

#ifdef __cplusplus
}
#endif
#endif	/* DATA_OBJ_READ_H */
