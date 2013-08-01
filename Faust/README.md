### Hoa Library for FAUST 

<p><a title="FAUST" href="http://faust.grame.fr/" target="_blank">FAUST</a> (Functional Audio Stream) developed at <a title="GRAME" href="http://www.grame.fr/" target="_blank">GRAME</a> is a functional programming language specifically designed for real-time signal processing and synthesis. FAUST targets high-performance signal processing applications and audio plug-ins for a variety of platforms and standards.</p>

<p>The hoa.lib file contains the high order ambisonics functions in FAUST. This file should already be included in the last FAUST distribution. You just need to include hoa.lib before coding to use it.</p>

#### Functions

<p>encoder : encodes a signal in the circular harmonics domain depending on an order of decomposition and an angle.</p>

<p>decoder : decodes an ambisonics sound field for a circular array of loudspeakers.</p> 

<p>decoderStereo : decodes an ambisonic sound field for stereophonic configuration.</p> 

<p>optimBasic, optimMaxRe, optimInPhase : weights the circular harmonics signals depending to the ambisonics optimization. It can be "basic" for no optimization, "maxRe" or "inPhase".</p>

<p>wider : can be used to wide the diffusion of a localised sound. The order depending signals are weighted and appear in a logarithmic way to have linear changes.</p>

<p>map : encodes a source with distance compensation.</p>

<p>rotate : applies a rotation of the sound field.</p>

#### Authors :

##### Julien Colafrancesco, Pierre Guillot, Eliott Paris

#### Thanks :

##### Yann Orlarey, Dominique Fober, Stéphane Letz
