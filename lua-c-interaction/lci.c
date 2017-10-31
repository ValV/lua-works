/* File:        lci.c
 * Description: This program is a layer between a lua script and a c library.
 *              It's a deductive stuff, thus has a lot of comments.
 * Author:      Vladimir Valeyev
 */

#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int main(int argc, char* argv[])
{
    FILE* script;
    char* buffer;
    int position;
    int length;

    /* This needs some input files on a command line */
    if (argc > 1) {
        script = fopen(argv[1], "r");
        if (script) {
            fseek(script, 0, SEEK_END);
            length = ftell(script);
            fseek(script, 0, SEEK_SET);
            buffer = malloc(length);
            if (buffer) {
                fread(buffer, 1, length, script);
            }
            fclose(script);
            /* Display the contents of the script */
            fwrite(buffer, 1, length, stdout);
            free(buffer);
        }
    }
}

/* vim: set et sw=4 ts=4: */
