import com.cycling74.max.*;
import com.cycling74.jitter.*;

/**
 * @author bbn
 *
 * stripes a 2D char matrix using copyVectorToArray and copyArrayToVector
 */
public class j51matrixstriperB extends MaxObject {
	
	JitterMatrix jm = new JitterMatrix();
	int frgb[] = new int[] {255, 255, 255, 255};
	int on = 2, off = 1;
	
	j51matrixstriperB()
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
		int planecount = jm.getPlanecount();
		int offset[] = new int[]{0,0};
		boolean notoff = true;
		int row[] = new int[dim[0]*planecount];
		
		for (int i=0;i<dim[1];i++)
		{
			offset[1] = i;
			jm.copyVectorToArray(0, offset, row, dim[0]*planecount, 0);
			for(int j=0;j<dim[0];j++)
			{
				if (notoff)
				{
					for (int k=0;k<planecount;k++)
						row[j*planecount+k] = frgb[k];
				}
				if ((notoff &&(++count > on))
						||(!notoff&&(++count > off)))
				{
					count = 0;
					notoff = !notoff;
				}
			}
			jm.copyArrayToVector(0, offset, row, dim[0]*planecount, 0);
		}
		outlet(0, "jit_matrix", jm.getName());
	}
}
