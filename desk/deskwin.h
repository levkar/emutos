/*      DESKWIN.H       06/11/84 - 01/04/85             Lee Lorenzen    */
/*      changed NUM_WOBS from 128 to 300        11/19/87        mdf     */
/*
*       Copyright 1999, Caldera Thin Clients, Inc.
*                 2002 The EmuTOS development team
*
*       This software is licenced under the GNU Public License.
*       Please see LICENSE.TXT for further information.
*
*                  Historical Copyright
*       -------------------------------------------------------------
*       GEM Desktop                                       Version 2.3
*       Serial No.  XXXX-0000-654321              All Rights Reserved
*       Copyright (C) 1987                      Digital Research Inc.
*       -------------------------------------------------------------
*/

#define DROOT 1
#define NUM_WNODES 2
#define NUM_WOBS 300
#define NUM_SOBS (NUM_WOBS + NUM_WNODES + 1)

#define WNODE struct windnode

WNODE
{
        WNODE           *w_next;
        WORD            w_flags;
        WORD            w_id;                   /* window handle id #   */
        WORD            w_obid;                 /* desktop object id    */
        WORD            w_root;                 /* pseudo root ob. in   */
                                                /*   gl_screen for this */
                                                /*   windows objects    */
        WORD            w_cvcol;                /* current virt. col    */
        WORD            w_cvrow;                /* current virt. row    */
        WORD            w_pncol;                /* physical # of cols   */
        WORD            w_pnrow;                /* physical # of rows   */
        WORD            w_vncol;                /* virtual # of cols    */
        WORD            w_vnrow;                /* virtual # of rows    */
        PNODE           *w_path;
        BYTE            w_name[LEN_ZPATH];
/*      BYTE            w_info[81];             NOT USED v2.1           */
};



/* Prototypes: */
void win_view(WORD vtype, WORD isort);
void win_start(void);
void win_free(WNODE *thewin);
WNODE *win_alloc(void);
WNODE *win_find(WORD wh);
void win_top(WNODE *thewin);
WNODE *win_ith(WORD level);
void win_bldview(WNODE *pwin, WORD x, WORD y, WORD w, WORD h);
void win_slide(WORD wh, WORD sl_value);
void win_arrow(WORD wh, WORD arrow_type);
void win_srtall(void);
void win_bdall(void);
void win_shwall();
WORD win_isel(OBJECT olist[], WORD root, WORD curr);
void win_sname(WNODE *pw);

