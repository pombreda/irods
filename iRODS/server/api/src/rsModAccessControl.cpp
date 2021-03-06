/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/* This is script-generated code (for the most part).  */
/* See modAccessControl.h for a description of this API call.*/

#include "reFuncDefs.hpp"
#include "modAccessControl.hpp"
#include "specColl.hpp"
#include "reGlobalsExtern.hpp"
#include "icatHighLevelRoutines.hpp"

int
rsModAccessControl( rsComm_t *rsComm, modAccessControlInp_t *modAccessControlInp ) {
    rodsServerHost_t *rodsServerHost;
    int status;
    specCollCache_t *specCollCache = NULL;
    char newPath[MAX_NAME_LEN];
    modAccessControlInp_t newModAccessControlInp = *modAccessControlInp;

    rstrcpy( newPath, newModAccessControlInp.path, MAX_NAME_LEN );
    resolveLinkedPath( rsComm, newPath, &specCollCache, NULL );
    if ( strcmp( newPath, newModAccessControlInp.path ) != 0 ) {
        newModAccessControlInp.path = newPath;
    }

    status = getAndConnRcatHost(
                 rsComm,
                 MASTER_RCAT,
                 ( const char* )newModAccessControlInp.path,
                 &rodsServerHost );
    if ( status < 0 ) {
        return status;
    }

    if ( rodsServerHost->localFlag == LOCAL_HOST ) {
#ifdef RODS_CAT
        status = _rsModAccessControl( rsComm, &newModAccessControlInp );
#else
        status = SYS_NO_RCAT_SERVER_ERR;
#endif
    }
    else {
        status = rcModAccessControl( rodsServerHost->conn,
                                     &newModAccessControlInp );
    }

    if ( status < 0 ) {
        rodsLog( LOG_NOTICE,
                 "rsModAccessControl: rcModAccessControl failed" );
    }
    return status;
}

#ifdef RODS_CAT
int
_rsModAccessControl( rsComm_t *rsComm,
                     modAccessControlInp_t *modAccessControlInp ) {
    int status, status2;

    const char *args[MAX_NUM_OF_ARGS_IN_ACTION];
    ruleExecInfo_t rei2;
    memset( ( char* )&rei2, 0, sizeof( ruleExecInfo_t ) );
    rei2.rsComm = rsComm;
    if ( rsComm != NULL ) {
        rei2.uoic = &rsComm->clientUser;
        rei2.uoip = &rsComm->proxyUser;
    }

    char rFlag[15];
    snprintf( rFlag, sizeof( rFlag ), "%d", modAccessControlInp->recursiveFlag );
    args[0] = rFlag;
    args[1] = modAccessControlInp->accessLevel;
    args[2] = modAccessControlInp->userName;
    args[3] = modAccessControlInp->zone;
    args[4] = modAccessControlInp->path;
    int argc = 5;
    status2 = applyRuleArg( "acPreProcForModifyAccessControl", args, argc, &rei2, NO_SAVE_REI );
    if ( status2 < 0 ) {
        if ( rei2.status < 0 ) {
            status2 = rei2.status;
        }
        rodsLog( LOG_ERROR,
                 "rsModAVUMetadata:acPreProcForModifyAccessControl error for %s.%s of level %s for %s,stat=%d",
                 modAccessControlInp->zone,
                 modAccessControlInp->userName,
                 modAccessControlInp->accessLevel,
                 modAccessControlInp->path, status2 );
        return status2;
    }

    status = chlModAccessControl( rsComm,
                                  modAccessControlInp->recursiveFlag,
                                  modAccessControlInp->accessLevel,
                                  modAccessControlInp->userName,
                                  modAccessControlInp->zone,
                                  modAccessControlInp->path );

    if ( status == 0 ) {
        status2 = applyRuleArg( "acPostProcForModifyAccessControl",
                                args, argc, &rei2, NO_SAVE_REI );
        if ( status2 < 0 ) {
            if ( rei2.status < 0 ) {
                status2 = rei2.status;
            }
            rodsLog( LOG_ERROR,
                     "rsModAVUMetadata:acPostProcForModifyAccessControl error for %s.%s of level %s for %s,stat=%d",
                     modAccessControlInp->zone,
                     modAccessControlInp->userName,
                     modAccessControlInp->accessLevel,
                     modAccessControlInp->path,
                     status2 );
            return status;
        }
    }

    return status;
}
#endif
