/*-------------------------------------------------------------------------
 *
 * copy.h
 *	  Definitions for using the POSTGRES copy command.
 *
 *
 * Portions Copyright (c) 1996-2013, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/commands/copy.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef COPY_H
#define COPY_H

#include "nodes/execnodes.h"
#include "nodes/parsenodes.h"
#include "tcop/dest.h"

/* CopyStateData is private in commands/copy.c */
typedef struct CopyStateData *CopyState;

extern Oid DoCopy(const CopyStmt *stmt, const char *queryString,
	   uint64 *processed);

extern void ProcessCopyOptions(CopyState cstate, bool is_from, List *options);
extern CopyState BeginCopyFrom(Relation rel, const char *filename,
			  bool is_program, List *attnamelist, List *options);
extern void EndCopyFrom(CopyState cstate);
extern bool NextCopyFrom(CopyState cstate, ExprContext *econtext,
			 Datum *values, bool *nulls, Oid *tupleOid);
extern bool NextCopyFromRawFields(CopyState cstate,
					  char ***fields, int *nfields);
extern void CopyFromErrorCallback(void *arg);

extern DestReceiver *CreateCopyDestReceiver(void);
#ifdef PGXC
extern CopyState pgxcMatViewBeginCopyTo(Relation mvrel);
extern int64 pgxcDoCopyTo(CopyState cstate);
#endif /* PGXC */

#ifdef ADB
extern char *copy_cmd_comment_str;
extern bool  copy_cmd_comment;
#endif

#endif   /* COPY_H */
