/*
    https://www.embedthis.com/goahead/doc/

    Usage: goahead-test [options] [documents] [endpoints...]
        Options:
        --auth authFile        # User and role configuration
        --home directory       # Change to directory to run
        --log logFile:level    # Log to file file at verbosity level
        --route routeFile      # Route configuration file
        --verbose              # Same as --log stderr:2
        --version              # Output version information

    Copyright (c) All Rights Reserved. See details at the end of the file.
 */

/********************************* Includes ***********************************/

#include    "goahead.h"
#include    "js.h"
#include "webs_agent_main.h" //yut_webs_agent
/********************************* Defines ************************************/

static int finished = 0;

#undef ME_GOAHEAD_LISTEN
/*
    These must match TOP.es.set
 */
#if TEST_IPV6
#if ME_COM_SSL
    #define ME_GOAHEAD_LISTEN "http://127.0.0.1:18080, https://127.0.0.1:14443, http://[::1]:18090, https://[::1]:14453"
#else
    #define ME_GOAHEAD_LISTEN "http://127.0.0.1:18080, http://[::1]:18090"
#endif
#else
#if ME_COM_SSL
    #define ME_GOAHEAD_LISTEN "http://127.0.0.1:18080, https://127.0.0.1:14443"
#else
    #define ME_GOAHEAD_LISTEN "http://127.0.0.1:18080"
#endif
#endif

/********************************* Forwards ***********************************/

static void initPlatform(void);
static void logHeader(void);
static void usage(void);
//yut_webs_agent
static void action_webs_agent(Webs *wp);
//
#if ME_GOAHEAD_UPLOAD && !ME_ROM
static void uploadTest(Webs *wp);
#endif
#if ME_UNIX_LIKE
static void sigHandler(int signo);
#endif
static void exitProc(void *data, int id);

/*********************************** Code *************************************/

MAIN(goahead, int argc, char **argv, char **envp)
{
    char    *argp, *auth, *home, *documents, *endpoints, *endpoint, *route, *tok, *lspec;
    int     argind, duration;

    route = "route.txt";
    auth = "auth.txt";
    duration = 0;

    for (argind = 1; argind < argc; argind++) {
        argp = argv[argind];
        if (*argp != '-') {
            break;

        } else if (smatch(argp, "--auth") || smatch(argp, "-a")) {
            if (argind >= argc) usage();
            auth = argv[++argind];



        } else if (smatch(argp, "--debugger") || smatch(argp, "-d") || smatch(argp, "-D")) {
            websSetDebug(1);

        } else if (smatch(argp, "--duration")) {
            if (argind >= argc) usage();
            duration = atoi(argv[++argind]);

        } else if (smatch(argp, "--home")) {
            if (argind >= argc) usage();
            home = argv[++argind];
            if (chdir(home) < 0) {
                error("Cannot change directory to %s", home);
                exit(-1);
            }
        } else if (smatch(argp, "--log") || smatch(argp, "-l")) {
            if (argind >= argc) usage();
            logSetPath(argv[++argind]);

        } else if (smatch(argp, "--verbose") || smatch(argp, "-v")) {
            logSetPath("stdout:2");

        } else if (smatch(argp, "--route") || smatch(argp, "-r")) {
            route = argv[++argind];

        } else if (smatch(argp, "--version") || smatch(argp, "-V")) {
            printf("%s\n", ME_VERSION);
            exit(0);

        } else if (*argp == '-' && isdigit((uchar) argp[1])) {
            lspec = sfmt("stdout:%s", &argp[1]);
            logSetPath(lspec);
            wfree(lspec);

        } else {
            usage();
        }
    }
    documents = ME_GOAHEAD_DOCUMENTS;
    if (argc > argind) {
        documents = argv[argind++];
    }
    initPlatform();
    if (websOpen(documents, route) < 0) {
        error("Cannot initialize server. Exiting.");
        return -1;
    }
    logHeader();
    if (websLoad(auth) < 0) {
        error("Cannot load %s", auth);
        return -1;
    }
    if (argind < argc) {
        while (argind < argc) {
            endpoint = argv[argind++];
            if (websListen(endpoint) < 0) {
                return -1;
            }
        }
    } else {
        endpoints = sclone(ME_GOAHEAD_LISTEN);
        for (endpoint = stok(endpoints, ", \t", &tok); endpoint; endpoint = stok(NULL, ", \t,", &tok)) {
            if (getenv("TRAVIS")) {
                if (strstr(endpoint, "::1") != 0) {
                    /* Travis CI does not support IPv6 */
                    continue;
                }
            }
            if (websListen(endpoint) < 0) {
                return -1;
            }
        }
        wfree(endpoints);
    }
    //yut_webs_agent
    //1. regist the webs_agent in web url
    //2. define the function for this entry
    websDefineAction("webs_agent", action_webs_agent);
    //
#if ME_GOAHEAD_UPLOAD && !ME_ROM
    websDefineAction("uploadTest", uploadTest);
#endif

#if ME_UNIX_LIKE && !MACOSX
    /*
        Service events till terminated
    */
    if (websGetBackground()) {
        if (daemon(0, 0) < 0) {
            error("Cannot run as daemon");
            return -1;
        }
    }
#endif
    if (duration) {
        printf("Running for %d secs\n", duration);
        websStartEvent(duration * 1000, (WebsEventProc) exitProc, 0);
    }
    websServiceEvents(&finished);
    logmsg(1, "Instructed to exit\n");
    websClose();
    return 0;
}


