inlets = 1;
outlets = 1;
//sketch.ortho3d(); //like default3d but uses orthographic projection
sketch.default2d();
//sketch.glenable("blend");
sketch.fsaa=1; // antialiasing
sketch.glenable("blend");
sketch.gldisable("depth_test"); //transparence !
var backgroundColor = [1,1,1];
//var vfrgb = [0,0.2,0.8];
var vfrgb = [1,0,0];
var virtualSourcePos = new Array(1); // sources
virtualSourcePos[0] = new Object();
virtualSourcePos[0].x = 0;
virtualSourcePos[0].y = 0.75;
virtualSourcePos[0].color = randomShinnyColor();

var activeSource = new Object();
activeSource.x = virtualSourcePos[0].x;
activeSource.y = virtualSourcePos[0].y;
activeSource.index = 0;

var gridOffset = 1;

var params = {
    displayCartVectors : 1,
    displayAngle : 1,
    displayGrid : 1,
    gridColor : [0,0,0,0.8],
    bgColor : [1,1,1],
    hpColor : [0.15,0.15,0.15],
    headColor : [0.15,0.15,0.15]
}

var zoomFactor = 0.50;
var numberOfSpeaker = 16;
var speakerSpacement = 0.20;
var speakerToHeadDistance = 1.5;
var arrayType = 1; // "wfs" or "ambisonic"
var currentGrabedItemIndex = -1;


