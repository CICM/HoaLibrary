'<CsoundSynthesizer>
<CsOptions>
</CsOptions>
<CsInstruments>
sr = 44100
ksmps = 32      
0dbfs = 1
nchnls = 4

/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaEnc3 - ordre 1 **/

#define HoaPi #6.283185#

	opcode HoaEnc1, aaa, ak
	
ain, kangle xin 

setksmps 1

ah0 init 0
ah0  = ain * cos(0*kangle)
ahn1 init 0
ahn1 = ain * sin(1*kangle)
ahn init 0
ah1  = ain * cos(1*kangle)


xout ah0, ahn1, ah1

	endop
	
/** UDO HoaWider1 - ordre 1 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/



/** UDO HoaEnc1 - ordre 1 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/


instr 1


ain inch 1
kangle chnget "angle"

aX, aY, aZ HoaEnc1 ain, kangle, kordre

kordre = 1
kindex[] = kordre + 1 * 2

asig1 = kindex / 2
asig2 = kindex / 4

kangle1 = 0    ; 0
kangle2 = 1.570796 ; kindex[] * $HoaPi / ( korder + 1 * 2)
kangle3 = 3.141592
kangle4 = 4.712388

aA init 0 
aB init 0
aC init 0
	aA = asig1 * cos(0*kangle1)
	aB = asig1 * sin(1*kangle1)
	aC = asig1 * cos(1*kangle1)


aD init 0
aE init 0
aF init 0
	aD = asig1 * cos(0*kangle2)
	aE = asig1 * sin(1*kangle2)
	aF = asig1 * cos(1*kangle2)

aG init 0
aH init 0
aI init 0
	aG = asig1 * cos(0*kangle3)
	aH = asig1 * sin(1*kangle3)
	aI = asig1 * cos(1*kangle3)

aJ init 0
aK init 0
aL init 0
	aJ = asig1 * cos(0*kangle4)
	aK = asig1 * sin(1*kangle4)
	aL = asig1 * cos(1*kangle4)

a11 init 0
a22 init 0
a33 init 0
a44 init 0

a11 = (asig2*aX) + (aB*aY) + (aC*aZ)
a22 = (asig2*aX) + (aE*aY) + (aF*aZ)
a33 = (asig2*aX) + (aH*aY) + (aI*aZ)
a44 = (asig2*aX) + (aK*aY) + (aL*aZ)
 
outch 1, a11*1, 2, a22*1, 3, a33*1, 4, a44*1 

endin

</CsInstruments>
<CsScore>
f1 0 16384 10 1


i1 0 60

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
