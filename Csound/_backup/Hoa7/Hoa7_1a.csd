'<CsoundSynthesizer>
<CsOptions>
</CsOptions>
<CsInstruments>
sr = 44100
ksmps = 32      
0dbfs = 1
nchnls = 16

/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  **/
/** UDO HoaEnc7 - ordre 7 **/

opcode HoaEnc7, aaaaaaaaaaaaaaa, aj
ain, aangle xin

ah0 init 0
ah0 = ain * cos(0*aangle)

ahn1 init 0
ahn1 = ain * sin(1*aangle)

ah1 init 0
ah1 = ain * cos(1*aangle)

ahn2 init 0
ahn2 = ain * sin(2*aangle)

ah2 init 0
ah2 = ain * cos(2*aangle)

ahn3 init 0
ahn3 = ain * sin(3*aangle)

ah3 init 0
ah3 = ain * cos(3*aangle)

ahn4 init 0
ahn4 = ain * sin(4*aangle)

ah4 init 0
ah4 = ain * cos(4*aangle)

ahn5 init 0
ahn5 = ain * sin(5*aangle)

ah5 init 0
ah5 = ain * cos(5*aangle)

ahn6 init 0
ahn6 = ain * sin(6*aangle)

ah6 init 0
ah6 = ain * cos(6*aangle)

ahn7 init 0
ahn7 = ain * sin(7*aangle)

ah7 init 0
ah7 = ain * cos(7*aangle)


xout ah0, ahn1, ah1, ahn2, ah2, ahn3, ah3, ahn4, ah4, ahn5, ah5, ahn6, ah6, ahn7, ah7

endop

/** UDO HoaEnc3 - ordre 7 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  **/
/** UDO HoaDec7 - ordre 7 **/

	opcode HoaDec7, aaaaaaaaaaaaaaaa, aaaaaaaaaaaaaaa

aL, aM, aN, aO, aP, aQ, aR, aS, aT, aU, aV, aW, aX, aY, aZ xin

ain1 = 0.125
asig2 = 0.0625

aA1 , aBn1 , aB1 , aCn1 , aC1 , aDn1 , aD1 , aEn1 , aE1 , aFn1 , aF1 , aGn1 , aG1 , aHn1 , aH1  HoaEnc7 ain1, 0
aA2 , aBn2 , aB2 , aCn2 , aC2 , aDn2 , aD2 , aEn2 , aE2 , aFn2 , aF2 , aGn2 , aG2 , aHn2 , aH2  HoaEnc7 ain1, 0.392699
aA3 , aBn3 , aB3 , aCn3 , aC3 , aDn3 , aD3 , aEn3 , aE3 , aFn3 , aF3 , aGn3 , aG3 , aHn3 , aH3  HoaEnc7 ain1, 0.785398
aA4 , aBn4 , aB4 , aCn4 , aC4 , aDn4 , aD4 , aEn4 , aE4 , aFn4 , aF4 , aGn4 , aG4 , aHn4 , aH4  HoaEnc7 ain1, 1.178097
aA5 , aBn5 , aB5 , aCn5 , aC5 , aDn5 , aD5 , aEn5 , aE5 , aFn5 , aF5 , aGn5 , aG5 , aHn5 , aH5  HoaEnc7 ain1, 1.570796
aA6 , aBn6 , aB6 , aCn6 , aC6 , aDn6 , aD6 , aEn6 , aE6 , aFn6 , aF6 , aGn6 , aG6 , aHn6 , aH6  HoaEnc7 ain1, 1.963495
aA7 , aBn7 , aB7 , aCn7 , aC7 , aDn7 , aD7 , aEn7 , aE7 , aFn7 , aF7 , aGn7 , aG7 , aHn7 , aH7  HoaEnc7 ain1, 2.356194
aA8 , aBn8 , aB8 , aCn8 , aC8 , aDn8 , aD8 , aEn8 , aE8 , aFn8 , aF8 , aGn8 , aG8 , aHn8 , aH8  HoaEnc7 ain1, 2.748893
aA9 , aBn9 , aB9 , aCn9 , aC9 , aDn9 , aD9 , aEn9 , aE9 , aFn9 , aF9 , aGn9 , aG9 , aHn9 , aH9  HoaEnc7 ain1, 3.141592
aA10, aBn10, aB10, aCn10, aC10, aDn10, aD10, aEn10, aE10, aFn10, aF10, aGn10, aG10, aHn10, aH10 HoaEnc7 ain1, 3.534291
aA11, aBn11, aB11, aCn11, aC11, aDn11, aD11, aEn11, aE11, aFn11, aF11, aGn11, aG11, aHn11, aH11 HoaEnc7 ain1, 3.92699
aA12, aBn12, aB12, aCn12, aC12, aDn12, aD12, aEn12, aE12, aFn12, aF12, aGn12, aG12, aHn12, aH12 HoaEnc7 ain1, 4.319689
aA13, aBn13, aB13, aCn13, aC13, aDn13, aD13, aEn13, aE13, aFn13, aF13, aGn13, aG13, aHn13, aH13 HoaEnc7 ain1, 4.712388
aA14, aBn14, aB14, aCn14, aC14, aDn14, aD14, aEn14, aE14, aFn14, aF14, aGn14, aG14, aHn14, aH14 HoaEnc7 ain1, 5.105087
aA15, aBn15, aB15, aCn15, aC15, aDn15, aD15, aEn15, aE15, aFn15, aF15, aGn15, aG15, aHn15, aH15 HoaEnc7 ain1, 5.497786
aA16, aBn16, aB16, aCn16, aC16, aDn16, aD16, aEn16, aE16, aFn16, aF16, aGn16, aG16, aHn16, aH16 HoaEnc7 ain1, 5.890485

