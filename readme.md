# 项目情况简介
* 本项目是基于 goAhead 开源 web server 的定制说明，本项目其他内容来源于我们自己的嵌入式项目，没有权属纠纷。
* 本文档以 ***makefile*** 方式构建项目，同时相关脚本文件以 ***`bash`*** 编写，所以代码最好在 ***`Linux`*** 下进行编译调试或者 ***`Windows10-WSL`*** 方式。
* 所有重要的修改处都以 ***yutWebsAgentDemo*** 作为标记以方便大家阅读比较。
* 官方文档
   https://www.embedthis.com/goahead/doc/ref/api/goahead.html
# demo代码如何运行
1. 准备环境
   * **方法一Linux**：准备好Linux下的工作目录
   * **方法二Windows**：打开Windows10-WSL Ubuntu环境并准备好工作目录
2. clone代码
    ```
    https://gitee.com/cmajor-cd/yutWebsAgent.git
    https://github.com/cmajor-cd/yutWebsAgent.git
    ```
3. 进入源码目录并运行编译和发布脚本
    ```
    $ cd yut_webs_agentdemo/
    $ ./build.sh
    $ ./releaseGo.sh
    ```
    系统显示处如下log意味着运行成功。
    ```
    yangyt@DESKTOP-MI7438E:/mnt/d/workspace/yut_webs_agentdemo$ ./releaseGo.sh
    [sudo] password for yangyt:
    goahead: 2: Configuration for Embedthis GoAhead Community Edition
    goahead: 2: ---------------------------------------------
    goahead: 2: Version:            5.1.0
    goahead: 2: BuildType:          Debug
    goahead: 2: CPU:                x64
    goahead: 2: OS:                 linux
    goahead: 2: Host:               127.0.1.1
    goahead: 2: Directory:          /mnt/d/workspace/VS/yutWebsAgent/release/webserver
    goahead: 2: Documents:          /mnt/d/workspace/VS/yutWebsAgent/yut_webs_agentdemo/../release/webroot
    goahead: 2: Configure:          me -d -q -platform linux-x86-default -configure . -gen make
    goahead: 2: ---------------------------------------------
    goahead: 2: Started http://0.0.0.0:8080
    ```
4. 检查web运行情况。
* 打开浏览器并输入地址： `http://127.0.0.1:8080/demo.html`
* 显示demo页面
    <div><h4>用form提交数据=>form</h4></div>
    <form action=/action/yutWebsAgentDemoEntry method="post">
        <table>
        <tr><td>命令:</td><td><input type="text" name="command" value="submitNameValue"></td></tr>
        <tr><td>账号:</td><td><input type="text" name="name"></td></tr>
        <tr><td>密码:</td><td><input type="password" name="address"></td></tr>
        <tr><td><input type="submit" name="submit" value="submit"></td>
            <td><input type="reset" value="reset"></td></tr>
        </table>
    </form>
    <div><h4>用ajax刷新=>触发getNetworkCfgInfor()</h4>
        <div id="myDemoText"></div>
    </div>
    <button type="button" onclick="getNetworkCfgInfor()">AJAX刷新</button>

# 目录说明
1. goahead_src
   * goahead的官方源代码。
   * 该目录被 build.sh 引用。
   * 如果要改动需要同步变更 build.sh 脚本中$定义的：goahead_src_dir / goahead_src_projects_dir
2. yut_webs_agentdemo
   * 移植定制文件目录，您可以变更为您自己的目录名。
   * 如果要改动 **该目录名** 需要同步变更同级目录下的makefile文件``yut_webs_agent.mk`` 脚本中的```SRC_CODE_DIR```定义。
   * 该目录中的文件
     * source files
     * makefile文件: 缺省的mk文件名为```yut_webs_agent.mk```，该文件需与`build.sh`脚本中的``$mk_filename``定义保持一致。 
     * build.sh编译脚本文件，该脚本定义了build-make方法，请注意定制是保证以下内容正确：
        ```
        goahead_src_dir="../goahead_src"
        goahead_src_projects_dir="../goahead_src/projects"
        build_dir="../build"
        mk_filename="yut_webs_agent.mk"
        ```
     * releaseGo.sh调试发布脚本文件，该脚本将自定义的源文件编译完成并将最终的bin文件和相关文件+web app代码发布到``./release``目录下，请注意定制是保证以下内容正确：
        ```
        rel_webs_bin_dir="../release/webserver"
        rel_webs_root_dir="../release/webroot"
        build_bin_dir="../build/bin"
        build_webs_root_dir="./webroot"
        build_bin_filename="yut_webs_agentdemo.bin"
        goahead_src_dir="../goahead_src"    
        ```
   * 该目录中的子目录
     * webroot: web app的源代码目录，请保证**该子目录名**与`releaseGo.sh`脚本中的``$build_webs_root_dir``保持一致。