static void exitProc(void *data, int id)
{
    websStopEvent(id);
    finished = 1;
}


static void logHeader(void)
{
    char    home[ME_GOAHEAD_LIMIT_STRING];

    getcwd(home, sizeof(home));
    logmsg(2, "Configuration for %s", ME_TITLE);
    logmsg(2, "---------------------------------------------");
    logmsg(2, "Version:            %s", ME_VERSION);
    logmsg(2, "BuildType:          %s", ME_DEBUG ? "Debug" : "Release");
    logmsg(2, "CPU:                %s", ME_CPU);
    logmsg(2, "OS:                 %s", ME_OS);
    logmsg(2, "Host:               %s", websGetServer());
    logmsg(2, "Directory:          %s", home);
    logmsg(2, "Documents:          %s", websGetDocuments());
    logmsg(2, "Configure:          %s", ME_CONFIG_CMD);
    logmsg(2, "---------------------------------------------");
}


static void usage(void) {
    fprintf(stderr, "\n%s Usage:\n\n"
        "  %s [options] [documents] [IPaddress][:port]...\n\n"
        "  Options:\n"
        "    --auth authFile        # User and role configuration\n"
#if ME_UNIX_LIKE && !MACOSX
        "    --background           # Run as a Unix daemon\n"
#endif
        "    --debugger             # Run in debug mode\n"
        "    --home directory       # Change to directory to run\n"
        "    --log logFile:level    # Log to file file at verbosity level\n"
        "    --route routeFile      # Route configuration file\n"
        "    --verbose              # Same as --log stderr:2\n"
        "    --version              # Output version information\n\n",
        ME_TITLE, ME_NAME);
    exit(-1);
}


void initPlatform(void)
{
#if ME_UNIX_LIKE
    signal(SIGINT, sigHandler);
    signal(SIGTERM, sigHandler);
    signal(SIGKILL, sigHandler);
    #ifdef SIGPIPE
        signal(SIGPIPE, SIG_IGN);
    #endif
#elif ME_WIN_LIKE
    _fmode=_O_BINARY;
#endif
}


#if ME_UNIX_LIKE
static void sigHandler(int signo)
{
    finished = 1;
}
#endif



/* -------------------------------
    Implement /action/webs_agent. Parse the form variables and echo back.
    ------------------------------
    * yangyutong:2019
    * 此处实现ajax.并且本样例只支持ajax数据!!!
    * 利用了cJson库来解析web传过来的json object
    * input JSON格式：
      { "command: "xxCommand",
        "dat":{"key1":"xxValue"}
        }
    * echo result JSON格式：
      { "rc: 0/1, 
        "errCode: "error msg txt",
        "dat:{"key1":"xxValue"}
        }
 */