a1  = asig2*aL + aBn1*aM  + aB1*aN  + aCn1*aO  + aC1*aP  + aDn1*aQ  + aD1*aR  + aEn1*aS  + aE1*aT  + aFn1*aU  + aF1*aV  + aGn1*aW + aG1*aX  + aHn1*aY  + aH1*aZ 
a2  = asig2*aL + aBn2*aM  + aB2*aN  + aCn2*aO  + aC2*aP  + aDn2*aQ  + aD2*aR  + aEn2*aS  + aE2*aT  + aFn2*aU  + aF2*aV  + aGn2*aW + aG2*aX  + aHn2*aY  + aH2*aZ 
a3  = asig2*aL + aBn3*aM  + aB3*aN  + aCn3*aO  + aC3*aP  + aDn3*aQ  + aD3*aR  + aEn3*aS  + aE3*aT  + aFn3*aU  + aF3*aV  + aGn3*aW + aG3*aX  + aHn3*aY  + aH3*aZ
a4  = asig2*aL + aBn4*aM  + aB4*aN  + aCn4*aO  + aC4*aP  + aDn4*aQ  + aD4*aR  + aEn4*aS  + aE4*aT  + aFn4*aU  + aF4*aV  + aGn4*aW + aG4*aX  + aHn4*aY  + aH4*aZ 
a5  = asig2*aL + aBn5*aM  + aB5*aN  + aCn5*aO  + aC5*aP  + aDn5*aQ  + aD5*aR  + aEn5*aS  + aE5*aT  + aFn5*aU  + aF5*aV  + aGn5*aW + aG5*aX  + aHn5*aY  + aH5*aZ
a6  = asig2*aL + aBn6*aM  + aB6*aN  + aCn6*aO  + aC6*aP  + aDn6*aQ  + aD6*aR  + aEn6*aS  + aE6*aT  + aFn6*aU  + aF6*aV  + aGn6*aW + aG6*aX  + aHn6*aY  + aH6*aZ
a7  = asig2*aL + aBn7*aM  + aB7*aN  + aCn7*aO  + aC7*aP  + aDn7*aQ  + aD7*aR  + aEn7*aS  + aE7*aT  + aFn7*aU  + aF7*aV  + aGn7*aW + aG7*aX  + aHn7*aY  + aH7*aZ 
a8  = asig2*aL + aBn8*aM  + aB8*aN  + aCn8*aO  + aC8*aP  + aDn8*aQ  + aD8*aR  + aEn8*aS  + aE8*aT  + aFn8*aU  + aF8*aV  + aGn8*aW + aG8*aX  + aHn8*aY  + aH8*aZ
a9  = asig2*aL + aBn9*aM  + aB9*aN  + aCn9*aO  + aC9*aP  + aDn9*aQ  + aD9*aR  + aEn9*aS  + aE9*aT  + aFn9*aU  + aF9*aV  + aGn9*aW + aG9*aX  + aHn9*aY  + aH9*aZ
a10 = asig2*aL + aBn10*aM + aB10*aN + aCn10*aO + aC10*aP + aDn10*aQ + aD10*aR + aEn10*aS + aE10*aT + aFn10*aU + aF10*aV + aGn10*aW+ aG10*aX + aHn10*aY + aH10*aZ
a11 = asig2*aL + aBn11*aM + aB11*aN + aCn11*aO + aC11*aP + aDn11*aQ + aD11*aR + aEn11*aS + aE11*aT + aFn11*aU + aF11*aV + aGn11*aW+ aG11*aX + aHn11*aY + aH11*aZ
a12 = asig2*aL + aBn12*aM + aB12*aN + aCn12*aO + aC12*aP + aDn12*aQ + aD12*aR + aEn12*aS + aE12*aT + aFn12*aU + aF12*aV + aGn12*aW+ aG12*aX + aHn12*aY + aH12*aZ
a13 = asig2*aL + aBn13*aM + aB13*aN + aCn13*aO + aC13*aP + aDn13*aQ + aD13*aR + aEn13*aS + aE13*aT + aFn13*aU + aF13*aV + aGn13*aW+ aG13*aX + aHn13*aY + aH13*aZ
a14 = asig2*aL + aBn14*aM + aB14*aN + aCn14*aO + aC14*aP + aDn14*aQ + aD14*aR + aEn14*aS + aE14*aT + aFn14*aU + aF14*aV + aGn14*aW+ aG14*aX + aHn14*aY + aH14*aZ
a15 = asig2*aL + aBn15*aM + aB15*aN + aCn15*aO + aC15*aP + aDn15*aQ + aD15*aR + aEn15*aS + aE15*aT + aFn15*aU + aF15*aV + aGn15*aW+ aG15*aX + aHn15*aY + aH15*aZ
a16 = asig2*aL + aBn16*aM + aB16*aN + aCn16*aO + aC16*aP + aDn16*aQ + aD16*aR + aEn16*aS + aE16*aT + aFn16*aU + aF16*aV + aGn16*aW+ aG16*aX + aHn16*aY + aH16*aZ 

xout a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16

	endop

/** UDO HoaDec3 - ordre 3 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  **/

instr 1


ain oscil 500, 440, 1
kangle1 phasor 1

kangle = kangle1 * 6.283185

aL, aM, aN, aO, aP, aQ, aR, aS, aT, aU, aV, aW, aX, aY, aZ HoaEnc7 ain, kangle

a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16 HoaDec7 aL, aM, aN, aO, aP, aQ, aR, aS, aT, aU, aV, aW, aX, aY, aZ

outch 1, a1, 2, a2, 3, a3, 4, a4, 5, a5, 6, a6, 7, a7, 8, a8, 9, a9, 10, a10, 11, a11, 12, a12, 13, a13, 14, a14, 15, a15, 16, a16 

endin

</CsInstruments>
<CsScore>
f1 0 16384 10 1


i1 0 60

e

</CsScore>
</CsoundSynthesizer>