with(sketch)
{
    function getParams() {
        // process arguments
        if (jsarguments.length>1) 
            backgroundColor[0] = jsarguments[1]/255.;
        if (jsarguments.length>2)
            backgroundColor[1] = jsarguments[2]/255.;
        if (jsarguments.length>3)
            backgroundColor[2] = jsarguments[3]/255.;
    }

    function nextPow2(aValue)
    {
        pow = 2;
        while( (aValue / pow) >= 1)
        {
            pow = pow*2;
        }
        return (pow)/4;
    }

    function drawCartVectorsCopy() // vecteurs sur la source
    {
        gllinewidth(1);
        glcolor([1,0,0]);
        moveto(0,0);
        lineto(0.5*zoomFactor,0);
        lineto(0.44*zoomFactor,0.03*zoomFactor);
        moveto(0.5*zoomFactor,0);
        lineto(0.44*zoomFactor,-0.03*zoomFactor);
        moveto(0.4*zoomFactor, 0.05*zoomFactor);
        fontsize(10*zoomFactor);
        text("x");
        
        glcolor([0,1,0]);
        moveto(0,0);
        lineto(0,0.5*zoomFactor);
        lineto(0.03*zoomFactor,0.44*zoomFactor);
        moveto(0,0.5*zoomFactor);
        lineto(-0.03*zoomFactor,0.44*zoomFactor);
        moveto(-0.05*zoomFactor, 0.4*zoomFactor);
        fontsize(10*zoomFactor);
        text("y");
        fontsize(9);
    }

    function drawCartVectors() // vecteurs sur la source
    {
        //var flechePoint = gridOffset*0.005;
        var flechePoint = 1;
        gllinewidth(1);
        glcolor([1,0,0]);
        moveto(0,0);
        lineto(1,0);
        //moveto(0,0);
        //lineto(0.5*zoomFactor,0);

        moveto(flechePoint*zoomFactor,0);
        lineto((flechePoint-0.06)*zoomFactor,0.03*zoomFactor);
        moveto(flechePoint*zoomFactor,0);
        lineto((flechePoint-0.06)*zoomFactor,-0.03*zoomFactor);
        moveto((flechePoint-0.1)*zoomFactor, 0.05*zoomFactor);
        fontsize(10*zoomFactor);
        text("x");
        
        glcolor([0,1,0]);
        moveto(0,0);
        lineto(0,1);
        moveto(0,flechePoint*zoomFactor);

        lineto(0.03*zoomFactor,(flechePoint-0.06)*zoomFactor);
        moveto(0,flechePoint*zoomFactor);
        lineto(-0.03*zoomFactor,(flechePoint-0.06)*zoomFactor);
        moveto(-0.05*zoomFactor, (flechePoint-0.1)*zoomFactor);
        fontsize(10*zoomFactor);
        text("y");
        fontsize(9);
    }
    
    function drawVirtualSource() //source à spatialiser
    {
        for (var speakerIndex = 0; speakerIndex < virtualSourcePos.length; speakerIndex++) 
        {
            var orientation = getAngle(speakerIndex);
            //var orientation =  Math.atan(virtualSourcePos[speakerIndex].x/ virtualSourcePos[speakerIndex].y);
            var module = Math.sqrt( virtualSourcePos[speakerIndex].x*virtualSourcePos[speakerIndex].x + virtualSourcePos[speakerIndex].y*virtualSourcePos[speakerIndex].y);
            //orientation = -orientation*180/Math.PI;
            //if (virtualSourcePos[speakerIndex].y <0) {orientation = orientation + 180;}
            if (zoomFactor <= 0.5) {var size = 0.25;}
            else {var size = 0.5*zoomFactor;}
            drawSource(size, orientation, 0, (module-0.05)*zoomFactor, virtualSourcePos[speakerIndex].color, speakerIndex);
        }
    }

    function getAngle(speakerIndex){
        var orientation =  Math.atan(virtualSourcePos[speakerIndex].x/ virtualSourcePos[speakerIndex].y);
        orientation = -orientation*180/Math.PI;
        if (virtualSourcePos[speakerIndex].y <0) {orientation = orientation + 180;}
        return orientation;
    }
    
    function drawGridCopy(spacement)
    {
        //var screenSpacement = spacement*zoomFactor;
        var offsetIndex = Math.ceil((1/zoomFactor)/spacement);
        var offsetPos = spacement * offsetIndex*zoomFactor;
        var offsetDistance;
        var test = nextPow2(offsetIndex);
        glcolor([0.5,0.5,0.5]);
        gllinewidth(0.1);
        while(offsetPos > -1)
        {    
            offsetPos = spacement * offsetIndex*zoomFactor;
            if (offsetIndex%test == 0)
            {
                glcolor([0.5,0.5,0.5]);
                moveto(-1, offsetPos);
                lineto(1,offsetPos);
                moveto(offsetPos, -1);
                lineto(offsetPos,1);

                if (offsetIndex >= 0)
                {
                    offsetDistance = offsetIndex * spacement;
                    moveto(0.93,offsetPos+0.007);
                    //glcolor([1,1,1,0.2]);
                    //roundedplane(1,0.065,0.02);
                    font("Sans Serif");
                    fontsize(8);
                    textalign("center","");
                    glcolor([0,0,0]);
                    text( ( offsetDistance.toFixed(2) )+" m");
                }
            }
            offsetIndex--;
        }
    }

    function drawGrid(spacement)
    {
        var offsetIndex = Math.ceil((1/zoomFactor));
        var offsetPos = offsetIndex*zoomFactor;
        var offsetDistance;
        var test = nextPow2(offsetIndex);
        gridOffset = test;
        //post(gridOffset,'\n');
        glcolor([0.5,0.5,0.5]);
        gllinewidth(0.1);
        while(offsetPos > -1)
        {    
            offsetPos = offsetIndex*zoomFactor;
            if (offsetIndex%test == 0)
            {
                glcolor([0.5,0.5,0.5]);
                moveto(-1, offsetPos);
                lineto(1,offsetPos);
                moveto(offsetPos, -1);
                lineto(offsetPos,1);

                if (offsetIndex >= 0)
                {
                    offsetDistance = offsetIndex;
                    moveto(0.93,offsetPos+0.007);
                    //glcolor([1,1,1,0.2]);
                    //roundedplane(1,0.065,0.02);
                    font("Sans Serif");
                    fontsize(8);
                    textalign("center","");
                    glcolor([0,0,0]);
                    text( ( offsetDistance.toFixed(2) )+" m");
                }
            }
            offsetIndex--;
        }
    }
    
    function drawWfsSpeakers()
    {
        var speakerPositionOffset;
        if (numberOfSpeaker % 2 == 0)
        speakerPositionOffset = -(numberOfSpeaker/2 - 0.5)*speakerSpacement;
        else
        speakerPositionOffset = -(Math.ceil(numberOfSpeaker/2) - 1)*speakerSpacement;
        
        for (var speakerIndex = 0; speakerIndex < numberOfSpeaker; speakerIndex++)
        {
            if (zoomFactor <= 0.5) {var size = 0.25;}
            else {var size = 0.5*zoomFactor;}
            drawSpeaker(size, 0, speakerPositionOffset* zoomFactor , speakerToHeadDistance* zoomFactor, params.hpColor);
            speakerPositionOffset += speakerSpacement;
        }
    }
    
    function drawAmbisonicsSpeakers()
    {
        var speakersStepAngle = 360 /numberOfSpeaker;
        
        for (var speakerIndex = 0; speakerIndex < numberOfSpeaker; speakerIndex++){
            if (zoomFactor <= 0.5) {var size = 0.25;}
            else {var size = 0.5*zoomFactor;}
            drawSpeaker(size, speakerIndex*speakersStepAngle, 0 , speakerToHeadDistance* zoomFactor, params.hpColor);
        }
    }
    
    function drawSpeakers()
    {
        if (arrayType == 0)
        drawWfsSpeakers();
        else
        drawAmbisonicsSpeakers();
        
    }
    
    function drawSpeaker(size, angle, xPos, yPos, color)
    {
        if (color == undefined) glcolor([0,0,0]);
        //var alpha = [0.5];
        else glcolor(color);
        glpushmatrix();
        glrotate(angle,0,0,1);
        gltranslate(xPos,yPos,0);
        glscale(size*0.8, size, size);
        glbegin("quad_strip");
        glvertex(0.2,0);
        glvertex(-0.2,0);
        glvertex(0.1,0.1);
        glvertex(-0.1,0.1);
        glvertex(0.1,0.2);
        glvertex(-0.1,0.2);
        glend();
        glpopmatrix();
    }

    function drawSourceCopy(size, angle, xPos, yPos, color, sourceIndex)
    {
        if (color == undefined) color = [0,0,0];
        //glcolor(color);
        gllinewidth(1);
        glpushmatrix();
        glrotate(angle,0,0,1);
        gltranslate(xPos,yPos-size*0.001,0);
        glscale(size, size, size);
        glbegin("quad_strip");
        glcolor([0,0,0]);
        circle(size*0.4, 0, 360);
        glcolor(color);
        framecircle(size, 0, 360);
        glcolor(color);
        framecircle(size*0.7, 0, 360);
        glcolor([color[0],color[1],color[2],0.4]);
        circle(size*1.1, 0, 360);
        //text
        glcolor([1,1,1]);
        fontsize(25*size);
        textalign("center","center");
        text(sourceIndex.toString());
        //--
        glend();
        glpopmatrix();
    }

    function drawSource(size, angle, xPos, yPos, color, sourceIndex)
    {
        var sourceX = virtualSourcePos[sourceIndex].x*zoomFactor;
        var sourceY = virtualSourcePos[sourceIndex].y*zoomFactor;
        size*=0.4;
        if (color == undefined) color = [0,0,0];
        gllinewidth(1);
        moveto(sourceX, sourceY);

        glcolor(color);
        framecircle(size, 0, 360);
        glcolor(color);
        framecircle(size*0.7, 0, 360);

        glcolor([color[0],color[1],color[2],0.4]);
        circle(size*1.1, 0, 360);

        glcolor([0,0,0]);
        circle(size*0.4, 0, 360);

        //text
        glcolor([1,1,1]);
        fontsize(100*size);
        textalign("center","center");
        text(sourceIndex.toString());
        //--
    }

    function drawAngle(sourceIndex){
        //post(xPos, yPos, angle, sourceIndex, "\n");
        var angle = getAngle(sourceIndex);
        var sourceX = virtualSourcePos[sourceIndex].x*zoomFactor;
        var sourceY = virtualSourcePos[sourceIndex].y*zoomFactor;
        //post(sourceIndex, sourceX, sourceY, angle, "\n");
        myAngle = (angle*-1);
        if (myAngle < -180) {myAngle+=360};
        glcolor([0,0,0,0.5]);
        gllinewidth(1);
        moveto(virtualSourcePos[sourceIndex].x*zoomFactor, virtualSourcePos[sourceIndex].y*zoomFactor);
        lineto(0,0);
        //lineto(0,0.2);
        //moveto(0,0);
        glcolor([0,0,0,0.1]);

        if (myAngle<0) {
            framecircle(0.13, 90, angle+90);
            circle(0.13, 90, angle+90);
        }
        else {
            framecircle(0.13, 90-myAngle, 90); 
            circle(0.13, 90-myAngle, 90); 
        };

        //text
        moveto(0,0.3);
        glcolor([0,0,0]);
        fontsize(15);
        textalign("center","center");
        text(myAngle.toFixed(1)+'°');
        //--
    }
    
    function drawHeadCopy()
    {
        var size = zoomFactor;
        if (size <= 0.3) {var size = 0.3;}
        // border :
        moveto(0,0);
        gllinewidth(2);
        glcolor(params.bgColor);

        moveto(0,0);
        glcolor(params.headColor);
        circle(0.1 * size, 0, 360);
        moveto(-0.08*size,0.)
        circle(0.05 * size, 0, 360);
        moveto(0.08*size,0.)
        circle(0.05 * size, 0, 360);
        moveto(0,0.03*size);
        ellipse (0.03*size, 0.1*size, 0, 360);
        moveto(0,0);
        glcolor([1,1,1,0.7]);
        framecircle(0.1 * size, 0, 360);
    }

    function drawHead()
    {
        var size = zoomFactor;
        if (size <= 0.3) {var size = 0.3;}
        // border :
        glcolor(params.headColor);
        //gllinewidth(2);
        moveto(0,0);
        circle(0.1 * size, 0, 360);

        // moveto(-0.08*size,0.);
        // circle(0.05 * size, 0, 360);
        // moveto(0.08*size,0.);
        // circle(0.05 * size, 0, 360);

        moveto(-0.115*size,0.);
        ellipse (0.01*size, 0.02*size, 0, 360); //oreille G

        moveto(0.115*size,0.);
        ellipse (0.01*size, 0.02*size, 0, 360); //oreille D

        moveto(0,0.03*size);
        ellipse (0.03*size, 0.1*size, 0, 360); //nez

        //moveto(0,0);
        //glcolor([1,1,1,0.7]);
        //framecircle(0.1 * size, 0, 360);
    }

    function calculateReproZonePoint(speakerId) // id is "first" or "last"
    {
        var speaker = new Object();
        if (speakerId == "first")
            speaker.x = -(numberOfSpeaker/2 - 0.5)*speakerSpacement;
        else if (speakerId == "last")
            speaker.x = (numberOfSpeaker/2 - 0.5)*speakerSpacement;
  
        speaker.y = speakerToHeadDistance;

        var vector = new Object();
        vector.x = speaker.x - activeSource.x;
        vector.y = speaker.y - activeSource.y;
        var vectorLength = Math.sqrt(vector.x*vector.x + vector.y*vector.y);
        vector.x /= vectorLength;
        vector.y /=  vectorLength;
        vector.x *= 5000;
        vector.y *=  5000;
        if (speaker.y  > activeSource.y)
        {
            vector.x *= -1;
            vector.y *=  -1;
        }
        vector.x += activeSource.x;
        vector.y +=  activeSource.y;

        return vector;

    }
    function drawReproZone()
    {
        if (arrayType == 0)
        {
            var firstPoint = calculateReproZonePoint('first');
            var secPoint = calculateReproZonePoint('last');
            glcolor([15/255,78/255, 99/255, 0.6]);


            if (speakerToHeadDistance  > activeSource.y)
            {
            tri(activeSource.x*zoomFactor, activeSource.y*zoomFactor, 0 , secPoint.x*zoomFactor ,secPoint.y*zoomFactor,0, firstPoint.x*zoomFactor ,firstPoint.y*zoomFactor, 0);
            }
            else
            {
            tri(activeSource.x*zoomFactor, activeSource.y*zoomFactor, 0 , firstPoint.x*zoomFactor ,firstPoint.y*zoomFactor,0, secPoint.x*zoomFactor ,secPoint.y*zoomFactor, 0)
            }
            //moveto(virtualSourcePos[0].x*zoomFactor ,virtualSourcePos[0].y * zoomFactor);
            //lineto(firstPoint.x*zoomFactor ,firstPoint.y*zoomFactor);
            //moveto(virtualSourcePos[0].x*zoomFactor ,virtualSourcePos[0].y * zoomFactor);
            //lineto(secPoint.x*zoomFactor ,secPoint.y*zoomFactor);
        }
    }
}
draw();




