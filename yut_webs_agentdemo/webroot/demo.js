
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
            // console.log(res);
            // var data = JSON.parse(res);
            var data = res;
            console.log(data);
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