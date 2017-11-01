/* File:        lci.c
 * Description: This program is a layer between a lua script and a c library.
 *              It's a deductive stuff, thus has a lot of comments.
 * Author:      Vladimir Valeyev
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int main(int argc, char* argv[])
{
    FILE* script;
    char* buffer;
    int position;
    int length;

    char line[256];
    lua_State* L;
    int error;

    /* This needs some input files on a command line */
    if (argc == 2) {
        script = fopen(argv[1], "r");
        if (script) {
            fseek(script, 0, SEEK_END);
            length = ftell(script);
            fseek(script, 0, SEEK_SET);
#if LUA_VERSION_NUM < 502 /* Use lua_open() function to get lua_State */
            L = lua_open();
#else /* Use luaL_newstate() to get lua_State (as of lua 5.3) */
            L = luaL_newstate();
#endif /* LUA_VERSION_NUM < 502 */
#if LUA_VERSION_NUM < 501 /* Use luaopen_*() functions to load libraries */
            luaopen_base(L); /* basic library */
            luaopen_table(L); /* table library */
            luaopen_io(L); /* input/output library */
            luaopen_string(L); /* string library */
            luaopen_math(L); /* math library */
#else /* Use luaL_openlibs() function to load libraries */
            luaL_openlibs(L); /* all the libraries */
#endif /* LUA_VERSION_NUM < 501 */
            /* Process the script */
            while (fgets(line, sizeof line, script)) {
                error = (luaL_loadbuffer(L, line, strlen(line), "line")
                        || lua_pcall(L, 0, 0, 0));
                if (error) {
                    fprintf(stderr, "%s\n", lua_tostring(L, -1));
                    lua_pop(L, 1); /* pop error message */
                }
            }
            /* TODO (ValV): remove after script processing implemented */
            fseek(script, 0, SEEK_SET);
            buffer = malloc(length);
            if (buffer) {
                fread(buffer, 1, length, script);
                /* Display the contents of the script */
                fwrite(buffer, 1, length, stdout);
            }
            free(buffer);
            fclose(script);
            lua_close(L);
        }
    } else {
        printf("Usage:\t%s <script_file>\n", argv[0]);
    }
}

/* vim: set et sw=4 ts=4: */
