<CsoundSynthesizer>
<CsOptions>

-odac


</CsOptions>
<CsInstruments>
sr = 44100
kr = 4410

idsp,a1 faustgen "process=+;",ain1,ain2


ifac faustcompile "process=+;", "-vec -lv 1"
idsp,a1 faustaudio ifac,ain1,ain2

gout faustcompile {{

import("hoa.lib") ;
import("filter.lib") ;
import("oscillator.lib");

r1 = hslider("Radius", 1.0, 0, 5, 0.001) : smooth(tau2pole(0.02));
a1 = hslider("Angle", 62831, -6.28318530717959, 6.28318530717959, 0.001) : smooth(tau2pole(0.02));

process(sig) = map(7, sig, r1, a1) : optimInPhase(7) : decoderStereo(7);
}} "-vec -lv 1"

instr 1 

aordre = 1
asig oscil 500, 440, 1
aangle = 100

ka = 1
kb = 0
kc = 0
kd = 0
ke = 0
kf = 0
kg = 0



asig OneSourceToStereo 500, 440, 1

outs a1, a2

endin

</CsInstruments>
<CsScore>
f1 0 512 10 1

i 1 0 10

e 


</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>100</x>
 <y>100</y>
 <width>320</width>
 <height>240</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="nobackground">
  <r>255</r>
  <g>255</g>
  <b>255</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
