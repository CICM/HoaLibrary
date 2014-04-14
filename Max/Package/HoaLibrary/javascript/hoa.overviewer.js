inlets=1;
outlets=1;

var name = "pack";
var dict;
var shortDesc = "";
var longDesc = "";
/*
function init()
{
	dict = max.getrefdict(name);
	if (typeof(dict) == "object") {
		shortDesc = dict.get("digest");
		longDesc = dict.get("description");
		dict.freepeer();
	}
	
	outlet(0, "name", name);
}

init();
*/

function anything()
{
	var a = arrayfromargs(messagename, arguments);
	post("received message " + a + "\n");
	myval = a;
	name = a;
	dict = max.getrefdict(name);
	if (typeof(dict) == "object") {
		shortDesc = dict.get("digest");
		longDesc = dict.get("description");
		dict.freepeer();
	}
	
	outlet(0, "name", name);
	outlet(0, "short", shortDesc);
	outlet(0, "description", longDesc);
}