function draw()
{
    var str;
    
    with (sketch) {
        glclear();
        getParams();
        if (params.displayGrid) {
            drawGrid(0.01); // c'était à 0.25 mais provoque un bug dans la grid !
        };
        drawReproZone();
        if (params.displayCartVectors) {
            drawCartVectors();
        };
        drawSpeakers();
        if (activeSource.index != undefined) {
            drawAngle(activeSource.index);
        };
        drawHead();
        drawVirtualSource();
    }
}


function onclick(x,y,button)
{
    var tmpCoordinates = toVirtualWorldCoordinate(x,y);
    var nearestSpeaker = getNearestSpeaker(tmpCoordinates[0],tmpCoordinates[1]);

    if (button == 1 && nearestSpeaker.distance < 0.1)
    {
        currentGrabedItemIndex = nearestSpeaker.index;
        activeSource.x  = virtualSourcePos[nearestSpeaker.index].x;
        activeSource.y  = virtualSourcePos[nearestSpeaker.index].y;   
        activeSource.index = nearestSpeaker.index;
        bang();
    }
    else
    {
    }
    //bang();
}
onclick.local = 1; //private

function ondblclick(x,y)
{
    var tmpCoordinates = toVirtualWorldCoordinate(x,y);
    var nearestSpeaker = getNearestSpeaker(tmpCoordinates[0],tmpCoordinates[1]);

    //post('fefe');
    //post();
    if (nearestSpeaker.distance > 0.1)
    {
        var lastObject = new Object();
        lastObject.color = randomShinnyColor();
        virtualSourcePos.push(lastObject);
        var tmpCoordinates = toVirtualWorldCoordinate(x,y);
        updateSpeakerPosition(tmpCoordinates[0],tmpCoordinates[1],virtualSourcePos.length-1);
    }    
    else if (virtualSourcePos.length > 1)
    {
        virtualSourcePos.splice(nearestSpeaker.index ,1);
        if (nearestSpeaker.index  == activeSource.index)
        {
            nearestSpeaker.index = 0;
            activeSource.x = virtualSourcePos[0].x; 
            activeSource.y = virtualSourcePos[0].y;
        }
        bang();
    }
}

