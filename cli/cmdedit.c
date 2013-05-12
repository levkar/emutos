/*
 * EmuCON2 command history handling
 *
 * Copyright (c) 2013 The EmuTOS development team
 *
 * Authors:
 *  RFB    Roger Burrows
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */
#include "cmd.h"
#include <string.h>

/*
 *  local to this set of functions
 */
LOCAL WORD history_num;
LOCAL char *history_line[HISTORY_SIZE];

/*
 *  function prototypes
 */
PRIVATE void delete_char(char *line,WORD pos,WORD len,WORD backspace);
PRIVATE WORD edit_line(char *line,WORD *pos,WORD *len,WORD scancode,WORD prevcode);
PRIVATE void erase_line(char *start,WORD len);
PRIVATE LONG getfirstnondot(char *buffer,WORD executable_only);
PRIVATE LONG getnextfile(WORD executable_only);
PRIVATE WORD next_history(char *line);
PRIVATE WORD next_word_count(char *line,WORD pos,WORD len);
PRIVATE WORD previous_history(char *line);
PRIVATE WORD previous_word_count(char *line,WORD pos);
PRIVATE WORD replace_line(char *line,WORD num);
PRIVATE char *start_of_current_word(char *line,WORD pos);

void read_line(char *line)
{
LONG charcode;
char c;
UWORD save_history_num;
WORD scancode, prevcode = 0;
WORD pos = 0, len = 0;
char prompt[] = "X:>";

    save_history_num = history_num;     /* so that edit_line() can play with it */

    prompt[0] = Dgetdrv() + 'A';
    message(prompt);
    while(1) {
        charcode = conin();
        scancode = ((charcode >> 8) | charcode) & 0xffff;

        /* check for line-editing key & handle if so */
        prevcode = edit_line(line,&pos,&len,scancode,prevcode);
        if (prevcode >= 0)
            continue;

        /* if any other non-ASCII key, ignore */
        c = charcode & 0xff;
        if (!c)
            continue;

        /* handle carriage return */
        if (c == '\r') {
            conout(c);
            conout('\n');       /* cr => crlf */
            line[len] = '\0';   /* nul-terminate line */
            break;
        }

        /* ignore other non-printable characters */
        if ((unsigned char)c < 0x20)
            continue;

        /* if other ASCII key but line is full, ignore */
        if (len >= linesize-2)
            continue;

        /* handle normal ASCII key */
        conout(c);
        if (pos < len)
            insert_char(line,pos,len,c);
        else line[len] = c;
        pos++;
        len++;
    }

    history_num = save_history_num;
}

/*
 *  insert character and redraw remainder of line
 */
void insert_char(char *line,WORD pos,WORD len,char c)
{
char *p;

    /* insert char in line */
    for (p = line+len; p > line+pos; p--)
        *p = *(p-1);
    *p++ = c;

    /* display characters after insertion point */
    while(p <= line+len)
        conout(*p++);

    /* reset insertion point */
    for ( ; p > line+pos+1; p--)
        cursor_left();
}

/*
 *  initialise command editing globals
 */
WORD init_cmdedit(void)
{
char *p;
WORD i;

    history_num = -1;       /* means history not available */

    p = (char *)Malloc(linesize*HISTORY_SIZE);
    if (!p)
        return -1;

    for (i = 0; i < HISTORY_SIZE; i++, p += linesize) {
        history_line[i] = p;
        *p = '\0';
    }

    history_num = 0;

    return 0;
}

/*
 *  save a line in the history
 */
void save_history(char *line)
{
    if (history_num < 0)
        return;

    strcpy((char *)(history_line[history_num]),(char *)line);

    if (++history_num >= HISTORY_SIZE)
        history_num = 0;
}

/*
 *  top level line editing routine
 */
PRIVATE WORD edit_line(char *line,WORD *pos,WORD *len,WORD scancode,WORD prevcode)
{
char buffer[MAXPATHLEN];
char *start, *p, *q;
LONG rc;
WORD n, shift = 0;

    switch(scancode) {
    case UPARROW:
        if (history_num >= 0) {
            erase_line(line,*len);
            *pos = *len = previous_history(line);
        }
        break;
    case DNARROW:
        if (history_num >= 0) {
            erase_line(line,*len);
            *pos = *len = next_history(line);
        }
        break;
    case LTARROW_SHFT:
        shift = 1;
    case LTARROW:
        if (*pos > 0) {
            n = shift ? previous_word_count(line,*pos) : 1;
            while (n-- > 0) {
                (*pos)--;
                cursor_left();
            }
        }
        break;
    case RTARROW_SHFT:
        shift = 1;
    case RTARROW:
        if (*pos < *len) {
            n = shift ? next_word_count(line,*pos,*len) : 1;
            while (n-- > 0) {
                (*pos)++;
                cursor_right();
            }
        }
        break;
    case BKSP:          /* delete char to left of cursor */
        if (*pos > 0) {
            delete_char(line,*pos,*len,1);
            (*pos)--;
            (*len)--;
        }
        break;
    case DEL:           /* delete char at cursor */
        if (*pos < *len) {
            delete_char(line,*pos,*len,0);
            (*len)--;
        }
        break;
    case TAB:           /* tab completion */
        start = start_of_current_word(line,*pos);
        if (start+sizeof(dta->d_fname)-line >= linesize)
            break;
        if (prevcode == TAB) {
            rc = getnextfile(start==line);
            if (rc < 0L) {              /* assume no more files */
                rc = getfirstnondot(buffer,start==line);
            }
        } else {
            for (p = start, q = buffer; p < line+*pos; )
                *q++ = *p++;
            *q++ = '*';
            *q++ = '.';
            *q++ = '*';
            *q = '\0';
            rc = getfirstnondot(buffer,start==line);
        }
        if (rc == 0L) {
            erase_line(start,*pos-(start-line));
            for (q = start, p = dta->d_fname; *p; ) {
                conout(*p);
                *q++ = *p++;
            }
            *q = '\0';
            *pos = *len = q - line;
        }
        break;
    default:
        /* we handle ASCII keys separately because scancodes can vary */
        switch(scancode & 0xff) {
        case CTL_C:
            erase_line(line,*len);
            *pos = *len = 0;
            break;
        default:
            return -1;  /* we didn't process this key */
        }
        break;
    }

    return scancode;    /* we processed this key */
}

