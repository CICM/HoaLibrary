'<CsoundSynthesizer>
<CsOptions>
</CsOptions>
<CsInstruments>
sr = 44100
ksmps = 32      
0dbfs = 1
nchnls = 8

/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaEnc3 - ordre 3 **/

opcode HoaEnc3, aaaaaaa, ak
ain, kangle xin

ah0 init 0
ah0 = ain * cos(0*kangle)

ahn1 init 0
ahn1 = ain * sin(1*kangle)

ahn init 0
ah1 = ain * cos(1*kangle)

ahn2 init 0
ahn2 = ain * sin(2*kangle)

ah2 init 0
ah2 = ain * cos(2*kangle)

ahn3 init 0
ahn3 = ain * sin(3*kangle)

ah3 init 0
ah3 = ain * cos(3*kangle)


xout ah0, ahn1, ah1, ahn2, ah2, ahn3, ah3

endop

/** UDO HoaEnc3 - ordre 3 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaDec1 - ordre 3 **/

	opcode HoaDec3, aaaaaaaa, aaaaaaa

aT, aU, aV, aW, aX, aY, aZ xin

ain1 = 0.25
asig2 = 0.125

aA1, aB1, aC1, aD1, aE1, aF1, aG1 HoaEnc3 ain1, 0
aA2, aB2, aC2, aD2, aE2, aF2, aG2 HoaEnc3 ain1, 0.785398
aA3, aB3, aC3, aD3, aE3, aF3, aG3 HoaEnc3 ain1, 1.570796
aA4, aB4, aC4, aD4, aE4, aF4, aG4 HoaEnc3 ain1, 2.356194
aA5, aB5, aC5, aD5, aE5, aF5, aG5 HoaEnc3 ain1, 3.141592
aA6, aB6, aC6, aD6, aE6, aF6, aG6 HoaEnc3 ain1, 3.92699
aA7, aB7, aC7, aD7, aE7, aF7, aG7 HoaEnc3 ain1, 4.712388
aA8, aB8, aC8, aD8, aE8, aF8, aG8 HoaEnc3 ain1, 5.497786

a1 = asig2*aT + aB1*aU + aC1*aV + aD1*aW + aE1*aX + aF1*aY + aG1*aZ
a2 = asig2*aT + aB2*aU + aC2*aV + aD2*aW + aE2*aX + aF2*aY + aG2*aZ
a3 = asig2*aT + aB3*aU + aC3*aV + aD3*aW + aE3*aX + aF3*aY + aG3*aZ
a4 = asig2*aT + aB4*aU + aC4*aV + aD4*aW + aE4*aX + aF4*aY + aG4*aZ
a5 = asig2*aT + aB5*aU + aC5*aV + aD5*aW + aE5*aX + aF5*aY + aG5*aZ
a6 = asig2*aT + aB6*aU + aC6*aV + aD6*aW + aE6*aX + aF6*aY + aG6*aZ
a7 = asig2*aT + aB7*aU + aC7*aV + aD7*aW + aE7*aX + aF7*aY + aG7*aZ
a8 = asig2*aT + aB8*aU + aC8*aV + aD8*aW + aE8*aX + aF8*aY + aG8*aZ

xout a1, a2, a3, a4, a5, a6, a7, a8

	endop

/** UDO HoaDec3 - ordre 3 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/

instr 1


ain inch 1
kangle chnget "angle"

aM, aN, aO, aP, aQ, aR, aS HoaEnc3 ain, kangle


outch 1, aM, 2, aN, 3, aO, 4, aP, 5, aQ, 6, aR, 7, aS

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
;[winxound_bookmarks,52,53]