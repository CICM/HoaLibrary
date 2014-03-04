'<CsoundSynthesize
<CsOptions>
</CsOptions>
<CsInstruments>
sr = 44100
ksmps = 32      
0dbfs = 1
nchnls = 8


#define HoaPi #6.283185#

/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaEnc1 - ordre 1 **/

opcode HoaEnc1, aaa, ak

ain, kangle xin

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

xout aHarmonic[0], aHarmonic[1], aHarmonic[1]

endop

/** UDO HoaEnc3 - ordre 3 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
/** UDO HoaDec1 - ordre 1 **/
/**	opcode HoaDec1, aaaa, aaa

setksmps 1

aX, aY, aZ xin

kordre = 1
kindex = kordre + 1 * 2

asig1 = kordre/2
asig2 = kordre/4

aA, aB, aC HoaEnc1 asig1, 0
aD, aE, aF HoaEnc1 asig1, 1 * $HoaPi / kindex
aG, aH, aI HoaEnc1 asig1, 2 * $HoaPi / kindex 
aJ, aK, aL HoaEnc1 asig1, 3 * $HoaPi / kindex 

a1 = asig2*aX + aB*aY + aC*aZ
a2 = asig2*aX + aE*aY + aF*aZ
a3 = asig2*aX + aH*aY + aI*aZ
a4 = asig2*aX + aK*aY + aL*aZ

xout a1, a2, a3, a4 

	endop

/** UDO HoaDec1 - ordre 1 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/
	opcode HoaDec1, aaaa, aaa

setksmps 1

aX, aY, aZ xin

kordre = 1
index = kordre + 1 * 2
kindex[] init kordre + 1 * 2

asig1 = kordre/2
asig2 = kordre/4

asortie[] init kindex

loop:
   
   a1[index], a2[index], a3[index] HoaEnc1 asig1, kindex[] * $HoaPi / kindex
   
   if(index < kindex) goto loop 


    
    asortie[] = asig2*aX + a2[]*aY + a3[]*aZ


xout asortie[0], asortie[1], asortie[2], asortie[3] 

	endop
/** UDO HoaDec1 - ordre 1 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX **/


instr 1

ain oscil 50, 440, 1
kangle = 0

aM, aN, aO HoaEnc1, ain, kangle
a1, a2, a3, a4 HoaDec1 aM, aN, aO

outq a1, a2, a3, a4

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
