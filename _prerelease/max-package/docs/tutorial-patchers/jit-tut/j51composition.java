import com.cycling74.max.*;
import com.cycling74.jitter.*;

/**
 * @author bbn
 *
 */
public class j51composition extends MaxObject {
	JitterMatrix jm = new JitterMatrix();
	JitterMatrix temp = new JitterMatrix();
	JitterObject brcosa;
	JitterObject sobel;
	boolean brcosafirst = false; 
	
	j51composition() {
		declareAttribute("brcosafirst");
		brcosa = new JitterObject("jit.brcosa");
		brcosa.setAttr("brightness", 2.0f);
		sobel = new JitterObject("jit.sobel");
		sobel.setAttr("thresh", 0.5f);
	}
	
	public void jit_matrix(String mname)
	{
		jm.frommatrix(mname);
		//temp.frommatrix(jm);
		temp.setinfo(jm);
		if (brcosafirst)
		{
			brcosa.matrixcalc(jm, temp);
			sobel.matrixcalc(temp, jm);
		}
		else
		{
			sobel.matrixcalc(jm, temp);
			brcosa.matrixcalc(temp, jm);
		}
		outlet(0, "jit_matrix", jm.getName());
	}
	
	public void notifyDeleted()
	{
		brcosa.freePeer();
		sobel.freePeer();
	}
}