function ondrag(x,y, button)
{
    var tmpCoordinates = toVirtualWorldCoordinate(x,y);
    
    if(!button)
    {
        currentGrabedItemIndex = -1;
    }
    
    if (currentGrabedItemIndex != -1)
    {
        updateSpeakerPosition(tmpCoordinates[0],tmpCoordinates[1],currentGrabedItemIndex);
    }
}

function module(x,y)
{
    return Math.sqrt(x*x + y*y);
}

function getNearestSpeaker(x,y)
{
    var nearestSpeaker = new Object();
    nearestSpeaker.distance = 1000000;
    var currentDistance;
    var nearestSpeakerIndex;
    
    for( var speakerIndex = 0; speakerIndex < virtualSourcePos.length ; speakerIndex++)
    {
        currentDistance = module(x-virtualSourcePos[speakerIndex].x, y-virtualSourcePos[speakerIndex].y)
        if ( currentDistance < nearestSpeaker.distance )
        {
            nearestSpeaker.distance = currentDistance;
            nearestSpeaker.index = speakerIndex;
        }
    }
    
    return nearestSpeaker;
}

function updateSpeakerPosition(x, y , speakerIndex)
{
    virtualSourcePos[speakerIndex].x = x;
    virtualSourcePos[speakerIndex].y = y;    
    activeSource.x = x;
    activeSource.y = y;
    activeSource.index = speakerIndex;
    notifyclients();
    bang();
}