3. libs
   * 3方库文件存放目录。
   * 该**目录名**需要与``yut_webs_agent.mk`` 脚本中的```LIBS_3rd```定义保持一致。
3. build   
    build.sh编译脚本，编译定制代码后的输出文件存放目录。
4. release   
    `releaseGo.sh`发布编译结果所在的文件目录。   
    注意：如果是最终发布，需要确保``./release/webroot/``中的web app代码已经编译过。因为```releaseGo.sh```没有去本web app的代码是否已经编译过！

# 定制说明
## 1.构建项目定制源代码目录
* 按照demo的目录结构构建自己的目录
  * 可以简单的 ``git clone``，也可以手工构建。
  * 将子目录名 ``yut_webs_agentdemo`` 改为自己的目录名，该目录存放自己的代码文件。
* 构建自己的makefile文件
  * 参考demo中的 ``yut_webs_agent.mk`` 创建自己的makefile文件。请注意该makefile文件的模板来自于``../goahead/projects``，您可以直接copy其中合适的mk文件过来并修改为**自定义文件名**。
* 修改`build.sh`文件
  * 修改 ``build.sh`` 脚本中的 ``$mk_filename`` 为与上一节相同的**自定义文件名**。
  * 以本目录为base确保以下路径和目录名定义正确。
    ```
    goahead_src_dir="../goahead_src"
    goahead_src_projects_dir="../goahead_src/projects"
    ```
* 修改``releaseGo.sh``文件，请注意定制是保证以下内容正确：
  * 修改 ``releaseGo.sh`` 脚本中的 ``$build_bin_filename`` 为与希望生成的最终bin文件的**自定义文件名**相同。
  * 以本目录为base确保以下路径和目录名定义正确。
    ```
    rel_webs_bin_dir="../release/webserver"
    rel_webs_root_dir="../release/webroot"
    build_bin_dir="../build/bin"
    build_webs_root_dir="./webroot"
    build_bin_filename="yut_webs_agentdemo.bin"
    goahead_src_dir="../goahead_src"    
    ```
## 2.定制makefile文件
### 2.1.行为说明   
    编译中 ``build.sh`` 脚本会将makefile文件拷贝到 ``$goahead_src_projects_dir`` 中，并执行make。
### 2.1.定制方法   
* **PROFILE**   
  如果是按照goahead官方的方法定制, build目录将在goahead目录下，该参数将影响**$CONFIG**，最终决定了build的目录位置。   
  在使用本方法定制时，我们更改了build目录位置到父一级目录，所以该参数无意义。
* **ARCH**   
  根据具体的情况来定义，比如：`ARCH ?=arm`
* **CC**   
  根据具体的情况来定义。
    * 比如，在Ubuntu下调试可以设置为：`CC ?= gcc`
    * 比如，在ARM下调试可以设置交叉编译环境为：`CC ?=arm-fsl-linux-gnueabi-gcc`
* **BUILD**   
  为了方便组织代码和调试，我们将 `$BUILD` 设置到父一级目录，同时为了添加**三方库**和方便组织**定制源码**需要增加两个变量 `$LIBS_3rd / $SRC_CODE_DIR`。
    ```
    BUILD        ?= ../build
    LIBS_3rd     ?= ../libs
    SRC_CODE_DIR ?= ../yut_webs_agentdemo
    ```
    ***注意***：`$SRC_CODE_DIR` 需要与您的**定制源码子目录**保持一致！
* **开放和关闭官方模块**   
    可以通过设置相应的项为``1/0``来开放或关闭官方提供的独立模块。   
    比如：关闭SSL模块   
    ``ME_COM_SSL ?= 0``
