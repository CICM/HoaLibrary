/**
	@file				
	testrefgen*.c		
	Sample code for Doctor Max
	^^^ This is the file name. It is actually unused by the parser, but you can add more specifications about the file itself, should you need them
	
	@name
	testrefgen*			
	^^^ This is the name or alias of your object, as shown in the object box. Single word, no spaces.

	@realname			
	testrefgentimes			
	^^^ This is the real name of your object, ignoring aliases (as the name of the .mxo/.mxe file). Single word, no spaces.

 
	@type				
	object				
	^^^ This is the type of the element: either "object" or "abstraction". Abstractions can have documentation too!
	To document abastractons, just write a dummy .c file code, only containing the documentation commented information (and "fake" attribute declarations).


	@module				
	CoolStuff
	^^^ This is the name of your collection including this specific object

 
	@author				
	DeSelbyCorporation
	^^^ This is the name of the author of the object
 
	
	@status
	ok
	^^^ The status declaration is optional: the status is ok by default. Yet, you might want to mark the element as one of the following
	symbols: deprecated, hidden, experimental. In any of these cases, the documentation will NOT be produced.
 
	@digest				
	Output multiplied elements randomly
	^^^ This is a small sentence representing what the object do. No final period, no third person "s".
 
 
	@description		
	<o>testrefgen*</o> takes any incoming element, multiplies it for a random integer, and then
	outputs the results from a random outlet. 
	The description tag represents a more accurate description of the object.
	This description must still be rather short, since it will appear 
	in the top part of the help files.

	If you leave a blank return space, description stops!
 

	@discussion
	<o>testrefgen*</o> uses uniform random algorithms to obtain randomness.
	Discussion is usually a more technical insight on the object details, possibly involves standard
	usages of the object. 
 
 
	@tag 
	bach, bach objects, bach llll
	^^^ Add a series of tags concerning the object. Separate them with commas.


	@seealso			
	bach.read, bach.shelf, bach.reg

	^^^ List a series of other objects, patches or tutorial names which will appear in the "See also" list. Use commas to separate. 
	They can also be on more than one line, that's why we have left a blank line before this comment (to avoid confusions).
 

	@owner				
	De Selby
 	^^^ For collective projects, you can put the name of the person in charge of the object

	@ingroup examples
	^^^ You can put more tags, needed for any other purpose (e.g. doxygen). They won't appear in compiled XMLs

	This lines will not appear in the reference XML either. 
	
	IMPORTANT: there are some limits and standard usages which you should be aware of: 
	- Throughout all the code documentation, all lines may have at most 400 characters (otherwise they are trimmed).
	- Element names (attributes, methods, objects...) may have at most 150 characters.
	- All "digest" tags must lie on a single line.
	- All "description" tags may have at most 800 lines.
	- All "discussion" tags may have at most 100 lines.
	- Only ASCII characters are allowed. In order to use &, < and > you should use the XML escaped versions, 
	  respectively: &amp; for "&", &lt; for "<" and &gt; for ">".
	- The "type" tags (specifying types of arguments, inlets, etc.) is always taken as-is as string, 
		so it can be any string you wish, such as "bang/int", or "number".
	- As a good role, all "digest" tags must be short, without the ending period, and without third person's "s";
	  all "description", on the other hand, must be longer, with the final period, and written with third person's "s".
	- Three angular-brackets tags are available, and should be always used when referring to the following things:
		~ the "o" tag is reserved for object or element names: <o>uzi</o>, <o>testrefgen*</o>, and will result in clickable underlined links;   
		~ the "b" tag makes words bold, and should be reserved to syntax examples, e.g. <b>outputfrom 2 15</b>;
		~ the "m" tag should be used for method or attribute names (such as <m>maxfactor</m>, <m>bang</m>), 
			or, in combination with the "b" tag, for placeholders to mark a given syntax: <b>outputfrom <m>outlet_num</m> <m>value</m></b>.
	- In all descriptions and discussion you can use the "copy" tag, which lets you copy a portion of documentation included in a 
		common reference file. This is handy if you have multiple locations where you should repeat the same stuff: instead, just
		put the stuff in the common reference file, and use the "copy" tags.
		See below to know some specifications of the "copy" tag.
*/

#include "ext.h"			// Of course you can comment anything else normally! Just don't use any of the reserved @-tags
#include "ext_obex.h"						

