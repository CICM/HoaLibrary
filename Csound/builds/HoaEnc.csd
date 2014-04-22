e<CsoundSynthesizer>
<CsOptions>

--opcode-lib=HoaEnc.dylib



</CsOptions>
<CsInstruments>
sr = 44100
kr = 4410
ksmps = 10
nchnls = 2

instr 1

        anoise pinkish 1000
        
        kazimuth = 100
        iordre = 1

        a1, a2, a3 hoaenc anoise
        

        outs a1, a2
endin

</CsInstruments>
<CsScore>


i 1 0 20
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