* **TARGETS**   
    根据自己的规划定义build输出bin文件信息：
    ```
    TARGETS += $(BUILD)/bin/yut_webs_agentdemo.bin
    ```
    ***注意***：`yut_webs_agentdemo.bin` 需要与您在后面设置的**link输出bin文件名**保持一致！
* **clean:**   
    将自己添加的`libs`以及`定制源文件`编译的中间文件和输出文件名加入`clean`中，以达成`make clean`操作时能够清理相关文件。
    ```
    rm -f "$(BUILD)/obj/yut_webs_agentdemo.o"
	rm -f "$(BUILD)/obj/cJSON.o"
	rm -f "$(BUILD)/bin/yut_webs_agentdemo.bin"
    ```
* **compile lib / source files**   
    仿照mk文件中其他`lib`和`source files`的编写方式编写新的`lib`和`soure files`编译脚本。
    ***注意：***
    * mk变量定义要唯一，如：`DEPS_yut_cjson_1` 和 `DEPS_yut_main_1`
    * lib库路径和soure files路径要正确，如：`$(LIBS_3rd)` 和 `$(SRC_CODE_DIR)`
* **link lib / source files**   
    仿照mk文件中其他`goahead-test`的编写方式编写新的`TARGETS`链接输出脚本。
    ***注意：***
    * mk变量定义要唯一，如：`DEPS_yut_main_x`
    * TARGETS的名字要正确，如：`yut_webs_agentdemo.bin`
* **other link output**   
    对官方提供其他 features 的链接输出配置，可以根据具体的需求保留相关配置或者注释掉。   
    比如，样例mk中将 `gopass` 注释掉后，该模块不再 `link` 出目标bin文件。

## 3.定制 main.c(goAction方式)的功能代码   
    作为样例的main.c文件 yut_webs_agentdemo.c，来自于goAhead官方的样例文件 ./goahead_src/test.c。其中有一些不需要内容已经删除，保留了主要的、与goAction编程相关的以便于作为demo阅读。
### 3.1.action处理函数声明和注册
* **声明action处理函数**   
    在文件头部声明action处理函数，如： 
    ```
    static void actionWebsAgentDemoEntry(Webs *wp);
    ```
* **注册action处理函数**   
    在`main()`函数中注册action处理函数，如： 
    ```
    websDefineAction("yutWebsAgentDemoEntry", actionWebsAgentDemoEntry);
    ```
* **action函数编写样例**   
    ```
    //yutWebsAgentDemo
    //static void actionTest(Webs *wp);
    static void actionWebsAgentDemoEntry(Webs *wp);
    /****** Code *******/
    MAIN(goahead, int argc, char **argv, char **envp)
    {
        /*argc 处理过程略... */
        /*initPlatform()  处理过程略.. */

        //yutWebsAgentDemo
        //1. regist the yutWebsAgentDemoEntry in web url
        //2. define the function for this entry
        websDefineAction("yutWebsAgentDemoEntry", actionWebsAgentDemoEntry);
        //
        if (duration) {
            printf("Running for %d secs\n", duration);
            websStartEvent(duration * 1000, (WebsEventProc) exitProc, 0);
        }
        websServiceEvents(&finished);
        logmsg(1, "Instructed to exit\n");
        websClose();
        return 0;
    }
    ```
### 3.2.action处理函数实现(form提交方式)
#### 3.2.1.FORM技术特点   
form data 是html技术中常用的数据提交和刷新方式，它的主要特点如下：
* ***全页面*** 刷新。
* 它的html代码形态，样例：
    ```
    <form action=/action/yutWebsAgentDemoEntry method="post">
        <table>
        <tr><td>命令:</td><td><input type="text" name="command" value="submitNameValue"></td></tr>
        <tr><td>账号:</td><td><input type="text" name="name"></td></tr>
        <tr><td>密码:</td><td><input type="password" name="address"></td></tr>
        <tr><td><input type="submit" name="submit" value="submit"></td>
            <td><input type="reset" value="reset"></td></tr>
        </table>
    </form>
    ```
    <form action=/action/yutWebsAgentDemoEntry method="post">
        <table>
        <tr><td>命令:</td><td><input type="text" name="command" value="submitNameValue"></td></tr>
        <tr><td>账号:</td><td><input type="text" name="name"></td></tr>
        <tr><td>密码:</td><td><input type="password" name="address"></td></tr>
        <tr><td><input type="submit" name="submit" value="submit"></td>
            <td><input type="reset" value="reset"></td></tr>
        </table>
    </form>
