
function getCfgInfor(){
    var str = {
        "command":"getCfgInfor"
    }
    parameters = JSON.stringify(str);
    $.ajax({
        type:"POST",
        url: "/action/getCfgInfor",
        data: parameters,
        contentType: 'application/json',
        dataType: 'json',//'text'
        success: function(res){
            /*
            { "rc":0/1, "errCode": error msg tx,
            "dat": {
                "command":"xx", //被响应的命令
                "cur_v":"xx", //电压值
                "cur_a":"xx"}  //电流值
                }
            } */
            // console.log(res);
            // var data = JSON.parse(res);
            var data = res;
            console.log(data);
            if(0 == data.rc){
                let textDiv = 'SUCCESS!!'+' Command:'+ data.dat.command+'<> 电压:'+ data.dat.cur_v+'<> 电流:'+data.dat.cur_a;
                console.log('getCfgInfor, succ.=>'+textDiv);
                $("input[name=cur_v]").val(data.dat.cur_v);
                $("input[name=cur_a]").val(data.dat.cur_a);
                $("#myText").text(textDiv);
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

function setCfgInfor(){
    var str = {
        "command":"setCfgInfor",
        "dat": {
            "cur_v":"12", //电压值
            "cur_a":"5"}  //电流值
            }
    parameters = JSON.stringify(str);
    $.ajax({
        type:"POST",
        url: "/action/setCfgInfor",
        data: parameters,
        contentType: 'application/json',
        dataType: 'json',//'text'
        success: function(res){
            /*
            { "rc":0/1, "errCode": error msg tx,
            } 
            */
            // console.log(res);
            // var data = JSON.parse(res);
            var data = res;
            console.log(data);
            if(0 == data.rc){
                let textDiv = 'SUCCESS to set the cfg into device!!';
                console.log('setCfgInfor, succ.=>'+textDiv);
                $("#myText").text(textDiv);
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