inlets = 10;
outlets = 2;
sketch.ortho3d(); //like default3d but uses orthographic projection
var backgroundColor = [0,0,0];
var vfrgb = [0,0.2,0.8];
var zoomFactor = 0.8;

var numberOfAngularStep= 200;
var angularSteps   = new Array(numberOfAngularStep);
var circularValues = new Array(numberOfAngularStep);
var contribValues = new Array(numberOfAngularStep);
var xCircleVector = new Array(numberOfAngularStep);
var yCircleVector = new Array(numberOfAngularStep);
var harmonicsValue = new Array(numberOfHarmonics);
var harmonicsBasis = new Array(numberOfHarmonics);
var activeHarmonic = 0;
var biggestContrib = 1;
var orderNumber =  jsarguments[1];
var numberOfHarmonics= orderNumber*2 +1;

for(var i = 0; i < numberOfHarmonics; i++)
{
    harmonicsValue[i] = 0;
}

for (var i = 0; i < numberOfAngularStep; i++)
{
    angularSteps[i] = (2*Math.PI/numberOfAngularStep)*i;
}
for (var i = 0; i < numberOfAngularStep; i++)
{    
    xCircleVector[i] = Math.cos(angularSteps[i]);
    yCircleVector[i] = Math.sin(angularSteps[i]);
}
 
for (var j = -orderNumber; j <= orderNumber; j++)
{

    harmonicsBasis[j+orderNumber] = new Array(numberOfAngularStep);
    for(var i = 0; i < numberOfAngularStep; i++)
    {
       // post((j+orderNumber) + "\n")
        if(j < 0)
          harmonicsBasis[j+orderNumber][i] = Math.sin(Math.abs(j)*angularSteps[i]);
        else if (j == 0)
            harmonicsBasis[j+orderNumber][i] = Math.cos(Math.abs(j)*angularSteps[i])/2;
        else 
            harmonicsBasis[j+orderNumber][i] = Math.cos(Math.abs(j)*angularSteps[i]);
    }
}

with(sketch)
{
    function drawPolarRepresentation()
    {
        moveto(0,0,0);
        var polarSize = zoomFactor;
        var numberOfCircleStep = 5;
        var rayStart = polarSize/numberOfCircleStep;
        glcolor([1,1,1]);
        framecircle(polarSize);
        glcolor([0.5,0.5,0.5]);
        framecircle(rayStart);
        for(var i = 1; i < numberOfCircleStep; i++)
        {
            moveto(0,0);
            framecircle(rayStart*i);
            moveto(0.01, rayStart*(i+1) - 0.05);
            text((biggestContrib*(i+1)/numberOfCircleStep).toFixed(2)+ "");
        }

        var tmpTheta = 0;
        var nbOfSteps = 12;
        var thetaStep = 2*Math.PI/nbOfSteps;
        for(var i = 0; i < nbOfSteps; i++)
        {
            tmpTheta = thetaStep * i;
            moveto(rayStart*Math.cos(tmpTheta),rayStart*Math.sin(tmpTheta),0);
            lineto(polarSize*Math.cos(tmpTheta), polarSize*Math.sin(tmpTheta), 0);
            moveto(polarSize*1.1*Math.cos(tmpTheta),polarSize*1.1*Math.sin(tmpTheta),0);
            //text((360*i/nbOfSteps) +"°");
            text(((+270+360*i/nbOfSteps)%360) +"°");
        }
    }
   
    function drawHarmonics()
    {
        var x = 0;
        var y = 0;
        var normalisationFactor = 0;
        var contrib = 0;
        biggestContrib = 1;
        for (var i = 0; i < numberOfAngularStep; i++)
        {    
            contrib = 0;

            for(var j = -orderNumber; j<= orderNumber; j++)
                contrib += harmonicsBasis[j+orderNumber][i]* harmonicsValue[j+orderNumber];

            if (Math.abs(contrib) > biggestContrib )
                biggestContrib = Math.abs(contrib);
                
            contribValues[i] = contrib;
        }

        moveto(0,0);
        normalisationFactor = zoomFactor/biggestContrib;
        for (var i = 0; i < numberOfAngularStep; i++)
        {    
            x =  xCircleVector[i] * Math.abs(contribValues[i]) * normalisationFactor;
            y =  yCircleVector[i] * Math.abs(contribValues[i]) * normalisationFactor;
            if (contribValues[i]< 0)
            {
                    if(i>1 && contribValues[i-1] >= 0)
                        lineto(0,0);
                    glcolor([1,0,0]);
            }
            else
            {
                    if(i>1 && contribValues[i-1] < 0)
                        lineto(0,0);
                    glcolor([0,0,1]);
            }
           if(i == 0)
                moveto(x,y);
            else
                lineto(x,y);
        }
        lineto(zoomFactor*Math.abs(contribValues[0])/biggestContrib);
    }
}
draw();




function draw()
{
    var str;
    
    with (sketch) {
        glclearcolor(backgroundColor);
        glclear();
        glcolor(vfrgb); 
        glcolor([1,1,1]);
        moveto([0,0,0]);
        gllinewidth (1);
        drawHarmonics()
        drawPolarRepresentation();
    }
}
function module(x,y)
{
    return Math.sqrt(x*x + y*y);
}



function list()
{
    var a = arrayfromargs(arguments);
    harmonicsValue = a;
    bang();
}

function bang()
{
    draw();
    refresh();

}

function onresize(w,h)
{
    draw();
    refresh();
}
onresize.local = 1; //private

