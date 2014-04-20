
// ------------------------------------------ hoa.highpass~ ------------------------------------------ //

/**
 @file      hoa.highpass~.cpp
 @name      hoa.highpass~
 @realname  hoa.highpass~
 @type      abstraction
 @module    hoa
 @author    Julien Colafrancesco, Pierre Guillot, Eliott Paris.
 
 @digest
 A multichannel version of the <o>onepole~</o> object.
 
 @description
 <o>hoa.highpass~</o> is a multichannel version of the <o>onepole~</o> object.
 This patcher requires to be loaded by a <o>hoa.process~</o> object to work.
 
 @discussion
 <o>hoa.highpass~</o> is a multichannel version of the <o>onepole~</o> object.
 This patcher requires to be loaded by a <o>hoa.process~</o> object to work.
 
 @category ambisonics, hoa objects, audio, MSP, abstraction
 
 @seealso onepole~, hoa.onepole~
 */

// @arg 0 @name initial-cutoff-frequency @optional 1 @type float @digest The initial cutoff frequency.
// @description First argument is the initial cutoff frequency.