typedef struct _testrefgentimes 
{
	t_object			ob;				//< The object itself (must be first)

	long				n_proxies;		//< Number of proxies
	void				**n_proxy;		//< Proxy array
	long				n_in;			//< Current proxy

	long				n_numouts;		//< Number of outlets
	void				**n_out;		//< Outlets
	
	long				maxfactor;		//< Maximum factor for random multiplications
	char				undocumented;
} t_testrefgentimes;

void *testrefgentimes_new(t_symbol *s, long argc, t_atom *argv);
void testrefgentimes_free(t_testrefgentimes *x);
void testrefgentimes_assist(t_testrefgentimes *x, void *b, long m, long a, char *s);
void testrefgentimes_outputfrom(t_testrefgentimes *x, t_symbol *s, long argc, t_atom *argv);
void testrefgentimes_int(t_testrefgentimes *x, long num);
void testrefgentimes_bang(t_testrefgentimes *x);

void *testrefgentimes_class;


int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("testrefgentimes", (method)testrefgentimes_new, (method)testrefgentimes_free, (long)sizeof(t_testrefgentimes), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	


	// *****************************
	// ********** METHODS **********
	// *****************************

	// Methods are declared via the "method" tag. Their argument, if any, can be specified via "marg" tags.
	// The "method" tag should be followed by the method symbol (single word, no spaces), and from the "digest" tag,
	// followed from a small description of the method.
	// Then a full description of the method should start on a new line, with the "description" tag.
	// The method arguments "marg" tags should be given at the end.
	
	
	// @method outputfrom @digest Output a number from a given outlet
	// @description The <m>outputfrom</m> message outputs from a given outlet (set as first parameter)
	// a given number (set as second parameter). The syntax is thus: <b>outputfrom <m>outlet_num</m> <m>value</m></b>.
	// This description should be an extensive description of the method behavior, with all its possible intricacies!
	// At the end, if the method has arguments, you should also declare them via "marg" tags (= method arguments).
	// No digest nor description is provided for "marg" specifications: this means that syntax should be clearly 
	// readable and understandable from the sole description. The "marg" declaration are useful so that help files
	// might show the arguments in the usual grey arrowed rectangle.
	// "marg" specifications need a 0-based progressive integer number identifying the position of the argument,
	// then a "name" specification, setting the name of the argument (no spaces allowed!), then an "optional"
	// specification, telling if the argument is optional, and at the end a "type" specification, setting the type
	// of the argument. All these specification must be on a single line for each method argument. 
	// @marg 0 @name outlet_num @optional 0 @type int
	// @marg 1 @name value @optional 0 @type int
	class_addmethod(c, (method) testrefgentimes_outputfrom, "outputfrom", A_GIMME, 0);


	// @method int @digest Output a random multiple of incoming number
	// @description When an integer is received in any inlet (except first and last), 
	// it is multiplied by a random factor (from 1 to <m>maxfactor</m>),
	// and sent along with such factor through the corresponding outlet couple.
	// When an integer is received in the last inlet, is simply output through the last outlet.
	// This method has no arguments, so we don't need to put any "marg" specification 
	class_addmethod(c, (method) testrefgentimes_int, "int", A_LONG, 0);


	// @method bang @digest Output results
	// @description Outputs the result depending on the most recently received input data.
	class_addmethod(c, (method) testrefgentimes_bang, "bang", 0);


	// This should and will not be tagged
    	class_addmethod(c, (method)testrefgentimes_assist,			"assist",		A_CANT, 0);  

	// If your object is a UI object, you might also want to add a "(mouse)" and/or "(keyboard)" method
	// specifying the behaviors upon mouse or keyboard operation.


	// ********************************
	// ********** ATTRIBUTES **********
	// ********************************
	
	// Attributes documentation is taken from the attribute declaration itself.
	// The digest is the LABEL you assign, the type is taken from the CLASS_ATTR declaration, and so on.
	// All you need to do is to add a "description" tag at the

	CLASS_ATTR_LONG(c, "maxfactor", 0, t_testrefgentimes, maxfactor); 
	CLASS_ATTR_STYLE_LABEL(c,"maxfactor",0,"text","Maximum Random Factor");
	CLASS_ATTR_FILTER_MIN(c,"maxfactor",1);
	CLASS_ATTR_BASIC(c,"maxfactor",0);
	// @description @copy COMMON_DOC_MAXFACTOR
	// If you have common pieces of comments, you can put them in one of the common reference files
	// and then just use the "copy" tag. You can of course continue writing below the "copy" tag
	// and all this text will be included in the description. You can even put other copy tags,
	// but only when a brand new line starts. For instance, we repeat the:
	// @copy COMMON_DOC_MAXFACTOR Beware: this text will not be shown: start a new line after a "copy" tag!!!
	// This text is correclty shown.


	// If for some reason (e.g. it is hidden), you don't want a given attribute to be documented, you should put an
	// "exclude" tag instead of a "description" tag, followed by the name of the object. The attribute
	// will be excluded from its documentation.
	// N.B.: Commented attribute declarations are STILL parsed: please use the "exclude" tag instead.

	CLASS_ATTR_CHAR(c, "myundocumentedattribute", 0, t_testrefgentimes, undocumented); 
	CLASS_ATTR_STYLE_LABEL(c,"myundocumentedattribute",0,"text","Undocumented Attribute");
	CLASS_ATTR_BASIC(c,"myundocumentedattribute",0);
	// @exclude testrefgen*
	
	
	
	class_register(CLASS_BOX, c);
	testrefgentimes_class = c;

	post("I am the testrefgen* object");
	return 0;
}

