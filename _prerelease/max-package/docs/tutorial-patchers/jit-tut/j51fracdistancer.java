import com.cycling74.max.*;
import com.cycling74.jitter.*;
import java.util.*;

/**
 * @author bbn
 *
 */
public class j51fracdistancer extends MaxObject{

	JitterMatrix ctlmatrix = 
		new JitterMatrix(1, "float32", 8);
	float ctldata[] = new float[8];
	int offset[] = new int[] {0};
	float frac = 0.5f;
	float noise = 0.5f;
	Random r = new Random();
	
	j51fracdistancer() {
		declareAttribute("frac");
		declareAttribute("noise");
	}
	
	//new x,y input
	public void list(int args[])
	{
		if (args.length != 2) return;
		float x = (float)args[0];
		float y = (float)args[1];
		for (int i=0;i<4;i++)
		{
			ctldata[i*2]   += (x-ctldata[i*2])   * frac + ((float)r.nextGaussian()*noise);
			ctldata[i*2+1] += (y-ctldata[i*2+1]) * frac + ((float)r.nextGaussian()*noise);
		}
		ctlmatrix.copyArrayToVector(0,offset, ctldata, 8, 0);
		outlet(0, "jit_matrix", ctlmatrix.getName());
	}
	
	public void jit_matrix(String mname)
	{
		JitterMatrix jm = new JitterMatrix(mname);
		if (jm.getDim()[0] != 8) return;
		if (jm.getPlanecount() != 1) return;
		if (!jm.getType().equals("float32")) return;
		
		ctlmatrix.frommatrix(mname);
		ctlmatrix.copyVectorToArray(0, offset, ctldata, 8, 0);
	}
}