#define MAX_INPUT_BUFF 4096
static void action_webs_agent(Webs *wp)
{
    cJSON* p_json_in = NULL;
    cJSON* p_json_node = NULL;
    char* p_json_node_value;
    //
    //* get input buff
    char buff[MAX_INPUT_BUFF];
    int len = bufGetBlk(&(wp->input), buff, bufLen(&(wp->input)));
    buff[len] = '\0'; //插入结束符
    //* decode json object by cJSON libs' api
    p_json_in = cJSON_Parse(buff);
    if(!p_json_in)
    {
        printf("Error[webs_agent] : [%s]\n", cJSON_GetErrorPtr());
        return;
    }
    else
    {
        // create the output cjson root
        cJSON* p_json_out = cJSON_CreateObject();
        // create the node. "dat"
        cJSON* p_json_out_dat = cJSON_CreateObject();
        cJSON_AddItemToObject(p_json_out, JSON_DAT, p_json_out_dat);

        // get the input value of key:command
        p_json_node = cJSON_GetObjectItem(p_json_in, JSON_COMMAND);
        p_json_node_value = cJSON_GetStringValue(p_json_node);
        printf("Log[ajax-command] : [%s]\n", p_json_node_value);
        if(!strcasecmp(p_json_node_value, SET_CFG_INFOR)){
            func_SET_CFG_INFOR(p_json_in, p_json_out);
        }else if(!strcasecmp(p_json_node_value, GET_CFG_INFOR)){
            func_GET_CFG_INFOR(p_json_in, p_json_out);
        }
        //
        // 4. fill the goAction webs return.
        websSetStatus(wp, 200);
        websWriteHeaders(wp, -1, 0);
        websWriteEndHeaders(wp);
        websWrite(wp, "%s", cJSON_Print(p_json_out));
        websFlush(wp, 0);
        websDone(wp);
    }
}


#if ME_GOAHEAD_UPLOAD && !ME_ROM
/*
    Dump the file upload details. Don't actually do anything with the uploaded file.
 */
static void uploadTest(Webs *wp)
{
    WebsKey         *s;
    WebsUpload      *up;
    char            *upfile;

    websSetStatus(wp, 200);
    websWriteHeaders(wp, -1, 0);
    websWriteHeader(wp, "Content-Type", "text/plain");
    websWriteEndHeaders(wp);
    if (scaselessmatch(wp->method, "POST")) {
        for (s = hashFirst(wp->files); s; s = hashNext(wp->files, s)) {
            up = s->content.value.symbol;
            websWrite(wp, "FILE: %s\r\n", s->name.value.string);
            websWrite(wp, "FILENAME=%s\r\n", up->filename);
            websWrite(wp, "CLIENT=%s\r\n", up->clientFilename);
            websWrite(wp, "TYPE=%s\r\n", up->contentType);
            websWrite(wp, "SIZE=%d\r\n", up->size);
            upfile = sfmt("%s/tmp/%s", websGetDocuments(), up->clientFilename);
            if (rename(up->filename, upfile) < 0) {
                error("Cannot rename uploaded file: %s to %s, errno %d", up->filename, upfile, errno);
            }
            wfree(upfile);
        }
        websWrite(wp, "\r\nVARS:\r\n");
        for (s = hashFirst(wp->vars); s; s = hashNext(wp->vars, s)) {
            websWrite(wp, "%s=%s\r\n", s->name.value.string, s->content.value.string);
        }
    }
    websDone(wp);
}
#endif

/*
    @copy   default

    Copyright (c) Embedthis Software LLC, 2003-2014. All Rights Reserved.

    This software is distributed under commercial and open source licenses.
    You may use the Embedthis GoAhead open source license or you may acquire
    a commercial license from Embedthis Software. You agree to be fully bound
    by the terms of either license. Consult the LICENSE.md distributed with
    this software for full details and other copyrights.

    Local variables:
    tab-width: 4
    c-basic-offset: 4
    End:
    vim: sw=4 ts=4 expandtab

    @end
 */
