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

opcode HoaWide3, aaaaaaa, aaaaaaakk

aA, aB, aC, aD, aE, aF, aG, kouv, kdist xin

kg = 1/kdist^2

aWA = 1
aWB = (kouv * log(3 + 1)) - (log(1) * 1 / log(1 + 1) - log(1))
aWC = (kouv * log(3 + 1)) - (log(1) * 1 / log(1 + 1) - log(1)) 
aWD = (kouv * log(3 + 1)) - (log(2) * 1 / log(2 + 1) - log(2))
aWE = (kouv * log(3 + 1)) - (log(2) * 1 / log(2 + 1) - log(2))
aWF = (kouv * log(3 + 1)) - (log(3) * 1 / log(3 + 1) - log(3))
aWG = (kouv * log(3 + 1)) - (log(3) * 1 / log(3 + 1) - log(3))

a1 = (aA * (1 - kouv)) * ((log(3 + 1) + 1) * aWA)
a2 = (aB * (1 - kouv)) * ((log(3 + 1) + 1) * aWB)
a3 = (aC * (1 - kouv)) * ((log(3 + 1) + 1) * aWC)
a4 = (aD * (1 - kouv)) * ((log(3 + 1) + 1) * aWD)
a5 = (aE * (1 - kouv)) * ((log(3 + 1) + 1) * aWE)
a6 = (aF * (1 - kouv)) * ((log(3 + 1) + 1) * aWF)
a7 = (aG * (1 - kouv)) * ((log(3 + 1) + 1) * aWG)


xout a1*kg, a2*kg, a3*kg, a4*kg, a5*kg, a6*kg, a7*kg

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



a1 inch 1
kangle chnget "angle"
kdist chnget "dist"
kouv chnget "ouv"

aA, aB, aC, aD, aE, aF, aG HoaEnc3 a1, kangle
a1, a2, a3, a4, a5, a6, a7 HoaWide3 aA, aB, aC, aD, aE, aF, aG, kouv, kdist


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
