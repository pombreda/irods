/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/* replUtil.h - Header for for replUtil.c */

#ifndef REPL_UTIL_HPP
#define REPL_UTIL_HPP

#include "rodsClient.hpp"
#include "parseCommandLine.hpp"
#include "rodsPath.hpp"

#ifdef __cplusplus
extern "C" {
#endif
int
replUtil( rcComm_t *conn, rodsEnv *myRodsEnv, rodsArguments_t *myRodsArgs,
          rodsPathInp_t *rodsPathInp );
int
replDataObjUtil( rcComm_t *conn, char *srcPath, rodsLong_t srcSize,
                 rodsArguments_t *rodsArgs, dataObjInp_t *dataObjInp );
int
initCondForRepl( rodsEnv *myRodsEnv, rodsArguments_t *rodsArgs,
                 dataObjInp_t *dataObjInp, rodsRestart_t *rodsRestart );
int
replCollUtil( rcComm_t *conn, char *srcColl, rodsEnv *myRodsEnv,
              rodsArguments_t *rodsArgs, dataObjInp_t *dataObjInp,
              rodsRestart_t *rodsRestart );

#ifdef __cplusplus
}
#endif

#endif	/* REPL_UTIL_H */
