<CsoundSynthesizer>
<CsOptions>

--opcode-lib=osc.dylib

-odac


</CsOptions>
<CsInstruments>
sr = 44100
kr = 4410


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



asig osc 500, 440, 1

outs asig, asig

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