/*
 *  delete character and redraw remainder of line
 *
 *  handles backspace or delete
 */
PRIVATE void delete_char(char *line,WORD pos,WORD len,WORD backspace)
{
char *p;

    if (backspace)          /* adjust position */
        pos--;

    /* delete char from line */
    for (p = line+pos; p < line+len; p++)
        *p = *(p+1);

    if (backspace)
        cursor_left();      /* adjust cursor */

    /* display characters after insertion point */
    for (p = line+pos; p < line+len-1; p++)
        conout(*p);
    conout(' ');            /* blank out end of line */

    /* reset insertion point */
    for ( ; p >= line+pos; p--)
        cursor_left();
}

#if 0
/*
 *  erase single character to left of cursor
 */
PRIVATE void erase_char(void)
{
    cursor_left();
    conout(' ');
    cursor_left();
}

/*
 *  erase to end of line (old method, assumed slower)
 */
PRIVATE void erase_line(char *start,WORD len)
{
WORD n;

    for (n = len; n > 0; n--)
        erase_char();

    *start = '\0';
}
#endif

/*
 *  erase to end of line
 */
PRIVATE void erase_line(char *start,WORD len)
{
WORD i;

    for (i = 0; i < len; i++)
        cursor_left();
    escape('K');

    *start = '\0';
}

/*
 *  display the next line in the circular history buffer
 */
PRIVATE WORD next_history(char *line)
{
    if (++history_num >= HISTORY_SIZE)
        history_num = 0;

    return replace_line(line,history_num);
}

/*
 *  display the previous line in the circular history buffer
 */
PRIVATE WORD previous_history(char *line)
{
    if (--history_num < 0)
        history_num = HISTORY_SIZE - 1;

    return replace_line(line,history_num);
}

/*
 *  display the line from the specified history buffer
 */
PRIVATE WORD replace_line(char *line,WORD num)
{
char *p, *q;

    for (p = line, q = history_line[num]; *q; ) {
        conout(*q);
        *p++ = *q++;
    }
    *p = '\0';

    return p - line;
}

/*
 *  return pointer to start of the current word
 */
PRIVATE char *start_of_current_word(char *line,WORD pos)
{
char *p;

    for (p = line+pos; p > line; p--) {
        if (*p == ' ')
            return p + 1;
    }

    /* no spaces found, so start of line */
    return line;
}

/*
 *  return the number of characters to the start of the
 *  next word
 */
PRIVATE WORD next_word_count(char *line,WORD pos,WORD len)
{
char *p;
WORD gotspace = 0;

    for (p = line+pos; p < line+len; p++) {
        if (*p == ' ')
            gotspace = 1;
        else if (gotspace)
            return p-(line+pos);
    }

    /* no spaces found, so count to end of line */
    return len-pos;
}

/*
 *  return the number of characters to the start of the
 *  previous word
 */
PRIVATE WORD previous_word_count(char *line,WORD pos)
{
char *p;
WORD gotword = 0;

    for (p = line+pos-1; p > line; p--) {
        if (*p != ' ')
            gotword = 1;
        else if (gotword)
            return line+pos-(p+1);
    }

    /* no spaces found, so count to start of line */
    return pos;
}

/*
 *  get first file/folder in dir that doesn't start with .
 */
PRIVATE LONG getfirstnondot(char *buffer,WORD executable_only)
{
LONG rc;

    for (rc = Fsfirst(buffer,0x17); !rc; rc=Fsnext()) {
        if (rc < 0L)
            break;
        if (dta->d_fname[0] == '.') /* ignore . & .. */
            continue;
        if (!executable_only)
            break;
        /* got filename, need to check for executable */
        if (program_extension(dta))
            break;
    }
    return rc;
}

/*
 *  get next file
 */
PRIVATE LONG getnextfile(WORD executable_only)
{
LONG rc;

    while(1) {
        rc = Fsnext();
        if ((rc < 0L) || !executable_only)
            break;
        /* got filename, need to check for executable */
        if (program_extension(dta))
            break;
    }

    return rc;
}
