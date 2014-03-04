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

	opcode HoaEnc7, aaaaaaaaaaaaaaa, ak
	
setksmps 1

ain, kangle xin

ah0 = ain * cos(0*kangle)
ah_1 = ain * sin(1*kangle)
ah1 = ain * cos(1*kangle)
ah_2 = ain * sin(2*kangle)
ah2 = ain * cos(2*kangle)
ah_3 = ain * sin(3*kangle)
ah3 = ain * cos(3*kangle)
ah_4 = ain * sin(4*kangle)
ah4 = ain * cos(4*kangle)
ah_5 = ain * sin(5*kangle)
ah5 = ain * cos(5*kangle)
ah_6 = ain * sin(6*kangle)
ah6 = ain * cos(6*kangle)
ah_7 = ain * sin(7*kangle)
ah7 = ain * cos(7*kangle)


xout ah0, ah_1, ah1, ah_2, ah2, ah_3, ah3, ah_4, ah4, ah_5, ah5, ah_6, ah6, ah_7, ah7

	endop

/** UDO HoaEnc3 - ordre 7 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  **/
/** UDO HoaWide7 - ordre 7 **/

	opcode HoaWide7, aaaaaaaaaaaaaaa, aaaaaaaaaaaaaaak

aA, aB, aC, aD, aE, aF, aG, aH, aI, aJ, aK, aL, aM, aN, aO, kWide xin
	
kWide limit kWide, 0, 1

aWB = (kWide * log(7 + 1) - log(1)) / (log(1 + 1) - log(1))
aWB limit aWB, 0, 1
aWC = (kWide * log(7 + 1) - log(1)) / (log(1 + 1) - log(1))
aWC limit aWC, 0, 1
aWD = (kWide * log(7 + 1) - log(2)) / (log(2 + 1) - log(2))
aWD limit aWD, 0, 1
aWE = (kWide * log(7 + 1) - log(2)) / (log(2 + 1) - log(2))
aWE limit aWE, 0, 1
aWF = (kWide * log(7 + 1) - log(3)) / (log(3 + 1) - log(3))
aWF limit aWF, 0, 1
aWG = (kWide * log(7 + 1) - log(3)) / (log(3 + 1) - log(3))
aWG limit aWG, 0, 1
aWH = (kWide * log(7 + 1) - log(4)) / (log(4 + 1) - log(4))
aWH limit aWF, 0, 1
aWI = (kWide * log(7 + 1) - log(4)) / (log(4 + 1) - log(4))
aWI limit aWG, 0, 1
aWJ = (kWide * log(7 + 1) - log(5)) / (log(5 + 1) - log(5))
aWJ limit aWF, 0, 1
aWK = (kWide * log(7 + 1) - log(5)) / (log(5 + 1) - log(5))
aWK limit aWG, 0, 1
aWL = (kWide * log(7 + 1) - log(6)) / (log(6 + 1) - log(6))
aWL limit aWF, 0, 1
aWM = (kWide * log(7 + 1) - log(6)) / (log(6 + 1) - log(6))
aWM limit aWG, 0, 1
aWN = (kWide * log(7 + 1) - log(7)) / (log(7 + 1) - log(7))
aWN limit aWF, 0, 1
aWO = (kWide * log(7 + 1) - log(7)) / (log(7 + 1) - log(7))
aWO limit aWG, 0, 1

aWeight = log(7 + 1) * (1 - kWide) + 1

a1  = aA * aWeight
a2  = aB * aWeight * aWB
a3  = aC * aWeight * aWC
a4  = aD * aWeight * aWD
a5  = aE * aWeight * aWE
a6  = aF * aWeight * aWF
a7  = aG * aWeight * aWG
a8  = aH * aWeight * aWH
a9  = aI * aWeight * aWI
a10 = aJ * aWeight * aWJ
a11 = aK * aWeight * aWK
a12 = aL * aWeight * aWL
a13 = aM * aWeight * aWM
a14 = aN * aWeight * aWN
a15 = aO * aWeight * aWO


xout a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15


	endop

/** UDO HoaWide7 - ordre 7 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  **/
/** UDO HoaMap7 - ordre 7 **/

	opcode HoaMap7, aaaaaaaaaaaaaaa, akk
	
aSig, kradius, kangle xin

kwide limit kradius, 0, 1
kdist max kradius, 1
kdist = kdist*kdist
aSignal = aSig / kdist

a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15 HoaEnc7 aSignal, kangle

a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15 HoaWide7 a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, kwide

xout a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15

	endop

/** UDO HoaMap7 - ordre 7 **/
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

/** UDO HoaDec7 - ordre 7 **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  **/
/** XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  **/


</CsInstruments>
<CsScore>

</CsScore>
</CsoundSynthesizer>
xs