function randomShinnyColor()
{
    // var totalColor = 4;
    // var color = new Array(2);
    // color[0] = Math.random()*totalColor;
    // color[1] = totalColor - color[0];

    // var supressedColorIndex = Math.floor(Math.random()*3);
    // color.splice(supressedColorIndex, 0 , 0);
    // color[3] = 0.6;
    // return color;
    var color = new Array();
    color[0] = Math.random();
    color[1] = Math.random()*0.8;
    color[2] = Math.random()*0.5;
    color[3] = 0.5;
    return color;
}

function toVirtualWorldCoordinate(x,y)
{
    var width = box.rect[2] - box.rect[0];
    var height = box.rect[3] - box.rect[1];
    
    if (x<0)
        x = 0;
    else if (x>width)
        x = width;
    
    if (y<0)
        y = 0;
    else if (y>height)
        y = height;
    
    var tmpCoordinates = sketch.screentoworld(x,y);
    tmpCoordinates[0] = tmpCoordinates[0]/zoomFactor;
    tmpCoordinates[1] = tmpCoordinates[1]/zoomFactor;
    return tmpCoordinates;
}

/* ------ MSG EXTERNS ------ */

function zoom(v){
    if (v>1) {v = 1};
    if (v< 0.1) {v = 0.1};
    zoomFactor = v;
    if(zoomFactor == 1 || zoomFactor == 0.1) {return;};
    bang();
}

