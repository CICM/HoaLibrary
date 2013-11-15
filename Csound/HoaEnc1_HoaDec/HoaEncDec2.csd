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
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaDec1 - ordre 1 **/

	opcode HoaDec1, aa, aaa

setksmps 1

aX, aY, aZ xin

asig1 = 0.5
asig2 = 0.25

kangle1 = 0
kangle2 = 1.570796
kangle3 = 3.141592
kangle4 = 4.712388

aA init 0 
aB init 0
aC init 0
	aA init 0
	aA  = asig1 * cos(0*kangle1)
	aB init 0
	aB = asig1 * sin(1*kangle1)
	aC init 0
	aC  = asig1 * cos(1*kangle1)


aD init 0
aE init 0
aF init 0
	aD init 0
	aD  = asig1 * cos(0*kangle2)
	aE init 0
	aE = asig1 * sin(1*kangle2)
	aF init 0
	aF  = asig1 * cos(1*kangle2)



a11 init 0
a22 init 0
a33 init 0
a44 init 0

a11 = asig2*aX + aB*aY + aC*aZ
a22 = asig2*aX + aE*aY + aF*aZ

xout a11, a22

	endop

/** UDO HoaDec1 - ordre 1 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/

instr 1


ain inch 1
kangle chnget "angle"

aM, aN, aO HoaEnc1 ain, kangle


a1, a2 HoaDec1 aM, aN, aO

outs a1, a2

endin

</CsInstruments>
<CsScore>
f1 0 16384 10 1


i1 0 60

e

</CsScore>
</CsoundSynthesizer>