* 它的http数据格式，样例：```command=submitNameValue&name=&address=&submit=submit```
#### 3.2.1.goAction处理方式   
goAction提供了API函数可以直接处理FORM样式数据。样例如下:
```
int SUBMIT_NAME_VALUE_func(Webs *wp){
    cchar *name, *address;

    name = websGetVar(wp, "name", NULL);
    address = websGetVar(wp, "address", NULL);
    websSetStatus(wp, 200);
    websWriteHeaders(wp, -1, 0);
    websWriteEndHeaders(wp);
    websWrite(wp, "<html><body><h2>demo name: %s, demo address: %s</h2></body></html>\n", name, address);
    websFlush(wp, 0);
    websDone(wp);
}
```
### 3.3.action处理函数实现(ajax提交方式)   
大多数web页面都要求进行局部刷新，所以处理ajax是必不可少的能力。goAhead官方没有提供直接的API来处理ajax。但它的API结构中有名为`Webs`的数据结构，其保存了所有的`http消息`信息，我们可以通过Webs中的数据来处理ajax请求。
#### 3.3.1.导入cJSON库   
    外部三方库的引入方式前面章节已经详细讲解，请直接参考前面章节。
#### 3.3.2.获取输入数据buff   
我们可以通过goAction提供的API函数 `bufLen() / bufGetBlk() `来获取Webs中原始数据。
* 获取输入http数据缓冲区：`wp->input`
* 获取缓冲区数据用于后续处理: buff中即是获取的`json`数据包。
```
    //* get input buff
    char buff[MAX_INPUT_BUFF];
    int len = bufGetBlk(&(wp->input), buff, bufLen(&(wp->input)));
    buff[len] = '\0'; //插入结束符
```
#### 3.3.3.转换json数据到value   
我们使用`cJSON`的API函数来完成转换工作。
```
    cJSON* p_json_root = NULL;
    cJSON* p_json_node = NULL;
    char* p_json_node_value;
    //
    /* get input buff
     * => buff[len] 已经就绪
     */
    //* decode json object by cJSON libs' api
    p_json_root = cJSON_Parse(buff);
    if(!p_json_root)
    {
        printf("Error[actionWebsAgentDemoEntry] : [%s]\n", cJSON_GetErrorPtr());
        return;
    }
    else
    {
        p_json_node = cJSON_GetObjectItem(p_json_root, JSON_COMMAND);
        p_json_node_value = cJSON_GetStringValue(p_json_node);
        printf("Log[ajax-command] : [%s]\n", p_json_node_value);
        /* p_json_node_value 中即为与 JSON_COMMAND 对应的Value //#define JSON_COMMAND "command"
        */
        ...后续处理代码
    }
```
#### 3.3.4.打包json数据回传web app
* **构建 response json包**
    * response包的格式定义如下：
        ```
        //echo result JSON格式：
            { "rc: 0/1, 
            "errCode: "error msg txt",
            "dat:{"key1":"xxValue"}
            }
        ```
    * 利用cJSON库的API打包
        ```
        #define JSON_DAT "dat"
        #define JSON_ERRCODE "errCode"
        #define JSON_RC "rc"
        #define KEY_NAME "name"
        #define KEY_PWD "pwd"
        ...
        cJSON* _root = cJSON_CreateObject(); // create the root
        cJSON* _next = cJSON_CreateObject();
        cJSON_AddItemToObject(_root, JSON_DAT, _next); //create the node. "dat"
        // write the echo result
        // 1. fill the "dat".
        cJSON_AddItemToObject(_next, KEY_NAME, cJSON_CreateString("demo value"));
        cJSON_AddItemToObject(_next, KEY_PWD, cJSON_CreateString("demo pwd"));
        // 2. fill the "rc"
        int rc = 0; // success rc
        cJSON_AddItemToObject(_root, JSON_RC, cJSON_CreateNumber(rc));
        // 3. fill the "errCode"
        strcat(errCode, "no error!");
        cJSON_AddItemToObject(_root, JSON_ERRCODE, cJSON_CreateString(errCode));
        printf("Log[ajax-ret] : [%s]\n", cJSON_Print(_root));

        ```