function nb_hp(v){
    if (v <= 1) { v = 1 }
    numberOfSpeaker = v;
    bang();
}

function shape(v){
    if (v <= 0) { v = 0 }
    else if (v >= 1) { v = 1 };
    arrayType = v;
    bang();
}

function delta(v){
    if (v <= 0) { v = 0 }
    //else if (v >= 1) { v = 1 };
    speakerSpacement = v;
    bang();
}

function distance(v){
    if (v <= 0) { v = 0 }
    speakerToHeadDistance = v;
    bang();
}

function display_angle(v){
    if (v == 1) { params.displayAngle = 1; }
    else {params.displayAngle = 0;};
    bang();
}
function display_grid(v){
    if (v == 1) { params.displayGrid = 1; }
    else {params.displayGrid = 0;};
    bang();
}
function display_cartvectors(v){
    if (v == 1) { params.displayCartVectors = 1; }
    else {params.displayCartVectors = 0;};
    bang();
}

/*
function msg_float(v)
{
    var i = inlet;
    if (i==0)
        zoomFactor = v
    else if (i==1)
        numberOfSpeaker = v;
    else if (i==2)
        speakerSpacement = v;
    else if (i==3)
        arrayType = v;
    else if (i == 4)
        speakerToHeadDistance = v;
    else if (i == 5)
    {
        virtualSourcePos[0].x = v;
        activeSource.x = virtualSourcePos[0].x;
        activeSource.y = virtualSourcePos[0].y;
    }
    else if (i == 6)
    {
        virtualSourcePos[0].y = v;
        activeSource.x = virtualSourcePos[0].x;
        activeSource.y = virtualSourcePos[0].y;
    }
    bang();
}
*/

function list(v){
    // post("list (", arguments.length, "elements) :\n");
    // post("arg 1 : ", arguments[0]);
    // post();

    if ( (isNaN(arguments[0])) || (arguments[0] < 0) || (arguments[0] > virtualSourcePos.length-1)) {error("bad list format\n"); return;};
    if ( isNaN(arguments[1]) ) {error("bad list format\n"); return;};
    if ( isNaN(arguments[2]) ) {error("bad list format\n"); return;};

    var sourceIndex = arguments[0];
    virtualSourcePos[sourceIndex].x = arguments[1];
    virtualSourcePos[sourceIndex].y = arguments[2];
    activeSource.x = virtualSourcePos[sourceIndex].x;
    activeSource.y = virtualSourcePos[sourceIndex].y;
    bang();
}

function assistance(){
    //inlets :
    setinletassist(0, "list : [source, sourceX, sourceY], msg : [zoom (0.1->1.), nb_hp (int), shape(0/1), delta(float), distance(float)].");
    //outlets :
    setoutletassist(0, "list output : (source, sourceX, sourceY)");
}
assistance();
assistance.local = 1;

function bang()
{
    draw();
    refresh();
    for (var speakerIndex = 0; speakerIndex < virtualSourcePos.length; speakerIndex++){
        outlet(0, speakerIndex, virtualSourcePos[speakerIndex].x, virtualSourcePos[speakerIndex].y);
    }
}

function forcesize(w,h)
{
    if (w!=h) {
        h = w;
        box.size(w,h);
    }
}
forcesize.local = 1; //private

function onresize(w,h)
{
    forcesize(w,h);
    draw();
    refresh();
}
onresize.local = 1; //private

