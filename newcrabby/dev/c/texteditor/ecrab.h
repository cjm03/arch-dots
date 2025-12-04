#ifndef ECRAB_H
#define ECRAB_H

#include <time.h>
#include <termios.h>

enum editorKey {
    // ESCAPE = 27,
    BACKSPACE = 127,
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY
};

enum editorHighlight {
    HL_NORMAL = 0,
    HL_COMMENT,
    HL_MLCOMMENT,
    HL_KEYWORD1,
    HL_KEYWORD2,
    HL_STRING,
    HL_NUMBER,
    HL_MATCH
};

typedef enum MODE { INSERT, NORMAL } MODE;

#define HL_HIGHLIGHT_NUMBERS (1 << 0)
#define HL_HIGHLIGHT_STRINGS (1 << 1)

struct editorSyntax {
    char* filetype;
    char** filematch;
    char** keywords;
    char* slcstart;     // single-line comment start
    char* mlcstart;     // multi-line comment start
    char* mlcend;       // multi-line comment end
    int flags;
};

typedef struct erow {
    int idx;
    int size;
    int rsize;
    char* chars;
    char* render;
    unsigned char* hl;
    int hlopencomment;
} erow;

/* editor state */
struct editorConfig {
    int cx, cy;
    int rx;
    int rowoff;
    int coloff;
    int screenrows;
    int screencols;
    int numrows;
    erow* row;
    int dirty;
    MODE mode;
    char* filename;
    char statusmsg[80];
    time_t statusmsg_time;
    struct editorSyntax* syntax;
    struct termios orig_termios;    // <--  clean copy of terminal attributes
};

struct abuf {
    char* b;
    int len;
};



/* terminal */
void die(const char* s);
void disableRawMode(void);
void enableRawMode(void);
int editorReadKey(void);
int getCursorPosition(int* rows, int* cols);
int getWindowSize(int* rows, int* cols);

/* syntax highlighting */
int IsSeparator(int c);
void editorUpdateSyntax(erow* row);
int editorSyntaxToColor(int hl);
void editorSelectSyntaxHighlight(void);

/* row operations */
int editorRowCxToRx(erow* row, int cx);
void editorUpdateRow(erow* row);
void editorInsertRow(int at, char* s, size_t len);
void editorFreeRow(erow* row);
void editorDelRow(int at);
void editorRowInsertChar(erow* row, int at, int c);
void editorRowAppendString(erow* row, char* s, size_t len);
void editorRowDelChar(erow* row, int at);

/* editor operations */
void editorInsertChar(int c);
void editorInsertNewline(void);
void editorDelChar(void);

/* file i/o */
char* editorRowsToString(int* buflen);
void editorOpen(char* filename);
void editorSave(void);

/* append buffer */
void abAppend(struct abuf* ab, const char* s, int len);
void abFree(struct abuf* ab);

/* output */
void editorScroll(void);
void editorDrawRows(struct abuf* ab);
void editorDrawStatusBar(struct abuf* ab);
void editorDrawMessageBar(struct abuf* ab);
void editorRefreshScreen(void);
void editorSetStatusMessage(const char* fmt, ...);

/* input */
char* editorPrompt(char* prompt);
void editorMoveCursor(int key);
void editorProcessKeypress(void);

/* init */
void initEditor(void);


#endif     // ECRAB_H
