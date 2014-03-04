<CsoundSynthesizer>
<CsOptions>
</CsOptions>
<CsInstruments>
sr = 44100
ksmps = 32      
0dbfs = 1
nchnls = 7
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaWide3 - ordre 3 **/

opcode HoaWide3, aaaaaaa, aaaaaaak

aA, aB, aC, aD, aE, aF, aG, kWide xin
	
kWide limit kWide, 0, 1

aWB = (kWide * log(3 + 1) - log(1)) / (log(1 + 1) - log(1))
aWB limit aWB, 0, 1
aWC = (kWide * log(3 + 1) - log(1)) / (log(1 + 1) - log(1))
aWC limit aWC, 0, 1
aWD = (kWide * log(3 + 1) - log(2)) / (log(2 + 1) - log(2))
aWD limit aWD, 0, 1
aWE = (kWide * log(3 + 1) - log(2)) / (log(2 + 1) - log(2))
aWE limit aWE, 0, 1
aWF = (kWide * log(3 + 1) - log(3)) / (log(3 + 1) - log(3))
aWF limit aWF, 0, 1
aWG = (kWide * log(3 + 1) - log(3)) / (log(3 + 1) - log(3))
aWG limit aWG, 0, 1

aWeight = log(3 + 1) * (1 - kWide) + 1

a1 = aA * aWeight
a2 = aB * aWeight * aWB
a3 = aC * aWeight * aWC
a4 = aD * aWeight * aWD
a5 = aE * aWeight * aWE
a6 = aF * aWeight * aWF
a7 = aG * aWeight * aWG


xout a1, a2, a3, a4, a5, a6, a7

endop

/** UDO HoaWide3 - ordre 3 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaEnc3 - ordre 3 **/

opcode HoaEnc3, aaaaaaa, ak

setksmps 1

ain, kangle xin


ah0 = ain * cos(0*kangle)
ahn1 = ain * sin(1*kangle)
ah1 = ain * cos(1*kangle)
ahn2 = ain * sin(2*kangle)
ah2 = ain * cos(2*kangle)
ahn3 = ain * sin(3*kangle)
ah3 = ain * cos(3*kangle)


xout ah0, ahn1, ah1, ahn2, ah2, ahn3, ah3

endop

/** UDO HoaEnc3 - ordre 3 **/


instr 1



aA inch 1
aB inch 2
aC inch 3
aD inch 4
aE inch 5
aF inch 6
aG inch 7

kwide chnget "wide"


a1, a2, a3, a4, a5, a6, a7 HoaWide3 aA, aB, aC, aD, aE, aF, aG, kwide


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