int rand_range(int min_n, int max_n)
{
    return rand() % (max_n - min_n + 1) + min_n;
}

void testrefgentimes_outputfrom(t_testrefgentimes *x, t_symbol *s, long argc, t_atom *argv){
	if (argc >= 2 && atom_gettype(argv) == A_LONG && atom_gettype(argv+1) == A_LONG) {
		long outlet_num = atom_getlong(argv) - 1;
		long value = atom_getlong(argv + 1);
		if (outlet_num >= 0 && outlet_num < x->n_numouts)
		outlet_int(x->n_out[outlet_num - 1], value);
	}
}


void testrefgentimes_anything(t_testrefgentimes *x, t_symbol *s, long argc, t_atom *argv)
{
	long inlet = proxy_getinlet((t_object *) x);
	if (argc && atom_gettype(argv) == A_LONG) {
		if (inlet == x->n_proxies) {
			outlet_int(x->n_out[x->n_numouts - 1], atom_getlong(argv));		// simply outputting incoming number
		} else {
			long random_factor = rand_range(1, x->maxfactor);
			long random_number = random_factor * atom_getlong(argv);
			outlet_int(x->n_out[x->n_numouts - 1], random_number);		// outputting random number from right outlet
			if (inlet < x->n_proxies) {
				outlet_int(x->n_out[2 * (inlet - 1) + 1], random_factor);	// outputting random factor
				outlet_int(x->n_out[2 * (inlet - 1)], random_number);		// outputting random number from specific outlet
			}
		}
	}
}

void testrefgentimes_int(t_testrefgentimes *x, long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	testrefgentimes_anything(x, gensym("list"), 1, argv);
}


void testrefgentimes_bang(t_testrefgentimes *x)
{
	long i; 
	for (i = 1; i < x->n_numouts - 1; i+=2) {
		long random_factor = rand_range(1, x->maxfactor);
		outlet_int(x->n_out[i], random_factor);				// outputting random factor
	}
}