* **打包到 http 消息中回传**   
此处利用goAction的API函数完成打包http并回传。
    ```
        ...
        printf("Log[ajax-ret] : [%s]\n", cJSON_Print(_root));
        // 4. fill the goAction webs return.
        websSetStatus(wp, 200);
        websWriteHeaders(wp, -1, 0);
        websWriteEndHeaders(wp);
        websWrite(wp, "%s", cJSON_Print(_root));
        websFlush(wp, 0);
        websDone(wp);
    ```
* **完整处理代码**
    ```
    //-- define the json dat, key name.
    #define KEY_NAME "name"
    #define KEY_PWD "pwd"
    int GET_NET_CFG_func(cJSON* json_node, Webs *wp){
        cJSON* _root = cJSON_CreateObject(); // create the root
        cJSON* _next = cJSON_CreateObject();
        cJSON_AddItemToObject(_root, JSON_DAT, _next); //create the node. "dat"
        int rc = 0;
        char errCode[100] = "";
        char* value;
        // write the echo result
        // 1. fill the "dat".
        cJSON_AddItemToObject(_next, KEY_NAME, cJSON_CreateString("demo value"));
        cJSON_AddItemToObject(_next, KEY_PWD, cJSON_CreateString("demo pwd"));
        cJSON_AddItemToObject(_next, JSON_COMMAND, cJSON_CreateString(_json_node_value));
        // 2. fill the "rc"
        rc = 0; // success rc
        cJSON_AddItemToObject(_root, JSON_RC, cJSON_CreateNumber(rc));
        // 3. fill the "errCode"
        strcat(errCode, "no error!");
        cJSON_AddItemToObject(_root, JSON_ERRCODE, cJSON_CreateString(errCode));
        printf("Log[ajax-ret] : [%s]\n", cJSON_Print(_root));

        // 4. fill the goAction webs return.
        websSetStatus(wp, 200);
        websWriteHeaders(wp, -1, 0);
        websWriteEndHeaders(wp);
        websWrite(wp, "%s", cJSON_Print(_root));
        websFlush(wp, 0);
        websDone(wp);
    }
    ```
## 4.定制web app内容   
web app定制主要在demo.js中完成，有以下要点。
### 4.1. 格式化json传输格式   
需要打包json数据为json字符串形式以方便http传输。
```
    var str = {
        "command":"getNetworkCfgInfor"
    }
    parameters = JSON.stringify(str);
```
### 4.2. 定义正确的ajax接收格式   
需要定义为`dataType: 'json'`。   
在调试时如果出现问题，可以尝试将其改为`dataType: 'text'`，以便查看返回的具体内容。
### 4.3. 定义正确的action处理url地址   
此处需要与您在`main()`中注册的地址完全一致，ajax包才能被正确的路由到goAction注册函数处理。例如我们样例代码中的 ***yutWebsAgentDemoEntry***
```
    //yutWebsAgentDemo
    //1. regist the yutWebsAgentDemoEntry in web url
    //2. define the function for this entry
    websDefineAction("yutWebsAgentDemoEntry", actionWebsAgentDemoEntry);
```
### 4.4. 完整的ajax处理函数样例
```
function getNetworkCfgInfor(){
    var str = {
        "command":"getNetworkCfgInfor"
    }
    parameters = JSON.stringify(str);
    $.ajax({
        type:"POST",
        url: "/action/yutWebsAgentDemoEntry",
        data: parameters,
        contentType: 'application/json',
        dataType: 'json',//'text'
        success: function(res){
            var data = res;
            if(0 == data.rc){
                let textDiv = 'SUCCESS!!<br>'+' DemoCommand:'+ data.dat.command+'<br> DemoName:'+ data.dat.name+'<br> DemoPwd:'+data.dat.pwd+'<br>';
                console.log('getNetworkCfgInfor, succ.=>'+textDiv);
                $("#myDemoText").append(textDiv);
            }
            else{
                console.log('data.errCode::'+data.errCode);
            }
        },
        error: function (errorThrown) { 
            console.log('ajax error');
            console.log(errorThrown);
        }
    });
}
```
