import com.cycling74.max.*;
import com.cycling74.jitter.*;

/**
 * @author bbn
 * 
 * part of Jitter tutorial 51
 * helps illustrate the difference between copying the data from an input matrix
 * versus directly writing into the input matrix
 */
public class j51whycopy extends MaxObject {
	
	JitterMatrix jm = new JitterMatrix();
	boolean copy = false;
	
	j51whycopy()
	{
		declareAttribute("copy");
	}
	
	public void jit_matrix(String inname)
	{
		//under normal circumstances
		//we would only create this matrix once
		jm = new JitterMatrix();
		if (copy)
		{
			jm.frommatrix(inname);
		}
		else //!copy
		{
			jm = new JitterMatrix(inname);
		}
		zero(jm);
		outlet(0, "jit_matrix", jm.getName());
	}
	
	//note that this method assumes the matrix is of type char
	private void zero(JitterMatrix m)
	{
		int z[] = new int[m.getPlanecount()];
		for (int i=0;i<m.getPlanecount();i++)
			z[i] = 0;
		m.setall(z);
	}
}
