import com.cycling74.max.*;
import com.cycling74.jitter.*;

/**
 * @author bbn
 *
 * stripes a 2D char matrix using setcell
 */
public class j51matrixstriperA extends MaxObject {
	
	JitterMatrix jm = new JitterMatrix();
	int frgb[] = new int[] {255, 255, 255, 255};
	int on = 2, off = 1;
	
	j51matrixstriperA()
	{
		declareAttribute("frgb");
		declareAttribute("on");
		declareAttribute("off");
	}

	//note that this method assumes a 2D char matrix!
	public void jit_matrix(String s)
	{
		jm.frommatrix(s);
		int dim[] = jm.getDim();
		int count = 0;
		boolean notoff = true;
		for (int i=0;i<dim[1];i++)
			for(int j=0;j<dim[0];j++)
			{
				if (notoff)
					jm.setcell2d(j, i, frgb);
				if ((notoff &&(++count > on))
						||(!notoff&&(++count > off)))
				{
					count = 0;
					notoff = !notoff;
				}
			}
		outlet(0, "jit_matrix", jm.getName());
	}
}
