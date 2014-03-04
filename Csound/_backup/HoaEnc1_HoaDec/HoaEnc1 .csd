<CsoundSynthesizer>
<CsOptions>
</CsOptions>
<CsInstruments>

/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaEnc3 - ordre 1 **/

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

/** UDO HoaEnc1 - ordre 1 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaDec1 - ordre 1 **/

	opcode HoaDec1, aaaa, aaaa

ain, aX, aY, aZ xin

ain1 = ain*0.5

aA, aB, aC HoaEnc1 ain1, 0
aD, aE, aF HoaEnc1 ain1, 1.570796
aG, aH, aI HoaEnc1 ain1, 3.141592
aJ, aK, aL HoaEnc1 ain1, 4.712388

a1 = ain*0.25 + aB*aY + aC*aZ
a2 = ain*0.25 + aE*aY + aF*aZ
a3 = ain*0.25 + aH*aY + aI*aZ
a4 = ain*0.25 + aJ*aY + aL*aZ

xout a1, a2, a3, a4 

	endop

/** UDO HoaDec1 - ordre 1 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/


instr 1

ain inch 1
kangle chnget "angle"

a1, a2, a3 HoaEnc1 ain, kangle

outch 1, a1, 2, a2, 3, a3

endin

</CsInstruments>
<CsScore>
f1 0 16384 10 1


i1 0 60
e

</CsScore>
</CsoundSynthesizer>

