# Hoa Library 

A high order ambisonics library.

Hoa Library is a collection of C++ classes and MAX/MSP objects destined to high order ambisonic sound reproduction. 
It‘s totally free and made availlable by CICM, a research center bi-localized between Paris VIII University and the MSH (Maison des sciences de l‘Homme).

## Libraries : 

### Mac OsX Install

#### GSL (http://www.gnu.org/software/gsl/) : 

	1 . Download (ftp://ftp.gnu.org/gnu/gsl/gsl-1.15.tar.gz)
	2 . Unpack gsl-1.15.tar.gz
	3 . Use the Terminal and change the directory (cd gsl-1.15)
	4 . ./configure CFLAGS="-m32 -g -O2"
	5 . make
	6 . sudo make install

#### GFORTRAN (http://gcc.gnu.org/wiki/GFortranBinariesMacOS) :

	1 . Download (http://quatramaran.ens.fr/~coudert/gfortran/gfortran-and-gcc-4-6-2-RC20111019-Sno-x86-64.dmg)
	2 . Install the package

#### ATLAS and LAPACK (http://math-atlas.sourceforge.net/)

	1 . Download (http://sourceforge.net/projects/math-atlas/files/latest/download?source=files)
	2 . Download (http://www.netlib.org/lapack/lapack-3.4.2.tgz)
	3 . Create tempory directory
	4 . Put the two packages and unpack atlas3.10.0.tar.bz2
	5 . Use the Terminal and change the directory (cd atlas3.10.0)
	6 . mkdir bld
	7 . cd bld
	8 . ../configure -b 64 --shared --prefix=/usr/local/atlas-3.10.0 \
    --with-netlib-lapack-tarfile=../../lapack-3.4.2.tgz
    9 . make build
