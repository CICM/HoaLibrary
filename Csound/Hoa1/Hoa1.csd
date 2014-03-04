<CsoundSynthesizer>
<CsOptions>
</CsOptions>
<CsInstruments>
sr = 44100
ksmps = 32      
0dbfs = 1
nchnls = 4

/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaEnc1 - ordre 1 **/

	opcode HoaEnc1, aaa, ak
	
setksmps 1

ain, kangle xin 

ah0  = ain * cos(0*kangle)
ah_1 = ain * sin(1*kangle)
ah1  = ain * cos(1*kangle)


xout ah0, ah_1, ah1

	endop

/** UDO HoaEnc1 - ordre 1 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaWide1 - ordre 1 **/

	opcode HoaWide1, aaa, aaak

aA, aB, aC, kWide xin
	
kWide limit kWide, 0, 1

aWB = (kWide * log(1 + 1) - log(1)) / (log(1 + 1) - log(1))
aWB limit aWB, 0, 1
aWC = (kWide * log(1 + 1) - log(1)) / (log(1 + 1) - log(1))
aWC limit aWC, 0, 1

aWeight = log(1 + 1) * (1 - kWide) + 1

a1 = aA * aWeight
a2 = aB * aWeight * aWB
a3 = aC * aWeight * aWC


xout a1, a2, a3


	endop

/** UDO HoaWide1 - ordre 1 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaMap1 - ordre 3 **/

	opcode HoaMap1, aaaaaaa, akk
	
aSig, kradius, kangle xin

kwide limit kradius, 0, 1
kdist max kradius, 1
kdist = kdist*kdist
aSignal = aSig / kdist

a1, a2, a3 HoaEnc1 aSignal, kangle

a1, a2, a3 HoaWide1 a1, a2, a3, kwide

xout a1, a2, a3

endop

/** UDO HoaMap3 - ordre 3 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaDec1 - ordre 1 **/

	opcode HoaDec1, aaaa, aaa

setksmps 1

aX, aY, aZ xin

asig1 = 0.5
asig2 = 0.25

aA, aB, aC HoaEnc1 asig1, 0
aD, aE, aF HoaEnc1 asig1, 1.570796
aG, aH, aI HoaEnc1 asig1, 3.141592
aJ, aK, aL HoaEnc1 asig1, 4.712388

a1 = asig2*aX + aB*aY + aC*aZ
a2 = asig2*aX + aE*aY + aF*aZ
a3 = asig2*aX + aH*aY + aI*aZ
a4 = asig2*aX + aK*aY + aL*aZ

xout a1, a2, a3, a4 

	endop

/** UDO HoaDec1 - ordre 1 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/


</CsInstruments>
<CsScore>

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
