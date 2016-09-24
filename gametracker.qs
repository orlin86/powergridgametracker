
function Init(p_xSkin)
{
	var xCtrl=p_xSkin.getControl();
	var xCfgData=xCtrl.getConfigData();
	var xRes=this.FindLayout("Result");
    var xTitle=this.FindLayout("MTitle");
    var items=["Deaths"];

	p_xSkin.data={
        ctrl:this,
        xRes:xRes,
        xTitle:xTitle,
        xcfg:xCfgData,
        xHandle:0,
    };
    p_xSkin.data.xRes.setText("starting");
};

function Tick(p_xSkin)
{
	var iRes=this.CallFunc("gametracker:GetValue",["blabla","blabla2"]);
    if ( iRes <0 )
        iRes="err";
	p_xSkin.data.xRes.setText(iRes);
};

