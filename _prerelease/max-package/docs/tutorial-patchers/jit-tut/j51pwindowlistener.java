import com.cycling74.max.*;
import com.cycling74.jitter.*;

public class j51pwindowlistener extends MaxObject implements JitterNotifiable
{
	JitterListener listener;
	boolean verbose = false;

	j51pwindowlistener() 
	{
		declareIO(1,2);
		declareAttribute("verbose");
	}
 
	public void name(String s)
	{
		listener = new JitterListener(s,this);
	}
    
	public void notify(JitterEvent e)
	{
		//this gets the name of the listening context - in this case, the pwindow
		String subjectname = e.getSubjectName(); 
		//this gets the type of event...mouse, mouseidle, etc.
		String eventname = e.getEventName();
		//this gets the arguments of the event
		Atom args[] = e.getArgs();
		if (verbose)
		{
			outlet(1,subjectname);
			outlet(1,eventname,args);
		}
		
		if ((eventname.equals("mouse"))||(eventname.equals("mouseidle")))
		{
			int xy[] = new int[] {args[0].toInt(), args[1].toInt()};
			//output the x and y coordinates of the mouse
			outlet(0, xy);
		}
	}

   
}