void testrefgentimes_assist(t_testrefgentimes *x, void *b, long m, long a, char *s)
{
	// ****************************************
	// ********** INLETS AND OUTLETS **********
	// ****************************************

	// Inlets and outlets are documented via the "in" and "out" tags. The best way to do this is to comment the "assist" method.
	//
	// Such tag expects a 0-based number specifying the number of the inlet or outlet,
	// and must be *immediately* followed by a "type" tag (specifying the type of the outlet, optional) and a "digest" tag (compulsory),
	// as a short description of the inlet/outlet.
	// You can also add a "description" tag on one or more new lines, specifying a more detailed description of the outlet.
	//
	// In case your object has a variable number of inlets and outlets (e.g. depending on an argument),
	// you can assign to a portion of inlets/outlets a "loop" tag, meaning that that inlet(s)/outlet(s) must be looped till next
	// documented inlet/outlet. The "loop" tag expects an 1-based index identifying the position of the outlet in the loop.
	// For simple loops, where all inlets/outlets have the same role, just use 1. For loops where inlets/outlets are looped coupled,
	// you can define two inlets/outlets and assign them values 1 and 2 for the "loop" tag.
	//
	// In general, the order in which they appear is irrelevant, only their 0-based number matters.

	if (m == ASSIST_INLET) {
		if (a == 0)												// @in 0 @type bang @digest bang to output random factors
			sprintf(s, "bang to output random factors");		// @description You can add an optional description if you wish, but it is not mandatory.
																// In this case, a bang outputs random factor through all the factor outlets
		
		else if (a < x->n_proxies)				// @in 1 @loop 1 @type int @digest Incoming integer number
			sprintf(s, "input %ld", a);			// @description Since we added the "loop" tag, this inlet is tagged as "looped" for an indefinite
												// number of times, until the next inlet (indexed with 2) appears.
												// You only need loops if you have a variable number of inlets/outlets. Otherwise, just omit it!
												// You can also add a "copy" tag to copy a part of a common reference, located in one of the 
												// specified common reference files. If a copy tag cannot be found in the common reference files, 
												// a warning message will appear in the log.
												// For instance:
												// @copy COMMON_DOC_CANT_FIND_ME
													
		else											// @in 2 @type int @digest Output number from all outlets
			sprintf(s, "Output int from all outlets");	// @description Outputs the incoming number from all the outlets.
														// This inlet will appear in the reference marked as "Last outlet", since it comes after an inlet loop
	} else {
		if (a == x->n_proxies * 2)			
			sprintf(s, "int: Global output");			// @out 2 @type int @digest Output all random elements 
														// @description Inlets and outlets need not be documented in a specific order. 
														// This is the last outlet, indeed.
		else {
			switch (a % 2) {
				case 0: sprintf(s, "int: number %ld", a / 2 + 1);		break;	// @out 0 @loop 1 @type int @digest Random multiplied element
																				// @description @copy COMMON_DOC_RANDOM_OUTPUT
				case 1: sprintf(s, "int: factor %ld", a / 2 + 1);	break;		// @out 1 @loop 2 @type int @digest Used random multiplier 
																				// @description @copy COMMON_DOC_RANDOM_OUTPUT
			}
		}
	}
}

void testrefgentimes_free(t_testrefgentimes *x)
{
	long i;
	for (i = x->n_proxies; i > 0; i--)
		object_free(x->n_proxy[i]);
	sysmem_freeptr(x->n_proxy);
}


void *testrefgentimes_new(t_symbol *s, long argc, t_atom *argv)
{
	t_testrefgentimes *x = NULL;
    long i;
	long true_ac = attr_args_offset(argc, argv);
    
	if (x = (t_testrefgentimes *)object_alloc(testrefgentimes_class)) {

		// *******************************
		// ********** ARGUMENTS **********
		// *******************************

		// Arguments should be documented via a "arg" tag. The easiest way to do this is to put it in the "new" method.
		// The arg tag must be followed by the 0-based index of the argument, a "name" tag specifying its name
		// (no spaces!), a mandatory "optional" tag (sorry for the pun...) specifying whether this argument is optional (1) or not (0),
		// a "type" tag, specifying the type of the argument.

		// @arg 0 @name num_ins @optional 0 @type int @digest Number of incoming numbers
		// @description First argument is the number of independent inlets, which also affects the number of outlets.
		// This number does not take into account the last inlet, reserved for a number to be output only from the last outlet.

		// @arg 1 @name maxfactor @optional 1 @type int @digest Maximum factor
		// @description Third (optional) argument is reserved for the maximum factor for multiplication, as for 
		// the <m>maxfactor</m> attribute.
		// @copy COMMON_DOC_MAXFACTOR

  		long proxies = (true_ac && atom_gettype(argv) == A_LONG) ? abs(atom_getlong(argv)) + 1 : 2;		
  		long outlets = 2 * (proxies - 1) + 1;
		x->n_proxies = MIN(proxies, 100); /// Maximum 100 inlets
		x->n_numouts = MIN(outlets, 100); /// Maximum 100 outlets
		x->maxfactor = (true_ac > 1 && atom_gettype(argv + 1) == A_LONG) ? MAX(1, atom_getlong(argv+1)) : 10;
		x->undocumented = 0;
		
		x->n_proxy = (void **) sysmem_newptr((x->n_proxies + 1) * sizeof (void *));
		for (i = x->n_proxies; i > 0; i--)
			x->n_proxy[i] = proxy_new((t_object *) x, i, &x->n_in);

		x->n_out = (void **)sysmem_newptrclear(x->n_numouts * sizeof(void *));
		x->n_out[x->n_numouts - 1] = bangout(x);
		for (i = x->n_numouts - 2; i >= 0; i--) 
			x->n_out[i] = intout(x);

		attr_args_process(x, argc, argv);
	}
	return (x);
}
