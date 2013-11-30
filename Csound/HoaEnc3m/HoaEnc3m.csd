<CsoundSynthesizer>
<CsOptions>
</CsOptions>
<CsInstruments>
sr = 44100
ksmps = 32      
0dbfs = 1
nchnls = 7

/** UDO HoaEnc3 - ordre 3 **/

opcode HoaEnc3, aaaaaaa, akk
ain, kangle, kdist xin

kg = 1/kdist^2

aHarmonic[] init 0
index  =  0
loop:
    	
    	if(index % 2 == 0) goto positif
	if(index % 2 != 0) goto negatif
	
positif:
	aHarmonic[index] = ain * cos(index * kangle)
negatif:
    	aHarmonic[index] = ain * sin(abs(index) * kangle)
 
	index = index+1
	
	if(index < 7) goto loop

xout aHarmonic[0]*kg, aHarmonic[1]*kg, aHarmonic[2]*kg, aHarmonic[3]*kg, aHarmonic[4]*kg, aHarmonic[5]*kg, aHarmonic[6]*kg

endop

/** UDO HoaEnc3 - ordre 3 **/


instr 1

ain inch 1
axangle inch 2
kdist chnget "dist"

a1, a2, a3, a4, a5, a6, a7 HoaEnc3 ain, axangle, kdist

outch 1, a1, 2, a2, 3, a3, 4, a4, 5, a5, 6, a6, 7, a7

endin



</CsInstruments>
<CsScore>
f1 0 16384 10 1


i1 0 30
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
