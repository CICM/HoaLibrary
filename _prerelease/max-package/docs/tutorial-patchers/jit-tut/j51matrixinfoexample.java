import com.cycling74.max.*;
import com.cycling74.jitter.*;

/**
 * @author bbn
 *
 * shows the basic transaction between the Max patcher and an
 * mxj object that wants to process a matrix of data
 */
public class j51matrixinfoexample extends MaxObject {
	
	public void jit_matrix(String s) 
	{
		JitterMatrix jm = new JitterMatrix(s);

		outlet(0,"name", jm.getName());
		outlet(0,"planecount", jm.getPlanecount());
		outlet(0,"type", jm.getType());
		outlet(0,"dim", jm.getDim());
	}
}
