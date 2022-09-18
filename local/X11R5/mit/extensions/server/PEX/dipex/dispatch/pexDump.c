/* $XConsortium: pexDump.c,v 5.1 91/02/16 09:56:40 rws Exp $ */

/***********************************************************
Copyright 1989, 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Sun Microsystems,
the X Consortium, and MIT not be used in advertising or publicity 
pertaining to distribution of the software without specific, written 
prior permission.  

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/


/*
 *	File:	pexDump.c
 *
 *	Module(s):
 *		PEXDumpScruc
 *              PEXDumpBlock
 *	Notes:
 *
 */

#ifdef	DUMP_ON

#include "X.h"
#include "PEXproto.h"
#include "Xproto.h"
#include "misc.h"
#include "dixstruct.h"
#include "dix.h"
#include "pexSwap.h"
#include "dipex.h"

#include "pexStruct.h"

PEXDumpBlock( block )
struct structureBlock *block;
{
int i;
struct genericElement *cmd;
char                  *curCmd;

   ErrorF( "\n\nDump of block: %8.8x\n", block );
   ErrorF( "prev, next: %8.8x %8.8x\n", block->prev, block->next );
   ErrorF( "element size: %d  next free: %d\n",
                    block->elementSize, block->nextFree );

   curCmd = block->elements;

   while( 1 )
   {

      cmd  = ( struct genericElement * )curCmd;

      switch( cmd->opcode )
      {
   
         case OP_POLYLINE3D:
         {
         struct elPolyline3D *pl;
   
            pl = ( struct elPolyline3D * )cmd;

            ErrorF( "Polyline vertex count = %d\n",
                             pl->count );
            curCmd += sizeof( struct elPolyline3D ) + 
                      ( pl->count - 1 ) * sizeof( struct point3d );

            for( i = 0; i < pl->count; i++ )
            {
               ErrorF( "%d ( %f %f %f )\n",
                        i, 
                        pl->points[i].x,
                        pl->points[i].y,
                        pl->points[i].z
                      );
            }
            ErrorF( "\n" );
         }
         break;

         case 0:
         {
         struct elEndBlock *end;

            end = ( struct elEndBlock * )cmd;
            ErrorF( "End Block, next: %8.8x\n", end->next );

            return;
         }
         break;

         default:
            ErrorF( "--WARNING unrecognized opcode found--\n" );
            ErrorF( "--the rest of this block is assumed HOSED--\n" );
            return;
         break;

      } /* switch( cmd->opcode ) */

   } /* while( 1 ) */

} /* function PEXDumpBlock */
   


PEXDumpStructure( context, id )
pexContext *context;
int id;
{
struct phigsStructure *str;
struct structureBlock *block;


   str = PEXLookupStruc( context, id );
   if( str == 0 )
   {
      ErrorF( "no structure with id: %d %8.8x\n", id, id );
      return;
   }

   ErrorF( "dump of structure: %d  %8.8x\n", id, id );
   ErrorF( "  at address: %8.8x\n", str );
   ErrorF( "  previous, next: %8.8x %8.8x\n",
                    str->prev, str->next);
   ErrorF( "  first, last block: %8.8x %8.8x\n",
                    str->firstBlock, str->lastBlock );
   ErrorF( "  edit block, element: %8.8x  %8.8x\n",
                    str->editBlock, str->editElement );
   ErrorF( "  search block, element: %8.8x %8.8x \n",
                    str->searchBlock, str->searchElement );
   ErrorF( "  element count: %d\n", str->elementCount );
   ErrorF( "  curElement: %d\n", str->curElement );
   ErrorF( "  edit Mode: %d\n", str->editMode );

   
   block = str->firstBlock;
   while( block )
   {
      PEXDumpBlock( block );
      block = block->next;
   }

}

#endif	/* DUMP_ON */

