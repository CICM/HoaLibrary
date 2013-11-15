<CsoundSynthesizer>
<CsOptions>
</CsOptions>
<CsInstruments>
sr = 44100
ksmps = 32      
0dbfs = 1
nchnls = 7

/** UDO HoaEnc3 - ordre 3 **/

opcode HoaEnc3m, aaaaaaa, akk

setksmps 1

ain, kangle, kdist xin

kg = 1/kdist^2

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


xout ah0*kg, ahn1*kg, ah1*kg, ahn2*kg, ah2*kg, ahn3*kg, ah3*kg

endop

/** UDO HoaEnc3 - ordre 3 **/


instr 1



ain inch 1
kangle chnget "angle"
kdist chnget "dist"

a1, a2, a3, a4, a5, a6, a7 HoaEnc3m a1, kangle, kdist

outch 1, a1, 2, a2, 3, a3, 4, a4, 5, a5, 6, a6, 7, a7

endin



</CsInstruments>
<CsScore>
f1 0 16384 10 1


i1 0 30
e


</CsScore>
</CsoundSynthesizer>